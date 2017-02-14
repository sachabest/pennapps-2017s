// Fill out your copyright notice in the Description page of Project Settings.

#include "DuelVR.h"
#include "SpellType.h"
#include "GraphNode.h"

UGraphNode::UGraphNode()
{
}

// Cascade
UGraphNode::~UGraphNode()
{
	for (auto &edge : Edges) {
		if (edge) {
			edge->ConditionalBeginDestroy();
		}
	}
}

ESpellTypeEnum UGraphNode::Validate(const TArray<int> &sequence, const int idx) const
{
	if (sequence.Num() == 1) {
		return sequence[idx] == Value ? SpellType : ESpellTypeEnum::ST_Invalid;
	} else {
		if (sequence[idx] != Value) {
			return ESpellTypeEnum::ST_Invalid;
		} else {
			for (auto &edge : Edges) {
				ESpellTypeEnum spell = edge->Validate(sequence, idx + 1);
				if (spell != ESpellTypeEnum::ST_Invalid) {
					return spell;
				}
			}
			return ESpellTypeEnum::ST_Invalid;
		}
	}
}