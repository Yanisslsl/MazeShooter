#include <iostream>
#include <stack>
using namespace std;
#include <SFML/Graphics.hpp>



#pragma once
class Maze
{

public:
	Maze(int nWidth, int nHeight, int nPathWidth = 3);
	//~MazeGenerator();

	void Load();
	void Draw(sf::RenderWindow& window);
private:
	int  m_nMazeWidth;
	int  m_nMazeHeight;
	int* m_maze;


	enum
	{
		CELL_PATH_N = 0x01,
		CELL_PATH_E = 0x02,
		CELL_PATH_S = 0x04,
		CELL_PATH_W = 0x08,
		CELL_VISITED = 0x10,
	};

	int  m_nVisitedCells;
	stack<pair<int, int>> m_stack;	// (x, y) coordinate pairs
	int  m_nPathWidth;
};

