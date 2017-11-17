//
//  AI.h
//  Game
//
//  Created by Michael Rokitko on 5/31/17.
//  Copyright © 2017 misha rok. All rights reserved.
//

#ifndef AI_h
#define AI_h
#include "grid.h"
#include "gameActions.h"
#include "HelperFunctions.h"
typedef struct grid *Section;
typedef struct PlayerBoard *Board;
Board HitRight(Board One,int i,int j,int *Hit);                     //HitRight

Board HitLeft(Board One,int i,int j,int *Hit);                      //HitLeft

Board HitBot(Board One,int i,int j,int *Hit);                       //HitBot

Board HitTop(Board One,int i,int j,int *Hit);                       //HitTop

Board HitTopLeft(Board One,int i,int j,int *Hit);                   //HitTopLeft

Board HitTopRight(Board One,int i,int j,int *Hit);                  //HitTopRight

Board HitBotLeft(Board One,int i,int j,int *Hit);                   //HiltBotLeft

Board HitBotRight(Board One,int i,int j,int *Hit);                  //HiltBotRight

Board ShipPlacement(Board One);                                     //my AI will place some ships on the board

void MovesVS_AI(Board FirstPlayer,Board SecondPlayer,FILE *out);    //you will play against my AI here (pure magic)

#endif /* AI_h */
