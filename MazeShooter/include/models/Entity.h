#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "../utils/Vector2.h"

class Entity
{
public:
	enum class EntityType
	{
		PLAYER,
		BULLET,
		MOB
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
	bool isInSameCell(const Vec2f& position);
	bool checkCollision(const Vec2f& position, float rotation);
	Vec2f GetSize();
	void SetDirection(Vec2f direction);
	Vec2f GetDirection() const;
	void SetType(EntityType type);
	EntityType GetType();
	Vec2f m_velocity;
	void updateMovement(const Vec2f& acceleration, float rotation);
	void move(const Vec2f postition, float rotation);
private:
	sf::Sprite* m_sprite;
	Vec2f m_spriteSize;
	Vec2f m_position;
	Vec2f m_size;
	float m_rotation;
	EntityType m_type;
	Vec2f m_direction;
};
