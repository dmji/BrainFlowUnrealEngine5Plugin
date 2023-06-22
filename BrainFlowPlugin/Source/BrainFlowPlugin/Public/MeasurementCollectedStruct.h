// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeasurementCollectedStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct BRAINFLOWPLUGIN_API FMeasurementCollectedStruct
{
    GENERATED_USTRUCT_BODY()

    TArray<TArray<double>> Data;
};
