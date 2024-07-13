// game.c
#include "game.h"
#include <stdint.h>

int buttonCb(PDButtons button, int down, uint32_t when, void *userdata);
enum View { title_screen, game };
enum View view = title_screen;
int onStartGame(PlaydateAPI *pd);
int level = 1;

int setup(PlaydateAPI *pd) {
  pd->system->logToConsole("Setting Up Game.");
  pd->system->setButtonCallback(buttonCb, pd, 5);
  LCDBitmap *img = loadImageAtPath("images/background", pd);
  pd->graphics->drawBitmap(img, 0, 0, kBitmapUnflipped);
  return 0;
}

int update(void *userdata) {
  PlaydateAPI *pd = userdata;
  return 0;
}

int buttonCb(PDButtons button, int down, uint32_t when, void *userdata) {
  PlaydateAPI *pd = userdata;
  if (view == title_screen && down) {
    onStartGame(pd);
    return 0;
  }

  if (down) {
    if (button == kButtonA) {
      pd->system->logToConsole("A pressed!");
    } else if (button == kButtonB) {
      pd->system->logToConsole("B pressed!");
    } else if (button == kButtonLeft) {
      pd->system->logToConsole("Left pressed!");
    } else if (button == kButtonRight) {
      pd->system->logToConsole("Right pressed!");
    } else if (button == kButtonUp) {
      pd->system->logToConsole("Up pressed!");
    } else if (button == kButtonDown) {
      pd->system->logToConsole("Down pressed!");
    }
  } else {
    if (button == kButtonA) {
      pd->system->logToConsole("A released!");
    } else if (button == kButtonB) {
      pd->system->logToConsole("B released!");
    } else if (button == kButtonLeft) {
      pd->system->logToConsole("Left released!");
    } else if (button == kButtonRight) {
      pd->system->logToConsole("Right released!");
    } else if (button == kButtonUp) {
      pd->system->logToConsole("Up released!");
    } else if (button == kButtonDown) {
      pd->system->logToConsole("Down released!");
    }
  }
  return 0;
}

int onStartGame(PlaydateAPI *pd) {
  pd->system->logToConsole("Starting Game.");
  view = game;
  return 0;
}
