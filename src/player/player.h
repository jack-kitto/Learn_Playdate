#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "pd_api.h"
#include "src/defs.h"
typedef struct Player Player;

Player *Player_new(void);
void Player_update(Player *player, PlaydateAPI *pd);
void Player_setup(Player *player, PlaydateAPI *pd);
void Player_delete(Player *player);
Vec2 Player_getWorldPos(Player *player);
void Player_setWorldPos(Player *player, Vec2 p);
void Player_setWorldX(Player *player, float x);
void Player_setWorldY(Player *player, float y);

#endif // !PLAYER_H
