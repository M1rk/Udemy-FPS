// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCPP.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "ActorPool.h"
#include "Runtime/NavigationSystem/Public/NavMesh/NavMeshBoundsVolume.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"


// Sets default values
ATileCPP::ATileCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATileCPP::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawnNumber,int32 MaxSpawnNumber,float ActorSize,float MinScale, float MaxScale )
{
	
	int NumberToSpawn = FMath::RandRange(MinSpawnNumber, MaxSpawnNumber);
	FVector ActorLocation = this->GetActorLocation();
	
	for(int32 i = 0; i<NumberToSpawn; i++)
	{
		float ScaleMultiplier = FMath::RandRange(MinScale, MaxScale);
		FVector NewScale(1.f*ScaleMultiplier, 1.f*ScaleMultiplier, 1.f*ScaleMultiplier);
		float NewActorSize = ActorSize * ScaleMultiplier;
		FVector SpawnLocation;
		bool NotEmpty = true;
		while(NotEmpty)
		{
			FVector SpawnPointForStuff = FMath::RandPointInBox(FBox(FVector(0, -1960, 175), FVector(3980, 1970, 175)));
		    
			if(!CastSphere(SpawnPointForStuff+ActorLocation,NewActorSize))
			{
			   SpawnLocation = SpawnPointForStuff;
			   NotEmpty = false;
			}
		}
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *SpawnLocation.ToString());
		FRotator SpawnRotation(0, FMath::RandRange(0, 360),0);
		AActor* Subject = GetWorld()->SpawnActor<AActor>(ToSpawn,SpawnLocation,SpawnRotation);
		Subject->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative,true));
		Subject->SetActorScale3D(NewScale);
		
		
	}
}

void ATileCPP::PlaceAI(TSubclassOf<APawn> ToSpawn, int32 MinSpawnNumber, int32 MaxSpawnNumber, float ActorSize)
{
	int NumberToSpawn = FMath::RandRange(MinSpawnNumber, MaxSpawnNumber);
	FVector ActorLocation = this->GetActorLocation();

	for (int32 i = 0; i < NumberToSpawn; i++)
	{
		
		
		
		FVector SpawnLocation;
		bool NotEmpty = true;
		while (NotEmpty)
		{
			FVector SpawnPointForStuff = FMath::RandPointInBox(FBox(FVector(0, -1960, 250), FVector(3980, 1970, 250)));

			if (!CastSphere(SpawnPointForStuff + ActorLocation, ActorSize))
			{
				SpawnLocation = SpawnPointForStuff;
				NotEmpty = false;
			}
		}
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *SpawnLocation.ToString());
		FRotator SpawnRotation(0, FMath::RandRange(0, 360), 0);
		APawn* Subject = GetWorld()->SpawnActor<APawn>(ToSpawn, SpawnLocation, SpawnRotation);
		Subject->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Subject->SpawnDefaultController();
		Subject->Tags.Add(FName("Enemy"));

		
		
	}
}

void ATileCPP::SetPool(UActorPool * Inpool)
{
	Pool = Inpool;
	PositionNavMeshBoundsVolume();
}

void ATileCPP::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if(NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] NavMeshBoundsVolume in TileCPP is nullptr"),*this->GetName());
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] NavMeshBoundsVolume in TileCPP: %s"), *this->GetName(),*NavMeshBoundsVolume->GetName());
		NavMeshBoundsVolume->SetActorLocation(GetActorLocation()-FVector(-2000.f,0.f,-250.f));
		UE_LOG(LogTemp, Warning, TEXT("[%s] ActorLocation of NavMeshBoundsVolume in TileCPP has been set"), *this->GetName());
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		NavSystem->Build();
		
	}
}

// Called when the game starts or when spawned
void ATileCPP::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ATileCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileCPP::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Pool->Return(NavMeshBoundsVolume);
	Super::EndPlay(EndPlayReason);
	
	TArray<AActor*> temp;
	GetAttachedActors(temp);
	for (int i = 0; i < temp.Num(); ++i)
	{
		temp[i]->Destroy();
	}
}

bool ATileCPP::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, Location, Location, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	FColor ResultColor2 = HasHit ? FColor::Orange : FColor::Blue;
	//DrawDebugCapsule(GetWorld(), Location, 0, Radius, FQuat::Identity, ResultColor, true, 120, 0, 5);
	return HasHit;
}

