// Fill out your copyright notice in the Description page of Project Settings.

#include "GaitAnimator.h"
#include "NetworkBlueprintLibrary.h"
#include "Runtime/Networking/Public/Networking.h"

FSocket* UNetworkBlueprintLibrary::ServerSocket;
FSocket* UNetworkBlueprintLibrary::ClientSocket;

bool UNetworkBlueprintLibrary::NetworkSetup(int32 ServerPort) {

	FSocket* Socket = nullptr;
	bool res = false;
	uint16 castServerPort = (uint16)ServerPort;
	
	//int32 dataQty;
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	
	// Instead of that useless FTcpSocketBuilder I will try to create the socket by hand and then debug it... >:(
	if (SocketSubsystem != nullptr)
	{
		FIPv4Address ServerAddress = FIPv4Address(127, 0, 0, 1);

		TSharedRef<FInternetAddr> LocalAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		LocalAddress->SetIp(ServerAddress.GetValue());
		LocalAddress->SetPort(castServerPort);

		Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("Server Socket"), false);

		if (Socket != nullptr)
		{
			bool SocketCreationError = !Socket->Connect(*LocalAddress);

			if (SocketCreationError)
			{
				GLog->Logf(TEXT("Failed to create the Server Socket as configured!"));

				SocketSubsystem->DestroySocket(Socket);

				Socket = nullptr;
			}
		}
	}

	// Instead of using the step-by-step approach I will use the FTcpSocketBuilder Function :D
	//FTcpSocketBuilder SocketBuilder = FTcpSocketBuilder(TEXT("Server Socket")); 
	//FIPv4Address ServerAddress = FIPv4Address(127, 0, 0, 1);
	//FIPv4Endpoint ServerEndpoint = FIPv4Endpoint(ServerAddress, castServerPort);

	//SocketBuilder.AsNonBlocking();
	//SocketBuilder.BoundToEndpoint(ServerEndpoint);
	//SocketBuilder.AsReusable();
	//SocketBuilder.Listening(100);

	//Socket = SocketBuilder.AsNonBlocking().AsReusable().Listening(100).Build();

	if (Socket != nullptr){
		/*FString message = FString(TEXT("Hello Bitches!"));
		TCHAR *sendData = message.GetCharArray().GetData();
		int32 size = FCString::Strlen(sendData);

		UNetworkBlueprintLibrary::ServerSocket = Socket;
		UNetworkBlueprintLibrary::ServerSocket->Send((uint8*)TCHAR_TO_UTF8(sendData), size, dataQty);*/
		UNetworkBlueprintLibrary::ServerSocket = Socket;
		res = true;
	}
	else {
		res = false;
	}

	return res;
}

bool UNetworkBlueprintLibrary::NewConnectionRequests(){
	bool bPendingConnection;

	UNetworkBlueprintLibrary::ServerSocket->HasPendingConnection(bPendingConnection);

	return bPendingConnection;
}


bool UNetworkBlueprintLibrary::AcceptConnections(){
	bool res;
	FString connectionResponse;

	UNetworkBlueprintLibrary::ClientSocket =  UNetworkBlueprintLibrary::ServerSocket->Accept(connectionResponse);

	if (UNetworkBlueprintLibrary::ClientSocket != NULL){
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