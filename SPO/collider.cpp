#include "Collider.h"


Collider::Collider() :
	m_IsActive(true)
{
	m_CollisionRect.x = 0;
	m_CollisionRect.y = 0;
	m_CollisionRect.w = 0;
	m_CollisionRect.h = 0;
}

Collider::Collider(SDL_Rect rect) :
	m_IsActive(true)
{
	m_CollisionRect.x = rect.x;
	m_CollisionRect.y = rect.y;
	m_CollisionRect.w = rect.w;
	m_CollisionRect.h = rect.h;
}


Collider::~Collider(void)
{
}

void Collider::UpdateCollisionRect(int x, int y)
{
	m_CollisionRect.x = x;
	m_CollisionRect.y = y;
}

bool Collider::CollidesWith(const Collider& col) const
{
	return SDL_HasIntersection(
		&m_CollisionRect,
		&col.m_CollisionRect);
}

bool Collider::CollidesWith(const SDL_Rect* colRect) const
{
	return SDL_HasIntersection(
		&m_CollisionRect,
		colRect);
}

void Collider::Print(int num) const
{
	printf("n: %d\n", num);
	printf("x: %d\n", m_CollisionRect.x);
	printf("y: %d\n", m_CollisionRect.y);
}

bool Collider::IsActive() const
{
	return m_IsActive;
}

void Collider::SetActive(bool isActive)
{
	m_IsActive = isActive;
}

//GameObject* Collider::GetParent() const
//{
//	return m_Parent;
//}