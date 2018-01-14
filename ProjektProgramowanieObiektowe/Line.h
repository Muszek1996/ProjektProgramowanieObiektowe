#pragma once
#include <SFML/System/Vector2.hpp>

class Worm;

class Line
{
    sf::Vector2f start, end;

public:
    float length;
    friend Worm;
    sf::Vector2f newWormHeadPosition(float step);
    Line(sf::Vector2f, sf::Vector2f);
    ~Line();
};
