// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SpellType.h"
#include "GraphNode.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUELVR_API UGraphNode : public UObject
{
public:

	GENERATED_BODY()

	UGraphNode();
	~UGraphNode();

	ESpellTypeEnum Validate(const TArray<int> &sequence, const int idx = 0) const;

	ESpellTypeEnum SpellType = ESpellTypeEnum::ST_Invalid;
	
	int Value;
	TArray<UGraphNode *> Edges;
};
