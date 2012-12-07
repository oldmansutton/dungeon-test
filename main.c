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
int size_x, size_y;

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

void printmap(void)
{
	int xi, yi;

	for(xi = 0; xi < size_x; xi++)
	{
		for(yi = 0; yi < size_y; yi++)
		{
			switch(map[xi][yi]) 
			{
				case TILE_WALL:  putchar('#'); break;
				case TILE_FLOOR: putchar('.'); break;
			}
		}
        putchar('\n');
	}
}


int main()
{
	int ii = 0;
	tunneler *pTunneler;
	tunnelerQueue *queueTunneler;
	
	srand(time(NULL));

	size_x = 64;
	size_y = 64;

	initmap();

	pTunneler = malloc(sizeof(tunneler));
	tunneler_rand(pTunneler,1);
	pTunneler->xCoord = 32;
	pTunneler->yCoord = 32;

	queueTunneler = newTQueue(50);
	if (queueTunneler == 0)
	{
		printf("Out of memory\n");
		return (1);
	}
	pushTunnelerTQueue (queueTunneler, pTunneler);

	int x,y,xdir,ydir,die;

	int newname = 2;
	printf("Size of queue is %i\n",queueTunneler->size);
	
	while (queueTunneler->size > 0)
	{
		/* sleep(2); */
		*pTunneler = popTunnelerTQueue(queueTunneler);
    	printf("Size of queue is %i\n",queueTunneler->size);

		die = 0;
		x = pTunneler->xCoord;
		y = pTunneler->yCoord;
		xdir = pTunneler->xDir;
		ydir = pTunneler->yDir;

		printf("**NAME** %i\n",pTunneler->name);
		printf("x: %i / y: %i / xdir: %i / ydir: %i\n",x,y,xdir,ydir);
		printf("age: %i / lifetime: %i / Tile: %i\n",pTunneler->age,pTunneler->lifetime,map[x+xdir][y+ydir]);
		
		if (x + xdir > 0 && x + xdir < size_x - 1 && 
		    y + ydir > 0 && y + ydir < size_y - 1 &&
		    map[x+xdir][y+ydir] == TILE_WALL)
		{
			if (x + (xdir * 2) >= 0 && x + (xdir * 2) <= size_x - 1 && 
			    y + (ydir * 2) >= 0 && y + (ydir * 2) <= size_y - 1)
			{
				if (map[y + (ydir * 2)][x + (xdir * 2)] == TILE_FLOOR)
				{
					puts("Tunneler dying - Won't break through corridor\n");					
					die = 1;
				}
			}
			if (die == 0)
			{
				puts("Tunneling\n");
				map[x + xdir][y + ydir] = TILE_FLOOR;
				pTunneler->xCoord = x + xdir;
				pTunneler->yCoord = y + ydir;
				/* See if tunneler will change directions */
				if (rand() % 100 <= pTunneler->turnChance)
				{
					puts("Changing direction\n");
					if (pTunneler->yDir != 0)
					{
						pTunneler->yDir = 0;
						if (rand() % 100 < 50)
						{
							pTunneler->xDir = -1;
						} else {
							pTunneler->xDir = 1;
						}
					} else {
						pTunneler->xDir = 0;
						if (rand() % 100 < 50)
						{
							pTunneler->yDir = -1;
						} else {
							pTunneler->yDir = 1;
						}
					}
				}
				/* See if tunneler will spawn a child tunneler */
				if (rand() % 100 <= pTunneler->tunnelerSpawn)
				{
					puts("Spawning new tunneler\n");
					tunneler *temp = (tunneler*)malloc(sizeof(tunneler));
					tunneler_rand(temp,newname);
					newname++;
					temp->xCoord = pTunneler->xCoord;
					temp->yCoord = pTunneler->yCoord;

					int dp = rand() % 100;
					temp->xDir = 0;
					temp->yDir = 0;
					if (pTunneler->xDir == 0)
					{
						if (dp < 50)
						{
							temp->xDir = -1;
						} else {
							temp->xDir = 1;
						}
					} else {
						if (dp < 50)
						{
							temp->yDir = -1;
						} else {
							temp->yDir = 1;
						}
					}
					pushTunnelerTQueue(queueTunneler, temp);
					free(temp);
					printf("Size of queue is %i\n",queueTunneler->size);
				}
				if (pTunneler->age < pTunneler->lifetime)
				{
					pTunneler->age++;
					pushTunnelerTQueue (queueTunneler, pTunneler);
					printf("Size of queue is %i\n",queueTunneler->size);
				} else {
					puts("Tunneler dying - old age\n");
				}
			}
		} else {
			puts("Tunneler dying - map boundary or next tile in line is floor\n");
		}
	}
	free(pTunneler);
	dieTQueue(queueTunneler);
	printmap();
	return (0);
}
