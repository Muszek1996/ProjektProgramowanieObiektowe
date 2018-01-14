#include "Circle.h"


class Food : public Circle
{
public:
    static int foodAtm;
    static int amount;
    static int minRadius, maxRadius;
    Food * next_food;


    Food(sf::RenderWindow &Window);
    void drawFood();
    ~Food();
};
