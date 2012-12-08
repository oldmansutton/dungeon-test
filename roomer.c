// roomer.c
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
#include <stdio.h>
#include "roomer.h"

void newRoomer(roomer *room, int x, int y, int xdir, int ydir)
{
	room->xDir = xdir;
	room->yDir = ydir;
	room->doorX = x;
	room->doorY = y;
	room->dimX = (rand() % (ROOM_MAX + 1 - ROOM_MIN)) + ROOM_MIN;
	room->dimY = (rand() % (ROOM_MAX + 1 - ROOM_MIN)) + ROOM_MIN;		
}

roomCorners *get_RoomCorners(roomer *room, int offset_x, int offset_y)
{
	roomCorners *corners = (roomCorners*)malloc(sizeof(roomCorners));

	int top, bottom, left, right;

	printf("Room xdir: %i / Room ydir: %i\n",room->xDir,room->yDir);
	printf("offset_x: %i / offset_y: %i\n",offset_x,offset_y);
	if (room->yDir == 0)
	{
		if (room->xDir < 0)
		{
			right = room->doorX - 1;
			left = room->doorX - room->dimX - 1;
		} else {
			right = room->doorX + room->dimX + 1;
			left = room->doorX + 1;
		}
		top = room->doorY - room->dimY + offset_y;
		bottom = room->doorY + offset_y;
	} else {
		int top, bottom;
		if (room->yDir < 0)
		{
			top = room->doorY - room->dimY - 1;
			bottom = room->doorY - 1;
		} else {
			top = room->doorY + 1;
			bottom = room->doorY + room->dimY + 1;
		}
		right = room->doorX + offset_x;
		left = room->doorX - room->dimX + offset_x;
	}
	corners->x_br = right;
	corners->x_bl = left;
	corners->x_ur = right;
	corners->x_ul = left;
	corners->y_br = bottom;
	corners->y_bl = bottom;
	corners->y_ur = top;
	corners->y_ul = top;

	return corners;
}
