#pragma once
#include <set>
#include <vector>
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "power_up.h"
#include "obstacle.h"
#include "cell.h"
#include "game_constants.h"

class Grid
{
public:
	Grid(Player*);
	~Grid();
	void Populate(
		std::vector<Enemy*>&,
		std::vector<Bullet*>&,
		std::vector<PowerUp*>&,
		std::vector<Obstacle*>&);
	void Update();
	void Clear();
	std::set<Enemy*>& GetEnemiesInCell(int, int);
	std::set<Bullet*>& GetBulletsInCell(int, int);
	std::set<PowerUp*>& GetPowerUpsInCell(int, int);
	std::set<Obstacle*>& GetObstaclesInCell(int, int);
	bool IsPlayerInCell(int, int);
	void UpdateObstacles();
	void Close();

private:
	void AddPlayerToGrid(int, int, int, int);
	void AddEnemyToGrid(int, int, int, int, Enemy*);
	void AddBulletToGrid(int, int, int, int, Bullet*);
	void AddPowerUpToGrid(int, int, int, int, PowerUp*);
	void AddObstacleToGrid(int, int, int, int, Obstacle*);
	void PopulateGrid();
	void RemovePlayerFromCell(int, int);
	void RemovePlayerFromGrid();
	void RemoveEnemyFromCell(int, int, Enemy*);
	void RemoveEnemyFromGrid(Enemy*);
	void RemoveBulletFromCell(int, int, Bullet*);
	void RemoveBulletFromGrid(Bullet*);
	void RemovePowerUpFromCell(int, int, PowerUp*);
	void RemovePowerUpFromGrid(PowerUp*);
	void RemoveObstacleFromCell(int, int, Obstacle*);
	void RemoveObstacleFromGrid(Obstacle*);
	bool NeedToUpdatePlayer(int, int, int, int);
	bool NeedToUpdateEnemy(int, int, int, int, Enemy*);
	bool NeedToUpdateBullet(int, int, int, int, Bullet*);
	bool NeedToUpdatePowerUp(int, int, int, int, PowerUp*);

	Player* m_pPlayer;
	std::vector<Enemy*> m_Enemies;
	std::vector<Bullet*> m_Bullets;
	std::vector<PowerUp*> m_PowerUps;
	std::vector<Obstacle*> m_Obstacles;
	Cell m_Grid[GRID_WIDTH][GRID_HEIGHT];
};
