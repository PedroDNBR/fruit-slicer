// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Launcher.generated.h"

UCLASS()
class FRUITSLICER_API ALauncher : public AActor
{
	GENERATED_BODY()
	
public:	
	ALauncher();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<AActor> Actor;

	UPROPERTY(EditAnywhere, Category = "Properties")
	class USoundCue* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Properties")
	int32 MinLauncherDelay = 1.f;

	UPROPERTY(EditAnywhere, Category = "Properties")
	int32 MaxLauncherDelay = 5.f;

private:
	virtual void LaunchActor();
	virtual void StartTimer();
	FTimerHandle LaunchTimer;



};
