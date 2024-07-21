#include "player.h"
#include "pd_api.h"
#include "pd_api/pd_api_sys.h"
#include "src/camera/camera.h"
#include "src/defs.h"
#include "src/graphics/graphics.h"
#include "src/level/level.h"
#include "src/pattern/patterns.h"
#include <stdlib.h>
#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 32

struct Player {
  Vec2 vel;
  Box hitBox;
};
int draw_(Player *self, Camera *camera, PlaydateAPI *pd);
int move_(Player *self, PlaydateAPI *pd, float dt_seconds, Level *level);
void moveClosest_(Player *self, Box b, Level *level, PlaydateAPI *pd);
Vec2 getVelocity_(PlaydateAPI *pd);

Player *Player_new() {
  Player *player = malloc(sizeof(Player));
  player->hitBox.pos = Vec2_new(0, 0);
  player->hitBox.length = Vec2_new(0.8, 0.8);
  player->vel = Vec2_new(0, 0);
  return player;
}

int Player_setup(Player *player, PlaydateAPI *pd, Level *level) {
  if (!player || !pd) {
    return 1;
  }
  player->hitBox.pos = Level_getStart(level);
  return 0;
}

int Player_update(Player *self, PlaydateAPI *pd, Camera *camera,
                  float dt_seconds, Level *level) {
  if (!self || !pd) {
    return 1;
  }
  move_(self, pd, dt_seconds, level);
  draw_(self, camera, pd);
  return 0;
}

Vec2 Player_getWorldPos(Player *player) { return player->hitBox.pos; }
int Player_setWorldPos(Player *player, Vec2 p) {
  if (!player) {
    return 1;
  }
  player->hitBox.pos = p;
  return 0;
};

int Player_setWorldX(Player *player, float x) {
  if (!player) {
    return 1;
  }
  player->hitBox.pos.x = x;
  return 0;
};
int Player_setWorldY(Player *player, float y) {
  if (!player) {
    return 1;
  }
  player->hitBox.pos.y = y;
  return 0;
};

int Player_delete(Player *player) {
  if (!player) {
    return 1;
  }
  free(player);
  return 0;
}

Box Player_getHitBox(Player *self) { return self->hitBox; }

int draw_(Player *self, Camera *camera, PlaydateAPI *pd) {
  if (!self || !camera || !pd) {
    return 1;
  }
  Box cameraBox = Camera_getWorld(camera), playerBox;
  Vec2 playerPos = self->hitBox.pos,
       posRelativeToCamera = Vec2_subtract(playerPos, cameraBox.pos);
  playerBox.pos = Vec2_multiply(posRelativeToCamera, Camera_getScale(camera));
  playerBox.length =
      Vec2_multiply(self->hitBox.length, Camera_getScale(camera));
  drawBox(pd, playerBox, Pattern_new(PATTERN_GREY50));
  return 0;
}

Vec2 getVelocity_(PlaydateAPI *pd) {
  Vec2 v = Vec2_new(0, 0);
  PDButtons current, pushed, released;
  float VELOCITY_INCREMENT = 0.2f;
  pd->system->getButtonState(&current, &pushed, &released);
  if (current & kButtonLeft) {
    v.x -= VELOCITY_INCREMENT;
  }
  if (current & kButtonRight) {
    v.x += VELOCITY_INCREMENT;
  }
  if (current & kButtonUp) {
    v.y -= VELOCITY_INCREMENT;
  }
  if (current & kButtonDown) {
    v.y += VELOCITY_INCREMENT;
  }
  return v;
}

int canMoveTo(Player *self, Box b, Level *level, PlaydateAPI *pd) {
  int res = 1;
  Vec2 tl = Box_getTL(b);
  Vec2 bl = Box_getBL(b);
  Vec2 br = Box_getBR(b);
  Vec2 tr = Box_getTR(b);
  if (Level_getTileAt(level, tl, pd) == BLOCK) {
    res = 0;
  }
  if (Level_getTileAt(level, bl, pd) == BLOCK) {
    res = 0;
  }
  if (Level_getTileAt(level, br, pd) == BLOCK) {
    res = 0;
  }
  if (Level_getTileAt(level, tr, pd) == BLOCK) {
    res = 0;
  }
  return res;
}

void moveClosest_(Player *self, Box b, Level *level, PlaydateAPI *pd) {
  // Vec2 originalPos = self->hitBox.pos;
  // Vec2 targetPos = b.pos;
  // Vec2 direction = Vec2_subtract(targetPos, originalPos);
  // float step = 0.1f; // Adjust step size for finer collision checking
  // Vec2 stepVector = Vec2_multiplyScalar(direction, step);
  // Box checkBox = self->hitBox;
  //
  // while (Vec2_length(direction) > 0.0f) {
  //   checkBox.pos = Vec2_add(checkBox.pos, stepVector);
  //   if (canMoveTo(self, checkBox, level, pd)) {
  //     self->hitBox.pos = checkBox.pos;
  //     break;
  //   }
  //   direction = Vec2_subtract(targetPos, checkBox.pos);
  // }
}

int move_(Player *self, PlaydateAPI *pd, float dt_seconds, Level *level) {
  if (!self || !pd || !level) {
    return 1;
  }
  // reset player velocity so that the player doesn't accelerate;
  self->vel = Vec2_new(0, 0);
  Vec2 vel = getVelocity_(pd), newPos = Vec2_add(self->hitBox.pos, vel);
  Box newPlayerBox;
  newPlayerBox.pos = newPos;
  newPlayerBox.length = self->hitBox.length;
  if (canMoveTo(self, newPlayerBox, level, pd)) {
    self->hitBox = newPlayerBox;
  } else {
    moveClosest_(self, newPlayerBox, level, pd);
  }
  return 0;
}
