// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "CrimRdsEvaluator_Randomizer.h"
#include "CrimRdsEvaluator_RandomizerDefault.generated.h"

struct FCrimRdsRow;

/**
 * 
 */
UCLASS(ClassGroup = "CrimRds", DisplayName = "Default")
class CRIMRANDOMDISTRIBUTIONSYSTEM_API UCrimRdsEvaluator_RandomizerDefault : public UCrimRdsEvaluator_Randomizer
{
	GENERATED_BODY()

public:
	virtual FCrimRdsRow SelectRow(const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsRow>& SelectableRows) override;
};
