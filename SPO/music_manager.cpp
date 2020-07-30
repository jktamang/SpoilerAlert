#include <stdio.h>
#include "music_manager.h"
#include "game_constants.h"

MusicManager::MusicManager() :
	m_pMusic(NULL),
	m_pGameOver(NULL),
	m_pPowerUp(NULL),
	m_pDeath(NULL),
	m_IsMuted(false)
{
}

MusicManager::~MusicManager()
{
}

bool MusicManager::Init()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    m_pMusic = Mix_LoadMUS(BACKGROUND_MUSIC_PATH.c_str());
	m_pGameOver = Mix_LoadMUS(GAME_OVER_MUSIC_PATH.c_str());
	m_pPowerUp = Mix_LoadWAV(POWER_UP_SOUND_PATH.c_str());
	m_pDeath = Mix_LoadWAV(DEATH_SOUND_PATH.c_str());

    if (m_pMusic == NULL || m_pGameOver == NULL || m_pPowerUp == NULL || m_pDeath == NULL)
    {
        printf("Failed to load audio! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
	return true;
}

void MusicManager::PlayMusic()
{
	if (m_IsMuted)
		return;

	if (Mix_PlayingMusic() != 0)
    {
		Mix_HaltMusic();
	}
	Mix_PlayMusic(m_pMusic, -1);
}

void MusicManager::ToggleAudio()
{
	if (m_IsMuted)
    {
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
	m_IsMuted = !m_IsMuted;
}

void MusicManager::PlayGameOverMusic()
{
	if (m_IsMuted)
		return;

	if (Mix_PlayingMusic() != 0)
    {
		Mix_HaltMusic();
	}
	Mix_PlayMusic(m_pGameOver, 1);
}

void MusicManager::PlayPowerUp()
{
	if (m_IsMuted)
		return;

	Mix_PlayChannel(-1, m_pPowerUp, 0);
}

void MusicManager::PlayDeath()
{
	if (m_IsMuted)
		return;

	Mix_PlayChannel(-1, m_pDeath, 0);
}

void MusicManager::StopMusic()
{
	Mix_HaltMusic();
}

void MusicManager::Close()
{
	Mix_FreeMusic(m_pMusic);
	Mix_FreeMusic(m_pGameOver);
	Mix_FreeChunk(m_pPowerUp);
	Mix_FreeChunk(m_pDeath);

	m_pMusic = NULL;
	m_pGameOver = NULL;
	m_pPowerUp = NULL;
	m_pDeath = NULL;

	Mix_Quit();
}
