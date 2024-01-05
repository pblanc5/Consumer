#include "enemy.h"

// TODO: Add Last Known Goal Logic

void ChasePlayer(Entity *, Entity *);
void FleePlayer(Entity *, Entity *);
void ChaseEnemy(Entity *, Entity *);
void FleeEnemy(Entity *, Entity *);

void InitEnemy(Entity *e) {
  e->color = RED;
  DebugEntity(e, "(InitEnemy) Enemy iniitialized");
}

void UpdateEnemyForPlayer(Entity *e, Entity *p) {
  int error = GetRandomValue(1, 100);

  if (error < 50) {
    IdleMovement(e);
    return;
  }

  if (e->radius > p->radius) {
    ChasePlayer(e, p);
    return;
  }

  FleePlayer(e, p);
}

void UpdateEnemyForEnemy(Entity *e1, Entity *e2) {
  int error = GetRandomValue(1, 100);

  if (error < 25) {
    IdleMovement(e1);
    return;
  }

  if (e1->radius > e2->radius) {
    ChaseEnemy(e1, e2);
    return;
  }

  FleeEnemy(e1, e2);
}

void ChasePlayer(Entity *e, Entity *p) {
  int srcW = GetScreenWidth();
  int srcH = GetScreenHeight();

  if (e->position.x > p->position.x) {
    e->position.x = Clamp(e->position.x - e->speed, e->radius, srcW);
  } else {
    e->position.x = Clamp(e->position.x + e->speed, e->radius, srcW - e->radius);
  }

  if (e->position.y > p->position.y) {
    e->position.y = Clamp(e->position.y - e->speed, e->radius, srcH);
  } else {
    e->position.y = Clamp(e->position.y + e->speed, e->radius, srcH - e->radius);
  }
}

void FleePlayer(Entity *e, Entity *p) {
  int srcW = GetScreenWidth();
  int srcH = GetScreenHeight();

  if (e->position.x > p->position.x) {
    e->position.x = Clamp(e->position.x + e->speed, e->radius, srcW - e->radius);
  } else {
    e->position.x = Clamp(e->position.x - e->speed, e->radius, srcW + e->radius);
  }

  if (e->position.y > p->position.y) {
    e->position.y = Clamp(e->position.y + e->speed, e->radius, srcH - e->radius);
  } else {
    e->position.y = Clamp(e->position.y - e->speed, e->radius, srcH + e->radius);
  }
}

void ChaseEnemy(Entity *e1, Entity *e2) {
  int srcW = GetScreenWidth();
  int srcH = GetScreenHeight();

  if (e1->position.x > e2->position.x) {
    e1->position.x = Clamp(e1->position.x - e1->speed, e1->radius, srcW + e1->radius);
  } else {
    e1->position.x = Clamp(e1->position.x + e1->speed, e1->radius, srcW - e1->radius);
  }

  if (e1->position.y > e2->position.y) {
    e1->position.y = Clamp(e1->position.y - e1->speed, e1->radius, srcH + e1->radius);
  } else {
    e1->position.y = Clamp(e1->position.y + e1->speed, e1->radius, srcH - e1->radius);
  }
}

void FleeEnemy(Entity *e1, Entity *e2) {
  int srcW = GetScreenWidth();
  int srcH = GetScreenHeight();

  if (e1->position.x > e2->position.x) {
    e1->position.x =  Clamp(e1->position.x - e1->speed, e1->radius, srcW + e1->radius);
  } else {
    e1->position.x =  Clamp(e1->position.x + e1->speed, e1->radius, srcW - e1->radius);
  }

  if (e1->position.y > e2->position.y) {
    e1->position.y = Clamp(e1->position.y - e1->speed, e1->radius, srcH + e1->radius);
  } else {
    e1->position.y = Clamp(e1->position.y + e1->speed, e1->radius, srcH - e1->radius);
  }
}

void IdleMovement(Entity *e) {
  int srcW = GetScreenWidth();
  int srcH = GetScreenHeight(); 
  
  int direction = GetRandomValue(1, 100);

  if (direction < 25) {
    float x = e->position.x - e->speed;
    e->position.x = Clamp(x, e->radius, srcW + e->radius);
    return;
  }

  if (direction < 50) {
    float x = e->position.x + e->speed;
    e->position.x = Clamp(x, e->radius, srcW - e->radius);
    return;
  }

  if (direction < 75) {
    float y = e->position.y + e->speed;
    e->position.y = Clamp(y, e->radius, srcH - e->radius);
    return;
  }

  if (direction < 100) {
    float y = e->position.y - e->speed;
    e->position.y = Clamp(y, e->radius, srcH + e->radius);
    return;
  }
}
