// Copyright Soccertitan


#include "CrimRdsTypes.h"


FCrimRdsRow::FCrimRdsRow(FName InName, const FCrimRdsTableRow& TableRow)
{
	Name = InName;
	Probability = TableRow.Probability;
	bIsUnique = TableRow.bIsUnique;
	bAlwaysPick = TableRow.bAlwaysPick;
	bEnabled = TableRow.bEnabled;
	OwnedTags = TableRow.OwnedTags;
	Item = TableRow.Item;
	Id = FGuid::NewGuid();
}
