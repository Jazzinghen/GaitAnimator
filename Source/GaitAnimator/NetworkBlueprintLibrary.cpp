// Fill out your copyright notice in the Description page of Project Settings.

#include "GaitAnimator.h"
#include "NetworkBlueprintLibrary.h"
#include "Runtime/Networking/Public/Networking.h"

FSocket* UNetworkBlueprintLibrary::ServerSocket;

bool UNetworkBlueprintLibrary::NetworkSetup(int32 ServerPort) {

	bool res = false;


	// Creating a Socket pointer, wich will temporary contain our 
	FSocket* Socket = nullptr;
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	
	// Instead of that useless FTcpSocketBuilder I will try to create the socket by hand and then debug it... >:(
	if (SocketSubsystem != nullptr) {
		// Try to create a stream socket using the system-intependent interface
		Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("Server Socket"), false);

		if (Socket != nullptr) {
			FIPv4Address ServerAddress = FIPv4Address(127, 0, 0, 1);
			TSharedRef<FInternetAddr> LocalAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
			uint16 castServerPort = (uint16)ServerPort;

			// Attach received port and IPAddress to Internet Address pointer
			LocalAddress->SetIp(ServerAddress.GetValue());
			LocalAddress->SetPort(castServerPort);
			
			bool SocketCreationError = !Socket->Connect(*LocalAddress);

			if (SocketCreationError)
			{
				GLog->Logf(TEXT("Failed to create %s as configured!"), Socket->GetDescription());

				SocketSubsystem->DestroySocket(Socket);

				Socket = nullptr;
			}
		}
	}



	if (Socket != nullptr){
		UNetworkBlueprintLibrary::ServerSocket = Socket;
		res = true;
	}
	else {
		res = false;
	}

	return res;
}

bool UNetworkBlueprintLibrary::NewDataAvailable(){

	uint32 NetData;

	return UNetworkBlueprintLibrary::ServerSocket->HasPendingData(NetData);
}

bool UNetworkBlueprintLibrary::GetRotationPacket(TArray<FRotator> &newData){

	bool bDataPresent;
	bool res;
	uint32 NetData;
	
	bDataPresent = UNetworkBlueprintLibrary::ServerSocket->HasPendingData(NetData);

	if (bDataPresent){
		res = true;
	}
	else {
		res = false;
	}

	return res;
}

void UNetworkBlueprintLibrary::StopCommunications(){
	UNetworkBlueprintLibrary::ServerSocket->Close();
}