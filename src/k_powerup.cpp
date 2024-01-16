/// \brief Battle mode power-up code

#include <algorithm>

#include "k_kart.h"
#include "k_objects.h"
#include "k_powerup.h"
#include "k_hud.h" // K_AddMessage

tic_t K_PowerUpRemaining(const player_t* player, kartitems_t powerup)
{
	switch (powerup)
	{
	case POWERUP_SMONITOR:
		return player->powerup.superTimer;

	case POWERUP_BARRIER:
		return player->powerup.barrierTimer;

	case POWERUP_BADGE:
		return player->powerup.rhythmBadgeTimer;

	case POWERUP_SUPERFLICKY:
		return Obj_SuperFlickySwarmTime(player->powerup.flickyController);

	default:
		return 0u;
	}
}

UINT32 K_AnyPowerUpRemaining(const player_t* player)
{
	UINT32 mask = 0;

	for (int k = FIRSTPOWERUP; k < ENDOFPOWERUPS; ++k)
	{
		if (K_PowerUpRemaining(player, static_cast<kartitems_t>(k)))
		{
			mask |= POWERUP_BIT(k);
		}
	}

	return mask;
}

void K_GivePowerUp(player_t* player, kartitems_t powerup, tic_t time)
{
	if (!K_AnyPowerUpRemaining(player))
	{
		Obj_SpawnPowerUpAura(player);
	}

	switch (powerup)
	{
	case POWERUP_SMONITOR:
		K_AddMessageForPlayer(player, "Got S MONITOR!", true, false);
		K_DoInvincibility(player, time);
		player->powerup.superTimer += time;
		break;

	case POWERUP_BARRIER:
		K_AddMessageForPlayer(player, "Got MEGA BARRIER!", true, false);
		player->powerup.barrierTimer += time;
		Obj_SpawnMegaBarrier(player);
		break;

	case POWERUP_BUMPER:
		K_AddMessageForPlayer(player, "Got BUMPER RESTOCK!", true, false);
		K_GiveBumpersToPlayer(player, nullptr, 5);
		break;

	case POWERUP_BADGE:
		K_AddMessageForPlayer(player, "Got RHYTHM BADGE!", true, false);
		player->powerup.rhythmBadgeTimer += time;
		break;

	case POWERUP_SUPERFLICKY:
		K_AddMessageForPlayer(player, "Got SUPER FLICKY!", true, false);
		if (K_PowerUpRemaining(player, POWERUP_SUPERFLICKY))
		{
			Obj_ExtendSuperFlickySwarm(player->powerup.flickyController, time);
		}
		else
		{
			Obj_SpawnSuperFlickySwarm(player, time);
		}
		break;

	default:
		break;
	}
}

void K_DropPowerUps(player_t* player)
{
	auto drop = [player](kartitems_t powerup, auto callback)
	{
		tic_t remaining = K_PowerUpRemaining(player, powerup);

		if (remaining)
		{
			K_DropPaperItem(player, powerup, remaining);
			callback();
		}
	};

	auto& powerup = player->powerup;

	drop(
		POWERUP_SMONITOR, [&]
		{
			// P_CheckInvincibilityTimer needs 1 tic to end the music
			player->invincibilitytimer -= std::min(+powerup.superTimer, player->invincibilitytimer - 1);
			powerup.superTimer = 0;
		}
	);

	drop(POWERUP_BARRIER, [&] { powerup.barrierTimer = 0; });
	drop(POWERUP_BADGE, [&] { powerup.rhythmBadgeTimer = 0; });
	drop(POWERUP_SUPERFLICKY, [&] { Obj_EndSuperFlickySwarm(powerup.flickyController); });
}
