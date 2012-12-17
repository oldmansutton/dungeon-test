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
#include "vision.h"
#include "map.h"
#include "player.h"
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

void draw_map(int x, int y, map *_map, tileDefs *_TD, SDL_Surface *_surface)
{
	SDL_Surface *unseen = load_image("unseen.png");
	SDL_Surface *unvisible = load_image("unvisible.png");
	update_PVision(_map, _TD, x, y, 9);
	int map_x, map_y;
	for (map_y = -9; map_y <= 9; map_y++)
	{
		for (map_x = -12; map_x <= 12; map_x++)
		{
			if (y + map_y < 0 || x + map_x < 0 || y + map_y > MAP_HEIGHT - 1 || x + map_x > MAP_WIDTH - 1)
			{
				apply_surface((map_x + 12) * 32, (map_y + 9) * 32,  unseen, _surface);
				continue;
			}
			int i = get_TileType (_map, map_x + x, map_y + y);
			if ((map_y + 9) * 32 >= 0 && (map_y + 9) * 32 <= 576 && (map_x + 12) * 32 >= 0 && (map_x + 12) * 32 <= 768)
			{
				apply_surface ((map_x + 12) * 32, (map_y + 9) * 32, _TD[0].Image, _surface);
				apply_surface ((map_x + 12) * 32, (map_y + 9) * 32, _TD[i].Image, _surface);
				if (map_Visible(_map, map_x + x, map_y + y) != true)
				{
					if (map_Seen(_map, map_x + x, map_y + y) == true)
					{
						apply_surface((map_x + 12) * 32, (map_y + 9) * 32, unvisible, _surface);
					} else {
						apply_surface((map_x + 12) * 32, (map_y + 9) * 32, unseen, _surface);
					}
				} 
			}
		}
	}
	SDL_FreeSurface(unseen);
	SDL_FreeSurface(unvisible);
}

void draw_mini_map(map *_map, tileDefs *_TD, Player *_player, SDL_Surface *_surface)
{
	int x, y;
	SDL_Surface *sp_wall;
	SDL_Surface *sp_floor;
	SDL_Surface *sp_door;
	SDL_Surface *sp_player;
	SDL_Surface *sp_unseen;
	sp_wall = load_image("mini_wall.png");
	sp_floor = load_image("mini_floor.png");
	sp_door = load_image("mini_door.png");
	sp_player = load_image("mini_player.png");
	sp_unseen = load_image("mini_unseen.png");
	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			if (x < 0 || y < 0 || x > MAP_WIDTH - 1 || y > MAP_HEIGHT - 1)
			{
				continue;
			}
			if (map_Seen(_map,x,y) == true)
			{
				int i = get_TileType(_map,x,y);
				switch(i)
				{
					case TILE_O_DOOR:
					case TILE_C_DOOR:	apply_surface (808 + (x * 3), 414 + (y * 3), sp_door, _surface);
										break;
					case TILE_WALL: 	apply_surface (808 + (x * 3), 414 + (y * 3), sp_wall, _surface);
										break;
					case TILE_FLOOR:
					case TILE_ROOM:		apply_surface (808 + (x * 3), 414 + (y * 3), sp_floor, _surface);
										break;
				}
			} else {
				apply_surface(808 + (x * 3), 414 + (y * 3), sp_unseen, _surface);
			}
		}
	}
	apply_surface (808 + (_player->x * 3), 414 + (_player->y * 3), sp_player, _surface);
}

int show_surface(SDL_Surface *_surface)
{
	int r = 0;
	if (SDL_Flip(_surface) == -1)
	{
		fprintf(stderr,"Exiting:  Unable to update video\n");
		r = 3;
	}
	return r;
}
	
