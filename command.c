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

Keys *init_Keys(void)
{
	Keys *_keys = (Keys*)malloc(sizeof(Keys) * 322);
	int i;
	for (i = 0; i < 322; i++)
	{
		_keys[i] = false;
	}
	return _keys;
}

bool get_Input(bool *running, map *_map, tileDefs *_TD, Player *_player)
{
	bool updateMap  = false;
	SDL_Event event;
    while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:	updateMap = processCommand(&event.key, _map, _TD, _player);
								break;
			case SDL_KEYUP:	    set_CommandFlags(&event.key, _player);
								break;
       	    case SDL_QUIT:		*running = false; 
               					break;
           	default:			break;
		}
	}
	return updateMap;
}

void set_CommandFlags(SDL_KeyboardEvent *key, Player *_player)
{
	_player->State.isMoving = false;
	switch (key->keysym.sym)
	{
		case SDLK_1:
		case SDLK_KP1:	_player->State.MoveSW = false;
						break;
		case SDLK_2:
		case SDLK_KP2:	_player->State.MoveS = false;
						break;
		case SDLK_3:
		case SDLK_KP3:	_player->State.MoveSE = false;
						break;
		case SDLK_4:
		case SDLK_KP4:	_player->State.MoveW = false;
						break;
		case SDLK_6:
		case SDLK_KP6:	_player->State.MoveE = false;
						break;
		case SDLK_7:
		case SDLK_KP7:	_player->State.MoveNW = false;
						break;
		case SDLK_8:
		case SDLK_KP8:	_player->State.MoveN = false;
						break;
		case SDLK_9:
		case SDLK_KP9:	_player->State.MoveNE = false;
		default:		break;
	}
}
		

bool processCommand(SDL_KeyboardEvent *key, map *_map, tileDefs *_TD, Player *_player)
{
	bool update;
	update = false;
	
	switch (key->keysym.sym)
	{
		case SDLK_1:
		case SDLK_KP1:	/* Move SouthWest */
						set_PlayerState_Moving(_player, true, -1, 1);
						_player->State.MoveSW = true;
						update = true;
						break;
		case SDLK_2:
		case SDLK_DOWN:
		case SDLK_KP2:	/* Move South */
						set_PlayerState_Moving(_player, true, 0, 1);
						_player->State.MoveS = true;
						update = true;
						break;
		case SDLK_3:
		case SDLK_KP3:	/* Move SouthEast */
						set_PlayerState_Moving(_player, true, 1, 1);
						_player->State.MoveSE = true;
						update = true;
						break;
		case SDLK_LEFT:
		case SDLK_4:
		case SDLK_KP4:	/* Move West */
						set_PlayerState_Moving(_player, true, -1, 0);
						_player->State.MoveW = true;
						update = true;
						break;
		case SDLK_5:
		case SDLK_KP5:	/* Do Nothing */
						break;
		case SDLK_6:
		case SDLK_RIGHT:
		case SDLK_KP6:	/* Move East */
						set_PlayerState_Moving(_player, true, 1, 0);
						_player->State.MoveE = true;
						update = true;
						break;
		case SDLK_7:
		case SDLK_KP7:	/* Move NorthWest */
						set_PlayerState_Moving(_player, true, -1, -1);
						_player->State.MoveNW = true;
						update = true;
						break;
		case SDLK_8:
		case SDLK_UP:
		case SDLK_KP8:	/* Move North */
						set_PlayerState_Moving(_player, true, 0, -1);
						_player->State.MoveN = true;
						update = true;
						break;
		case SDLK_9:
		case SDLK_KP9:	/* Move NorthEast */
						set_PlayerState_Moving(_player, true, 1, -1);
						_player->State.MoveNE = true;
						update = true;
						break;
		case SDLK_o:	/* Open a door */
						update = cmd_actionDoor(_map, _player, A_OPEN_DOOR);
						break;
		case SDLK_c:	update = cmd_actionDoor(_map, _player, A_CLOSE_DOOR);
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
		set_Occupied(_map, _player->x, _player->y, false);
		set_Occupied(_map, nx, ny, false);
		_player->x = nx;
		_player->y = ny;
		return true;
	}
	return false;
}

bool cmd_actionDoor(map *_map, Player *_player, int caseOpenClose)
{
	int tiletype;
	switch (caseOpenClose)
	{
		case A_OPEN_DOOR:	tiletype = TILE_C_DOOR; break;
		case A_CLOSE_DOOR:	tiletype = TILE_O_DOOR; break;
	}
	int numDoors = count_SurroundingTypes(_map, _player->x, _player->y, tiletype);

	if (numDoors < 1)
	{
		return false;
	}
	
	_Point *_doorLocs;
	_doorLocs = get_SurroundingTypeLocs(_map, _player->x, _player->y, numDoors, tiletype);

	int i;

	if (_doorLocs == NULL)
	{
		return false;
	}
	for (i = 0; i < numDoors; i++)
	{
		if (caseOpenClose == A_OPEN_DOOR)
		{
			open_Door(_map, _doorLocs[i].x, _doorLocs[i].y);
		} else {
			close_Door(_map, _doorLocs[i].x, _doorLocs[i].y);
		}
	}

	free(_doorLocs);
	return true;
}
		
