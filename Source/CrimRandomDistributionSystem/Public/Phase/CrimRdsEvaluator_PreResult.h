// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "CrimRdsEvaluatorBase.h"
#include "CrimRdsExecutionEvaluator.h"
#include "UObject/Object.h"
#include "CrimRdsEvaluator_PreResult.generated.h"

struct FCrimRdsCustomExecutionParams;
struct FCrimRdsRow;

/**
 * Called in the evaluator before all the probabilities of all items of the current RDSTable are summed up together.
 * This is the moment to modify any values before a result is calculated.
 */
UCLASS(ClassGroup = "CrimRds", BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced, Abstract)
class CRIMRANDOMDISTRIBUTIONSYSTEM_API UCrimRdsEvaluator_PreResult : public UCrimRdsEvaluatorBase
{
	GENERATED_BODY()

public:

	UCrimRdsEvaluator_PreResult();

	/**
	 * Allows you to modify the values of each Row before any Rows are added to the result.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Row The mutable row to update.
	 */
	virtual void OnPreResultRowEvaluation(const FCrimRdsCustomExecutionParams& ExecutionParams, FCrimRdsRow& Row);

	/**
	 * Called after all rows have been evaluated in OnPreResultRowEvaluation. Allows you to modify the Rows array and
	 * other parameters before any rows are added to the result.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Rows The mutable array of rows.
	 */
	virtual void OnPreResultTableEvaluation(const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsRow>& Rows);

protected:
	
	/**
	 * Allows you to modify the values of the Row before any Rows are added to the result.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Row The mutable row to update.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnPreResultRowEvaluation")
	void K2_OnPreResultRowEvaluation(UPARAM(ref) const FCrimRdsCustomExecutionParams& ExecutionParams, UPARAM(ref) FCrimRdsRow& Row);

	/**
	 * Called after all rows have been evaluated in OnPreResultRowEvaluation. Allows you to modify the Rows array and
	 * other parameters before any rows are added to the result.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Rows The mutable array of rows.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnPreResultTableEvaluation")
	void K2_OnPreResultTableEvaluation(UPARAM(ref) const FCrimRdsCustomExecutionParams& ExecutionParams, UPARAM(ref) TArray<FCrimRdsRow>& Rows);

private:

	uint8 bHasOnPreResultRowEvaluation : 1;
	uint8 bHasOnPreResultTableEvaluation : 1;
};
