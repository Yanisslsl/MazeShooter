#include "../../include/managers/LevelManager.h"
#include "../../include/models/Level.h";
#include "../../include/managers/WindowManager.h"
#include <iostream>


LevelManager* LevelManager::m_instance = nullptr;

LevelManager* LevelManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new LevelManager();
	}

	return m_instance;
}

LevelManager::LevelManager()
{
	m_levels = {};
	current_index = 0;
}

LevelManager::~LevelManager()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		for (Level* maze : m_levels) {
			delete maze;
		}
	}
}

Level* LevelManager::getCurrent()
{
	if (m_levels.empty())
	{
		m_levels.push_back(LevelManager::create());
	}
	return m_levels.back();
}


Level *LevelManager::create() {
	auto maze = new Level(40, 20, 3);
	return maze;
}

void LevelManager::Load()
{
	WindowManager* windowManager = WindowManager::GetInstance();
	auto current_maze = LevelManager::getCurrent();
	current_maze->Load(*windowManager->GetWindow());
}

void LevelManager::RenderLevel(sf::RenderWindow& window)
{
	auto current_maze = LevelManager::getCurrent();
	current_maze->Draw(window);
}

void updateLevel(sf::Event event,float dt)
{
	
}


// Passer les input en event -> afin d'arreter de passer inputManager->update dans la while loop
// Faire le mouvement des ennemis et des balles
