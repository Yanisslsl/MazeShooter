#include <iostream>
#include <stack>
using namespace std;
#include <SFML/Graphics.hpp>



#pragma once
class MazeGenerator
{

public:
	MazeGenerator(int nWidth, int nHeight, int nPathWidth = 3);
	//~MazeGenerator();

	void GenerateMaze(sf::RenderWindow& window);
	void PrintMaze();
private:
	int  m_nMazeWidth;
	int  m_nMazeHeight;
	int* m_maze;


	// Some bit fields for convenience
	enum
	{
		CELL_PATH_N = 0x01,
		CELL_PATH_E = 0x02,
		CELL_PATH_S = 0x04,
		CELL_PATH_W = 0x08,
		CELL_VISITED = 0x10,
	};


	// Algorithm variables
	int  m_nVisitedCells;
	stack<pair<int, int>> m_stack;	// (x, y) coordinate pairs
	int  m_nPathWidth;
};

