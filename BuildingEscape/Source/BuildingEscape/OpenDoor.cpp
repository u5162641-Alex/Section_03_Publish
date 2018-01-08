// Copyright Alex Stuchbery 2018

#include "OpenDoor.h"
#include "Engine/World.h"

// Alex made header file which just includes all of the .h files 
// within the GameFramework directory - Good for learning, bad for optimization
#include "GameFramework/all_headers.h" 

#define OUT

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

	// Removed in update
	///ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); // find the player's pawn
	Owner = GetOwner(); // set the owner to the owning door instance


	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s cannot find a Trigger Volume"),
			*GetOwner()->GetName()
		);
	}

	
	// ...
	
}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Polling the trigger volume
	if (GetTotalMassOfActorsOnPlate()>=TriggerMass) //TODO Make into parameter 
	{
		OnOpen.Broadcast(); // Broad cast on event for BluePrint
	}
	else
	{
		OnClose.Broadcast();
	}
	

	
	// ...
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	//Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);


	// TODO itterate through them adding their masses
	for (const auto* ActorOnTrigger : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor on plate: %s"), *ActorOnTrigger->GetName());
		TotalMass += ActorOnTrigger->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}