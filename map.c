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
#include <SDL/SDL_image.h>
#include "helper.h"
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
			newmap[MAP_XY(x,y)].Visible = false;
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
				case TILE_WALL:  	putchar('#'); break;
				case TILE_ROOM:
				case TILE_FLOOR: 	putchar('.'); break;
				case TILE_C_DOOR:	putchar('_'); break;
				case TILE_O_DOOR:	putchar('+'); break;
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

bool tile_Walkable(map *_map, int x, int y, tileDefs *_TD)
{
	int tile = get_TileType(_map,x,y);
	bool walk = _TD[tile].Walkable;
	return walk;
}


bool map_Visible(map *_map, int x, int y)
{
	return _map[MAP_XY(x,y)].Visible;
}

bool map_Seen(map *_map, int x, int y)
{
	return _map[MAP_XY(x,y)].Seen;
}

bool map_Occupied(map *_map, int x, int y)
{
	return _map[MAP_XY(x,y)].Occupied;
}

bool map_Lit(map *_map, int x, int y)
{
	return _map[MAP_XY(x,y)].Lit;
}

void set_Visible(map *_map, int x, int y, bool set)
{
	_map[MAP_XY(x,y)].Visible = set;
}

void set_Seen(map *_map, int x, int y, bool set)
{
	_map[MAP_XY(x,y)].Seen = set;
}

void set_Occupied(map *_map, int x, int y, bool set)
{
	_map[MAP_XY(x,y)].Occupied = set;
}

void set_Lit(map *_map, int x, int y, bool set)
{
	_map[MAP_XY(x,y)].Lit = set;
}

/* Pick a random (x,y) on the map that is Walkable */
_Point get_RandWalkable(map *_map)
{
	bool validPXY = false;
	_Point coords;
	while (!validPXY) /* Find a random place to stand */
	{
		int rpx, rpy;
		rpx = randr(1,MAP_WIDTH - 1);
		rpy = randr(1,MAP_HEIGHT - 1);
		/* Test to make sure we're on an unoccupied floor tile */
		if (get_TileType(_map,rpx,rpy) == TILE_FLOOR && map_Occupied(_map,rpx,rpy) == false)
		{
			validPXY = true;
			coords.x = rpx;
			coords.y = rpy;
		}
	}
	/* Return random (x,y) _Point struct */
	return coords;
}

/* Return how many doors immediately surround point (x,y) */
int count_SurroundingTypes(map *_map, int x, int y, int tiletype)
{
	int xi, yi;
	int numtypes = 0;
	for (yi = -1; yi <= 1; yi++)
	{
		for (xi = -1; xi <= 1; xi++)
		{
			if (x + xi < 0 || y + yi < 0 || x + xi >= MAP_WIDTH || y + yi >= MAP_HEIGHT)		
			{
				continue;
			}
			if (x == xi && y == yi)
			{
				continue;
			}
			int test = get_TileType(_map,x + xi,y + yi);
			if (test == tiletype)
			{
				numtypes++;
			}
		}
	}
	return numtypes;
}

_Point *get_SurroundingTypeLocs(map *_map, int x, int y, int numLocs, int tiletype)
{
	_Point *_typelocs = (_Point*)malloc(sizeof(_Point) * numLocs);
	int xi, yi;
	int index = 0;
	for (yi = -1; yi <= 1; yi++)
	{
		for (xi = -1; xi <= 1; xi++)
		{
			if (x + xi < 0 || y + yi < 0 || x + xi >= MAP_WIDTH || y + yi >= MAP_HEIGHT)		
			{
				continue;
			}
			if (x == xi && y == yi)
			{
				continue;
			}
			if (get_TileType(_map, x + xi, y + yi) == tiletype)	
			{
				_typelocs[index].x = x + xi;
				_typelocs[index].y = y + yi;
				index++;
			}
		}
	}
	return _typelocs;
}
	

void open_Door(map *_map, int x, int y)
{
	if (get_TileType(_map, x, y) != TILE_C_DOOR)
	{
		return;
	}
	/* TO DO:  Logic for locks, stuck doors, secret doors, etc */
	set_TileType(_map,x,y,TILE_O_DOOR);
}
	
/* Return the initialized set of Tile Definitions for the game */	
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
			case 2:	TD[i].Name = "Room Floor";
					TD[i].Image = load_image("floor.png");
					TD[i].Walkable = true;
					TD[i].Permanent = true;
					break;
			case 3:	TD[i].Name = "Open Door";
					TD[i].Image = load_image("opendoor.png");
					TD[i].Walkable = true;
					TD[i].Permanent = false;
					break;
			case 4:	TD[i].Name = "Closed Door";
					TD[i].Image = load_image("closedoor.png");
					TD[i].Walkable = false;
					TD[i].Permanent = false;
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
	
