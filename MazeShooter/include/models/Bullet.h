#pragma once
#include "Entity.h"

class Bullet: public Entity
{
public:
	Bullet(const Vec2f& _position);
	virtual ~Bullet() = default;
};

