﻿// Copyright Soccertitan


#include "Phase/CrimRdsEvaluator_Randomizer.h"

#include "BlueprintNodeHelpers.h"
#include "CrimRdsExecutionEvaluator.h"

UCrimRdsEvaluator_Randomizer::UCrimRdsEvaluator_Randomizer()
{
	bHasSelectRow = BlueprintNodeHelpers::HasBlueprintFunction(TEXT("K2_SelectRow"), *this, *StaticClass());
}

FCrimRdsRow UCrimRdsEvaluator_Randomizer::SelectRow(const FCrimRdsCustomExecutionParams& ExecutionParams,
		TArray<FCrimRdsRow>& SelectableRows)
{
	if (IsValid(ExecutionParams.Evaluator))
	{
		if (bHasSelectRow)
		{
			return K2_SelectRow(ExecutionParams, SelectableRows);
		}
	}
	return FCrimRdsRow();
}
