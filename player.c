// player.c
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

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "graphics.h"
#include "player.h"

Player *new_Player(void)
{
	Player *_player = (Player*)malloc(sizeof(Player));
	_player->x = 0;
	_player->y = 0;
	_player->Image = load_image("player.png");
	return _player;
}

void free_Player(Player *_player)
{
	SDL_FreeSurface(_player->Image);
	free(_player);
}

void set_PlayerState_Moving(Player *_player, bool moving, int byX, int byY)
{
	_player->State.isMoving = moving;
	_player->State.MoveByX = byX;
	_player->State.MoveByY = byY;
}
