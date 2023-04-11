#include "../../include/models/Level.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include "../../include/models/Player.h"
#pragma once

Level::Level(int nWidth, int nHeight, int nPathWidth)
{
	m_nLevelWidth = nWidth;
	m_nLevelHeight = nHeight;
	m_nPathWidth = nPathWidth;
	m_nVisitedCells = 1;
	m_level = new int[m_nLevelWidth * m_nLevelHeight];
	m_levelMap.assign(m_nLevelWidth * m_nLevelHeight, nullptr);
	memset(m_level, 0x00, m_nLevelWidth * m_nLevelHeight * sizeof(int));
	m_stack.push(make_pair(0, 0));
	m_level[0] = CELL_VISITED;

}


void Level::InitializeEntities() {
	Player* player = new Player(Vec2f(0, 0));
	player->SetSize(Vec2f(1.0f, 1.0f));
	m_entities["player"] = player;
}

void Level::Load() {
	InitializeEntities();
	//lambda function to calculate offset
	auto offset = [&](int x, int y)
	{
		return (m_stack.top().second + y) * m_nLevelWidth + (m_stack.top().first + x);
	};

	while (m_nVisitedCells < m_nLevelWidth * m_nLevelHeight) {
		// 1. Create a set of unvisited neighboors
		vector<int> neighboors;
		
		// Nothern neighboors
		if (m_stack.top().second > 0 && (m_level[offset(0, -1)] & CELL_VISITED) == 0)
			neighboors.push_back(0);
		// East neighbour
		if (m_stack.top().first < m_nLevelWidth - 1 && (m_level[offset(1, 0)] & CELL_VISITED) == 0)
			neighboors.push_back(1);
		// South neighbour
		if (m_stack.top().second < m_nLevelHeight - 1 && (m_level[offset(0, 1)] & CELL_VISITED) == 0)
			neighboors.push_back(2);
		// West neighbour
		if (m_stack.top().first > 0 && (m_level[offset(-1, 0)] & CELL_VISITED) == 0)
			neighboors.push_back(3);

		if (!neighboors.empty()) {
			// choose randomly an avaible neighboor
			int next_cell_dir = neighboors[rand() % neighboors.size()];

			switch (next_cell_dir)
			{
			case 0: // North
				m_level[offset(0, -1)] |= CELL_VISITED | CELL_PATH_S;
				m_level[offset(0, 0)] |= CELL_PATH_N;
				m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second - 1)));
				break;

			case 1: // East
				m_level[offset(+1, 0)] |= CELL_VISITED | CELL_PATH_W;
				m_level[offset(0, 0)] |= CELL_PATH_E;
				m_stack.push(make_pair((m_stack.top().first + 1), (m_stack.top().second + 0)));
				break;

			case 2: // South
				m_level[offset(0, +1)] |= CELL_VISITED | CELL_PATH_N;
				m_level[offset(0, 0)] |= CELL_PATH_S;
				m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second + 1)));
				break;

			case 3: // West
				m_level[offset(-1, 0)] |= CELL_VISITED | CELL_PATH_E;
				m_level[offset(0, 0)] |= CELL_PATH_W;
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

void Level::Draw(sf::RenderWindow& window) {
	auto offset = [&](int x, int y)
	{
		return (m_stack.top().second + y) * m_nLevelWidth + (m_stack.top().first + x);
	};

	//draw for each lines and columns in the maze dimensions
	for (int x = 0; x < m_nLevelWidth; x++) {
		for (int y = 0; y < m_nLevelHeight; y++) {
			//draw for each pixel in the path width
			for (int py = 0; py < m_nPathWidth; py++)
			{
				for (int px = 0; px < m_nPathWidth; px++)
				{
					auto t = m_level[y * m_nLevelWidth + x];
					if (m_level[y * m_nLevelWidth + x] & CELL_VISITED) {
						sf::RectangleShape square(sf::Vector2f(10, 10));
						square.setPosition(sf::Vector2f((float)x * (m_nPathWidth + 1) * 10 + px * 10, (float)y * 10 * (m_nPathWidth + 1) + py * 10));
						auto vec = sf::Vector2f((float)x * (m_nPathWidth + 1) * 10 + px * 10, (float)y * 10 * (m_nPathWidth + 1) + py * 10);
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
			//// overide cells with avaibles neigbours to draw the path
			for (int p = 0; p < m_nPathWidth; p++)
			{
				if (m_level[y * m_nLevelWidth + x] & CELL_PATH_S) {
					sf::RectangleShape square(sf::Vector2f(10, 10));
					square.setPosition(sf::Vector2f((float)x * (m_nPathWidth + 1) * 10 + p * 10, (float)y * (m_nPathWidth + 1) * 10 + m_nPathWidth * 10));
					square.setFillColor(sf::Color::White);
					window.draw(square);
				}

				if (m_level[y * m_nLevelWidth + x] & CELL_PATH_E) {
					sf::RectangleShape square(sf::Vector2f(10, 10));
					square.setPosition(sf::Vector2f((float)x * (m_nPathWidth + 1) * 10 + m_nPathWidth * 10, (float)y * 10 * (m_nPathWidth + 1) + p * 10));
					square.setFillColor(sf::Color::White);
					window.draw(square);
				}
			}
			auto cell = new Cell();
			std::vector<int> arr;


			if (m_level[y * m_nLevelWidth + x] & CELL_PATH_E) {
				cell->avaiblePaths = CELL_PATH_E;
			}
			if (m_level[y * m_nLevelWidth + x] & CELL_PATH_S) {
				cell->avaiblePaths |= CELL_PATH_S;
			}
			if (m_level[y * m_nLevelWidth + x] & CELL_PATH_N) {
				cell->avaiblePaths |= CELL_PATH_N;
			}
			if (m_level[y * m_nLevelWidth + x] & CELL_PATH_W) {
				cell->avaiblePaths |= CELL_PATH_W;
			}
			m_levelMap[y * m_nLevelWidth + x] = cell;
		}
	}

	
	
	for (auto& entity : m_entities) {
		entity.second->Render(window);
	}
}

Player* Level::getPlayer() {
	return dynamic_cast<Player*>(m_entities["player"]);
}


void Level::DrawLevel() {
}


// & 1 if all bytes are 1 so 0011 & 0001 = 0001
// | 1 if at least one byte is 1 so 0011 | 0001 = 0011

Level::Cell* Level::getRelativePositionInLevel() {
	auto player = m_entities["player"];
	auto playerPos = player->GetPosition();

	auto x = floor(playerPos.x / (1600 / 40));
	auto y = floor(playerPos.y / (800 / 20));

	auto u = y * m_nLevelWidth + x;
	auto d = m_levelMap[y * m_nLevelWidth + x];
	d->currentLocation = Vec2f(x * 40, y * 40);
	return d;
}

