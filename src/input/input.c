#include "input.h"
#include "src/game/game.h"

static Input input;
static Game *game;

int buttonCb(PDButtons button, int down, uint32_t when, void *userdata) {
  PlaydateAPI *pd = userdata;
  // pd->system->logToConsole("Handling button cb");
  // game.print("Handling button cb");
  if (game->state == MENU && down) {
    game->startGame();
    return 0;
  }

  if (down) {
    if (button == kButtonA) {
      game->print("A pressed!");
    } else if (button == kButtonB) {
      game->print("B pressed!");
    } else if (button == kButtonLeft) {
      game->print("Left pressed!");
    } else if (button == kButtonRight) {
      game->print("Right pressed!");
    } else if (button == kButtonUp) {
      game->print("Up pressed!");
    } else if (button == kButtonDown) {
      game->print("Down pressed!");
    }
  } else {
    if (button == kButtonA) {
      game->print("A released!");
    } else if (button == kButtonB) {
      game->print("B released!");
    } else if (button == kButtonLeft) {
      game->print("Left released!");
    } else if (button == kButtonRight) {
      game->print("Right released!");
    } else if (button == kButtonUp) {
      game->print("Up released!");
    } else if (button == kButtonDown) {
      game->print("Down released!");
    }
  }
  return 0;
}

Input *initialiseInput(Game *g) {
  game = g;
  input.buttonCb = &buttonCb;
  g->pd->system->setButtonCallback(input.buttonCb, g->pd, 5);
  return &input;
}
