// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Networking/Public/Networking.h"
#include "NetworkBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAITANIMATOR_API UNetworkBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:

	/** The server socket. As I understood since FSocket is not a USTRUCT then it cannot make use of
	 *  the UPROPERTY macro. Actually it would be more "It does not require UPROPERTY", as I suppose,
	 *  not being a USTRUCT won't make you Garbage Collected with the power of a thousan suns.
	 *
	 *  Code removed:
	 *	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Network)
	 */
	static FSocket* ServerSocket;

public:
	
	/** Network initialisation function, should be called only at start of the system */
	UFUNCTION(BlueprintCallable, Category = Network, meta = (FriendlyName = "Network Initialisation"))
	bool NetworkSetup(int ServerPort);

	/** Check for data available in network socket, use to know when to call the "getPacket" function */
	UFUNCTION(BlueprintCallable, Category = Network, meta = (FriendlyName = "Check for new data in socket buffer"))
	bool NewDataAvailable();

	/** Get rotations from the network socket */
	UFUNCTION(BlueprintCallable, Category = Network, meta = (FriendlyName = "Check for new data in socket buffer"))
	bool GetRotationPacket(TArray<FRotator> &newData);

};
