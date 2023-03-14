#include "Maze.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
using namespace std;
#pragma once

Maze::Maze(int nWidth, int nHeight, int nPathWidth)
{
	m_nMazeWidth = nWidth;
	m_nMazeHeight = nHeight;
	m_nPathWidth = nPathWidth;
	m_nVisitedCells = 1;
	m_maze = new int[m_nMazeWidth * m_nMazeHeight];
	memset(m_maze, 0x00, m_nMazeWidth * m_nMazeHeight * sizeof(int));
	m_stack.push(make_pair(0, 0));
	m_maze[0] = CELL_VISITED;

}

void Maze::Load() {

	//lambda function to calculate offset
	auto offset = [&](int x, int y)
	{
		return (m_stack.top().second + y) * m_nMazeWidth + (m_stack.top().first + x);
	};

	while (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight) {
		// 1. Create a set of unvisited neighboors
		vector<int> neighboors;
		
		// Nothern neighboors
		if (m_stack.top().second > 0 && (m_maze[offset(0, -1)] & CELL_VISITED) == 0)
			neighboors.push_back(0);
		// East neighbour
		if (m_stack.top().first < m_nMazeWidth - 1 && (m_maze[offset(1, 0)] & CELL_VISITED) == 0)
			neighboors.push_back(1);
		// South neighbour
		if (m_stack.top().second < m_nMazeHeight - 1 && (m_maze[offset(0, 1)] & CELL_VISITED) == 0)
			neighboors.push_back(2);
		// West neighbour
		if (m_stack.top().first > 0 && (m_maze[offset(-1, 0)] & CELL_VISITED) == 0)
			neighboors.push_back(3);

		if (!neighboors.empty()) {
			// choose randomly an avaible neighboor
			int next_cell_dir = neighboors[rand() % neighboors.size()];

			switch (next_cell_dir)
			{
			case 0: // North
				m_maze[offset(0, -1)] |= CELL_VISITED | CELL_PATH_S;
				m_maze[offset(0, 0)] |= CELL_PATH_N;
				m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second - 1)));
				break;

			case 1: // East
				m_maze[offset(+1, 0)] |= CELL_VISITED | CELL_PATH_W;
				m_maze[offset(0, 0)] |= CELL_PATH_E;
				m_stack.push(make_pair((m_stack.top().first + 1), (m_stack.top().second + 0)));
				break;

			case 2: // South
				m_maze[offset(0, +1)] |= CELL_VISITED | CELL_PATH_N;
				m_maze[offset(0, 0)] |= CELL_PATH_S;
				m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second + 1)));
				break;

			case 3: // West
				m_maze[offset(-1, 0)] |= CELL_VISITED | CELL_PATH_E;
				m_maze[offset(0, 0)] |= CELL_PATH_W;
				m_stack.push(make_pair((m_stack.top().first - 1), (m_stack.top().second + 0)));
				break;
			}
			
			m_nVisitedCells++;

		}
		else {
			m_stack.pop();
		}
	}
}

void Maze::Draw(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);

	//draw for each lines and columns in the maze dimensions
	for (int x = 0; x < m_nMazeWidth; x++) {
		for (int y = 0; y < m_nMazeHeight; y++) {
			//draw for each pixel in the path width
			for (int py = 0; py < m_nPathWidth; py++)
			{
				for (int px = 0; px < m_nPathWidth; px++)
				{
					if (m_maze[y * m_nMazeWidth + x] & CELL_VISITED) {
						sf::RectangleShape square(sf::Vector2f(10, 10));
						square.setPosition(sf::Vector2f((float)x * (m_nPathWidth + 1) * 10 + px * 10, (float)y * 10 * (m_nPathWidth + 1) + py * 10));
						square.setFillColor(sf::Color::White);
						window.draw(square);
					}
					else {
						sf::RectangleShape square(sf::Vector2f(10, 10));
						square.setPosition(sf::Vector2f((float)x * (m_nPathWidth + 1) * 10 + px * 10, (float)y * 10 * (m_nPathWidth + 1) + py * 10));
						square.setFillColor(sf::Color::Blue);
						window.draw(square);
					}
				}

			}
			// overide cells with avaibles neigbours to draw the path
			for (int p = 0; p < m_nPathWidth; p++)
			{
				if (m_maze[y * m_nMazeWidth + x] & CELL_PATH_S) {
					sf::RectangleShape square(sf::Vector2f(10, 10));
					square.setPosition(sf::Vector2f((float)x * (m_nPathWidth + 1) * 10 + p * 10, (float)y * (m_nPathWidth + 1) * 10 + m_nPathWidth * 10));
					square.setFillColor(sf::Color::White);
					window.draw(square);
				}

				if (m_maze[y * m_nMazeWidth + x] & CELL_PATH_E) {
					sf::RectangleShape square(sf::Vector2f(10, 10));
					square.setPosition(sf::Vector2f((float)x * (m_nPathWidth + 1) * 10 + m_nPathWidth * 10, (float)y * 10 * (m_nPathWidth + 1) + p * 10));
					square.setFillColor(sf::Color::White);
					window.draw(square);
				}
			}

		}
	}
}


