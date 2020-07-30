#pragma once
#include <vector>
#include "game_object.h"
#include "obstacle.h"

enum EnemyType
{
	Follows,
	Roams
};

class Enemy :
	public GameObject
{
public:
	Enemy(const std::vector<Obstacle*>&);
	~Enemy();
	void Turn(int, int);
	void Update();
	void Resurrect();
	void TakeDamage();

private:
	bool IsAtEdge();
	void FollowPlayer(int, int);
	void Roam();
	bool CollidesWithObstacles();

	std::vector<Obstacle*> m_Obstacles;
	int m_RoamCounter;
	EnemyType m_Type;
};