// Copyright Gamal Emira


#include "KismetLineTrace.h"
#include "Kismet\KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"


#define OUT

// Sets default values for this component's properties
UKismetLineTrace::UKismetLineTrace()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKismetLineTrace::BeginPlay()
{
	Super::BeginPlay();

	ActorsToIgnore.Add(GetOwner());
}


// Called every frame
void UKismetLineTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector StartPoint;
	FVector EndPoint;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	StartPoint = GetOwner()->GetActorLocation();
	EndPoint = (GetForwardVector() * LineTraceDistance) + StartPoint;

	//Draw Line Trace
	bool ReturnResult = DrawALineTrace(StartPoint, EndPoint);

	//If did not hit anything then do not execute the next lines of code
	if (!ReturnResult) { return; }
	
	//This if it hit something but not actor, Like Brush a Box Brush (Geometry tab actors in ER4 editor window)  
	//it will generate error to UE4 editor due to no LineTraceHitResult.GetActor()->GetName()
	AActor* ActorThatGetHit = nullptr;
	ActorThatGetHit = LineTraceHitResult.GetActor();
	if (!ActorThatGetHit) { return; }

	//Print the TEXT in the UR4 Screen
	if (ReturnResult)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,  //key
			1, //Time to display
			FColor::Blue,
			FString::Printf(TEXT("Trace Hit %s"), *LineTraceHitResult.GetActor()->GetName()) //the message
		);
	}
}

bool UKismetLineTrace::DrawALineTrace(FVector StartPoint, FVector EndPoint)
{
	//This code will draw and generate HitResult using Kismet 
	bool bHit = UKismetSystemLibrary::LineTraceSingle(
		this,
		StartPoint,
		EndPoint,
		UEngineTypes::ConvertToTraceType(ECC_Camera),  // Use the Camera Channel
		false,  // No Trace complex
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OUT LineTraceHitResult,
		true, //Ignore self
		FLinearColor::Green, // Line color
		FLinearColor::Red, // the Hit color
		LineTraceDurationTime // duration time
	);

	return bHit;
}