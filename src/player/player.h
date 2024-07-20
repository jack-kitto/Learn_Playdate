#ifndef PLAYER_H
#define PLAYER_H

#include "src/defs.h"
typedef struct Player Player;
struct Player {
  Vec2 worldPos;
  Vec2 vel;
  void (*drawPlayer)(void);
};

typedef struct Game Game;
Player *initialisePlayer(Game *g);
#endif // !PLAYER_H
