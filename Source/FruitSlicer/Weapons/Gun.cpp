// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h" 
#include "DrawDebugHelpers.h"

void AGun::ShotgunTraceEndWithScatter(const FVector& HitTarget, TArray<FVector_NetQuantize>& HitTargets)
{
	const USkeletalMeshSocket* MuzzleFlashSocket = GetMesh()->GetSocketByName("MuzzleFlash");
	if (MuzzleFlashSocket == nullptr) return;

	const FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetMesh());
	const FVector TraceStart = SocketTransform.GetLocation();

	const FVector ToTargetNormalized = (HitTarget - TraceStart).GetSafeNormal();
	const FVector SphereCenter = TraceStart + ToTargetNormalized * DistanceToSphere;

	for (uint32 i = 0; i < NumberOfPellets; i++)
	{
		const FVector RandVec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, SphereRadius);
		const FVector EndLoc = SphereCenter + RandVec;
		FVector ToEndLoc = EndLoc - TraceStart;
		ToEndLoc = TraceStart + ToEndLoc * TRACE_LENGTH / ToEndLoc.Size();

		HitTargets.Add(ToEndLoc);
	}
}

void AGun::Fire()
{
	const USkeletalMeshSocket* MuzzleFlashSocket = GetMesh()->GetSocketByName("MuzzleFlash");
	const USkeletalMeshSocket* MuzzleFlashEndSocket = GetMesh()->GetSocketByName("MuzzleFlashEnd");

	if (MuzzleFlashSocket && MuzzleFlashEndSocket)
	{
		const FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetMesh());
		const FTransform SocketEndTransform = MuzzleFlashEndSocket->GetSocketTransform(GetMesh());

		FVector Start = SocketTransform.GetLocation();

		FVector End = SocketEndTransform.GetLocation();

		if (FireAnimation)
		{
			GetMesh()->PlayAnimation(FireAnimation, false);
		}
		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				MuzzleFlash,
				SocketTransform
			);
		}
		if (FireSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				FireSound,
				Start
			);
		}

		TArray<FVector_NetQuantize> HitTargets;
		ShotgunTraceEndWithScatter(End, HitTargets);

		// Maps hit character to number of times hit
		for (FVector_NetQuantize HitTarget : HitTargets)
		{
			UWorld* World = GetWorld();

			if (MuzzleFlashSocket && World && Projectile)
			{
				// From muzzle flash socket to hit location from TraceUnderCrosshairs
				FVector ToTarget = HitTarget - SocketTransform.GetLocation();
				FRotator TargetRotation = ToTarget.Rotation();

				FActorSpawnParameters SpawnParams;

				AActor* SpawnedProjectile = nullptr;

				SpawnedProjectile = World->SpawnActor<AActor>(
					Projectile,
					SocketTransform.GetLocation(),
					TargetRotation,
					SpawnParams
				);
			}
		}
	}
}
