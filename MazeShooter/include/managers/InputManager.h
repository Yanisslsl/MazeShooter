#pragma once
#include "../models/Level.h"


class InputManager
{
public:
	virtual ~InputManager();
	InputManager(InputManager& _other) = delete;
	void operator=(const InputManager& _other) = delete;
	static InputManager* GetInstance();
	void Update(sf::Keyboard::Key key);
	void HandleEvent(sf::Event event);
private:
	InputManager();
	static InputManager* m_instance;
};
