#include "game.h"

LCDBitmap *loadImageAtPath(const char *path, PlaydateAPI *pd) {
  const char *outErr = NULL;
  LCDBitmap *img = pd->graphics->loadBitmap(path, &outErr);
  if (outErr != NULL) {
    pd->system->logToConsole("Error loading image at path '%s': %s", path,
                             outErr);
  }
  return img;
}
