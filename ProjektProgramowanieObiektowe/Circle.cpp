#include "Circle.h"
#include "Display.h"
#include <Random>

int Circle::maxRadius = 10;
int Circle::minRadius = 3;

std::random_device rd;
std::uniform_int_distribution<int> gen(-2000, 2000);
std::uniform_int_distribution<int> genRadius(Circle::minRadius, Circle::maxRadius);
std::uniform_int_distribution<int> colorGen(0, 255);


void Circle::drawCircle()
{
    circle.setOutlineThickness(1);
    circle.setOutlineColor(sf::Color::White);
    circle.setFillColor(kolor);
    Window->draw(circle);
}

Circle::Circle(sf::RenderWindow &window)
{
        Circle::Window = &window;
        radius = genRadius(rd);
        circle.setRadius(radius);
        position = sf::Vector2f(gen(rd), gen(rd));
        circle.setPosition(position);
        weight = radius;
        kolor = sf::Color(colorGen(rd), colorGen(rd), colorGen(rd), 255);
}


Circle::~Circle()
{
}
