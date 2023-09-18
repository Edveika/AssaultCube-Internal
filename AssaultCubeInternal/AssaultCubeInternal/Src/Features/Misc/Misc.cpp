#include "../../Includes.h"

void Misc::InfiniteHealth()
{
	pLocalPlayer->Health = 1337;
}

void Misc::InfiniteArmor()
{
	pLocalPlayer->Armor = 1337;
}

void Misc::InfiniteAmmo()
{
	pLocalPlayer->CurrentWeapon->Ammo->Ammo = 1337;
}