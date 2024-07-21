// main.c

#include "game/game.h"
#include "pd_api.h"
#include <stdio.h>
#include <stdlib.h>

const char *fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";
LCDFont *font = NULL;
Game *game;

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
  (void)arg;
  const char *err;
  switch (event) {
  case kEventInit:
    pd->display->setRefreshRate(20);
    font = pd->graphics->loadFont(fontpath, &err);
    if (font == NULL)
      pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__,
                        fontpath, err);
    game = Game_new(pd);
    Game_setup(game);
    pd->system->setUpdateCallback(Game_update, game);
    break;
  case kEventInitLua:
    break;
  case kEventKeyPressed:
    break;
  case kEventKeyReleased:
    break;
  case kEventLock:
    break;
  case kEventUnlock:
    break;
  case kEventPause:
    break;
  case kEventResume:
    break;
  case kEventLowPower:
    break;
  case kEventTerminate:
    Game_delete(game);
    break;
  };
  return 0;
}
