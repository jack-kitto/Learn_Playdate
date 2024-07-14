#include "src/graphics/graphics.h"
#include "src/game/game.h"

static Game *game;
static Graphics graphics;
void drawPatternRect(int x, int y, int width, int height,
                     LCDPattern *lcdPattern);

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
  graphics.drawPatternRect = &drawPatternRect;
  LCDBitmap *img = loadImageAtPath("images/background", g->pd);
  g->pd->graphics->drawBitmap(img, 0, 0, kBitmapUnflipped);
  return &graphics;
}

void drawPatternRect(int x, int y, int width, int height,
                     LCDPattern *lcdPattern) {
  LCDBitmap *lcdBitmap =
      game->pd->graphics->newBitmap(width, height, (LCDColor)lcdPattern);
  game->pd->graphics->drawBitmap(lcdBitmap, x, y, kBitmapUnflipped);
  game->pd->graphics->drawBitmap(lcdBitmap, x, y, kBitmapUnflipped);
  game->pd->graphics->freeBitmap(lcdBitmap);
}
