// Copyright Soccertitan


#include "Phase/CrimRdsEvaluator_RowSelected.h"

#include "BlueprintNodeHelpers.h"
#include "CrimRdsExecutionEvaluator.h"

UCrimRdsEvaluator_RowSelected::UCrimRdsEvaluator_RowSelected()
{
	bHasOnRowSelected = BlueprintNodeHelpers::HasBlueprintFunction(TEXT("K2_OnRowSelected"), *this, *StaticClass());
}

void UCrimRdsEvaluator_RowSelected::OnRowSelected(const FCrimRdsCustomExecutionParams& ExecutionParams, FCrimRdsTableRow& Row)
{
	if (IsValid(ExecutionParams.Evaluator))
	{
		if (bHasOnRowSelected)
		{
			K2_OnRowSelected(ExecutionParams, Row);
		}
	}
}
