#include "player.h"
#include "src/defs.h"
#include "src/game/game.h"
#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 32

static Game *game;
static Player player;
void drawPlayer(void);

Player *initialisePlayer(Game *g) {
  Vec2 p = {.x = 0, .y = 0};
  Vec2 vel = {.x = 0, .y = 0};
  player.worldPos = p;
  player.vel = vel;
  player.drawPlayer = &drawPlayer;
  game = g;
  return &player;
}

void drawPlayer() {
  int x = 10;
  int y = 10;
  game->graphics->drawPatternRect(x, y, PLAYER_WIDTH, PLAYER_HEIGHT,
                                  game->patterns->grey50);
}

// TODO: Setup player starting position
//   game.player->worldX = start.x - (int)(game.camera->worldWidth / 2);
//   game.player->worldY = start.y - (int)(game.camera->worldHeight / 2);
