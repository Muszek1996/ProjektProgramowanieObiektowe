#include "Display.h"
#include <SFML/Graphics.hpp>
#include "Worm.h"
#include <iostream>
#include "Food.h"
#include "Line.h"
using namespace std;
sf::Vector2f Display::windowSize(2000, 2000);

Display::Display(sf::RenderWindow &Window, Worm &mainPlayer)
{



    
    int counter = 0;
    sf::View myView;



  

    Window.create(sf::VideoMode(windowSize.x, windowSize.y), "OKIENKO", sf::Style::Resize);//, sf::Style::Fullscreen
    Window.setKeyRepeatEnabled(false);

    Food jedzonko(Window);


    sf::VertexArray lines(sf::LinesStrip, 5);

    lines[0].position = windowSize;
    lines[1].position = sf::Vector2f(windowSize.x, 0);
    lines[2].position = windowSize - sf::Vector2f(windowSize.x, windowSize.y);
    lines[3].position = sf::Vector2f(0, windowSize.y);
    lines[4].position = windowSize;


    Window.setFramerateLimit(60);

    const sf::Sprite obrazek;
    while (Window.isOpen())
    {
        if(counter<100)
        {
            Window.clear();
            counter = 0;
        }
  
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window.close();
            }

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    std::cout << "wheel type: vertical" << std::endl;
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                    std::cout << "wheel type: horizontal" << std::endl;
                else
                    std::cout << "wheel type: unknown" << std::endl;

                std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                myView.zoom(1 + (0.1 / event.mouseWheelScroll.delta));
                std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
            }



        }

      
        myView.move(2553.f, 2550.f);

        myView.setCenter(mainPlayer.wormParts[0].getPosition());
        Window.setView(myView);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))Window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))mainPlayer.setSpeed(mainPlayer.speed + 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))mainPlayer.setSpeed(mainPlayer.speed - 1);


        cout << "xPos:" << sf::Mouse::getPosition().x << " yPos:" << sf::Mouse::getPosition().y << endl;



        for (Food* ptr = &jedzonko; ptr != nullptr; ptr = ptr->next_food)
        {
            if(Line(ptr->circle.getPosition(), mainPlayer.wormParts[0].getPosition()).length<50)
            {
                ptr->circle.setPosition(100.0,100.0);
                mainPlayer.grow(ptr->weight);
            }

        
        }
       
        jedzonko.drawFood();
        mainPlayer.drawWorm();
        Window.draw(lines);
        //Window.draw(kolo);
        Window.display();

    }
}

Display::~Display()
{
}
