// Copyright by Free2Play-Entertainment (2020)


#include "GetRank.h"

UGetRank* UGetRank::GetRank(UGameJolt* GJAPI, const int32 Sort, const int32 TableID)
{
    UGetRank* ScoreNode = NewObject<UGetRank>();
    ScoreNode->GameJolt = GJAPI;
    ScoreNode->ScoreSort = Sort;
    ScoreNode->Table = TableID;
    return ScoreNode;
}

void UGetRank::Activate()
{
    if(!Super::Validate())
    {
        Failure.Broadcast();
        return;
    }

    FScriptDelegate funcDelegate;
    funcDelegate.BindUFunction(this, "Callback");

    FString BaseURL = "/scores/get-rank/?sort=" + FString::FromInt(ScoreSort);
    if(Table != 0)
        BaseURL += "&table_id=" + FString::FromInt(Table);
    FieldData = UJsonData::GetRequest(UGameJolt::CreateURL(BaseURL, GameJolt));
    FieldData->OnGetResult.AddUnique(funcDelegate);
}

void UGetRank::Callback(const bool bSuccess, UJsonData* JSON)
{
    Super::Callback(bSuccess, JSON);
    if(!bResponseValid)
    {
        Failure.Broadcast();
        return;
    }

    int32 Rank = response->GetInt("rank");
    if(Rank == 0)
    {
        Failure.Broadcast();
        return;
    }
    Success.Broadcast(Rank);
}