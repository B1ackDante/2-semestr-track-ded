#ifndef GAME_BUFFER_HPP
#define GAME_BUFFER_HPP

#define MAX_FRAME 1379
#define FRAME_HEIGHT  180.0
#define FRAME_WIDTH   320.0

#define ROTATE_CONST 150

typedef struct object
  {
    Texture* texture;
    Sprite*  sprite;
    SoundBuffer* s_buffer;
    Sound* sound;
  } OBJECT;


class GameBuffer
  {
  public:

    Texture** back_texture_;
    Sprite** back_sprite_;
    int current_num;
    Music* music_;

    double inc_;
    long int max_size_;
    long int ptr_;

    OBJECT* object_;
    char* data_;

    View* view_;
    bool is_rotate_;

    GameBuffer(const char* mlg_name);
    ~GameBuffer();

    bool inc(double time);
    bool collision(Hero & hero, double bias);
    void draw(RenderWindow & window, double bias);
  };

GameBuffer::GameBuffer(const char* mlg_name)
  {
    char* mus = (char*)calloc(100, sizeof(char));
    sprintf(mus, "../mlg_files/%s/music.wav", mlg_name);
    music_ = new Music;
    music_->openFromFile(mus);
    free(mus);

    current_num = 0;

    back_texture_ = new Texture*[MAX_FRAME];
    back_sprite_  = new Sprite*[MAX_FRAME];
    for(int i = 0; i < MAX_FRAME; i++)
      {
        char* str = (char*)calloc(100, sizeof(char));
        sprintf(str, "../mlg_files/%s/video/image%05d.png", mlg_name, i + 1);

        back_texture_[i] = new Texture;
        back_texture_[i]->loadFromFile(str);

        back_sprite_[i] = new Sprite;
        back_sprite_[i]->setTexture(*back_texture_[i]);
        back_sprite_[i]->setScale(1000 / FRAME_WIDTH, 700 / FRAME_HEIGHT);

        free(str);
      }


    char* filename_head = (char*)calloc(100, sizeof(char));
    sprintf(filename_head, "../mlg_files/%s/head.mlg", mlg_name);
    FILE* input_head = fopen(filename_head, "rb");

    int num = 0;

    fread(&num, 1, sizeof(int), input_head);

    object_ = (OBJECT*)calloc(num, sizeof(OBJECT));

    for(int i = 0; i < num; i++)
      {
        int len = 0;
        fread(&len, 1, sizeof(int), input_head);

        char* str = (char*)calloc(num, sizeof(char));
        fread(str, len, sizeof(char), input_head);

        char* filename = (char*)calloc(100, sizeof(char));
        strcpy(filename, "../textures/");
        strcat(filename, str);

        object_[i].texture = new Texture;
        object_[i].texture->loadFromFile(filename);

        object_[i].sprite = new Sprite;
        object_[i].sprite->setTexture(*(object_[i].texture));

        object_[i].sound = NULL;

        free(str);
        free(filename);
      }

    int sound_num = 0;
    fread(&sound_num, 1, sizeof(int), input_head);

    std::cout << sound_num << std::endl;

    for(int i = 0; i < sound_num; i++)
      {
        int sound_index = 0;
        fread(&sound_index, 1, sizeof(int), input_head);

        int sound_len = 0;
        fread(&sound_len, 1, sizeof(int), input_head);

        char* str = (char*)calloc(sound_len, sizeof(char));
        fread(str, sound_len, sizeof(char), input_head);

        char* filename = (char*)calloc(100, sizeof(char));
        strcpy(filename, "../sound/");
        strncat(filename, str, sound_len); 


        std::cout << filename << std::endl;
        std::cout << sound_index << std::endl;
		std::cout << sound_len << std::endl;

        object_[sound_index].s_buffer = new SoundBuffer;
        object_[sound_index].s_buffer->loadFromFile(filename);

        object_[sound_index].sound = new Sound;
        object_[sound_index].sound->setBuffer(*object_[sound_index].s_buffer);

        free(filename);
        free(str);
      }

    fclose(input_head);
    free(filename_head);


    int file_index = 1;
    int buff_len = 0;
    data_ = (char*)calloc(1, sizeof(char));
    while(true)
      {
        char* filename = (char*)calloc(100, sizeof(char));
        sprintf(filename, "../mlg_files/%s/%d.mlg", mlg_name, file_index);

        FILE* mlg_game = fopen(filename, "rb");

        if(mlg_game == NULL) break;

        long int first  = ftell(mlg_game);
        fseek(mlg_game, 0, SEEK_END);
        long int second = ftell(mlg_game);
        fseek(mlg_game, first, SEEK_SET);

        long int file_len = second - first;

        std::cout << file_len << std::endl;
        data_ = (char*)realloc(data_, (buff_len + file_len)*sizeof(char));
        fread(data_ + buff_len, file_len, sizeof(char), mlg_game);
        buff_len += file_len;

        fclose(mlg_game);
        free(filename);

        file_index++;
      }

    ptr_ = 0;
    inc_ = 0;
    max_size_  = buff_len;

    view_ = new View;
    view_->reset(sf::FloatRect(0, 0, WIN_WIDTH, WIN_HEIGHT));
    view_->setCenter(WIN_WIDTH/2, WIN_HEIGHT/2);

    is_rotate_ = false;
  }

GameBuffer::~GameBuffer()
  {
    free(data_);
    free(object_);
  }

bool GameBuffer::inc(double time)
  {
    inc_ += 24*time / 1000000;

    if(is_rotate_) view_->rotate(ROTATE_CONST*time / 1000000);

    while(inc_ >= 1)
      {
        if(ptr_ >= max_size_ - 10) return false;

        int num = *(int*)(data_ + ptr_);

        ptr_ += sizeof(int);

        if(num < 0)
          {
            switch(num)
              {
                case -1:
                is_rotate_ = true;
                break;
              }

            continue;
          }

        ptr_ += sizeof(int)*3 * num;

        inc_--;

        current_num++;
      }

    return true;
  }

bool GameBuffer::collision(Hero & hero, double bias)
  {
    long int index = ptr_;

    int num = *(int*)(data_ + index);
    index += sizeof(int);

    for(int i = 0; i < num; i++)
      {
        int image = *(int*)(data_ + index);
        index += sizeof(int);

        int x = *(int*)(data_ + index);
        index += sizeof(int);

        int y = *(int*)(data_ + index);
        index += sizeof(int);

        object_[image].sprite->setPosition(x - bias, y);

        if(object_[image].sprite->getGlobalBounds().intersects(hero.sprite_->getGlobalBounds()) == true)
        return true;
      }

    return false;
  }

void GameBuffer::draw(RenderWindow & window, double bias)
  {
    window.draw(*back_sprite_[current_num]);

    long int index = ptr_;

    int num = *(int*)(data_ + index);
    index += sizeof(int);

    for(int i = 0; i < num; i++)
      {
        int image = *(int*)(data_ + index);
        index += sizeof(int);

        int x = *(int*)(data_ + index);
        index += sizeof(int);

        int y = *(int*)(data_ + index);
        index += sizeof(int);

        object_[image].sprite->setPosition(x - bias, y);

        if(object_[image].sound != NULL) object_[image].sound->play();

        window.draw(*object_[image].sprite);
      }

    window.setView(*view_);
  }

#endif
