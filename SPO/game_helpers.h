#pragma once

#include <set>
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "obstacle.h"
#include "game_constants.h"

void CheckPlayerEnemyCollision(Player*, Enemy*, bool, bool);

void CheckEnemyEnemyCollision(std::set<Enemy*>::iterator&, const std::set<Enemy*>&);

void CheckEnemyObstacleCollision(Enemy*, const std::set<Obstacle*>&);

bool CheckBulletEnemyCollision(Bullet*, const std::set<Enemy*>&);

void CheckBulletObstacleCollision(Bullet*, const std::set<Obstacle*>&);

void CheckPlayerObstacleCollision(Player*, const std::set<Obstacle*>&);