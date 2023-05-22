#include "../../include/models/Bullet.h"
#include "../../include/managers/GameManager.h"
#include "../../include/managers/EntityManager.h"


Bullet::Bullet(const Vec2f& _position)
{
	SetPosition(_position);
	SetSprite("bullet", 0.05f);
}

void Bullet::moveBullet()
{
	const auto deltaTime = GameManager::GetInstance()->GetDeltaTime();
	const auto entityManager = EntityManager::GetInstance();
	const auto rotation = GetRotation();
	Vec2f acceleration;
	const float dAcc = 500;

	if(rotation == 0)
	{
		acceleration.x += dAcc;

	} else if (rotation == 180)
	{
		acceleration.x -= dAcc;

	} else if (rotation == 270)
	{
		acceleration.y -= dAcc;

	} else {
		acceleration.y += dAcc;
	}
	auto position = GetPosition();
	float pX = position.x + acceleration.x * deltaTime;
	float pY = position.y + acceleration.y * deltaTime;

	if (IsInSameCell(Vec2f(pX, pY), 5)) {
		Move(Vec2f(pX, pY), rotation);
	}
	else if (CheckCollision(Vec2f(pX, pY), rotation, 5)) {
		Move(Vec2f(pX, pY), rotation);
	}
	else if(!CheckCollision(Vec2f(pX, pY), rotation, 5))
	{
		entityManager->DestroyBullet(this);
	}
}


