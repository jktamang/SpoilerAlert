#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

class MusicManager
{
public:
	MusicManager();
	~MusicManager();
	bool Init();
	void PlayMusic();
	void ToggleAudio();
	void PlayGameOverMusic();
	void StopMusic();
	void PlayPowerUp();
	void PlayDeath();
	void Close();

private:
	Mix_Music* m_pMusic;
	Mix_Music* m_pGameOver;
	Mix_Chunk* m_pPowerUp;
	Mix_Chunk* m_pDeath;
	bool m_IsMuted;
};

