#include "obstacle.h"

Obstacle::Obstacle(const SDL_Rect* pPlayerRect) :
	GameObject(
		rand()%(MAP_WIDTH-OBSTACLE_WIDTH),
		rand()%(MAP_HEIGHT-OBSTACLE_HEIGHT),
		OBSTACLE_WIDTH, OBSTACLE_HEIGHT,
		0.0f, 0.0f, 0.0f,
		OBSTACLE_SPRITE_PATH, 1)
{
	Respawn(pPlayerRect);
	StopMoving();
	StopTurning();

	pPlayerRect = NULL;
}

Obstacle::~Obstacle()
{
}


void Obstacle::Respawn(const SDL_Rect* pPlayerRect)
{
	do
	{
		GameObject::Resurrect(
			rand()%(MAP_WIDTH-OBSTACLE_WIDTH),
			rand()%(MAP_HEIGHT-OBSTACLE_HEIGHT));
	}while (CollidesWith(pPlayerRect));

	pPlayerRect = NULL;
}
