#pragma once
#pragma once
#include "../../include/utils/Vector2.h"
#include "../../include/models/Entity.h"
#include "../../include/Events/Event.h"

class Enemy : public Entity
{
public:
	Enemy(const Vec2f& _position);
	virtual ~Enemy() = default;
	void moveEnemy();
	int Enemy::GetAvailablesPaths();
};
