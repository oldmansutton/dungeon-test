// roomer.h
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

#ifndef ROOMER_H
#define ROOMER_H

#define ROOM_MIN 3
#define ROOM_MAX 6


typedef struct
{
	int xDir;
	int yDir;
	int doorX;
	int doorY;
	int dimX;
	int dimY;
} roomer;

typedef struct
{
	int x_ul,y_ul;
	int x_ur,y_ur;
	int x_bl,y_bl;
	int x_br,y_br;
} roomCorners;

extern void newRoomer(roomer *room, int x, int y, int xdir, int ydir);

extern roomCorners *get_RoomCorners(roomer *room, int offset_x, int offset_y);

#endif
