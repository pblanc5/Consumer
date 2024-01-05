#ifndef ENEMY_H_
#define ENEMY_H_

#include "entity.h"

void InitEnemy(Entity *);
void UpdateEnemyForPlayer(Entity *, Entity *);
void UpdateEnemyForEnemy(Entity *, Entity *);
void IdleMovement(Entity *);

#endif /* _ENEMY_H */