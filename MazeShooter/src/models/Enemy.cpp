#include "../../include/models/Enemy.h";
#include "../../include/models/MazeLevel.h";
#include "../../include/managers/GameManager.h"
#include "../../include/managers/EntityManager.h"



Enemy::Enemy(const Vec2f& _position)
{
	SetPosition(_position);
	SetSprite("enemy", 0.008f);
	SetDirection(Entity::Direction::RIGHT);
}

void Enemy::MoveEnemy()
{
	const auto deltaTime = GameManager::GetInstance()->GetDeltaTime();
	const auto rotation = GetRotation();
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

	if (IsInSameCell(Vec2f(pX, pY ), 10)) {
		Move(Vec2f(pX, pY), rotation);
	}
	else if ((CheckCollision(Vec2f(pX , pY ), rotation, 10)))
	{
		Move(Vec2f(pX, pY), rotation);
	}
	else  {
		auto pathToFollow = Enemy::GetAvailablesPaths();
		Vec2f acceleration;
		if (pathToFollow == MazeLevel::CELL_PATH_E)
		{
			SetDirection(Direction::RIGHT);
			acceleration.x += dAcc;
		}
		else if (pathToFollow == MazeLevel::CELL_PATH_W)
		{
			SetDirection(Direction::LEFT);
			acceleration.x -= dAcc;
		}
		else if (pathToFollow == MazeLevel::CELL_PATH_S)
		{
			SetDirection(Direction::DOWN);
			acceleration.y += dAcc;
		}
		else {
			SetDirection(Direction::UP);
			acceleration.y -= dAcc;
		}
		auto position = GetPosition();
		float pX = position.x + acceleration.x * deltaTime;
		float pY = position.y + acceleration.y * deltaTime;

		SetRotation(rotation);
		Move(Vec2f(pX, pY), rotation);
	}

}

int Enemy::GetAvailablesPaths()
{
	const auto currentLevel = GameManager::GetInstance()->GetCurrentScene()->GetCurrentLevel();
	auto currentCell = dynamic_cast<MazeLevel*>(currentLevel)->GetRelativePositionInLevel(this);
	auto possiblesPaths = std::vector<int>();
	const auto availablesPaths = currentCell->avaiblePaths;
	if (currentCell->avaiblePaths & MazeLevel::CELL_PATH_E) {
		possiblesPaths.push_back(MazeLevel::CELL_PATH_E);
	}
	if (currentCell->avaiblePaths & MazeLevel::CELL_PATH_W)
	{
		possiblesPaths.push_back(MazeLevel::CELL_PATH_W);
	}
	if (currentCell->avaiblePaths & MazeLevel::CELL_PATH_N)
	{
		possiblesPaths.push_back(MazeLevel::CELL_PATH_N);
	}
	if (currentCell->avaiblePaths & MazeLevel::CELL_PATH_S)
	{
		possiblesPaths.push_back(MazeLevel::CELL_PATH_S);
	}
	return possiblesPaths[rand() % possiblesPaths.size()];
}




