// // Copyright UnexGames, 2023 All Rights Reserved.


#include "UMPI_ScreenIndicator_Component.h"
#include "Containers/Map.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"

// Sets default values for this component's properties
UUMPI_ScreenIndicator_Component::UUMPI_ScreenIndicator_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UUMPI_ScreenIndicator_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UUMPI_ScreenIndicator_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UUMPI_ScreenIndicator_Component::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	if (Clear_All_On_End_Play)
	{
		TArray<AActor*> Actor_Indicator_List_Keys;
		Actor_Indicator_List.GenerateKeyArray(Actor_Indicator_List_Keys);
		for (int i = 0; i < Actor_Indicator_List_Keys.Num(); i++)
		{
			if (IsValid(Actor_Indicator_List_Keys[i]))
			{
				if (Actor_Indicator_List.Find(Actor_Indicator_List_Keys[i]))
				{
					UUMPI_ScreenIndicator_WidgetBase* TempFindedWidgetActor = *Actor_Indicator_List.Find(Actor_Indicator_List_Keys[i]);
					Remove_Indicator(TempFindedWidgetActor, true, Actor_Indicator_List_Keys[i], Actor_Indicator_List_Keys[i]->GetActorLocation());
				}
			}
			else
			{
				TArray<FVector> Location_Indicator_List_Keys;
				Location_Indicator_List.GenerateKeyArray(Location_Indicator_List_Keys);

				for (int j = 0; j < Location_Indicator_List_Keys.Num(); j++)
				{
					if (Location_Indicator_List.Find(Location_Indicator_List_Keys[j]))
					{
						UUMPI_ScreenIndicator_WidgetBase* TempFindedWidgetLocation = *Location_Indicator_List.Find(Location_Indicator_List_Keys[j]);
						Remove_Indicator(TempFindedWidgetLocation, true, NULL, Location_Indicator_List_Keys[j]);
					}
				}
			}
		}

	}
	else
	{
		Actor_Indicator_List.Empty();
	}

}



void UUMPI_ScreenIndicator_Component::Spawn_Indicator()
{
	if (Indicator_Widget_ToSpawn != nullptr)
	{
		SpawnedIndicatorWidget = CreateWidget<UUMPI_ScreenIndicator_WidgetBase>(GetWorld(), Indicator_Widget_ToSpawn);
		if (IsValid(SpawnedIndicatorWidget))
		{
			SpawnedIndicatorWidget->IndicatorData = IndicatorData;
			SpawnedIndicatorWidget->Indicator_Component = this;
			if (Target_Actor != NULL)
			{
				SpawnedIndicatorWidget->Target_Actor = Target_Actor;
				SpawnedIndicatorWidget->Target_Location = Target_Location;
			}
			else
			{
				SpawnedIndicatorWidget->Target_Actor = NULL;
				SpawnedIndicatorWidget->Target_Location = Target_Location;
			}
		}

		SpawnedIndicatorWidget->AddToViewport(0);

		if (IsValid(Target_Actor))
		{
			Actor_Indicator_List.Add(Target_Actor, SpawnedIndicatorWidget);
		}
		else
		{
			Location_Indicator_List.Add(Target_Location, SpawnedIndicatorWidget);
		}
			

	}
}



bool UUMPI_ScreenIndicator_Component::Check_Actor_Is_Tracking(AActor* targetActor, FVector targetLocation)
{
	if (targetActor != NULL)
	{
		if(Actor_Indicator_List.Find(targetActor))
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
	else
	{

		if (Location_Indicator_List.Find(targetLocation))
		{
			return(false);
		}
		else
		{
			return(true);
		}

	}
}



void UUMPI_ScreenIndicator_Component::Remove_Indicator(UUMPI_ScreenIndicator_WidgetBase* indicatorWidgetRef, bool Immediately, AActor* targetActor, FVector targetLocation)
{
	if (indicatorWidgetRef == nullptr)
	{

		if (Actor_Indicator_List.Find(targetActor))
		{
			UUMPI_ScreenIndicator_WidgetBase* FindedWidget = *Actor_Indicator_List.Find(targetActor);
			FindedWidget->Custom_Remove_From_Parent();
			
		}
		else
		{
			if (Location_Indicator_List.Find(targetLocation))
			{
				UUMPI_ScreenIndicator_WidgetBase* FindedWidget_From_Location = *Location_Indicator_List.Find(targetLocation);
				FindedWidget_From_Location->Custom_Remove_From_Parent();
			}


		}
	}
	else
	{
		if (Immediately && IsValid(indicatorWidgetRef))
		{
			TArray<AActor*> Indicator_List_Keys;
			Actor_Indicator_List.GetKeys(Indicator_List_Keys);

			for (int i = 0; i < Indicator_List_Keys.Num(); i++)
			{
				if (*Actor_Indicator_List.Find(Indicator_List_Keys[i]) == indicatorWidgetRef)
				{
					UUMPI_ScreenIndicator_WidgetBase* Temp_Indicator_Adress = *Actor_Indicator_List.Find(Indicator_List_Keys[i]);
					Temp_Indicator_Adress->Custom_Remove_From_Parent();
					break;
				}
			}
		}
	}
}



void UUMPI_ScreenIndicator_Component::Create_Indicator(FUMPI_IndicatorSettings_Struct indicatorData, AActor* targetActor, FVector enteredLocation, UUMPI_ScreenIndicator_WidgetBase*& indicatorWidgetRef)
{
	if (UseDataTable)
	{

		if (DataTableToUse != nullptr)
		{
			TArray<FName>ScanDataTableArrows = DataTableToUse->GetRowNames();
			if (ScanDataTableArrows.Num() > DataTable_Row_Index)
			{

				if (DataTableToUse->GetRowStruct() == IndicatorData.StaticStruct())
				{

					FUMPI_IndicatorSettings_Struct* FindedDTSettings = DataTableToUse->FindRow<FUMPI_IndicatorSettings_Struct>(ScanDataTableArrows[DataTable_Row_Index], "");
					IndicatorData = *FindedDTSettings;
					SetOtherIndicatorSettings(targetActor, enteredLocation);
					indicatorWidgetRef = SpawnedIndicatorWidget;

				}
				else
				{
					IndicatorData = indicatorData;
					SetOtherIndicatorSettings(targetActor, enteredLocation);
					indicatorWidgetRef = SpawnedIndicatorWidget;
				}

			}
			else
			{
				IndicatorData = indicatorData;
				SetOtherIndicatorSettings(targetActor, enteredLocation);
				indicatorWidgetRef = SpawnedIndicatorWidget;
			}
		}
		else
		{
				IndicatorData = indicatorData;
				SetOtherIndicatorSettings(targetActor, enteredLocation);
				indicatorWidgetRef = SpawnedIndicatorWidget;
		}
	}
	else
	{
			IndicatorData = indicatorData;
			SetOtherIndicatorSettings(targetActor, enteredLocation);
			indicatorWidgetRef = SpawnedIndicatorWidget;
	}
}




void UUMPI_ScreenIndicator_Component::SetOtherIndicatorSettings(AActor* targetActor, FVector targetLocation)
{
	
	Target_Actor = targetActor;
	Target_Location = targetLocation;
	
	if (Check_Actor_Is_Tracking(Target_Actor, Target_Location))
	{
		Spawn_Indicator();
	}
	else
	{
		Remove_Indicator(SpawnedIndicatorWidget, false, Target_Actor, Target_Location);
	}
}





