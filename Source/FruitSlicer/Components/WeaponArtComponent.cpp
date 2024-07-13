#include "WeaponArtComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values for this component's properties
UWeaponArtComponent::UWeaponArtComponent()
{
}

void UWeaponArtComponent::BeginPlay()
{
	if (TrailAnim && Weapon && Weapon->GetMesh())
	{
		Weapon->GetMesh()->PlayAnimation(TrailAnim, true);
	}
}

void UWeaponArtComponent::CastSlashSpell()
{
	StartBaseSlashPosition = Weapon->GetActorLocation();
	StartTipSlashPosition = Weapon->GetMesh()->GetSocketLocation(FName("trailEnd"));
	StartSlashRotation = Weapon->GetActorRotation();
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(
			SlashSpellTimer,
			this,
			&UWeaponArtComponent::LaunchSlashSpell,
			CastTime
		);
	}
}

void UWeaponArtComponent::LaunchSlashSpell()
{
	UWorld* World = GetWorld();

	if (World && Projectile)
	{
		EndBaseSlashPosition = Weapon->GetActorLocation();
		EndTipSlashPosition = Weapon->GetMesh()->GetSocketLocation(FName("trailEnd"));

		EndSlashRotation = Weapon->GetActorRotation();

		const float LerpAlpha = 0.5f;

		FVector StartMiddleBaseSlashPosition = FMath::Lerp(StartBaseSlashPosition, EndBaseSlashPosition, LerpAlpha);
		FVector StartMiddleTipSlashPosition = FMath::Lerp(StartTipSlashPosition, EndTipSlashPosition, LerpAlpha);

		FQuat MiddleSlashRotation = FQuat::Slerp(StartSlashRotation.Quaternion(), EndSlashRotation.Quaternion(), LerpAlpha);

		FActorSpawnParameters SpawnParams;
		AActor* SpawnedProjectile = nullptr;

		// (StartMiddleTipSlashPosition - StartMiddleBaseSlashPosition).Rotation(),

		SpawnedProjectile = World->SpawnActor<AActor>(
			Projectile,
			StartMiddleBaseSlashPosition,
			MiddleSlashRotation.Rotator() + FRotator(90.f, 0.f, 0.f),
			SpawnParams
		);

		if (CastSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CastSound, StartMiddleTipSlashPosition);
		}
	}
}


