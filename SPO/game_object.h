#pragma once
#include <SDL.h>
#include <string>
#include "game_constants.h"

class GameObject
{
public:
	GameObject(int, int, int, int, float, float, float, std::string, int);
	~GameObject();
	bool Init(SDL_Renderer*);
	void MoveForward();
	void MoveBackward();
	void TurnLeft();
	void TurnRight();
	void StopMoving();
	void StopTurning();
	void Turn();
	void SetCanMoveX(bool);
	void SetCanMoveY(bool);
	bool CanMoveX();
	bool CanMoveY();
	void MoveX();
	void MoveY();
	void Update();
	void FinalizeUpdate();
	void Render(SDL_Renderer*, SDL_Rect);
	void Close();
	int GetX() const;
	int GetY() const;
	int GetW() const;
	int GetH() const;
	bool CollidesWith(const SDL_Rect*);
	void Resurrect(int, int);
	void TakeDamage();
	int GetHealth() const;
	float GetAngle();
	const SDL_Rect* GetRect();
	bool IsInvisible(SDL_Rect&);
	void SetActive(bool);
	bool IsActive();
	int GetGridMinColumn() const;
	int GetGridMinRow() const;
	void SetGridMinColumn(int);
	void SetGridMinRow(int);
	SDL_Rect TryMoveX();
	SDL_Rect TryMoveY();

protected:
	void SetCurrentMoveSpeedX(float);
	void SetCurrentMoveSpeedY(float);
	float GetCurrentMoveSpeedX();
	float GetCurrentMoveSpeedY();
	void SetRotationSpeed(float);
	void UpdateCollider();
	void SetSprite(std::string);
	void SetAngle(float);
	void SetHealth(int);

private:
	SDL_Rect m_Rect;
	float m_Angle;
	float m_RotationSpeed;
	const float m_MoveSpeed;
	float m_CurrentMoveSpeedX;
	float m_CurrentMoveSpeedY;
	float m_CurrentRotationSpeed;
	SDL_Texture* m_pTexture;
	std::string m_SpritePath;
	int m_Health;
	int m_MaxHealth;
	bool m_IsActive;
	int m_GridMinColumn;
	int m_GridMinRow;
	bool m_CanMoveX;
	bool m_CanMoveY;
	bool m_Updated;
};