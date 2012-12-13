// generate.c
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
#include <math.h>
#include "generate.h"
#include "tunneler.h"
#include "queue.h"
#include "roomer.h"

void create_Level(map *_map)
{
	int x, y;
	/* Start with a clean map */
	for (y = 1; y < MAP_HEIGHT - 1; y++)
	{
		for (x = 1; x < MAP_WIDTH - 1; x++)
		{
			set_TileType (_map, x, y, TILE_WALL);
		}
	}
	if (rand() % 100 < CAVERN_CHANCE)
	{
		gen_Noise(_map);
		int i;
		for (i = 0; i < CAVERN_RECURSE; i++)
		{
			gen_Cavern(_map,CAVERN_R1,CAVERN_R2);
		}
		for (i = 0; i < CAVERN_RECURSE - 1; i++)
		{
			gen_Cavern(_map,CAVERN_R1,-1);
		}
		/* TO DO:  Remove unreachable locations from map (find spot, flood fill, unfilled are walls) */
	} else {
		/* TO DO:  Add more dungeon types by tweaking min/max ranges */
		switch(rand() % 8)
		{
			case 0:
			case 2:	gen_Dungeon(_map,15,60,10,33,10,40,15,30,2,6,50);
					break;
			case 1:	
			case 3:	gen_Dungeon(_map,40,60,0,15,20,20,20,30,2,4,50);
					break;
			case 4:	gen_Dungeon(_map,35,35,0,5,40,60,10,25,7,9,20);
					break;
			case 5:	gen_Dungeon(_map,10,10,0,0,50,75,0,15,3,3,30);
					break;
			case 6:	
			case 7:	gen_Dungeon(_map,33,33,12,12,33,33,25,25,3,3,25);
					break;
		}
	}
}

void gen_Dungeon(map *_map, int lifeMin, int lifeMax, int turnMin, int turnMax, int tspMin, int tspMax, int rspMin, int rspMax, int neatMin, int neatMax, int chanceDoor)
{
	tunneler *pTunneler;
	tunnelerQueue *queueTunneler;

	pTunneler = malloc(sizeof(tunneler));
	tunneler_rand(pTunneler,lifeMin,lifeMax,turnMin,turnMax,tspMin,tspMax,rspMin,rspMax,neatMin,neatMax);
	pTunneler->xDir = 0;
	pTunneler->yDir = 1;
	pTunneler->xCoord = MAP_WIDTH / 2;
	pTunneler->yCoord = MAP_HEIGHT / 2;

	queueTunneler = newTQueue(50);
	if (queueTunneler == 0)
	{
		fprintf(stderr, "Out of memory (Queuing Tunnelers)\n");
		return;
	}
	
	pushTunnelerTQueue(queueTunneler, pTunneler);

	int xc,yc,xdir,ydir;
	int newname = 2;
	int qIterate = 0;
	int cntDug = 0;
	
	while (queueTunneler->size > 0 && qIterate < 2500)
	{
		qIterate++;
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
			if (mapCx > 0 && mapCx < MAP_WIDTH - 1) {
				for (chkSQy = -1; chkSQy <= 1; chkSQy++)
				{
					int mapCy;
					mapCy = yc + ydir + chkSQy;
					if (mapCy > 0 && mapCy < MAP_HEIGHT - 1)
					{
						switch(get_TileType(_map,mapCx,mapCy))
						{
							case TILE_FLOOR:	cntFloors++;
												break;
							case TILE_ROOM:		validMove = 0;
												chkSQx = 2;
												chkSQy = 2;
						}
					}
				}
			}
		}
		if (xc + (xdir * 2) > 0 && xc + (xdir * 2) < MAP_WIDTH && yc + (ydir * 2) > 0 && yc + (ydir * 2) < MAP_HEIGHT)
		{
			if (get_TileType(_map,xc + (xdir * 2),yc + (ydir * 2)) == TILE_ROOM)
			{
				int zz, chkz;
				chkz = 1;
				for (zz = -1; zz <= 1; zz++)
				{
					if (get_TileType(_map,xc + xdir + (ydir * zz),yc + ydir + (xdir * zz)) == TILE_DOOR)
					{
						chkz = 0;
					}
				}
				if (chkz == 1 && rand() % 100 < chanceDoor)
				{
					set_TileType(_map,xc + xdir,yc + ydir,TILE_DOOR);
				}
				validMove = 0;
			}
		}
		if (cntFloors > pTunneler->neatness)
		{
			validMove = 0;
		}
		if (xc + xdir > 0 && xc + xdir < MAP_WIDTH - 1 && yc + ydir > 0 && yc + ydir < MAP_HEIGHT - 1 &&
		    validMove == 1)
		{
			set_TileType(_map,xc + xdir,yc + ydir,TILE_FLOOR);
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
				if (dx < 1 || dx > MAP_WIDTH - 1 || dy < 1 || dy > MAP_HEIGHT - 1)
				{
					validDoor = 0;
				}
				if (validDoor == 1 && get_TileType(_map,dx,dy) == TILE_WALL)
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
						if (crn->x_ul <= 0 || crn->x_ul >= MAP_WIDTH - 1 || crn->y_ul <= 0 || crn->y_ul >= MAP_HEIGHT - 1) validRoom = 0;
						if (crn->x_ur <= 0 || crn->x_ur >= MAP_WIDTH - 1 || crn->y_ur <= 0 || crn->y_ur >= MAP_HEIGHT - 1) validRoom = 0;
						if (crn->x_bl <= 0 || crn->x_bl >= MAP_WIDTH - 1 || crn->y_bl <= 0 || crn->y_bl >= MAP_HEIGHT - 1) validRoom = 0;
						if (crn->x_br <= 0 || crn->x_br >= MAP_WIDTH - 1 || crn->y_br <= 0 || crn->y_br >= MAP_HEIGHT - 1) validRoom = 0;
						if (validRoom == 1)
						{
							int ixcollide, iycollide;
							for (ixcollide = crn->x_ul-1; ixcollide <= crn->x_br+1; ixcollide++)
							{
								for (iycollide = crn->y_ul-1; iycollide <= crn->y_br+1; iycollide++)
								{
									if (get_TileType(_map,ixcollide,iycollide) != TILE_WALL)
									{
										validRoom = 0;
										ixcollide = MAP_WIDTH;
										iycollide = MAP_HEIGHT;
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
									set_TileType(_map,ixdig,iydig,TILE_ROOM);
									cntDug++;
								}
							}
							set_TileType(_map,roomsp->doorX,roomsp->doorY,TILE_DOOR);
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
				tunneler_rand(temp,lifeMin,lifeMax,turnMin,turnMax,tspMin,tspMax,rspMin,rspMax,neatMin,neatMax);
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
		if ((queueTunneler->size == 0 || qIterate >= 2500) && cntDug < (int)((MAP_WIDTH * MAP_HEIGHT) * 0.35))
		{
			int xi;
			free(_map);
			_map = init_map();
			cntDug = 0;
			qIterate = 0;
			tunneler_rand(pTunneler,lifeMin,lifeMax,turnMin,turnMax,tspMin,tspMax,rspMin,rspMax,neatMin,neatMax);
			pTunneler->xCoord = (rand() % ((MAP_WIDTH + 4) + 1 - (MAP_WIDTH - 4))) + (MAP_WIDTH - 4);
			pTunneler->yCoord = (rand() % ((MAP_HEIGHT + 4) + 1 - (MAP_HEIGHT - 4))) + (MAP_HEIGHT - 4);
			newname = 2;
			pushTunnelerTQueue (queueTunneler, pTunneler);
		}
	}
	free(pTunneler);
	dieTQueue(queueTunneler);	
}

void gen_Noise(map *_map)
{
	int xa, ya;
	for (ya = 1; ya < MAP_HEIGHT - 1; ya++)
	{
		for (xa = 1; xa < MAP_WIDTH - 1; xa++)
		{
			if(rand() % 100 < CAVERN_NOISE)
			{
				set_TileType(_map,xa,ya,TILE_WALL);
			} else {
				set_TileType(_map,xa,ya,TILE_FLOOR);
			}
		}
	}
}
			
void gen_Cavern(map *_map, int r1, int r2)
{
	int x, y;
	int *_maptmp = (int*)malloc(sizeof(int) * MAP_HEIGHT * MAP_WIDTH);
	for (y = 1; y < MAP_HEIGHT - 1; y++)
	{
		for (x = 1; x < MAP_WIDTH - 1; x++)
		{
			int xb, yb;
			int adjcnt_r1 = 0;
			int adjcnt_r2 = 0;
			for (yb = -1; yb <= 1; yb++)
			{
				for (xb = -1; xb <= 1; xb++)
				{
					if(get_TileType(_map,x + xb,y + yb) == TILE_WALL)
					{
						adjcnt_r1++;
					}				
				}
			}
			if (r2 >= 0)
			{
				for (yb = y - 2; yb <= y + 2; yb++)
				{
					for (xb = x - 2; xb <= x + 2; xb++)
					{
						if (abs(yb - y) == 2 && abs(xb - x) == 2)
						{
							continue;
						}
						if (yb < 0 || xb < 0 || yb >= MAP_HEIGHT || xb >= MAP_WIDTH)
						{
							continue;
						}
						if (get_TileType(_map,xb,yb) == TILE_WALL)
						{
							adjcnt_r2++;
						}
					}
				}
			}
			if (adjcnt_r1 >= r1 || adjcnt_r2 <= r2)
			{
				_maptmp[MAP_XY(x,y)] = TILE_WALL;
			} else {
				_maptmp[MAP_XY(x,y)] = TILE_FLOOR;
			}
		}
	}
	for (y = 1; y < MAP_HEIGHT - 1; y++)
	{
		for (x = 1; x < MAP_WIDTH - 1; x++)
		{
			set_TileType (_map,x,y,_maptmp[MAP_XY(x,y)]);
		}
	}
}
