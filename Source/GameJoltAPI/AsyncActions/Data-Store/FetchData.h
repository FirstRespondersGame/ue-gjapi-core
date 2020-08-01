// Copyright by Free2Play-Entertainment (2020)

#pragma once

#include "CoreMinimal.h"
#include "GameJoltAsyncBase.h"
#include "GameJoltEnums.h"
#include "FetchData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFetchDataSuccessDelegate, FString, Data);

/**
 * Returns data from the data store.
 */
UCLASS()
class GAMEJOLTAPI_API UFetchData final : public UGameJoltAsyncBase
{
	GENERATED_BODY()

public:

	/**
	 * Returns data from the data store.
	 * @param Scope If you select 'User', the data item will be fetched for a user. If you select 'Global', it will be fetched globally for the game.
	 * @param Key The key of the data item you'd like to fetch.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UFetchData* FetchData(UGameJolt* GameJoltAPI, EGJDataStore Scope, const FString Key);

	UPROPERTY(BlueprintAssignable)
	FFetchDataSuccessDelegate Success;

	// UBlueprintAsyncActionBase interface
    virtual void Activate() override;
    //~UBlueprintAsyncActionBase interface

private:

	FString DataKey;
	EGJDataStore Filter;

	UFUNCTION()
	virtual void Callback(const bool bSuccess, UJsonData* JSON) override;
};
