#include "camera.h"
#include "pd_api.h"
#include "src/defs.h"
#include "src/game/game.h"
#include "src/level/level.h"
#include "src/player/player.h"
#include <stdlib.h>

struct Camera {
  Box world;
  Box screen;
  Vec2 scale;
};
int followPlayer_(Camera *self, Player *player);

Camera *Camera_new() {
  Camera *self = malloc(sizeof(Camera));
  self->world.pos = Vec2_new(0, 0);
  self->world.length = Vec2_new(0, 0);
  self->screen.length = Vec2_new(400, 240);
  self->screen.pos = Vec2_new(0, 0);
  self->scale = Vec2_new(0, 0);
  return self;
}

int Camera_setup(Camera *self, Game *game) {
  if (!self || !game) {
    return 1;
  }
  Level *level = Game_getLevel(game);
  if (!level) {
    return 1;
  }
  PlaydateAPI *pd = Game_getPd(game);
  Vec2 tileSize_px = Level_getTileSize(level);
  self->world.length = Vec2_divide(self->screen.length, tileSize_px);
  self->scale = Vec2_divide(self->screen.length, self->world.length);
  pd->system->logToConsole("Camera length");
  Vec2_print(pd, self->world.length);
  followPlayer_(self, Game_getPlayer(game));
  return 0;
}

int Camera_update(Camera *self, Player *player) {
  if (!self || !player) {
    return 1;
  }
  followPlayer_(self, player);
  return 0;
}

int Camera_delete(Camera *self) {
  if (!self) {
    return 1;
  }
  free(self);
  return 0;
}

int followPlayer_(Camera *self, Player *player) {
  if (!player || !self) {
    return 1;
  }
  Vec2 playerPos = Player_getWorldPos(player);
  Vec2 halfCamera = Vec2_divideScalar(self->world.length, 2);
  self->world.pos =
      Vec2_add(Vec2_subtract(playerPos, halfCamera),
               Vec2_divideScalar(Player_getHitBox(player).length, 2));
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

Vec2 Camera_getScale(Camera *self) { return self->scale; }
Box Camera_getWorld(Camera *self) { return self->world; }
Box Camera_getScreen(Camera *self) { return self->screen; }
