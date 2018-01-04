// Copyright Ido Reshef 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	AActor * Owner = GetOwner();
	FRotator OwnerRotation = Owner->GetActorRotation();
	OwnerRotation.Yaw += 60; 
	// Alternate method: FRotator OwnerRotation = FRotator(0.f, 60.f, 0.f);
	Owner->SetActorRotation(OwnerRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

