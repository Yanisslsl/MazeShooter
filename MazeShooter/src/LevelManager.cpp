#include "../include/LevelManager.h"
#include "../include/Maze.h";
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
	m_mazes = {};
	current_index = 0;
}

LevelManager::~LevelManager()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		for (Maze* maze : m_mazes) {
			delete maze;
		}
	}
}

Maze* LevelManager::getCurrent()
{
	if (m_mazes.empty())
	{
		m_mazes.push_back(LevelManager::create());
	}
	return m_mazes.back();
}


Maze *LevelManager::create() {
	auto maze = new Maze(40, 25, 3);
	return maze;
}

void LevelManager::Load()
{
	auto current_maze = LevelManager::getCurrent();
	current_maze->Load();
}

void LevelManager::RenderLevel(sf::RenderWindow& window)
{
	auto current_maze = LevelManager::getCurrent();
	current_maze->Draw(window);
}


