// monster.h
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

#ifndef MONSTER_H
#define MONSTER_H

#include <SDL/SDL.h>

typedef struct 
{
	int x;
	int y;
	
	SDL_Surface *Image;
} Monster;

extern Monster *new_Monster(char *image);
extern void free_Monster(Monster *_monster);

extern Monster *get_Monster();

#endif
