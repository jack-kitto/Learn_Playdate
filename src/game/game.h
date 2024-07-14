// game.h

#ifndef game_h
#define game_h

#include "pd_api.h"
#include "src/graphics/graphics.h"
#include "src/input/input.h"

typedef struct Game Game;
typedef enum { MENU, ACTIVE } State;
/*View *view;*/

struct Game {
  State state;

  PlaydateAPI *pd;
  Input *input;
  Graphics *graphics;

  int (*update)(void *userdata);
  int (*setupGame)(void);
  void (*startGame)(void);
  void (*print)(char *str);
};

Game *initialiseGame(PlaydateAPI *pd);

#endif /* game_h */
