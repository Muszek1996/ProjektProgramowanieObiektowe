#include "Circle.h"


class Food : public Circle
{
public:
    static int foodAtm;
    static int amount;
    sf::RenderWindow Window;
    Food * next_food;


    Food(sf::RenderWindow &window);
    void drawFood();
    ~Food();
};
