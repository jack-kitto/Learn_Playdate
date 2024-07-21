#include "level.h"
#include "pd_api.h"
#include "pd_api/pd_api_gfx.h"
#include "src/camera/camera.h"
#include "src/defs.h"
#include "src/graphics/graphics.h"
#include "src/pattern/patterns.h"
#include <stdlib.h>

struct Level {
  char (*tilemap)[LEVEL_WIDTH];
  Vec2 tileSize_px;
  Vec2 tilesInLevel;
};

char tilemap[LEVEL_HEIGHT][LEVEL_WIDTH] = {
    "################################################################",
    "#..........................................................#...#",
    "#.#################################################........##..#",
    "#....................................................#######..##",
    "#................................S...............##........##..#",
    "##########.##############..####################......#######..##",
    "#E.......#................#..................#..####..#....##..#",
    "####...####################..................##......##....#..##",
    "######............................................##.......##..#",
    "###########.....................................############..##",
    "############...................###################...........###",
    "#############...............#####.....#####........#############",
    "##############...#################.............###.............#",
    "###############...###########################################..#",
    "################..............................................##",
    "################################################################",
};

Level *Level_new() {
  Level *level = malloc(sizeof(Level));
  level->tilemap = tilemap;
  level->tileSize_px = Vec2_new(32, 32);
  // level->tileSize_px = Vec2_new(16, 16);
  level->tilesInLevel = Vec2_new(LEVEL_WIDTH, LEVEL_HEIGHT);
  return level;
}

int Level_delete(Level *level) {
  if (!level) {
    return 1;
  }
  free(level);
  return 0;
}

TileType Level_getTileAt(Level *self, Vec2 position, PlaydateAPI *pd) {
  if (!self || !pd) {
    pd->system->error("No level or pd");
    return UNKNOWN; // Return an UNKNOWN tile type if level is NULL
  }

  // Calculate the tile coordinates
  // int tileX = (int)(position.x / self->tileSize_px.x);
  // int tileY = (int)(position.y / self->tileSize_px.y);
  int tileX = (int)(position.x);
  int tileY = (int)(position.y);

  // Check if the coordinates are within bounds
  if (tileX < 0 || tileX >= LEVEL_WIDTH || tileY < 0 || tileY >= LEVEL_HEIGHT) {
    pd->system->error("Out of bounds");
    return UNKNOWN; // Return an UNKNOWN tile type if out of bounds
  }

  // Return the tile type at the calculated coordinates
  return charToTileType(self->tilemap[tileY][tileX]);
}

void Level_printTileAt(PlaydateAPI *pd, Level *self, Vec2 position) {
  printTileType(pd, Level_getTileAt(self, position, pd));
}
void printTileType(PlaydateAPI *pd, TileType tile) {
  switch (tile) {
  case BLOCK:
    pd->system->logToConsole("BLOCK");
    break;
  case START:
    pd->system->logToConsole("START");
    break;
  case END:
    pd->system->logToConsole("END");
    break;
  case AIR:
    pd->system->logToConsole("AIR");
    break;
  default:
    pd->system->logToConsole("UNKNOWN");
    break;
  };
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

LCDPattern *charToPattern(char c) {
  return tileTypeToPattern(charToTileType(c));
}

int Level_print(Level *level, PlaydateAPI *pd) {
  if (!level || !pd) {
    return 1;
  }
  for (int i = 0; i < LEVEL_HEIGHT; i++) {
    char str[LEVEL_WIDTH + 1];
    for (int j = 0; j < LEVEL_WIDTH; j++) {
      str[j] = level->tilemap[i][j];
    }
    str[LEVEL_WIDTH] = '\0';
    pd->system->logToConsole(str);
  }
  return 0;
}

LCDPattern *tileTypeToPattern(TileType tileType) {
  switch (tileType) {
  case START:
    return Pattern_new(PATTERN_GREY12_5);
  case END:
    return Pattern_new(PATTERN_GREY12_5);
  case BLOCK:
    return Pattern_new(PATTERN_BLACK);
  case AIR:
    return Pattern_new(PATTERN_GREY25);
  case UNKNOWN:
    return Pattern_new(PATTERN_WHITE);
  default:
    return Pattern_new(PATTERN_WHITE);
  }
}
void Level_printTilemap(Level *level, PlaydateAPI *pd) {
  if (!level) {
    return;
  }
  for (int i = 0; i < LEVEL_HEIGHT; i++) {
    for (int j = 0; j < LEVEL_WIDTH; j++) {
      pd->system->logToConsole("%c", level->tilemap[j][i]);
    }
    pd->system->logToConsole("\n");
  }
}
// Subtract camera position from object position to get the object position
// relative to the camera The camera is the screen #define LEVEL_WIDTH 60
// #define LEVEL_HEIGHT 10
// #define TILE_SIZE 8

int Level_setup(Level *self, PlaydateAPI *pd) {
  if (!self || !pd) {
    return 1;
  }
  pd->system->logToConsole("---------------------");
  pd->system->logToConsole("Setting up level");
  pd->system->logToConsole("---------------------");
  Vec2 a = Vec2_new(0, 0);
  Vec2 b = Vec2_new(63, 0);
  Vec2 c = Vec2_new(63, 15);
  Vec2 d = Vec2_new(0, 15);
  Vec2 e = Vec2_new(5, 1);
  Vec2_print(pd, a);
  Level_printTileAt(pd, self, a);
  Vec2_print(pd, b);
  Level_printTileAt(pd, self, b);
  Vec2_print(pd, c);
  Level_printTileAt(pd, self, c);
  Vec2_print(pd, d);
  Level_printTileAt(pd, self, d);
  Vec2_print(pd, e);
  Level_printTileAt(pd, self, e);
  pd->system->logToConsole("---------------------");
  return 0;
}

int test = 0;

int Level_update(Level *self, PlaydateAPI *pd, Camera *camera) {
  if (!pd || !self || !camera) {
    return 1;
  }
  // pd->graphics->clear(kColorWhite);
  Vec2 tileSize = self->tileSize_px;
  Box cameraBox = Camera_getWorld(camera);
  // set cameraBox.length to the bottom right corner of the world that the
  // camera can see
  cameraBox.length = Vec2_add(cameraBox.pos, cameraBox.length);
  for (int y = cameraBox.pos.y; y < (int)cameraBox.length.y + 1; y++) {
    for (int x = cameraBox.pos.x; x < (int)cameraBox.length.x + 1; x++) {
      // Set the world position of the current tile
      Vec2 tilePos = Vec2_new(x, y);
      // Ensure the tile coordinates are within bounds
      // Calculate the tile position relative to the camera
      Vec2 tilePosRelativeToCameraPos = Vec2_subtract(tilePos, cameraBox.pos);
      // create box to store the screen coordinates of the tile
      Box tileBox;
      // scale the tile position relative to the camera up to the screen
      // position in pixels
      tileBox.pos = Vec2_multiply(tilePosRelativeToCameraPos, tileSize);
      // add a gap between the tiles so you can see them
      tileBox.length = Vec2_subtractScalar(tileSize, 1);
      // Draw blocks outside the level
      if (tilePos.x < 0 || tilePos.x >= LEVEL_WIDTH || tilePos.y < 0 ||
          tilePos.y >= LEVEL_HEIGHT) {
        drawBox(pd, tileBox, tileTypeToPattern(BLOCK));
        continue;
      }
      // Get the tile at the current tile position
      TileType tile = Level_getTileAt(self, tilePos, pd);
      drawBox(pd, tileBox, tileTypeToPattern(tile));
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

Vec2 Level_getTileSize(Level *level) { return level->tileSize_px; }
