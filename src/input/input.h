#ifndef INPUT_H
#define INPUT_H
#include "pd_api.h"
typedef struct Input Input;
typedef struct Game Game;

struct Input {
  int (*buttonCb)(PDButtons button, int down, uint32_t when, void *userdata);
};

Input *initialiseInput(Game *game);
#endif // !INPUT_H
