#ifndef MENU_CPP
#define MENU_CPP


#define IMAGE_COUNT 1047
#define IMAGE_PR 1

#define FONT_SIZE 80
#define NEW_GAME_X 300
#define NEW_GAME_Y 200
#define CREATE_MAP_X 300
#define CREATE_MAP_Y 280
#define EXIT_X 300
#define EXIT_Y 360

#define LOAD_WIDTH 225
#define LOAD_HEIGHT 225

#define BACK_WIDTH 360
#define BACK_HEIGHT 360

#define BIRD_WIDTH 260
#define BIRD_HEIGHT 162
#define NEW_BIRD_WIDTH 300
#define NEW_BIRD_HEIGHT 300

#define MASS_WIDTH 268
#define MASS_HEIGHT 188
#define NEW_MASS_WIDTH 300
#define NEW_MASS_HEIGHT 300


void loading(RenderWindow & window)
  {
    Texture loading_t;
    loading_t.loadFromFile(   "../menu/images/load.png");
    Sprite loading_s(          loading_t);
    loading_s.setScale(WIN_WIDTH * 1.0 / LOAD_WIDTH, WIN_HEIGHT * 1.0 / LOAD_HEIGHT);

    window.draw(loading_s);
    window.display();
  }

Text* create_menu_text(Font &font, const char* str, int x, int y, int size)
  {
    Text* new_text = new Text(str, font, size);
    new_text->setStyle(sf::Text::Bold | sf::Text::Underlined);
    new_text->setColor(Color::Red);
    new_text->setPosition(x, y);
    return new_text;
  }

#include "create_map_menu.cpp"
#include "new_game_menu.cpp"

Sprite* load_background(void)
  {
    Texture* background_t  = new Texture[IMAGE_COUNT];
    Sprite* background_s   = new Sprite[IMAGE_COUNT];

    for (int i = 0; i < IMAGE_COUNT; i += 1)
      {
        char* str = (char*)calloc(100, sizeof(char));
        sprintf(str, "../menu/images/background/images%05d.png", i);
        background_t[i].loadFromFile(str);
        background_s[i].setTexture(background_t[i]);
        background_s[i].setScale(WIN_WIDTH * 1.0 / BACK_WIDTH, WIN_HEIGHT * 1.0 / BACK_HEIGHT);
        free(str);
      }

    return background_s;
  }


void menu(RenderWindow & window)
  {
     loading(window);

     Font font;
     font.loadFromFile("../menu/16391.ttf");

     Text* mlg   = create_menu_text(font, "MLG Flappy Bird",    100, 20, 100);

     Text* new_game   = create_menu_text(font, "New Game",    NEW_GAME_X, NEW_GAME_Y, FONT_SIZE);
     Text* create_map = create_menu_text(font, "Create Map",  CREATE_MAP_X, CREATE_MAP_Y, FONT_SIZE);
     Text* exit       = create_menu_text(font, "Exit",        EXIT_X, EXIT_Y, FONT_SIZE);

     Sprite* background_s = load_background();

     Texture mlg_bird;
     mlg_bird.loadFromFile("../menu/images/mlg_bird.png");

     Sprite mlg_bird1;
     mlg_bird1.setTexture(mlg_bird);
     mlg_bird1.setScale(NEW_BIRD_WIDTH * 1.0 / BIRD_WIDTH, NEW_BIRD_HEIGHT * 1.0 / BIRD_HEIGHT);
     mlg_bird1.setPosition(0, WIN_HEIGHT - NEW_BIRD_HEIGHT);

     Sprite mlg_bird2;
     mlg_bird2.setTexture(mlg_bird);
     mlg_bird2.setScale(-NEW_BIRD_WIDTH * 1.0 / BIRD_WIDTH, NEW_BIRD_HEIGHT * 1.0 / BIRD_HEIGHT);
     mlg_bird2.setPosition(WIN_WIDTH , WIN_HEIGHT - NEW_BIRD_HEIGHT);

     Texture mlg_mass;
     mlg_mass.loadFromFile("../menu/images/mass.png");

     Sprite mlg_mass1;
     mlg_mass1.setTexture(mlg_mass);
     mlg_mass1.setScale(-NEW_MASS_WIDTH * 1.0 / MASS_WIDTH, NEW_MASS_HEIGHT * 1.0 / MASS_HEIGHT);
     mlg_mass1.setPosition(NEW_MASS_WIDTH - 80, 100);

     Sprite mlg_mass2;
     mlg_mass2.setTexture(mlg_mass);
     mlg_mass2.setScale(NEW_MASS_WIDTH * 1.0 / MASS_WIDTH, NEW_MASS_HEIGHT * 1.0 / MASS_HEIGHT);
     mlg_mass2.setPosition(WIN_WIDTH - NEW_MASS_WIDTH + 80, 100);

     bool isMenu = 1;
	   int menuNum = 0;

     int rot = 0;

     double CurFrame = 0;

     sf::Clock clock;

     Music music;
     music.openFromFile("../menu/music/menu.wav");
     music.play();
	 clock.restart();

	   //////////////////////////////МЕНЮ///////////////////
	   while (isMenu)
	    {
//========================Обновляем время и текцщий кадр начало====================================

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        CurFrame += time / 40000;
        if(CurFrame > IMAGE_COUNT)
          {
            CurFrame = 0;
            music.setPlayingOffset(seconds(0.f));
          }

//========================Обновляем время и текцщий кадр конец====================================

//========================Надписи начало====================================

		    new_game->setColor(   Color::Red);
        create_map->setColor( Color::Red);
		    exit->setColor(       Color::Red);

		    menuNum = 0;

		    if (IntRect(NEW_GAME_X, NEW_GAME_Y,      8*FONT_SIZE / 2, FONT_SIZE).contains(Mouse::getPosition(window)))
          {
            new_game->setColor(Color::Blue);
            menuNum = 1;
          }
		    if (IntRect(CREATE_MAP_X, CREATE_MAP_Y, 10*FONT_SIZE / 2, FONT_SIZE).contains(Mouse::getPosition(window)))
          {
            create_map->setColor(Color::Blue);
            menuNum = 2;
          }
        if (IntRect(EXIT_X, EXIT_Y,              4*FONT_SIZE / 2, FONT_SIZE).contains(Mouse::getPosition(window)))
          {
            exit->setColor(Color::Blue);
            menuNum = 3;
          }

        if (Mouse::isButtonPressed(Mouse::Left))
		      {
			      if (menuNum == 1) { isMenu = new_game_menu(window, font, music, mlg_bird1, mlg_bird2, mlg_mass1, mlg_mass2, mlg, background_s, &CurFrame); sleep(milliseconds(200));}
			      if (menuNum == 2) { isMenu = create_map_menu(window, font, music, mlg_bird1, mlg_bird2, mlg_mass1, mlg_mass2, mlg, background_s, &CurFrame); sleep(milliseconds(200));}
            if (menuNum == 3) { window.close(); isMenu = false; }
		      }

//========================Надписи конец====================================

        Event event;
        while (window.pollEvent(event))
          if(event.type == Event::Closed)
            {
              window.close();
              isMenu = 0;
            }


		    window.draw(background_s[((int)CurFrame / IMAGE_PR) * IMAGE_PR]);

        window.draw(*mlg);

        window.draw(*new_game);
        //window.draw(*create_map);
        window.draw(*exit);

        window.draw(mlg_bird1);
        window.draw(mlg_bird2);

        window.draw(mlg_mass1);
        window.draw(mlg_mass2);

        window.display();
	    }
	////////////////////////////////////////////////////
}

#undef IMAGE_COUNT
#undef IMAGE_PR

#undef FONT_SIZE
#undef NEW_GAME_X
#undef NEW_GAME_Y
#undef CREATE_MAP_X
#undef CREATE_MAP_Y
#undef EXIT_X
#undef EXIT_Y

#undef LOAD_WIDTH
#undef LOAD_HEIGHT

#undef BACK_WIDTH
#undef BACK_HEIGHT

#endif
