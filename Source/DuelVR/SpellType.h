// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ESpellTypeEnum : uint8
{
	ST_Invalid 		UMETA(DisplayName = "Invalid"),
	ST_Block		UMETA(DisplayName = "Block"),
	ST_Damage 		UMETA(DisplayName = "Damage"),
	ST_Stun			UMETA(DisplayName = "Stun")
};

