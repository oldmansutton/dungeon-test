// queue.h
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

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "tunneler.h"

typedef struct
{
	tunneler *population; 
	int head;
	int tail;
	int size;
	int maxSize;
} tunnelerQueue;

extern tunnelerQueue *newTQueue(int s);
extern void dieTQueue(tunnelerQueue *q);
extern void addTunnelerTQueue(tunnelerQueue *q, tunneler *newT);



#endif 
