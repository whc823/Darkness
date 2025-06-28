// // Copyright UnexGames, 2023 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UMPI_IndicatorSettings_Struct.h"
#include "Engine/DataTable.h"
#include "UMPI_ScreenIndicator_WidgetBase.h"
#include "UMPI_ScreenIndicator_Component.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetArrived);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNIVERSALMPINDICATOR_API UUMPI_ScreenIndicator_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUMPI_ScreenIndicator_Component();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (DisplayName = "Indicator Settings"), Category = "UMPI Settings")
		FUMPI_IndicatorSettings_Struct IndicatorSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UMPI DataTable")
		bool UseDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UMPI DataTable")
		bool Clear_All_On_End_Play = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = UseDataTable), Category = "UMPI DataTable")
		UDataTable* DataTableToUse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = UseDataTable), Category = "UMPI DataTable")
		int DataTable_Row_Index;

	UPROPERTY(BlueprintReadOnly, Category = "UMPI Settings")
		TMap<AActor*, UUMPI_ScreenIndicator_WidgetBase*> Actor_Indicator_List;

	UPROPERTY(BlueprintReadOnly, Category = "UMPI Settings")
		TMap<FVector, UUMPI_ScreenIndicator_WidgetBase*> Location_Indicator_List;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Indicator Widget"), Category = "UMPI Settings")
		TSubclassOf<UUMPI_ScreenIndicator_WidgetBase> Indicator_Widget_ToSpawn;




//-------------------------------------------------------------------------------------------------------------------------------------------------------------------



	UFUNCTION(BlueprintCallable, Category = "UMPI Settings", DisplayName = "Check Actor Is Already Tracking?")
		bool Check_Actor_Is_Tracking(AActor* targetActor, FVector targetLocation);

	UFUNCTION(BlueprintCallable, Category = "UMPI Settings", DisplayName = "Remove Indicator")
		void Remove_Indicator(UUMPI_ScreenIndicator_WidgetBase* indicatorWidgetRef, bool Immediately, AActor* targetActor, FVector targetLocation);

	UFUNCTION(BlueprintCallable, Category = "UMPI Settings", DisplayName = "Create Indicator")
		void Create_Indicator(FUMPI_IndicatorSettings_Struct indicatorData, AActor* targetActor, FVector enteredLocation, UUMPI_ScreenIndicator_WidgetBase*& indicatorWidgetRef);






//------------------------------------------------------------------  DELEGATE  -----------------------------------------------------------------------------------


	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BindableEvents")
	FOnTargetArrived OnTargetArrivedNative;


//------------------------------------------------------------------  DELEGATE  -----------------------------------------------------------------------------------




protected:
	// Called when the game starts
	virtual void BeginPlay() override;







private:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when component destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


		
	UPROPERTY()
		FUMPI_IndicatorSettings_Struct IndicatorData;


	UPROPERTY()
		UUMPI_ScreenIndicator_WidgetBase* SpawnedIndicatorWidget;

	UPROPERTY()
		AActor* Target_Actor;

	UPROPERTY()
		FVector Target_Location;

	void SetOtherIndicatorSettings(AActor* targetActor, FVector targetLocation);



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------



	UFUNCTION(BlueprintCallable, Category = "UMPI Settings", DisplayName = "Spawn Indicator")
		void Spawn_Indicator();










};
