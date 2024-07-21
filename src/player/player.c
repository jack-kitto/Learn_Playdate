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
  float moveSpeed;
  float jumpSpeed;
  Vec2 gravity;
  Box hitBox;
};
int draw_(Player *self, Camera *camera, PlaydateAPI *pd);
int move_(Player *self, PlaydateAPI *pd, float dt_seconds, Level *level);
void handleCollision_(Player *self, Box b, Level *level, PlaydateAPI *pd,
                      Vec2 vel);
void setDirections_(int *left, int *up, int *right, int *down, Vec2 vel);
Vec2 getVelocity_(Player *self, PlaydateAPI *pd);

Player *Player_new() {
  Player *player = malloc(sizeof(Player));
  player->hitBox.pos = Vec2_new(0, 0);
  player->hitBox.length = Vec2_new(0.99, 0.99);
  player->vel = Vec2_new(0, 0);
  player->gravity = Vec2_new(0, 0.4);
  player->moveSpeed = 0.2f;
  player->jumpSpeed = 0.6f;
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

Vec2 getVelocity_(Player *self, PlaydateAPI *pd) {
  Vec2 v = Vec2_new(0, 0);
  PDButtons current, pushed, released;
  pd->system->getButtonState(&current, &pushed, &released);
  if (current & kButtonLeft) {
    v.x -= self->moveSpeed;
  } else if (current & kButtonRight) {
    v.x += self->moveSpeed;
  } else if (current & kButtonUp) {
    v.y -= self->moveSpeed;
  } else if (current & kButtonDown) {
    v.y += self->moveSpeed;
  }
  if (current & kButtonA) {
    v.y -= self->jumpSpeed;
  }
  return v;
}

void setDirections_(int *left, int *up, int *right, int *down, Vec2 vel) {
  if (vel.y > 0) {
    *down = 1;
  }
  if (vel.y < 0) {
    *up = 1;
  }
  if (vel.x < 0) {
    *left = 1;
  }
  if (vel.x > 0) {
    *right = 1;
  }
}

int move_(Player *self, PlaydateAPI *pd, float dt_seconds, Level *level) {
  if (!self || !pd || !level) {
    return 1;
  }
  // reset player velocity so that the player doesn't accelerate;
  self->vel = Vec2_new(0, 0);
  self->vel = getVelocity_(self, pd);
  self->vel = Vec2_add(self->vel, self->gravity);
  Vec2 newPos = Vec2_add(self->hitBox.pos, self->vel);

  int movingLeft = 0, movingRight = 0, movingUp = 0, movingDown = 0;
  setDirections_(&movingLeft, &movingUp, &movingRight, &movingDown, self->vel);

  if (movingRight) { // moving right
    Vec2 tr = Vec2_new(newPos.x + 1, self->hitBox.pos.y);
    Vec2 br = Vec2_new(newPos.x + 1, self->hitBox.pos.y + 0.9);
    int trHit = Level_isCollision(level, pd, tr);
    int brHit = Level_isCollision(level, pd, br);
    if (trHit || brHit) {
      pd->system->logToConsole("right hit");
      newPos.x = (int)newPos.x;
    }
  }
  if (movingLeft) { // moving left
    Vec2 tl = newPos;
    Vec2 bl = Vec2_new(newPos.x, self->hitBox.pos.y + 0.9);
    int tlHit = Level_isCollision(level, pd, tl);
    int blHit = Level_isCollision(level, pd, bl);
    if (tlHit || blHit) {
      pd->system->logToConsole("left hit");
      newPos.x = (int)newPos.x + 1;
    }
  }
  if (movingDown) { // moving down
    Vec2 bl = Vec2_new(newPos.x, newPos.y + 1);
    Vec2 br = Vec2_new(newPos.x + 0.9, newPos.y + 1);
    int blHit = Level_isCollision(level, pd, bl);
    int brHit = Level_isCollision(level, pd, br);
    if (blHit || brHit) {
      newPos.y = (int)newPos.y;
    }
  }
  if (movingUp) { // moving up
    Vec2 tl = Vec2_new(newPos.x, newPos.y);
    Vec2 tr = Vec2_new(newPos.x + 0.9, newPos.y);
    int tlHit = Level_isCollision(level, pd, tl);
    int trHit = Level_isCollision(level, pd, tr);
    if (tlHit || trHit) {
      pd->system->logToConsole("Top hit");
      newPos.y = (int)newPos.y + 1;
    }
  }

  self->hitBox.pos = newPos;
  return 0;
}
