#pragma once
#include "game_object.h"
#include "player.h"

enum PowerUpType
{
	Bucket,
	Soda
};

class PowerUp :
	public GameObject
{
public:
	PowerUp(std::string, PowerUpType);
	~PowerUp();
	void ApplyPowerUp(Player*);
	void Update();

private:
	PowerUpType m_Type;
	int m_NotActiveCounter;
};

