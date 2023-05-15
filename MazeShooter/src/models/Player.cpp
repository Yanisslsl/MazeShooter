#include "../../include/models/Player.h"
#include "../../include/models/Bullet.h"
#include "../../include/utils/Vector2.h"
#include "../../include/Events/Event.h"
#include "../../include/managers/GameManager.h"
#include "../../include/managers/EntityManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>




Player::Player(const Vec2f& _position)
{
	SetPosition(_position);
	SetSprite("player", 0.15f);
	SetRotation(90);
}

void Player::movePlayer(const Event::EventType key, Event e)
{
	auto deltaTime = GameManager::GetInstance()->getDeltaTime();
	Vec2f acceleration;
	float rotation = GetRotation();
	const float dAcc = 100;
	switch(e.key)
	{
	case sf::Keyboard::Up:
		acceleration.y -= dAcc;
		rotation = 270;
		break;
	case sf::Keyboard::Down:
		acceleration.y += dAcc;
		rotation = 90;
		break;
	case sf::Keyboard::Right:
		acceleration.x += dAcc;
		rotation = 0;
		break;
	case sf::Keyboard::Left:
		acceleration.x -= dAcc;
		rotation = 180;
		break;
	}

	updateMovement(Vec2f(acceleration.x * deltaTime, acceleration.y * deltaTime), rotation);
}

void Player::shootBullet()
{
	auto entityManager = EntityManager::GetInstance();
	entityManager->createBullet(GetPosition(), GetRotation());
}