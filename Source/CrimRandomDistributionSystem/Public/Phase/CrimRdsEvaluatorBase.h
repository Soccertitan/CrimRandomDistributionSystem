// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CrimRdsEvaluatorBase.generated.h"

/**
 * The parent class for types of Evaluators.
 */
UCLASS(Abstract)
class CRIMRANDOMDISTRIBUTIONSYSTEM_API UCrimRdsEvaluatorBase : public UObject
{
	GENERATED_BODY()

public:

	UCrimRdsEvaluatorBase();
};
