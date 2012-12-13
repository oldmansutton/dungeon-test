// graphics.c
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
#include <SDL/SDL_image.h>
#include "map.h"
#include "graphics.h"

SDL_Surface *load_image(char *filename)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	loadedImage = IMG_Load(filename);
	if(loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *dest)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, dest, &offset);
}

void draw_map(map *_map, tileDefs *_TD, SDL_Surface *_surface)
{
	int map_x, map_y;
	for (map_y = 0; map_y < MAP_HEIGHT; map_y++)
	{
		for (map_x = 0; map_x < MAP_WIDTH; map_x++)
		{
			int i = get_TileType (_map,map_x,map_y);
			if (map_y * 4 >= 0 && map_y * 4 <= 596 && map_x * 4 >= 0 && map_x * 4 <= 796)
			{
				apply_surface (map_x * 4, map_y * 4, _TD[i].Image, _surface);
			}
		}
	}
}
