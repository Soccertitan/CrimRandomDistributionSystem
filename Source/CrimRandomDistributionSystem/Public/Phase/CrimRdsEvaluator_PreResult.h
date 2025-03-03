// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CrimRdsEvaluator_PreResult.generated.h"

struct FCrimRdsCustomExecutionParams;
struct FCrimRdsTableRow;

/**
 * Called in the evaluator before all the probabilities of all items of the current RDSTable are summed up together.
 * This is the moment to modify any values before a result is calculated.
 */
UCLASS(ClassGroup = "CrimRds", BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced, Abstract)
class CRIMRANDOMDISTRIBUTIONSYSTEM_API UCrimRdsEvaluator_PreResult : public UObject
{
	GENERATED_BODY()

public:

	UCrimRdsEvaluator_PreResult();

	/**
	 * Allows you to modify the values of the Row before any Rows are added to the result.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Row The mutable row to update.
	 */
	virtual void OnPreResultEvaluation(const FCrimRdsCustomExecutionParams& ExecutionParams, FCrimRdsTableRow& Row);

protected:
	
	/**
	 * Allows you to modify the values of the Row before any Rows are added to the result.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Row The mutable row to update.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnPreResultEvaluation")
	void K2_OnPreResultEvaluation(UPARAM(ref) const FCrimRdsCustomExecutionParams& ExecutionParams, UPARAM(ref) FCrimRdsTableRow& Row);

private:

	uint8 bHasOnPreResultEvaluation : 1;
};
