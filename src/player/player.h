#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player Player;
struct Player {
  float worldX;
  float worldY;
  float velocityX;
  float velocityY;
  void (*drawPlayer)(void);
};

typedef struct Game Game;
Player *initialisePlayer(Game *g);
#endif // !PLAYER_H
