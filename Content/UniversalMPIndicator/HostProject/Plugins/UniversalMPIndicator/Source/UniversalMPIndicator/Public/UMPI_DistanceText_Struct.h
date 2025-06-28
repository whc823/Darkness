// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Fonts/SlateFontInfo.h"
#include "Math/Color.h"
#include "UMPI_DistanceText_Struct.generated.h"

/**
 * 
 */
class UNIVERSALMPINDICATOR_API UMPI_DistanceText_Struct
{
public:
	UMPI_DistanceText_Struct();
	~UMPI_DistanceText_Struct();
};

USTRUCT(BlueprintType)
struct FUMPI_DistanceText_Struct
{

	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ShowDistance Text"), Category = "Struct")
		bool Show_Distance_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
		FSlateFontInfo Font_Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Text Color"), Category = "Struct")
		FLinearColor Text_Color;


};
