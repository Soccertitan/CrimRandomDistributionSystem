// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"

#include "CrimRdsTypes.generated.h"

/**
 * The base struct that defines an item. Must be subclassed to allow new types of data to be
 * defined in the FCrimRdsTableRow.
 */
USTRUCT(BlueprintType)
struct CRIMRANDOMDISTRIBUTIONSYSTEM_API FCrimRdsItemBase
{
	GENERATED_BODY()
};

/**
 * A special struct that allows linking to a table with CrimRdsTableRows. The entry point for all RdsTables must start from here.
 */
USTRUCT(BlueprintType)
struct CRIMRANDOMDISTRIBUTIONSYSTEM_API FCrimRdsItem_Table : public FCrimRdsItemBase
{
	GENERATED_BODY()

	/**
	 * The maximum number of entries expected in the result. The final count of items in the result may be lower
	 * if some of the entries return a null result (no drop).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1, UIMin = 1))
	int32 Count = 1;

	/** The table to query for entries. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RequiredAssetDataTags = "RowStructure=/Script/CrimRandomDistributionSystem.CrimRdsTableRow"))
	TSoftObjectPtr<UDataTable> DataAsset;
};

/**
 * Contains a gameplay tag and value pair.
 */
USTRUCT(BlueprintType)
struct CRIMRANDOMDISTRIBUTIONSYSTEM_API FCrimRdsItem_TagValue : public FCrimRdsItemBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value = 0;
};

/**
 * A generic object soft class reference.
 */
USTRUCT(BlueprintType)
struct CRIMRANDOMDISTRIBUTIONSYSTEM_API FCrimRdsItem_ObjectClass : public FCrimRdsItemBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UObject> Object;
};

/**
 * A generic object soft path reference.
 */
USTRUCT(BlueprintType)
struct CRIMRANDOMDISTRIBUTIONSYSTEM_API FCrimRdsItem_ObjectPointer : public FCrimRdsItemBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UObject> Object;
};

/**
 * The CrimRdsTableRow used for determining the results.
 */
USTRUCT(BlueprintType)
struct FCrimRdsTableRow : public FTableRowBase
{
	GENERATED_BODY()

	/** The likelihood this entry will be selected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	float Probability = 0.f;
	/** This row can only be selected once in the result. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUnique = false;
	/** This row will always be part of the result set. Will only be selected once. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAlwaysPick = false;
	/** Only enabled rows can be selected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnabled = true;
	/** Gameplay tags this row has. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer OwnedTags;
	/** The actual item you want to return. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExcludeBaseStruct))
	TInstancedStruct<FCrimRdsItemBase> Item;
};

/**
 * The struct used in the CrimRdsExecutionEvaluator. Contains a copy of the data from an FCrimRdsTableRow.
 * Includes extra information for query.
 */
USTRUCT(BlueprintType)
struct CRIMRANDOMDISTRIBUTIONSYSTEM_API FCrimRdsRow
{
	GENERATED_BODY()

	FCrimRdsRow(){}
	FCrimRdsRow(FName InName, const FCrimRdsTableRow& TableRow);

	/** The name of the row from the FCrimRdsTableRow */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name = NAME_None;
	/** The likelihood this entry will be selected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	float Probability = 0.f;
	/** This row can only be selected once in the result. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUnique = false;
	/** This row will always be part of the result set. Will only be selected once. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAlwaysPick = false;
	/** Only enabled rows can be selected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnabled = true;
	/** Gameplay tags this row has. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer OwnedTags;
	/** The actual item you want to return. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExcludeBaseStruct))
	TInstancedStruct<FCrimRdsItemBase> Item;

	FGuid GetId() const {return Id;}
	
private:
	/** This Guid is used to identify equality between two structs. */
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	FGuid Id = FGuid();

public:
	friend bool operator==(const FCrimRdsRow& X, const FCrimRdsRow& Y)
	{
		return X.Id == Y.Id;
	}

	friend bool operator!=(const FCrimRdsRow& X, const FCrimRdsRow& Y)
	{
		return X.Id != Y.Id;
	}
};
