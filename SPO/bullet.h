#pragma once
#include "game_object.h"

class Bullet :
	public GameObject
{
public:
	Bullet();
	~Bullet();
	void Shoot(int, int, float);
	void Update();
	void Render(SDL_Renderer*, SDL_Rect);
	bool IsOutOfBounds();
};

