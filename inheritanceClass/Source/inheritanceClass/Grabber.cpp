// Copyright Ido Reshef 2017

#include "Grabber.h"
#include "Engine/World.h"
//#include <string>

#define OUT  
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("I am grabber !"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	// Get the player view point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	UE_LOG(LogTemp, Warning, TEXT("ViewPointLocation: %s is at PlayerViewPointRotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	
	FVector LineTraceEnd = PlayerViewPointLocation +
		PlayerViewPointRotation.Vector() * Reach;
	
	//Draw a red trace in the world to visualise
	
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	); //add
	// Ray-cast out to reach distance

	// See what we hit 
}

