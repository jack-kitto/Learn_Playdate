#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include "pd_api.h"
#include "src/camera/camera.h"
#include "src/defs.h"
typedef enum TileType TileType;
enum TileType { START, END, BLOCK, AIR, UNKNOWN };
typedef enum LEVEL_ERROR LEVEL_ERROR;
typedef struct Level Level;
int Level_print(Level *level, PlaydateAPI *pd);
Vec2 Level_getStart(Level *level);
Level *Level_new(void);
int Level_update(Level *level, PlaydateAPI *pd, Camera *camera);
void printTileType(PlaydateAPI *pd, TileType tile);
void Level_printTileAt(PlaydateAPI *pd, Level *self, Vec2 position);
int Level_delete(Level *level);
int Level_setup(Level *self, PlaydateAPI *pd);
LCDPattern *tileTypeToPattern(TileType tileType);
Vec2 Level_getTileSize(Level *level);

TileType charToTileType(char tile);
char tileTypeToChar(TileType tileType);

#endif // !LEVEL_H
