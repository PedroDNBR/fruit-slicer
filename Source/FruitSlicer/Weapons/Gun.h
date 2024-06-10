// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class FRUITSLICER_API AGun : public AWeapon
{
	GENERATED_BODY()

public:
	void ShotgunTraceEndWithScatter(const FVector& HitTarget, TArray<FVector_NetQuantize>& HitTargets);
	UFUNCTION(BlueprintCallable)
	virtual void Fire();

protected:
	UPROPERTY(EditAnywhere, Category = "Gun Scatter")
	float DistanceToSphere = 800.f;
	UPROPERTY(EditAnywhere, Category = "Gun Scatter")
	float SphereRadius = 75.f;

	UPROPERTY(EditAnywhere, Category = "Gun Ammo")
	TSubclassOf<AActor> Projectile;

private:
	UPROPERTY(EditAnywhere, Category = "Gun Properties")
	class UAnimationAsset* FireAnimation;

	UPROPERTY(EditAnywhere, Category = "Gun Scatter")
	uint32 NumberOfPellets = 7;

	UPROPERTY(EditAnywhere, Category = "Gun Properties")
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Gun Properties")
	class USoundCue* FireSound;

};
