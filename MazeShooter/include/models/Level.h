#include <iostream>
#include <stack>
using namespace std;
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../../include/models/Entity.h"
#include "../../include/models/Player.h"
#include "../utils/Vector2.h"
#include "Bullet.h"
#include <variant>
#include <vector>

#pragma once
class Level
{

public:
	enum class LevelType
	{
		MainMenu,
		Maze
	};
	Level(int nWidth_, int _nHeight, LevelType _levelType);
	void virtual Load();
	void virtual Draw();
	int  m_nLevelWidth;
	int  m_nLevelHeight;
	void virtual Update();
	void SetLevelType(LevelType _levelType);
	LevelType GetLevelType();
private:
	std::unordered_map<string, std::variant<std::vector<Entity*>*, Entity*>> m_entities;
	LevelType m_levelType;
};

