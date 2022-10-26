/*
#include <iostream>
#include <SFML/Graphics.hpp>

#include "n.h"




int main()
{
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(60);
    sf::Uint8 a = 0U;
    sf::Int8 d = 0U;
    sf::Int8 xD = 0U;

    sf::Color colors[8] = { sf::Color(255, 0, 0), sf::Color(0, 255, 0), sf::Color(0, 0, 255), sf::Color(255, 0, 255), sf::Color(0, 255, 255), sf::Color(255, 255, 0) };


    sf::RectangleShape rectangle(sf::Vector2f(4U, 4U));
    rectangle.setFillColor(colors[a%6]);

    int grid[200][200];

    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            grid[j][i] = rand()%6;
        }
    }

    sf::Int16 yD = 0U;

    while (window.isOpen())
    {


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            for (int i = 0; i < 200; i++)
            {
                for (int j = 0; j < 200; j++)
                {
                    grid[j][i] = rand() % 6;
                }
            }
        }



        int gridN[200][200];

        window.clear();
        
        
        for (int i = 0; i < 200; i++)
        {
            for (int j = 0; j < 200; j++)
            {
                bool check = false;
                rectangle.setPosition(4 * j, 4 * i);

                if ((((grid[(j + 1)% 200][i] - grid[j][i]) == 1) || ((grid[(j - 1) % 200][i] - grid[j][i]) == 1) || ((grid[j][(i - 1) % 200] - grid[j][i]) == 1) || ((grid[j][(i + 1) % 200] - grid[j][i]) == 1)) || (((grid[(j + 1) % 200][i] - grid[j][i]) == -5) || ((grid[(j - 1) % 200][i] - grid[j][i]) == -5) || ((grid[j][(i - 1) % 200] - grid[j][i]) == -5) || ((grid[j][(i + 1) % 200] - grid[j][i]) == -5)))
                {
                    gridN[j][i] = (grid[j][i] + 1) % 6;
                }

                rectangle.setFillColor(colors[gridN[j][i]]);
                window.draw(rectangle);

            }
        }

        for (int i = 0; i < 200; i++)
        {
            for (int j = 0; j < 200; j++)
            {
                grid[j][i] = gridN[j][i];
            }
        }

        
        window.display();
    }


   




    return 0;
}



*/


