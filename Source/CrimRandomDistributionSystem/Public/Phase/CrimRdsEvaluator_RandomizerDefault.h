// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "CrimRdsEvaluator_Randomizer.h"
#include "CrimRdsEvaluator_RandomizerDefault.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = "CrimRds", DisplayName = "Default")
class CRIMRANDOMDISTRIBUTIONSYSTEM_API UCrimRdsEvaluator_RandomizerDefault : public UCrimRdsEvaluator_Randomizer
{
	GENERATED_BODY()

public:
	virtual FCrimRdsTableRow SelectRow(const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsTableRow>& SelectableRows) override;
};
