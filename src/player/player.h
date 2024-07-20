#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "pd_api.h"
#include "src/defs.h"
typedef struct Player Player;

Player *Player_new(void);
Player *Player_update(Player *player, PlaydateAPI *pd);
void Player_delete(Player *player);
void setWorldPos(Player *player, Vec2 p);
void setWorldX(Player *player, float x);
void setWorldY(Player *player, float y);

#endif // !PLAYER_H
