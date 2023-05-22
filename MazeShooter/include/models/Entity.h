#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "../utils/Vector2.h"
#include "Collider.h"
class Collider;
class Entity
{
public:
	enum class EntityType
	{
		PLAYER,
		BULLET,
		ENEMY
	};

	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	Entity();
	virtual ~Entity();
	void Render(sf::RenderTarget& _target);
	void SetSprite(const std::string& _assetId, const float scale, const Vec2f& _position = { 0.f, 0.f }, const Vec2f& _size = { 0.f, 0.f });
	void SetPosition(const Vec2f& _position);
	Vec2f GetPosition();
	float GetRotation();
	void SetRotation(float angle);
	void SetSize(const Vec2f& _size);
	bool IsInSameCell(const Vec2f& position, int padding);
	bool CheckCollision(const Vec2f& position, float rotation, int padding);
	Vec2f GetSize();
	void SetDirection(Direction direction);
	Direction GetDirection();
	void SetType(EntityType type);
	EntityType GetType();
	Vec2f m_velocity;
	void UpdateMovement(const Vec2f& acceleration, float rotation);
	void Move(const Vec2f postition, float rotation);
	void SetCollider(Collider* m_collider);
	Collider* GetCollider();
	void SetHealth(float health);
	float GetHealth();
	void takeDamage(float damage);
	void SetUuid(float _uuid);
	float GetUuid();
private:
	sf::Sprite* m_sprite;
	Vec2f m_spriteSize;
	Vec2f m_position;
	Vec2f m_size;
	float m_rotation;
	EntityType m_type;
	Direction m_direction;
	// TODO change to getters/setters
	float m_acceleration;
	float m_health;
	Collider* m_collider;
	sf::Clock damageTimer;
	const sf::Time damageCooldown = sf::seconds(1.0f);
	float uuid;
};
