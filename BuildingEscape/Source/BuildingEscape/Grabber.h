// Copyright Alex Stuchbery 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* Owner; // The owning pawn / actor
	
	UPROPERTY(EditAnywhere)
		float Reach = 100.f; 
	
};
