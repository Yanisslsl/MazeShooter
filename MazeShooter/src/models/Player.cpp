#include "../../include/models/Player.h"
#include "../../include/utils/Vector2.h"


Player::Player(const Vec2f& _position)
{
	SetPosition(_position);
	SetSprite("player", 0.15f);
	SetRotation(90);
}

