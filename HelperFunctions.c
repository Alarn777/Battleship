//
//  HelperFunctions.c
//  Game
//
//  Created by Michael Rokitko on 5/27/17.
//  Copyright © 2017 misha rok. All rights reserved.
//

#include "HelperFunctions.h"
void checkmemory(void *ptr)
{
    if(ptr == NULL)
        printf("Error allocating memory");
}
int checkColomn(char a)
{
    int i = -1;
    switch (a) {
        case 'A':
            i = 1;
            break;
        case 'B':
            i = 2;
            break;
        case 'C':
            i = 3;
            break;
        case 'D':
            i = 4;
            break;
        case 'E':
            i = 5;
            break;
        case 'F':
            i = 6;
            break;
        case 'G':
            i = 7;
            break;
        case 'H':
            i = 8;
            break;
        case 'I':
            i = 9;
            break;
        case 'J':
            i = 10;
            break;
        default:
            i = -1;
    }
    return i;
}
int charIntoInt(char a)
{
    int j = -1;
    j = a - '0';
    return j;
}
char* addtobuff(char *PtrToBuff,char OneToAdd[50])
{
    int count = 0;
    while(OneToAdd[count] != '\0')
    {
        *PtrToBuff = OneToAdd[count];
        count++;
        PtrToBuff++;
    }
    return PtrToBuff;
}



