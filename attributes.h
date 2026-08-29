// attributes.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "entity.h"
#include "entity_definitions.h"

typedef struct {
    // BASE ATTRIBUTES
    // Physical
    int strength;      // power: melee/carry
    int dexterity;     // finesse: precision/hit/dodge/speed
    int constitution;  // resistance: hp/regen/poisons
    // Mental
    int intelligence;  // power: spell dmg/mana/learning
    int wisdom;        // finesse: perception/tracks/mana regen
    int resolve;       // resistance: willpower/focus
    // Social
    int presence;      // power: intimidate/leader
    int charisma;      // finesse: barter/deception/persuasion
    int nerve;         // resistance: sanity/bravery/fear resist
    // TRAIT ACTIVATED ATTRIBUTES
    int luck; // modifies roll outcomes +/-, loot drops, crits, etc.
} Attributes;

const Attributes *getAttributes(Entity entity);
int initAttributes(Entity entity, const Entity_Definition_Component *component);

#endif
