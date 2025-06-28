// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMPI_Indicator_Type_Enum.h"
#include "UMPI_IndicatorType_Struct.generated.h"

/**
 * 
 */
class UNIVERSALMPINDICATOR_API UMPI_IndicatorType_Struct
{
public:
	UMPI_IndicatorType_Struct();
	~UMPI_IndicatorType_Struct();
};


USTRUCT(BlueprintType)
struct FUMPI_IndicatorType_Struct
{

	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Indicator Type"), Category = "Struct")
		TEnumAsByte<UMPI_Indicator_Type_Enum_OP> Indicator_Type = UMPI_Indicator_Type_Enum_OP::OP_Classic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Circle Radius"), Category = "Struct")
		float Circle_Radius;


};

