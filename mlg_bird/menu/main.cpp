#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace sf;

#define WIN_WIDTH 1000
#define WIN_HEIGHT 700

//g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lavformat -lavdevice -lavcodec -lavutil -lswscale -lswresample

#include "menu.cpp"

int main(void)
  {
    RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Bird window");

    menu(window);
  }
