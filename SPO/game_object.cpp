#include <cmath>
#include <SDL_image.h>
#include "game_object.h"

GameObject::GameObject(
	int x, int y, int w, int h, float angle,
	float rotationSpeed, float moveSpeed,
	std::string spritePath, int health) :
	m_Angle(angle),
	m_RotationSpeed(rotationSpeed), m_MoveSpeed(moveSpeed),
	m_CurrentRotationSpeed(0.0f),
	m_CurrentMoveSpeedX(0.0f),
	m_CurrentMoveSpeedY(0.0f),
	m_pTexture(NULL),
	m_SpritePath(spritePath),
	m_Health(health),
	m_MaxHealth(health),
	m_IsActive(true),
	m_CanMoveX(true),
	m_CanMoveY(true),
	m_Updated(false)
{
	m_Rect.x = x;
	m_Rect.y = y;
	m_Rect.w = w;
	m_Rect.h = h;
}

GameObject::~GameObject()
{
}

bool GameObject::Init(SDL_Renderer* pRenderer)
{	
	SDL_Surface* pSurface = IMG_Load(m_SpritePath.c_str());
	if (pSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", m_SpritePath.c_str(), IMG_GetError());
		return false;
    }
	
	SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0xFF, 0x00, 0xFF));

	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (m_pTexture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", m_SpritePath.c_str(), SDL_GetError());
    }

    SDL_FreeSurface(pSurface);
	pSurface = NULL;

	return true;
}

void GameObject::SetCanMoveX(bool canMoveX)
{
	m_CanMoveX = canMoveX;
}

void GameObject::SetCanMoveY(bool canMoveY)
{
	m_CanMoveY = canMoveY;
}

bool GameObject::CanMoveX()
{
	return m_CanMoveX;
}

bool GameObject::CanMoveY()
{
	return m_CanMoveY;
}

SDL_Rect GameObject::TryMoveX()
{
	SDL_Rect tryRect = m_Rect;
	float xMovement = m_CurrentMoveSpeedX * cos(m_Angle*PI/180);
	if (float(tryRect.x) + xMovement <= 0.0f)
		tryRect.x = 0;
	else if (tryRect.x + xMovement + tryRect.w >= MAP_WIDTH)
		tryRect.x = MAP_WIDTH - tryRect.w;
	else
		tryRect.x += (int)xMovement;
	return tryRect;
}

SDL_Rect GameObject::TryMoveY()
{
	SDL_Rect tryRect = m_Rect;
	float yMovement = m_CurrentMoveSpeedY * sin(m_Angle*PI/180);
	if (tryRect.y + yMovement <= 0.0f)
		tryRect.y = 0;
	else if (tryRect.y + yMovement + tryRect.h >= MAP_HEIGHT)
		tryRect.y = MAP_HEIGHT - tryRect.h;
	else
		tryRect.y += (int)yMovement;
	return tryRect;
}

void GameObject::MoveX()
{
	float xMovement = m_CurrentMoveSpeedX * cos(m_Angle*PI/180);
	if (m_Rect.x + xMovement <= 0.0f)
		m_Rect.x = 0;
	else if (m_Rect.x + xMovement + m_Rect.w >= MAP_WIDTH)
		m_Rect.x = MAP_WIDTH - m_Rect.w;
	else
		m_Rect.x += int(xMovement);
}

void GameObject::MoveY()
{
	float yMovement = m_CurrentMoveSpeedY * sin(m_Angle*PI/180);
	if (m_Rect.y + yMovement <= 0.0f)
		m_Rect.y = 0;
	else if (m_Rect.y + yMovement + m_Rect.h >= MAP_HEIGHT)
		m_Rect.y = MAP_HEIGHT - m_Rect.h;
	else
		m_Rect.y += (int)yMovement;
}

void GameObject::MoveForward()
{
	m_CurrentMoveSpeedX = m_MoveSpeed;
	m_CurrentMoveSpeedY = m_MoveSpeed;
}

void GameObject::MoveBackward()
{
	m_CurrentMoveSpeedX = -m_MoveSpeed;
	m_CurrentMoveSpeedY = -m_MoveSpeed;
}

void GameObject::StopMoving()
{
	m_CurrentMoveSpeedX = m_CurrentMoveSpeedY = 0;
}

void GameObject::TurnLeft()
{
	m_CurrentRotationSpeed = -m_RotationSpeed;
}

void GameObject::TurnRight()
{
	m_CurrentRotationSpeed = m_RotationSpeed;
}

void GameObject::StopTurning()
{
	m_CurrentRotationSpeed = 0;
}

int GameObject::GetX() const
{
	return m_Rect.x;
}

int GameObject::GetY() const
{
	return m_Rect.y;
}

int GameObject::GetW() const
{
	return m_Rect.w;
}

int GameObject::GetH() const
{
	return m_Rect.h;
}

void GameObject::Turn()
{
	m_Angle = fmod(m_Angle + m_CurrentRotationSpeed + 360, 360);
}

void GameObject::Update()
{	
	if (m_Updated) return;
	if (m_CanMoveX) MoveX();
	if (m_CanMoveY) MoveY();
	m_Updated = true;
}

void GameObject::FinalizeUpdate()
{
	m_CanMoveX = true;
	m_CanMoveY = true;
	m_Updated = false;
}

bool GameObject::IsInvisible(SDL_Rect& cameraRect)
{
	return !SDL_HasIntersection(&m_Rect, &cameraRect);
}

void GameObject::Render(SDL_Renderer* pRenderer, SDL_Rect cameraRect)
{
	if (IsInvisible(cameraRect) || !IsActive()) return;
	SDL_Rect renderRect = {m_Rect.x - cameraRect.x, m_Rect.y - cameraRect.y, m_Rect.w, m_Rect.h};
	SDL_RenderCopyEx(pRenderer, m_pTexture, NULL, &renderRect, m_Angle, NULL, SDL_FLIP_NONE);
}

void GameObject::Close()
{
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = NULL;
}

bool GameObject::CollidesWith(const SDL_Rect* pColRect)
{
	return SDL_HasIntersection(&m_Rect, pColRect) == 1;
}

void GameObject::SetCurrentMoveSpeedX(float moveSpeedX)
{
	m_CurrentMoveSpeedX = moveSpeedX;
}

void GameObject::SetCurrentMoveSpeedY(float moveSpeedY)
{
	m_CurrentMoveSpeedY = moveSpeedY;
}

float GameObject::GetCurrentMoveSpeedX()
{
	return m_CurrentMoveSpeedX;
}

float GameObject::GetCurrentMoveSpeedY()
{
	return m_CurrentMoveSpeedY;
}

float GameObject::GetAngle()
{
	return m_Angle;
}

const SDL_Rect* GameObject::GetRect()
{
	return &m_Rect;
}

void GameObject::Resurrect(int x, int y)
{
	m_Rect.x = x;
	m_Rect.y = y;
	m_Health = m_MaxHealth;
}

void GameObject::SetSprite(std::string spritePath)
{
	m_SpritePath = spritePath;
}

void GameObject::SetRotationSpeed(float rotationSpeed)
{
	m_RotationSpeed = rotationSpeed;
}

void GameObject::TakeDamage()
{
	m_Health--;
}

int GameObject::GetHealth() const
{
	return m_Health;
}

void GameObject::SetAngle(float angle)
{
	m_Angle = angle;
}

void GameObject::SetActive(bool isActive)
{
	m_IsActive = isActive;
}

bool GameObject::IsActive()
{
	return m_IsActive;
}

int GameObject::GetGridMinColumn() const
{
	return m_GridMinColumn;
}

int GameObject::GetGridMinRow() const
{
	return m_GridMinRow;
}

void GameObject::SetGridMinColumn(int minCol)
{
	m_GridMinColumn = minCol;
}

void GameObject::SetGridMinRow(int minRow)
{
	m_GridMinRow = minRow;
}

void GameObject::SetHealth(int newHealth)
{
	if (newHealth > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
	else
	{
		m_Health = newHealth;
	}
}