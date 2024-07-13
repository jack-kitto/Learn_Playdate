// game.c

#include "game.h"

int setup(PlaydateAPI *pd) {
  pd->system->logToConsole("Setting Up Game.");
  return 0;
}

int update(void *userdata) {
  PlaydateAPI *pd = userdata;
  pd->system->logToConsole("Updating Game.");
  return 1;
}
