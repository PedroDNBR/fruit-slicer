// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cuttable.generated.h"

UCLASS()
class FRUITSLICER_API ACuttable : public AActor
{
	GENERATED_BODY()
	
public:	
	ACuttable();
	virtual void Tick(float DeltaTime) override;

	float InitialSpeedBase = 800.f;
	float InitialSpeedMax = 1100.f;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, 
		const FHitResult& Hit
	);

	void OnCollide(AActor* OtherActor);
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	class USoundCue* CutSound;

private:
	UPROPERTY(VisibleAnywhere, Category = "Properties")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<class AActor> CuttedMeshActor;


};
