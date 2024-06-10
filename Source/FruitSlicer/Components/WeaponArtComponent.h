// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FruitSlicer/Weapons/Weapon.h"
#include "WeaponArtComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRUITSLICER_API UWeaponArtComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponArtComponent();
	friend class AWeapon;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class AWeapon* Weapon;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	class UAnimSequence* TrailAnim;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	class USoundCue* CastSound;

	UFUNCTION(BlueprintCallable)
	void CastSlashSpell();

	void LaunchSlashSpell();

	FTimerHandle SlashSpellTimer;

	FVector StartBaseSlashPosition;
	FVector EndBaseSlashPosition;

	FVector StartTipSlashPosition;
	FVector EndTipSlashPosition;

	UPROPERTY(EditAnywhere, Category = "Weapon Ammo")
	TSubclassOf<AActor> Projectile;

public:
	FORCEINLINE void SetWeapon(AWeapon* WeaponToSet) { Weapon = WeaponToSet; }

};
