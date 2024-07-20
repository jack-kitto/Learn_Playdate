// game.c
#include "game.h"
#include "src/level/level.h"
#include "src/player/player.h"
#include <stdint.h>

struct Game {
  State state;
  PlaydateAPI *pd;
  Level *level;
  Player *player;
  Camera *camera;
};

Game *Game_new(PlaydateAPI *pd) {
  Game *game = malloc(sizeof(Game));
  game->state = GAME_MENU;
  game->level = Level_new();
  game->camera = initialiseCamera(game);
  game->pd = pd;
  game->player = Player_new();
  return game;
}

int Game_setup(Game *g) {
  if (!g) {
    return 1;
  }
  Level_print(g->level, g->pd);
  Player_setup(g->player, g->pd);
  int error = Level_draw(g->level, g->pd, g->camera);
  if (error) {
    Game_error(g, "Error occurred drawing level");
  }
  return 0;
}

int Game_update(void *userdata) {
  Game *g = userdata;
  if (!g) {
    return 1;
  }
  Game_printState(g);
  return 0;
}

int Game_delete(Game *game) {
  if (!game) {
    return 1;
  }
  Level_delete(game->level);
  Player_delete(game->player);
  free(game);
  return 0;
}

int Game_printState(Game *g) {
  if (!g) {
    return 1;
  }
  switch (g->state) {
  case GAME_MENU:
    Game_print(g, "Menu");
    break;
  case GAME_ACTIVE:
    Game_print(g, "Active");
    break;
  default:
    Game_print(g, "Unknown");
    break;
  }
  return 0;
};

int Game_print(Game *game, const char *fmt, ...) {
  if (!game) {
    return 1;
  }

  va_list args;
  va_start(args, fmt);
  game->pd->system->logToConsole(fmt, args);
  va_end(args);

  return 0;
}

int Game_error(Game *game, const char *fmt, ...) {
  if (!game) {
    return 1;
  }

  va_list args;
  va_start(args, fmt);
  game->pd->system->error(fmt, args);
  va_end(args);

  return 0;
}
