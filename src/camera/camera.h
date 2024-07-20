#pragma once
#include "src/defs.h"
#include "src/player/player.h"
#ifndef CAMERA_H
#define CAMERA_H

typedef struct Camera Camera;
typedef struct Game Game;
Camera *Camera_new(void);
int Camera_setup(Camera *self);
int Camera_update(Camera *self, Player *player);
int Camera_delete(Camera *self);
Box Camera_getWorld(Camera *self);
Box Camera_getScreen(Camera *self);
int Camera_WorldToScreenBox(Camera *self, Box *b);
int Camera_WorldToScreenCoord(Camera *self, Vec2 *p);

#endif
