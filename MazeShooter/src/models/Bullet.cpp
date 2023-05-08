#include "../../include/models/Bullet.h";
#include "../../include/managers/GameManager.h"
#include "../../include/managers/EntityManager.h"


Bullet::Bullet(const Vec2f& _position)
{
	SetPosition(_position);
	SetSprite("bullet", 0.15f);
}

void Bullet::moveBullet()
{
	auto deltaTime = GameManager::GetInstance()->getDeltaTime();
	auto entityManager = EntityManager::GetInstance();
	auto rotation = GetRotation();
	Vec2f acceleration;
	const float dAcc = 100;

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

	if (isInSameCell(Vec2f(pX, pY))) {
		move(Vec2f(pX, pY), rotation);
	}
	else if (checkCollision(Vec2f(pX, pY), rotation)) {
		move(Vec2f(pX, pY), rotation);
	}
	else if(!checkCollision(Vec2f(pX, pY), rotation))
	{
		entityManager->DestroyBullet(this);
	}
}


