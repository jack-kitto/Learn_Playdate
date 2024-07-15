#include "camera.h"
#include "src/game/game.h"

static Camera camera;
static Game *game;

Camera *initialiseCamera(Game *g) {
  camera.worldX = 0;
  camera.worldY = 0;
  camera.worldWidth = 4;
  camera.worldHeight = 4;
  game = g;
  return &camera;
}
