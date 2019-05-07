// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrolingGuard.generated.h"

/**
 * 
 */
UCLASS()
class UDEMYFPS_API APatrolingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
public:
		UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
		TArray<AActor*> PatrolPointsCPP;
};
