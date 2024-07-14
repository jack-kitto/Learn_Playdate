// main.c

#include "game/game.h"
#include <stdio.h>
#include <stdlib.h>

const char *fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";
LCDFont *font = NULL;

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
  (void)arg; // arg is currently only used for event = kEventKeyPressed
  if (event == kEventInit) {
    const char *err;
    font = pd->graphics->loadFont(fontpath, &err);
    if (font == NULL)
      pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__,
                        fontpath, err);
    // Note: If you set an update callback in the kEventInit handler, the system
    // assumes the game is pure C and doesn't run any Lua code in the game
    Game *game = initialiseGame(pd);
    // setup(pd);
  }
  return 0;
}
