#include <cmath>
#include "player.h"

Player::Player() : 
	GameObject(
		rand()%(MAP_WIDTH - PLAYER_WIDTH),
		rand()%(MAP_HEIGHT - PLAYER_HEIGHT),
		PLAYER_WIDTH, PLAYER_HEIGHT,
		fmod(float(rand()), 360.0f),
		PLAYER_ROTATION_SPEED, PLAYER_MOVE_SPEED,
		PLAYER_SPRITE_PATH, PLAYER_HEALTH),
	m_IsInvincible(false), m_InvincibilityFrames(0),
	m_IsShooting(false), m_HasPowerUp(false)
{
}


Player::~Player()
{
}

void Player::MakeInvincible(int invincibilityFrames)
{
	m_IsInvincible = true;
	m_InvincibilityFrames = invincibilityFrames;
}

void Player::ManageInvincibility()
{
	if (!m_IsInvincible) return;

	m_InvincibilityFrames--;
	
	if (m_InvincibilityFrames <= 0)
		m_IsInvincible = false;
}

void Player::ManagePowerUp()
{
	if (!m_HasPowerUp) return;

	m_PowerUpTimer--;
	
	if (m_PowerUpTimer <= 0)
		m_HasPowerUp = false;
}

void Player::Update()
{
	ManageInvincibility();
	ManagePowerUp();

	GameObject::Update();
}

void Player::TakeDamage()
{
	if (m_IsInvincible) return;

	GameObject::TakeDamage();
	MakeInvincible(INVINCIBILITY_FRAMES);
}

void Player::StartShooting()
{
	m_IsShooting = true;
}

void Player::StopShooting()
{
	m_IsShooting = false;
}

bool Player::IsShooting()
{
	return m_IsShooting;
}

bool Player::HasPowerUp()
{
	return m_HasPowerUp;
}

void Player::PowerUp()
{
	m_HasPowerUp = true;
	m_PowerUpTimer = POWER_UP_DURATION;
}

void Player::RestoreHealth()
{
	SetHealth(GetHealth() + 10);
}

bool Player::IsInvincible()
{
	return m_IsInvincible;
}

void Player::Resurrect(int x, int y)
{
	StopMoving();
	StopTurning();
	StopShooting();
	m_HasPowerUp = false;

	GameObject::Resurrect(x, y);
}
