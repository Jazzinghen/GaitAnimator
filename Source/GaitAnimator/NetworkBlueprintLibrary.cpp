// Fill out your copyright notice in the Description page of Project Settings.

#include "GaitAnimator.h"
#include "NetworkBlueprintLibrary.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Runtime/Json/Public/Json.h"

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
	TArray<uint8>		receivedData;

	bDataPresent = UNetworkBlueprintLibrary::ServerSocket->HasPendingData(netData);
	receivedData.Empty(netData + 1);

	// If we received enough data (16 is a placeholder for now)
	if (netData >= 6) {
		// Get data from socket buffer
		bDataPresent = UNetworkBlueprintLibrary::ServerSocket->Recv(receivedData.GetData(), netData, bytesRead);
		if (bDataPresent) {
			// Convert bytes into a string
			FString receivedString = ANSI_TO_TCHAR((char*)receivedData.GetData());
			// Cut all the useless stuff (some... dirty memory, maybe generated while doing the -1...)
			receivedString = receivedString.Left(bytesRead);
			// Writing received message on LOG
			UE_LOG(NetworkInfo, Warning, TEXT("Got message %s"), *receivedString);

			TSharedPtr<FJsonObject> JsonObject;
			// Create a JSON reader based on our received string
			TSharedRef<TJsonReader<>> receivedJson = TJsonReaderFactory<>::Create(receivedString);

			// Convert the entire string in a JSON object for further exploration
			if (FJsonSerializer::Deserialize<TCHAR>(receivedJson, JsonObject)) {
				// Temporary JSON object containing single bone rotator
				const TSharedPtr<FJsonObject> *boneRotationObject;

				// Try to extract the left_calf rotator
				if (JsonObject->TryGetObjectField(TEXT("left_calf"), boneRotationObject)) {
					FRotator boneRotator;
					double tempAngle;

					if (boneRotationObject->Get()->TryGetNumberField(TEXT("pitch"), tempAngle)) {
						boneRotator.Pitch = tempAngle;
					}

					if (boneRotationObject->Get()->TryGetNumberField(TEXT("yaw"), tempAngle)) {
						boneRotator.Yaw = tempAngle;
					}

					if (boneRotationObject->Get()->TryGetNumberField(TEXT("roll"), tempAngle)) {
						boneRotator.Roll = tempAngle;
					}

					UE_LOG(NetworkInfo, Warning, TEXT("Got angle: [%f; %f; %f]"), boneRotator.Pitch, boneRotator.Yaw, boneRotator.Roll);
					tempData.Add(boneRotator);
				}
			}
		}
	} 

	return tempData;
}

void UNetworkBlueprintLibrary::StopCommunications(){
	UNetworkBlueprintLibrary::ServerSocket->Close();
}