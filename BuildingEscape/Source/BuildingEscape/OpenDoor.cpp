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
	// ...
	
}

void UOpenDoor::OpenDoor() 
{
	// set the door rotation
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor() 
{

	// set the door rotation
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Polling the trigger volume
	if (GetTotalMassOfActorsOnPlate()>=60.f) //TODO Make into parameter 
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	// check if its time to close the door
	if (GetWorld()->GetTimeSeconds() >= LastDoorOpenTime + DoorCloseDelay)
	{
		CloseDoor();
	}

	
	// ...
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	//Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// TODO itterate through them adding their masses
	for (const auto* ActorOnTrigger : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor on plate: %s"), *ActorOnTrigger->GetName());
		TotalMass += ActorOnTrigger->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}