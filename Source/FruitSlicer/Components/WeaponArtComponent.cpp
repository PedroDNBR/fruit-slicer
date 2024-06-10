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
	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(
		SlashSpellTimer,
		this,
		&UWeaponArtComponent::LaunchSlashSpell,
		.5f
	);
}



void UWeaponArtComponent::LaunchSlashSpell()
{
	UWorld* World = GetWorld();

	if (World && Projectile)
	{
		EndBaseSlashPosition = Weapon->GetActorLocation();
		EndTipSlashPosition = Weapon->GetMesh()->GetSocketLocation(FName("trailEnd"));

		FVector StartMiddleBaseSlashPosition = FMath::Lerp(StartBaseSlashPosition, EndBaseSlashPosition, 0.5f);
		FVector StartMiddleTipSlashPosition = FMath::Lerp(StartTipSlashPosition, EndTipSlashPosition, 0.5f);


		FActorSpawnParameters SpawnParams;
		AActor* SpawnedProjectile = nullptr;

		// (StartMiddleTipSlashPosition - StartMiddleBaseSlashPosition).Rotation(),

		SpawnedProjectile = World->SpawnActor<AActor>(
			Projectile,
			StartMiddleBaseSlashPosition,
			Weapon->GetActorRotation() + FRotator(90.f,0.f,0.f),
			SpawnParams
		);

		if (CastSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CastSound, StartMiddleTipSlashPosition);
		}
	}
}


