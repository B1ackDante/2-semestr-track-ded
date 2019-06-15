#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define CHOOSE_LEVEL_X 300
#define CHOOSE_LEVEL_Y 200

#define NUM_FILES 4

int new_game_menu(RenderWindow & window, Font & font, Music & music, Sprite & mlg_bird1, Sprite & mlg_bird2, Sprite & mlg_mass1, Sprite & mlg_mass2, Text * mlg, Sprite* background_s, double *CurFrame)
  {
    Text* choose_level = create_menu_text(font, "Choose Level", CHOOSE_LEVEL_X, CHOOSE_LEVEL_Y, FONT_SIZE);

    int mlg_file_num = 0;
    Text** mlg_file = (Text** )calloc(NUM_FILES, sizeof(Text*));

    DIR *dir;
    struct dirent *entry;

    dir = opendir("../mlg_files");

    while ( (entry = readdir(dir)) != NULL && mlg_file_num < NUM_FILES)
      {
        if(strcmp(entry->d_name,"..") == 0) continue;
        if(strcmp(entry->d_name,".") == 0) continue;
        mlg_file[mlg_file_num] = create_menu_text(font, entry->d_name, CHOOSE_LEVEL_X, CHOOSE_LEVEL_Y + FONT_SIZE*(1 + mlg_file_num), FONT_SIZE);
        mlg_file_num++;
      };

    closedir(dir);

    Text* exit    = create_menu_text(font, "Exit", CHOOSE_LEVEL_X, CHOOSE_LEVEL_Y + FONT_SIZE*(1 + NUM_FILES), FONT_SIZE);

    bool isMenu = 1;
    int menuNum = 0;

    sf::Clock clock;

    sleep(milliseconds(100));

    while(isMenu)
      {
//========================Обновляем время и текцщий кадр начало====================================

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        *CurFrame += time / 40000;
        if(*CurFrame > IMAGE_COUNT)
          {
            *CurFrame = 0;
            music.setPlayingOffset(seconds(0.f));
          }

//========================Обновляем время и текцщий кадр конец====================================

//========================Надписи начало====================================

        choose_level->setColor( Color::Red);
        for(int i = 0; i < mlg_file_num; i++) mlg_file[i]->setColor( Color::Red);
        exit->setColor(    Color::Red);

        menuNum = 0;

		    if (IntRect(CHOOSE_LEVEL_X, CHOOSE_LEVEL_Y, 12*FONT_SIZE / 2, FONT_SIZE).contains(Mouse::getPosition(window)))
          {
            choose_level->setColor(Color::Blue);
            menuNum = 1;
          }

        for(int i = 0; i < mlg_file_num; i++)
          {
            if(IntRect(CHOOSE_LEVEL_X, CHOOSE_LEVEL_Y + FONT_SIZE*(1 + i), 12*FONT_SIZE / 2, FONT_SIZE).contains(Mouse::getPosition(window)))
              mlg_file[i]->setColor( Color::Blue);
            menuNum = i + 2;
          }

        if (IntRect(CHOOSE_LEVEL_X, CHOOSE_LEVEL_Y + FONT_SIZE*(1 + NUM_FILES), 4*FONT_SIZE / 2, FONT_SIZE).contains(Mouse::getPosition(window)))
          {
            exit->setColor(Color::Blue);
            menuNum = 7;
          }

        if (Mouse::isButtonPressed(Mouse::Left))
		      {
				if(menuNum == 7) { return true;}
				
				if(menuNum == 2)
					{
						music.stop();
						system("b king_of_the_jungle");
						music.play();
						return true;
					}
		      }

//========================Надписи конец====================================


        Event event;
        while (window.pollEvent(event))
          if(event.type == Event::Closed)
            {
              window.close();
              isMenu = 0;
            }


        window.draw(background_s[((int)(*CurFrame) / IMAGE_PR) * IMAGE_PR]);

        window.draw(*mlg);

        window.draw(*choose_level);
        for(int i = 0; i < mlg_file_num; i++) window.draw(*(mlg_file[i]));
        window.draw(*exit);

        window.draw(mlg_bird1);
        window.draw(mlg_bird2);

        window.draw(mlg_mass1);
        window.draw(mlg_mass2);

        window.display();
      }
  }
