// Creative Commons - Reconocimiento (by)


#include "Components/MHealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UMHealthComponent::UMHealthComponent()
{

	DefaultHealth = 100;
	SetIsReplicated(true);
}


// Called when the game starts
void UMHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
	AActor* MyOwner = GetOwner();

	if (MyOwner)
	{
		// Only hook if we are server
		if (GetOwnerRole() == ROLE_Authority)
		{
			MyOwner->OnTakeAnyDamage.AddDynamic(this, &UMHealthComponent::HandleTakeAnyDamage);
		}
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

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

void UMHealthComponent::Heal(float HealAmount)
{
	if (HealAmount <= 0.0f || Health <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health + HealAmount, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s (+%s)"), *FString::SanitizeFloat(Health), *FString::SanitizeFloat(HealAmount));
	OnHealthChanged.Broadcast(this, Health, -HealAmount, nullptr, nullptr, nullptr);

}

void UMHealthComponent::OnRep_Health(float OldHealth)
{
	float Damage = Health - OldHealth;

	OnHealthChanged.Broadcast(this, Health, Damage, nullptr, nullptr, nullptr);
}

void UMHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMHealthComponent, Health);

}
