// game.h
#pragma once
#ifndef game_h
#define game_h
#include "pd_api.h"
#include "src/camera/camera.h"
#include "src/graphics/graphics.h"
#include "src/input/input.h"
#include "src/level/level.h"
#include "src/player/player.h"

typedef struct Game Game;
typedef enum { MENU, ACTIVE } State;
/*View *view;*/

struct Game {
  State state;

  PlaydateAPI *pd;
  Input *input;
  Level *level;
  Player *player;
  Camera *camera;

  int (*update)(void *userdata);
  int (*setupGame)(void);
  void (*startGame)(void);
  void (*print)(char *str);
};

Game *initialiseGame(PlaydateAPI *pd);

#endif /* game_h */
