// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMPI_OnScreenOpacity_Struct.generated.h"


/**
 * 
 */
class UNIVERSALMPINDICATOR_API UMPI_OnScreenOpacity_Struct
{
public:
	UMPI_OnScreenOpacity_Struct();
	~UMPI_OnScreenOpacity_Struct();
};


USTRUCT(BlueprintType)
struct FUMPI_OnScreenOpacity_Struct
{

	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Use"), Category = "Struct")
		bool Use;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Speed"), Category = "Struct")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Do Once"), Category = "Struct")
		bool Do_Once;

};


