// Fill out your copyright notice in the Description page of Project Settings.


#include "BrainFlowReceiverComponent.h"
#include "MeasurementCollectedStruct.h"
#include "board_shim.h"

// Sets default values for this component's properties
UBrainFlowReceiverComponent::UBrainFlowReceiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBrainFlowReceiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBrainFlowReceiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBrainFlowReceiverComponent::GrabMeasurementAndStop(FMeasurementCollectedStruct& Measurements)
{
	try
	{
		std::vector<int> eeg_channels = BoardShim::get_eeg_channels(m_board->get_board_id());
		m_board->stop_stream();
		BrainFlowArray<double, 2> data = m_board->get_board_data();
		for(auto channel : eeg_channels)
		{
			TArray<double> channelData;
			for(int32 i = 0; i < data.get_size(1); i++)
				channelData.Add(data.at(channel, 1));
			Measurements.Data.Add(channelData);
		}
	}
	catch(const BrainFlowException& err)
	{
		FString t = err.what();
	}
}

void UBrainFlowReceiverComponent::StartCollectingFor(float Second, float& SecondDelay)
{
	try
	{
		m_board->start_stream();
	}
	catch(const BrainFlowException& err)
	{
		FString t = err.what();
	}
	SecondDelay = Second;
}

bool UBrainFlowReceiverComponent::StartSession(int32 BoardId)
{
	try
	{
		BrainFlowInputParams params = BrainFlowInputParams();
		m_board.Reset(new BoardShim(BoardId, params));
		m_board->prepare_session();
	}
	catch(const BrainFlowException& err)
	{
		FString t = err.what();
		return false;
	}
	return true;
}

bool UBrainFlowReceiverComponent::ReleaseSession()
{
	try
	{
		m_board->release_session();
	}
	catch(const BrainFlowException& err)
	{
		FString t = err.what();
		return false;
	}
	return true;
}

