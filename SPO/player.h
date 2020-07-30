#pragma once
#include "game_object.h"
#include "game_constants.h"

class Player :
	public GameObject
{
public:
	Player();
	~Player();
	void Update();
	void TakeDamage();
	void StartShooting();
	void StopShooting();
	bool IsShooting();
	bool HasPowerUp();
	void PowerUp();
	void RestoreHealth();
	bool IsInvincible();
	void Resurrect(int, int);

private:
	void MakeInvincible(int);
	void ManageInvincibility();
	void ManagePowerUp();

	bool m_IsInvincible;
	int m_InvincibilityFrames;
	bool m_IsShooting;
	bool m_HasPowerUp;
	int m_PowerUpTimer;
};
