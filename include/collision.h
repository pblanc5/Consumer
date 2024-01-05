#ifndef COLLISION_H_
#define COLLISION_H_

#include "entity.h"

#define VISIBILITY_DIST 100

void HandlePlayerCollision(Entity *, Entity *);
void HandleEnemyCollision(Entity *, Entity *);
bool IsPlayerVisible(Entity *, Entity *);
bool IsEnemyVisible(Entity *, Entity *);

#endif