// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMPI_IndicatorSettings_Struct.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/SlateWrapperTypes.h"
#include "UMPI_OffScreenRotationRule_Enum.h"
#include "UMPI_Indicator_Type_Enum.h"
#include "GameFramework/Pawn.h"
#include "Engine/GameViewportClient.h"
#include "UMPI_ScreenIndicator_WidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class UNIVERSALMPINDICATOR_API UUMPI_ScreenIndicator_WidgetBase : public UUserWidget
{
	GENERATED_BODY()
	



public:





//------------------------------------------------------------  Meta Binded Values ------------------------------------------------------------


	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* FadeOut;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UMPI OnScreen Settings")
		UCanvasPanel* OnScr_Distance_Canvas;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UMPI OnScreen Settings")
		UTextBlock* OnScr_Distance_Text;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UMPI OnScreen Settings")
		UImage* OnScr_Texture;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UMPI OnScreen Settings")
		UVerticalBox* OnScrVertical_Box;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UMPI OFF_Screen Settings")
		UCanvasPanel* OffScr_Distance_Canvas;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UMPI OFF_Screen Settings")
		UTextBlock* OffScr_Distance_Text;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UMPI OFF_Screen Settings")
		UCanvasPanel* OffScr_Texture_Canvas;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "UMPI OFF_Screen Settings")
		UImage* OffScr_Texture;

//------------------------------------------------------------  Normal Created Values ------------------------------------------------------------



	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Indicator Data"), Category = "UMPI Calculation Settings")
		FUMPI_IndicatorSettings_Struct IndicatorData;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Indicator Data"), Category = "UMPI Settings")
		class UUMPI_ScreenIndicator_Component* Indicator_Component;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Indicator Data"), Category = "UMPI Settings")
		AActor* Target_Actor;

	UPROPERTY( BlueprintReadWrite, meta = (DisplayName = "Indicator Data"), Category = "UMPI Settings")
		FVector Target_Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI OnScreen Settings")
		FVector2D OnScreen_Scale_From_To_Effect = {5,5};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI OnScreen Settings")
		float OnScreen_FadeIn_Opacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI OnScreen Settings")
		bool ScaleFromToEffect_is_Done;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI Calculation Settings")
		bool Is_Target_Selected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI Calculation Settings")
		FVector2D Primary_Screen_Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI Calculation Settings")
		float Spawn_Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI Calculation Settings")
		float Degree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI Calculation Settings")
		bool On_Off_Screen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI Calculation Settings")
		FVector2D Center_Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI Calculation Settings")
		bool Indicator_Visibility_Bind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI Calculation Settings")
		float Edge_Interp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMPI Calculation Settings")
		float IndicatorTickFrequency = 0.05;



	FTimerHandle TickHandle;
	FTimerHandle DestroyTimerHandle;
	bool DoOnceOnScreenActivation;
	bool DoOnceOffScreenActivation;





//------------------------------------------------------------  Functions  ------------------------------------------------------------
	// Called on BeginPlay
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// Called every frame
	void CustomTickFunction();




	UFUNCTION(BlueprintCallable, Category = "UMPI Settings")
		void Custom_Remove_From_Parent();

	UFUNCTION(BlueprintCallable, Category = "UMPI Settings")
	    void Remove_Itself_from_Indicator_List();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMPI Settings")
		FText Bind_Distance_Text_Value();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMPI Settings")
		ESlateVisibility Bind_Distance_Text_Visibility();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMPI Settings")
		bool Check_Target_Is_In_Viewport();

	UFUNCTION(BlueprintCallable, Category = "UMPI Settings")
		void Take_Target_Location();

	UFUNCTION(BlueprintCallable, Category = "UMPI Settings")
		void Set_Indicator_Textures();

	UFUNCTION(BlueprintCallable, Category = "UMPI Settings")
		void Set_Pivot_Of_Indicators();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMPI Settings")
		ESlateVisibility Bind_Indicator_Visibility();

	UFUNCTION(BlueprintCallable, Category = "UMPI Settings")
		bool Check_Distance();





//------------------------------------------------------------  ON Screen Functions Down  ------------------------------------------------------------



	UFUNCTION(BlueprintCallable, Category = "UMPI OnScreen Settings")
		void Set_OnScreen_Position();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMPI OnScreen Settings")
		FVector2D OnScreen_Edge_Clamp(FVector2D enteredValue);

	UFUNCTION(BlueprintCallable, Category = "UMPI OnScreen Settings")
		void OnScreen_Scale_Swift();

	UFUNCTION(BlueprintCallable, Category = "UMPI OnScreen Settings")
		void Rotation_OnScreen_Effect();

	UFUNCTION(BlueprintCallable, Category = "UMPI OnScreen Settings")
		void FadeIn_OnScreen_Effect();

	UFUNCTION(BlueprintCallable, Category = "UMPI OnScreen Settings")
		void Pulse_OnScreen_Effect();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMPI OnScreen Settings")
	ESlateVisibility OnScrVerticalBoxVisibility();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMPI OnScreen Settings")
		FVector Calculate_Actor_Bound_Offset(FVector enteredVector);




//------------------------------ OFF Screen Functions Down --------------------------------------------------------------------------------------




	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMPI OFFScreen Settings")
		FVector2D OffScreen_Edge_Clamp(FVector2D entered2D_Size);

	UFUNCTION(BlueprintCallable, Category = "UMPI OFFScreen Settings")
		void Calculate_Off_Screen_Position(FVector2D& OffScreen_Position, float& Render_Angle);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMPI OFFScreen Settings")
		ESlateVisibility OFFScrVerticalBoxVisibility();

	UFUNCTION(BlueprintCallable, Category = "UMPI OFFScreen Settings")
		void OffScreen_Position_And_Angle();

	UFUNCTION(BlueprintCallable, Category = "UMPI OFFScreen Settings")
		void OffScr_Distance_TextF(float Current_Angle);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMPI OFFScreen Settings")
		void Find_Closest_Edge(float& angle);






	FVector2D Select2DVector(FVector2D enterVectorA, FVector2D enterVectorB, bool enterController);
	FVector2D Select2DVectorByIndicatorType(FVector2D clasic, FVector2D circle, UMPI_Indicator_Type_Enum_OP enterController);
	float SelectFloat(float enterFloatA, float enterFloatB, bool enterController);
	ESlateVisibility SelectVisibility(ESlateVisibility False, ESlateVisibility True, bool enterController);
	FVector SelectVector(FVector False, FVector True, bool enterController);
	float SelectRotationRule(float free, float closestEdge, float doNotRotate, UMPI_OffScreenRotationRule_Enum_OP enterController);





protected:







private:



	UPROPERTY(EditAnywhere, meta = (DisplayName = "Target ActorP"), Category = "UMPI Calculation Settings")
		AActor* Target_ActorP;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Target LocationP"), Category = "UMPI Calculation Settings")
		FVector Target_LocationP;



};
