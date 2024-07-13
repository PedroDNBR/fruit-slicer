// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "FruitSlicer/FruitSlicer.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "FruitSlicer/Components/WeaponArtComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	SetRootComponent(SkeletalMesh);

	SkeletalMesh->SetCollisionObjectType(ECC_Damagable);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	SkeletalMesh->SetSimulatePhysics(true);
	SkeletalMesh->SetAllMassScale(MassScale);
	SkeletalMesh->SetNotifyRigidBodyCollision(true);
	SkeletalMesh->SetGenerateOverlapEvents(false);

	WeaponArtComponent = CreateDefaultSubobject<UWeaponArtComponent>(TEXT("WeaponArtComponent"));
	WeaponArtComponent->SetWeapon(this);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	WeaponArtComponent->SetWeapon(this);
}

USkeletalMeshComponent* AWeapon::GetMesh()
{
	return SkeletalMesh;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

