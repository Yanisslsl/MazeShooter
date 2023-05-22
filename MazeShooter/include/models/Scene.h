#pragma once
#include "Level.h"
using namespace std;

class Scene
{
public:
	Scene();
	~Scene();
	void Load();
	void Update();
	void Render();
	std::vector<Level*> GetLevels();
	void AddLevel(Level* _level);
	Level* GetCurrentLevel();
	void SetCurrentLevel(Level* _level);
	void SwitchLevel(Level::LevelType _levelType);
private:
	std::vector<Level*> m_levels;
	Level* m_currentLevel;
};