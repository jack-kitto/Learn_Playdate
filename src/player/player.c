#include "player.h"
#include "pd_api.h"
#include "src/defs.h"
#include <stdlib.h>
#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 32

struct Player {
  Vec2 worldPos;
  Vec2 vel;
};

Vec2 Player_getWorldPos(Player *player) { return player->worldPos; }
int Player_setWorldPos(Player *player, Vec2 p) {
  if (!player) {
    return 1;
  }
  player->worldPos = p;
  return 0;
};

int Player_setWorldX(Player *player, float x) {
  if (!player) {
    return 1;
  }
  player->worldPos.x = x;
  return 0;
};
int Player_setWorldY(Player *player, float y) {
  if (!player) {
    return 1;
  }
  player->worldPos.y = y;
  return 0;
};

Player *Player_new() {
  Vec2 p = {.x = 0, .y = 0};
  Vec2 vel = {.x = 0, .y = 0};
  Player *player = malloc(sizeof(Player));
  player->worldPos = p;
  player->vel = vel;
  return player;
}

int Player_setup(Player *player, PlaydateAPI *pd) {
  if (!player) {
    return 1;
  }
  if (!pd) {
    return 1;
  }
  return 0;
}
int Player_update(Player *player, PlaydateAPI *pd) {
  if (!player) {
    return 1;
  }
  if (!pd) {
    return 1;
  }
  return 0;
}

int Player_delete(Player *player) {
  if (!player) {
    return 1;
  }
  free(player);
  return 0;
}

// void drawPlayer(Player *player, PlaydateAPI *pd) {};

// TODO: Setup player starting position
//   game.player->worldX = start.x - (int)(game.camera->worldWidth / 2);
//   game.player->worldY = start.y - (int)(game.camera->worldHeight / 2);
