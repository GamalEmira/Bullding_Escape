// Copyright Gamal Emira


#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Grabber.h"

#define OUT


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
	ActorsToIgnore.Add(GetOwner());
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandleComponent)
	{
		bPhysicsHandleComponentLoaded = false;
		WriteMessage("PhysicsHandComponed not detected", 3, FColor::Red);
	}
	else
	{
		bPhysicsHandleComponentLoaded = true;
		WriteMessage("PhysicsHandComponed detected", 3, FColor::Green);
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		WriteMessage("No InputComponet Found", 3, FColor::Red);
	}
	else
	{
		WriteMessage("InputComponet Found", 3, FColor::Green);
		SetupPlayerInputComponent(InputComponent);
	}
	
}

void UGrabber::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	//check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabObject);
	PlayerInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleseObject);

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsMyPawnHasPhyscisHandleComponent()) { return; }
	

	//** Get StartPoint and End Point
	FVector StartPoint;
	FVector EndPoint;

	StartPoint = GetOwner()->GetActorLocation();
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	EndPoint = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * TraceDistance);
	
	//** Draw Debug LindTrace
	bool bHasHit = DrawGrabberLineTrace(StartPoint, EndPoint);
	ActorHit = Hit.GetActor();
	if (!ActorHit) { return; } // if it hit anything not Actor's inheritance it will exit
	if (bHasHit)
	{
		//Write in the UR4 "Output Log" window
		UE_LOG(LogTemp, Warning, TEXT("Actor that Hit is : %s"), *ActorHit->GetName());
		
		//Write in the UR4 Viewport window
		WriteMessage(Hit.GetActor()->GetName(), 0, FColor::Blue);

		//Grab object
		ComponentToGrab = Hit.GetComponent();
		LineTraceEnd = Hit.ImpactPoint;
		
		///// ?????????
		if (PhysicsHandleComponent->GrabbedComponent)
		{
			PhysicsHandleComponent->SetTargetLocation(LineTraceEnd);

		}
	}
}

void UGrabber::DrawGrabberDebugLine() 
{

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	DrawDebugLine(GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);



	
}



bool UGrabber::DrawGrabberLineTrace(FVector StartPoint, FVector EndPoint)
{
	
	//************************************************************************************
	//   for this function to work you must run on the Simulation Generates Hit Events   *
	//   and Generate Overlap Event in the object that you need interact with in the     *
	//   UR4 editor																		 *
	//************************************************************************************
	
	/*FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
		);*/

//****************************************************************************************************
	bool bHit = UKismetSystemLibrary::LineTraceSingle(
			this,
			StartPoint,
			EndPoint,
			UEngineTypes::ConvertToTraceType(ECC_Camera),  // Use the Camera Channel
			false,  // No Trace complex
			ActorsToIgnore,	
			EDrawDebugTrace::ForDuration,
			OUT Hit,
			true, //Ignore self
			FLinearColor::Green, // Line color
			FLinearColor::Red, // the Hit color
			0.1f // duration time
		);

	return bHit;
}

bool UGrabber::IsMyPawnHasPhyscisHandleComponent() 
{
	
	// that to be sure our Pawn has a Physics Component
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHndleCompenet found in the my Pawn"));
		return false;
	}
	else
	{
		return true;
	}
}

void UGrabber::WriteMessage(FString MyMessage,float DispalyTime, FColor DispalyColor)
{

	//Write in the UR4 Viewport window
	GEngine->AddOnScreenDebugMessage(
		-1,  //key
		DispalyTime, //Time to display
		DispalyColor,
		FString::Printf(TEXT("%s"), *MyMessage) //the message
	);
}

void UGrabber::GrabObject()
{
	
	PhysicsHandleComponent->GrabComponentAtLocation(ComponentToGrab, NAME_None, LineTraceEnd);
	WriteMessage("Grabber Pressed", 3, FColor::Magenta);
	
}

void UGrabber::ReleseObject()
{
	WriteMessage("Object Released", 3, FColor::Black);
}

