// generate.h
//
// Copyright (C) 2012 - Ryan Sutton
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef GENERATE_H
#define GENERATE_H

#include "map.h"

#define CAVERN_CHANCE 18
#define CAVERN_R1 5
#define CAVERN_R2 2
#define CAVERN_NOISE 40
#define CAVERN_RECURSE 4

extern void create_Level(map *_map);
extern void gen_Noise(map *_map);
extern void gen_Cavern(map *_map, int r1, int r2);
extern void gen_Dungeon(map *_map, int lifeMin, int lifeMax, int turnMin, int turnMax, int tspMin, int tspMax, int rspMin, int rspMax, int neatMin, int neatMax, int chanceDoor);

#endif
