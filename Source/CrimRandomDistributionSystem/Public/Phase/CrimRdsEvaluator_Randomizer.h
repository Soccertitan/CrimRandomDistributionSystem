// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "CrimRdsEvaluatorBase.h"
#include "UObject/Object.h"
#include "CrimRdsEvaluator_Randomizer.generated.h"

struct FCrimRdsCustomExecutionParams;
struct FCrimRdsTableRow;

/**
 * The algorithm to use when selecting a row from a collection.
 */
UCLASS(ClassGroup = "CrimRds", BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced, Abstract)
class CRIMRANDOMDISTRIBUTIONSYSTEM_API UCrimRdsEvaluator_Randomizer : public UCrimRdsEvaluatorBase
{
	GENERATED_BODY()

public:
	UCrimRdsEvaluator_Randomizer();

	/**
	 * Randomly picks a row from the SelectedRows.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param SelectableRows The rows that can be selected.
	 * @return A copy of the row that was chosen.
	 */
	virtual FCrimRdsTableRow SelectRow(const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsTableRow>& SelectableRows);

protected:
	
	/**
	 * Randomly picks a row from the SelectedRows.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param SelectableRows The rows that can be selected.
	 * @return A copy of the row that was chosen.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "SelectRow")
	FCrimRdsTableRow K2_SelectRow(UPARAM(ref) const FCrimRdsCustomExecutionParams& ExecutionParams, UPARAM(ref) TArray<FCrimRdsTableRow>& SelectableRows);

private:

	uint8 bHasSelectRow : 1;
};
