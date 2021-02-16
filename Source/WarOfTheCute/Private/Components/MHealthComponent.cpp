// Creative Commons - Reconocimiento (by)


#include "Components/MHealthComponent.h"

// Sets default values for this component's properties
UMHealthComponent::UMHealthComponent()
{

	DefaultHealth = 100;
}


// Called when the game starts
void UMHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();

	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UMHealthComponent::HandleTakeAnyDamage);
	}
	
	Health = DefaultHealth;
}

void UMHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	// Update helath clamped
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));

}
