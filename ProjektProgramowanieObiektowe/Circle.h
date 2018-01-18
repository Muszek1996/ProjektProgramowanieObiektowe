#pragma once
#include <SFML/Graphics.hpp>


class Circle 
{
protected:
    int radius;
    sf::Vector2f position;
    unsigned int weight;
    sf::RenderWindow *Window;
    friend class Display;
    sf::Color kolor;
public:
    sf::CircleShape circle;
    static int minRadius, maxRadius;
    void drawCircle();
    Circle(sf::RenderWindow &window);
    ~Circle();
};

