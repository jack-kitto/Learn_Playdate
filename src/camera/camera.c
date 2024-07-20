#include "camera.h"
#include "src/defs.h"
#include "src/player/player.h"
#include <stdlib.h>

struct Camera {
  Box world;
  Box screen;
};

Box Camera_getWorld(Camera *self) { return self->world; }
Box Camera_getScreen(Camera *self) { return self->screen; }

Camera *Camera_new() {
  Camera *self = malloc(sizeof(Camera));
  self->world.pos.x = 0;
  self->world.pos.y = 0;
  self->world.length.y = 4;
  self->world.length.x = 4;
  self->screen.pos.x = 0;
  self->screen.pos.y = 0;
  self->screen.length.y = 240;
  self->screen.length.x = 400;
  return self;
}

int Camera_setup(Camera *self) {
  if (!self) {
    return 1;
  }
  return 0;
}

int Camera_update(Camera *self, Player *player) {
  if (!self) {
    return 1;
  }
  if (!player) {
    return 1;
  }
  Vec2 playerPos = Player_getWorldPos(player);
  Vec2 halfCamera = Vec2_divideScalar(self->world.length, 2);
  self->world.pos = Vec2_subtract(playerPos, halfCamera);
  return 0;
}

int Camera_delete(Camera *self) {
  if (!self) {
    return 1;
  }
  free(self);
  return 0;
}
