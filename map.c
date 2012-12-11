// map.c
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

#include "map.h"

map *initmap(void)  /* Initialize the map */
{
	map *newmap = (map*)malloc(sizeof(map) * MAP_HEIGHT * MAPWIDTH);

	int x, y;

	/* Fill map grid with "WALL" tiles */
	for (x = 0; x < MAP_WIDTH; x++)
	{
		for (y = 0; y < MAP_HEIGHT; y++)
		{
			newmap[MAP_XY].tile = TILE_WALL;
			newmap[MAP_XY].Seen = false;
			newmap[MAP_XY].Occupied = false;
			newmap[MAP_XY].Lit = false;
		}
	}
}

void printmap(map *pmap)
{
	int x, y;

	for(x = 0; x < MAP_WIDTH; x++)
	{
		for(y = 0; y < MAP_HEIGHT; y++)
		{
			switch(pmap[MAP_XY]) 
			{
				case TILE_WALL:  putchar('#'); break;
				case TILE_ROOM:
				case TILE_FLOOR: putchar('.'); break;
				case TILE_DOOR:	  putchar('+'); break;
			}
		}
        putchar('\n');
	}
}
