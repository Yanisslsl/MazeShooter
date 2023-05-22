#pragma once
#include "Level.h"

class MenuLevel : public Level
{
public:
	MenuLevel(int nWidth, int nHeight, LevelType _levelType);
	void Load();
	void Draw();
};