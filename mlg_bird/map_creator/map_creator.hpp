#ifndef MAP_CREATOR_HPP
#define MAP_CREATOR_HPP

#include "line.hpp"
#include "wind.hpp"
#include "image.hpp"
#include "animation.hpp"
#include "animation_list.hpp"
#include "sprite_list.hpp"
#include "write_mlg.hpp"
#include "frame.hpp"

//кол во кадров
#define FRAME_MAX 300

//окно редактирования
#define MAP_WIDTH 1000
#define MAP_HEIGHT 700

//список активных анимаций
#define ANIMATION_LIST_WIDTH 200
#define ANIMATION_LIST_HEIGHT 350

//список анимаций
#define ANIMATION_WIDTH 200
#define ANIMATION_HEIGHT 350

//список активных спрайтов
#define SPRITE_WIDTH 200
#define SPRITE_HEIGHT 350

//список текстур
#define TEXT_WIDTH 200
#define TEXT_HEIGHT 350

//максимум изображений и анимаций
#define IMAGE_MAX 100
#define ANIMATION_MAX 100

//размер надписей
#define FONT_SIZE 20

class MapCreator
  {
  public:

    enum MousePosition
      {
        MAP_RECT,
        SPRITE_RECT,
        TEXT_RECT,
        ANIMATION_LIST_RECT,
        ANIMATION_RECT,
        NONE
      };

    Wind *map_w_;
    Wind *sprite_w_;
    Wind *texture_w_;
    Wind *animation_list_w_;
    Wind *animation_w_;

    RectangleShape** line_;
    RectangleShape* yellow_line_;

    int im_or_an_ = 0;

    FRAME** frame_;

    IMAGE** image_;
    int image_max_;
    int image_active_;

    ANIMATION** animation_;
    int animation_max_;
    int animation_active_;

    SPRITE_LIST* sprite_list_;

    ANIMATION_LIST* animation_list_;

    double bias_ = 0;
    double yellow_line_bias_ = 0;
    double speed_ = 200;
    int CurrentFrame_ = 0;
    int MaxFrame_ = 0;

    FILE* output_;

    enum MousePosition mouse_position_ = NONE;

    MapCreator(Font & font, FILE* output, int first_frame, int second_frame);
   ~MapCreator();

    void draw(RenderWindow & window);

    void upgrade_mouse_coordinate(RenderWindow & window);
    void left_click_mouse(RenderWindow & window);
    void right_click_mouse(RenderWindow & window);

    void keybard_click_F2(RenderWindow & window);
    void keybard_click_F4(RenderWindow & window);
    void keybard_click_F6(RenderWindow & window);

    void keybard_click_D(RenderWindow & window);
    void keybard_click_A(RenderWindow & window);

    void keybard_click_1(RenderWindow & window);
    void keybard_click_2(RenderWindow & window);
    void keybard_click_3(RenderWindow & window);
  };

MapCreator::MapCreator(Font & font, FILE* output, int first_frame, int second_frame)
  {
    map_w_ = new Wind(0, 0, MAP_WIDTH, MAP_HEIGHT, font, "Map", FONT_SIZE);
    sprite_w_ = new Wind(1000, 0, SPRITE_WIDTH, SPRITE_HEIGHT, font, "Sprites", FONT_SIZE);
    texture_w_ = new Wind(1200, 0, TEXT_WIDTH, TEXT_HEIGHT, font, "Textures", FONT_SIZE);
    animation_list_w_ = new Wind(1000, 350, ANIMATION_LIST_WIDTH, ANIMATION_LIST_HEIGHT, font, "Animation_list", FONT_SIZE);
    animation_w_ = new Wind(1200, 350, ANIMATION_WIDTH, ANIMATION_HEIGHT, font, "Animation", FONT_SIZE);

    image_ = (IMAGE**)calloc(IMAGE_MAX, sizeof(IMAGE*));
    image_max_ = 0;
    image_active_ = 0;

    animation_ = (ANIMATION**)calloc(ANIMATION_MAX, sizeof(ANIMATION*));
    animation_max_ = 0;
    animation_active_ = 0;

    frame_ = (FRAME**)calloc(second_frame - first_frame, sizeof(FRAME*));
    for(int i = 0; i < second_frame - first_frame; i++) frame_[i] = create_frame(i + first_frame);

    sprite_list_ = create_sprite_list();

    animation_list_ = create_animation_list();

    output_ = output;

    read_textures(&animation_max_, &image_max_, animation_, image_, font, FONT_SIZE);

    FILE* head = fopen("../map_creator/head.mlg", "wb");
    write_head_mlg(head, image_, image_max_, animation_, animation_max_);
    fclose(head);

    line_ = (RectangleShape**) calloc(6, sizeof(RectangleShape*));
    for(int i = 0; i < 6; i++) line_[i] = create_line(500 + i*speed_, 0);

    yellow_line_ = create_yellow_line(500, 0);

    CurrentFrame_ = 0;
    MaxFrame_ = second_frame - first_frame;
    bias_ = first_frame/ 24.0 * speed_;
  }

MapCreator::~MapCreator()
  {
    delete map_w_;
    delete sprite_w_;
    delete texture_w_;

    for(int i = 0; i < image_max_; i++)
      delete_image(image_[i]);

    for(int i = 0; i < sprite_list_->num; i++)
      delete_node(sprite_list_, 0);

    free(sprite_list_);
  }

void MapCreator::draw(RenderWindow & window)
  {
    int mouse_x = Mouse::getPosition(window).x;
    int mouse_y = Mouse::getPosition(window).y;

    map_w_->draw(window);

    window.draw(*frame_[CurrentFrame_]->sprite);

    draw_sprite_list(window, sprite_list_, image_, bias_);
    draw_animation_list(window, animation_list_, animation_, bias_);

    for(int i = 0; i < 6; i++) window.draw(*line_[i]);

    yellow_line_->setPosition(500 + yellow_line_bias_, 0);
    window.draw(*yellow_line_);

    if(mouse_position_ == MAP_RECT && im_or_an_ == 0)
      {
        image_[image_active_]->sprite->setPosition(mouse_x, mouse_y);
        window.draw(*image_[image_active_]->sprite);
      }

    if(mouse_position_ == MAP_RECT && im_or_an_ == 1)
      {
        animation_[animation_active_]->sprite[0].setPosition(mouse_x, mouse_y);
        window.draw(animation_[animation_active_]->sprite[0]);
      }


    sprite_w_->draw(window);
    draw_sprite_list_text(window, sprite_list_, image_, FONT_SIZE);


    texture_w_->draw(window);
    draw_image_text(window, image_max_, image_active_, im_or_an_, image_, FONT_SIZE);


    animation_list_w_->draw(window);
    draw_animation_list_text(window, animation_list_, animation_, FONT_SIZE);


    animation_w_->draw(window);
    draw_animation_text(window, animation_max_, animation_active_, im_or_an_, animation_, FONT_SIZE);

  }

void MapCreator::upgrade_mouse_coordinate(RenderWindow & window)
  {
    int mouse_x = Mouse::getPosition(window).x;
    int mouse_y = Mouse::getPosition(window).y;

    if(mouse_x > 0 && mouse_x < 1000    && mouse_y > 0 && mouse_y < 700)
      mouse_position_ = MAP_RECT;

    if(mouse_x > 1000 && mouse_x < 1200 && mouse_y > 0 && mouse_y < 350)
      mouse_position_ = SPRITE_RECT;

    if(mouse_x > 1200 && mouse_x < 1400 && mouse_y > 0 && mouse_y < 350)
      mouse_position_ = TEXT_RECT;

    if(mouse_x > 1000 && mouse_x < 1200 && mouse_y > 350 && mouse_y < 700)
      mouse_position_ = ANIMATION_LIST_RECT;

    if(mouse_x > 1200 && mouse_x < 1400 && mouse_y > 350 && mouse_y < 700)
      mouse_position_ = ANIMATION_RECT;
  }

void MapCreator::left_click_mouse(RenderWindow & window)
  {
    int mouse_x = Mouse::getPosition(window).x;
    int mouse_y = Mouse::getPosition(window).y;

    if(mouse_position_ == MAP_RECT)
      {
        if(im_or_an_ == 0)
          add_node(sprite_list_, image_active_, mouse_x + bias_, mouse_y);
        else
          add_animation_node(animation_list_, animation_active_, mouse_x + bias_, mouse_y);
      }
    if(mouse_position_ == SPRITE_RECT)
      {
        int mouse_number = mouse_y/FONT_SIZE - 2;

        SPRITE_NODE* sprite_node = sprite_list_->first;
        for(int i = 0; i < mouse_number; i++) sprite_node = sprite_node->next;
        sprite_node->outline = (sprite_node->outline == 0) ? 1 : 0;
      }
    if(mouse_position_ == ANIMATION_LIST_RECT)
      {
        int mouse_number = (mouse_y - 350)/FONT_SIZE - 2;

        ANIMATION_NODE* animation_node = animation_list_->first;
        for(int i = 0; i < mouse_number; i++) animation_node = animation_node->next;
        animation_node->outline = (animation_node->outline == 0) ? 1 : 0;
      }
    if(mouse_position_ == TEXT_RECT)
      {
        image_active_ = mouse_y/FONT_SIZE - 2;
        im_or_an_ = 0;
      }
    if(mouse_position_ == ANIMATION_RECT)
      {
        animation_active_ = (mouse_y - 350)/FONT_SIZE - 2;
        im_or_an_ = 1;
      }

    sleep(milliseconds(200));
  }

void MapCreator::right_click_mouse(RenderWindow & window)
  {
    int mouse_x = Mouse::getPosition(window).x;
    int mouse_y = Mouse::getPosition(window).y;

    if(mouse_position_ == SPRITE_RECT)
      {
        int mouse_number = mouse_y/FONT_SIZE - 2;

        delete_node(sprite_list_, mouse_number);
      }

    if(mouse_position_ == ANIMATION_LIST_RECT)
      {
        int mouse_number = (mouse_y - 350)/FONT_SIZE - 2;

        delete_animation_node(animation_list_, mouse_number);
      }

    sleep(milliseconds(200));
  }

void MapCreator::keybard_click_F2(RenderWindow & window)
  {
    CurrentFrame_ += 1;
    if(CurrentFrame_ >= MaxFrame_) return;

    for(int i = 0; i < 1; i++)
      {
        write_current_frame(output_, sprite_list_, animation_list_, image_max_, animation_);
        upgrade_animation_list(animation_list_, animation_);
      }

    bias_ += speed_ / 24;
    sleep(milliseconds(200));
  }

void MapCreator::keybard_click_F4(RenderWindow & window)
  {
    CurrentFrame_ += 24;
    if(CurrentFrame_ >= MaxFrame_)
      {
        CurrentFrame_ -= 24;
        return;
      }

    for(int i = 0; i < 24; i++)
      {
        write_current_frame(output_, sprite_list_, animation_list_, image_max_, animation_);
        upgrade_animation_list(animation_list_, animation_);
      }

    bias_ += speed_;
    sleep(milliseconds(200));
  }

void MapCreator::keybard_click_F6(RenderWindow & window)
  {
    CurrentFrame_ += 24 * 5;
    if(CurrentFrame_ >= MaxFrame_)
      {
        CurrentFrame_ -= 24 * 5;
        return;
      }

    for(int i = 0; i < 24 * 5; i++)
      {
        write_current_frame(output_, sprite_list_, animation_list_, image_max_, animation_);
        upgrade_animation_list(animation_list_, animation_);
      }

    bias_ += speed_ * 5;
    sleep(milliseconds(200));
  }

void MapCreator::keybard_click_D(RenderWindow & window)
  {
    bias_ += speed_;
    yellow_line_bias_ -= speed_;
    sleep(milliseconds(200));
  }

void MapCreator::keybard_click_A(RenderWindow & window)
  {
    bias_ -= speed_;
    yellow_line_bias_ += speed_;
    sleep(milliseconds(200));
  }

void MapCreator::keybard_click_1(RenderWindow & window)
  {
    int command = -1;
    fwrite(&command, 1, sizeof(int), output_);
    sleep(milliseconds(200));
  }

void MapCreator::keybard_click_2(RenderWindow & window)
  {
    int command = -2;
    fwrite(&command, 1, sizeof(int), output_);
    sleep(milliseconds(200));
  }

void MapCreator::keybard_click_3(RenderWindow & window)
  {
    int command = -3;
    fwrite(&command, 1, sizeof(int), output_);
    sleep(milliseconds(200));
  }

#endif
