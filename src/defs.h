#ifndef DEFS_H
#define DEFS_H

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 400
#define LEVEL_WIDTH 60
#define LEVEL_HEIGHT 10
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
#endif // !DEFS_H
