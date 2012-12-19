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

void get_Input(bool *running, Keys *_keys)
{
	SDL_Event event;
    while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:	_keys[event.key.keysym.sym] = true;
								break;
			case SDL_KEYUP:	    _keys[event.key.keysym.sym] = false;
								break;
       	    case SDL_QUIT:		*running = false; 
               					break;
           	default:			break;
		}
	}
}

bool set_MovementFlags(Keys *_keys, Player *_player)
{
	bool isMoving = false;
	set_PlayerState_Moving(_player, false, 0, 0);
	if (_keys[SDLK_1] || _keys[SDLK_KP1])
	{
		set_PlayerState_Moving(_player, true, -1, 1);
		_player->State.MoveSW = true;
		isMoving = true;
	} else {
		_player->State.MoveSW = false;
	}
	if (_keys[SDLK_2] || _keys[SDLK_KP2] || _keys[SDLK_DOWN])
	{
		set_PlayerState_Moving(_player, true, 0, 1);
		_player->State.MoveS = true;
		isMoving = true;
	} else {
		_player->State.MoveS = false;
	}
	if (_keys[SDLK_3] || _keys[SDLK_KP3])
	{
		set_PlayerState_Moving(_player, true, 1, 1);
		_player->State.MoveSE = true;
		isMoving = true;
	} else {
		_player->State.MoveSE = false;
	}
	if (_keys[SDLK_4] || _keys[SDLK_KP4] || _keys[SDLK_LEFT])
	{
		set_PlayerState_Moving(_player, true, -1, 0);
		_player->State.MoveW = true;
		isMoving = true;
	} else {
		_player->State.MoveW = false;
	}
	if (_keys[SDLK_6] || _keys[SDLK_KP6] || _keys[SDLK_RIGHT])
	{
		set_PlayerState_Moving(_player, true, 1, 0);
		_player->State.MoveE = true;
		isMoving = true;
	} else {
		_player->State.MoveE = false;
	}
	if (_keys[SDLK_7] || _keys[SDLK_KP7])
	{
		set_PlayerState_Moving(_player, true, -1, -1);
		_player->State.MoveNW = true;
		isMoving = true;
	} else {
		_player->State.MoveNW = false;
	}
	if (_keys[SDLK_8] || _keys[SDLK_KP8] || _keys[SDLK_UP])
	{
		set_PlayerState_Moving(_player, true, 0, -1);
		_player->State.MoveN = true;
		isMoving = true;
	} else {
		_player->State.MoveN = false;
	}
	if (_keys[SDLK_9] || _keys[SDLK_KP9])
	{
		set_PlayerState_Moving(_player, true, 1, -1);
		_player->State.MoveNE = true;
		isMoving = true;
	} else {
		_player->State.MoveNE = false;
	}
	return isMoving;
}
		

bool processCommand(Keys *_keys, map *_map, Player *_player)
{
	if (set_MovementFlags(_keys, _player))
	{
		return true;
	}

	if (_keys[SDLK_o])	/* Open a door */
	{
		if (cmd_actionDoor(_map, _player, A_OPEN_DOOR))
		{
			return true;
		} else {
			return false;
		}
	}
	if (_keys[SDLK_c])	/* Close a door */
	{
		if (cmd_actionDoor(_map, _player, A_CLOSE_DOOR))
		{
			return true;
		} else {
			return false;
		}
	}
	return false;
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
	int tiletype = -1;
	switch (caseOpenClose)
	{
		case A_OPEN_DOOR:	tiletype = TILE_C_DOOR; break;
		case A_CLOSE_DOOR:	tiletype = TILE_O_DOOR; break;
	}
	if (tiletype < 0)
	{
		return false;
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
		
