#ifndef CAMERA_H
#define CAMERA_H

#include "src/defs.h"
typedef struct Camera Camera;
struct Camera {
  Vec2 worldPos;
  int viewPortWidth;
  int viewPortHeight;
  int worldWidth;
  int worldHeight;
};

typedef struct Game Game;
Camera *initialiseCamera(Game *g);

#endif
