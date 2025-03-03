# CrimRandomDistributionSystem

## Introduction
This is an Unreal Engine 5.5+ plugin that was inspired by Mike's (Prof. Chuck) writeup on loot tables, maps, and monsters. You can find his documentation here for his C# implementation: https://www.codeproject.com/Articles/420046/Loot-Tables-Random-Maps-and-Monsters-Part-I

In Unreal Engine we can achieve the same level of polymorphism by utulizing InstancedStructs in DataTables which would not be possible otherwise. The entire system is generic enough that it can be used for anything. Loot for items to give player, randomly select monsters to spawn, rolling affixes/stats on equipment, generating maps, you name it. Anything should be possible. I highly recommend Mike's article for the design philosophy.

The code base is quite small and well commented. I would encourage you to look at the CrimRdsTypes.h file to see all the structs.

## Structs
Instanced Structs are normal structs wrapped in a TInstancedStruct or FInstancedStruct. You can read more about them on mattyman174 GenericItemizationPlugin https://github.com/mattyman174/GenericItemization
He does a good writeup on what they are.

In this plugin there are three primary Structs.
1. FCrimRdsTableRow: This is the struct that contains the attributes a row has for determining selection and an InstancedStruct called Item.
2. FCrimRdsItemBase: The base struct for any item in a CrimRdsTableRow.
3. FCrimRdsItem_Table: This special struct allows for having child tables to query for loot.

There are also some additional FCrimRdsItemBase child structs that should be able to handle common use cases. A TagValue pair, an FName, and generic UObject soft class and pointer references. If you need data that is not already included, you will need to create a child Struct of type FCrimRdsItemBase in C++.

The last struct is in the CrimRdsExecutionEvaluator and is called FCrimRdsCustomExecutionParams. It contains information on the DataTableRowHandle to kick off the loot table, an optional Context, and a reference to the Evaluator object that last executed with the Params. The ExecutionParams are sent to the various hooks during the Execute process. This allows designers to have access to information on the currently running Execution.

## CrimRdsExecutionEvaluator
This is the base class for determining the outcome of a 'loot' table. The class is designed similiary to Mike's. There is a PreResult, OnSelect, PostResult, and Randomizer supporting classes that are designed to be extended and added as properties to the the main CrimRdsExecutionEvaluator.

PreResultEvaluators is called prior to any rows in the table being added to the pool of selectable rows. This is where you can play with probability, uniqueness, always pick variables.

When a row is added to the Result, RowSelectedEvaluators get called. This is an opportunity to do anything you want to the row. As it is a copy of the element in the selectable rows array. For a Diable example, initiating a new execution that rolls stats on the selected item.

The Randomizer is called whenever the execution wants a random row selected. It will return a copy of the select row which will then be added to the Results.

The final class is the PostResultEvaluators. This is called prior to the execution terminating allowing you to make final changes to Results array prior to the caller getting the Results back.
