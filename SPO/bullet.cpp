#include "bullet.h"

Bullet::Bullet() : 
	GameObject(0, 0,
			BULLET_WIDTH, BULLET_HEIGHT, 0.0f,
			0.0f, BULLET_MOVE_SPEED, BULLET_SPRITE_PATH,
			BULLET_HEALTH)
{
	MoveForward();
	SetActive(false);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	MoveX();
	MoveY();
	if (IsOutOfBounds())
		SetActive(false);
}

void Bullet::Render(SDL_Renderer* pRenderer, SDL_Rect cameraRect)
{
	GameObject::Render(pRenderer, cameraRect);
}

void Bullet::Shoot(int x, int y, float angle)
{
	SetActive(true);
	Resurrect(x, y);
	SetAngle(angle);
}

bool Bullet::IsOutOfBounds()
{
	return GetX() <= 0 ||
		GetX() >= MAP_WIDTH - BULLET_WIDTH ||
		GetY() <= 0 ||
		GetY() >= MAP_HEIGHT - BULLET_HEIGHT;
}
