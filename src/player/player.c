#include "player.h"
#include "src/game/game.h"

static Game *game;
static Player player;
void drawPlayer(void);

Player *initialisePlayer(Game *g) {
  player.worldX = 0;
  player.worldY = 0;
  player.velocityX = 0;
  player.velocityY = 0;
  game = g;
  return &player;
}
void drawPlayer(void) {}
