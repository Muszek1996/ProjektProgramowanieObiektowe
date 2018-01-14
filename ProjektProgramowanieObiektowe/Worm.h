#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Worm
{
public:
    unsigned points;
    int radius;
    int length;
    int speed;
    sf::CircleShape *wormParts;
    friend class Line;
    sf::RenderWindow *okno;
    sf::Texture texture;

    void grow(unsigned weight);
    int setSpeed(int);
    void move(sf::Vector2f);
    void drawWorm();
    Worm(float,int, sf::RenderWindow&);
    Worm(float, int, sf::RenderWindow&, std::string);
    ~Worm();
};

