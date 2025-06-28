 // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMPI_OffScreenRotationRule_Enum.h"
#include "UMPI_DistanceText_Struct.h"
#include "UMPI_OnScreenScaleSwift_Struct.h"
#include "UMPI_OnScreenRotation_Struct.h"
#include "UMPI_OnScreenOpacity_Struct.h"
#include "UMPI_OnScreenPulse_Struct.h"
#include "UMPI_Effect_Struct.generated.h"


/**
 * 
 */
class UNIVERSALMPINDICATOR_API UMPI_Effect_Struct
{
public:
	UMPI_Effect_Struct();
	~UMPI_Effect_Struct();
};

USTRUCT(BlueprintType)
struct FUMPI_Effect_Struct
{

	GENERATED_BODY()


public:
    
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Off Rotation Rule"), Category = "Struct")
		TEnumAsByte<UMPI_OffScreenRotationRule_Enum_OP> Off_Rotation_Rule = UMPI_OffScreenRotationRule_Enum_OP::OP_Closest_Edge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Distance Text"), Category = "Struct")
		FUMPI_DistanceText_Struct Distance_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "On Screen Scale Swift Settings"), Category = "Struct")
		FUMPI_OnScreenScaleSwift_Struct OnScreenScaleSwift;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "OnScreen Rotation"), Category = "Struct")
		FUMPI_OnScreenRotation_Struct OnScreen_Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "On Screen Opacity"), Category = "Struct")
		FUMPI_OnScreenOpacity_Struct OnScreenOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "On Screen Pulse"), Category = "Struct")
		FUMPI_OnScreenPulse_Struct OnScreenPulse;


};