#include "GORHealthComponentBase.h"


UGORHealthComponentBase::UGORHealthComponentBase()
{
	
}

bool UGORHealthComponentBase::ApplyDamage(float Damage, AActor* DamageInstigator, UObject* DamageCause)
{
	if(bIsDead)
	{
		return false;
	}

	if(bCanReceiveDamage)
	{
		Health -= Damage;

		if(Health <= 0.0f)
		{
			bIsDead = true;
			Health = 0.0f;
			bCanReceiveDamage =false;

			OnDeathDelegate.Broadcast();
		}

		return true;
	}

	return false;

}

void UGORHealthComponentBase::AddHealth(float ExtraHealth)
{
	Health += ExtraHealth;

	if(Health >= MaxHealth)
	{
		Health = MaxHealth;
	}

	OnHealthAddedDelegate.Broadcast();
}

void UGORHealthComponentBase::SetCanReceiveDamage(bool Val)
{
	bCanReceiveDamage = Val;
}

