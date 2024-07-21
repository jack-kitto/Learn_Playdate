#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "pd_api.h"
#include "src/defs.h"
typedef struct Player Player;
typedef struct Level Level;
typedef struct Camera Camera;

Player *Player_new(void);
int Player_update(Player *self, PlaydateAPI *pd, Camera *camera, float dt);
int Player_setup(Player *player, PlaydateAPI *pd, Level *level);
int Player_delete(Player *player);
Vec2 Player_getWorldPos(Player *player);
Box Player_getHitBox(Player *self);
int Player_setWorldPos(Player *player, Vec2 p);
int Player_setWorldX(Player *player, float x);
int Player_setWorldY(Player *player, float y);

#endif // !PLAYER_H
