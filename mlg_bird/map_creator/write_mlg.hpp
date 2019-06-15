#ifndef WRITE_MLG_HPP
#define WRITE_MLG_HPP

void read_textures(int *animation_max_, int *image_max_, ANIMATION** animation_, IMAGE** image_, Font & font, int font_size)
  {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("../textures");

    while ( (entry = readdir(dir)) != NULL )
      {
        if(strcmp(entry->d_name,"..") == 0) continue;
        if(strcmp(entry->d_name,".") == 0) continue;

        if(entry->d_name[0] == '_')
          {
            animation_[*animation_max_] = create_animation(entry->d_name, font, font_size);
            (*animation_max_)++;
          }
        else
          {
            image_[*image_max_] = create_image(entry->d_name, font, font_size);
            (*image_max_)++;
          }
      }
  }

void write_head_mlg(FILE* output, IMAGE** image_, int image_max_, ANIMATION** animation_, int animation_max_)
  {
    int max_im_an = image_max_;
    for(int i = 0; i < animation_max_; i++) max_im_an += animation_[i]->current_num;
    fwrite(&(max_im_an), 1, sizeof(int), output);

    for(int i = 0; i < image_max_; i++)
      {
        int len = strlen(image_[i]->name);

        fwrite(&len, 1, sizeof(int), output);
        fwrite(image_[i]->name, len, sizeof(char), output);
      }

    for(int i = 0; i < animation_max_; i++)
      for(int j = 0; j < animation_[i]->current_num; j++)
        {
          char* file_name = (char*) calloc(100, sizeof(char));
          char* file_name1 = (char*) calloc(100, sizeof(char));
          strcpy(file_name, "../textures/");
          strcat(file_name, animation_[i]->name);
          strcat(file_name, "/image%03d.png");
          sprintf(file_name1, file_name, j + 1);

          int len = strlen(file_name1);

          fwrite(&len, 1, sizeof(int), output);
          fwrite(file_name1, len, sizeof(char), output);

          free(file_name);
          free(file_name1);
        }

    int sound_index = image_max_;

    fwrite(&animation_max_, 1, sizeof(int), output);

    for(int i = 0; i < animation_max_; i++)
      {
        char* file_name = (char*) calloc(100, sizeof(char));
        strcat(file_name, animation_[i]->name);
        strcat(file_name, ".wav");

        int len = strlen(file_name);

        fwrite(&sound_index, 1, sizeof(int), output);

        fwrite(&len, 1, sizeof(int), output);
        fwrite(file_name, len, sizeof(char), output);

        sound_index += animation_[i]->current_num;
      }
  }

void write_current_frame(FILE* input, SPRITE_LIST* sprite_list, ANIMATION_LIST* animation_list, int max_image, ANIMATION** animation)
  {
    int num = sprite_list->num + animation_list->num;
    fwrite(&num, 1, sizeof(int), input);

    SPRITE_NODE* sprite_node = sprite_list->first;

    for(int i = 0; i < sprite_list->num; i++)
      {
        fwrite(&(sprite_node->index), 1, sizeof(int), input);
        fwrite(&(sprite_node->x),     1, sizeof(int), input);
        fwrite(&(sprite_node->y),     1, sizeof(int), input);

        sprite_node = sprite_node->next;
      }

    ANIMATION_NODE* animation_node = animation_list->first;

    for(int i = 0; i < animation_list->num; i++)
      {
        int index = max_image;

        for(int j = 0; j < animation_node->index; j++)
          index += animation[j]->current_num;

        index += animation_node->current_frame;

        std::cout << index << std::endl;

        fwrite(&index, 1, sizeof(int), input);

        fwrite(&(animation_node->x),     1, sizeof(int), input);
        fwrite(&(animation_node->y),     1, sizeof(int), input);

        animation_node = animation_node->next;
      }
  }

#endif
