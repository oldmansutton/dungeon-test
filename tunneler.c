// tunneler.c
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

#include <stdlib.h>
#include "helper.h"
#include "tunneler.h"

void tunneler_rand(tunneler *inTunneler, int lifeMin, int lifeMax, int turnMin, int turnMax, int tspMin, int tspMax, int rspMin, int rspMax, int neatMin, int neatMax)
{
	int r;
	int d;	

	inTunneler->xDir = 0;
 	inTunneler->yDir = 0;

	r = rand() % 100;
	d = rand() % 100;
	if (r < 50)
	{
		if (d < 50)
		{
			inTunneler->xDir = -1;
		} else {
			inTunneler->xDir = 1;
		}
	} else {
		if (d < 50)
		{
			inTunneler->yDir = -1;
		} else {
			inTunneler->yDir = 1;
		}
	}

	inTunneler->lifetime = randr(lifeMin, lifeMax);
	inTunneler->age = 0;
	inTunneler->turnChance = randr(turnMin, turnMax);
	inTunneler->tunnelerSpawn = randr(tspMin, tspMax);
	inTunneler->roomerSpawn = randr(rspMin, rspMax);
	inTunneler->neatness = randr(neatMin, neatMax);
}
