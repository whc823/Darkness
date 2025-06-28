// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMPI_OnScreenPulse_Struct.generated.h"

/**
 * 
 */
class UNIVERSALMPINDICATOR_API UMPI_OnScreenPulse_Struct
{
public:
	UMPI_OnScreenPulse_Struct();
	~UMPI_OnScreenPulse_Struct();
};


USTRUCT(BlueprintType)
struct FUMPI_OnScreenPulse_Struct
{

	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Use"), Category = "Struct")
		bool Use;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Speed"), Category = "Struct")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Pulse Scale Limit"), Category = "Struct")
		float Pulse_Scale_Limit;

};

