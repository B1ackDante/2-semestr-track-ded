#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
using namespace sf;

#define WIN_WIDTH 1000
#define WIN_HEIGHT 700

#define LOAD_WIDTH 225
#define LOAD_HEIGHT 225

#define BIRD_SPEED_X 200.0

Text* create_menu_text(Font &font, const char* str, int x, int y, int size)
  {
    Text* new_text = new Text(str, font, size);
    new_text->setStyle(sf::Text::Bold | sf::Text::Underlined);
    new_text->setColor(Color::Red);
    new_text->setPosition(x, y);
    return new_text;
  }

#include "hero.hpp"
#include "gameBuffer.hpp"

void loading(RenderWindow & window)
  {
    Texture loading_t;
    loading_t.loadFromFile(   "../menu/images/load.png");
    Sprite loading_s(          loading_t);
    loading_s.setScale(WIN_WIDTH * 1.0 / LOAD_WIDTH, WIN_HEIGHT * 1.0 / LOAD_HEIGHT);

    window.draw(loading_s);
    window.display();
  }
 

//g++ new_game.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lm

//a king_of_the_jungle
int main(int argv, char* argc[])
  {
	Font font;
    font.loadFromFile("../menu/16391.ttf");
	  
	RenderWindow window(sf::VideoMode(1000, 700), "Bird window");
	
	loading(window);
	  
    GameBuffer game_buffer(argc[1]);

    double bias = 0;
    double speed = BIRD_SPEED_X;

    Texture bird_i;
    bird_i.loadFromFile("../new_game/hero_image/bluebird.png");

    SoundBuffer s_buffer;
    s_buffer.loadFromFile("../new_game/hero_sound/YYY.wav");

    Hero bird(WIN_WIDTH / 2, 0, bird_i, s_buffer);

    game_buffer.music_->play();
	
	Clock clock;

    while (true)
      {
        double time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        bird.update(Keyboard::isKeyPressed(Keyboard::Space), time);
        if(game_buffer.inc(time) == false)
          break;
        bias += speed * time/1000000;

        window.clear(sf::Color::Black);

        game_buffer.draw(window, bias);
        bird.draw(window, font);

        window.display();

        if(game_buffer.collision(bird, bias))
			if(bird.inv())
				{
					bird.sound_->play();
					bird.death_time_++;
				}
      }
	  
	game_buffer.music_->stop();
	
	window.clear(sf::Color::Black);
	
	char* str = (char*) calloc(100, sizeof(char));
	
	sprintf(str, "death time %d", bird.death_time_);
		
	Text* d_time = create_menu_text(font, str, 30, 300, 100);
		
	window.draw(*d_time);
	
	window.display();
	
	sleep(milliseconds(5000));
	
	loading(window);

    return 0;
  }
