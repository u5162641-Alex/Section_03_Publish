// Copyright Alex Stuchbery 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/PrimitiveComponent.h"
// Needs to be the last include because of reasons
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, 
		ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction
	) override;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;
	

private:

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float TriggerMass = 60.f;
	
	// Removed in update
	/// AActor* ActorThatOpens; // NOTE Pawn inherrits from Actor

	AActor* Owner = nullptr; // The owning door

	float GetTotalMassOfActorsOnPlate();
};
