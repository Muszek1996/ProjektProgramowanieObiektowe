#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Worm
{
public:
    unsigned points=0;
    int radius;
    int length;
    int speed;
    int accelerateVal;
    sf::CircleShape *wormParts;
    friend class Line;
    sf::RenderWindow *Window;
    sf::Texture texture;

    void grow(unsigned weight);
    void move(sf::Vector2f);
    void accelerate(float valueOfAcceleration);
    void drawWorm();
    Worm(float, int, sf::RenderWindow&, std::string);
    ~Worm();
};

