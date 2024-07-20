#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include "pd_api.h"
#include "src/camera/camera.h"
#include "src/defs.h"
typedef enum TileType TileType;
enum TileType { START, END, BLOCK, AIR, UNKNOWN };

typedef struct Level Level;
void Level_print(Level *level, PlaydateAPI *pd);
void Level_draw(Level *level, PlaydateAPI *pd, Camera *camera);
Vec2 Level_getStart(Level *level);
Level *Level_new(void);
Level *Level_update(Level *level);
void Level_delete(Level *level);

TileType charToTileType(char tile);
char tileTypeToChar(TileType tileType);

#endif // !LEVEL_H
