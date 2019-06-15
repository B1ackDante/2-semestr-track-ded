#ifndef IMAGE_DEN_HPP
#define IMAGE_DEN_HPP

typedef struct image
  {
    char* name;
    Text* text;
    Texture* texture;
    Sprite* sprite;
  } IMAGE;

IMAGE* create_image(char* name, Font & font, int size)
  {
    IMAGE* image = (IMAGE*)calloc(1, sizeof(IMAGE));

    image->name = strdup(name);

    image->text = new Text(name, font, size);
    image->text->setColor(sf::Color::Black);

    char* file_name = (char*) calloc(100, sizeof(char));
    strcpy(file_name, "../textures/");
    strcat(file_name, name);

    image->texture = new Texture;
    image->texture->loadFromFile(file_name);

    image->sprite = new Sprite;
    image->sprite->setTexture(*image->texture);

    return image;
  }

void delete_image(IMAGE* image)
  {
    free(image->name);

    delete image->text;
    delete image->texture;
    delete image->sprite;

    free(image);
  }

void draw_image_text(RenderWindow & window, int image_max_, int image_active_, int im_or_an_, IMAGE** image_, int font_size)
  {
    for(int i = 0; i < image_max_; i++)
      {
        image_[i]->text->setColor(sf::Color::Black);
        if(i == image_active_ && im_or_an_ == 0) image_[i]->text->setColor(sf::Color::Blue);
        image_[i]->text->setPosition(1200, (i + 2)* font_size);
        window.draw(*image_[i]->text);
      }
  }

#endif
