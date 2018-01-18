#include "Worm.h"
#include "Display.h"

int main()
{
    sf::RenderWindow Window;
    Worm mainPlayer(20, 54, Window, "snake.jpg"); // radius,length,sf::RenderWindow object,texturePath;
    Display disp(Window,mainPlayer);

 




    return 0;
}