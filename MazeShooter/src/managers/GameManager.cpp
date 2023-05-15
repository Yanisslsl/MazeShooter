#include "../../include/managers/GameManager.h"
#include "../../include/managers/WindowManager.h"
#include "../../include/managers/AssetManager.h"
#include "../../include/managers/LevelManager.h"
#include "../../include/managers/InputManager.h"
#include "../../include/utils/Vector2.h"
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

float GameManager::getDeltaTime()
{
	return m_deltaTime;
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

	InputManager* inputManager = InputManager::GetInstance();

	
	sf::View view(sf::FloatRect(0.f, 0.f, _size.x, _size.y));
	sf::Clock deltaTime;
	// made for initiliaze mLevelMap to avoid empty pointers on vectors due to the moving of the enemies on game start
	// //TODO update with level draw or encapsulate initilization of levelMap
	levelManager->RenderLevel(*window);
	levelManager->getCurrent()->InitializeEntities();



	// GAME LOOP
	while (window->isOpen())
	{
		m_deltaTime = deltaTime.restart().asSeconds();
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window->close();
					break;
				case sf::Event::KeyPressed:
					inputManager->update(event.key.code);
			}
		}
		levelManager->getCurrent()->update();
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
	success &= assetManager->LoadTexture("idle.png", "player");
	success &= assetManager->LoadTexture("bullet.png", "bullet");
	success &= assetManager->LoadTexture("enemy.png", "enemy");


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
