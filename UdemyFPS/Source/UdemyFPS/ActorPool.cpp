// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"
#include "Runtime/NavigationSystem/Public/NavMesh/NavMeshBoundsVolume.h"
// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


ANavMeshBoundsVolume * UActorPool::Checkout()
{
	if(PoolOfNavMeshes.Num()>0)
	{
		return PoolOfNavMeshes.Pop();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PoolOfNavMeshes.Num()==0"));
		return nullptr;
	}
}

void UActorPool::Return(ANavMeshBoundsVolume * ActorToReturn)
{
	if(ActorToReturn!=NULL)
	{
		PoolOfNavMeshes.Push(ActorToReturn);
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ActorToReturn in ActorPool is nullptr"));
		return;
	}
}

void UActorPool::AddActor(ANavMeshBoundsVolume * ActorToAdd)
{
	PoolOfNavMeshes.Push(ActorToAdd);
	
}

// Called when the game starts
void UActorPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

