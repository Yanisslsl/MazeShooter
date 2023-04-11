#include <SFML/Graphics.hpp>
#include "./include/managers/GameManager.h"

int main()
{

    GameManager* gameManager = GameManager::GetInstance();
    bool success = gameManager->Run("My Sokoban Game", Vec2i(1600, 800));

    return success ? EXIT_SUCCESS : EXIT_FAILURE;

    return 0;
}