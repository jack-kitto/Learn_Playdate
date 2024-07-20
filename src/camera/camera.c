#include "camera.h"
#include "src/defs.h"
#include "src/game/game.h"

static Camera camera;
static Game *game;

Camera *initialiseCamera(Game *g) {
  Vec2 p = {.x = 0, .y = 0};
  camera.worldPos = p;
  camera.worldWidth = 4;
  camera.worldHeight = 4;
  game = g;
  return &camera;
}
