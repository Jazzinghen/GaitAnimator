// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GaitDollSkeleton.h"
#include "GaitDoll2.generated.h"

UCLASS()
class GAITANIMATOR_API AGaitDoll2 : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = GaitDoll, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* GaitSkeleton;

	UPROPERTY(Category = GaitDoll, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator LeftCalfRotation;

public:
	// Sets default values for this pawn's properties
	AGaitDoll2();

	AGaitDoll2(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FORCEINLINE FRotator GetLeftCalf() const { return LeftCalfRotation; }
	
};
