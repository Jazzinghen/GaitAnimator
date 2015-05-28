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

	/** WHAT */
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Network)
	FSocket* ServerSocket;

public:
	
	/** Network initialisation function, should be called only at start of the system */
	UFUNCTION(BlueprintCallable, Category = Network, meta = (FriendlyName = "Network Initialisation"))
	bool NetworkSetup();

};
