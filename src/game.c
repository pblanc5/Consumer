#include <stdlib.h>
#include <time.h>

#include "game.h"

#include "raymath.h"

/*
* SpawnGame
* @Param void
* @Return (Game *)
*/
Game *SpawnGame(void) {
  Game *g = malloc(sizeof(Game));
  TraceLog(LOG_INFO, "(InitGame): Game initialized");
  return g;
}

/*
* InitGame
* @Param (Game *)
* @Returns void
*/
void InitGame(Game *g) {
  srand(time(NULL));

  Entity *p = SpawnEntity(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1);
  InitPlayer(p);

  g->isOver = false;
  g->isPaused = true;
  g->player = p;

  for (int i = 0; i < MAX_ENEMIES; i++) {
    int x = rand() % SCREEN_WIDTH;
    int y = rand() % SCREEN_HEIGHT;
    int r = rand();

    Entity *e = SpawnEntity(x, y, r);
    InitEnemy(e);
    g->enemies[i] = e;    
  }
}

/*
* UpdateGame
* @Param (Game *)
* @Returns void
*/
void UpdateGame(Game *g) {

  if (!g->isOver) {

    if (IsKeyPressed(KEY_P)) {
      g->isPaused = !g->isPaused;
    }

    if(!g->isPaused) {
      UpdatePlayer(g->player);

      // Track Player Collisions
      for (int i = 0; i < MAX_ENEMIES; i++) {
        HandlePlayerCollision(g->player, g->enemies[i]);
      }

      // Track Enemy Collisions
      for (int i = 0; i < MAX_ENEMIES; i++) {
        for (int j = 0; j < MAX_ENEMIES; j++) {
          if (i != j) {
            HandleEnemyCollision(g->enemies[i], g->enemies[j]);
          }
        }
      }

      // Enemy AI
      int deactivated = 0;
      for (int i = 0; i < MAX_ENEMIES; i++) {
        Entity *e1 = g->enemies[i];

        if (!e1->active) {
          deactivated += 1;
        }

        if (deactivated == MAX_ENEMIES) {
          g->isOver = true;
          break;
        }

        if (!e1->active) {
          continue;
        }

        // Handle Player Visibility
        if (IsPlayerVisible(g->player, e1)) {
          TraceLog(LOG_DEBUG, "Player is visibile to enemy %d", i);
          UpdateEnemyForPlayer(e1, g->player);

          // Game Over
          if (!g->player->active) {
            g->isOver = true;
            break;
          }
          continue;
        }

        Entity *closestEnemy = NULL;
        float minDist = 1000000;

        // Find Closest Enemy
        for (int j = 0; j < MAX_ENEMIES; j++) {
          Entity *e2 = g->enemies[j];
          if (i != j && IsEnemyVisible(e1, e2)) {
            float dist = Vector2Distance(e1->position, e2->position);
            if (dist < minDist) {
              minDist = dist;
              closestEnemy = e2;
            }
          }
        }

        // Update Movement
        if (closestEnemy != NULL) {
          UpdateEnemyForEnemy(e1, closestEnemy);
          continue;
        } else {
          IdleMovement(e1);
        }
      }
    }
  } else {
    if (IsKeyPressed(KEY_ENTER)) {
      ResetGame(g);
    }
  }

  
}

/*
* DrawGame
* @Param (Game *)
* @Return void
*/
void DrawGame(Game *g) {
  if (g->isOver) {
    if (!g->player->active) {
      DrawText("YOU LOST: PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("YOU LOST: PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
    } else {
      DrawText("YOU WON: PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("YOU WON: PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
    }
    return;
  }

  if (g->isPaused) {
    DrawText("PRESS [P] TO UNPAUSE", GetScreenWidth()/2 - MeasureText("PRESS [P] TO UNPAUSE", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
  }

  DrawEntity(g->player);

  for (int i = 0; i < MAX_ENEMIES; i++) {
    DrawEntity(g->enemies[i]);
  }
}

/*
* ResetGame
* @Param (Game *)
* @Return void
*/
void ResetGame(Game *g) {
  DestroyEntity(g->player);

  for (int i = 0; i < MAX_ENEMIES; i++) {
    DestroyEntity(g->enemies[i]);
  }

  InitGame(g);
}

/*
* DestroyGame
* @Param (Game *g)
* @Return void
*/
void DestroyGame(Game *g) {
  DestroyEntity(g->player);

  for (int i = 0; i < MAX_ENEMIES; i++) {
    DestroyEntity(g->enemies[i]);
  }

  free(g);
}

