#include "player.h"
#include "src/game/game.h"
#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 32

static Game *game;
static Player player;
void drawPlayer(void);

Player *initialisePlayer(Game *g) {
  player.worldX = 0;
  player.worldY = 0;
  player.velocityX = 0;
  player.velocityY = 0;
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
