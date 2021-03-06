
#pragma once
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INHERITANCECLASS_API UGrabber : public UActorComponent
{
	public:	
	// Sets default values for this component's properties
	UGrabber();
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	float Reach = 100.f;
	UPhysicsHandleComponent * PhysicsHandle = nullptr;
	UInputComponent * InputComponent = nullptr;

	//Ray-cast and grab what's in reach
	void Grab();

	// Called when grab is released
	void Release();

	// Find attached physics handle
	void FindPhysicsHandleComponent();

	//Setup (assumed) attached input component
	void SetupInputComponent();

	


	//  Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach();
	struct GRABPOS {
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		FVector LineTraceEnd;
	};
	GRABPOS CalculateGrabbingPosition();

};
