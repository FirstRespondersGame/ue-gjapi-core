// Copyright by Free2Play-Entertainment (2020)


#include "CloseSession.h"

UCloseSession* UCloseSession::CloseSession(UGameJolt* GJAPI)
{
    UCloseSession* SessionNode = NewObject<UCloseSession>();
    SessionNode->GameJolt = GJAPI;
    return SessionNode;
}

void UCloseSession::Activate()
{
    if(!Super::Validate())
    {
        Failure.Broadcast();
        return;
    }
    FScriptDelegate funcDelegate;
    funcDelegate.BindUFunction(this, "Callback");
    FieldData = UJsonData::GetRequest(UGameJolt::CreateURL(("/sessions/close/?"), GameJolt));
    FieldData->OnGetResult.AddUnique(funcDelegate);
}

void UCloseSession::Callback(const bool bSuccess, UJsonData* JSON)
{
    Super::Callback(bSuccess, JSON);
    if(!bResponseValid)
    {
        Failure.Broadcast();
        return;
    }

    Success.Broadcast();
}