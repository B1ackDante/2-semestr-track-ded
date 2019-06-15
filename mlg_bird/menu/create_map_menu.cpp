int create_map_menu(RenderWindow & window, Font & font, Music & music, Sprite & mlg_bird1, Sprite & mlg_bird2, Sprite & mlg_mass1, Sprite & mlg_mass2, Text * mlg, Sprite* background_s, double *CurFrame)
  {
    Text* new_map = create_menu_text(font, "New Map",    NEW_GAME_X, NEW_GAME_Y, FONT_SIZE);
    Text* edit_map = create_menu_text(font, "Edit Map",  CREATE_MAP_X, CREATE_MAP_Y, FONT_SIZE);
    Text* exit    = create_menu_text(font, "Exit",        EXIT_X, EXIT_Y, FONT_SIZE);

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

        new_map->setColor( Color::Red);
        edit_map->setColor(Color::Red);
        exit->setColor(    Color::Red);

        menuNum = 0;

		    if (IntRect(NEW_GAME_X, NEW_GAME_Y,      8*FONT_SIZE / 2, FONT_SIZE).contains(Mouse::getPosition(window)))
          {
            new_map->setColor(Color::Blue);
            menuNum = 1;
          }
		    if (IntRect(CREATE_MAP_X, CREATE_MAP_Y, 10*FONT_SIZE / 2, FONT_SIZE).contains(Mouse::getPosition(window)))
          {
            edit_map->setColor(Color::Blue);
            menuNum = 2;
          }
        if (IntRect(EXIT_X, EXIT_Y,              4*FONT_SIZE / 2, FONT_SIZE).contains(Mouse::getPosition(window)))
          {
            exit->setColor(Color::Blue);
            menuNum = 3;
          }

        if (Mouse::isButtonPressed(Mouse::Left))
		      {
			      if (menuNum == 1) { return false;}
			      if (menuNum == 2) { return false;}
            if (menuNum == 3) { return true;}
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

        window.draw(*new_map);
        window.draw(*edit_map);
        window.draw(*exit);

        window.draw(mlg_bird1);
        window.draw(mlg_bird2);

        window.draw(mlg_mass1);
        window.draw(mlg_mass2);

        window.display();
      }
  }
