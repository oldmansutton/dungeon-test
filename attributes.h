// attributes.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

typedef struct {
    // BASE ATTRIBUTES
    // Physical
    unsigned int strength;      // power: melee/carry
    unsigned int dexterity;     // finesse: precision/hit/dodge/speed
    unsigned int constitution;  // resistance: hp/regen/poisons
    // Mental
    unsigned int intelligence;  // power: spell dmg/mana/learning
    unsigned int wisdom;        // finesse: perception/tracks/mana regen
    unsigned int resolve;       // resistance: willpower/focus
    // Social
    unsigned int presence;      // power: intimidate/leader
    unsigned int charisma;      // finesse: barter/deception/persuasion
    unsigned int nerve;         // resistance: sanity/bravery/fear resist
    // TRAIT ACTIVATED ATTRIBUTES
    int luck; // modifies roll outcomes +/-, loot drops, crits, etc.
} Attributes;

