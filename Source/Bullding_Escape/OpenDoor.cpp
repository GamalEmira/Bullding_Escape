// Copyright Gamal Emira

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.h"

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

	DoorIntialRotaionYaw = GetOwner()->GetActorRotation().Yaw;
	DoorTargetRotationYaw += DoorIntialRotaionYaw;
	DoorCurrentRotaionYaw = DoorIntialRotaionYaw;
	
	MyPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PressurePlat)
	{
		// Actor name has open door component on it , but no PressurePlat set
		UE_LOG(LogTemp, Error, TEXT("%s Actor name has open door component on it , but no PressurePlat set"), *GetOwner()->GetName());
	}	
}
	

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if (PressurePlat && PressurePlat->IsOverlappingActor(MyPlayer))
	{
		OpenDoor(DeltaTime);
		// when door last open 
		DoorLastOpend= GetWorld()->GetTimeSeconds();
	}
	else 
	{
		if ((GetWorld()->GetTimeSeconds()- DoorLastOpend) > DoorCloseDelay) // that mean it stop opening
		{ 
			CloseDoor(DeltaTime);
			
		}
	}

	//if the door has been open long than x sec. (like Delay node in Blueprint)

}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	DoorOpenSpeed = DeltaTime * 0.5f;
	DoorCurrentRotaionYaw = FMath::Lerp(DoorCurrentRotaionYaw, DoorTargetRotationYaw, DoorOpenSpeed);
	DoorRotation = { 0.f, DoorCurrentRotaionYaw, 0.f };
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	DoorCloseSpeed = DeltaTime * 0.4f;
	DoorCurrentRotaionYaw = FMath::Lerp(DoorCurrentRotaionYaw, DoorIntialRotaionYaw, DoorCloseSpeed);
	DoorRotation = { 0.f, DoorCurrentRotaionYaw, 0.f };
	GetOwner()->SetActorRotation(DoorRotation);
}

