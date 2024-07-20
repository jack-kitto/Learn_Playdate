#include "level.h"
#include "src/camera/camera.h"
#include "src/defs.h"
#include "src/graphics/graphics.h"
#include "src/pattern/patterns.h"
#include <stdlib.h>

struct Level {
  char (*tilemap)[LEVEL_WIDTH];
};

char tilemap[LEVEL_HEIGHT][LEVEL_WIDTH];
TileType charToTileType(char tile);
char tileTypeToChar(TileType tileType);
void printLevel(void);
void drawLevel(void);
Vec2 getStartPosition(void);

void Level_print(Level *level, PlaydateAPI *pd);
Vec2 Level_getStart(Level *level);
Level *Level_update(Level *level);

Level *Level_new() {
  Level *level = malloc(sizeof(Level));
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
  level->tilemap = tilemap;
  return level;
}

void Level_delete(Level *level) {
  if (level) {
    free(level);
  }
}

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

void Level_print(Level *level, PlaydateAPI *pd) {
  if (!level) {
    return;
  }
  if (!pd) {
    return;
  }
  for (int i = 0; i < LEVEL_HEIGHT; i++) {
    char str[LEVEL_WIDTH + 1];
    for (int j = 0; j < LEVEL_WIDTH; j++) {
      str[j] = level->tilemap[i][j];
    }
    str[LEVEL_WIDTH] = '\0';
  }
}

LCDPattern *tileTypeToPattern(TileType tileType) {
  switch (tileType) {
  case START:
    return getPattern(PATTERN_GREY12_5);
  case END:
    return getPattern(PATTERN_GREY12_5);
  case BLOCK:
    return getPattern(PATTERN_BLACK);
  case AIR:
    return getPattern(PATTERN_GREY25);
  case UNKNOWN:
    return getPattern(PATTERN_WHITE);
  default:
    return getPattern(PATTERN_WHITE);
  }
}

// Subtract camera position from object position to get the object position
// relative to the camera The camera is the screen #define LEVEL_WIDTH 60
// #define LEVEL_HEIGHT 10
// #define TILE_SIZE 8

int Level_draw(Level *level, PlaydateAPI *pd, Camera *camera) {
  if (!pd) {
    return 1;
  }
  if (!level) {
    pd->system->error("Level ptr does not exist");
    return 2;
  }
  if (!camera) {
    pd->system->error("Camera ptr does not exist");
    return 3;
  }
  pd->system->logToConsole("Drawing level");
  pd->graphics->clear(kColorWhite);
  // float startX = camera->world.pos.x; // Camera x
  // float startY = camera->world.pos.y;
  float startX = Camera_getWorld(camera).pos.x;
  float startY = Camera_getWorld(camera).pos.y;
  float cameraWidthInWorld = Camera_getWorld(camera).length.x;
  float cameraHeightInWorld = Camera_getWorld(camera).length.y;
  int stopY = startY + cameraHeightInWorld;
  int stopX = startX + cameraWidthInWorld;
  Box box;
  box.length.y = SCREEN_HEIGHT / cameraHeightInWorld;
  box.length.x = SCREEN_WIDTH / cameraWidthInWorld;
  for (int i = startY; i < stopY; i++) {
    for (int j = startX; j < stopX; j++) {
      box.pos.x = (j - startX) * box.length.x;
      box.pos.y = (i - startY) * box.length.y;
      if (i < 0 || j < 0) {
        drawBox(pd, box, getPattern(PATTERN_BLACK));
        continue;
      }
      if (i >= LEVEL_HEIGHT || j >= LEVEL_WIDTH) {
        drawBox(pd, box, getPattern(PATTERN_BLACK));
        continue;
      }
      TileType tile = charToTileType(level->tilemap[i][j]);
      drawBox(pd, box, tileTypeToPattern(tile));
    }
  }
  return 0;
}

Vec2 Level_getStart(Level *level) {
  Vec2 start;
  for (int i = 0; i < LEVEL_HEIGHT; i++) {
    for (int j = 0; j < LEVEL_WIDTH; j++) {
      TileType tile = charToTileType(level->tilemap[i][j]);
      if (tile == START) {
        start.x = j;
        start.y = i;
        return start;
      }
    }
  }
  return start;
}
