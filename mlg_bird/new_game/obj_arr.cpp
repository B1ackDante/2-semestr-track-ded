//===========================================================
typedef struct object
  {
    Texture* texture;
    Sprite*  sprite;
  } OBJECT;

OBJECT* read_object(FILE* input)
  {
    int num = 0;

    fread(&num, 1, sizeof(int), input);

    OBJECT* object = (OBJECT*)calloc(num, sizeof(OBJECT));

    for(int i = 0; i < num; i++)
      {
        int len = 0;
        fread(&len, 1, sizeof(int), input);

        char* str = (char*)calloc(num, sizeof(char));
        fread(str, len, sizeof(char), input);

        char* filename = (char*)calloc(100, sizeof(char));
        strcpy(filename, "../textures/");
        strcat(filename, str);

        object[i].texture = new Texture;
        object[i].texture->loadFromFile(filename);

        object[i].sprite = new Sprite;
        object[i].sprite->setTexture(*(object[i].texture));

        free(str);
        free(filename);
      }

    return object;
  }
//===========================================================

//===========================================================
typedef struct game_buffer
  {
    double inc;
    long int max_size;
    long int ptr;
    char* data;
  } GAME_BUFFER;

GAME_BUFFER* read_game_buffer(FILE* input)
  {
    long int first  = ftell(input);
    fseek(input, 0, SEEK_END);
    long int second = ftell(input);
    fseek(input, first, SEEK_SET);

    long int file_len = second - first;

    GAME_BUFFER* game_buffer = (GAME_BUFFER*)calloc(1, sizeof(GAME_BUFFER));
    std::cout << file_len << std::endl;
    game_buffer->data = (char*)calloc(file_len, sizeof(char));
    fread(game_buffer->data, file_len, sizeof(char), input);

    game_buffer->ptr = 0;
    game_buffer->inc = 0;
    game_buffer->max_size  = second - first;

    return game_buffer;
  }

bool inc_game_buffer(GAME_BUFFER* game_buffer, double time)
  {
    game_buffer->inc += 24*time / 1000000;

    while(game_buffer->inc > 1)
      {
        if(game_buffer->ptr >= game_buffer->max_size) return false;

        int num = *(int*)(game_buffer->data + game_buffer->ptr);
        game_buffer->ptr += sizeof(int);

        game_buffer->ptr += sizeof(int)*3 * num;

        game_buffer->inc--;
      }

    return true;
  }

void draw_game_buffer(GAME_BUFFER* game_buffer, OBJECT* object, RenderWindow & window, double bias)
  {
    long int index = game_buffer->ptr;

    int num = *(int*)(game_buffer->data + index);
    index += sizeof(int);

    for(int i = 0; i < num; i++)
      {
        int image = *(int*)(game_buffer->data + index);
        index += sizeof(int);

        int x = *(int*)(game_buffer->data + index);
        index += sizeof(int);

        int y = *(int*)(game_buffer->data + index);
        index += sizeof(int);

        object[image].sprite->setPosition(x - bias, y);

        window.draw(*object[image].sprite);
      }
  }
//===========================================================
