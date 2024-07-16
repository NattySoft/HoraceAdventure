// NattySoft - All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HA_BaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class HORACEADVENTURE_API AHA_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHA_BaseCharacter();

protected:
	virtual void BeginPlay() override;

	// COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* CameraBoomComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	float MaxWalkSpeed = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	float JumpVelocityZ = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	float GravityScale = 2.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movements")
	float AirControl = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Camera Logic")
	bool bCanAdjustCamera = false; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Camera Logic")
	float CameraDistanceFromPlayer = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Camera Logic")
	float CameraOffsetX = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Camera Logic")
	float CameraOffsetY = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Camera Logic")
	float CameraOffsetZ = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Camera Logic")
	float CameraLagSpeed = 10.f;

private:
	void UpdateCamera();
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
