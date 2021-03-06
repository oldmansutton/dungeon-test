// player.h
//
// Copyright (C) 2012 - oldmansutton
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

#ifndef PLAYER_H
#define PLAYER_H

#include <SDL/SDL.h>

typedef struct
{
	bool MoveNW;
	bool MoveN;
	bool MoveNE;
	bool MoveW;
	bool MoveE;
	bool MoveSW;
	bool MoveS;
	bool MoveSE;
	bool isMoving;
	int MoveByX;
	int MoveByY;
} PlayerState;

typedef struct
{
	int x;
	int y;
	SDL_Surface *Image;
	PlayerState State;
} Player;

extern Player *new_Player(void);
extern void free_Player(Player *_player);

extern void set_PlayerState_Moving(Player *_player, bool moving, int byX, int byY);

#endif
