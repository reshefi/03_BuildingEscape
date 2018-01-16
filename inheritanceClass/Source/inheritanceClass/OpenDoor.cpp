// Copyright Ido Reshef 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"


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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}

void UOpenDoor::OpenDoor() {
	AActor * Owner = GetOwner();
	Owner->SetActorRotation(FRotator(0.f, ANGLE_OF_DOOR_OPEN, 0.f));
	this->isDoorOpen = true;
}

void UOpenDoor::CloseDoor() {
	AActor * Owner = GetOwner();
	Owner->SetActorRotation(FRotator(0.f, ANGLE_OF_DOOR_CLOSED, 0.f));
	this->isDoorOpen = false;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll theh trigger Volume
	// If the ActorThatOpens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else if (isDoorOpen && GetWorld()->GetTimeSeconds()  > (LastDoorOpenTime+ DOOR_CLOSE_DELAY)) { 
		CloseDoor();
	}
	
}

