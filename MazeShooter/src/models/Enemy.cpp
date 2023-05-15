#include "../../include/models/Enemy.h";
#include "../../include/managers/GameManager.h"
#include "../../include/managers/EntityManager.h"
#include "../../include/managers/LevelManager.h"



Enemy::Enemy(const Vec2f& _position)
{
	SetPosition(_position);
	SetSprite("enemy", 0.008f);
	SetDirection(Entity::Direction::RIGHT);
}

void Enemy::moveEnemy()
{
	const auto deltaTime = GameManager::GetInstance()->getDeltaTime();
	auto rotation = GetRotation();
	Vec2f acceleration;
	const float dAcc = 50;
	const auto direction = Entity::GetDirection();

	if (direction == Direction::RIGHT)
	{
		acceleration.x += dAcc;
	}
	else if (direction == Direction::LEFT)
	{
		acceleration.x -= dAcc;
	}
	else if (direction == Direction::UP)
	{
		acceleration.y -= dAcc;
	}
	else {
		acceleration.y += dAcc;
	}
	auto position = GetPosition();
	float pX = position.x + acceleration.x * deltaTime;
	float pY = position.y + acceleration.y * deltaTime;

	if (isInSameCell(Vec2f(pX, pY ), 10)) {
		std::cout << "same cell" << std::endl;
		move(Vec2f(pX, pY), rotation);
	}
	else if ((checkCollision(Vec2f(pX , pY ), rotation, 10)))
	{
		std::cout << "collision" << std::endl;
		move(Vec2f(pX, pY), rotation);

	}
	else  {
		std::cout << "no collision" << std::endl;
		auto pathToFollow = Enemy::GetAvailablesPaths();
		Vec2f acceleration;
		if (pathToFollow == Level::CELL_PATH_E)
		{
			SetDirection(Direction::RIGHT);
			std::cout << "E" << std::endl;

			acceleration.x += dAcc;
		}
		else if (pathToFollow == Level::CELL_PATH_W)
		{
			SetDirection(Direction::LEFT);

			std::cout << "W" << std::endl;

			acceleration.x -= dAcc;
		}
		else if (pathToFollow == Level::CELL_PATH_S)
		{
			SetDirection(Direction::DOWN);

			std::cout << "S" << std::endl;

			acceleration.y += dAcc;
		}
		else {
			SetDirection(Direction::UP);
			std::cout << "N" << std::endl;

			acceleration.y -= dAcc;
		}
		auto position = GetPosition();
		float pX = position.x + acceleration.x * deltaTime;
		float pY = position.y + acceleration.y * deltaTime;

		SetRotation(rotation);
		move(Vec2f(pX, pY), rotation);
	}

}

int Enemy::GetAvailablesPaths()
{
	Level* level = LevelManager::GetInstance()->getCurrent();
	const auto currentCell = level->getRelativePositionInLevel(this);
	auto possiblesPaths = std::vector<int>();
	const auto availablesPaths = currentCell->avaiblePaths;
	if (currentCell->avaiblePaths & Level::CELL_PATH_E) {
		possiblesPaths.push_back(Level::CELL_PATH_E);
	}
	if (currentCell->avaiblePaths & Level::CELL_PATH_W)
	{
		possiblesPaths.push_back(Level::CELL_PATH_W);
	}
	if (currentCell->avaiblePaths & Level::CELL_PATH_N)
	{
		possiblesPaths.push_back(Level::CELL_PATH_N);
	}
	if (currentCell->avaiblePaths & Level::CELL_PATH_S)
	{
		possiblesPaths.push_back(Level::CELL_PATH_S);	
	}
	return possiblesPaths[rand() % possiblesPaths.size()];
}




