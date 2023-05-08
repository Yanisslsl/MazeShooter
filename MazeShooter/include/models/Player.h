#pragma once
#include "../../include/utils/Vector2.h"
#include "../../include/models/Entity.h"
#include "../../include/Events/Event.h"

class Player : public Entity
{
public:
	Player(const Vec2f& _position);
	virtual ~Player() = default;
	void movePlayer(const Event::EventType key, Event e);
	void shootBullet();
};
