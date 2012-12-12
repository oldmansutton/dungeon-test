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

#define true 1
#define false 0

#define MAP_WIDTH 96
#define MAP_HEIGHT 60

#define MAP_XY(x,y) ((y * MAP_WIDTH) + x)

#define TILE_COUNT 4

#define TILE_FLOOR 0
#define TILE_WALL 1
#define TILE_DOOR 2
#define TILE_ROOM 3

typedef int bool;

typedef struct
{
	char *Name;
	bool Walkable;
	bool Permanent;
} tileDefs;

typedef struct
{
	int tile;
	bool Seen;
	bool Occupied;
	bool Lit;
} map;

extern map *init_map(void);
extern void print_map(map *_map);
int get_TileType(map *_map, int x, int y);
void set_TileType(map *_map, int x, int y, int type);

extern tileDefs *init_tileDefs(void);

#endif
