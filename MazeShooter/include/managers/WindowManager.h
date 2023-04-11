#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "../utils/Vector2.h"

class WindowManager
{
public:
	virtual ~WindowManager();
	WindowManager(const WindowManager& _other) = delete;
	void operator=(const WindowManager& _other) = delete;
	static WindowManager* GetInstance();

	sf::RenderWindow* CreateWindow(const std::string& _title, const int& _width, const int& _height);
	sf::RenderWindow* GetWindow();

	unsigned int GetWidth();
	unsigned int GetHeight();
	Vec2f GetSize();

private:
	WindowManager();
	static WindowManager* m_instance;

	sf::RenderWindow* m_window;
	unsigned int m_width;
	unsigned int m_height;
};
