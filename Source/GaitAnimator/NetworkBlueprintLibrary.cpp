// Fill out your copyright notice in the Description page of Project Settings.

#include "GaitAnimator.h"
#include "NetworkBlueprintLibrary.h"
#include "Runtime/Networking/Public/Networking.h"

//Logging for your AI system
DEFINE_LOG_CATEGORY(NetworkInfo);

FSocket* UNetworkBlueprintLibrary::ServerSocket;

bool UNetworkBlueprintLibrary::NetworkSetup(int32 ServerPort) {

	bool res = false;

	//FTcpSocketBuilder blah;
	//blah.Build()
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
				GLog->Logf(TEXT("Failed to create Server Socket as configured!"));

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

TArray<FRotator> UNetworkBlueprintLibrary::GetRotationPacket(){

	bool				bDataPresent;
	uint32				netData;
	int32				bytesRead;
	TArray<FRotator>	tempData;
	uint8				receivedData[100];

	bDataPresent = UNetworkBlueprintLibrary::ServerSocket->HasPendingData(netData);

	if (netData >= 16) {
		UNetworkBlueprintLibrary::ServerSocket->Recv(receivedData, (int32) 100, bytesRead);
		
		FString debugData = BytesToString(receivedData, bytesRead);
		// Writing received message on LOG
		UE_LOG(NetworkInfo, Warning, TEXT("Got message %s"), *debugData);
		
	} 

	return tempData;
}

void UNetworkBlueprintLibrary::StopCommunications(){
	UNetworkBlueprintLibrary::ServerSocket->Close();
}