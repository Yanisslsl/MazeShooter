#include "../../include/models/MazeLevel.h"
#include "../../include/models/Level.h"
#include <SFML/Graphics.hpp>
#include <stack>
#include "../../include/models/Player.h"
#include "../../include/models/Bullet.h"
#include "../../include/managers/EntityManager.h"
#include "../../include/core/Eventdispatcher.h"
#include "../../include/managers/UIManager.h"
#include "../../include/managers/WindowManager.h"


MazeLevel::MazeLevel(int nWidth, int nHeight, LevelType _levelType, int nPathWidth): Level::Level(nWidth, nHeight, _levelType)
{
	m_nPathWidth = nPathWidth;
	m_nVisitedCells = 1;
	m_level = new int[m_nLevelWidth * m_nLevelHeight];
	m_levelMap.assign(m_nLevelWidth * m_nLevelHeight, nullptr);
	memset(m_level, 0x00, m_nLevelWidth * m_nLevelHeight * sizeof(int));
	m_stack.push(make_pair(0, 0));
	m_level[0] = CELL_VISITED;
	m_LevelLoaded = false;
}

void MazeLevel::InitializeEntities()  {
	EntityManager::GetInstance()->CreatePlayer();
	initializeEnemies();
	InitializeUI();
	m_LevelLoaded = true;
}

void MazeLevel::Load()
{
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
	if(!m_LevelLoaded)
	{
		for (int x = 0; x < m_nLevelWidth; x++) {
			for (int y = 0; y < m_nLevelHeight; y++) {
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
				cell->currentLocation = Vec2f(x * 40, y * 40);
				m_levelMap[y * m_nLevelWidth + x] = cell;
			}
		}
	}
	InitializeEntities();

}

void MazeLevel::Draw() {

	auto entities = EntityManager::GetInstance()->getEntities();
	auto player = EntityManager::GetInstance()->GetPlayer();
	auto window = WindowManager::GetInstance()->GetWindow();
	const auto rec = new sf::RectangleShape(Vec2f(1600, 800));
	rec->setFillColor(sf::Color::Black);
	window->draw(*rec);
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
						window->draw(square);
					}
					else {
						sf::RectangleShape square(sf::Vector2f(10, 10));
						square.setPosition(sf::Vector2f((float)x * (m_nPathWidth + 1) * 10 + px * 10, (float)y * 10 * (m_nPathWidth + 1) + py * 10));
						square.setFillColor(sf::Color::Blue);
						window->draw(square);
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
					window->draw(square);
				}

				if (m_level[y * m_nLevelWidth + x] & CELL_PATH_E) {
					sf::RectangleShape square(sf::Vector2f(10, 10));
					square.setPosition(sf::Vector2f((float)x * (m_nPathWidth + 1) * 10 + m_nPathWidth * 10, (float)y * 10 * (m_nPathWidth + 1) + p * 10));
					square.setFillColor(sf::Color::White);
					window->draw(square);
				}
			}
	
		}
	}

	for (auto& [key, value] : entities) {
		if (std::holds_alternative<Entity*>(value)) {
			Entity* entity_ptr = std::get<Entity*>(value);
			entity_ptr->Render(*window);
		}
		else {
			std::vector<Entity*>* entity_ptr = std::get<std::vector<Entity*>*>(value);
			for (auto& entity : *entity_ptr)
			{
				entity->Render(*window);
			}
		}
	}
	UIManager::GetInstance()->Render();
}

MazeLevel::Cell* MazeLevel::GetRelativePositionInLevel(Entity* entity) {
	auto playerPos = entity->GetPosition();

	auto x = floor(playerPos.x / (1600 / 40));
	auto y = floor(playerPos.y / (800 / 20));


	auto d = m_levelMap.at(y * m_nLevelWidth + x);
	return d;
}

void MazeLevel::Update()
{
	auto entities = EntityManager::GetInstance()->getEntities();
	const auto player = EntityManager::GetInstance()->GetPlayer();
	CheckPlayerDamage();
	CheckEnemiesDamage();
	CheckPlayerWin();
	const auto healthBar = UIManager::GetInstance()->GetElementByType(UIManager::HEALTH_BAR);
	if(auto rectangleShape = std::get_if<sf::RectangleShape*>(&healthBar->m_shape))
	{
		(*rectangleShape)->setSize(Vec2f(player == nullptr ? 80 * 2 - 2 : player->GetHealth() * 2 - 2, 28));
	}

	for (auto& [key, value] : entities) {
		if (std::holds_alternative<std::vector<Entity*>*>(value)) {
			std::vector<Entity*>* entity_ptr = std::get<std::vector<Entity*>*>(value);
			for (auto& entity : *entity_ptr)
			{
				if (entity->GetType() == Entity::EntityType::BULLET)
				{
					dynamic_cast<Bullet*>(entity)->moveBullet();
				}
				else if (entity->GetType() == Entity::EntityType::ENEMY)
				{
					dynamic_cast<Enemy*>(entity)->MoveEnemy();
				}
			}
		}
	}
}

void MazeLevel::initializeEnemies()
{

	for (int i = 0; i < 100; i++)
	{
		const auto randomCell = m_levelMap.at(rand() % m_levelMap.size());
		EntityManager::GetInstance()->CreateEnemy(Vec2f(randomCell->currentLocation.x + 10, randomCell->currentLocation.y + 10), 0);
	}
}

void MazeLevel::CheckPlayerDamage()
{
	const auto player = EntityManager::GetInstance()->GetPlayer();
	auto entities = EntityManager::GetInstance()->getEntities();
	const auto dispatcher = Eventdispatcher::GetInstance();


	if (auto enemiesVec = std::get_if<std::vector<Entity*>*>(&entities["enemies"]))
	{
		for (auto enemy : **enemiesVec)
		{
			if (enemy->GetCollider()->CheckCollision(player))
			{
				dispatcher->Dispatch(Event::EventType::ENEMY_COLLISION, Event::CollisionEvent(enemy));
			}
		}
	}

}

void MazeLevel::CheckEnemiesDamage()
{
	const auto player = EntityManager::GetInstance()->GetPlayer();
	auto entities = EntityManager::GetInstance()->getEntities();

	if (auto bulletsVec = std::get_if<std::vector<Entity*>*>(&entities["bullets"]))
	{
		if (auto enemiesVec = std::get_if<std::vector<Entity*>*>(&entities["enemies"]))
		{
			for (auto& bullet : **bulletsVec)
			{
				for (auto& enemy : **enemiesVec)
				{
					if (bullet->GetCollider()->CheckCollision(enemy))
					{
						EntityManager::GetInstance()->DestroyEnemy(enemy);
						EntityManager::GetInstance()->DestroyBullet(bullet);
					}
				}
			}
		}
	}
}

void MazeLevel::InitializeUI()
{
	UIManager::GetInstance()->CreateButton(Vec2f(200, 30), Vec2f(10,10), sf::Color(0, 0, 0, 100));
	UIManager::GetInstance()->CreateButton(Vec2f(200, 30), Vec2f(10, 10) + Vec2f(1, 1), sf::Color(255, 0, 0, 100), "", 0, UIManager::HEALTH_BAR);
	UIManager::GetInstance()->CreateButton(Vec2f(80, 30), Vec2f(1500, 10), sf::Color(0, 0, 0, 150), "Main Menu", 10, UIManager::BUTTON_MENU);
}

void MazeLevel::GameOver()
{
	UIManager::GetInstance()->CreateBackGround("background", Vec2f(1600, 800));
	UIManager::GetInstance()->CreateText("Game Over", Vec2f(608, 178), sf::Color::White, 70);
	UIManager::GetInstance()->CreateButton(Vec2f(400, 75), Vec2f(608, 300), sf::Color::Black, "Main Menu", 50, UIManager::BUTTON_MENU);
	UIManager::GetInstance()->CreateButton(Vec2f(400, 75), Vec2f(608 , 400), sf::Color::Black, "Quit", 50, UIManager::BUTTON_EXIT);
}

void MazeLevel::CheckPlayerWin()
{
	const auto playerPosition = EntityManager::GetInstance()->GetPlayer()->GetPosition();
	const auto lastCell = m_levelMap.at(m_levelMap.size() - 1);
	if(playerPosition.x >= lastCell->currentLocation.x && playerPosition.y >= lastCell->currentLocation.y)
	{
		UIManager::GetInstance()->CreateBackGround("background", Vec2f(1600, 800));
		UIManager::GetInstance()->CreateText("You have won !", Vec2f(608, 178), sf::Color::White, 70);
		UIManager::GetInstance()->CreateButton(Vec2f(400, 75), Vec2f(608, 300), sf::Color::Black, "Main Menu", 50, UIManager::BUTTON_MENU);
		UIManager::GetInstance()->CreateButton(Vec2f(400, 75), Vec2f(608, 400), sf::Color::Black, "Quit", 50, UIManager::BUTTON_EXIT);
	}
}
