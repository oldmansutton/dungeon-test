// queue.c
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

#include <stdio.h>
#include "queue.h"

tunnelerQueue *newTQueue(int s)
{
	tunnelerQueue *q = (tunnelerQueue*)malloc(sizeof(tunnelerQueue));
	q->population = (tunneler*)malloc(sizeof(tunneler) * s);
	q->size = 0;
	q->maxSize = s;
	return q;
}

void dieTQueue (tunnelerQueue *q)
{
	puts("Removing queue\n");
	free(q->population);
	free(q);
}

void pushTunnelerTQueue(tunnelerQueue *q, tunneler *newT)
{
	if (q->size + 1 <= q->maxSize)
	{
		q->population[q->size] = *newT;
		q->size++;
	} else {
		/* Queue is full, do nothing */
	}
}

tunneler popTunnelerTQueue(tunnelerQueue *q)
{
	tunneler rtn;
	if (q->population != NULL && q->size > 0)
	{
		rtn = q->population[0];
		int i;
		for (i = 0; i < q->size; i++)
		{
			q->population[i] = q->population[i + 1];
		}
		q->size--;
	}
	return rtn;
}
			
			
		
		
		
	
	
	
	

