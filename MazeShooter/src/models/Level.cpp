#include "../../include/models/Level.h"
#include <SFML/Graphics.hpp>
#include <stack>
#include "../../include/models/Player.h"
#include "../../include/models/Bullet.h"
#include "../../include/managers/EntityManager.h"
#include "../../include/core/Eventdispatcher.h"
#include "../../include/managers/UIManager.h"
#include<cstdlib>
#pragma once

Level::Level(int _nWidth, int _nHeight, LevelType _levelType)
{
	m_nLevelWidth = _nWidth;
	m_nLevelHeight = _nHeight;
	m_levelType = _levelType;
}

void Level::Load() {

}

void Level::Draw() {

}


void Level::Update()
{
	
}

void Level::SetLevelType(LevelType _levelType)
{
	m_levelType = _levelType;
}

Level::LevelType Level::GetLevelType()
{
	return m_levelType;
}
