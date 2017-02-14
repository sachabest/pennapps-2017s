// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "SpellType.h"
#include "GraphNode.h"
#include "WandTracker.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUELVR_API UWandTracker : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWandTracker();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void LockStartingTransform();
	void EndMotion();

	// https://answers.unrealengine.com/questions/210255/how-would-i-create-an-event-on-an-actorcomponent-t.html
	// do this later
	DECLARE_EVENT(UWandTracker, EFailedCastEvent)
	EFailedCastEvent &EFailedCast() { return FailedCastEvent; }

	DECLARE_EVENT(UWandTracker, ESucceededCastEvent)
	ESucceededCastEvent &ESucceededCast(ESpellTypeEnum CastSpell) { return SuceededCastEvent; }
private:
	EFailedCastEvent FailedCastEvent;
	ESucceededCastEvent SuceededCastEvent;

 	ESpellTypeEnum ValidateSequence();
	bool InMedianRadius();
	int InQuadrant();
	
	FTransform startingTransform;
	TArray<int> currentSequence;
	bool bInMotion;
	float fMedianRadius;

	UGraphNode *stateMachien;
};
