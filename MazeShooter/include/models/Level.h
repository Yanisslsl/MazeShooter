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


#pragma once
class Level
{

public:
	Level(int nWidth, int nHeight, int nPathWidth = 3);


	struct Cell
	{
		int avaiblePaths;
		Vec2f currentLocation;
	};

	void Load();
	void Draw(sf::RenderWindow& window);
	void InitializeEntities();
	Player* getPlayer();
	int  m_nLevelWidth;
	int  m_nLevelHeight;
	int* m_level;
	std::vector<Cell*> m_levelMap;
	std::vector<Bullet*> m_bullets;
	void DrawLevel();
	Cell* getRelativePositionInLevel();
	void update(Vec2f playerPosition, float playerRotation);
	void addBullet();
	std::variant<int, float> v, w;
	enum
	{
		CELL_PATH_N = 0x01, //1
		CELL_PATH_E = 0x02, //2
		CELL_PATH_S = 0x04, //4
		CELL_PATH_W = 0x08, //8
		CELL_VISITED = 0x10, //16
	};
private:
	std::unordered_map<string,Entity*> m_entities;
	int  m_nVisitedCells;
	stack<pair<int, int>> m_stack;	// (x, y) coordinate pairs
	int  m_nPathWidth;
};

