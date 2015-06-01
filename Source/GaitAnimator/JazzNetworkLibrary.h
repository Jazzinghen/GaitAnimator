// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "JazzNetworkLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAITANIMATOR_API UJazzNetworkLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	/** Check for data available in network socket, use to know when to call the "getPacket" function */
	UFUNCTION(BlueprintCallable, Category = "JazzNetwork")
	bool NewDataAvailable();
	
	
};
