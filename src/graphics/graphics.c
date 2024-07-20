#include "src/graphics/graphics.h"
#include "src/camera/camera.h"

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

int drawBoxWorld(PlaydateAPI *pd, Camera *camera, Box b,
                 LCDPattern *lcdPattern) {
  if (!pd || !lcdPattern) {
    return 1;
  }
  int error = Camera_WorldToScreenBox(camera, &b);
  if (error) {
    return error;
  }
  LCDBitmap *lcdBitmap =
      pd->graphics->newBitmap(b.length.x, b.length.y, (LCDColor)lcdPattern);
  pd->graphics->drawBitmap(lcdBitmap, b.pos.x, b.pos.y, kBitmapUnflipped);
  pd->graphics->drawBitmap(lcdBitmap, b.pos.x, b.pos.y, kBitmapUnflipped);
  pd->graphics->freeBitmap(lcdBitmap);
  return 0;
}
