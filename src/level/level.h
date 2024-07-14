#ifndef LEVEL_H

#define LEVEL_H
#define LEVEL_WIDTH 60
#define LEVEL_HEIGHT 10

typedef enum TileType TileType;
enum TileType { START, END, BLOCK, AIR, UNKNOWN };

typedef struct Level Level;
struct Level {
  char (*tilemap)[LEVEL_WIDTH];
  void (*printLevel)(void);
  void (*drawLevel)(void);
  TileType (*charToTileType)(char tile);
  char (*tileTypeToChar)(TileType tileType);
};

typedef struct Game Game;
Level *initialiseLevel(Game *g);
#endif // !LEVEL_H
