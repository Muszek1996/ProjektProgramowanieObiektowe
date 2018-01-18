#include "Circle.h"
#include <SFML/Graphics.hpp>


class Worm;

class Display
{
    static sf::Vector2f windowSize;
public:
    static sf::Vector2f mapSize;
    friend class Circle;
    static sf::Vector2f getDisplayMapSize() { return windowSize; };
    friend class Food;
    Display(sf::RenderWindow &Window, Worm &mainPlayer);
    ~Display();
};
