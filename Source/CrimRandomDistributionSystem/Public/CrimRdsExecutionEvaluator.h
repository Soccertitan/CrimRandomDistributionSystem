// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "CrimRDSTypes.h"
#include "UObject/Object.h"
#include "CrimRdsExecutionEvaluator.generated.h"

class UCrimRdsEvaluator_Randomizer;
class UCrimRdsEvaluator_PostResult;
class UCrimRdsEvaluator_RowSelected;
class UCrimRdsEvaluator_PreResult;
class UCrimRdsExecutionEvaluator;

/**
 * Contains the params to start an execution.
 */
USTRUCT(BlueprintType)
struct CRIMRANDOMDISTRIBUTIONSYSTEM_API FCrimRdsCustomExecutionParams
{
	GENERATED_BODY()

	/** The Table and Row that contains a CrimRdsItem_Table item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RowType ="CrimRdsTableRow"))
	FDataTableRowHandle RdsTableRowHandle;

	/** If set to greater than 0, will use this value instead of the TableRowHandle's value for number of counts. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count = 0;

	/** Can contain custom information to pass along to the function. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UObject> Context;

	/** The evaluator for the params. Will be set in the CrimRDSExecutionEvaluator. */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCrimRdsExecutionEvaluator> Evaluator;
};

/**
 * A class that can take a FCrimDataTable row and return a list of CrimRDSEntries that were successfully hit by the
 * evaluator. This class is generic to handle all sorts of 'loot' table designs.
 */
UCLASS(ClassGroup = "CrimRds", BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class CRIMRANDOMDISTRIBUTIONSYSTEM_API UCrimRdsExecutionEvaluator : public UObject
{
	GENERATED_BODY()

public:

	UCrimRdsExecutionEvaluator();
	
	/**
	 * Initiates the functions to determine which rows will/can be selected from the table. Throughout the process, there are hooks
	 * that can modify values during the execution. Pre result, on select, and post result evaluation steps.
	 * @param ExecutionParams Contains the parameters to evaluate a CrimRdsTableRow Table. Including a custom context
	 * that can be passed in.
	 * @param OutResult All the rows that were selected by the evaluator.
	 * @return True if at least one result was returned.
	 */
	UFUNCTION(BlueprintCallable)
	bool Execute(UPARAM(ref) FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsTableRow>& OutResult);

protected:

	/** The randomizer to use when selecting a row. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, NoClear)
	TObjectPtr<UCrimRdsEvaluator_Randomizer> Randomizer;
	
	/** Called on each row in the table prior to adding them to the list of eligible entries. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<UCrimRdsEvaluator_PreResult>> PreResultEvaluators;

	/** Called anytime a row is selected from the table. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<UCrimRdsEvaluator_RowSelected>> RowSelectedEvaluators;

	/** Called at the end of the evaluation once the selection is completed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<UCrimRdsEvaluator_PostResult>> PostResultEvaluators;

private:

	/**
	 * Runs through the process of adding rows to the Result. Calling on RowSelected when a row is added to the Result.
	 * 1. Makes a mutable copy of the DataTable Rows.
	 * 2. Runs the PreResultEvaluators on each Row. The only opportunity to modify the Row's values before selection occurs.
	 * 3. Adds all Rows where AlwaysPick and Enabled is true to the Results.
	 * 4. Runs the Randomizer equal to the Count number - the number of Results added in Step 3 and sends the Rows that were not picked in step 3.
	 * 5. Exit function.
	 * @param Table The DataTable with row type CrimRdsTableRow.
	 * @param Count The number of attempts to try and select an item from the row.
	 * @param ExecutionParams Context of the Execution.
	 * @param Result All the results that have been selected.
	 */
	void EvaluateTable(const UDataTable* Table, int32 Count, const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsTableRow>& Result);

	/**
	 * Adds the Row to the Result. If a CrimRdsItem_Row is the item in the passed in row. It will trigger EvaluateTable.
	 * @param Row The row to add to Result.
	 * @param ExecutionParams Context of the Execution.
	 * @param Result All the results that have been selected.
	 */
	void AddToResult(FCrimRdsTableRow Row, const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsTableRow>& Result);
};
