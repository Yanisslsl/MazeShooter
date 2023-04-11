#pragma once
#include "../../include/utils/Vector2.h"
#include "../../include/models/Entity.h"

class Player : public Entity
{
public:
	Player(const Vec2f& _position);
	virtual ~Player() = default;
};
