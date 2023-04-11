#include "../../include/models/Bullet.h";

Bullet::Bullet(const Vec2f& _position)
{
	SetPosition(_position);
	SetSprite("bullet", 0.15f);
	//SetRotation(90);
}
