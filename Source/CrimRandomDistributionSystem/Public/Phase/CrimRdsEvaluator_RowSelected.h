// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CrimRdsEvaluator_RowSelected.generated.h"

struct FCrimRdsCustomExecutionParams;
struct FCrimRdsTableRow;

/**
 * Called after the Evaluator has selected a Row.
 */
UCLASS(ClassGroup = "CrimRds", BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced, Abstract)
class CRIMRANDOMDISTRIBUTIONSYSTEM_API UCrimRdsEvaluator_RowSelected : public UObject
{
	GENERATED_BODY()

public:
	UCrimRdsEvaluator_RowSelected();

	/**
	 * Allows you to react when a Row is selected and about to be added to Results.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Row The selected row.
	 */
	virtual void OnRowSelected(const FCrimRdsCustomExecutionParams& ExecutionParams, FCrimRdsTableRow& Row);

protected:
	
	/**
	 * Allows you to react when a Row is selected and about to be added to Results.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Row The selected row.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnRowSelected")
	void K2_OnRowSelected(UPARAM(ref) const FCrimRdsCustomExecutionParams& ExecutionParams, UPARAM(ref) FCrimRdsTableRow& Row);
	
private:

	uint8 bHasOnRowSelected : 1;
};
