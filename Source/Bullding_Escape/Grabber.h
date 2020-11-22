// Copyright Gamal Emira

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void DrawGrabberDebugLine();
	bool DrawGrabberLineTrace(FVector StartPoint, FVector EndPoint);
	bool IsMyPawnHasPhyscisHandleComponent();
	void WriteMessage(FString MyMessage,float DispalyTime, FColor DispalyColor);
	void GrabObject();
	void ReleseObject();
	


private:
	float Reach = 200.f;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector LineTraceEnd;
	FHitResult Hit;
	float TraceDistance = 100.0f;
	bool bPhysicsHandleComponentLoaded;

	

	/*
	FVector StartPoint;
	FVector EndPoint;*/

	TArray<AActor*> ActorsToIgnore;
	AActor* ActorHit = nullptr;
	UPhysicsHandleComponent* PhysicsHandleComponent = nullptr;
	UInputComponent* InputComponent = nullptr;
	UPrimitiveComponent* ComponentToGrab = nullptr;



};
