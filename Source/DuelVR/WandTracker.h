// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "SpellType.h"
#include "GraphNode.h"
#include "WandTracker.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSuceededCast, ESpellTypeEnum, SucceededSpell);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFailedCast);

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

	UPROPERTY(BlueprintAssignable, Category = "Spell Casting")
		FOnFailedCast OnFailedCast;
	UPROPERTY(BlueprintAssignable, Category = "Spell Casting")
		FOnSuceededCast OnSuceededCast;
private:

 	ESpellTypeEnum ValidateSequence();
	bool InMedianRadius();
	int InQuadrant();
	
	FTransform startingTransform;
	TArray<int> currentSequence;
	bool bInMotion;
	float fMedianRadius;

	UGraphNode *stateMachien;
};
