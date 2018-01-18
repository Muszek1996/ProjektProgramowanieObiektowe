#include "Display.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Worm.h"
#include <iostream>
#include "Food.h"
#include "Line.h"
#include <random>

using namespace sf;
std::random_device randomGenerator;
std::uniform_real_distribution<float> generator(-2000.0, 2000.0);
using namespace std;
sf::Vector2f Display::windowSize(2000, 2000);
sf::Vector2f Display::mapSize(2000,2000);
float RADIUS = 10;



Display::Display(sf::RenderWindow &Window, Worm &mainPlayer)
{

    Window.create(sf::VideoMode(windowSize.x, windowSize.y), "OKIENKO", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings(32, 32, 16));//, sf::Style::Fullscreen
    Window.setKeyRepeatEnabled(false);

    // radius,length,sf::RenderWindow object,texturePath;
    unsigned int points = 0;
    int counter = 0;
    sf::View myView;
    sf::View defaultView;

    sf::Music music;
    if (!music.openFromFile("music.wav"))
        std::cout << "Error loading music";
    music.play();
    music.setLoop(true);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Bloop.wav"))
        cout << "error loading sound";
    sf::Sound slurpSound;
    slurpSound.setBuffer(buffer);
    slurpSound.isRelativeToListener();

    sf::Font font;
    if (!font.loadFromFile("pricedown bl.ttf"))
    {
        std::cout << "Error loading font";
    }
    sf::Text points_text;
    points_text.setFont(font);
    points_text.setCharacterSize(45);
    points_text.setFillColor(sf::Color::Red);
    points_text.setPosition(20, 200);
    sf::Text length_text;
    length_text.setFont(font);
    length_text.setCharacterSize(34);
    length_text.setFillColor(sf::Color::Green);
    length_text.setPosition(20, 240);



    Food food(Window);


    sf::VertexArray lines(sf::LinesStrip, 5);

    lines[0].position = -mapSize;
    lines[0].color = sf::Color::Red;
    lines[1].position = sf::Vector2f(-mapSize.x, mapSize.y);
    lines[1].color = sf::Color::Yellow;
    lines[2].position = mapSize;
    lines[2].color = sf::Color::Green;
    lines[3].position = sf::Vector2f(mapSize.x, -mapSize.y);
    lines[3].color = sf::Color::Blue;
    lines[4].position = -mapSize;

    Window.setFramerateLimit(60);

    const sf::Sprite obrazek;
    while (Window.isOpen())
    {
        points_text.setString("SCORE:" + to_string(points));
        length_text.setString("LENGTH:" + to_string(mainPlayer.length));
        Window.clear();
        Window.setView(defaultView);
        Window.draw(length_text);
        Window.draw(points_text); //Draw Hud
        Window.setView(myView);




        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            music.setPitch(1.24);
            mainPlayer.accelerateVal = 5;
            if (points>0)
                --points;
            for (Food* ptr = &food; ptr != nullptr; ptr = ptr->next_food)
            {
                if (float length = Line(ptr->circle.getPosition(), mainPlayer.wormParts[0].getPosition()).length<150)
                {
                    sf::Vector2f end(mainPlayer.wormParts[0].getPosition());
                    sf::Vector2f start(ptr->circle.getPosition());
                    sf::Vector2f newpos(((end.x - start.x) / length)*0.03, ((end.y - start.y) / length)*0.03);
                    ptr->circle.move(newpos);
                }
            }
        }
        else
        {
            music.setPitch(1);
            mainPlayer.accelerateVal = 1;
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


        //myView.move(2553.f, 2550.f);

        myView.setCenter(mainPlayer.wormParts[0].getPosition());

        Window.setView(myView);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Window.close();





        //cout << "xPos:" << sf::Mouse::getPosition().x << " yPos:" << sf::Mouse::getPosition().y << endl;



        for (Food* ptr = &food; ptr != nullptr; ptr = ptr->next_food)
        {
            if (Line(ptr->circle.getPosition(), mainPlayer.wormParts[0].getPosition()).length<20)
            {
                ptr->circle.setPosition(generator(randomGenerator), generator(randomGenerator));
                points += ptr->weight;
                if (mainPlayer.speed>200)
                {
                    mainPlayer.speed -= (points / 100);
                }
                else if (mainPlayer.speed>150)
                {
                    mainPlayer.speed -= (points / 1000);
                }
                else if (mainPlayer.speed>100)
                {
                    mainPlayer.speed -= (points / 5000);
                }
                else {
                    mainPlayer.speed -= (points / 10000);
                }

                mainPlayer.grow(ptr->weight);
                slurpSound.setVolume(10 * ptr->weight);
                slurpSound.play();
            }
        }



        if (mainPlayer.wormParts[0].getPosition().x > mapSize.x || mainPlayer.wormParts[0].getPosition().y > mapSize.y || mainPlayer.wormParts[0].getPosition().x < -mapSize.x || mainPlayer.wormParts[0].getPosition().y < -mapSize.y)
            Window.close();


        food.drawFood();
        mainPlayer.drawWorm();
        Window.draw(lines);






        Window.display();

    }

}

Display::~Display()
{
}
