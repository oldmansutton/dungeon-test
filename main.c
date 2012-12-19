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
#include "map.h"
#include "command.h"
#include "graphics.h"
#include "player.h"
#include "generate.h"

int errlvl = 0;

int main()
{
	srand(time(NULL));

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Exiting:  (SDL) Cannot initialize video!\n");
		exit(1);
	}

	atexit(SDL_Quit);
	
    int width = 1000;
    int height = 608;

    SDL_Surface *_screen = SDL_SetVideoMode(width, height, 0, SDL_SWSURFACE);
	if(_screen == NULL) {
        fprintf(stderr, "Exiting:  (SDL) Invalid screen pointer\n");
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

	_Point rCoords;
	rCoords = get_RandWalkable(_map);
	_player->x = rCoords.x;
	_player->y = rCoords.y;

	set_Occupied(_map, _player->x, _player->y, true);

	draw_map(_player->x, _player->y, _map, _TileDefs, _screen);
	draw_mini_map(_map, _TileDefs, _player, _screen);
	apply_surface(12 * 32, 9 * 32,_player->Image,_screen);

	Keys *_keys = init_Keys();
	
	bool updateMap = true;

	Uint32 lasttime = SDL_GetTicks();
	Uint32 dtime;
	
	while (running)
	{
		dtime = SDL_GetTicks() - lasttime;
		updateMap = get_Input(&running, _map, _TileDefs, _player);
		bool playerMoved = false;
		if (_player->State.isMoving && dtime >= 250)
		{
			playerMoved = move_Player(_player->State.MoveByX, _player->State.MoveByY, _map, _TileDefs, _player);
			lasttime = SDL_GetTicks();
		}
		if (updateMap || playerMoved)
		{
			draw_map(_player->x, _player->y, _map, _TileDefs, _screen);
			draw_mini_map(_map, _TileDefs, _player, _screen);
			apply_surface(12 * TILE_WIDTH, 9 * TILE_HEIGHT, _player->Image, _screen);
			errlvl = show_surface(_screen);
			if (errlvl != 0)
			{
				exit(errlvl);
			}
			updateMap = false;
		}
	}

	SDL_FreeSurface(_screen);
	
	free_Player(_player);
	free_tileDefs(_TileDefs);
	free(_map);
	
	return (0);
	
}
