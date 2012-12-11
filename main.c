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
#include "map.h"
#include "tunneler.h"
#include "roomer.h"
#include "queue.h"

#define X_LEFT -1
#define X_RIGHT 1
#define Y_UP -1
#define Y_DOWN 1


/* Global Variables */
int **map;
int size_x, size_y;
int cntDug;


int main()
{
	tileDefs *_TileDefs = init_TileDefs();
	
	tunneler *pTunneler;
	tunnelerQueue *queueTunneler;
	
	srand(time(NULL));

	size_x = 64;
	size_y = 90;

	map *_map = init_map();

	pTunneler = malloc(sizeof(tunneler));
	tunneler_rand(pTunneler,1);
	pTunneler->xDir = 0;
	pTunneler->yDir = 1;
	pTunneler->xCoord = 32;
	pTunneler->yCoord = 45;
	pTunneler->roomerSpawn = 100;

	queueTunneler = newTQueue(50);
	if (queueTunneler == 0)
	{
		printf("Out of memory\n");
		return (1);
	}
	pushTunnelerTQueue (queueTunneler, pTunneler);

	int xc,yc,xdir,ydir;

	int newname = 2;

	int qIterate = 0;

	cntDug = 0;
	
	while (queueTunneler->size > 0 && qIterate < 2500)
	{
		qIterate++;
		/* sleep(2); */
		*pTunneler = popTunnelerTQueue(queueTunneler);
		xc = pTunneler->xCoord;
		yc = pTunneler->yCoord;
		xdir = pTunneler->xDir;
		ydir = pTunneler->yDir;

		int validMove = 1;
	
		int chkSQx;
		int chkSQy;
		int cntFloors;
		cntFloors = 0;
		for (chkSQx = -1; chkSQx <= 1; chkSQx++)
		{
			int mapCx;
			mapCx = xc + xdir + chkSQx;
			if (mapCx > 0 && mapCx < size_x - 1) {
				for (chkSQy = -1; chkSQy <= 1; chkSQy++)
				{
					int mapCy;
					mapCy = yc + ydir + chkSQy;
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
		if (xc + (xdir * 2) > 0 && xc + (xdir * 2) < size_x && y + (ydir * 2) > 0 && yc + (ydir * 2) < size_y)
		{
			if (map[xc + (xdir * 2)][yc + (ydir * 2)] == TILE_ROOM)
			{
				int zz, chkz;
				chkz = 1;
				for (zz = -1; zz <= 1; zz++)
				{
					if (map[xc + xdir + (ydir * zz)][yc + ydir + (xdir * zz)] == TILE_DOOR)
					{
						chkz = 0;
					}
				}
				if (chkz == 1)
				{
					map[xc + xdir][yc + ydir] = TILE_DOOR;
				}
				validMove = 0;
			}
		}
		if (cntFloors > pTunneler->neatness)
		{
			validMove = 0;
		}
		if (xc + xdir > 0 && xc + xdir < size_x - 1 && yc + ydir > 0 && yc + ydir < size_y - 1 &&
		    validMove == 1)
		{
			map[xc + xdir][yc + ydir] = TILE_FLOOR;
			cntDug++;
			pTunneler->xCoord = xc + xdir;
			pTunneler->yCoord = yc + ydir;
			/* Check if spawning a roomer, and try to spawn room */
			if (rand() % 100 <= pTunneler->roomerSpawn)
			{				
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
						}
						if (validRoom == 1)
						{
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
						}
						free(crn);
					}
					free(roomsp);
				}
			}
			/* See if tunneler will change directions */
			if (rand() % 100 <= pTunneler->turnChance)
			{
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
			}
			if (pTunneler->age < pTunneler->lifetime)
			{
				pTunneler->age++;
				pushTunnelerTQueue (queueTunneler, pTunneler);
			}
		}
		if ((queueTunneler->size == 0 || qIterate >= 2500) && cntDug < (int)((size_x * size_y) * 0.35))
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
			pTunneler->yCoord = (rand() % (50 + 1 - 40)) + 40;
			newname = 2;
			pushTunnelerTQueue (queueTunneler, pTunneler);
		}
	}
	free(pTunneler);
	dieTQueue(queueTunneler);
	printmap();
	return (0);
	
}
