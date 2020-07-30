// Copyright by Free2Play-Entertainment (2020)


#include "Update.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Engine/Engine.h"
#include "UObject/Class.h"
#include "Containers/EnumAsByte.h"

UUpdate* UUpdate::UpdateData(UGameJolt* GJAPI, EGJDataStore Scope, const FString Key, const FString Value, EGJDataOperation Operation)
{
    UUpdate* DataStoreNode = NewObject<UUpdate>();
    DataStoreNode->GameJolt = GJAPI;
    DataStoreNode->Filter = Scope;
    DataStoreNode->DataKey = Key;
    DataStoreNode->DataValue = Value;
    DataStoreNode->DataOperation = Operation;
    return DataStoreNode;
}

void UUpdate::Activate()
{
    if(!Super::Validate())
    {
        Failure.Broadcast();
        return;
    }
    FScriptDelegate funcDelegate;
    funcDelegate.BindUFunction(this, "Callback");

    FString BaseURL = "/data-store/update/?";

    BaseURL += "&key=" + DataKey + "&value=" + FGenericPlatformHttp::UrlEncode(DataValue) + "&operation=" + UEnum::GetValueAsString<EGJDataOperation>(DataOperation).RightChop(16);
    UE_LOG(LogTemp, Error, TEXT("%s"), *UGameJolt::CreateURL(BaseURL, GameJolt));
    FieldData = UJsonFieldData::GetRequest(UGameJolt::CreateURL(BaseURL, GameJolt, Filter == EGJDataStore::user ? true : false));
    FieldData->OnGetResult.AddUnique(funcDelegate);
}

void UUpdate::Callback(const bool bSuccess, UJsonFieldData* JSON, const EJSONResult Status)
{
    Super::Callback(bSuccess, JSON, Status);
    if(!bResponseValid)
    {
        Failure.Broadcast();
        return;
    }
    bool bJsonSuccess = false;
    Success.Broadcast(response->GetString("data", bJsonSuccess));
}