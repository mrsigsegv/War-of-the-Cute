// Creative Commons - Reconocimiento (by)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UMHealthComponent;
class URadialForceComponent;


UCLASS()
class WAROFTHECUTE_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void Attack();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAttack();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMHealthComponent* HealthComp;

	UFUNCTION()
	void OnHealthChanged(UMHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/* Pawn died previously */
	UPROPERTY(BlueprintReadOnly, Category = "Player")
	bool bDied;

	/* Simple Attack */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* RadialForceComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* AttackFX;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	float AttackImpulse;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float AttackRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float AttackDamage;

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void MulticastRPCPlayEffects();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
