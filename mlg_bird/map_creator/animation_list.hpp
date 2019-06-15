#ifndef ANIMATION_LIST_HPP
#define ANIMATION_LIST_HPP

typedef struct animation_node
  {
    int x;
    int y;
    int index;
    int outline;
    int current_frame;

    struct animation_node* next;
    struct animation_node* prev;
  } ANIMATION_NODE;

ANIMATION_NODE* create_animation_node(int index, int x, int y)
  {
    ANIMATION_NODE* animation_node = (ANIMATION_NODE*) calloc(1, sizeof(ANIMATION_NODE));

    animation_node->x = x;
    animation_node->y = y;

    animation_node->index = index;
    animation_node->current_frame = 0;

    animation_node->next = NULL;
    animation_node->prev = NULL;

    return animation_node;
  }

typedef struct animation_list
  {
    ANIMATION_NODE* first;
    int num;
  } ANIMATION_LIST;

ANIMATION_LIST* create_animation_list(void)
  {
    ANIMATION_LIST* animation_list = (ANIMATION_LIST*) calloc(1, sizeof(ANIMATION_LIST));

    animation_list->first = NULL;
    animation_list->num = 0;

    return animation_list;
  }

void upgrade_animation_list(ANIMATION_LIST* animation_list, ANIMATION** animation_)
  {
    ANIMATION_NODE* animation_node = animation_list->first;
    int index = 0;

    while(animation_node != NULL)
      {
        animation_node->current_frame++;

        if(animation_node->current_frame >= animation_[animation_node->index]->current_num)
          {
            ANIMATION_NODE* animation_node_del = animation_node;
            animation_node = animation_node->next;

            if(animation_list->first == animation_node_del) animation_list->first = animation_list->first->next;

            if(animation_node_del->next != NULL) animation_node_del->next->prev = animation_node_del->prev;
            if(animation_node_del->prev != NULL) animation_node_del->prev->next = animation_node_del->next;

            animation_list->num--;

            free(animation_node_del);
          }
        else
          {
            animation_node = animation_node->next;
          }
      }
  }

void add_animation_node(ANIMATION_LIST* animation_list, int index, int x, int y)
  {
    ANIMATION_NODE* animation_node = create_animation_node(index, x, y);

    animation_node->next = animation_list->first;

    if(animation_list->first != NULL) animation_list->first->prev = animation_node;

    animation_list->first = animation_node;

    animation_list->num++;
  }

void delete_animation_node(ANIMATION_LIST* animation_list, int count)
  {
    ANIMATION_NODE* animation_node = animation_list->first;

    if(count == 0) animation_list->first = animation_list->first->next;

    for(int i = 0; i < count; i++) animation_node = animation_node->next;

    if(animation_node->next != NULL) animation_node->next->prev = animation_node->prev;
    if(animation_node->prev != NULL) animation_node->prev->next = animation_node->next;

    animation_list->num--;

    free(animation_node);
  }

void draw_animation_list(RenderWindow & window, ANIMATION_LIST* animation_list_, ANIMATION** animation_, double bias_)
  {
    ANIMATION_NODE* animation_node = animation_list_->first;
    for(int i = 0; i < animation_list_->num; i++)
      {
        animation_[animation_node->index]->sprite[animation_node->current_frame].setPosition(animation_node->x - bias_, animation_node->y);

        if(animation_node->outline == 0)
          window.draw(animation_[animation_node->index]->sprite[animation_node->current_frame]);

        animation_node = animation_node->next;
      }
  }

void draw_animation_list_text(RenderWindow & window, ANIMATION_LIST* animation_list_, ANIMATION** animation_, int font_size)
  {
    ANIMATION_NODE* animation_node = animation_list_->first;
    for(int i = 0; i < animation_list_->num; i++)
      {
        int index = animation_node->index;

        animation_[index]->text->setPosition(1000, 350 + (i + 2)* font_size);
        animation_[index]->text->setColor(sf::Color::Black);

        if(animation_node->outline == 1)
          {
            animation_[animation_node->index]->text->setOutlineThickness(3.f);
            animation_[animation_node->index]->text->setOutlineColor(Color::Red);
          }

        window.draw(*animation_[index]->text);

        animation_[animation_node->index]->text->setOutlineThickness(0.f);

        animation_node = animation_node->next;
      }
  }

#endif
