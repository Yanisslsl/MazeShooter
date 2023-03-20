#include <SFML/Graphics.hpp>
#include "./include/GameManager.h"

int main()
{
    srand(clock());

    GameManager* gameManager = GameManager::GetInstance();
    bool success = gameManager->Run("My Sokoban Game", Vec2i(1920, 1080));

    return success ? EXIT_SUCCESS : EXIT_FAILURE;

    return 0;
}