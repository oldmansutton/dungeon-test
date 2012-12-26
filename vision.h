// vision.h
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

#ifndef VISION_H
#define VISION_H

#include "map.h"

extern void update_PVision(map *_map, tileDefs *_TD, int x, int y, int r);
extern bool in_LineOfSight(int player_x, int player_y, int target_x, int target_y, map *_map, tileDefs *_TD);

#endif
