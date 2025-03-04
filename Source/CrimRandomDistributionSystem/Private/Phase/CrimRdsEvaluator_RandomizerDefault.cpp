// Copyright Soccertitan


#include "Phase/CrimRdsEvaluator_RandomizerDefault.h"

#include "CrimRdsTypes.h"

FCrimRdsTableRow UCrimRdsEvaluator_RandomizerDefault::SelectRow(const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsTableRow>& SelectableRows)
{
	FCrimRdsTableRow Result = Super::SelectRow(ExecutionParams, SelectableRows);

	/** Return the result if the Id is valid. */
	if (Result.Id.IsValid())
	{
		return Result;
	}

	/**
	 * Adds up all the Row's probability values.
	 */
	float TotalProbability = 0.f;
	for (const FCrimRdsTableRow& Row : SelectableRows)
	{
		TotalProbability += Row.Probability;
	}

	float HitValue = FMath::FRandRange(0.f, TotalProbability);
	float RunningValue = 0.f;
	for (const FCrimRdsTableRow& Row : SelectableRows)
	{
		// Count up until we find the first item that exceeds the HitValue.
		RunningValue += Row.Probability;
		if (HitValue <= RunningValue)
		{
			return Row;
		}
	}
	return Result;
}
