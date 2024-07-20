#include "camera.h"
#include "src/defs.h"
#include "src/game/game.h"

static Camera camera;
static Game *game;

Camera *initialiseCamera(Game *g) {
  Vec2 pos = {.x = 0, .y = 0};
  Vec2 size = {.x = 4, .y = 0};
  Box b = {.pos = pos, .length = size};
  camera.worldBox = b;
  game = g;
  return &camera;
}
