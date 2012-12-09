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
#include <math.h>
#include "tunneler.h"
#include "roomer.h"
#include "queue.h"

#define TILE_FLOOR 0
#define TILE_WALL 1
#define TILE_DOOR 2
#define TILE_ROOM 3
#define X_LEFT -1
#define X_RIGHT 1
#define Y_UP -1
#define Y_DOWN 1


/* Global Variables */
int **map;
int size_x, size_y;
int cntDug;

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
				case TILE_ROOM:
				case TILE_FLOOR: putchar('.'); break;
				case TILE_DOOR:	  putchar('D'); break;
			}
		}
        putchar('\n');
	}
}


int main()
{
	tunneler *pTunneler;
	tunnelerQueue *queueTunneler;
	
	srand(time(NULL));

	size_x = 64;
	size_y = 64;

	initmap();

	pTunneler = malloc(sizeof(tunneler));
	tunneler_rand(pTunneler,1);
	pTunneler->xDir = 0;
	pTunneler->yDir = 1;
	pTunneler->xCoord = 32;
	pTunneler->yCoord = 32;
	pTunneler->roomerSpawn = 100;

	queueTunneler = newTQueue(50);
	if (queueTunneler == 0)
	{
		printf("Out of memory\n");
		return (1);
	}
	pushTunnelerTQueue (queueTunneler, pTunneler);

	int x,y,xdir,ydir;

	int newname = 2;
	printf("Size of queue is %i\n",queueTunneler->size);

	int qIterate = 0;

	cntDug = 0;
	
	while (queueTunneler->size > 0 && qIterate < 1500)
	{
		qIterate++;
		/* sleep(2); */
		*pTunneler = popTunnelerTQueue(queueTunneler);
   		printf("Size of queue is %i\n",queueTunneler->size);
		x = pTunneler->xCoord;
		y = pTunneler->yCoord;
		xdir = pTunneler->xDir;
		ydir = pTunneler->yDir;
		printf("**NAME** %i\n",pTunneler->name);
		printf("x: %i / y: %i / xdir: %i / ydir: %i\n",x,y,xdir,ydir);
		printf("age: %i / lifetime: %i / Tile: %i\n",pTunneler->age,pTunneler->lifetime,map[x+xdir][y+ydir]);

		int validMove = 1;
	
		int chkSQx;
		int chkSQy;
		int cntFloors;
		cntFloors = 0;
		for (chkSQx = -1; chkSQx <= 1; chkSQx++)
		{
			int mapCx;
			mapCx = x + xdir + chkSQx;
			if (mapCx > 0 && mapCx < size_x - 1) {
				for (chkSQy = -1; chkSQy <= 1; chkSQy++)
				{
					int mapCy;
					mapCy = y + ydir + chkSQy;
					if (mapCy > 0 && mapCy < size_y - 1)
					{
						if (map[mapCx][mapCy] == TILE_FLOOR)
						{
							cntFloors++;
						}
						if (map[mapCx][mapCy] == TILE_ROOM)
						{
							validMove = 0;
							chkSQx = 2;
							chkSQy = 2;
						}
					}
				}
			}
		}
		if (x + (xdir * 2) > 0 && x + (xdir * 2) < size_x && y + (ydir * 2) > 0 && y + (ydir * 2) < size_y)
		{
			if (map[x + (xdir * 2)][y + (ydir * 2)] == TILE_ROOM)
			{
				int zz, chkz;
				chkz = 1;
				for (zz = -1; zz <= 1; zz++)
				{
					if (map[x + xdir + (ydir * zz)][y + ydir + (xdir * zz)] == TILE_DOOR)
					{
						chkz = 0;
					}
				}
				if (chkz == 1)
				{
					map[x + xdir][y + ydir] = TILE_DOOR;
				}
				validMove = 0;
			}
		}
		if (cntFloors > pTunneler->neatness)
		{
			validMove = 0;
		}
		if (x + xdir > 0 && x + xdir < size_x - 1 && y + ydir > 0 && y + ydir < size_y - 1 &&
		    validMove == 1)
		{
			puts("Tunneling\n");
			map[x + xdir][y + ydir] = TILE_FLOOR;
			cntDug++;
			pTunneler->xCoord = x + xdir;
			pTunneler->yCoord = y + ydir;
			/* Check if spawning a roomer, and try to spawn room */
			if (rand() % 100 <= pTunneler->roomerSpawn)
			{				
				puts("Spawning ROOMER\n");
				int dp;
				dp = rand() % 100;
				int dirx = 0;
				int diry = 0;

				if (pTunneler->xDir == 0)
				{
					if (dp < 50)
					{
						dirx = -1;
					} else {
						dirx = 1;
					}
				} else {
					if (dp < 50)
					{
						diry = -1;
					} else {
						diry = 1;
					}
				}
				
				int dx, dy;
				dx = pTunneler->xCoord + dirx;
				dy = pTunneler->yCoord + diry;
				int validDoor = 1;
				if (dx < 1 || dx > size_x - 1 || dy < 1 || dy > size_y - 1)
				{
					validDoor = 0;
				}
				if (validDoor == 1 && map[dx][dy] == TILE_WALL)
				{
					puts("Valid door\n");
					roomer *roomsp;
					roomsp = (roomer*)malloc(sizeof(roomer));
					newRoomer(roomsp,dx,dy,dirx,diry);
					int i_bnd; 
					int chk_bnd;
					if (dirx != 0) 
					{
						chk_bnd = roomsp->dimY;
					} else {
						chk_bnd = roomsp->dimX;
					}
					int validRoom = 1;
					for (i_bnd = rand() % (chk_bnd - 1); i_bnd < chk_bnd; i_bnd++)
					{
						int absx = abs(dirx) * i_bnd;
						int absy = abs(diry) * i_bnd;
						roomCorners *crn = get_RoomCorners(roomsp,absy,absx);
						validRoom = 1;
						if (crn->x_ul <= 0 || crn->x_ul >= size_x - 1 || crn->y_ul <= 0 || crn->y_ul >= size_y - 1) validRoom = 0;
						if (crn->x_ur <= 0 || crn->x_ur >= size_x - 1 || crn->y_ur <= 0 || crn->y_ur >= size_y - 1) validRoom = 0;
						if (crn->x_bl <= 0 || crn->x_bl >= size_x - 1 || crn->y_bl <= 0 || crn->y_bl >= size_y - 1) validRoom = 0;
						if (crn->x_br <= 0 || crn->x_br >= size_x - 1 || crn->y_br <= 0 || crn->y_br >= size_y - 1) validRoom = 0;
						if (validRoom == 1)
						{
							int ixcollide, iycollide;
							for (ixcollide = crn->x_ul-1; ixcollide <= crn->x_br+1; ixcollide++)
							{
								for (iycollide = crn->y_ul-1; iycollide <= crn->y_br+1; iycollide++)
								{
									if (map[ixcollide][iycollide] != TILE_WALL)
									{
										validRoom = 0;
										ixcollide = size_x;
										iycollide = size_y;
									}
								}
							}
						} else {
							puts("Room outside bounds\n");
						}
						if (validRoom == 1)
						{
							puts("Room valid!! Digging Room!\n");
							int ixdig, iydig;
							for (ixdig = crn->x_ul; ixdig <= crn->x_br; ixdig++)
							{
								for (iydig = crn->y_ul; iydig <= crn->y_br; iydig++)
								{
									map[ixdig][iydig] = TILE_ROOM;
									cntDug++;
								}
							}
							map[roomsp->doorX][roomsp->doorY] = TILE_DOOR;
							i_bnd = chk_bnd + 1;
						} else {
							puts("Room intersects tunnels\n");
						}
						free(crn);
					}
					free(roomsp);
				} else {
					puts("Can't place room's door\n");
				}
			}
			/* See if tunneler will change directions */
			if (rand() % 100 <= pTunneler->turnChance)
			{
				puts("Changing direction\n");
				if (pTunneler->xDir == 0)
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
		} else {
			puts("Tunneler dying - map boundary or next tile in line is floor\n");
		}
		if ((queueTunneler->size == 0 || qIterate >= 1500) && cntDug < (int)((size_x * size_y) * 0.35))
		{
			int xi;
			for (xi = 0; xi < size_x; xi++)
			{
				free(map[xi]);
			}
			free(map);
			initmap();
			cntDug = 0;
			qIterate = 0;
			tunneler_rand(pTunneler,1);
			pTunneler->xCoord = (rand() % (36 + 1 - 28)) + 28;
			pTunneler->yCoord = (rand() % (36 + 1 - 28)) + 28;
			newname = 2;
			pushTunnelerTQueue (queueTunneler, pTunneler);
		}
	}
	free(pTunneler);
	dieTQueue(queueTunneler);
	printmap();
	return (0);
	
}
