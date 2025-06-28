// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class UNIVERSALMPINDICATOR_API UMPI_OffScreenRotationRule_Enum
{
public:
	UMPI_OffScreenRotationRule_Enum();
	~UMPI_OffScreenRotationRule_Enum();
};

UENUM(BlueprintType, Category = "UMPI OffScreen RotationRule")
enum UMPI_OffScreenRotationRule_Enum_OP
{
	OP_Free              UMETA(DisplayName = "Free"),
	OP_Closest_Edge      UMETA(DisplayName = "Closest Edge"),
	OP_Do_Not_Rotate     UMETA(DisplayName = "Do Not Rotate"),

};

