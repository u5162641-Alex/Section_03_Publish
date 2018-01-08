// Copyright Alex Stuchbery 2018
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Grabber.generated.h" // Needs to be the last include because of reasons

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupInputComponent();
	
	void FindPhysicsHandleComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float Reach = 150.f; 
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr; 

	// Ray cast and grab whats in reach
	void Grab();
	void Release();

	// return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	
	// get reach vector end point
	FVector GetReachLineStart();

	// get reach vector end point
	FVector GetReachLineEnd();
};
