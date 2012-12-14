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

#include <stdlib.h>
#include <SDL/SDL.h>
#include "graphics.h"
#include "map.h"

map *init_map(void)  /* Initialize the map */
{
	map *newmap = (map*)malloc(sizeof(map) * MAP_HEIGHT * MAP_WIDTH);

	int x, y;

	/* Fill map grid with "WALL" tiles */
	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			set_TileType(newmap,x,y,TILE_WALL);
			newmap[MAP_XY(x,y)].Seen = false;
			newmap[MAP_XY(x,y)].Occupied = false;
			newmap[MAP_XY(x,y)].Lit = false;
		}
	}

	return newmap;
}

void print_map(map *_map)
{
	int x, y;

	for(y = 0; y < MAP_HEIGHT; y++)
	{
		for(x = 0; x < MAP_WIDTH; x++)
		{
			switch(get_TileType(_map,x,y))
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

int get_TileType(map *_map, int x, int y)
{
	return _map[MAP_XY(x,y)].tile;
}

void set_TileType(map *_map, int x, int y, int type)
{
	_map[MAP_XY(x,y)].tile = type;
}

tileDefs *init_tileDefs(void)
{
	tileDefs *TD = (tileDefs*)malloc(sizeof(tileDefs) * TILE_COUNT);
	int i;
	for (i = 0; i < TILE_COUNT; i++)
	{
		switch(i)
		{
			case 0:	TD[i].Name = "Floor";
					TD[i].Image = load_image("floor.png");
					TD[i].Walkable = true;
					TD[i].Permanent = true;
					break;
			case 1:	TD[i].Name = "Wall";
					TD[i].Image = load_image("wall.png");
					TD[i].Walkable = false;
					TD[i].Permanent = true;
					break;
			case 2:	TD[i].Name = "Door";
					TD[i].Image = load_image("door.png");
					TD[i].Walkable = true;
					TD[i].Permanent = false;
					break;
			case 3:	TD[i].Name = "Room Floor";
					TD[i].Image = load_image("floor.png");
					TD[i].Walkable = true;
					TD[i].Permanent = true;
					break;
		}
	}

	return TD;
}

void free_tileDefs(tileDefs *TD)
{
	int i;
	for (i = 0; i < TILE_COUNT; i++)
	{
		SDL_FreeSurface(TD[i].Image);
	}
	free(TD);
}
	
