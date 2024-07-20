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
