// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class UNIVERSALMPINDICATOR_API UMPI_Indicator_Type_Enum
{
public:
	UMPI_Indicator_Type_Enum();
	~UMPI_Indicator_Type_Enum();
};

UENUM(BlueprintType, Category = "Indicator Type")
enum UMPI_Indicator_Type_Enum_OP
{
	OP_Classic      UMETA(DisplayName = "Classic"),
	OP_Circle      UMETA(DisplayName = "Circle"),
};