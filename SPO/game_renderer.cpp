#include <string>
#include <stdio.h>
#include "game_renderer.h"
#include "game_constants.h"

GameRenderer::GameRenderer(
	SDL_Rect* pCameraRect, int* pScore, int* pHighScore) :
		m_pWindow(NULL),
		m_pCameraRect(pCameraRect),
		m_pBackground(NULL),
		m_pRenderer(NULL),
		m_pFont(NULL),
		m_pPlayer(NULL),
		m_FrameStartTime(0),
		m_pScore(pScore),
		m_pHighScore(pHighScore)
{
}

GameRenderer::~GameRenderer()
{
}

bool GameRenderer::BackgroundInit()
{
	SDL_Surface* pSurface = IMG_Load(BACKGROUND_IMAGE_PATH.c_str());
	if (pSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n",
			BACKGROUND_IMAGE_PATH.c_str(), IMG_GetError());
		return false;
    }

	m_pBackground = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
	if (m_pBackground == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n",
			BACKGROUND_IMAGE_PATH.c_str(), SDL_GetError());
    }

    SDL_FreeSurface(pSurface);
	pSurface = NULL;

	return true;
}

bool GameRenderer::MenuInit()
{
	SDL_Surface* pSurface = IMG_Load(MENU_IMAGE_PATH.c_str());
	if (pSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n",
			MENU_IMAGE_PATH.c_str(), IMG_GetError());
		return false;
    }

	m_pMenu = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
	if (m_pMenu == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n",
			MENU_IMAGE_PATH.c_str(), SDL_GetError());
    }

    SDL_FreeSurface(pSurface);
	pSurface = NULL;

	return true;
}

bool GameRenderer::GameOverInit()
{
	SDL_Surface* pSurface = IMG_Load(GAME_OVER_IMAGE_PATH.c_str());
	if (pSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n",
			GAME_OVER_IMAGE_PATH.c_str(), IMG_GetError());
		return false;
    }
	m_pGameOver = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
	if (m_pGameOver == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n",
			GAME_OVER_IMAGE_PATH.c_str(), SDL_GetError());
    }

    SDL_FreeSurface(pSurface);
	pSurface = NULL;

	return true;
}

bool GameRenderer::PauseInit()
{
	SDL_Surface* pSurface = IMG_Load(PAUSE_IMAGE_PATH.c_str());
	if (pSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n",
			PAUSE_IMAGE_PATH.c_str(), IMG_GetError());
		return false;
    }

	m_pPause = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
	if (m_pPause == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n",
			PAUSE_IMAGE_PATH.c_str(), SDL_GetError());
    }

    SDL_FreeSurface(pSurface);
	pSurface = NULL;

	return true;
}

bool GameRenderer::Init(
	Player* pPlayer,
	std::vector<Enemy*>& enemies,
	std::vector<Bullet*>& bullets,
	std::vector<PowerUp*>& powerUps,
	std::vector<Obstacle*>& obstacles)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if (TTF_Init() < 0)
	{
		printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
		return false;
	}

	m_pFont = TTF_OpenFont("Resources\\ARIAL.TTF", 25);
	m_pMenuFont = TTF_OpenFont("Resources\\Fipps-Regular.otf", 25);
	if (m_pMenuFont == NULL || m_pFont == NULL)
	{
		printf("Font could not be opened! TTF_Error: %s\n", TTF_GetError());
	}

	m_pWindow = SDL_CreateWindow("Spoiler Alert", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_pWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_pRenderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
	SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

	if (!BackgroundInit() || !MenuInit() || !GameOverInit() || !PauseInit())
		return false;

	m_pPlayer = pPlayer;
	if (!m_pPlayer->Init(m_pRenderer))
		return false;
	
	m_Enemies = enemies;
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		if (!m_Enemies[i]->Init(m_pRenderer))
			return false;
	}

	m_Bullets = bullets;
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		if (!m_Bullets[i]->Init(m_pRenderer))
			return false;
	}
	m_PowerUps = powerUps;
	for (int i = 0; i < m_PowerUps.size(); i++)
	{
		if (!m_PowerUps[i]->Init(m_pRenderer))
			return false;
	}
	m_Obstacles = obstacles;
	for (int i = 0; i < m_Obstacles.size(); i++)
	{
		if (!m_Obstacles[i]->Init(m_pRenderer))
			return false;
	}

	return true;
}

void GameRenderer::StartFrame()
{
	m_FrameStartTime = SDL_GetTicks();
}

void GameRenderer::RenderBackground()
{
	SDL_RenderCopy(m_pRenderer, m_pBackground, m_pCameraRect, NULL);
}

void GameRenderer::RenderEnemies()
{
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i]->Render(m_pRenderer, *m_pCameraRect);
	}
}

void GameRenderer::RenderBullets()
{
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		m_Bullets[i]->Render(m_pRenderer, *m_pCameraRect);
	}
}

void GameRenderer::RenderPowerUps()
{
	for (int i = 0; i < m_PowerUps.size(); i++)
	{
		m_PowerUps[i]->Render(m_pRenderer, *m_pCameraRect);
	}
}

void GameRenderer::RenderObstacles()
{
	for (int i = 0; i < m_Obstacles.size(); i++)
	{
		m_Obstacles[i]->Render(m_pRenderer, *m_pCameraRect);
	}
}

void GameRenderer::RenderHealth()
{
	std::string healthStr = "HP";
	int health = m_pPlayer->GetHealth();

	SDL_Surface* pSurface = TTF_RenderText_Solid(m_pFont, healthStr.c_str(), BLACK);
	SDL_Texture * pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(pTexture, NULL, NULL, &texW, &texH);
	SDL_Rect dstRect = {5, 0, texW, texH};
	SDL_Rect outerBarRect = {0, 0, texW + 120, 30};
	SDL_Rect innerBarRect = {texW + 10, 5, health, 20};

	SDL_SetRenderDrawColor(m_pRenderer, 0xBB, 0xBB, 0xBB, 0xFF);
    SDL_RenderFillRect(m_pRenderer, &outerBarRect);

	if (m_pPlayer->GetHealth() > 50)
		SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0xFF, 0x00, 0xFF);
	else if (m_pPlayer->GetHealth() < 25)
		SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0x00, 0x00, 0xFF);
	else
		SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0xFF, 0x00, 0xFF);

    SDL_RenderFillRect(m_pRenderer, &innerBarRect);

	SDL_RenderCopy(m_pRenderer, pTexture, NULL, &dstRect);

	SDL_DestroyTexture(pTexture);
	SDL_FreeSurface(pSurface);
	pSurface = NULL;
	pTexture = NULL;
}

void GameRenderer::RenderScore(bool isGameOver)
{
	std::string scoreStr = "Score: ";
	scoreStr += std::to_string(static_cast<long long>(*m_pScore));

	SDL_Color color = (isGameOver) ? BLACK : WHITE;

	SDL_Surface* pSurface;
	if (isGameOver)
		pSurface= TTF_RenderText_Solid(m_pMenuFont, scoreStr.c_str(), color);
	else
		pSurface= TTF_RenderText_Solid(m_pFont, scoreStr.c_str(), color);

	SDL_Texture * pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
	int texW = 0, texH = 0;
	SDL_QueryTexture(pTexture, NULL, NULL, &texW, &texH);
	SDL_Rect dstRect = {(SCREEN_WIDTH/2) - (texW/2), 0, texW, texH};
	if (isGameOver)
		dstRect.y = SCREEN_HEIGHT/2;

	if (!isGameOver)
	{
		SDL_SetRenderDrawColor(m_pRenderer, 0x88, 0x14, 0x00, 0xFF);
		SDL_RenderFillRect(m_pRenderer, &dstRect);
	}

	SDL_RenderCopy(m_pRenderer, pTexture, NULL, &dstRect);

	SDL_DestroyTexture(pTexture);
	SDL_FreeSurface(pSurface);
	pSurface = NULL;
	pTexture = NULL;
}

void GameRenderer::RenderHighScore()
{
	std::string scoreStr = "High Score: ";
	scoreStr += std::to_string(static_cast<long long>(*m_pHighScore));

	SDL_Surface* pSurface= TTF_RenderText_Solid(m_pMenuFont, scoreStr.c_str(), BLACK);

	SDL_Texture * pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
	int texW = 0, texH = 0;
	SDL_QueryTexture(pTexture, NULL, NULL, &texW, &texH);
	SDL_Rect dstRect = {
		(SCREEN_WIDTH/2) - (texW/2),
		(SCREEN_HEIGHT/2) + (texH/2),
		texW, texH};

	SDL_RenderCopy(m_pRenderer, pTexture, NULL, &dstRect);

	SDL_DestroyTexture(pTexture);
	SDL_FreeSurface(pSurface);
	pSurface = NULL;
	pTexture = NULL;
}

void GameRenderer::RenderFps()
{
	while(SDL_GetTicks() - m_FrameStartTime < 1000/FPS);
	float currentFps = 1000.0f / float(SDL_GetTicks() - m_FrameStartTime);
	std::string fpsStr = "FPS: ";
	fpsStr += std::to_string(static_cast<long long>(currentFps));

	SDL_Color color;
	if (currentFps > 45.0)		color = GREEN;
	else if (currentFps < 30.0) color = RED;
	else						color = YELLOW;

	SDL_Surface* pSurface = TTF_RenderText_Solid(m_pFont, fpsStr.c_str(), color);
	SDL_Texture * pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(pTexture, NULL, NULL, &texW, &texH);
	SDL_Rect dstRect = {SCREEN_WIDTH-texW, 0, texW, texH};

	SDL_RenderCopy(m_pRenderer, pTexture, NULL, &dstRect);
	SDL_DestroyTexture(pTexture);
	SDL_FreeSurface(pSurface);
	pSurface = NULL;
	pTexture = NULL;
}

void GameRenderer::RenderMenuScreen()
{
	SDL_RenderCopy(m_pRenderer, m_pMenu, NULL, NULL);
}

void GameRenderer::RenderGameOverScreen()
{
	SDL_RenderCopy(m_pRenderer, m_pGameOver, NULL, NULL);
	RenderHighScore();
}

void GameRenderer::RenderPauseScreen()
{
	SDL_RenderCopy(m_pRenderer, m_pPause, NULL, NULL);
}

void GameRenderer::RenderGame()
{
	RenderBackground();
	RenderEnemies();
	RenderBullets();
	RenderPowerUps();
	RenderObstacles();

	m_pPlayer->Render(m_pRenderer, *m_pCameraRect);
	RenderHealth();
}

void GameRenderer::Render(bool isGameOver, bool isInMenu, bool isPaused)
{
	SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(m_pRenderer);

	if (isInMenu)
	{
		RenderMenuScreen();
	}
	else if (isPaused)
	{
		RenderPauseScreen();
	}
	else if (!isGameOver)
	{
		RenderGame();
	}
	else
	{
		RenderGameOverScreen();
	}

	if (!isInMenu) RenderScore(isGameOver);
	RenderFps();

	SDL_RenderPresent(m_pRenderer);
}

void GameRenderer::Close()
{
	m_pPlayer->Close();
	m_pPlayer = NULL;

	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i]->Close();
		m_Enemies[i] = NULL;
	}
	for (int i = 0; i < m_Bullets.size(); i++)
	{
		m_Bullets[i]->Close();
		m_Bullets[i] = NULL;
	}
	for (int i = 0; i < m_PowerUps.size(); i++)
	{
		m_PowerUps[i]->Close();
		m_PowerUps[i] = NULL;
	}
	for (int i = 0; i < m_Obstacles.size(); i++)
	{
		m_Obstacles[i]->Close();
		m_Obstacles[i] = NULL;
	}

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyTexture(m_pBackground);
	SDL_DestroyTexture(m_pMenu);
	SDL_DestroyTexture(m_pGameOver);
	SDL_DestroyTexture(m_pPause);
	TTF_CloseFont(m_pFont);
	TTF_CloseFont(m_pMenuFont);

	m_pCameraRect = NULL;
	m_pWindow = NULL;
	m_pRenderer = NULL;
	m_pBackground = NULL;
	m_pMenu = NULL;
	m_pGameOver = NULL;
	m_pPause = NULL;
	m_pMenuFont = NULL;
	m_pFont = NULL;
	m_pScore = NULL;
	m_pHighScore = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

