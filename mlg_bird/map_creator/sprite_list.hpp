#ifndef SPRITE_LIST_HPP
#define SPRITE_LIST_HPP

typedef struct sprite_node
  {
    int x;
    int y;
    int index;
    int outline;

    struct sprite_node* next;
    struct sprite_node* prev;
  } SPRITE_NODE;

SPRITE_NODE* create_node(int index, int x, int y)
  {
    SPRITE_NODE* sprite_node = (SPRITE_NODE*) calloc(1, sizeof(SPRITE_NODE));

    sprite_node->x = x;
    sprite_node->y = y;

    sprite_node->index = index;

    sprite_node->next = NULL;
    sprite_node->prev = NULL;

    return sprite_node;
  }

typedef struct sprite_list
  {
    SPRITE_NODE* first;
    int num;
  } SPRITE_LIST;

SPRITE_LIST* create_sprite_list(void)
  {
    SPRITE_LIST* sprite_list = (SPRITE_LIST*) calloc(1, sizeof(SPRITE_LIST));

    sprite_list->first = NULL;
    sprite_list->num = 0;

    return sprite_list;
  }

void add_node(SPRITE_LIST* sprite_list, int index, int x, int y)
  {
    SPRITE_NODE* sprite_node = create_node(index, x, y);

    sprite_node->next = sprite_list->first;

    if(sprite_list->first != NULL) sprite_list->first->prev = sprite_node;

    sprite_list->first = sprite_node;

    sprite_list->num++;
  }

void delete_node(SPRITE_LIST* sprite_list, int count)
  {
    SPRITE_NODE* sprite_node = sprite_list->first;

    if(count == 0) sprite_list->first = sprite_list->first->next;

    for(int i = 0; i < count; i++) sprite_node = sprite_node->next;

    if(sprite_node->next != NULL) sprite_node->next->prev = sprite_node->prev;
    if(sprite_node->prev != NULL) sprite_node->prev->next = sprite_node->next;

    sprite_list->num--;

    free(sprite_node);
  }

void draw_sprite_list(RenderWindow & window, SPRITE_LIST* sprite_list_, IMAGE** image_, double bias_)
  {
    SPRITE_NODE* sprite_node = sprite_list_->first;
    for(int i = 0; i < sprite_list_->num; i++)
      {
        image_[sprite_node->index]->sprite->setPosition(sprite_node->x - bias_, sprite_node->y);

        if(sprite_node->outline == 0)
          window.draw(*image_[sprite_node->index]->sprite);

        sprite_node = sprite_node->next;
      }
  }

void draw_sprite_list_text(RenderWindow & window, SPRITE_LIST* sprite_list_, IMAGE** image_, int font_size)
  {
    SPRITE_NODE* sprite_node = sprite_list_->first;
    for(int i = 0; i < sprite_list_->num; i++)
      {
        int index = sprite_node->index;

        image_[index]->text->setPosition(1000, (i + 2)* font_size);
        image_[index]->text->setColor(sf::Color::Black);

        if(sprite_node->outline == 1)
          {
            image_[sprite_node->index]->text->setOutlineThickness(3.f);
            image_[sprite_node->index]->text->setOutlineColor(Color::Red);
          }

        window.draw(*image_[index]->text);

        image_[sprite_node->index]->text->setOutlineThickness(0.f);

        sprite_node = sprite_node->next;
      }
  }

#endif
