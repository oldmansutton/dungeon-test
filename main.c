/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) 2012 Ryan Sutton <oldmansutton@gmail.com>
 * 
 * dungeon-test is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * dungeon-test is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tunneler.h"
#include "queue.h"

#define TILE_FLOOR 0
#define TILE_WALL 1

/* Global Variables */
int **map;
int size_x = 64, size_y = 64;

void initmap(void)  /* Initialize the map */
{
	int xi, yi;

	/* Allocate memory for multidimensional map array */
	map = (int**)malloc(sizeof(int*) * size_x);
	for (xi = 0; xi < size_x; xi++)
	{
		map[xi] = (int*)malloc(sizeof(int) * size_y);
	}

	/* Fill map grid with "WALL" tiles */
	for (xi = 0; xi < size_x; xi++)
	{
		for (yi = 0; yi < size_y; yi++)
		{
			map[xi][yi] = TILE_WALL;
		}
	}
}

int main()
{
	int ii = 0;
	tunneler *pTunneler;
	tunnelerQueue *queueTunneler;
	tunnelerQueue *queueList;
	
	srand(time(NULL));

	pTunneler = malloc(sizeof(Tunneler));
	tunneler_rand(&pTunneler);

	queueTunneler = malloc(sizeof(TunnelerQueue));
	if (queueTunneler == 0)
	{
		printf("Out of memory\n");
		return (1);
	}
	queueTunneler->qTunneler = &pTunneler;
	queueTunneler->next = 0;

	int x,y,xdir,ydir,die;
	
	while (queueTunneler != NULL)
	{
		pTunneler = queueTunneler->qTunneler;

		die = 0;
		x = pTunneler->xCoord;
		y = pTunneler->yCoord;
		xdir = pTunneler->xDir;
		ydir = pTunneler->yDir;

		if (x + xdir > 0 && x + xdir < size_x - 1 && 
		    y + ydir > 0 && y + ydir < size_y - 1 && 
		    map[x+xdir][y+ydir] == TILE_WALL)
		{
			if (x + (xdir * 2) >= 0 && x + (xdir * 2) <= size_x - 1 && 
			    y + (ydir * 2) >= 0 && y + (ydir * 2) <= size_y - 1)
			{
				if (map[y + (ydir * 2)][x + (xdir * 2)] == TILE_FLOOR)
				{
					die = 1;
				}
			}
			if (die == 0)
			{
				map[x + xdir][y + ydir] = TILE_FLOOR;
				pTunneler->xCoord = x + xdir;
				pTunneler->yCoord = y + ydir;
				/* See if tunneler will change directions */
				if (rand() % 100 <= pTunneler->turnChance)
				{
					pTunneler->xDir = 0;
					pTunneler->yDir = 0;
					if (rand() % 100 < 50)
					{
						if (rand() % 100 < 50)
						{
							pTunneler->xDir = -1;
						} else {
							pTunneler->xDir = 1;
						}
					} else {
						if (rand() % 100 < 50)
						{
							pTunneler->yDir = -1;
						} else {
							pTunneler->yDir = 1;
						}
					}
				}
				/* See if tunneler will spawn a child tunneler */
				

		}
	}

	

	return (0);
}
