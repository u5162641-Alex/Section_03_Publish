// Copyright Alex Stuchbery 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/all_headers.h" 

#define OUT // OUT does nothing but allows us to annotate when a getter is changing variables (bad)

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

	// Find attached physics handle
	FindPhysicsHandleComponent();
	
	// Find attached input component
	SetupInputComponent();
}


void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		/// Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s cannot find a Physics Handle Component"),
			*GetOwner()->GetName()
		);
	}
}
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found on %s"),
			*GetOwner()->GetName()
		);
		/// Bind the input actions
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s cannot find an Input Component"),
			*GetOwner()->GetName()
		);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));

	// Line trace and see if we  any actors with physics set
	GetFirstPhysicsBodyInReach();


	// If we hit something then attach a physics handle
	// TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));

	//TODO release physics handle

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get the player view point at current time
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/// Log out location and rotation 
	/*UE_LOG(LogTemp, Warning, TEXT("Location: %s  Rotation: %s"),
	*PlayerViewPointLocation.ToString(),
	*PlayerViewPointRotation.ToString()
	);*/


	/// ray-cast out to reach distance
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	//Draw a Debug Line
	/*
	// Draw a red trace in the world to visualise
	DrawDebugLine(
	GetWorld(),
	PlayerViewPointLocation,
	LineTraceEnd,
	FColor(255, 0, 0),
	false,
	0.f,
	0,
	1.5f
	);
	*/

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// line trace (aka ray cast) to reach a distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// See what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT: %s"), *(ActorHit->GetName()))
	}

	return FHitResult();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
		// move the object that we're holding





	

		
	
	// 
	// ...
}

