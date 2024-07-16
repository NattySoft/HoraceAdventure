// NattySoft - All Right Reserved


#include "Characters/HA_BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AHA_BaseCharacter::AHA_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>("CameraBoomComponent");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	CameraBoomComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(CameraBoomComponent, USpringArmComponent::SocketName);

	CameraBoomComponent->TargetArmLength = CameraDistanceFromPlayer;
	CameraBoomComponent->bDoCollisionTest = false;
	CameraBoomComponent->bInheritPitch = false;
	CameraBoomComponent->bInheritYaw = false;
	CameraBoomComponent->bEnableCameraLag = true;
	CameraBoomComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// ReSharper disable CppVirtualFunctionCallInsideCtor
	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	CharacterMovementComponent->bConstrainToPlane = true;
	CharacterMovementComponent->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
	CharacterMovementComponent->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	CharacterMovementComponent->MaxWalkSpeed = MaxWalkSpeed;
	CharacterMovementComponent->GroundFriction = 2.f;
	CharacterMovementComponent->JumpZVelocity = JumpVelocityZ;
	CharacterMovementComponent->GravityScale = GravityScale;
	CharacterMovementComponent->AirControl = AirControl;;
	
}

void AHA_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHA_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCamera();
}

void AHA_BaseCharacter::UpdateCamera()
{
	if (!bCanAdjustCamera) return;
	FVector NewLocation;
	NewLocation.X = CameraOffsetX;
	NewLocation.Y = CameraOffsetY;
	NewLocation.Z = CameraOffsetZ;
	CameraBoomComponent->SetRelativeLocation(NewLocation);
	CameraBoomComponent->CameraLagSpeed = CameraLagSpeed;
	CameraBoomComponent->TargetArmLength = CameraDistanceFromPlayer;
}

void AHA_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

