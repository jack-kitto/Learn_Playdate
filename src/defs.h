#pragma once
#include "pd_api.h"
#ifndef DEFS_H
#define DEFS_H

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 400
#define LEVEL_WIDTH 64
#define LEVEL_HEIGHT 16
#define TILE_SIZE 8

typedef struct Vec2 Vec2;
struct Vec2 {
  float x;
  float y;
};

typedef struct Box Box;
struct Box {
  Vec2 pos;
  Vec2 length;
};

Vec2 Vec2_subtract(Vec2 a, Vec2 b);
Vec2 Vec2_add(Vec2 a, Vec2 b);
Vec2 Vec2_multiply(Vec2 a, Vec2 b);
void Box_print(PlaydateAPI *pd, Box b);
Vec2 Vec2_multiplyScalar(Vec2 a, float scalar);
Vec2 Vec2_subtractScalar(Vec2 a, float scalar);
Vec2 Vec2_addScalar(Vec2 a, float scalar);
Vec2 Vec2_divideScalar(Vec2 a, float scalar);
Vec2 Vec2_divide(Vec2 a, Vec2 b);
Vec2 Box_getCenter(Box box);
Vec2 Vec2_new(float x, float y);
void Vec2_print(PlaydateAPI *pd, Vec2 v);
Box Box_new(float x, float y, float w, float h);
Vec2 Box_getTL(Box b);
Vec2 Box_getTR(Box b);
Vec2 Box_getBR(Box b);
Vec2 Box_getBL(Box b);
float Vec2_length(Vec2 v);
#endif // !DEFS_H
