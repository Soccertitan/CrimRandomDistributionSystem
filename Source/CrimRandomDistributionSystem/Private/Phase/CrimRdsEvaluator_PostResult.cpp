// Copyright Soccertitan


#include "Phase/CrimRdsEvaluator_PostResult.h"

#include "BlueprintNodeHelpers.h"
#include "CrimRdsExecutionEvaluator.h"

UCrimRdsEvaluator_PostResult::UCrimRdsEvaluator_PostResult()
{
	bHasOnPostResultEvaluation = BlueprintNodeHelpers::HasBlueprintFunction(TEXT("K2_OnPostResultEvaluation"), *this, *StaticClass());
}

void UCrimRdsEvaluator_PostResult::OnPostResultEvaluation(const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsRow>& Result)
{
	if (IsValid(ExecutionParams.Evaluator))
	{
		if (bHasOnPostResultEvaluation)
		{
			K2_OnPostResultEvaluation(ExecutionParams, Result);
		}
	}
}
