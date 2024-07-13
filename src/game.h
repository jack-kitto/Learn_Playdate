// game.h

#ifndef game_h
#define game_h

#include "pd_api.h"

int update(void *userdata);
int setup(PlaydateAPI *pd);
LCDBitmap *loadImageAtPath(const char *path, PlaydateAPI *pd);

#endif /* game_h */
