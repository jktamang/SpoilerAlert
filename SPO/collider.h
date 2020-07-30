#pragma once
#include <SDL.h>
#include <stdio.h>

class GameObject;

class Collider
{
public:
	Collider();
	Collider(SDL_Rect);
	~Collider(void);
	bool CollidesWith(const Collider&) const;
	bool CollidesWith(const SDL_Rect*) const;
	void UpdateCollisionRect(int, int);
	void Print(int) const;
    bool IsActive() const;
	void SetActive(bool);
private:
	SDL_Rect m_CollisionRect;
	bool m_IsActive;
};


