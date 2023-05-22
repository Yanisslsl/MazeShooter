#include "../../include/Events/Event.h"

Event::Event(sf::Keyboard::Key _key, Entity* _entity, Vec2f _position)
{
	key = _key;
	entity = _entity;
	position = _position;
}

Event Event::InputEvent(sf::Keyboard::Key _key)
{
	return Event(_key, nullptr);
}

Event Event::CollisionEvent(Entity* _entity)
{
	return Event(sf::Keyboard::Unknown, _entity);
}

Event Event::MouseEvent(Vec2f _position)
{
	return Event(sf::Keyboard::Unknown, nullptr, _position);
}