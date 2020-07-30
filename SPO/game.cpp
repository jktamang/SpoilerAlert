#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "game.h"
#include "game_constants.h"
#include "game_helpers.h"

Game::Game() :
	m_pMusic(NULL),
	m_Renderer(&m_CameraRect, &m_Score, &m_HighScore),
	m_Player(),
	m_IsGameOver(false),
	m_IsInMenu(true),
	m_IsPaused(false),
	m_Score(0),
	m_HighScore(0),
	m_Grid(&m_Player)
{
	m_CameraRect.x = 0;
	m_CameraRect.y = 0;
	m_CameraRect.w = SCREEN_WIDTH;
	m_CameraRect.h = SCREEN_HEIGHT;

	srand((unsigned int)time(NULL));
	
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		m_Obstacles.push_back(new Obstacle(m_Player.GetRect()));
	}

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		m_Enemies.push_back(new Enemy(m_Obstacles));
	}

	for (int i = 0; i < BULLET_COUNT; i++)
	{
		m_Bullets.push_back(new Bullet());
	}
	
	for (int i = 0; i < BUCKET_COUNT; i++)
	{
		m_PowerUps.push_back(
			new PowerUp(POWER_UP_SPRITE_PATH1, Bucket));
	}
	
	for (int i = 0; i < SODA_COUNT; i++)
	{
		m_PowerUps.push_back(
			new PowerUp(POWER_UP_SPRITE_PATH2, Soda));
	}
}

Game::~Game()
{
}

void Game::InitHighScore()
{
	m_ScoreFile.open(SCORE_FILE_PATH, std::ios::in);

	if (!m_ScoreFile || m_ScoreFile.peek() == std::fstream::traits_type::eof())
		m_HighScore = 0;
	else
		m_ScoreFile >> m_HighScore;

	m_ScoreFile.close();
}

bool Game::Init()
{
	InitHighScore();
	m_Grid.Populate(m_Enemies, m_Bullets, m_PowerUps, m_Obstacles);
	return m_Renderer.Init(&m_Player, m_Enemies, m_Bullets, m_PowerUps, m_Obstacles) &&
		m_MusicManager.Init();
}

void Game::StartFrame()
{
	m_Renderer.StartFrame();
}

void Game::Reset()
{
	m_IsGameOver = false;
	m_MusicManager.PlayMusic();
	m_Score = 0;

	m_Player.Resurrect(
		rand()%(MAP_WIDTH - PLAYER_WIDTH),
		rand()%(MAP_HEIGHT - PLAYER_HEIGHT));

	for (int i = 0; i < m_Obstacles.size(); i++)
	{
		m_Obstacles[i]->Respawn(m_Player.GetRect());
	}
	m_Grid.UpdateObstacles();

	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i]->Resurrect();
	}

	for (int i = 0; i < m_Bullets.size(); i++)
	{
		m_Bullets[i]->SetActive(false);
	}
}

void Game::UpdateHighScore()
{
	if (m_Score > m_HighScore)
	{
		m_HighScore = m_Score;

		m_ScoreFile.open(SCORE_FILE_PATH, std::ios::out);
		m_ScoreFile << m_HighScore;
		m_ScoreFile.close();
	}
}

void Game::ProcessGameOver()
{
	m_IsGameOver = true;
	m_MusicManager.PlayDeath();
	m_MusicManager.PlayGameOverMusic();
	UpdateHighScore();
}

void Game::ProcessPause()
{
	m_Player.StopMoving();
	m_Player.StopShooting();
	m_Player.StopTurning();
	m_IsPaused = true;
}

bool Game::ProcessGameOverInput(SDL_Keycode key)
{
	switch(key)
	{
		case SDLK_ESCAPE:
			return true;
		case SDLK_RETURN:
			Reset();
		default:
			break;
	}
	return false;
}

void Game::ProcessMenuInput(SDL_Keycode key)
{
	switch(key)
	{
		case SDLK_RETURN:
			m_IsInMenu = false;
			m_MusicManager.PlayMusic();
			break;
		default:
			break;
	}
}

void Game::ProcessPauseInput(SDL_Keycode key)
{
	switch(key)
	{
		case SDLK_ESCAPE:
			m_IsPaused = false;
			break;
		case SDLK_m:
			m_MusicManager.ToggleAudio();
			break;
		default:
			break;
	}
}

void Game::ProcessGameInputDown(SDL_Keycode key)
{
	switch(key)
	{
		case SDLK_UP:
			m_Player.MoveForward();
			break;
		case SDLK_DOWN:
			m_Player.MoveBackward();
			break;
		case SDLK_LEFT:
			m_Player.TurnLeft();
			break;
		case SDLK_RIGHT:
			m_Player.TurnRight();
			break;
		case SDLK_q:
			m_Player.StartShooting();
			break;
		case SDLK_a:
			m_Player.StartShooting();
			break;
		case SDLK_ESCAPE:
			ProcessPause();
			break;
		default:
			break;
	}
}

void Game::ProcessGameInputUp(SDL_Keycode key)
{
	switch(key)
	{
		case SDLK_UP:
			m_Player.StopMoving();
			break;
		case SDLK_DOWN:
			m_Player.StopMoving();
			break;
		case SDLK_LEFT:
			m_Player.StopTurning();
			break;
		case SDLK_RIGHT:
			m_Player.StopTurning();
			break;
		case SDLK_q:
			m_Player.StopShooting();
			break;
		case SDLK_a:
			m_Player.StopShooting();
			break;
		default:
			break;
	}
}

bool Game::ProcessInput()
{
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0)
    {
		if (e.type == SDL_QUIT)
		{
			return true;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			if (m_IsGameOver)
			{
				if (ProcessGameOverInput(e.key.keysym.sym))
					return true;
			}
			else if (m_IsInMenu)
			{
				ProcessMenuInput(e.key.keysym.sym);
			}
			else if (m_IsPaused)
			{
				ProcessPauseInput(e.key.keysym.sym);
			}
			else
			{
				ProcessGameInputDown(e.key.keysym.sym);
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			if (!m_IsGameOver && !m_IsPaused && !m_IsInMenu)
			{
				ProcessGameInputUp(e.key.keysym.sym);
			}
		}
	}
	return false;
}

void Game::ShootBullet(float shootingAngle)
{
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		if (!m_Bullets[i]->IsActive())
		{
			m_Bullets[i]->Shoot(
				m_Player.GetX(), m_Player.GetY(),
				shootingAngle);
			break;
		}
	}
}

void Game::Shoot()
{
	if (m_Player.HasPowerUp())
	{
		ShootBullet(fmod((m_Player.GetAngle() + 20), 360.0f));
		ShootBullet(fmod((m_Player.GetAngle() - 20 + 360), 360));
	}
	ShootBullet(m_Player.GetAngle());
}

void Game::UpdatePlayer()
{
	int playerMinColumn = m_Player.GetGridMinColumn();
	int playerMinRow = m_Player.GetGridMinRow();
	int playerMaxColumn = playerMinColumn + 1;
	int playerMaxRow = playerMinRow + 1;
	m_Player.Turn();

	CheckPlayerObstacleCollision(
		&m_Player,
		m_Grid.GetObstaclesInCell(playerMinColumn, playerMinRow));

	if (playerMinColumn < GRID_WIDTH && playerMaxRow < GRID_HEIGHT)
	{
		CheckPlayerObstacleCollision(
			&m_Player,
			m_Grid.GetObstaclesInCell(playerMinColumn, playerMaxRow));
	}

	if (playerMaxColumn < GRID_WIDTH && playerMinRow < GRID_HEIGHT)
	{
		CheckPlayerObstacleCollision(
			&m_Player,
			m_Grid.GetObstaclesInCell(playerMaxColumn, playerMinRow));
	}

	if (playerMaxColumn < GRID_WIDTH && playerMaxRow < GRID_HEIGHT)
	{
		CheckPlayerObstacleCollision(
			&m_Player,
			m_Grid.GetObstaclesInCell(playerMaxColumn, playerMaxRow));
	}

	m_Player.Update();
	if (m_Player.IsShooting()) Shoot();
}

void Game::UpdateCamera()
{
	const int playerX = m_Player.GetX();
	const int playerY = m_Player.GetY();

	m_CameraRect.x = playerX - (SCREEN_WIDTH / 2);
	m_CameraRect.y = playerY - (SCREEN_HEIGHT / 2);
	
	if (m_CameraRect.x < 0)
		m_CameraRect.x = 0;
	else if (m_CameraRect.x + SCREEN_WIDTH > MAP_WIDTH)
		m_CameraRect.x = MAP_WIDTH - SCREEN_WIDTH;

	if (m_CameraRect.y < 0)
		m_CameraRect.y = 0;
	else if (m_CameraRect.y + SCREEN_HEIGHT > MAP_HEIGHT)
		m_CameraRect.y = MAP_HEIGHT - SCREEN_HEIGHT;
}

void Game::UpdateEnemies()
{
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			UpdateEnemies(
				m_Grid.GetEnemiesInCell(i, j),
				m_Grid.GetObstaclesInCell(i, j),
				m_Grid.IsPlayerInCell(i, j),
				m_Player.IsInvincible());
		}
	}
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i]->Update();
	}
}

void Game::UpdateEnemies(
	const std::set<Enemy*>& enemies,
	const std::set<Obstacle*>& obstacles,
	bool isPlayerInCell,
	bool isPlayerInvincible)
{
	std::set<Enemy*>::iterator enemy;

	for (enemy = enemies.begin(); enemy != enemies.end() ; enemy++)
	{
		(*enemy)->Turn(m_Player.GetX(), m_Player.GetY());

		CheckEnemyEnemyCollision(enemy, enemies);
		
		if ((*enemy)->CanMoveX() || (*enemy)->CanMoveY())
		{
			CheckEnemyObstacleCollision(*enemy, obstacles);
		}

		CheckPlayerEnemyCollision(&m_Player, *enemy, isPlayerInCell, isPlayerInvincible);
	}
}

void Game::UpdateBullets()
{
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			UpdateBullets(
				m_Grid.GetBulletsInCell(i, j),
				m_Grid.GetEnemiesInCell(i, j),
				m_Grid.GetObstaclesInCell(i, j));
		}
	}
}

void Game::UpdateBullets(
	const std::set<Bullet*>& bullets,
	const std::set<Enemy*>& enemies,
	const std::set<Obstacle*>& obstacles)
{
	std::set<Bullet*>::iterator bullet;

	for (bullet = bullets.begin(); bullet != bullets.end() ; bullet++)
	{
		if (!(*bullet)->IsActive()) continue;
		(*bullet)->Update();

		if (CheckBulletEnemyCollision(*bullet, enemies))
			m_Score++;

		if (!(*bullet)->IsActive()) continue;
		CheckBulletObstacleCollision(*bullet, obstacles);
	}
}

void Game::UpdatePowerUps()
{
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			UpdatePowerUps(
				m_Grid.GetPowerUpsInCell(i, j),
				m_Grid.IsPlayerInCell(i, j));
		}
	}
}

void Game::UpdatePowerUps(
	const std::set<PowerUp*>& powerUps, bool isPlayerInCell)
{
	std::set<PowerUp*>::iterator powerUp;

	for (powerUp = powerUps.begin(); powerUp != powerUps.end() ; powerUp++)
	{
		(*powerUp)->Update();

		if (!(*powerUp)->IsActive() || !isPlayerInCell)
				continue;

		if ((*powerUp)->CollidesWith(m_Player.GetRect()))
		{
			(*powerUp)->ApplyPowerUp(&m_Player);
			m_MusicManager.PlayPowerUp();
			break;
		}
	}
}

void Game::FinalizeUpdate()
{
	m_Player.FinalizeUpdate();
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i]->FinalizeUpdate();
	}
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		m_Bullets[i]->FinalizeUpdate();
	}
	for (int i = 0; i < m_PowerUps.size(); i++)
	{
		m_PowerUps[i]->FinalizeUpdate();
	}

	if (m_Player.GetHealth() == 0)
	{
		ProcessGameOver();
	}
}

void Game::Update()
{
	if (!m_IsGameOver && !m_IsInMenu && !m_IsPaused)
	{
		UpdatePlayer();
		UpdateCamera();
		m_Grid.Update();
		UpdateBullets();
		UpdateEnemies();
		UpdatePowerUps();
		FinalizeUpdate();
	}
}

void Game::Render()
{
	m_Renderer.Render(m_IsGameOver, m_IsInMenu, m_IsPaused);
}

void Game::Close()
{
	m_MusicManager.Close();
	m_Renderer.Close();
}
