// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "ActorPool.h"
#include "Runtime/NavigationSystem/Public/NavMesh/NavMeshBoundsVolume.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}
void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* navmesh)
{
	NavMeshBoundsVolumePool->AddActor(navmesh);
}

void AInfiniteTerrainGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
	for (int32 i = 0; i < NavMeshBoundsVolumePool->PoolOfNavMeshes.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("PoolOfNavMeshes: %s"), *NavMeshBoundsVolumePool->PoolOfNavMeshes[i]->GetName())
	}
}
