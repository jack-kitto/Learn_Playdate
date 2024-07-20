#include "camera.h"
#include "src/defs.h"
#include "src/player/player.h"
#include <stdlib.h>

struct Camera {
  Box world;
  Box screen;
  Vec2 scale;
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
  self->scale = Vec2_divide(self->world.length, self->screen.length);
  return self;
}

int Camera_setup(Camera *self) {
  if (!self) {
    return 1;
  }
  return 0;
}

int Camera_update(Camera *self, Player *player) {
  if (!self || !player) {
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

int Camera_WorldToScreenBox(Camera *self, Box *b) {
  if (!self || !b) {
    return 1;
  }
  Box res;
  // Calculate the position of the box relative to the camera's world position
  Vec2 boxPositionRelativeToCamera = Vec2_subtract(b->pos, self->world.pos);
  // Convert to screen coordinates by applying scale
  res.pos = Vec2_multiply(boxPositionRelativeToCamera, self->scale);
  // Convert the box dimensions to screen coordinates
  res.length = Vec2_multiply(b->length, self->scale);
  // Update the box with the result
  *b = res;
  return 0;
}

int Camera_WorldToScreenCoord(Camera *self, Vec2 *p) {
  if (!self || !p) {
    return 1;
  }
  Vec2 res;
  // Calculate the position of the point relative to the camera's world position
  Vec2 boxPositionRelativeToCamera = Vec2_subtract(*p, self->world.pos);
  // Convert to screen coordinates by applying scale
  res = Vec2_multiply(boxPositionRelativeToCamera, self->scale);
  // Update the point with the result
  *p = res;
  return 0;
}
