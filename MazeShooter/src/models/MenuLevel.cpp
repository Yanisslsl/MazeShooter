#include "../../include/models/MenuLevel.h"
#include "../../include/models/Level.h"
#include "../../include/managers/UIManager.h"



MenuLevel::MenuLevel(int nWidth, int nHeight, LevelType _levelType): Level::Level(nWidth, nHeight, _levelType)
{
	
};

void MenuLevel::Load()
{
	UIManager::GetInstance()->CreateBackGround("background", Vec2f(1600, 800));
	UIManager::GetInstance()->CreateText("Maze Shooter", Vec2f(1215 / 2, 355 / 2), sf::Color::White, 60);
	UIManager::GetInstance()->CreateButton(Vec2f(400, 75), Vec2f(1215 / 2, 600 / 2), sf::Color::Black, "Play", 50, UIManager::BUTTON_PLAY);
	UIManager::GetInstance()->CreateButton(Vec2f(400, 75), Vec2f(1215 / 2, 800 / 2), sf::Color::Black, "Quit", 50, UIManager::BUTTON_EXIT);
}

void MenuLevel::Draw()
{
	UIManager::GetInstance()->Render();
}