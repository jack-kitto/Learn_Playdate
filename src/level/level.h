#ifndef LEVEL_H

#define LEVEL_H

#include "src/defs.h"
typedef enum TileType TileType;
enum TileType { START, END, BLOCK, AIR, UNKNOWN };

typedef struct Level Level;
struct Level {
  char (*tilemap)[LEVEL_WIDTH];
  void (*printLevel)(void);
  void (*drawLevel)(void);
  TileType (*charToTileType)(char tile);
  char (*tileTypeToChar)(TileType tileType);
  Coord_i (*getStartPosition)(void);
};

typedef struct Game Game;
Level *initialiseLevel(Game *g);
#endif // !LEVEL_H
