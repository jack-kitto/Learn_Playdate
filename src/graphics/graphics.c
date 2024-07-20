#include "src/graphics/graphics.h"
#include "src/defs.h"

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

void drawBox(PlaydateAPI *pd, Box b, LCDPattern *lcdPattern) {
  LCDBitmap *lcdBitmap =
      pd->graphics->newBitmap(b.length.x, b.length.y, (LCDColor)lcdPattern);
  pd->graphics->drawBitmap(lcdBitmap, b.pos.x, b.pos.y, kBitmapUnflipped);
  pd->graphics->drawBitmap(lcdBitmap, b.pos.x, b.pos.y, kBitmapUnflipped);
  pd->graphics->freeBitmap(lcdBitmap);
}
