// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM()
enum AttackType
{
	Null = -1 UMETA(DisplayName = "Null"),
	Fire     UMETA(DisplayName = "Fire"),
	Poison      UMETA(DisplayName = "Poison"),
	AntiHeal   UMETA(DisplayName = "AntiHeal"),
	TypeCount UMETA(DisplayName = "TypeCount"),
};