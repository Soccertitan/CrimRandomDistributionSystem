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

bool UCrimRdsExecutionEvaluator::Execute(FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsRow>& OutResult)
{
	if (!IsValid(ExecutionParams.RdsTable) ||
		!ExecutionParams.RdsTable->GetRowStruct()->IsChildOf(FCrimRdsTableRow::StaticStruct()))
	{
		return false;
	}

	OutResult.Empty();
	ExecutionParams.Evaluator = this;
	
	EvaluateTable(ExecutionParams.RdsTable, ExecutionParams.Count, ExecutionParams, OutResult);

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
	TArray<FCrimRdsRow>& Result)
{
	//----------------------------------------------------------------------------------------
	// 1. Make a mutable copy of the rows from the Table.
	// Then run the PreResultEvaluator's to give designers a chance to modify the Row's value
	// before running the randomizer.
	//----------------------------------------------------------------------------------------
	TArray<FCrimRdsRow> MutableRows;
	for (const auto& It : Table->GetRowMap())
	{
		FCrimRdsRow MutableRow = FCrimRdsRow(It.Key, *(FCrimRdsTableRow*)It.Value);

		for (TObjectPtr<UCrimRdsEvaluator_PreResult>& Evaluator : PreResultEvaluators)
		{
			if (Evaluator)
			{
				Evaluator->OnPreResultRowEvaluation(ExecutionParams, MutableRow);
			}
		}
		MutableRows.Add(MutableRow);
	}
	
	if (MutableRows.Num() == 0)
	{
		return;
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
	TArray<FCrimRdsRow> SelectableRows;
	for (FCrimRdsRow& Row : MutableRows)
	{
		if (Row.bAlwaysPick && Row.bEnabled)
		{
			Count--;
			AddToResult(Row, ExecutionParams, Result);

			if (!Row.bIsUnique)
			{
				SelectableRows.Add(Row);
			}
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
			FCrimRdsRow SelectedRow = Randomizer->SelectRow(ExecutionParams, SelectableRows);

			if (SelectedRow.bIsUnique)
			{
				SelectableRows.Remove(SelectedRow);
			}
			AddToResult(SelectedRow, ExecutionParams, Result);
		}
	}
}

void UCrimRdsExecutionEvaluator::AddToResult(FCrimRdsRow Row, const FCrimRdsCustomExecutionParams& ExecutionParams, TArray<FCrimRdsRow>& Result)
{
	// Must have a valid Row Item to be added to the result.
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
