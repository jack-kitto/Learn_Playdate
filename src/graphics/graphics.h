#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "pd_api.h"
typedef struct Graphics Graphics;
struct Graphics {
  LCDBitmap *(*loadImageAtPath)(const char *path, PlaydateAPI *pd);
};

typedef struct Game Game;

Graphics *initialiseGraphics(Game *game);

#endif // !GRAPHICS_H
