#include "../../include/models/Scene.h"
#include "../../include/managers/UIManager.h"
#include "../../include/managers/WindowManager.h"
#include "../../include/models/Level.h"

Scene::Scene()
{
	m_levels = std::vector<Level*>();
	m_currentLevel = nullptr;
}

void Scene::Load()
{
	m_currentLevel->Load();
}


std::vector<Level*> Scene::GetLevels()
{
	return m_levels;
}

void Scene::AddLevel(Level* _level)
{
	m_levels.push_back(_level);
}

Level* Scene::GetCurrentLevel()
{
	return m_currentLevel;
}

void Scene::SetCurrentLevel(Level* _level)
{
	m_currentLevel = _level;
}


void Scene::Update()
{
	m_currentLevel->Update();
}

void Scene::Render()
{
	m_currentLevel->Draw();
}


void Scene::SwitchLevel(Level::LevelType _levelType)
{
	for (Level* level : m_levels)
	{
		if(level->GetLevelType() == _levelType)
		{
			UIManager::GetInstance()->Clear();
			m_currentLevel = level;
			Load();
		}
	}
}