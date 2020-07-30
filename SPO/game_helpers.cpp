#include "game_helpers.h"

void CheckPlayerEnemyCollision(
	Player* pPlayer,
	Enemy* pEnemy,
	bool isPlayerInCell,
	bool playerIsInvincible)
{
	if (isPlayerInCell && !playerIsInvincible)
	{
		if (pPlayer->CollidesWith(pEnemy->GetRect()))
		{
			pPlayer->TakeDamage();
		}
	}

	pPlayer = NULL;
	pEnemy = NULL;
}

void CheckEnemyEnemyCollision(
	std::set<Enemy*>::iterator& enemy,
	const std::set<Enemy*>& otherEnemies)
{
	SDL_Rect enemyTryX = (*enemy)->TryMoveX();
	SDL_Rect enemyTryY = (*enemy)->TryMoveY();
	std::set<Enemy*>::iterator otherEnemy;

	for (otherEnemy = std::next(enemy, 1); otherEnemy != otherEnemies.end(); otherEnemy++)
	{
		if (!(*enemy)->CanMoveX() && !(*enemy)->CanMoveY()) break;

		if ((*enemy)->CanMoveX() && (*otherEnemy)->CollidesWith(&enemyTryX))
		{
			(*enemy)->SetCanMoveX(false);
		}
		if ((*enemy)->CanMoveY() && (*otherEnemy)->CollidesWith(&enemyTryY))
		{
			(*enemy)->SetCanMoveY(false);
		}
	}
}


void CheckEnemyObstacleCollision(Enemy* pEnemy, const std::set<Obstacle*>& obstacles)
{
	SDL_Rect enemyTryX = pEnemy->TryMoveX();
	SDL_Rect enemyTryY = pEnemy->TryMoveY();
	std::set<Obstacle*>::iterator obstacle;

	for (obstacle = obstacles.begin(); obstacle != obstacles.end();
					obstacle++)
	{
		if (!pEnemy->CanMoveX() && !pEnemy->CanMoveY()) break;

		if (pEnemy->CanMoveX() && (*obstacle)->CollidesWith(&enemyTryX))
		{
			pEnemy->SetCanMoveX(false);
		}
		if (pEnemy->CanMoveY() && (*obstacle)->CollidesWith(&enemyTryY))
		{
			pEnemy->SetCanMoveY(false);
		}
	}
	pEnemy = NULL;
}

bool CheckBulletEnemyCollision(Bullet* pBullet, const std::set<Enemy*>& enemies)
{
	std::set<Enemy*>::iterator enemy;

	for (enemy = enemies.begin(); enemy != enemies.end() ; enemy++)
	{
		if (pBullet->CollidesWith((*enemy)->GetRect()))
		{
			(*enemy)->TakeDamage();
			pBullet->SetActive(false);
			pBullet = NULL;
			return true;
		}
	}
	pBullet = NULL;
	return false;
}

void CheckBulletObstacleCollision(Bullet* pBullet, const std::set<Obstacle*>& obstacles)
{
	std::set<Obstacle*>::iterator obstacle;

	for (obstacle = obstacles.begin(); obstacle != obstacles.end() ; obstacle++)
	{
		if (pBullet->CollidesWith((*obstacle)->GetRect()))
		{
			pBullet->SetActive(false);
			break;
		}
	}
	pBullet = NULL;
}

void CheckPlayerObstacleCollision(Player* pPlayer, const std::set<Obstacle*>& obstacles)
{
	if (!pPlayer->CanMoveX() && !pPlayer->CanMoveY())
			return;

	std::set<Obstacle*>::iterator obstacle;
	SDL_Rect playerTryX = pPlayer->TryMoveX();
	SDL_Rect playerTryY = pPlayer->TryMoveY();

	for (obstacle = obstacles.begin(); obstacle != obstacles.end();
			obstacle++)
	{
		if (!pPlayer->CanMoveX() && !pPlayer->CanMoveY())
			break;

		if (pPlayer->CanMoveX() && (*obstacle)->CollidesWith(&playerTryX))
		{
			pPlayer->SetCanMoveX(false);
		}
		if (pPlayer->CanMoveY() && (*obstacle)->CollidesWith(&playerTryY))
		{
			pPlayer->SetCanMoveY(false);
		}
	}
	pPlayer = NULL;
}
