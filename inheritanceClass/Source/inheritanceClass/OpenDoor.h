#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INHERITANCECLASS_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float ANGLE_OF_DOOR_OPEN = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate;
		
	UPROPERTY(EditAnywhere)
	float DOOR_CLOSE_DELAY = 0.55f;

	float LastDoorOpenTime;
	AActor * ActorThatOpens;  // Remember pawn inherits from actor
	
	float ANGLE_OF_DOOR_CLOSED = 270.f;
	bool isDoorOpen = false;
};
