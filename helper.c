// helper.c
//
// Copyright (C) 2012 - oldmansutton
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
#include "map.h"
#include "helper.h"

int randr(int min, int max)
{
	int r;
	r = (rand() % (max + 1 - min)) + min;
	return r;
}

_Point *new_Point(int x, int y)
{
	_Point *_point = (_Point*)malloc(sizeof(_Point));
	_point->x = x;
	_point->y = y;
	return _point;
}

_Line *new_Line(int x1, int y1, int x2, int y2)
{
	_Line *_line = (_Line*)malloc(sizeof(_Line));
	
	int numpts = 1;
	_Point *_pt = (_Point*)malloc(sizeof(_Point));
	
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;

	int err = dx - dy;

	while(true)
	{
		_pt = realloc(_pt,sizeof(_Point) * numpts);
		_pt[numpts - 1].x = x1;
		_pt[numpts - 1].y = y1;

		if (x1 == x2 && y1 == y2)
		{
			break;
		}

		int e2 = err * 2;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
		numpts++;
	}

	_line->points = _pt;
	_line->num_pts = numpts;

	return _line;
}
