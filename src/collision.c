#include "collision.h"

void HandlePlayerCollision(Entity *p, Entity *e) {
  bool hasCollision = CheckCollisionCircles(p->position, p->radius, e->position, e->radius);

  if (!e->active || !hasCollision) {
    return;
  }

  TraceLog(LOG_DEBUG, "Detected Player Collision with Enemy");
  if (p->radius > e->radius) {
    Consume(p, e);
  }

  if (e->radius > p->radius) {
    Consume(e, p);
  }
}

void HandleEnemyCollision(Entity *e1, Entity *e2) {
  bool hasCollision = CheckCollisionCircles(e1->position, e1->radius, e2->position, e2->radius);

  if (!e1->active || !e2->active || !hasCollision) {
    return;
  }

  if (e1->radius > e2->radius) {
    Consume(e1, e2);
    return;
  }

  if (e2->radius > e1-> radius) {
    Consume(e2, e1);
    return;
  }

  // Let first bot win
  Consume(e1, e2);
}

bool IsPlayerVisible(Entity *p, Entity *e) {
  if (e->active) {
    return CheckCollisionCircles(p->position, p->radius, e->position, e->radius + VISIBILITY_DIST);
  }

  return false;
}

bool IsEnemyVisible(Entity *e1, Entity *e2) {
  if (e1->active && e2->active) {
    return CheckCollisionCircles(e1->position, e1->radius + VISIBILITY_DIST, e2->position, e2->radius);
  }

  return false;
}