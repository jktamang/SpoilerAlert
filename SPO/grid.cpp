#include "grid.h"

Grid::Grid(Player* pPlayer) :
	m_pPlayer(pPlayer)
{
}

Grid::~Grid()
{
}

std::set<Enemy*>& Grid::GetEnemiesInCell(int column, int row)
{
	return m_Grid[column][row].m_Enemies;
}

std::set<Bullet*>& Grid::GetBulletsInCell(int column, int row)
{
	return m_Grid[column][row].m_Bullets;
}

std::set<PowerUp*>& Grid::GetPowerUpsInCell(int column, int row)
{
	return m_Grid[column][row].m_PowerUps;
}

std::set<Obstacle*>& Grid::GetObstaclesInCell(int column, int row)
{
	return m_Grid[column][row].m_Obstacles;
}

bool Grid::IsPlayerInCell(int column, int row)
{
	return !m_Grid[column][row].m_Player.empty();
}

void Grid::AddPlayerToGrid(int minCol, int minRow, int maxCol, int maxRow)
{
	m_Grid[minCol][minRow].m_Player.insert(m_pPlayer);
	m_Grid[minCol][maxRow].m_Player.insert(m_pPlayer);
	m_Grid[maxCol][minRow].m_Player.insert(m_pPlayer);
	m_Grid[maxCol][maxRow].m_Player.insert(m_pPlayer);
	m_pPlayer->SetGridMinColumn(minCol);
	m_pPlayer->SetGridMinRow(minRow);
}

void Grid::AddEnemyToGrid(int minCol, int minRow, int maxCol, int maxRow, Enemy* pEnemy)
{
	m_Grid[minCol][minRow].m_Enemies.insert(pEnemy);
	m_Grid[minCol][maxRow].m_Enemies.insert(pEnemy);
	m_Grid[maxCol][minRow].m_Enemies.insert(pEnemy);
	m_Grid[maxCol][maxRow].m_Enemies.insert(pEnemy);
	pEnemy->SetGridMinColumn(minCol);
	pEnemy->SetGridMinRow(minRow);
	pEnemy = NULL;
}

void Grid::AddBulletToGrid(int minCol, int minRow, int maxCol, int maxRow, Bullet* pBullet)
{
	m_Grid[minCol][minRow].m_Bullets.insert(pBullet);
	m_Grid[minCol][maxRow].m_Bullets.insert(pBullet);
	m_Grid[maxCol][minRow].m_Bullets.insert(pBullet);
	m_Grid[maxCol][maxRow].m_Bullets.insert(pBullet);
	pBullet->SetGridMinColumn(minCol);
	pBullet->SetGridMinRow(minRow);
	pBullet = NULL;
}

void Grid::AddPowerUpToGrid(int minCol, int minRow, int maxCol, int maxRow, PowerUp* pPowerUp)
{
	m_Grid[minCol][minRow].m_PowerUps.insert(pPowerUp);
	m_Grid[minCol][maxRow].m_PowerUps.insert(pPowerUp);
	m_Grid[maxCol][minRow].m_PowerUps.insert(pPowerUp);
	m_Grid[maxCol][maxRow].m_PowerUps.insert(pPowerUp);
	pPowerUp->SetGridMinColumn(minCol);
	pPowerUp->SetGridMinRow(minRow);
	pPowerUp = NULL;
}

void Grid::AddObstacleToGrid(int minCol, int minRow, int maxCol, int maxRow, Obstacle* pObstacle)
{
	m_Grid[minCol][minRow].m_Obstacles.insert(pObstacle);
	m_Grid[minCol][maxRow].m_Obstacles.insert(pObstacle);
	m_Grid[maxCol][minRow].m_Obstacles.insert(pObstacle);
	m_Grid[maxCol][maxRow].m_Obstacles.insert(pObstacle);
	pObstacle->SetGridMinColumn(minCol);
	pObstacle->SetGridMinRow(minRow);
	pObstacle = NULL;
}

void Grid::RemovePlayerFromCell(int column, int row)
{
	if (column < GRID_WIDTH && row < GRID_HEIGHT)
	{
		std::set<Player*>::iterator playerItr = m_Grid[column][row].m_Player.find(m_pPlayer);
		if (playerItr != m_Grid[column][row].m_Player.end())
			m_Grid[column][row].m_Player.erase(playerItr);
	}
}

void Grid::RemovePlayerFromGrid()
{
	int minCol = m_pPlayer->GetGridMinColumn();
	int minRow= m_pPlayer->GetGridMinRow();
	
	RemovePlayerFromCell(minCol, minRow);
	RemovePlayerFromCell(minCol + 1, minRow);
	RemovePlayerFromCell(minCol, minRow + 1);
	RemovePlayerFromCell(minCol + 1, minRow + 1);
}

void Grid::RemoveEnemyFromCell(int column, int row, Enemy* pEnemy)
{
	if (column < GRID_WIDTH && row < GRID_HEIGHT)
	{
		std::set<Enemy*>::iterator enemyItr = m_Grid[column][row].m_Enemies.find(pEnemy);
		if (enemyItr != m_Grid[column][row].m_Enemies.end())
			m_Grid[column][row].m_Enemies.erase(enemyItr);
	}
	pEnemy = NULL;
}

void Grid::RemoveEnemyFromGrid(Enemy* pEnemy)
{
	int minCol = pEnemy->GetGridMinColumn();
	int minRow= pEnemy->GetGridMinRow();

	RemoveEnemyFromCell(minCol, minRow, pEnemy);
	RemoveEnemyFromCell(minCol + 1, minRow, pEnemy);
	RemoveEnemyFromCell(minCol, minRow + 1, pEnemy);
	RemoveEnemyFromCell(minCol + 1, minRow + 1, pEnemy);
	
	pEnemy = NULL;
}

void Grid::RemoveBulletFromCell(int column, int row, Bullet* pBullet)
{
	if (column < GRID_WIDTH && row < GRID_HEIGHT)
	{
		std::set<Bullet*>::iterator bulletItr = m_Grid[column][row].m_Bullets.find(pBullet);
		if (bulletItr != m_Grid[column][row].m_Bullets.end())
			m_Grid[column][row].m_Bullets.erase(bulletItr);
	}
	pBullet = NULL;
}

void Grid::RemoveBulletFromGrid(Bullet* pBullet)
{
	int minCol = pBullet->GetGridMinColumn();
	int minRow= pBullet->GetGridMinRow();

	RemoveBulletFromCell(minCol, minRow, pBullet);
	RemoveBulletFromCell(minCol + 1, minRow, pBullet);
	RemoveBulletFromCell(minCol, minRow + 1, pBullet);
	RemoveBulletFromCell(minCol + 1, minRow + 1, pBullet);

	pBullet = NULL;
}

void Grid::RemovePowerUpFromCell(int column, int row, PowerUp* pPowerUp)
{
	if (column < GRID_WIDTH && row < GRID_HEIGHT)
	{
		std::set<PowerUp*>::iterator powerUpItr = m_Grid[column][row].m_PowerUps.find(pPowerUp);
		if (powerUpItr != m_Grid[column][row].m_PowerUps.end())
			m_Grid[column][row].m_PowerUps.erase(powerUpItr);
	}
	pPowerUp = NULL;
}

void Grid::RemovePowerUpFromGrid(PowerUp* pPowerUp)
{
	int minCol = pPowerUp->GetGridMinColumn();
	int minRow= pPowerUp->GetGridMinRow();

	RemovePowerUpFromCell(minCol, minRow, pPowerUp);
	RemovePowerUpFromCell(minCol + 1, minRow, pPowerUp);
	RemovePowerUpFromCell(minCol, minRow + 1, pPowerUp);
	RemovePowerUpFromCell(minCol + 1, minRow + 1, pPowerUp);
	
	pPowerUp = NULL;
}

void Grid::RemoveObstacleFromCell(int column, int row, Obstacle* pObstacle)
{
	if (column < GRID_WIDTH && row < GRID_HEIGHT)
	{
		std::set<Obstacle*>::iterator obstacleItr = m_Grid[column][row].m_Obstacles.find(pObstacle);
		if (obstacleItr != m_Grid[column][row].m_Obstacles.end())
			m_Grid[column][row].m_Obstacles.erase(obstacleItr);
	}

	pObstacle = NULL;
}

void Grid::RemoveObstacleFromGrid(Obstacle* pObstacle)
{
	int minCol = pObstacle->GetGridMinColumn();
	int minRow= pObstacle->GetGridMinRow();

	RemoveObstacleFromCell(minCol, minRow, pObstacle);
	RemoveObstacleFromCell(minCol + 1, minRow, pObstacle);
	RemoveObstacleFromCell(minCol, minRow + 1, pObstacle);
	RemoveObstacleFromCell(minCol + 1, minRow + 1, pObstacle);

	pObstacle = NULL;
}

bool Grid::NeedToUpdatePlayer(int minCol, int minRow, int maxCol, int maxRow)
{
	return (m_Grid[minCol][minRow].m_Player.find(m_pPlayer)
				== m_Grid[minCol][minRow].m_Player.end()) ||
			(m_Grid[maxCol][minRow].m_Player.find(m_pPlayer)
				== m_Grid[maxCol][minRow].m_Player.end()) ||
			(m_Grid[minCol][maxRow].m_Player.find(m_pPlayer)
				== m_Grid[minCol][maxRow].m_Player.end()) ||
			(m_Grid[maxCol][maxRow].m_Player.find(m_pPlayer)
				== m_Grid[maxCol][maxRow].m_Player.end());
}

bool Grid::NeedToUpdateEnemy(int minCol, int minRow, int maxCol, int maxRow, Enemy* pEnemy)
{
	return (m_Grid[minCol][minRow].m_Enemies.find(pEnemy)
				== m_Grid[minCol][minRow].m_Enemies.end()) ||
			(m_Grid[maxCol][minRow].m_Enemies.find(pEnemy)
				== m_Grid[maxCol][minRow].m_Enemies.end()) ||
			(m_Grid[minCol][maxRow].m_Enemies.find(pEnemy)
				== m_Grid[minCol][maxRow].m_Enemies.end()) ||
			(m_Grid[maxCol][maxRow].m_Enemies.find(pEnemy)
				== m_Grid[maxCol][maxRow].m_Enemies.end());
}

bool Grid::NeedToUpdateBullet(int minCol, int minRow, int maxCol, int maxRow, Bullet* pBullet)
{
	return (m_Grid[minCol][minRow].m_Bullets.find(pBullet)
				== m_Grid[minCol][minRow].m_Bullets.end()) ||
			(m_Grid[maxCol][minRow].m_Bullets.find(pBullet)
				== m_Grid[maxCol][minRow].m_Bullets.end()) ||
			(m_Grid[minCol][maxRow].m_Bullets.find(pBullet)
				== m_Grid[minCol][maxRow].m_Bullets.end()) ||
			(m_Grid[maxCol][maxRow].m_Bullets.find(pBullet)
				== m_Grid[maxCol][maxRow].m_Bullets.end());
}

bool Grid::NeedToUpdatePowerUp(int minCol, int minRow, int maxCol, int maxRow, PowerUp* pPowerUp)
{
	return (m_Grid[minCol][minRow].m_PowerUps.find(pPowerUp)
				== m_Grid[minCol][minRow].m_PowerUps.end()) ||
			(m_Grid[maxCol][minRow].m_PowerUps.find(pPowerUp)
				== m_Grid[maxCol][minRow].m_PowerUps.end()) ||
			(m_Grid[minCol][maxRow].m_PowerUps.find(pPowerUp)
				== m_Grid[minCol][maxRow].m_PowerUps.end()) ||
			(m_Grid[maxCol][maxRow].m_PowerUps.find(pPowerUp)
				== m_Grid[maxCol][maxRow].m_PowerUps.end());
}

void Grid::Populate(
	std::vector<Enemy*>& enemies,
	std::vector<Bullet*>& bullets,
	std::vector<PowerUp*>& powerUps,
	std::vector<Obstacle*>& obstacles)
{
	m_Enemies = enemies;
	m_Bullets = bullets;
	m_PowerUps = powerUps;
	m_Obstacles = obstacles;

	int playerMinCol = m_pPlayer->GetX()/CELL_SIZE;
	int playerMinRow = m_pPlayer->GetY()/CELL_SIZE;
	int playerMaxCol = (m_pPlayer->GetX()+m_pPlayer->GetW())/CELL_SIZE;
	int playerMaxRow = (m_pPlayer->GetY()+m_pPlayer->GetH())/CELL_SIZE;

	AddPlayerToGrid(playerMinCol, playerMinRow, playerMaxCol, playerMaxRow);

	for (int i = 0; i < m_Enemies.size(); i++)
	{
		int enemyMinCol = m_Enemies[i]->GetX()/CELL_SIZE;
		int enemyMinRow = m_Enemies[i]->GetY()/CELL_SIZE;
		int enemyMaxCol = (m_Enemies[i]->GetX()+m_Enemies[i]->GetW())/CELL_SIZE;
		int enemyMaxRow = (m_Enemies[i]->GetY()+m_Enemies[i]->GetH())/CELL_SIZE;
	
		AddEnemyToGrid(enemyMinCol, enemyMinRow, enemyMaxCol, enemyMaxRow, m_Enemies[i]);
	}
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		int bulletMinCol = m_Bullets[i]->GetX()/CELL_SIZE;
		int bulletMinRow = m_Bullets[i]->GetY()/CELL_SIZE;
		int bulletMaxCol = (m_Bullets[i]->GetX()+m_Bullets[i]->GetW())/CELL_SIZE;
		int bulletMaxRow = (m_Bullets[i]->GetY()+m_Bullets[i]->GetH())/CELL_SIZE;

		AddBulletToGrid(bulletMinCol, bulletMinRow, bulletMaxCol, bulletMaxRow, m_Bullets[i]);
	}
	for (int i = 0; i < m_PowerUps.size(); i++)
	{
		int powerUpMinCol = m_PowerUps[i]->GetX()/CELL_SIZE;
		int powerUpMinRow = m_PowerUps[i]->GetY()/CELL_SIZE;
		int powerUpMaxCol = (m_PowerUps[i]->GetX()+m_PowerUps[i]->GetW())/CELL_SIZE;
		int powerUpMaxRow = (m_PowerUps[i]->GetY()+m_PowerUps[i]->GetH())/CELL_SIZE;

		AddPowerUpToGrid(powerUpMinCol, powerUpMinRow, powerUpMaxCol, powerUpMaxRow, m_PowerUps[i]);
	}
	for (int i = 0; i < m_Obstacles.size(); i++)
	{
		int obstacleMinCol = m_Obstacles[i]->GetX()/CELL_SIZE;
		int obstacleMinRow = m_Obstacles[i]->GetY()/CELL_SIZE;
		int obstacleMaxCol = (m_Obstacles[i]->GetX()+m_Obstacles[i]->GetW())/CELL_SIZE;
		int obstacleMaxRow = (m_Obstacles[i]->GetY()+m_Obstacles[i]->GetH())/CELL_SIZE;

		AddObstacleToGrid(obstacleMinCol, obstacleMinRow, obstacleMaxCol, obstacleMaxRow, m_Obstacles[i]);
	}
}

void Grid::Update()
{
	int playerMinCol = m_pPlayer->GetX()/CELL_SIZE;
	int playerMinRow = m_pPlayer->GetY()/CELL_SIZE;
	int playerMaxCol = (m_pPlayer->GetX()+m_pPlayer->GetW())/CELL_SIZE;
	int playerMaxRow = (m_pPlayer->GetY()+m_pPlayer->GetH())/CELL_SIZE;
	
	if (NeedToUpdatePlayer(playerMinCol, playerMinRow, playerMaxCol, playerMaxRow))
	{
		RemovePlayerFromGrid();
		AddPlayerToGrid(playerMinCol, playerMinRow, playerMaxCol, playerMaxRow);
	}

	for (int i = 0; i < m_Enemies.size(); i++)
	{
		int enemyMinCol = m_Enemies[i]->GetX()/CELL_SIZE;
		int enemyMinRow = m_Enemies[i]->GetY()/CELL_SIZE;
		int enemyMaxCol = (m_Enemies[i]->GetX()+m_Enemies[i]->GetW())/CELL_SIZE;
		int enemyMaxRow = (m_Enemies[i]->GetY()+m_Enemies[i]->GetH())/CELL_SIZE;
	
		if (NeedToUpdateEnemy(enemyMinCol, enemyMinRow, enemyMaxCol, enemyMaxRow, m_Enemies[i]))
		{
			RemoveEnemyFromGrid(m_Enemies[i]);
			AddEnemyToGrid(enemyMinCol, enemyMinRow, enemyMaxCol, enemyMaxRow, m_Enemies[i]);
		}
	}

	for (int i = 0; i < m_Bullets.size(); i++)
	{
		if (!m_Bullets[i]->IsActive()) continue;
		int bulletMinCol = m_Bullets[i]->GetX()/CELL_SIZE;
		int bulletMinRow = m_Bullets[i]->GetY()/CELL_SIZE;
		int bulletMaxCol = (m_Bullets[i]->GetX()+m_Bullets[i]->GetW())/CELL_SIZE;
		int bulletMaxRow = (m_Bullets[i]->GetY()+m_Bullets[i]->GetH())/CELL_SIZE;
	
		if (NeedToUpdateBullet(bulletMinCol, bulletMinRow, bulletMaxCol, bulletMaxRow, m_Bullets[i]))
		{
			RemoveBulletFromGrid(m_Bullets[i]);
			AddBulletToGrid(bulletMinCol, bulletMinRow, bulletMaxCol, bulletMaxRow, m_Bullets[i]);
		}
	}

	for (int i = 0; i < m_PowerUps.size(); i++)
	{
		int powerUpMinCol = m_PowerUps[i]->GetX()/CELL_SIZE;
		int powerUpMinRow = m_PowerUps[i]->GetY()/CELL_SIZE;
		int powerUpMaxCol = (m_PowerUps[i]->GetX()+m_PowerUps[i]->GetW())/CELL_SIZE;
		int powerUpMaxRow = (m_PowerUps[i]->GetY()+m_PowerUps[i]->GetH())/CELL_SIZE;

		if (NeedToUpdatePowerUp(powerUpMinCol, powerUpMinRow, powerUpMaxCol, powerUpMaxRow, m_PowerUps[i]))
		{
			RemovePowerUpFromGrid(m_PowerUps[i]);
			AddPowerUpToGrid(powerUpMinCol, powerUpMinRow, powerUpMaxCol, powerUpMaxRow, m_PowerUps[i]);
		}
	}
}

void Grid::UpdateObstacles()
{
	for (int i = 0; i < m_Obstacles.size(); i++)
	{
		int obstacleMinCol = m_Obstacles[i]->GetX()/CELL_SIZE;
		int obstacleMinRow = m_Obstacles[i]->GetY()/CELL_SIZE;
		int obstacleMaxCol = (m_Obstacles[i]->GetX()+m_Obstacles[i]->GetW())/CELL_SIZE;
		int obstacleMaxRow = (m_Obstacles[i]->GetY()+m_Obstacles[i]->GetH())/CELL_SIZE;

		RemoveObstacleFromGrid(m_Obstacles[i]);
		AddObstacleToGrid(obstacleMinCol, obstacleMinRow, obstacleMaxCol, obstacleMaxRow, m_Obstacles[i]);
	}
}

void Grid::Close()
{
	m_pPlayer = NULL;
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i] = NULL;
	}
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		m_Bullets[i] = NULL;
	}
	for (int i = 0; i < m_PowerUps.size(); i++)
	{
		m_PowerUps[i] = NULL;
	}
	for (int i = 0; i < m_Obstacles.size(); i++)
	{
		m_Obstacles[i] = NULL;
	}
}