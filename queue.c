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

#include "queue.h"

tunnelerQueue *newTQueue(int s)
{
	tunnelerQueue *q = (tunnelerQueue*)malloc(sizeof(tunnelerQueue));
	q->population = (tunneler*)malloc(sizeof(tunneler));
	q->head = 0;
	q->tail = 0;
	q->size = 0;
	q->maxSize = s;
	return q;
}

void dieTQueue (tunnelerQueue *q)
{
	free(q->population);
	free(q);
}

void addTunnelerTQueue(tunnelerQueue *q, tunneler *newT)
{
	if (q->size + 1 <= q->maxSize)
	{
		q->size++;
		q->tail++;
		q->population = (tunneler*)realloc(q->population,sizeof(tunneler) * q->size);
		q->population[q->tail - 1] = newT;
		
	
	
	
	

