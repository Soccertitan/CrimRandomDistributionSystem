// Copyright Soccertitan


#include "Phase/CrimRdsEvaluator_PreResult.h"

#include "BlueprintNodeHelpers.h"
#include "CrimRdsExecutionEvaluator.h"

UCrimRdsEvaluator_PreResult::UCrimRdsEvaluator_PreResult()
{
	bHasOnPreResultRowEvaluation = BlueprintNodeHelpers::HasBlueprintFunction(TEXT("K2_OnPreResultRowEvaluation"), *this, *StaticClass());
	bHasOnPreResultTableEvaluation = BlueprintNodeHelpers::HasBlueprintFunction(TEXT("K2_OnPreResultTableEvaluation"), *this, *StaticClass());
}

void UCrimRdsEvaluator_PreResult::OnPreResultRowEvaluation(const FCrimRdsCustomExecutionParams& ExecutionParams, FCrimRdsRow& Row)
{
	if (IsValid(ExecutionParams.Evaluator))
	{
		if (bHasOnPreResultRowEvaluation)
		{
			K2_OnPreResultRowEvaluation(ExecutionParams, Row);
		}
	}
}

void UCrimRdsEvaluator_PreResult::OnPreResultTableEvaluation(const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsRow>& Rows)
{
	if (IsValid(ExecutionParams.Evaluator))
	{
		if (bHasOnPreResultTableEvaluation)
		{
			K2_OnPreResultTableEvaluation(ExecutionParams, Rows);
		}
	}
}
