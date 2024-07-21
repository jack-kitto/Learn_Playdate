// game.c
#include "game.h"
#include "pd_api.h"
#include "src/camera/camera.h"
#include "src/level/level.h"
#include "src/player/player.h"
#include <stdint.h>

struct Game {
  State state;
  PlaydateAPI *pd;
  Level *level;
  Player *player;
  Camera *camera;
  float dt_seconds;
};
int updateDt_(Game *self);

Game *Game_new(PlaydateAPI *pd) {
  Game *game = malloc(sizeof(Game));
  game->state = GAME_MENU;
  game->camera = Camera_new();
  game->level = Level_new();
  game->pd = pd;
  game->player = Player_new();
  game->dt_seconds = 0;
  return game;
}

int Game_setup(Game *g) {
  if (!g) {
    return 1;
  }
  Player_setup(g->player, g->pd, g->level);
  Camera_setup(g->camera, g);
  Level_setup(g->level, g->pd);
  return 0;
}

int Game_update(void *userdata) {
  Game *g = userdata;
  if (!g) {
    return 1;
  }
  int error;
  error = updateDt_(g);
  if (error) {
    Game_error(g, "Error updating the delta time");
  }

  error = Camera_update(g->camera, g->player);
  if (error) {
    Game_error(g, "Error in Camera_update");
  }
  error = Level_update(g->level, g->pd, g->camera);
  if (error) {
    Game_error(g, "Error in Level_update");
  }
  error = Player_update(g->player, g->pd, g->camera, g->dt_seconds, g->level);
  if (error) {
    Game_error(g, "Error in Player_update");
  }
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

Level *Game_getLevel(Game *game) { return game->level; }
Player *Game_getPlayer(Game *game) { return game->player; }
PlaydateAPI *Game_getPd(Game *game) { return game->pd; }
int updateDt_(Game *self) {
  if (!self) {
    return 1;
  }
  float dt_seconds = self->pd->system->getElapsedTime();
  self->pd->system->resetElapsedTime();
  self->dt_seconds = dt_seconds;
  return 0;
}

float Game_getDt(Game *self) { return self->dt_seconds; };
