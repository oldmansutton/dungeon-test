// monster.c
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

#include <SDL/SDL.h>
#include "graphics.h"
#include "monster.h"

Monster *new_Monster(char *image)
{
	Monster *_monster = (Monster*)malloc(sizeof(Monster));
	_monster->x = 0;
	_monster->y = 0;
	_monster->Image = load_image(image);
	return _monster;
}

void free_Monster(Monster *_monster)
{
	SDL_FreeSurface(_monster->Image);
	free(_monster);
}
