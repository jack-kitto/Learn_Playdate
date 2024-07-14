#include "level.h"
#include "src/game/game.h"

static Game *game;
static Level level;
char tilemap[LEVEL_HEIGHT][LEVEL_WIDTH];
TileType charToTileType(char tile);
char tileTypeToChar(TileType tileType);
void printLevel(void);
void drawLevel(void);

Level *initialiseLevel(Game *g) {
  level.charToTileType = &charToTileType;
  level.tileTypeToChar = &tileTypeToChar;
  level.printLevel = &printLevel;
  level.drawLevel = &drawLevel;
  level.tilemap = tilemap;
  game = g;
  return &level;
}

char tilemap[LEVEL_HEIGHT][LEVEL_WIDTH] = {
    "############################################################",
    "#..........................................................#",
    "#.#################################################........#",
    "#....................................................#######",
    "#.S..............................................##........#",
    "##########.##############..####################......#######",
    "#E.......#................#..................#..####..#....#",
    "####...####################..................##......##....#",
    "######............................................##.......#",
    "############################################################",
};

TileType charToTileType(char tile) {
  switch (tile) {
  case '#':
    return BLOCK;
  case 'S':
    return START;
  case 'E':
    return END;
  case '.':
    return AIR;
  default:
    return UNKNOWN;
  };
}

char tileTypeToChar(TileType tileType) {
  switch (tileType) {
  case BLOCK:
    return '#';
  case START:
    return 'S';
  case END:
    return 'E';
  case AIR:
    return '.';
  default:
    return ' ';
  };
}

void printLevel() {
  for (int i = 0; i < LEVEL_HEIGHT; i++) {
    char str[LEVEL_WIDTH + 1];
    for (int j = 0; j < LEVEL_WIDTH; j++) {
      str[j] = level.tilemap[i][j];
    }
    str[LEVEL_WIDTH] = '\0';
    game->print(str);
  }
}

void drawLevel() { game->print("Drawing level."); }
