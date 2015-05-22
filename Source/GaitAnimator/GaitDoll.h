// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GaitDoll.generated.h"

UCLASS()
class GAITANIMATOR_API AGaitDoll : public AActor
{
	GENERATED_BODY()

private_subobject:
	/** The main skeletal mesh associated with this Character (optional sub-object). */
	DEPRECATED_FORGAME(4.6, "Mesh should not be accessed directly, please use GetMesh() function instead. Mesh will soon be private and your code will not compile.")
	UPROPERTY(Category = GaitDoll, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh;
	
public:	
	// Sets default values for this actor's properties
	AGaitDoll();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
