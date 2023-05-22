#pragma once
#include <SFML/Graphics.hpp>
#include "../../include/models/Entity.h"


class Event
{
public:
	Event(sf::Keyboard::Key _key, Entity* _entity, Vec2f _position = Vec2f());
	static Event InputEvent(sf::Keyboard::Key _key);
	static Event CollisionEvent(Entity* _entity);
	static Event MouseEvent(Vec2f _position);
	enum class EventType
	{
		INPUT_PLAYER,
		INPUT_BULLET,
		ENEMY_COLLISION,
		MOUSE_CLICKED,
		EXIT
	};
	sf::Keyboard::Key key;
	Entity* entity;
	Vec2f position;
};