	// Copyright Gamal Emira


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	//// *****************  Display LOG ***********************
	////UE_LOG - You can see it in UE editor - Windows->Devolper Tools-> Output Log
	//UE_LOG(LogTemp, Warning, TEXT("This is a Warning !")); // Warning shows the log in yellow
	//UE_LOG(LogTemp, Error, TEXT("This is a Error Message ??")); // Error Shows Red
	//UE_LOG(LogTemp, Display, TEXT("This is a Display message :) :)"));


	//int32 Number = 9;
	//FString Log = TEXT("Hello");
	//FString* PtrLog = &Log;

	//Log.Len();

	//// --->   PtrLog->Len();  is replacing    --->   (*PtrLog).Len();
	////  Mean get the value inside the address of pointer PtrLog
	//PtrLog->Len();


	//UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog);

	//FString Objectname = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Object Name is : %s"), *GetOwner()->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("Object Location is : %s"), *GetOwner()->GetActorLocation().ToString());

	FString ObjectName = GetOwner()->GetName();
	FString ObjectLocation = GetOwner()->GetActorLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("The %s location is %s"), *ObjectName, *ObjectLocation);

}

	



// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

