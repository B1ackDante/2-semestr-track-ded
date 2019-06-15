#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace sf;

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define WIN_WIDTH 1400
#define WIN_HEIGHT 700

#include "map_creator.hpp"

//g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lavformat -lavdevice -lavcodec -lavutil -lswscale -lswresample

//./a.out 1.mlg 1 50
// аргументы командной строки
// 1) название файла
// 2) начальный кадр
// 3) конечный кадр
int main(int argc, char const *argv[])
  {
    Font font;
    font.loadFromFile("14835.ttf");

    FILE* output = fopen(argv[1], "wb");

    MapCreator map_creator(font, output, atoi(argv[2]), atoi(argv[3]));

    RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Bird window");

    Clock clock;

    while (window.isOpen())
      {
        double time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        Event event;
        while (window.pollEvent(event))
          if(event.type == Event::Closed)
            window.close();

        map_creator.upgrade_mouse_coordinate(window);

        if(Mouse::isButtonPressed(Mouse::Left)) map_creator.left_click_mouse(window);
        if(Mouse::isButtonPressed(Mouse::Right)) map_creator.right_click_mouse(window);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) map_creator.keybard_click_F2(window);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) map_creator.keybard_click_F4(window);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) map_creator.keybard_click_F6(window);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) map_creator.keybard_click_A(window);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) map_creator.keybard_click_D(window);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) map_creator.keybard_click_1(window);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) map_creator.keybard_click_2(window);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) map_creator.keybard_click_3(window);

        if(map_creator.CurrentFrame_ >= map_creator.MaxFrame_)
          {
            window.close();
            break;
          }

        window.clear(sf::Color::Black);

        map_creator.draw(window);

        window.display();

      }

    fclose(output);

    return 0;

  }
