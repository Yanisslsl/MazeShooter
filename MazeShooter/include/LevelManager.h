#pragma once

#include <string>;
#include "Maze.h";
#include <vector>

class LevelManager
{
public:
	virtual ~LevelManager();
	LevelManager(LevelManager& _other) = delete;
	void operator=(const LevelManager& _other) = delete;
	static LevelManager* GetInstance();

	Maze* getCurrent();
	Maze* getNext();
	Maze* getLast();
	Maze* create();
	void Load();
	void RenderLevel(sf::RenderWindow& window);
private:
	LevelManager();
	static LevelManager* m_instance;
	std::vector<Maze*> m_mazes;
	int current_index;
};
