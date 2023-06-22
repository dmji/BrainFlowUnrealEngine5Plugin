// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrainFlowReceiverComponent.generated.h"

class BoardShim;
struct FMeasurementCollectedStruct;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAINFLOWPLUGIN_API UBrainFlowReceiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBrainFlowReceiverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Persistence", meta = (DisplayName = "Grab Series AUX And Stop Collection", Keywords = "Measurement"))
		void GrabMeasurementAndStop(FMeasurementCollectedStruct& Measurements);

	UFUNCTION(BlueprintCallable, Category = "Persistence", meta = (DisplayName = "Start Collecting Series AUX for", Keywords = "Measurement"))
		void StartCollectingFor(float Second, float& SecondDelay);

	UFUNCTION(BlueprintCallable, Category = "Persistence", meta = (DisplayName = "Start Session", Keywords = "Session"))
		bool StartSession(int32 BoardId);

	UFUNCTION(BlueprintCallable, Category = "Persistence", meta = (DisplayName = "Release Session", Keywords = "Session"))
		bool ReleaseSession();

private:
	TUniquePtr<BoardShim> m_board;
};
