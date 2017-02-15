// Fill out your copyright notice in the Description page of Project Settings.

#include "DuelVR.h"
#include "WandTracker.h"

// Sets default values for this component's properties
UWandTracker::UWandTracker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	stateMachien = NewObject<UGraphNode>();
	// ...
}


// Called when the game starts
void UWandTracker::BeginPlay()
{
	Super::BeginPlay();

	UGraphNode *zero_start = NewObject<UGraphNode>();
	zero_start->Value = 0;

	UGraphNode *one_start = NewObject<UGraphNode>();
	one_start->Value = 1;

	UGraphNode *two_end = NewObject<UGraphNode>();
	two_end->Value = 2;
	two_end->SpellType = ESpellTypeEnum::ST_Damage;

	UGraphNode *three_start = NewObject<UGraphNode>();
	three_start->Value = 3;

	UGraphNode *three_end = NewObject<UGraphNode>();
	three_end->Value = 3;
	three_end->SpellType = ESpellTypeEnum::ST_Stun;

	UGraphNode *one_end = NewObject<UGraphNode>();
	one_end->Value = 1;
	one_end->SpellType = ESpellTypeEnum::ST_Block;

	stateMachien->Edges.Push(zero_start);
	stateMachien->Edges.Push(one_start);
	stateMachien->Edges.Push(three_start);

	zero_start->Edges.Push(two_end);
	one_start->Edges.Push(three_end);
	three_start->Edges.Push(one_start);
	// ...
	
}


// Called every frame
void UWandTracker::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
	if (bInMotion) {
		bool inMedian = !InMedianRadius();
		int inQuadrant = InQuadrant();
		if (!inMedian && inQuadrant == -1) {
			EndMotion();
		} else if (inQuadrant > -1) {
			if (currentSequence.Last() != inQuadrant) {
				currentSequence.Push(inQuadrant);
				ESpellTypeEnum spell = ValidateSequence();
				if (spell == ESpellTypeEnum::ST_Invalid) {
					EndMotion();
				}
			}
		}
	}
}

void UWandTracker::EndMotion()
{
	if (currentSequence.Num()) {
		ESpellTypeEnum spell = ValidateSequence();
		if (spell != ESpellTypeEnum::ST_Invalid) {
			OnSuceededCast.Broadcast(spell);
		}
		else {
			OnFailedCast.Broadcast();
		}
	}
	else {
		OnFailedCast.Broadcast();
	}
	bInMotion = false;
	currentSequence.Empty();
}

ESpellTypeEnum UWandTracker::ValidateSequence()
{
	return stateMachien->Validate(currentSequence);
}

int UWandTracker::InQuadrant()
{
	FVector delta = ComponentToWorld.GetLocation() - startingTransform.GetLocation();
	if (delta.X >= 0 && delta.Z >= 0) {
		if (delta.Z >= delta.X) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else if (delta.X < 0 && delta.Z >= 0) {
		if (delta.Z >= (-1 * delta.X)) {
			return 0;
		}
		else {
			return 3;
		}
	}
	else if (delta.X < 0 && delta.Z < 0) {
		if (delta.X < delta.Z) {
			return 3;
		}
		else {
			return 2;
		}
	}
	else {
		if (delta.X >= (-1 * delta.Z)) {
			return 1;
		}
		else {
			return 2;
		}
	}
}

void UWandTracker::LockStartingTransform()
{
	startingTransform = ComponentToWorld;
	bInMotion = true;
}

bool UWandTracker::InMedianRadius()
{
	return (ComponentToWorld.GetLocation() - startingTransform.GetLocation()).Size() <= fMedianRadius;
}
