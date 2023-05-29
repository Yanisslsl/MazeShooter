#include "../../include/managers/GameManager.h"
#include "../../include/managers/WindowManager.h"
#include "../../include/managers/AssetManager.h"
#include "../../include/managers/InputManager.h"
#include "../../include/models/Scene.h"
#include "../../include/models/MazeLevel.h"
#include "../../include/models/MenuLevel.h"
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
	InitializeScenes();
}

void GameManager::InitializeScenes()
{
	Scene* scene = new Scene();
	const auto menuLevel = new MenuLevel(40, 20, Level::LevelType::MainMenu);
	const auto mazeLevel = new MazeLevel(40, 20, Level::LevelType::Maze);
	scene->AddLevel(menuLevel);
	scene->AddLevel(mazeLevel);
	scene->SetCurrentLevel(menuLevel);
	AddScene(scene);
	SetCurrentScene(scene);
}
GameManager::~GameManager()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
	}
}

float GameManager::GetDeltaTime()
{
	return m_deltaTime;
}

bool GameManager::Run(const std::string& _title, const Vec2i& _size)
{
	bool success = LoadResources();
	if (!success)
		return false;

	WindowManager* windowManager = WindowManager::GetInstance();
	if (windowManager == nullptr)
		return false;

	sf::RenderWindow* window = windowManager->CreateWindow(_title, _size.x, _size.y);
	if (window == nullptr)
	{
		std::cout << ">> Cannot create window !" << std::endl;
		return false;
	}


	InputManager* inputManager = InputManager::GetInstance();

	
	sf::View view(sf::FloatRect(0.f, 0.f, _size.x, _size.y));
	sf::Clock deltaTime;

	GetCurrentScene()->Load();

	while (window->isOpen())
	{
		m_deltaTime = deltaTime.restart().asSeconds();
		sf::Event event;
		while (window->pollEvent(event))
		{
			inputManager->HandleEvent(event);
		}

		GetCurrentScene()->Update();
		GetCurrentScene()->Render();
		window->display();
	}

	return true;
}

bool GameManager::LoadResources()
{
	bool success = true;
	AssetManager* assetManager = AssetManager::GetInstance();

	success &= assetManager->LoadFont("arial.ttf", "arial");

	success &= assetManager->LoadTexture("idle.png", "player");
	success &= assetManager->LoadTexture("bullet.png", "bullet");
	success &= assetManager->LoadTexture("enemy.png", "enemy");
	success &= assetManager->LoadTexture("menu-background.png", "background");


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

void GameManager::Quit()
{
	WindowManager* windowManager = WindowManager::GetInstance();
	if (windowManager != nullptr)
	{
		sf::RenderWindow* window = windowManager->GetWindow();
		if (window != nullptr)
		{
			window->close();
		}
	}
}

void GameManager::AddScene(Scene* _scene)
{
	m_scenes.push_back(_scene);
}

Scene* GameManager::GetCurrentScene()
{
	if(m_currentScene == nullptr)
	{
		m_currentScene = m_scenes[0];
	}
	return m_currentScene;
}

void GameManager::SetCurrentScene(Scene* _scene)
{
	auto it = std::find((m_scenes).begin(), (m_scenes).end(), _scene);
	if(it != m_scenes.end())
	{
		m_currentScene = _scene;
	} else
	{
		AddScene(_scene);
		m_currentScene = _scene;
	}
}
