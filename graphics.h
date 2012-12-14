// graphics.h
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

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL/SDL.h>
#include "map.h"
#include "player.h"

SDL_Surface *load_image(char *filename);
extern void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *dest);
extern void draw_map(int x, int y, map *_map, tileDefs *_TD, SDL_Surface *_surface);
extern void draw_mini_map(map *_map, tileDefs *_TD, Player *_player, SDL_Surface *_surface);

extern int show_surface(SDL_Surface *_surface);

#endif
