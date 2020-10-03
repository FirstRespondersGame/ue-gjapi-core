// Copyright by Free2Play-Entertainment (2020)

#pragma once

#include "CoreMinimal.h"
#include "GameJoltAsyncBase.h"
#include "GameJoltEnums.h"
#include "Update.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateSuccessDelegate, FString, Data);

/**
 * Updates data in the data store.
 */
UCLASS()
class GAMEJOLTAPI_API UUpdate final : public UGameJoltAsyncBase
{
	GENERATED_BODY()

public:

	/**
	 * Updates data in the data store.
	 * @param Key The key of the data item you'd like to update.
	 * @param Value The value you'd like to apply to the data store item. 
	 * @param Operation The operation you'd like to perform.
	 * You can only perform mathematic operations on numerical data.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UUpdate* UpdateData(EGJDataStore Scope, const FString Key, const FString Value, EGJDataOperation Operation);

	UPROPERTY(BlueprintAssignable)
	FUpdateSuccessDelegate Success;

	// UBlueprintAsyncActionBase interface
    virtual void Activate() override;
    //~UBlueprintAsyncActionBase interface

private:

	FString DataKey;
	FString DataValue;
	EGJDataStore Filter;
	EGJDataOperation DataOperation;

	UFUNCTION()
	virtual void Callback(const bool bSuccess, UJsonData* JSON) override;
};
