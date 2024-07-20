// game.c
#include "game.h"
#include "src/defs.h"
#include "src/player/player.h"
#include <stdint.h>

static Game game;

int update(void *userdata);
int setupGame(void);
void startGame(void);
void print(char *str) { game.pd->system->logToConsole(str); }

int setupGame() {
  game.pd->system->setUpdateCallback(game.update, game.pd);
  game.print("Setting Up Game.");
  return 0;
}

int update(void *userdata) {
  PlaydateAPI *pd = userdata;
  return 0;
}

Game *initialiseGame(PlaydateAPI *pd) {
  game.print = &print;
  game.update = &update;
  game.setupGame = &setupGame;
  game.pd = pd;
  game.state = MENU;
  game.startGame = &startGame;
  game.input = initialiseInput(&game);
  game.graphics = initialiseGraphics(&game);
  game.level = initialiseLevel(&game);
  game.camera = initialiseCamera(&game);
  game.patterns = initialisePatterns();
  game.player = Player_new();
  game.setupGame();
  return &game;
}

void startGame() {
  game.print("Starting game.");
  game.state = ACTIVE;
  Vec2 start = game.level->getStartPosition();
  game.level->drawLevel();
  // game.level->printLevel();
  // game.pd->graphics->clear(kColorWhite);
  // game.player->drawPlayer();
}
