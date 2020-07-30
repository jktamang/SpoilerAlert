#pragma once
#include <set>

class Enemy;
class Bullet;
class Player;
class PowerUp;
class Obstacle;

struct Cell
{
	std::set<Enemy*> m_Enemies;
	std::set<Bullet*> m_Bullets;
	std::set<Player*> m_Player;
	std::set<PowerUp*> m_PowerUps;
	std::set<Obstacle*> m_Obstacles;
};
