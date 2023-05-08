#pragma once
#include <SFML/Graphics.hpp>

class Event
{
public:
	Event(sf::Keyboard::Key _key);
	enum class EventType
	{
		INPUT_PLAYER,
		INPUT_BULLET,
		EXIT
	};
	sf::Keyboard::Key key;
};