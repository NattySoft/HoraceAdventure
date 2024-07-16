// NattySoft - All Right Reserved


#include "Weapons/HA_FireBall.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "HoraceAdventure/HoraceAdventure.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AHA_FireBall::AHA_FireBall()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Sphere");
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	
	SetRootComponent(Mesh);
	ParticleSystem->SetupAttachment(Mesh);

	Mesh->SetCollisionObjectType(ECC_FireBall); // FireBall
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_FireBall, ECR_Ignore);
	
	ProjectileMovement->InitialSpeed = InitialSpeed;
	ProjectileMovement->MaxSpeed = MaxSpeed;
	ProjectileMovement->bShouldBounce = bShouldBounce;
	ProjectileMovement->Bounciness = Bounciness;
	ProjectileMovement->Friction = Friction;
}

void AHA_FireBall::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(DestroyAfterSeconds);
	ProjectileMovement->OnProjectileBounce.AddDynamic(this, &AHA_FireBall::OnFireBallBounce);
}

void AHA_FireBall::Destroyed()
{
	FireballDestroyedDelegate.Broadcast();
	Super::Destroyed();
}

void AHA_FireBall::OnFireBallBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	if (const float ImpactNormalZ = ImpactResult.Normal.GetAbs().Z; ImpactNormalZ < 0.9f)
	{
		Explode();
	}
	else
	{
		BounceCounter++;
		if (BounceCounter >= BounceMaxCounter)
		{
			Explode();
		}
	}
}

void AHA_FireBall::Explode()
{
	if (ExplodeEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplodeEffect, GetActorLocation());
	}

	if (ExplodeSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplodeSound, GetActorLocation());
	}

	Destroy();
}
