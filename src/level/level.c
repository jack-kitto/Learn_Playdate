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

LCDPattern *tileTypeToPattern(TileType tileType) {
  switch (tileType) {
  case START:
    return game->patterns->white;
  case END:
    return game->patterns->white;
  case BLOCK:
    return game->patterns->grey62_5;
  case AIR:
    return game->patterns->grey12_5;
  case UNKNOWN:
    return game->patterns->white;
  default:
    return game->patterns->black;
  }
}

void drawLevel() {
  game->print("Drawing level.");
  game->pd->graphics->clear(kColorWhite);
  int startX = 0;
  int startY = 0;
  for (int i = startY; i < LEVEL_HEIGHT; i++) {
    for (int j = startX; j < LEVEL_WIDTH; j++) {
      // Coordinate currentWorldPosition = {.x = j, .y = i};
      // Coordinate screenCoordinate =
      //     worldPositionToScreenCoodinates(currentWorldPosition, &camera);
      // drawPatternRect(pd, screenCoordinate.x * TILE_SIZE,
      //                 screenCoordinate.y * TILE_SIZE, TILE_SIZE, TILE_SIZE,
      //                 tileTypeToPattern(level->tilemap[i][j]));
    }
  }
}
