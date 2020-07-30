#include <cmath>
#include <cstdlib>
#include "enemy.h"
#include "game_constants.h"

Enemy::Enemy(const std::vector<Obstacle*>& obstacles) : 
	GameObject(
		0, 0,
		ENEMY_WIDTH, ENEMY_HEIGHT,
		fmod((float)rand(), 360.0f),
		ENEMY_ROTATION_SPEED, ENEMY_MOVE_SPEED,
		ENEMY_SPRITE_PATH1, ENEMY_HEALTH),
	m_RoamCounter(FPS)
{
	MoveForward();
	if (rand()%2 == 0)
	{
		m_Type = Roams;
		SetSprite(ENEMY_SPRITE_PATH2);
	}
	else
	{
		m_Type = Follows;
	}
	m_Obstacles = obstacles;
	Resurrect();
}

Enemy::~Enemy()
{
}

bool Enemy::IsAtEdge()
{
	return GetX() == 0 || GetY() == 0 ||
		GetX() >= MAP_WIDTH - ENEMY_WIDTH ||
		GetY() >= MAP_HEIGHT - ENEMY_HEIGHT;
}

void Enemy::FollowPlayer(int playerX, int playerY)
{
	float y = float(playerY - GetY());
	float x = float(playerX - GetX());
	
	float targetAngle = atan2(y, x) * 180 / PI;
	float adjustedAngle = fmod(((targetAngle - GetAngle()) + 540), 360);

	if (adjustedAngle < 180)
		TurnLeft();
	else if (adjustedAngle >= 180)
		TurnRight();
	else
		StopTurning();
}

void Enemy::Roam()
{
	if (IsAtEdge())
	{
		if (rand()%2 == 0)
			TurnLeft();
		else
			TurnRight();
	}
	else
	{
		StopTurning();
	}
}

void Enemy::Turn(int playerX, int playerY)
{
	switch (m_Type)
	{
		case Follows:
		{
			FollowPlayer(playerX, playerY);
			GameObject::Turn();
			break;
		}
		case Roams:
		{
			Roam();
			break;
		}
		default:
			break;
	}
}

void Enemy::Update()
{
	if (m_Type == Roams && !CanMoveX() && !CanMoveY())
	{
		TurnRight();
		GameObject::Turn();
	}
	GameObject::Update();
}

bool Enemy::CollidesWithObstacles()
{
	for (int i = 0; i < (int)m_Obstacles.size(); i++)
	{
		if (GameObject::CollidesWith(m_Obstacles[i]->GetRect()))
			return true;
	}
	return false;
}

void Enemy::Resurrect()
{
	do 
	{
		GameObject::Resurrect(
			rand()%(1920 - ENEMY_WIDTH),
			rand()%(1440 - ENEMY_HEIGHT));

	}while (CollidesWithObstacles());
}

void Enemy::TakeDamage()
{
	GameObject::TakeDamage();
	if (GetHealth() <= 0) Resurrect();
}