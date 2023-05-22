#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/Vector2.h"
#include "Entity.h"

class Entity;
class Collider
{
public:
	Collider(Entity* _entity, Vec2f _size);
	~Collider();
	void SetBoxCollider(const Vec2f& _position = { 0.f, 0.f }, const Vec2f& _size = { 0.f, 0.f });
	void SetPosition(const Vec2f& _position);
	void SetEntity(Entity _entity);
	Entity GetEntity();
	Vec2f GetPosition();
;	Entity* CheckCollision(Entity* _entity);
	sf::RectangleShape* GetCollider();
private:
	sf::RectangleShape m_boxCollider;
	Vec2f m_position;
	Entity* m_entity;
};