// position.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef POSITION_H
#define POSITION_H

#include "entity.h"

typedef struct
{
    int x;
    int y;
} Position;

Position *positionGet(Entity entity);
void positionAdd(Entity entity, int x, int y);
void positionRemove(Entity entity);

#endif
