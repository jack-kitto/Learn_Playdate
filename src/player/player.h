#ifndef PLAYER_H
#define PLAYER_H

#include "src/defs.h"
typedef struct Player Player;
struct Player {
  Vec2 worldPos;
  Vec2 vel;
  void (*drawPlayer)(void);
  void (*setWorldPos)(Vec2);
  void (*setWorldX)(float x);
  void (*setWorldY)(float y);
};

typedef struct Game Game;
Player *createPlayer(Game *g);
#endif // !PLAYER_H
