// game.h
#pragma once
#ifndef game_h
#define game_h
#include "src/camera/camera.h"
#include "src/graphics/graphics.h"

typedef struct Game Game;
typedef enum { GAME_MENU, GAME_ACTIVE } State;

int Game_update(void *userdata);
Game *Game_new(PlaydateAPI *pd);
int Game_delete(Game *game);
int Game_setup(Game *game);
int Game_printState(Game *game);
int Game_print(Game *game, const char *fmt, ...);
int Game_error(Game *game, const char *fmt, ...);

#endif /* game_h */
