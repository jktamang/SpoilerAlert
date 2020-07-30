#include <cstdlib>
#include "power_up.h"

PowerUp::PowerUp(std::string spritePath, PowerUpType type) :
		GameObject(
			rand()%(MAP_WIDTH - POWER_UP_WIDTH),
			rand()%(MAP_HEIGHT - POWER_UP_HEIGHT),
			POWER_UP_WIDTH, POWER_UP_HEIGHT, 0.0f,
			0.0f, 0.0f, spritePath, 1),
		m_NotActiveCounter(POWER_UP_DURATION),
		m_Type(type)
{
	StopMoving();
	StopTurning();
}

PowerUp::~PowerUp()
{
}

void PowerUp::ApplyPowerUp(Player* pPlayer)
{
	switch (m_Type)
	{
		case Soda:
			pPlayer->RestoreHealth();
			break;
		case Bucket:
			pPlayer->PowerUp();
			break;
		default:
			break;
	}
	m_NotActiveCounter = POWER_UP_DURATION;
	SetActive(false);
	pPlayer = NULL;
}

void PowerUp::Update()
{
	if (m_NotActiveCounter > 0)
	{
		m_NotActiveCounter--;
		return;
	}
	else if (!IsActive())
	{
		Resurrect(
			rand()%(MAP_WIDTH - POWER_UP_WIDTH),
			rand()%(MAP_HEIGHT - POWER_UP_HEIGHT));
		SetActive(true);
	}
}