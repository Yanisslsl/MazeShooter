#include "../../include/models/Collider.h"
#include "../../include/models/Entity.h"
#include <SFML/Graphics.hpp>


Collider::Collider(Entity* _entity, Vec2f _size)
{
	auto rectangle =  sf::RectangleShape(_size);
	rectangle.setFillColor(sf::Color(255, 255, 255, 0));
	const auto position = _entity->GetPosition();
	Vec2f size = _entity->GetSize();
	float rectPosX = position.x + size.x / 2.0f - rectangle.getSize().x / 2.0f;
	float rectPosY = position.y + size.y / 2.0f - rectangle.getSize().y / 2.0f;
	rectangle.setPosition(rectPosX, rectPosY);
	m_boxCollider = rectangle;
	m_entity = _entity;
	m_position = Vec2f(rectPosX, rectPosY);
}

Entity* Collider::CheckCollision(Entity* _entity)
{
	if (m_boxCollider.getGlobalBounds().intersects(_entity->GetCollider()->m_boxCollider.getGlobalBounds()))
	{
		return _entity;
	}
	return nullptr;
}


sf::RectangleShape* Collider::GetCollider()
{
		return &m_boxCollider;
}

void Collider::SetPosition(const Vec2f& _position)
{
		m_position = _position;
}

Vec2f Collider::GetPosition()
{
	return m_position;
}