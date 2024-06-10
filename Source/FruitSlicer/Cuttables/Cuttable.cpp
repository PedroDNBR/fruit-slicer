// Fill out your copyright notice in the Description page of Project Settings.


#include "Cuttable.h"
#include "FruitSlicer/FruitSlicer.h"
#include "FruitSlicer/Weapons/Weapon.h"
#include "FruitSlicer/Weapons/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundCue.h" 

// Sets default values
ACuttable::ACuttable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	SetRootComponent(Mesh);

	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_Damagable, ECollisionResponse::ECR_Block);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->SetGenerateOverlapEvents(false);
	Mesh->SetAllMassScale(1.f);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->SetIsReplicated(true);

	float const RandomSpeed = UKismetMathLibrary::RandomFloatInRange(InitialSpeedBase, InitialSpeedMax);
	ProjectileMovementComponent->InitialSpeed = RandomSpeed;
	ProjectileMovementComponent->MaxSpeed = RandomSpeed;

	SetLifeSpan(15.f);

}

// Called when the game starts or when spawned
void ACuttable::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &ACuttable::OnHit);
}

void ACuttable::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr) {
		AWeapon* Weapon = Cast<AWeapon>(OtherActor);
		AProjectile* Projectile = Cast<AProjectile>(OtherActor);
		if ((Weapon && Weapon->bCanCut) || Projectile)
		{
			FActorSpawnParameters SpawnParams;
			UWorld* World = GetWorld();
			if (World && CuttedMeshActor)
			{
				World->SpawnActor<AActor>(
					CuttedMeshActor,
					Mesh->GetComponentLocation(),
					Mesh->GetComponentRotation(),
					SpawnParams
				);
				World->SpawnActor<AActor>(
					CuttedMeshActor,
					Mesh->GetComponentLocation(),
					FRotator(-Mesh->GetComponentRotation().Pitch, -Mesh->GetComponentRotation().Yaw, -Mesh->GetComponentRotation().Roll),
					SpawnParams
				);
				if (CutSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, CutSound, GetActorLocation());
				}
			}			
			Destroy();
		}
	}
}

// Called every frame
void ACuttable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

