// Copyright by Free2Play-Entertainment (2020)


#include "RewardTrophy.h"

URewardTrophy* URewardTrophy::RewardTrophy(UGameJolt* GJAPI, const int32 ID)
{
    URewardTrophy* TrophyNode = NewObject<URewardTrophy>();
    TrophyNode->GameJolt = GJAPI;
    TrophyNode->TrophyID = ID;
    return TrophyNode;
}

void URewardTrophy::Activate()
{
    if(!Super::Validate())
    {
        Failure.Broadcast();
        return;
    }
    FScriptDelegate funcDelegate;
    funcDelegate.BindUFunction(this, "Callback");
    FieldData = UJsonFieldData::GetRequest(UGameJolt::CreateURL(("/trophies/add-achieved/?trophy_id=" + FString::FromInt(TrophyID)), GameJolt));
    FieldData->OnGetResult.AddUnique(funcDelegate);
}

void URewardTrophy::Callback(const bool bSuccess, UJsonFieldData* JSON, const EJSONResult Status)
{
    Super::Callback(bSuccess, JSON, Status);
    if(!bResponseValid)
    {
        Failure.Broadcast();
        return;
    }

    Success.Broadcast();
}