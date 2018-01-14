#include "Food.h"
#include "Display.h";
int Food::maxRadius = 99;
int Food::minRadius = 80;
int Food::amount = 100;
int Food::foodAtm = 0;

Food::Food(sf::RenderWindow &Window) :
    Circle(Window)
{
    foodAtm++;
    if(foodAtm<amount)
    next_food = new Food(Window);
    else
    {
        next_food = nullptr;
    }
}

void Food::drawFood()
{
    Food* ptr = this;
    while(ptr!=nullptr)
    {
       ptr->drawCircle();
        ptr = ptr->next_food;
    }
  

}


Food::~Food()
{
}