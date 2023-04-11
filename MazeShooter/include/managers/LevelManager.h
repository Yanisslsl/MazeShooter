#pragma once

#include <string>;
#include "../models/Level.h";
#include <vector>

class LevelManager
{
public:
	virtual ~LevelManager();
	LevelManager(LevelManager& _other) = delete;
	void operator=(const LevelManager& _other) = delete;
	static LevelManager* GetInstance();

	Level* getCurrent();
	Level* getNext();
	Level* getLast();
	Level* create();
	void Load();
	void RenderLevel(sf::RenderWindow& window);
private:
	LevelManager();
	static LevelManager* m_instance;
	std::vector<Level*> m_levels;
	int current_index;
};
