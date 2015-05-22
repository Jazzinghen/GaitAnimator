// Fill out your copyright notice in the Description page of Project Settings.

#include "GaitAnimator.h"
#include "GaitDoll2.h"


// Sets default values
AGaitDoll2::AGaitDoll2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AGaitDoll2::AGaitDoll2(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GaitSkeleton = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Gait Skeleton"));
	RootComponent = GaitSkeleton;
}

// Called when the game starts or when spawned
void AGaitDoll2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGaitDoll2::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AGaitDoll2::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

