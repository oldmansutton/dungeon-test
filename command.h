// command.h
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

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <SDL/SDL.h>
#include "map.h"
#include "player.h"

extern bool processCommand(SDL_KeyboardEvent *key, map *_map, tileDefs *_TD, Player *_player);
extern bool move_Player(int x, int y, map *_map, tileDefs *_TD, Player *_player);

#endif
