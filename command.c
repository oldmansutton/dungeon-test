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

#include "command.h"

void processCommand(SDL_KeyboardEvent *key)
{
	switch (key->keysym.sym)
	{
		case SDLK_KP1:	/* Move SouthWest */
						break;
		case SDLK_KP2:	/* Move South */
						break;
		case SDLK_KP3:	/* Move SouthEast */
						break;
		case SDLK_KP4:	/* Move West */
						break;
		case SDLK_KP5:	/* Do Nothing */
						break;
		case SDLK_KP6:	/* Move East */
						break;
		case SDLK_KP7:	/* Move NorthWest */
						break;
		case SDLK_KP8:	/* Move North */
						break;
		case SDLK_KP9:	/* Move NorthEast */
						break;
	}
}
