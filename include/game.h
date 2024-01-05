#ifndef GAME_H_
#define GAME_H_

#include "constants.h"
#include "player.h"
#include "enemy.h"
#include "entity.h"
#include "collision.h"

#include "raymath.h"

#define MAX_ENEMIES 25

typedef struct Game {
  bool isPaused;
  bool isOver;
  Entity *player;
  Entity *enemies[MAX_ENEMIES];
} Game;

Game* SpawnGame(void);
void InitGame(Game *g);
void UpdateGame(Game *g);
void DrawGame(Game *g);
void ResetGame(Game *g);
void DestroyGame(Game *g);

#endif /* _GAME_H */