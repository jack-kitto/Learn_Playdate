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
void Player_setWorldPos(Player *player, Vec2 p) { player->worldPos = p; };
void Player_setWorldX(Player *player, float x) { player->worldPos.x = x; };
void Player_setWorldY(Player *player, float y) { player->worldPos.y = y; };

Player *Player_new() {
  Vec2 p = {.x = 0, .y = 0};
  Vec2 vel = {.x = 0, .y = 0};
  Player *player = malloc(sizeof(Player));
  player->worldPos = p;
  player->vel = vel;
  return player;
}

void Player_setup(Player *player, PlaydateAPI *pd) {}
void Player_update(Player *player, PlaydateAPI *pd) {}

void Player_delete(Player *player) {
  if (player) {
    free(player);
  }
}

// void drawPlayer(Player *player, PlaydateAPI *pd) {};

// TODO: Setup player starting position
//   game.player->worldX = start.x - (int)(game.camera->worldWidth / 2);
//   game.player->worldY = start.y - (int)(game.camera->worldHeight / 2);
