#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
using namespace std;
#include "Worm.h"
#include "Display.h"
#include "Food.h"

int main()
{
    sf::RenderWindow Window;
    Worm mainPlayer(20, 54, Window, "snake.jpg"); // radius,length,sf::RenderWindow object,texturePath;
    Display disp(Window,mainPlayer);

 




    return 0;
}