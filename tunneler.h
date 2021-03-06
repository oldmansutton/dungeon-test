// tunneler.h
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

#ifndef TUNNELER_H
#define TUNNELER_H

#define NEATNESS_MIN 2
#define NEATNESS_MAX 6

typedef struct 
{
	int xCoord;
	int yCoord;
	int xDir;
	int yDir;
	int lifetime;
	int age;
	int turnChance;
	int tunnelerSpawn;
	int roomerSpawn;
	int neatness;
} tunneler;
	
extern void tunneler_rand(tunneler *inTunneler, int lifeMin, int lifeMax, int turnMin, int turnMax, int tspMin, int tspMax, int rspMin, int rspMax, int neatMin, int neatMax);

#endif 
