// vision.c
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

#include "vision.h"
#include "helper.h"
#include "map.h"

void update_PVision(map *_map, tileDefs *_TD, int px, int py, int r)
{
	int x, y;
	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			set_Visible(_map,x,y,false);
		}
	}
	for (y = -r; y <= r; y++)
	{
		for (x = -r; x <= r; x++)
		{
			/* Sanity checks */
			if (x * x + y * y > r * r)
			{
				continue;
			}
			if (px + x < 0 || py + y < 0 || px + x >= MAP_WIDTH || py + y >= MAP_WIDTH)
			{
				continue;
			}
			_Line *_line;
			_line = new_Line(px, py, px + x, py + y);
			int i;
			for (i = 0; i < _line->num_pts; i++)
			{
				int ptx = _line->points[i].x;
				int pty = _line->points[i].y;

				set_Visible(_map, ptx, pty, true);
				set_Seen(_map, ptx, pty, true);

				if (tile_Walkable(_map,ptx,pty,_TD) == false)
				{
					break;
				}
			}
			free(_line);
		}
	}
}
			
