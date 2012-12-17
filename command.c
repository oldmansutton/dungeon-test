// command.c
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
#include "map.h"
#include "player.h"
#include "command.h"

bool processCommand(SDL_KeyboardEvent *key, map *_map, tileDefs *_TD, Player *_player)
{
	bool update;
	update = false;
	switch (key->keysym.sym)
	{
		case SDLK_1:
		case SDLK_KP1:	/* Move SouthWest */
						update = move_Player(-1, 1, _map, _TD, _player);
						break;
		case SDLK_2:
		case SDLK_DOWN:
		case SDLK_KP2:	/* Move South */
						update = move_Player(0, 1, _map, _TD, _player);
						break;
		case SDLK_3:
		case SDLK_KP3:	/* Move SouthEast */
						update = move_Player(1, 1, _map, _TD, _player);
						break;
		case SDLK_LEFT:
		case SDLK_4:
		case SDLK_KP4:	/* Move West */
						update = move_Player(-1, 0, _map, _TD, _player);
						break;
		case SDLK_5:
		case SDLK_KP5:	/* Do Nothing */
						break;
		case SDLK_6:
		case SDLK_RIGHT:
		case SDLK_KP6:	/* Move East */
						update = move_Player(1, 0, _map, _TD, _player);
						break;
		case SDLK_7:
		case SDLK_KP7:	/* Move NorthWest */
						update = move_Player(-1, -1, _map, _TD, _player);
						break;
		case SDLK_8:
		case SDLK_UP:
		case SDLK_KP8:	/* Move North */
						update = move_Player(0, -1, _map, _TD, _player);
						break;
		case SDLK_9:
		case SDLK_KP9:	/* Move NorthEast */
						update = move_Player(1, -1, _map, _TD, _player);
						break;
		case SDLK_o:	/* Open a door */
						update = cmd_openDoor(_map, _player);
						break;
		default:		break;
	}
	return update;
}

bool move_Player(int x, int y, map *_map, tileDefs *_TD, Player *_player)
{
	int nx, ny;
	nx = _player->x + x;
	ny = _player->y + y;
	if (nx < 1 || nx >= MAP_WIDTH - 1 || ny < 1 || ny >= MAP_HEIGHT - 1)
	{
		return false;
	}
	if (get_TileType(_map, nx, ny) == TILE_C_DOOR)
	{
		/* TO DO: Make config option for auto-open-door */
		open_Door(_map, nx, ny);
	}
	if (tile_Walkable (_map, nx, ny, _TD))
	{
		_player->x = nx;
		_player->y = ny;
		return true;
	}
	return false;
}

bool cmd_openDoor(map *_map, Player *_player)
{
	int numDoors = count_SurroundingTypes(_map, _player->x, _player->y, TILE_C_DOOR);
	if (numDoors < 1)
	{
		return false;
	}
	_Point *_doorLocs;
	_doorLocs = get_SurroundingTypeLocs(_map, _player->x, _player->y, numDoors, TILE_C_DOOR);
	int i;
	if (_doorLocs == NULL)
	{
		return false;
	}
	if (numDoors == 1)
	{
		open_Door(_map, _doorLocs[0].x, _doorLocs[0].y);
		free(_doorLocs);
		return true;
	}		
	for (i = 0; i < numDoors; i++)
	{
		open_Door(_map, _doorLocs[i].x, _doorLocs[i].y);
	}
	free(_doorLocs);
	return true;
}
		
		
