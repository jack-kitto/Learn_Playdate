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
  (void)arg; // arg is currently only used for event = kEventKeyPressed
  const char *err;
  switch (event) {
  case kEventInit:
    pd->display->setRefreshRate(20);
    font = pd->graphics->loadFont(fontpath, &err);
    if (font == NULL)
      pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__,
                        fontpath, err);
    // Note: If you set an update callback in the kEventInit handler, the system
    // assumes the game is pure C and doesn't run any Lua code in the game
    game = Game_new(pd);
    Game_setup(game);
    pd->system->setUpdateCallback(Game_update, game);
    break;
  case kEventInitLua:
    pd->system->logToConsole("Event: kEventInitLua");
    break;
  case kEventKeyPressed:
    pd->system->logToConsole("Event: kEventKeyPressed");
    break;
  case kEventKeyReleased:
    pd->system->logToConsole("Event: kEventKeyReleased");
    break;
  case kEventLock:
    pd->system->logToConsole("Event: kEventLock");
    break;
  case kEventUnlock:
    pd->system->logToConsole("Event: kEventUnlock");
    break;
  case kEventPause:
    pd->system->logToConsole("Event: kEventPause");
    break;
  case kEventResume:
    pd->system->logToConsole("Event: kEventResume");
    break;
  case kEventLowPower:
    pd->system->logToConsole("Event: kEventLowPower");
    break;
  case kEventTerminate:
    Game_delete(game);
    break;
  };
  return 0;
}
