// Creative Commons - Reconocimiento (by)


#include "MPowerupActor.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AMPowerupActor::AMPowerupActor()
{

	PowerupInterval = 0.0f;
	TotalNrOfTicks = 0; 

	bIsPowerupActive = false;

	SetReplicates(true);
}

void AMPowerupActor::OnTickPowerup()
{
	TicksProcessed++;

	OnPowerupTicked();

	if (TicksProcessed >= TotalNrOfTicks)
	{
		OnExpired();
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTick);
	}
}

void AMPowerupActor::OnRep_PowerupActive()
{
	OnPowerupStateChanged(bIsPowerupActive);
}

void AMPowerupActor::ActivatePowerup(AActor* ActiveFor)
{

	OnAcivated(ActiveFor);

	bIsPowerupActive = true;
	OnRep_PowerupActive();

	if (PowerupInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTick, this, &AMPowerupActor::OnTickPowerup, PowerupInterval, true);
	}
	else
	{
		OnTickPowerup();
	}
}

void AMPowerupActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMPowerupActor, bIsPowerupActive);

}