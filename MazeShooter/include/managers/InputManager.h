#pragma once

#include <string>;
#include "../models/Level.h"
#include <vector>
#include <functional>

class InputManager
{
public:
	virtual ~InputManager();
	InputManager(InputManager& _other) = delete;
	void operator=(const InputManager& _other) = delete;
	static InputManager* GetInstance();
	void update(sf::Keyboard::Key key);
	
private:
	InputManager();
	static InputManager* m_instance;
};
