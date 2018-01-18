#include "Line.h"
#include <math.h>


sf::Vector2f Line::newWormHeadPosition(float step)
{
    float diff = ((end.x - start.x) / length)*step;
    return sf::Vector2f(((end.x - start.x)/length)*step, ((end.y - start.y)/length)*step);
}

Line::Line(sf::Vector2f beg, sf::Vector2f end)
{
    start = beg;
    Line::end = end;
    length= static_cast<float>(sqrt(pow(end.x - beg.x, 2)+pow(end.y-beg.y,2)));

}


Line::~Line()
{
}
