#include "level.h"
#include "src/defs.h"
#include "src/game/game.h"

static Game *game;
static Level level;
char tilemap[LEVEL_HEIGHT][LEVEL_WIDTH];
TileType charToTileType(char tile);
char tileTypeToChar(TileType tileType);
void printLevel(void);
void drawLevel(void);
Coord_i getStartPosition(void);

Level *initialiseLevel(Game *g) {
  level.charToTileType = &charToTileType;
  level.tileTypeToChar = &tileTypeToChar;
  level.printLevel = &printLevel;
  level.drawLevel = &drawLevel;
  level.tilemap = tilemap;
  level.getStartPosition = &getStartPosition;
  game = g;
  return &level;
}

char tilemap[LEVEL_HEIGHT][LEVEL_WIDTH] = {
    "############################################################",
    "#..........................................................#",
    "#.#################################################........#",
    "#....................................................#######",
    "#................................S...............##........#",
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
    return game->patterns->grey12_5;
  case END:
    return game->patterns->grey12_5;
  case BLOCK:
    return game->patterns->black;
  case AIR:
    return game->patterns->grey25;
  case UNKNOWN:
    return game->patterns->white;
  default:
    return game->patterns->white;
  }
}

// Subtract camera position from object position to get the object position
// relative to the camera The camera is the screen #define LEVEL_WIDTH 60
// #define LEVEL_HEIGHT 10
// #define TILE_SIZE 8

void drawLevel() {
  game->print("Drawing level.");
  game->pd->graphics->clear(kColorWhite);
  float startX = game->camera->worldX; // Camera x
  float startY = game->camera->worldY;
  float cameraWidthInWorld = game->camera->worldWidth;
  float cameraHeightInWorld = game->camera->worldHeight;
  float tileHeight = SCREEN_HEIGHT / cameraHeightInWorld;
  float tileWidth = SCREEN_WIDTH / cameraWidthInWorld;
  int stopY = startY + cameraHeightInWorld;
  int stopX = startX + cameraWidthInWorld;
  for (int i = startY; i < stopY; i++) {
    for (int j = startX; j < stopX; j++) {
      float x = (j - startX) * tileWidth;
      float y = (i - startY) * tileHeight;
      if (i < 0 || j < 0) {
        game->graphics->drawPatternRect(x, y, tileWidth, tileHeight,
                                        game->patterns->black);
        continue;
      }
      if (i >= LEVEL_HEIGHT || j >= LEVEL_WIDTH) {
        game->graphics->drawPatternRect(x, y, tileWidth, tileHeight,
                                        game->patterns->black);
        continue;
      }
      TileType tile = charToTileType(game->level->tilemap[i][j]);
      LCDPattern *pattern = tileTypeToPattern(tile);
      game->graphics->drawPatternRect(x, y, tileWidth, tileHeight, pattern);
    }
  }
}

Coord_i getStartPosition(void) {
  Coord_i start;
  for (int i = 0; i < LEVEL_HEIGHT; i++) {
    for (int j = 0; j < LEVEL_WIDTH; j++) {
      TileType tile = charToTileType(level.tilemap[i][j]);
      if (tile == START) {
        start.x = j;
        start.y = i;
        return start;
      }
    }
  }
  return start;
}
