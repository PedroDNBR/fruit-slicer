// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALauncher::ALauncher()
{

}

// Called when the game starts or when spawned
void ALauncher::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	StartTimer();
}

void ALauncher::LaunchActor()
{
	UWorld* World = GetWorld();
	if (Actor != nullptr && World)
	{
		FActorSpawnParameters SpawnParams;
		World->SpawnActor<AActor>(
			Actor,
			GetTransform(),
			SpawnParams
		);

		StartTimer();
	}
}

void ALauncher::StartTimer()
{
	GetWorldTimerManager().SetTimer(
		LaunchTimer,
		this,
		&ALauncher::LaunchActor,
		UKismetMathLibrary::RandomFloatInRange(1.f, 5.f)
	);
}


