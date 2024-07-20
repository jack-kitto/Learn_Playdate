#ifndef CAMERA_H
#define CAMERA_H

#include "src/defs.h"
typedef struct Camera Camera;
struct Camera {
  Box worldBox;
  int viewPortWidth;
  int viewPortHeight;
};

typedef struct Game Game;
Camera *initialiseCamera(Game *g);

#endif
