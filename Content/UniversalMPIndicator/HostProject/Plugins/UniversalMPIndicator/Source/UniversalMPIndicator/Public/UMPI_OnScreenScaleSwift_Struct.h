// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMPI_OnScreenScaleSwift_Struct.generated.h"

/**
 * 
 */
class UNIVERSALMPINDICATOR_API UMPI_OnScreenScaleSwift_Struct
{
public:
	UMPI_OnScreenScaleSwift_Struct();
	~UMPI_OnScreenScaleSwift_Struct();
};


USTRUCT(BlueprintType)
struct FUMPI_OnScreenScaleSwift_Struct
{

	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Use"), Category = "Struct")
		bool Use;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Init Scale"), Category = "Struct")
		FVector2D Init_Scale = {5,5};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Speed"), Category = "Struct")
		float Speed = 7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Do Once"), Category = "Struct")
		bool Do_Once;


};

