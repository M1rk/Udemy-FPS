// Fill out your copyright notice in the Description page of Project Settings.
#include "../NPC/ChooseNextWaypoint.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PatrolRoute.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* Waypoint = BlackboardComp->GetValueAsObject(WaypointKey.SelectedKeyName);
	Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();

	auto GuardComponent = Pawn->FindComponentByClass<UPatrolRoute>();
	int32 Length = GuardComponent->PatrolPointsCPP.Num();
	if(Index<Length)
	{
		if(GuardComponent->PatrolPointsCPP[Index] != nullptr)
		{
			AActor* CurrentTargetPoint = GuardComponent->PatrolPointsCPP[Index];
			BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, CurrentTargetPoint);
			Index += 1;
			int32 NextIndex = Index % Length;
			BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
		}
	}
	return EBTNodeResult::Succeeded;
}
