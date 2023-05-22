#pragma once
#include "../../include/utils/Vector2.h"
#include "../../include/models/Entity.h"
#include "../../include/Events/Event.h"

class Player : public Entity
{
public:
	struct Collision
	{
		Entity* collidedEntity;
		sf::Time damageCoutdown;
	};
	Player(const Vec2f& _position);
	virtual ~Player() = default;
	void MovePlayer(const Event::EventType key, Event e);
	void ShootBullet();
	void HandleCollision(Entity* _ennemy);
	bool Player::HasTakenDamage();
	void Player::SetHasTakenDamage(bool hasTakenDamage);
	void SetLastCollision(Collision& collision);
	Collision* GetLastCollision();
private:
	bool m_hasTakenDamage;
	Collision* m_lastCollision;
};
