// helper.h
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

#ifndef HELPER_H
#define HELPER_H

typedef struct
{
	int x;
	int y;
} _Point;

typedef struct
{
	_Point *points;
	int num_pts;
} _Line;

extern int randr(int min, int max);

extern _Point *new_Point(int x, int y);
extern _Line *new_Line(int x1, int y1, int x2, int y2);

#endif
