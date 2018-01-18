#include "Worm.h"
#include "Line.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>;
std::random_device randgen;
std::uniform_real_distribution<float> genDiretion(-0.3, 0.3);
std::uniform_real_distribution<float> gen2(-10,10);

void Worm::grow(unsigned weight)
{

    sf::CircleShape* wormPartsnew = new sf::CircleShape[length+(weight/10)];
    for (int i = 0; i < length; i++)
    {
        wormPartsnew[i] = wormParts[i];
    }
    int old_length = length;
    length += (weight / 10);
    for (old_length; old_length < length; old_length++)
    {
        wormPartsnew[old_length] = sf::CircleShape();
        wormPartsnew[old_length].setRadius(radius);
        wormPartsnew[old_length].setPosition(wormParts[old_length - 1].getPosition());
    }
    wormParts = wormPartsnew;
}



void Worm::move(sf::Vector2f targetPos)
{
    
    Line HeadToTarget(sf::Vector2f(1920/2,1080/2), targetPos);
    sf::Vector2f newHeadPos = HeadToTarget.newWormHeadPosition((wormParts[0].getRadius()/speed)*accelerateVal);
    wormParts[0].move(newHeadPos);


    sf::CircleShape old = wormParts[0];
    for(int i = 1;i<length;i++)
    {
        Line HeadToTarget(wormParts[i].getPosition(), old.getPosition());
        if(HeadToTarget.length>wormParts[i].getRadius())
        {
            newHeadPos = HeadToTarget.newWormHeadPosition((wormParts[i].getRadius() / speed)*accelerateVal);
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
        Window->draw(wormParts[i]);
        move(static_cast<sf::Vector2f>(sf::Mouse::getPosition()));
        wormParts[i].setTexture(&texture);
    }
}



Worm::Worm(float radius, int wormLength, sf::RenderWindow & window, std::string texturePath) :
    length(wormLength),
    speed(250),
    accelerateVal(0)
{

  
    if(!texture.loadFromFile(texturePath))
    {
        std::cout << "Error while loading texture: " << texturePath << std::endl;
    }


    Window = &window;
    wormParts = new sf::CircleShape[length];
    sf::Vector2f randomDirection(genDiretion(randgen), genDiretion(randgen));
    for (int i = 0; i < length; i++)
    {

        wormParts[i] = sf::CircleShape();
        wormParts[i].setRadius(radius);
        if (i)
            wormParts[i].setPosition(wormParts[i - 1].getPosition());
        wormParts[i].move(randomDirection.x*i, randomDirection.y*i);
    }
}

Worm::~Worm()
{
}
