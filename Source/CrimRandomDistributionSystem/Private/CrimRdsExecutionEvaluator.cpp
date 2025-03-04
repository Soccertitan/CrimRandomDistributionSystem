// Copyright Soccertitan


#include "CrimRdsExecutionEvaluator.h"

#include "CrimRdsTypes.h"
#include "Phase/CrimRdsEvaluator_RowSelected.h"
#include "Phase/CrimRdsEvaluator_PostResult.h"
#include "Phase/CrimRdsEvaluator_PreResult.h"
#include "Phase/CrimRdsEvaluator_Randomizer.h"
#include "Phase/CrimRdsEvaluator_RandomizerDefault.h"

UCrimRdsExecutionEvaluator::UCrimRdsExecutionEvaluator()
{
	Randomizer = CreateDefaultSubobject<UCrimRdsEvaluator_RandomizerDefault>("RandomizerCountUp");
}

bool UCrimRdsExecutionEvaluator::Execute(FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsTableRow>& OutResult)
{
	const FCrimRdsTableRow* Row = ExecutionParams.RdsTableRowHandle.GetRow<FCrimRdsTableRow>(FString());
	if (!IsValid(ExecutionParams.RdsTableRowHandle.DataTable) ||
		!ExecutionParams.RdsTableRowHandle.DataTable->GetRowStruct()->IsChildOf(FCrimRdsTableRow::StaticStruct()) ||
		!Row)
	{
		return false;
	}
	
	const FCrimRdsItem_Table* Table = Row->Item.GetPtr<FCrimRdsItem_Table>();
	if (!Table)
	{
		return false;
	}

	OutResult.Empty();
	const UDataTable* RootTable = Table->DataAsset.LoadSynchronous();
	ExecutionParams.Evaluator = this;

	int32 Count = 0;
	if (ExecutionParams.Count > 0)
	{
		Count = ExecutionParams.Count;
	}
	else
	{
		Count = Table->Count;
	}
	
	EvaluateTable(RootTable, Count, ExecutionParams, OutResult);

	if (OutResult.Num() == 0)
	{
		return false;
	}
	
	for (TObjectPtr<UCrimRdsEvaluator_PostResult>& Evaluator : PostResultEvaluators)
	{
		if (Evaluator)
		{
			Evaluator->OnPostResultEvaluation(ExecutionParams, OutResult);
		}
	}
	
	return true;
}

void UCrimRdsExecutionEvaluator::EvaluateTable(const UDataTable* Table, int32 Count, const FCrimRdsCustomExecutionParams& ExecutionParams,
	TArray<FCrimRdsTableRow>& Result)
{
	TArray<FCrimRdsTableRow*> Rows;
	Table->GetAllRows<FCrimRdsTableRow>(FString(), Rows);
	if (Rows.Num() == 0)
	{
		return;
	}
	
	//----------------------------------------------------------------------------------------
	// 1. Make a mutable copy of the rows from the Table. And assigns a Guid to determine
	// equality between rows. We do this here because the DataTable can't be trusted to have
	// unique Ids.
	// Then run the PreResultEvaluator's to give designers a chance to modify the Row's value
	// before running the randomizer.
	//----------------------------------------------------------------------------------------
	TArray<FCrimRdsTableRow> MutableRows;
	for (const auto& Row : Rows)
	{
		FCrimRdsTableRow MutableRow = *Row;
		MutableRow.Id = FGuid::NewGuid();

		for (TObjectPtr<UCrimRdsEvaluator_PreResult>& Evaluator : PreResultEvaluators)
		{
			if (Evaluator)
			{
				Evaluator->OnPreResultRowEvaluation(ExecutionParams, MutableRow);
			}
		}
		MutableRows.Add(MutableRow);
	}

	for (TObjectPtr<UCrimRdsEvaluator_PreResult>& Evaluator : PreResultEvaluators)
	{
		if (Evaluator)
		{
			Evaluator->OnPreResultTableEvaluation(ExecutionParams, MutableRows);
		}
	}

	//----------------------------------------------------------------------------------------
	// 2. Add all MutableRows that are AlwaysPicked and Enabled.
	// Also add the other enabled rows to a SelectableRows array. This will get passed to the
	// randomizer for processing.
	//----------------------------------------------------------------------------------------
	TArray<FCrimRdsTableRow> SelectableRows;
	for (FCrimRdsTableRow& Row : MutableRows)
	{
		if (Row.bAlwaysPick && Row.bEnabled)
		{
			Count--;
			AddToResult(Row, ExecutionParams, Result);
		}
		else if (Row.bEnabled)
		{
			SelectableRows.Add(Row);
		}
	}

	//----------------------------------------------------------------------------------------
	// 3. Continue only if there are counts left to process and SelectableRows is greater than 0.
	// Each loop for the CurrentCount the Randomizer will select a row to be added to the result.
	// Then, if the SelectedRow is unique, remove it from the SelectableRows array. This ensures
	// Unique results cannot be selected twice.
	//----------------------------------------------------------------------------------------
	if (Count > 0 && SelectableRows.Num() > 0)
	{
		for (int32 CurrentCount = 0; CurrentCount < Count; CurrentCount++)
		{
			FCrimRdsTableRow SelectedRow = Randomizer->SelectRow(ExecutionParams, SelectableRows);

			if (SelectedRow.bIsUnique)
			{
				SelectableRows.Remove(SelectedRow);	
			}
			AddToResult(SelectedRow, ExecutionParams, Result);
		}
	}
}

void UCrimRdsExecutionEvaluator::AddToResult(FCrimRdsTableRow Row, const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsTableRow>& Result)
{
	// Must have a valid Row Item to be added.
	if (Row.Item.GetPtr<FCrimRdsItemBase>())
	{
		for (auto& Evaluator : RowSelectedEvaluators)
		{
			if (Evaluator)
			{
				Evaluator->OnRowSelected(ExecutionParams, Row);
			}
		}
		
		if (const FCrimRdsItem_Table* Table = Row.Item.GetPtr<FCrimRdsItem_Table>())
		{
			EvaluateTable(Table->DataAsset.LoadSynchronous(), Table->Count, ExecutionParams, Result);
		}
		else
		{
			// Only add Non Table items to the Result.
			Result.Add(Row);
		}
	}
}
