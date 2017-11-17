//
//  gameActions.h
//  Game
//
//  Created by Michael Rokitko on 5/27/17.
//  Copyright © 2017 misha rok. All rights reserved.
//

#ifndef gameActions_h
#define gameActions_h
#include <stdio.h>
#include "HelperFunctions.h"
#include "grid.h"
typedef struct grid *Section;
typedef struct PlayerBoard *Board;
Board ShipsFromFile(Board One,FILE* file);                                      //Adds ships when playing via files

Board AddShip(Board OneToAddTo,char* action,int* AddedOrNot,int *ShipSize);     //adds one ship to the board

Board Ships(Board One);                                                         //adds ships in interactive game

Board AddShip(Board OneToAddTo,char* action,int* AddedOrNot,int *ShipSize);     //reads move of the players from FILE and actually makes them

void MovesLive(Board FirstPlayer,Board SecondPlayer,int *HitOrNot,FILE *out);   //game Player VS Player (all of it)

void MoveFromFile(Board FirstPlayer,Board SecondPlayer,FILE* simulation,int *HitOrNot,FILE *out);  //File based movements read and made

#endif /* gameActions_h */
