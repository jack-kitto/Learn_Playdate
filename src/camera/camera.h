#ifndef CAMERA_H
#define CAMERA_H

typedef struct Camera Camera;
struct Camera {
  float worldX;
  float worldY;
  int viewPortWidth;
  int viewPortHeight;
  int worldWidth;
  int worldHeight;
};

typedef struct Game Game;
Camera *initialiseCamera(Game *g);

#endif
