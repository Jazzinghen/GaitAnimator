// Fill out your copyright notice in the Description page of Project Settings.

#include "GaitAnimator.h"
#include "NetworkBlueprintLibrary.h"
#include "Runtime/Networking/Public/Networking.h"

bool UNetworkBlueprintLibrary::NetworkSetup(int ServerPort) {

	FSocket* Socket = nullptr;
	bool res = false;

	// Instead of using the step-by-step approach I will use the FTcpSocketBuilder Function :D
	FTcpSocketBuilder SocketBuilder = FTcpSocketBuilder(TEXT("Server Socket")); 
	FIPv4Address ServerAddress = FIPv4Address(127, 0, 0, 1);
	FIPv4Endpoint ServerEndpoint = FIPv4Endpoint(ServerAddress, (uint16)ServerPort);

	SocketBuilder.AsNonBlocking();
	SocketBuilder.BoundToEndpoint(ServerEndpoint);

	Socket = SocketBuilder.Build();

	if (Socket != NULL){
		ServerSocket = Socket;
		res = true;
	}
	else {
		res = false;
	}

	return res;
}

bool UNetworkBlueprintLibrary::NewDataAvailable(){

	uint32 NetData;

	return ServerSocket->HasPendingData(NetData);
}

bool UNetworkBlueprintLibrary::GetRotationPacket(TArray<FRotator> &newData){

	bool bDataPresent;
	uint32 NetData;
	
	bDataPresent = ServerSocket->HasPendingData(NetData);

	if (bDataPresent){
		return true;
	}
	else {
		return false;
	}
}