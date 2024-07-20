#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "pd_api.h"
#include "src/defs.h"

LCDBitmap *loadImageAtPath(const char *path, PlaydateAPI *pd);

void drawBox(PlaydateAPI *pd, Box b, LCDPattern *lcdPattern);

typedef struct Game Game;

#endif // !GRAPHICS_H
