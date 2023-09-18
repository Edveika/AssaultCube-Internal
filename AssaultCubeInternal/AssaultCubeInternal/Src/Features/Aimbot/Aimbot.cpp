#include "../../Includes.h"

Entity* GetBestTarget()
{
	float oldDistance = FLT_MAX;
	float newDistance = 0;
	Entity* target = nullptr;

	for (int i = 0; i < (*playerCount); i++)
	{
		Entity* entity = entityList->entity[i];

		if (entity && entity != pLocalPlayer && entity->Health > 0)
		{
			Vector3 angleTo = Math::CalcAngle(pLocalPlayer->HeadPos, entity->HeadPos);
			newDistance = Math::Distance(pLocalPlayer->ViewAngles, angleTo);

			if (newDistance < oldDistance)
			{
				oldDistance = newDistance;
				target = entity;
			}
		}
	}

	return target;
}

void Aimbot::Run()
{
	Entity* bestTarget = GetBestTarget();

	if (g_Settings.g_bAimbotVisibilityCheck && !IsVisible(bestTarget))
		return;

	if (g_Settings.g_bAimbotTeamCheck && pLocalPlayer->Team == bestTarget->Team)
		return;

	if (g_Settings.g_bAimbotAutoPistols)
		pLocalPlayer->CurrentWeapon->Stats->IsAutomatic = true;

	if (g_Settings.g_bAimbotNoShotCooldown)
		pLocalPlayer->CurrentWeapon->Stats->Cooldown = 0;

	if (g_Settings.g_bAimbotRCS)
		Utils::Nop((BYTE*)(moduleBase + 0x63786), 10);
	else
		Utils::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);

	Vector3 targetAngles = Math::CalcAngle(pLocalPlayer->HeadPos, bestTarget->HeadPos);

	if (bestTarget && bestTarget != NULL && bestTarget != pLocalPlayer && bestTarget->Health > 0)
		pLocalPlayer->ViewAngles = targetAngles;
}