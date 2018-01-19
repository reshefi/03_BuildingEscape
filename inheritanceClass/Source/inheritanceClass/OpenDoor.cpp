// Copyright Ido Reshef 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

# define OUT

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
	if (UOpenDoor::GetTotalOfMassOfActorsOnPlate() > 30.f) {  // TODO make into a parameter or constant
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else if (isDoorOpen && GetWorld()->GetTimeSeconds()  > (LastDoorOpenTime+ DOOR_CLOSE_DELAY)) { 
		CloseDoor();
	}
	
}

float UOpenDoor::GetTotalOfMassOfActorsOnPlate() {
	
	float TotalMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor *> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them adding their masses
	UPrimitiveComponent * MeshComponent = nullptr;

	for (const auto * actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping: %s"),  * actor->GetName());
		MeshComponent = actor->FindComponentByClass<UPrimitiveComponent>();
		TotalMass += MeshComponent->GetMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("Accumulated mass %f!"), TotalMass);
	return TotalMass;
}

