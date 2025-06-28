// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMPI_OnScreenRotation_Struct.generated.h"

/**
 * 
 */
class UNIVERSALMPINDICATOR_API UMPI_OnScreenRotation_Struct
{
public:
	UMPI_OnScreenRotation_Struct();
	~UMPI_OnScreenRotation_Struct();
};



USTRUCT(BlueprintType)
struct FUMPI_OnScreenRotation_Struct
{

	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Use"), Category = "Struct")
		bool Use;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Rotation Rate"), Category = "Struct")
		float Rotation_Rate;


};


