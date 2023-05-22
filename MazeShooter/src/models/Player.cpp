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
	SetHealth(100);
	m_hasTakenDamage = false;
	m_lastCollision = nullptr;
}

void Player::MovePlayer(const Event::EventType key, Event e)
{
	const auto deltaTime = GameManager::GetInstance()->GetDeltaTime();
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

	UpdateMovement(Vec2f(acceleration.x * deltaTime, acceleration.y * deltaTime), rotation);
}

void Player::ShootBullet()
{
	auto entityManager = EntityManager::GetInstance();
	entityManager->CreateBullet(GetPosition(), GetRotation());
}

bool Player::HasTakenDamage()
{
	return m_hasTakenDamage;
}

Player::Collision* Player::GetLastCollision()
{
	return m_lastCollision;
}

void Player::SetLastCollision(Collision& collision)
{
	m_lastCollision = &collision;
}

void Player::SetHasTakenDamage(bool hasTakenDamage)
{
	m_hasTakenDamage = hasTakenDamage;
}

void Player::HandleCollision(Entity* _ennemy)
{
	// static here to keep the timer between function calls 
	static sf::Clock deltaTime;
	const auto lastCollision = GetLastCollision();
	if(lastCollision == nullptr || (lastCollision->collidedEntity == _ennemy && lastCollision->damageCoutdown.asSeconds() > 1.000))
	{
		sf::Clock deltaTime;
		deltaTime.restart();
		takeDamage(20);
		const auto collision = new Collision({ _ennemy, sf::Time::Zero });
		SetLastCollision(*collision);
	} else
	{
		sf::Time elapsedTime = deltaTime.getElapsedTime();
		deltaTime.restart();
		lastCollision->damageCoutdown += elapsedTime;
	}
}
