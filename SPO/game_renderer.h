#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "power_up.h"
#include "obstacle.h"

class GameRenderer
{
public:
	GameRenderer(SDL_Rect*, int*, int*);
	~GameRenderer();
	bool Init(
		Player*,
		std::vector<Enemy*>&,
		std::vector<Bullet*>&,
		std::vector<PowerUp*>&,
		std::vector<Obstacle*>&);
	void StartFrame();
	void Render(bool, bool, bool);
	void Close();

private:
	bool BackgroundInit();
	bool MenuInit();
	bool GameOverInit();
	bool PauseInit();
	void RenderEnemies();
	void RenderBullets();
	void RenderPowerUps();
	void RenderObstacles();
	void RenderBackground();
	void RenderHealth();
	void RenderScore(bool);
	void RenderHighScore();
	void RenderFps();
	void RenderMenuScreen();
	void RenderGameOverScreen();
	void RenderPauseScreen();
	void RenderGame();
	SDL_Window* m_pWindow;
	SDL_Rect* m_pCameraRect;
	SDL_Texture* m_pBackground;
	SDL_Texture* m_pMenu;
	SDL_Texture* m_pGameOver;
	SDL_Texture* m_pPause;
	SDL_Renderer* m_pRenderer;
	TTF_Font* m_pMenuFont;
	TTF_Font* m_pFont;
	Player* m_pPlayer;
	std::vector<Enemy*> m_Enemies;
	std::vector<Bullet*> m_Bullets;
	std::vector<PowerUp*> m_PowerUps;
	std::vector<Obstacle*> m_Obstacles;
	int m_FrameStartTime;
	int* m_pScore;
	int* m_pHighScore;
};

