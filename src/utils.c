#include "defs.h"

Vec2 Vec2_subtract(Vec2 a, Vec2 b) {
  Vec2 result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  return result;
}

Vec2 Vec2_add(Vec2 a, Vec2 b) {
  Vec2 result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  return result;
}

Vec2 Vec2_multiply(Vec2 a, Vec2 b) {
  Vec2 result;
  result.x = a.x * b.x;
  result.y = a.y * b.y;
  return result;
}

Vec2 Vec2_subtractScalar(Vec2 a, float scalar) {
  Vec2 result;
  result.x = a.x - scalar;
  result.y = a.y - scalar;
  return result;
}
Vec2 Vec2_addScalar(Vec2 a, float scalar) {
  Vec2 result;
  result.x = a.x + scalar;
  result.y = a.y + scalar;
  return result;
}

Vec2 Vec2_multiplyScalar(Vec2 a, float scalar) {
  Vec2 result;
  result.x = a.x * scalar;
  result.y = a.y * scalar;
  return result;
}

Vec2 Box_getCenter(Box box) {
  Vec2 halfLength = Vec2_multiplyScalar(box.length, 0.5f);
  return Vec2_add(box.pos, halfLength);
}

Vec2 Vec2_divideScalar(Vec2 a, float scalar) {
  Vec2 res;
  res.x = a.x / scalar;
  res.y = a.y / scalar;
  return res;
}

Vec2 Vec2_divide(Vec2 a, Vec2 b) {
  Vec2 res;
  res.x = a.x / b.x;
  res.y = a.y / b.y;
  return res;
}

Vec2 Vec2_new(float x, float y) {
  Vec2 res;
  res.x = x;
  res.y = y;
  return res;
}

Box Box_new(float x, float y, float w, float h) {
  Box res;
  res.pos.x = x;
  res.pos.y = y;
  res.length.x = w;
  res.length.y = h;
  return res;
}

void Vec2_print(PlaydateAPI *pd, Vec2 v) {
  pd->system->logToConsole("Vec2(x: %.2f, y: %.2f)\n", v.x, v.y);
}

void Box_print(PlaydateAPI *pd, Box b) {
  pd->system->logToConsole("Box.pos:");
  Vec2_print(pd, b.pos);
  pd->system->logToConsole("Box.length:");
  Vec2_print(pd, b.length);
}

Vec2 Box_getTL(Box b) { return b.pos; }
Vec2 Box_getTR(Box b) {
  Vec2 v;
  v.x = b.pos.x + b.length.x;
  v.y = b.pos.y;
  return v;
}
Vec2 Box_getBR(Box b) { return Vec2_add(b.length, b.pos); }
Vec2 Box_getBL(Box b) {
  Vec2 v;
  v.x = b.pos.x;
  v.y = b.pos.y + b.length.y;
  return v;
}

float Vec2_length(Vec2 v) { return sqrtf(v.x * v.x + v.y * v.y); }

int Vec2_N(Vec2 v) {
  if (v.y < 0 && v.x == 0) {
    return 1;
  }
  return 0;
}

int Vec2_E(Vec2 v) {
  if (v.y == 0 && v.x > 0) {
    return 1;
  }
  return 0;
}

int Vec2_S(Vec2 v) {
  if (v.y > 0 && v.x == 0) {
    return 1;
  }
  return 0;
}

int Vec2_W(Vec2 v) {
  if (v.y == 0 && v.x < 0) {
    return 1;
  }
  return 0;
}

int Vec2_NE(Vec2 v) {
  if (v.y < 0 && v.x > 0) {
    return 1;
  }
  return 0;
}

int Vec2_SE(Vec2 v) {
  if (v.y > 0 && v.x > 0) {
    return 1;
  }
  return 0;
}

int Vec2_SW(Vec2 v) {
  if (v.y > 0 && v.x < 0) {
    return 1;
  }
  return 0;
}

int Vec2_NW(Vec2 v) {
  if (v.y < 0 && v.x < 0) {
    return 1;
  }
  return 0;
}

Vec2 Vec2_withoutY(Vec2 v) { return Vec2_new(v.x, 0); }
Vec2 Vec2_withoutX(Vec2 v) { return Vec2_new(0, v.y); }
