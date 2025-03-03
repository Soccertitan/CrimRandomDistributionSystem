// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CrimRdsEvaluator_PostResult.generated.h"

struct FCrimRdsCustomExecutionParams;
struct FCrimRdsTableRow;

/**
 * Occurs after the result has been calculated and the result set is complete, but before
 * the RDSTable's Result method exits.
 */
UCLASS(ClassGroup = "CrimRds", BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced, Abstract)
class CRIMRANDOMDISTRIBUTIONSYSTEM_API UCrimRdsEvaluator_PostResult : public UObject
{
	GENERATED_BODY()

public:

	UCrimRdsEvaluator_PostResult();

	/**
	 * Allows you to make further changes to the Result before the ExecutionEvaluator finishes.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Result A collection of all the rows that were selected.
	 */
	virtual void OnPostResultEvaluation(const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsTableRow>& Result);

protected:
	
	/**
	 * Allows you to make further changes to the Result before the ExecutionEvaluator finishes.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Result A collection of all the rows that were selected.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnPostResultEvaluation")
	void K2_OnPostResultEvaluation(UPARAM(ref) const FCrimRdsCustomExecutionParams& ExecutionParams, UPARAM(ref) TArray<FCrimRdsTableRow>& Result);

private:

	uint8 bHasOnPostResultEvaluation : 1;
};
