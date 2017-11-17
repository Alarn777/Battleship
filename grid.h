//
//  grid.h
//  Game
//
//  Created by Michael Rokitko on 5/26/17.
//  Copyright © 2017 misha rok. All rights reserved.
//

#ifndef grid_h
#define grid_h
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HelperFunctions.h"
#include "gameActions.h"
typedef struct grid *Section;
typedef struct PlayerBoard *Board;
Board Create(void);                                             //creates new board for 1 palyer, asks for player name in the middle, returns board created
void printBoard(Board OneToPrint);                              //prints board that given

void filePrintBoard(Board OneToPrint,FILE *out);                //prints board that given to a FILE given

Board HitShip(Board One,int i, int j);                          //symbol for hit ship

Board Missed(Board One,int i, int j);                           //symbol for hit ship

void destroyBoard(Board OneToDestroy);                          //frees memory of 1 board

Board fillSqare(Board One,int i, int j);                        //fill one sqare

int checkPositioning(Board One,int i,int j,int iMax,int jMax); //checks if the coordinates given are valid

int ScanIfShipsLeft(Board One);                                 //checks if the game has ended

void clearBoard(Board One);                                     //puts NULL to all addresses in the board

Board PlayerMove(Board Enemy,int i, int j,int *hitOrNot);      //One Move of a player
int Check(Board One,int i, int j, char *value);
#endif /* grid_h */
