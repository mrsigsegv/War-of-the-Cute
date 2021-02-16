// Creative Commons - Reconocimiento (by)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MHealthComponent.generated.h"


UCLASS( ClassGroup=(MONSTER), meta=(BlueprintSpawnableComponent) )
class WAROFTHECUTE_API UMHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "HealthComponent")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float DefaultHealth;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
		
};
