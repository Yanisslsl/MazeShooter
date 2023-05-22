#pragma once
#include "Level.h"
class MazeLevel: public Level
{
public:
	struct Cell
	{
		int avaiblePaths;
		Vec2f currentLocation;
	};
	MazeLevel(int nWidth, int nHeight, LevelType _levelType, int nPathWidth = 3);
	std::vector<Cell*> m_levelMap;
	std::vector<Bullet*> m_bullets;
	Cell* GetRelativePositionInLevel(Entity* entity);
	void AddBullet();
	void Update();
	void Load();
	void Draw();
	void initializeEnemies();
	void InitializeEntities();
	void CheckEnemiesDamage();
	void InitializeUI();
	void CheckPlayerDamage();
	void CheckPlayerWin();
	void GameOver();
	enum
	{
		CELL_PATH_N = 0x01, //1
		CELL_PATH_E = 0x02, //2
		CELL_PATH_S = 0x04, //4
		CELL_PATH_W = 0x08, //8
		CELL_VISITED = 0x10, //16
	};
	int  m_nVisitedCells;
	stack<pair<int, int>> m_stack;	// (x, y) coordinate pairs
	int  m_nPathWidth;
	int* m_level;
	bool m_LevelLoaded;
};