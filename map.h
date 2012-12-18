// map.h
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

#ifndef MAP_H
#define MAP_H

#include <SDL/SDL.h>
#include "helper.h"

#define true 1
#define false 0

#define MAP_WIDTH 64
#define MAP_HEIGHT 64

#define MAP_XY(x,y) ((y * MAP_WIDTH) + x)

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define TILE_COUNT 5

#define TILE_FLOOR 0
#define TILE_WALL 1
#define TILE_ROOM 2
#define TILE_O_DOOR 3
#define TILE_C_DOOR 4

typedef int bool;

typedef struct
{
	char *Name;
	SDL_Surface *Image;
	bool Walkable;
	bool Permanent;
} tileDefs;

typedef struct
{
	int tile;
	bool Seen;
	bool Visible;
	bool Occupied;
	bool Lit;
} map;

extern map *init_map(void);
extern void print_map(map *_map);

extern int get_TileType(map *_map, int x, int y);
extern void set_TileType(map *_map, int x, int y, int type);
extern bool tile_Walkable(map *_map, int x, int y, tileDefs *_TD);

extern bool map_Visible(map *_map, int x, int y);
extern bool map_Seen(map *_map, int x, int y);
extern bool map_Occupied(map *_map, int x, int y);
extern bool map_Lit(map *_map, int x, int y);
extern void set_Visible(map *_map, int x, int y, bool set);
extern void set_Seen(map *_map, int x, int y, bool set);
extern void set_Occupied(map *_map, int x, int y, bool set);
extern void set_Lit(map *_map, int x, int y, bool set);

extern _Point get_RandWalkable(map *_map);

extern int count_SurroundingTypes(map *_map, int x, int y, int tiletype);
extern _Point *get_SurroundingTypeLocs(map *_map, int x, int y, int numLocs, int tiletype);
extern void swap_ifTileType(map *_map, int x, int y, int ifType, int toType);

extern void open_Door(map *_map, int x, int y);
extern void close_Door(map *_map, int x, int y);

extern tileDefs *init_tileDefs(void);
extern void free_tileDefs(tileDefs *TD);

#endif
