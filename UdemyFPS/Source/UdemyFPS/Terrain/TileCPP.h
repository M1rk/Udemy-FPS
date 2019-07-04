// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileCPP.generated.h"
class UActorPool;
class ANavMeshBoundsVolume;
UCLASS()
class UDEMYFPS_API ATileCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileCPP();
	UFUNCTION(BlueprintCallable, Category = "Fire")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawnNumber, int32 MaxSpawnNumber,float ActorSize,float MinScale = 1.f , float MaxScale = 1.f);
	UFUNCTION(BlueprintCallable, Category = "Fire")
		void PlaceAI(TSubclassOf<APawn> ToSpawn, int32 MinSpawnNumber, int32 MaxSpawnNumber, float ActorSize);
	UFUNCTION(BlueprintCallable, Category = "Pool")
		void SetPool(UActorPool* Inpool);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void PositionNavMeshBoundsVolume();
	bool CastSphere(FVector Location, float Radius);
	UActorPool* Pool;
	ANavMeshBoundsVolume* NavMeshBoundsVolume;
};
