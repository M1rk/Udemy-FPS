// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UdemyFPSGameMode.h"
//#include "Runtime/NavigationSystem/Public/NavMesh/NavMeshBoundsVolume.h"
#include "InfiniteTerrainGameMode.generated.h"

class ANavMeshBoundsVolume;
class UActorPool;
/**
 * 
 */
UCLASS()
class UDEMYFPS_API AInfiniteTerrainGameMode : public AUdemyFPSGameMode
{
	GENERATED_BODY()
public:
	AInfiniteTerrainGameMode();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Fire")
	void PopulateBoundsVolumePool();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool")
	UActorPool* NavMeshBoundsVolumePool;
private:

	void AddToPool(ANavMeshBoundsVolume* navmesh);
	
};
