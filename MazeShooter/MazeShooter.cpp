#include <SFML/Graphics.hpp>
#include "MazeGenerator.h";

int main()
{
    srand(clock());

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");
    MazeGenerator maze(40, 25, 3);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        maze.GenerateMaze(window);
        window.display();
       
    }

    return 0;
}