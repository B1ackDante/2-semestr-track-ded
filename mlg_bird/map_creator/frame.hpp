#ifndef FRAME_HPP
#define FRAME_HPP

#define FRAME_HEIGHT  180.0
#define FRAME_WIDTH   320.0

typedef struct frame
  {
    Texture* texture;
    Sprite* sprite;
  } FRAME;

FRAME* create_frame(int num)
  {
    FRAME* frame = (FRAME*)calloc(1, sizeof(FRAME));

    char* file_name = (char*) calloc(100, sizeof(char));
    sprintf(file_name, "video/image%05d.png", num);

    frame->texture = new Texture;
    frame->texture->loadFromFile(file_name);

    frame->sprite = new Sprite;
    frame->sprite->setTexture(*frame->texture);
    frame->sprite->setScale(1000 / FRAME_WIDTH, 700 / FRAME_HEIGHT);

    free(file_name);

    return frame;
  }

#endif
