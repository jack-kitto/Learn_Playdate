#ifndef DEFS_H
#define DEFS_H

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 400
#define LEVEL_WIDTH 60
#define LEVEL_HEIGHT 10
#define TILE_SIZE 8

typedef struct Coord_i Coord_i;
struct Coord_i {
  int x;
  int y;
};

typedef struct Coord_f Coord_f;
struct Coord_f {
  float x;
  float y;
};

#endif // !DEFS_H
