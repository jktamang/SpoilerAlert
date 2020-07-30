#pragma once
#include <SDL.h>
#include "game_object.h"

class Obstacle :
	public GameObject
{
public:
	Obstacle(const SDL_Rect*);
	~Obstacle();
	void Respawn(const SDL_Rect*);
};

