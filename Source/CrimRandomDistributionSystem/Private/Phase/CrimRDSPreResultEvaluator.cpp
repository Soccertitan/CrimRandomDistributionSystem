// Copyright Soccertitan


#include "Phase/CrimRdsEvaluator_PreResult.h"

#include "BlueprintNodeHelpers.h"
#include "CrimRdsExecutionEvaluator.h"

UCrimRdsEvaluator_PreResult::UCrimRdsEvaluator_PreResult()
{
	bHasOnPreResultEvaluation = BlueprintNodeHelpers::HasBlueprintFunction(TEXT("K2_OnPreResultEvaluation"), *this, *StaticClass());
}

void UCrimRdsEvaluator_PreResult::OnPreResultEvaluation(const FCrimRdsCustomExecutionParams& ExecutionParams, FCrimRdsTableRow& Row)
{
	if (IsValid(ExecutionParams.Evaluator))
	{
		if (bHasOnPreResultEvaluation)
		{
			K2_OnPreResultEvaluation(ExecutionParams, Row);
		}
	}
}
