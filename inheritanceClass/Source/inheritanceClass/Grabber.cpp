// Copyright Ido Reshef 2017

#include "Grabber.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h" 
//#include <string>

#define OUT  


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::FindPhysicsHandleComponent() {

	FString ObjectName = GetOwner()->GetName();
	/// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
    {
		UE_LOG(LogTemp, Error, TEXT("No UPhysicsHandleComponent found at actor %s!"),*ObjectName);
	}
}

void UGrabber::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	FString ObjectName = GetOwner()->GetName();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s is missing Input component !"), *ObjectName);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
	// Get the player view point this tick
	/// Setup query prameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GRABPOS GrabPosition = CalculateGrabbingPosition();
	/// Line trace (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GrabPosition.PlayerViewPointLocation,
		GrabPosition.LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	/// See what we hit 
	if (Hit.Actor != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("We hit: %s"), *Hit.Actor->GetName());
	}
	return Hit;
}

UGrabber::GRABPOS UGrabber::CalculateGrabbingPosition() {

	GRABPOS  grabPositionOut;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT grabPositionOut.PlayerViewPointLocation,
		OUT grabPositionOut.PlayerViewPointRotation
	);
	
	FVector LineTraceEnd = grabPositionOut.PlayerViewPointLocation +
		grabPositionOut.PlayerViewPointRotation.Vector() * Reach;

	grabPositionOut.LineTraceEnd = LineTraceEnd;
	return grabPositionOut;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed !"));

	// LINE TRACE and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); //gets the mesh in our case
	auto ActorHit = HitResult.GetActor();
	
	// If we hit something then attach a physics handle
	if (ActorHit) {
		// TODO attach physics handle

		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation());
	 }
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Release Pressed !"));
	PhysicsHandle->ReleaseComponent();
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// if the physics handle is sttached
	if (PhysicsHandle->GrabbedComponent) {
	// move the object thath we're holding
	GRABPOS grabInfo = CalculateGrabbingPosition();
	PhysicsHandle->SetTargetLocation(grabInfo.LineTraceEnd);
	}
}

