// Copyright Gamal Emira

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "KismetLineTrace.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLDING_ESCAPE_API UKismetLineTrace : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKismetLineTrace();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

private:
	FHitResult LineTraceHitResult;
	TArray <AActor*> ActorsToIgnore;

	UPROPERTY(EditAnywhere, Category = "LineTrace")
	float LineTraceDistance = 500.0f;

	UPROPERTY(EditAnywhere, Category = "LineTrace")
	float LineTraceDurationTime = 0.2;

private:
	bool DrawALineTrace(FVector StartPoint, FVector EndPoint);

		
};
