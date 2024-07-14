#include "src/graphics/graphics.h"
#include "src/game/game.h"

static Game *game;
static Graphics graphics;

LCDBitmap *loadImageAtPath(const char *path, PlaydateAPI *pd) {
  const char *outErr = NULL;
  LCDBitmap *img = pd->graphics->loadBitmap(path, &outErr);
  if (outErr != NULL) {
    pd->system->logToConsole("Error loading image at path '%s': %s", path,
                             outErr);
  }
  return img;
}

Graphics *initialiseGraphics(Game *g) {
  game = g;
  graphics.loadImageAtPath = &loadImageAtPath;
  LCDBitmap *img = loadImageAtPath("images/background", g->pd);
  g->pd->graphics->drawBitmap(img, 0, 0, kBitmapUnflipped);
  return &graphics;
}
