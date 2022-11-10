// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/Undegard_AIController.h"
#include "AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Undegard/Public/Enemy/Undegard_Enemy.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "AIModule/Classes/Perception/AIPerceptionComponent.h"


AUndegard_AIController::AUndegard_AIController() {

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	LoopPathParameterName = "bLoopPath";
	DirectionIndexParameterName = "DirectionIndex";
	WaitingTimeOnPointParameterName = "WaitingTimeOnPathPoint";
	CanSeePlayerParameterName = "bCanSeePlayer";
	InvestigatingParameterName = "bIsInvestigating";
	TargetLocationParameterName = "TargetLocation";
}

void AUndegard_AIController::BeginPlay() {
	Super::BeginPlay();

	if (IsValid(EnemyBehaviorTree))
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}

	MyEnemy = Cast<AUndegard_Enemy>(K2_GetPawn());

	if (IsValid(MyEnemy))
	{
		MyBlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(this);
		if (IsValid(MyBlackBoard))
		{
			MyBlackBoard->SetValueAsBool(LoopPathParameterName, MyEnemy->GetLoopPath());
			MyBlackBoard->SetValueAsInt(DirectionIndexParameterName, MyEnemy->GetDirectionIndex());
			MyBlackBoard->SetValueAsFloat(WaitingTimeOnPointParameterName, MyEnemy->GetWaitingTime());
		}
	}

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AUndegard_AIController::UpdateSenses);
}

void AUndegard_AIController::UpdateSenses(const TArray<AActor*>& UpdatedActors)
{
	if (!IsValid(MyBlackBoard))
	{
		return;
	}

	for (AActor* Actor : UpdatedActors)
	{
		FActorPerceptionBlueprintInfo PerceptionInfo;
		AIPerceptionComponent->GetActorsPerception(Actor, PerceptionInfo);

		AUndegard_Character* SensedCharacter = Cast<AUndegard_Character>(Actor);
		if (IsValid(SensedCharacter) && SensedCharacter->GetCharacterType() == EUndegard_CharacterType::CharacterType_Player)
		{
			for (int i = 0; i < PerceptionInfo.LastSensedStimuli.Num(); i++)
			{
				switch (i)
				{

				case 0:
					MyBlackBoard->SetValueAsBool(CanSeePlayerParameterName, PerceptionInfo.LastSensedStimuli[i].WasSuccessfullySensed());
					break;

				case 1:
					MyBlackBoard->SetValueAsBool(InvestigatingParameterName, bReceivingDamage);
					if (bReceivingDamage)
					{
						MyBlackBoard->SetValueAsVector(TargetLocationParameterName, PerceptionInfo.LastSensedStimuli[i].StimulusLocation);
					}
					break;

				default:
					break;
				}
			}
		}
	}
}
