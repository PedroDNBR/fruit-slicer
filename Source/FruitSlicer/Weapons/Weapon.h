// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define TRACE_LENGTH 80000.f

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class FRUITSLICER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	bool bCanCut = true;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties", BlueprintReadWrite)
	class UWeaponArtComponent* WeaponArtComponent;

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	class USkeletalMeshComponent* SkeletalMesh;

public:
	UFUNCTION(BlueprintCallable) 
	USkeletalMeshComponent* GetMesh();
	FORCEINLINE void SetWeaponArtComponent(UWeaponArtComponent* WeaponArtComponentToSet) { WeaponArtComponent = WeaponArtComponentToSet; }
};	

