/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) 2012 Ryan Sutton <oldmansutton@gmail.com>
 * 
 * dungeon-test is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * dungeon-test is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include "helper.h"
#include "command.h"
#include "graphics.h"
#include "player.h"
#include "map.h"
#include "generate.h"

int main()
{
	srand(time(NULL));

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Cannot initialize SDL video!\n");
		exit(1);
	}

	atexit(SDL_Quit);
	
    int width = 1000;
    int height = 608;

    SDL_Surface *_screen = SDL_SetVideoMode(width, height, 0, SDL_SWSURFACE);
    if(_screen == NULL) {
        fprintf(stderr, "Error: Invalid screen pointer\n");
        exit(2);
    }

	SDL_WM_SetCaption("dungeon_test", NULL);
	
	
	tileDefs *_TileDefs;
	_TileDefs = init_tileDefs();

	map *_map;
	_map = init_map();

	bool running = true;

	create_Level(_map);

	Player *_player;
	_player = new_Player();

	bool validPXY = false;

	while (!validPXY)
	{
		int rpx, rpy;
		rpx = randr(1,MAP_WIDTH - 1);
		rpy = randr(1,MAP_HEIGHT - 1);
		if (get_TileType(_map,rpx,rpy) == TILE_FLOOR)
		{
			validPXY = true;
			_player->x = rpx;
			_player->y = rpy;
		}
	}

	draw_map(_player->x, _player->y, _map, _TileDefs, _screen);
	apply_surface(12 * 32, 9 * 32,_player->Image,_screen);

	if (SDL_Flip(_screen) == -1)
	{
		return 5;
	}

	while (running)
	{
		SDL_Event event;
		bool updateMap;
		updateMap = false;
	    while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
				case SDL_KEYDOWN:	puts("Keydown\n");
									updateMap = processCommand(&event.key, _map, _TileDefs, _player);
									break;
        	    case SDL_QUIT:		running = false; 
                					break;
            	default:			break;
            }
        }
		if (updateMap)
		{
			draw_map(_player->x, _player->y, _map, _TileDefs, _screen);
			draw_mini_map(_map, _TileDefs, _player, _screen);
			apply_surface(12 * 32, 9 * 32,_player->Image,_screen);
			if (SDL_Flip(_screen) == -1)
			{
				return 5;
			}
		}
	}

	free_Player(_player);
	free_tileDefs(_TileDefs);
	free(_map);
	
	return (0);
	
}
