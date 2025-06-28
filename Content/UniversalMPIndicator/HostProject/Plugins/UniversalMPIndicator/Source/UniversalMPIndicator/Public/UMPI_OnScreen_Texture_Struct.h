// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Math/Color.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInterface.h"
#include "UMPI_OnScreen_Texture_Struct.generated.h"

/**
 * 
 */
class UNIVERSALMPINDICATOR_API UMPI_OnScreen_Texture_Struct
{
public:
	UMPI_OnScreen_Texture_Struct();
	~UMPI_OnScreen_Texture_Struct();
};

USTRUCT(BlueprintType)
struct FUMPI_OnScreen_Texture_Struct
{

	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Use Material Image"), Category = "Struct")
		bool Use_Material_Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Indicator Material Image"), meta =(EditCondition = Use_Material_Image), Category = "Struct")
		UMaterialInterface* Material_Image = NULL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Indicator Texture"), Category = "Struct")
		UTexture2D* Screen_Texture = UTexture2D::CreateTransient(1024, 1024);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Indicator Size"), Category = "Struct")
		FVector2D Screen_Indicator_Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Indicator Pivot"), Category = "Struct")
		FVector2D Screen_Indicator_Pivot = {0.5,0.5};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Tint Color"), Category = "Struct")
		FLinearColor Tint_Color;


};
