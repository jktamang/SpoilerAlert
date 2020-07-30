#pragma once
#include <stdio.h>
#include <SDL.h>
#include <vector>
#include <set>
#include <fstream>
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "power_up.h"
#include "obstacle.h"
#include "grid.h"
#include "game_renderer.h"
#include "music_manager.h"

class Game
{
public:
	Game();
	~Game();
	bool Init();
	void StartFrame();
	bool ProcessInput();
	void Update();
	void Render();
	void Close();

private:
	bool ProcessGameOverInput(SDL_Keycode);
	void ProcessMenuInput(SDL_Keycode);
	void ProcessPauseInput(SDL_Keycode);
	void ProcessGameInputDown(SDL_Keycode);
	void ProcessGameInputUp(SDL_Keycode);
	void ProcessGameOver();
	void ProcessPause();
	void InitHighScore();
	void UpdateHighScore();
	void Reset();
	void ShootBullet(float);
	void Shoot();
	void UpdatePlayer();
	void UpdateCamera();
	void UpdateEnemies();
	void UpdateEnemies(
		const std::set<Enemy*>&,
		const std::set<Obstacle*>&,
		bool, bool);
	void UpdateBullets();
	void UpdateBullets(
		const std::set<Bullet*>&,
		const std::set<Enemy*>&,
		const std::set<Obstacle*>&);
	void UpdatePowerUps();
	void UpdatePowerUps(const std::set<PowerUp*>&, bool);
	void FinalizeUpdate();

	Mix_Music* m_pMusic;
	MusicManager m_MusicManager;
	GameRenderer m_Renderer;
	SDL_Rect m_CameraRect;
	Player m_Player;
	std::vector<Enemy*> m_Enemies;
	std::vector<Bullet*> m_Bullets;
	std::vector<PowerUp*> m_PowerUps;
	std::vector<Obstacle*> m_Obstacles;
	Grid m_Grid;
	bool m_IsGameOver;
	bool m_IsInMenu;
	bool m_IsPaused;
	int m_Score;
	int m_HighScore;
	std::fstream m_ScoreFile;
};
