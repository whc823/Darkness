// // Copyright UnexGames, 2023 All Rights Reserved.


#include "UMPI_ScreenIndicator_WidgetBase.h"
#include "Math/Vector2D.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Styling/SlateColor.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "TimerManager.h"
#include "UMPI_ScreenIndicator_Component.h"
#include "Kismet/KismetStringLibrary.h"




//    EventConstruct   

void UUMPI_ScreenIndicator_WidgetBase::NativeConstruct()
{


	Spawn_Time = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	Set_Indicator_Textures();
	Set_Pivot_Of_Indicators();
	OffScreen_Position_And_Angle();
	OnScreen_Scale_From_To_Effect = IndicatorData.EffectSettings.OnScreenScaleSwift.Init_Scale;
	OnScrVertical_Box->ForceLayoutPrepass();
	OffScr_Texture_Canvas->ForceLayoutPrepass();


	GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &UUMPI_ScreenIndicator_WidgetBase::CustomTickFunction, IndicatorTickFrequency, true);



	if (IndicatorData.Life_Time > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &UUMPI_ScreenIndicator_WidgetBase::Custom_Remove_From_Parent, IndicatorData.Life_Time, false);
	}

}




void UUMPI_ScreenIndicator_WidgetBase::CustomTickFunction()
{

	Take_Target_Location();
	
		if (Check_Distance())
		{

			if (Check_Target_Is_In_Viewport())
			{

				Set_OnScreen_Position();
				if (DoOnceOnScreenActivation == false)
				{
					On_Off_Screen = true;
					DoOnceOnScreenActivation = true;
					DoOnceOffScreenActivation = false;
				}
				FadeIn_OnScreen_Effect();
				OnScreen_Scale_Swift();
				Rotation_OnScreen_Effect();
				Pulse_OnScreen_Effect();
			}
			else
			{

				OffScreen_Position_And_Angle();
				if (DoOnceOffScreenActivation == false)
				{
					On_Off_Screen = false;
					DoOnceOffScreenActivation = true;
					DoOnceOnScreenActivation = false;

					OnScreen_Scale_From_To_Effect = Select2DVector(IndicatorData.EffectSettings.OnScreenScaleSwift.Init_Scale, { 1,1 }, IndicatorData.EffectSettings.OnScreenScaleSwift.Do_Once);
					OnScreen_FadeIn_Opacity = SelectFloat(0, 1, IndicatorData.EffectSettings.OnScreenOpacity.Do_Once);
					ScaleFromToEffect_is_Done = false;

				}

			}
		}
	
}





void UUMPI_ScreenIndicator_WidgetBase::NativeDestruct()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TickHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(TickHandle);
	}
}







void UUMPI_ScreenIndicator_WidgetBase::Custom_Remove_From_Parent()
{
	float animation_Time = FadeOut->GetEndTime();
	this->PlayAnimationForward(FadeOut);
	Remove_Itself_from_Indicator_List();
}

void UUMPI_ScreenIndicator_WidgetBase::Remove_Itself_from_Indicator_List()
{
	if (IsValid(Target_ActorP))
	{
		if (IsValid(Indicator_Component))
		{
			Indicator_Component->Actor_Indicator_List.Remove(Target_Actor);
			this->RemoveFromParent();
		}
		else
		{
			this->RemoveFromParent();
		}
	}
	else
	{
		if (IsValid(Indicator_Component))
		{
			Indicator_Component->Location_Indicator_List.Remove(Target_Location);
			this->RemoveFromParent();
		}
		else
		{
			this->RemoveFromParent();
		}
		
	}
}

void UUMPI_ScreenIndicator_WidgetBase::Set_OnScreen_Position()
{
	APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(),0);

	PlayerControllerRef->ProjectWorldLocationToScreen(Target_LocationP, Primary_Screen_Position, true);

	UCanvasPanelSlot* GettedOn_Scr_Vertical_Box_CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(OnScrVertical_Box);
	GettedOn_Scr_Vertical_Box_CanvasSlot->SetPosition(OnScreen_Edge_Clamp(Primary_Screen_Position));    

}


FVector2D UUMPI_ScreenIndicator_WidgetBase::OnScreen_Edge_Clamp(FVector2D enteredValue)
{
	FVector2D ResultVector;


	FVector2D VectorA = (OnScrVertical_Box->GetDesiredSize() * UWidgetLayoutLibrary::GetViewportScale(GetWorld())) / 2;

	FVector2D VectorB = { VectorA.X, ((VectorA * 2) * OnScrVertical_Box->GetRenderTransformPivot()).Y};

	FVector2D SelectedVector = Select2DVector(VectorA, VectorB, IndicatorData.Use_Z_Offset);
	FVector2D Pre_CalculatedVector = SelectedVector + IndicatorData.OffScreen_Texture_Settings.Screen_Margin;

	FVector2D ViewPortSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());


	ResultVector = { (FMath::Clamp(enteredValue.X, Pre_CalculatedVector.X, ViewPortSize.X - Pre_CalculatedVector.X)),
					 (FMath::Clamp(enteredValue.Y, (IndicatorData.OffScreen_Texture_Settings.Screen_Margin) + ((OnScrVertical_Box->GetDesiredSize() * OnScrVertical_Box->GetRenderTransformPivot()) * (UWidgetLayoutLibrary::GetViewportScale(GetWorld()))).Y ,
											 SelectFloat((ViewPortSize.Y - Pre_CalculatedVector.Y), ((ViewPortSize.Y - Pre_CalculatedVector.Y) + ((VectorA * 2) * OnScrVertical_Box->GetRenderTransformPivot()).Y), IndicatorData.Use_Z_Offset))) };

	ResultVector =  ResultVector / UWidgetLayoutLibrary::GetViewportScale(GetWorld());
		
	return(ResultVector);

}




FVector2D UUMPI_ScreenIndicator_WidgetBase::Select2DVector(FVector2D enterVectorA, FVector2D enterVectorB, bool enterController)
{
	if (enterController)
	{
		return(enterVectorB);
	}
	else
	{
		return(enterVectorA);
	}
}



FVector2D UUMPI_ScreenIndicator_WidgetBase::Select2DVectorByIndicatorType(FVector2D clasic, FVector2D circle, UMPI_Indicator_Type_Enum_OP enterController)
{
	switch (enterController)
	{
	case OP_Classic:
		return(clasic);
		break;
	case OP_Circle:
		return(circle);
		break;
	default:
		return(clasic);
		break;
	}
}




float UUMPI_ScreenIndicator_WidgetBase::SelectFloat(float enterFloatA, float enterFloatB, bool enterController)
{
	if (enterController)
	{
		return(enterFloatB);
	}
	else
	{
		return(enterFloatA);
	}
}


ESlateVisibility UUMPI_ScreenIndicator_WidgetBase::SelectVisibility(ESlateVisibility False, ESlateVisibility True, bool enterController)
{
	if (enterController)
	{
		return(True);
	}
	else
	{
		return(False);
	}
}


FVector UUMPI_ScreenIndicator_WidgetBase::SelectVector(FVector False, FVector True, bool enterController)
{
	if (enterController)
	{
		return(True);
	}
	else
	{
		return(False);
	}
}




float UUMPI_ScreenIndicator_WidgetBase::SelectRotationRule(float free, float closestEdge, float doNotRotate, UMPI_OffScreenRotationRule_Enum_OP enterController)
{
	switch (enterController)
	{
	case OP_Free:
		return(free);
		break;
	case OP_Closest_Edge:
		return(closestEdge);
		break;
	case OP_Do_Not_Rotate:
		return(doNotRotate);
		break;
	default:
		return(free);
		break;
	}
}




void UUMPI_ScreenIndicator_WidgetBase::OnScreen_Scale_Swift()
{
	if (IndicatorData.EffectSettings.OnScreenScaleSwift.Use)
	{
		OnScreen_Scale_From_To_Effect = UKismetMathLibrary::Vector2DInterpTo(OnScreen_Scale_From_To_Effect, FVector2D{1, 1}, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), IndicatorData.EffectSettings.OnScreenScaleSwift.Speed);
		OnScrVertical_Box->SetRenderScale(OnScreen_Scale_From_To_Effect);
		if (OnScreen_Scale_From_To_Effect == FVector2D{1, 1})
		{
			ScaleFromToEffect_is_Done = true;
		}
		else
		{
			ScaleFromToEffect_is_Done = false;
		}
	}
	else
	{
		OnScreen_Scale_From_To_Effect = { 1,1 };
		ScaleFromToEffect_is_Done = true;
	}
}



void UUMPI_ScreenIndicator_WidgetBase::Rotation_OnScreen_Effect()
{
	if (IndicatorData.EffectSettings.OnScreen_Rotation.Use)
	{
		OnScr_Texture->SetRenderTransformAngle(OnScr_Texture->GetRenderTransformAngle() + IndicatorData.EffectSettings.OnScreen_Rotation.Rotation_Rate);
	}
}




void UUMPI_ScreenIndicator_WidgetBase::FadeIn_OnScreen_Effect()
{
	if (IndicatorData.EffectSettings.OnScreenOpacity.Use)
	{
		OnScreen_FadeIn_Opacity = UKismetMathLibrary::FInterpTo(OnScreen_FadeIn_Opacity, 1, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), IndicatorData.EffectSettings.OnScreenOpacity.Speed);
		OnScrVertical_Box->SetRenderOpacity(OnScreen_FadeIn_Opacity);
	}
}



void UUMPI_ScreenIndicator_WidgetBase::Pulse_OnScreen_Effect()
{
	if (ScaleFromToEffect_is_Done && IndicatorData.EffectSettings.OnScreenPulse.Use)
	{
		float GameTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
		float OneMinus = -1;

		float Alfa = ((-1 * (cos((GameTime - Spawn_Time) * IndicatorData.EffectSettings.OnScreenPulse.Speed))) + 1) / 2 ;
		float RenderScale = UKismetMathLibrary::Lerp(1, IndicatorData.EffectSettings.OnScreenPulse.Pulse_Scale_Limit, Alfa);

		OnScrVertical_Box->SetRenderScale({ RenderScale, RenderScale });

	}
	else
	{
		Spawn_Time = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	}
}




ESlateVisibility UUMPI_ScreenIndicator_WidgetBase::OnScrVerticalBoxVisibility()
{
	if (IsValid(IndicatorData.OnScreen_Texture_Settings.Screen_Texture) || IsValid(IndicatorData.OnScreen_Texture_Settings.Material_Image) )
	{
		return(SelectVisibility(ESlateVisibility::Collapsed, ESlateVisibility::HitTestInvisible, On_Off_Screen));
	}
	else
	{
		return(ESlateVisibility::Collapsed);
	}
}




FVector UUMPI_ScreenIndicator_WidgetBase::Calculate_Actor_Bound_Offset(FVector enteredVector)
{
	FVector FalseVector = enteredVector;

	FVector OriginVector;
	FVector ExtendVector;
	Target_ActorP->GetActorBounds(true, OriginVector, ExtendVector, false);

	FVector TrueVector = enteredVector + FVector{ 0, 0,IndicatorData.Additional_Z_Offsett } + FVector{ 0, 0, ExtendVector.Z };

	FVector Actor_Vector_Result = SelectVector(FalseVector, TrueVector, IndicatorData.Use_Z_Offset);

	return(Actor_Vector_Result);

}




FVector2D UUMPI_ScreenIndicator_WidgetBase::OffScreen_Edge_Clamp(FVector2D entered2D_Size)
{
	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
	float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());

	bool MinXController = (OffScr_Distance_Text->GetDesiredSize().X > OffScr_Texture->GetDesiredSize().X);

	float DoNotRotateValueX = SelectFloat(OffScr_Texture->GetDesiredSize().X, OffScr_Distance_Text->GetDesiredSize().X, MinXController) * ViewportScale;
	
	float aditionSumX = SelectRotationRule(0.f, 0.f, DoNotRotateValueX, IndicatorData.EffectSettings.Off_Rotation_Rule);

	float MinX = IndicatorData.OffScreen_Texture_Settings.Screen_Margin + aditionSumX;

	float MaxX = ViewportSize.X - MinX;



	float DoNotRotateValueY = SelectRotationRule(0.f, 0.f, (OffScr_Texture->GetDesiredSize().Y + SelectFloat(OffScr_Distance_Text->GetDesiredSize().Y, 0.f, IndicatorData.EffectSettings.Distance_Text.Show_Distance_Text)) * 
		                                                                     ViewportScale, IndicatorData.EffectSettings.Off_Rotation_Rule);

	float aditionSumY = IndicatorData.OffScreen_Texture_Settings.Screen_Margin;

	float MinY = DoNotRotateValueY + aditionSumY;

    float MaxY = ViewportSize.Y - aditionSumY;



    float ClampedX = FMath::Clamp<float>(entered2D_Size.X, MinX, MaxX);

	float ClampedY = FMath::Clamp<float>(entered2D_Size.Y, MinY, MaxY);




	FVector2D ClampedVectorResult = UKismetMathLibrary::MakeVector2D( ClampedX, ClampedY );

	FVector2D ResultVector = ClampedVectorResult / ViewportScale;


	return(ResultVector);
}





void UUMPI_ScreenIndicator_WidgetBase::Calculate_Off_Screen_Position(FVector2D& OffScreen_Position, float& Render_Angle)
{
	APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
    float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld()->GetGameViewport());


	FVector2D TopCenterX = { (ViewportSize/2).X, 0.f};
	FVector2D BottomCenterX = { (ViewportSize / 2).X, ViewportSize.Y};
	FVector2D CenterOfScreen = ViewportSize / 2;



	FVector WorldLocation;
	FVector WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(PlayerControllerRef, CenterOfScreen, WorldLocation, WorldDirection);

	FVector WorldLocationSum = WorldLocation + (UKismetMathLibrary::GetForwardVector((UKismetMathLibrary::FindLookAtRotation(WorldLocation, Target_LocationP))));
	

	FVector2D Reference_Point;
	UGameplayStatics::ProjectWorldToScreen(PlayerControllerRef, WorldLocationSum, Reference_Point, true);


	FVector2D PointDiference = CenterOfScreen - Reference_Point;
	Degree = 180.f - UKismetMathLibrary::DegAtan2(PointDiference.X, PointDiference.Y);

    FVector2D CenterDirection = UKismetMathLibrary::Conv_VectorToVector2D(UKismetMathLibrary::GetForwardVector((UKismetMathLibrary::FindLookAtRotation(UKismetMathLibrary::Conv_Vector2DToVector(CenterOfScreen, 0.f), UKismetMathLibrary::Conv_Vector2DToVector(Reference_Point, 0.f)))));
	Center_Direction = CenterDirection;



	float ClampMax = (ViewportSize - CenterOfScreen).Size();
	float XRotatorCurrentA = FMath::Clamp<float>(UKismetMathLibrary::CrossProduct2D((TopCenterX - CenterOfScreen), FVector2D{1,0}) * 2, 0.f, ClampMax);
	float XRotatorCurrentB = FMath::Clamp<float>(UKismetMathLibrary::CrossProduct2D((BottomCenterX - CenterOfScreen), FVector2D{ 1,0 }) * 2, 0.f, ClampMax);
	float XMax = UKismetMathLibrary::FMax(XRotatorCurrentA, XRotatorCurrentB);

	FVector RotatedVectorA = UKismetMathLibrary::GreaterGreater_VectorRotator(FVector{ XMax, 0, 0 }, FRotator{ 0, Degree + 90, 0 });
	FVector2D ConvertedVectorLocA = { RotatedVectorA.X, RotatedVectorA.Y};

	FVector RotatedVectorB = UKismetMathLibrary::GreaterGreater_VectorRotator(FVector{ IndicatorData.Indicator_Type.Circle_Radius, 0, 0 }, FRotator{ 0, Degree + 90, 0 });
	FVector2D ConvertedVectorLocB = { RotatedVectorB.X, RotatedVectorB.Y };




	FVector2D ResultLocation = OffScreen_Edge_Clamp( CenterOfScreen + (Select2DVectorByIndicatorType(ConvertedVectorLocA, ConvertedVectorLocB, IndicatorData.Indicator_Type.Indicator_Type)) );
	OffScreen_Position = ResultLocation;
	Render_Angle = Degree;


}





ESlateVisibility UUMPI_ScreenIndicator_WidgetBase::OFFScrVerticalBoxVisibility()
{
	if (IsValid(IndicatorData.OffScreen_Texture_Settings.Screen_Texture) || IsValid(IndicatorData.OffScreen_Texture_Settings.Material_Image))
	{
		return(SelectVisibility(ESlateVisibility::SelfHitTestInvisible, ESlateVisibility::Collapsed, On_Off_Screen));
	}
	else
	{
		return(ESlateVisibility::Collapsed);
	}
}





void UUMPI_ScreenIndicator_WidgetBase::OffScreen_Position_And_Angle()
{
	FVector2D CalculatedScreenPosition;
	float CalculatedAngle;
	float NearestAngle;
	Find_Closest_Edge(NearestAngle);
	Calculate_Off_Screen_Position(CalculatedScreenPosition, CalculatedAngle);
	float CurrentAngle = SelectRotationRule(CalculatedAngle, NearestAngle, 0, IndicatorData.EffectSettings.Off_Rotation_Rule);
	UCanvasPanelSlot* Off_ScreenTexture_CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(OffScr_Texture_Canvas);
	Off_ScreenTexture_CanvasSlot->SetPosition(CalculatedScreenPosition);
	OffScr_Texture_Canvas->SetRenderTransformAngle(SelectRotationRule(CalculatedAngle, NearestAngle, 0, IndicatorData.EffectSettings.Off_Rotation_Rule));
	OffScr_Distance_TextF(SelectRotationRule(CalculatedAngle, NearestAngle, 0, IndicatorData.EffectSettings.Off_Rotation_Rule));
}




void UUMPI_ScreenIndicator_WidgetBase::Find_Closest_Edge(float& angle)
{

	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());


	FVector2D LeftBottomVector = (ViewportSize / 2) - FVector2D{ 0, ViewportSize.Y };
	float LeftBottomMin = ((UKismetMathLibrary::DegAtan2(LeftBottomVector.X, LeftBottomVector.Y)) * (-1)) + 180;


	FVector2D LeftTopVector = (ViewportSize / 2) - FVector2D{ 0, 0 };
	float LeftTopMin = ((UKismetMathLibrary::DegAtan2(LeftTopVector.X, LeftTopVector.Y)) * (-1)) + 180;


	FVector2D RightTopVector = (ViewportSize / 2) - FVector2D{ ViewportSize.X, 0 };
	float RightTopMin = ((UKismetMathLibrary::DegAtan2(RightTopVector.X, RightTopVector.Y)) * (-1)) + 180;


	FVector2D RightBottomVector = (ViewportSize / 2) - ViewportSize;
	float RightBottomMin = ((UKismetMathLibrary::DegAtan2(RightBottomVector.X, RightBottomVector.Y)) * (-1)) + 180;



	bool InRangeLeft = UKismetMathLibrary::InRange_FloatFloat(Degree, LeftBottomMin, LeftTopMin, true, false);
	bool InRangeTop = UKismetMathLibrary::InRange_FloatFloat(Degree, LeftTopMin, RightTopMin, true, false);
	bool InRangeRight = UKismetMathLibrary::InRange_FloatFloat(Degree, RightTopMin, RightBottomMin, true, false);


	FRotator CurrentRotation = {0, Edge_Interp, 0};
	FRotator TargetRotation = {0, SelectFloat(SelectFloat(SelectFloat(0, 270, InRangeRight), 180, InRangeTop), 90, InRangeLeft), 0};
	FRotator RotationResult = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 25);



	Edge_Interp = RotationResult.Yaw;
	angle = Edge_Interp;

}



void UUMPI_ScreenIndicator_WidgetBase::OffScr_Distance_TextF(float Current_Angle)
{
	if (IndicatorData.EffectSettings.Distance_Text.Show_Distance_Text)
	{
		FVector2D ResultSize;
		OffScr_Distance_Text->SetRenderTransformAngle(Current_Angle * -1);
		UCanvasPanelSlot* OffScr_Distance_Canvas_Slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(OffScr_Distance_Canvas);

		float OffScr_Distance_TextSize = (OffScr_Distance_Text->GetDesiredSize().Y) / 2;
		FVector2D OffScr_Texture_SizeA = OffScr_Texture->GetDesiredSize();

		float Free_ClosestEdgeB = UKismetMathLibrary::Lerp(1, 2, UKismetMathLibrary::Abs(UKismetMathLibrary::DotProduct2D({ 1, 0 }, Center_Direction))) * OffScr_Distance_TextSize;
		FVector2D OffScr_Texture_SizeB = { 0, SelectRotationRule(Free_ClosestEdgeB, Free_ClosestEdgeB, OffScr_Distance_TextSize, IndicatorData.EffectSettings.Off_Rotation_Rule) };

		float Free_ClosestEdgeC = ((FMath::Sqrt(FMath::Square(OffScr_Distance_Text->GetDesiredSize().X) + FMath::Square(OffScr_Distance_Text->GetDesiredSize().Y)) - OffScr_Distance_Text->GetDesiredSize().Y) / 2) * 1;
        FVector2D OffScr_Texture_SizeC = { 0,SelectRotationRule(Free_ClosestEdgeC, Free_ClosestEdgeC, 0, IndicatorData.EffectSettings.Off_Rotation_Rule) };



		ResultSize = OffScr_Texture_SizeA + OffScr_Texture_SizeB + OffScr_Texture_SizeC;
		OffScr_Distance_Canvas_Slot->SetSize(ResultSize);

	}
}



FText UUMPI_ScreenIndicator_WidgetBase::Bind_Distance_Text_Value()
{
	APlayerController * PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APawn* PlayerPawnRef = PlayerControllerRef->GetPawn();

	if (PlayerPawnRef != nullptr)
	{
		float Distance_Modificator = 100;
		FString Indicator_Unit = "m";

		if (IsValid(Indicator_Component) && Indicator_Component->IndicatorSettings.Use_Distance_Modificator)
		{
			Distance_Modificator = Indicator_Component->IndicatorSettings.Distance_Modification_Value;
			Indicator_Unit = Indicator_Component->IndicatorSettings.Distance_Unit_Indicator;
			FText TextResult = FText::FromString((FString::FromInt(UKismetMathLibrary::Round((PlayerPawnRef->GetActorLocation() - Target_LocationP).Size() / Distance_Modificator))) + Indicator_Unit);
			return(TextResult);

		}
		else
		{
			FText TextResult = FText::FromString((FString::FromInt(UKismetMathLibrary::Round((PlayerPawnRef->GetActorLocation() - Target_LocationP).Size() / 100))) + "m");
			return(TextResult);

		}
	}
	else
	{

		return(FText::FromString(""));

	}
}




ESlateVisibility UUMPI_ScreenIndicator_WidgetBase::Bind_Distance_Text_Visibility()
{
	ESlateVisibility ResultVisibility = SelectVisibility(ESlateVisibility::Collapsed, ESlateVisibility::Visible, IndicatorData.EffectSettings.Distance_Text.Show_Distance_Text);
	return(ResultVisibility);
}




bool UUMPI_ScreenIndicator_WidgetBase::Check_Target_Is_In_Viewport()
{
	APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FVector2D ViewportSize;
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
	float ViewPortScale = GetWorld()->GetGameViewport()->GetDPIScale();


	FVector2D ScreenLocation;
	bool ConditionA;
	bool ConditionB;
	
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PlayerControllerRef, Target_LocationP, ScreenLocation, false);

		ConditionA = UKismetMathLibrary::InRange_FloatFloat(ScreenLocation.X, 0.f, ViewportSize.X * 2, false, false);
		ConditionB = UKismetMathLibrary::InRange_FloatFloat(ScreenLocation.Y, 0.f, ViewportSize.Y, false, false);

		return(ConditionA && ConditionB);

}





void UUMPI_ScreenIndicator_WidgetBase::Take_Target_Location()
{
	if (Target_Actor != NULL)
	{

		Target_ActorP = Target_Actor;
		Target_LocationP = Calculate_Actor_Bound_Offset(Target_ActorP->GetActorLocation());

	}
	else
	{
		Target_LocationP = Target_Location;
	}
}



void UUMPI_ScreenIndicator_WidgetBase::Set_Indicator_Textures()
{


	FMargin BrushMargin = { 0,0,0,0 };
	FSlateBrush OnSlateBrush;
	OnSlateBrush.DrawAs = ESlateBrushDrawType::Image,
		OnSlateBrush.ImageSize = IndicatorData.OnScreen_Texture_Settings.Screen_Indicator_Size,
		OnSlateBrush.ImageType = ESlateBrushImageType::FullColor,
		OnSlateBrush.Margin = BrushMargin,
		OnSlateBrush.Mirroring = ESlateBrushMirrorType::NoMirror,
		OnSlateBrush.Tiling = ESlateBrushTileType::NoTile,
		OnSlateBrush.TintColor = IndicatorData.OnScreen_Texture_Settings.Tint_Color,
		OnSlateBrush.SetResourceObject(IndicatorData.OnScreen_Texture_Settings.Material_Image);


	FSlateBrush OffSlateBrush;
	OffSlateBrush.DrawAs = ESlateBrushDrawType::Image,
		OffSlateBrush.ImageSize = IndicatorData.OffScreen_Texture_Settings.Screen_Indicator_Size,
		OffSlateBrush.ImageType = ESlateBrushImageType::FullColor,
		OffSlateBrush.Margin = BrushMargin,
		OffSlateBrush.Mirroring = ESlateBrushMirrorType::NoMirror,
		OffSlateBrush.Tiling = ESlateBrushTileType::NoTile,
		OffSlateBrush.TintColor = IndicatorData.OffScreen_Texture_Settings.Tint_Color,
		OffSlateBrush.SetResourceObject(IndicatorData.OffScreen_Texture_Settings.Material_Image);




	if (IndicatorData.OnScreen_Texture_Settings.Use_Material_Image && IndicatorData.OnScreen_Texture_Settings.Material_Image != nullptr)
	{
		OnSlateBrush.SetResourceObject(IndicatorData.OnScreen_Texture_Settings.Material_Image);
		OnScr_Texture->SetBrush(OnSlateBrush);

		if (IndicatorData.OffScreen_Texture_Settings.Use_Material_Image && IndicatorData.OffScreen_Texture_Settings.Material_Image != nullptr)
		{
			OffSlateBrush.SetResourceObject(IndicatorData.OffScreen_Texture_Settings.Material_Image);
			OffScr_Texture->SetBrush(OffSlateBrush);
		}
		else
		{
			OffSlateBrush.SetResourceObject(IndicatorData.OffScreen_Texture_Settings.Screen_Texture);
			OffScr_Texture->SetBrush(OffSlateBrush);
		}

	}
	else
	{
		OnSlateBrush.SetResourceObject(IndicatorData.OnScreen_Texture_Settings.Screen_Texture);
		OnScr_Texture->SetBrush(OnSlateBrush);

		if (IndicatorData.OffScreen_Texture_Settings.Use_Material_Image && IndicatorData.OffScreen_Texture_Settings.Material_Image != nullptr)
		{
			OffSlateBrush.SetResourceObject(IndicatorData.OffScreen_Texture_Settings.Material_Image);
			OffScr_Texture->SetBrush(OffSlateBrush);
		}
		else
		{
			OffSlateBrush.SetResourceObject(IndicatorData.OffScreen_Texture_Settings.Screen_Texture);
			OffScr_Texture->SetBrush(OffSlateBrush);
		}
	}
}






void UUMPI_ScreenIndicator_WidgetBase::Set_Pivot_Of_Indicators()
{
	
	OnScrVertical_Box->SetRenderTransformPivot(IndicatorData.OnScreen_Texture_Settings.Screen_Indicator_Pivot);
	UCanvasPanelSlot* OnScrVertical_Box_Canvas_Slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(OnScrVertical_Box);
	OnScrVertical_Box_Canvas_Slot->SetAlignment(IndicatorData.OnScreen_Texture_Settings.Screen_Indicator_Pivot);


	OffScr_Texture_Canvas->SetRenderTransformPivot({ 0.5, 1 });
	UCanvasPanelSlot* OffScr_Texture_Canvas_Canvas_Slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(OffScr_Texture_Canvas);
	OffScr_Texture_Canvas_Canvas_Slot->SetAlignment({ 0.5, 1 });


	OffScr_Distance_Text->SetFont(IndicatorData.EffectSettings.Distance_Text.Font_Settings);
	OnScr_Distance_Text->SetFont(IndicatorData.EffectSettings.Distance_Text.Font_Settings);


	OffScr_Distance_Text->SetColorAndOpacity(IndicatorData.EffectSettings.Distance_Text.Text_Color);
	OnScr_Distance_Text-> SetColorAndOpacity(IndicatorData.EffectSettings.Distance_Text.Text_Color);

}




ESlateVisibility UUMPI_ScreenIndicator_WidgetBase::Bind_Indicator_Visibility()
{
	ESlateVisibility VisibilityResult = SelectVisibility(ESlateVisibility::Collapsed, ESlateVisibility::SelfHitTestInvisible, Indicator_Visibility_Bind);
	return(VisibilityResult);
}



bool UUMPI_ScreenIndicator_WidgetBase::Check_Distance()
{
	APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (PlayerControllerRef != nullptr)
	{

		APawn* PlayerPawnRef = PlayerControllerRef->GetPawn();

		bool Visible_Or_Not_Bind = ((PlayerPawnRef->GetActorLocation() - Target_LocationP).Size() > IndicatorData.Distance_Based_Visibility) && (IndicatorData.Distance_Based_Visibility > 0);

		if (PlayerPawnRef != nullptr)
		{
			if (IndicatorData.Arrive_Function)
			{
				if ((PlayerPawnRef->GetActorLocation() - Target_LocationP).Size() <= IndicatorData.Distance_For_Arrive_Units)
				{
					if (IsValid(Indicator_Component))
					{
						Indicator_Component->OnTargetArrivedNative.Broadcast();
						Indicator_Visibility_Bind = false;
						Custom_Remove_From_Parent();
						return(false);
					}
					Indicator_Visibility_Bind = false;
					return(false);
				}
				else
				{
					if (Visible_Or_Not_Bind)
					{
						Indicator_Visibility_Bind = false;
						return(false);
					}
					else
					{
						Indicator_Visibility_Bind = true;
						return(true);
					}
				}
			}
			else
			{
				if (Visible_Or_Not_Bind)
				{
					Indicator_Visibility_Bind = false;
					return(false);
				}
				else
				{
					Indicator_Visibility_Bind = true;
					return(true);
				}
			}
		}
		else
		{
			Indicator_Visibility_Bind = false;
			return(false);
		}

	}
	else
	{
		Indicator_Visibility_Bind = false;
		return(false);
	}
}