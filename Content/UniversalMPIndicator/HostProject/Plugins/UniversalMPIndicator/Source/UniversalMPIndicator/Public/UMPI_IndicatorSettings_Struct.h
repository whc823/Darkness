// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMPI_OnScreen_Texture_Struct.h"
#include "UMPI_OffScreen_Texture_Struct.h"
#include "UMPI_IndicatorType_Struct.h"
#include "UMPI_Effect_Struct.h"
#include "Engine/DataTable.h"
#include "UMPI_IndicatorSettings_Struct.generated.h"

/**
 * 
 */
class UNIVERSALMPINDICATOR_API UMPI_IndicatorSettings_Struct
{
public:
	UMPI_IndicatorSettings_Struct();
	~UMPI_IndicatorSettings_Struct();
};


USTRUCT(BlueprintType)
struct FUMPI_IndicatorSettings_Struct : public FTableRowBase
{

	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "OnScreen Texture Settings"), Category = "Struct")
		FUMPI_OnScreen_Texture_Struct OnScreen_Texture_Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "OffScreen Texture Settings"), Category = "Struct")
		FUMPI_OffScreen_Texture_Struct OffScreen_Texture_Settings;

	/* This is the value which activate or desactivate the indicator distance Modificator. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Use Distance Modificator"), Category = "Struct")
		bool Use_Distance_Modificator;

	/* This is the value which devide the main distance value(in Unreal Units), if divide to 100 result will be in metres (by def is 100 for metre show). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = Use_Distance_Modificator), meta = (DisplayName = "Distance Modification Value"), Category = "Struct")
		float Distance_Modification_Value = 100;

	/* This is Distance unit indicator */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = Use_Distance_Modificator), meta = (DisplayName = "Distance Unit Indicator"), Category = "Struct")
		FString Distance_Unit_Indicator = "m";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Enable Arrive Calculation Function"), Category = "Struct")
		bool Arrive_Function;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = Arrive_Function), meta = (DisplayName = "Distance For Arrive in Units (m * 100)"), Category = "Struct")
		float Distance_For_Arrive_Units = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Distance Based Visibility"), Category = "Struct")
		float Distance_Based_Visibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Life Time"), Category = "Struct")
		float Life_Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Use Bound Z Offset for Actor Target"), Category = "Struct")
		bool Use_Z_Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Additional Bound Z Offsett for Actor Target"), Category = "Struct")
		float Additional_Z_Offsett;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Indicator Type"), Category = "Struct")
		FUMPI_IndicatorType_Struct Indicator_Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Effect Settings"), Category = "Struct")
		FUMPI_Effect_Struct EffectSettings;


};

