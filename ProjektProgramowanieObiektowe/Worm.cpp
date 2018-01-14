#include "Worm.h"
#include "Line.h"
#include "SFML/Graphics.hpp"
#include <iostream>


void Worm::grow(unsigned weight)
{
    sf::CircleShape* wormPartsnew = new sf::CircleShape[length+weight];
    for (int i = 0; i < length; i++)
    {
        wormPartsnew[i] = wormParts[i];
    }
    for (int i = length; i < length+weight; i++)
    {

        wormPartsnew[i] = sf::CircleShape();
        wormPartsnew[i].setRadius(radius);
        wormPartsnew[i].move(-i * radius, 0);
        wormPartsnew[i].move(1000, 1000);
    }
    wormParts = wormPartsnew;
}

int Worm::setSpeed(int newSpeed)
{
    if (newSpeed > 10)
    speed = newSpeed;
    std::cout << "Set Speed to : "<< speed << std::endl;
    return speed;
}

void Worm::move(sf::Vector2f targetPos)
{
    
    Line HeadToTarget(sf::Vector2f(1920/2,1080/2), targetPos);
    sf::Vector2f newHeadPos = HeadToTarget.newWormHeadPosition(wormParts[0].getRadius()/speed);
    wormParts[0].move(newHeadPos);


    sf::CircleShape old = wormParts[0];
    for(int i = 1;i<length;i++)
    {
        Line HeadToTarget(wormParts[i].getPosition(), old.getPosition());
        if(HeadToTarget.length>wormParts[i].getRadius())
        {
            newHeadPos = HeadToTarget.newWormHeadPosition(wormParts[i].getRadius()/speed);
            wormParts[i].move(newHeadPos);
        }
        old = wormParts[i];
    }

}

void Worm::drawWorm()
{

    for (int i = 0; i<length; i++)
    {
        //   mainPlayer.wormParts[i].setTexture(&texturek);
        okno->draw(wormParts[i]);
        move(static_cast<sf::Vector2f>(sf::Mouse::getPosition()));
        wormParts[i].setTexture(&texture);
    }
}

Worm::Worm(float radius, int wormLength, sf::RenderWindow &Window) :
    length(wormLength),
    speed(300)
{
    Worm::radius = static_cast<int>(radius);
    okno = &Window;
    wormParts = new sf::CircleShape[length];
    for (int i = 0; i < length; i++)
    {
        
        wormParts[i] = sf::CircleShape();
        wormParts[i].setRadius(radius);
        wormParts[i].move(-i * radius, 0);
        wormParts[i].move(1000, 1000);
    }
}

Worm::Worm(float radius, int wormLength, sf::RenderWindow & Window, std::string texturePath) :
    length(wormLength),
    speed(300)
{

  
    if(!texture.loadFromFile(texturePath))
    {
        std::cout << "Error while loading texture: " << texturePath << std::endl;
    }


    okno = &Window;
    wormParts = new sf::CircleShape[length];
    for (int i = 0; i < length; i++)
    {

        wormParts[i] = sf::CircleShape();
        wormParts[i].setRadius(radius);
        wormParts[i].move(-i * radius, 0);
        wormParts[i].move(1000, 1000);
    }
}

Worm::~Worm()
{
}
