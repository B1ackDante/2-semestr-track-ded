#ifndef ANIMATION_HPP
#define ANIMATION_HPP

typedef struct animation
  {
    int current_num;
    char* name;
    Text* text;
    Texture* texture;
    Sprite* sprite;
  } ANIMATION;

ANIMATION* create_animation(char* name, Font & font, int size)
  {
    ANIMATION* animation = (ANIMATION*)calloc(1, sizeof(ANIMATION));

    animation->current_num = 0;

    char* dir_name = (char*) calloc(100, sizeof(char));
    strcpy(dir_name, "../textures/");
    strcat(dir_name, name);

    DIR *dir;
    struct dirent *entry;

    dir = opendir(dir_name);

    while ( (entry = readdir(dir)) != NULL )
      {
        if(strcmp(entry->d_name,"..") == 0) continue;
        if(strcmp(entry->d_name,".") == 0) continue;

        animation->current_num++;
      }

    free(dir_name);

    std::cout << "animation" << std::endl;
    std::cout << animation->current_num << std::endl;

    animation->name = strdup(name);

    animation->text = new Text(name, font, size);
    animation->text->setColor(sf::Color::Black);

    animation->texture = new Texture[animation->current_num];
    for(int i = 0; i < animation->current_num; i++)
      {
        char* file_name = (char*) calloc(100, sizeof(char));
        char* file_name1 = (char*) calloc(100, sizeof(char));
        strcpy(file_name, "../textures/");
        strcat(file_name, name);
        strcat(file_name, "/image%03d.png");
        sprintf(file_name1, file_name, i + 1);

        animation->texture[i].loadFromFile(file_name1);

        free(file_name);
        free(file_name1);
      }

    animation->sprite = new Sprite[animation->current_num];
    for(int i = 0; i < animation->current_num; i++)
      animation->sprite[i].setTexture(animation->texture[i]);

    return animation;
  }

void draw_animation_text(RenderWindow & window, int animation_max_, int animation_active_, int im_or_an_, ANIMATION** animation_, int font_size)
  {
    for(int i = 0; i < animation_max_; i++)
      {
        animation_[i]->text->setColor(sf::Color::Black);
        if(i == animation_active_ && im_or_an_ == 1) animation_[i]->text->setColor(sf::Color::Blue);
        animation_[i]->text->setPosition(1200, 350 + (i + 2)* font_size);
        window.draw(*animation_[i]->text);
      }
  }

#endif
