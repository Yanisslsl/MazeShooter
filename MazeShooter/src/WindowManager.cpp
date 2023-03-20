#include <iostream>
#include "../include/WindowManager.h"

WindowManager* WindowManager::m_instance = nullptr;

WindowManager* WindowManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new WindowManager();
	}

	return m_instance;
}

WindowManager::WindowManager()
{
	m_window = nullptr;
	m_width = 0;
	m_height = 0;
}

WindowManager::~WindowManager()
{
	if (m_instance)
	{
		delete m_instance;
	}
}

sf::RenderWindow* WindowManager::CreateWindow(const std::string& _title, const int& _width, const int& _height)
{
	if (m_window == nullptr && !_title.empty() && _width > 0 && _height > 0)
	{
		m_window = new sf::RenderWindow(sf::VideoMode(_width, _height), _title);

		m_window->clear();
		m_window->display();

		unsigned int width = m_window->getSize().x;
		unsigned int height = m_window->getSize().y;

		m_width = width;
		m_height = height;

		std::cout << "Window Size : (" << m_width << " x " << m_height << ")" << std::endl;
		sf::Vector2u size = m_window->getSize();
	}

	return m_window;
}

sf::RenderWindow* WindowManager::GetWindow()
{
	return m_window;
}

unsigned int WindowManager::GetWidth()
{
	return m_width;
}

unsigned int WindowManager::GetHeight()
{
	return m_height;
}

Vec2f WindowManager::GetSize()
{
	return Vec2f(m_width, m_height);
}
