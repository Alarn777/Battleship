//
//  HelperFunctions.h
//  Game
//
//  Created by Michael Rokitko on 5/27/17.
//  Copyright © 2017 misha rok. All rights reserved.
//

#ifndef HelperFunctions_h
#define HelperFunctions_h
#include "grid.h"
#include "gameActions.h"
void checkmemory(void *ptr);                            //memory allocation check

int checkColomn(char a);                                //takes char and gives back coordinates of x in board

int charIntoInt(char a);                                // turns char in to int

char* addtobuff(char *PtrToBuff,char OneToAdd[50]);     //stores all the moves and resoults in the buffer
#endif /* HelperFunctions_h */
