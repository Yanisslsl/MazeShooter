#include "../include/GameManager.h"
#include "../include/WindowManager.h"
#include "../include/AssetManager.h"
#include "../include/LevelManager.h"
#include <iostream>

GameManager* GameManager::m_instance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new GameManager();
	}

	return m_instance;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
	}
}

bool GameManager::Run(const std::string& _title, const Vec2i& _size)
{
	// MANAGE RESOURCES
	bool success = LoadResources();
	if (!success)
		return false;

	// MANAGE WINDOW
	WindowManager* windowManager = WindowManager::GetInstance();
	if (windowManager == nullptr)
		return false;

	sf::RenderWindow* window = windowManager->CreateWindow(_title, _size.x, _size.y);
	if (window == nullptr)
	{
		std::cout << ">> Cannot create window !" << std::endl;
		return false;
	}

	// MANAGE LEVELS
	LevelManager* levelManager = LevelManager::GetInstance();
	if (levelManager == nullptr)
		return false;
	levelManager->Load();


	
	sf::View view(sf::FloatRect(0.f, 0.f, _size.x, _size.y));

	// GAME LOOP
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			}
		}

		window->clear();
		window->setView(view);
		levelManager->RenderLevel(*window);
		window->display();
	}

	return true;
}

bool GameManager::LoadResources()
{
	bool success = true;
	AssetManager* assetManager = AssetManager::GetInstance();

	// Load fonts
	//success &= assetManager->LoadFont("arial.ttf", "arial");

	// Load textures
	success &= assetManager->LoadTexture("idle.png", "wall");

	if (success)
	{
		std::cout << ">> Loading resources was successful !" << std::endl;
	}
	else
	{
		std::cout << ">> Error while loading resources !" << std::endl;
		return false;
	}

	return true;
}
