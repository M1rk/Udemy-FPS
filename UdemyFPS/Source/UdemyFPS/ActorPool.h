// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"

class ANavMeshBoundsVolume;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMYFPS_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorPool();
	ANavMeshBoundsVolume* Checkout();
	void Return(ANavMeshBoundsVolume* ActorToReturn);
	void AddActor(ANavMeshBoundsVolume* ActorToAdd);
	TArray<ANavMeshBoundsVolume*> PoolOfNavMeshes;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
