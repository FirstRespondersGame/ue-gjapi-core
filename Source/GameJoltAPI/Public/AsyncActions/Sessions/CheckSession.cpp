// Copyright by Free2Play-Entertainment (2020)


#include "CheckSession.h"
#include "GameJoltEnums.h"

void UCheckSession::Activate()
{
    if(!Super::Validate())
        return;
    FScriptDelegate funcDelegate;
    funcDelegate.BindUFunction(this, "Callback");
    FieldData = UJsonData::GetRequest(UGameJolt::CreateURL("/sessions/check/?"));
    FieldData->OnGetResult.AddUnique(funcDelegate);
}

void UCheckSession::Callback(const bool bSuccess, UJsonData* JSON)
{
    if(!bSuccess)
    {
        Failure.Broadcast(EGJErrors::UnknownError);
        return;
    }

    response = JSON->GetObject("response");
    if(!response)
    {
        Failure.Broadcast(EGJErrors::ResponseInvalid);
        return;
    }

    bool bResponseSuccess = response->GetBool("success");
    Success.Broadcast(bResponseSuccess);
}