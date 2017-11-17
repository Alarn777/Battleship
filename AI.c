//
//  AI.c
//  Game
//
//  Created by Michael Rokitko on 5/31/17.
//  Copyright © 2017 misha rok. All rights reserved.
//

#include "AI.h"
#include <stdlib.h>
#include <time.h>
Board ShipPlacement(Board One)
{
    char buffer[96];
    char *action = buffer;
    int i = -1,iMax = -1,j = -1,jMax = -1,random = 0;
    srand(time(NULL));
    random =  rand();
    while(random > 10)
        random %= 10;
    switch (random) {
        case 1:
            strcpy(buffer, "A10-A10I2-I2I8-I8C7-C7F5-F6A5-A6E9-E10J4-J6B3-D3C1-F1");
            break;
        case 2:
            strcpy(buffer,"A10-A10J10-J10I1-I1A3-B3A7-B7J3-J4C10-E10D3-F3B5-E5");
            break;
        case 3:
            strcpy(buffer,"G2-G2J10-J10D7-D7D9-D9J2-J3C3-C4G9-H9A8-A10H5-H7E2-E5");
            break;
        case 4:
            strcpy(buffer,"J5-J5I3-I3E6-E6C10-C10A9-A10G3-G4D1-E1B3-D3B5-B7F8-I8");
            break;
        case 5:
            strcpy(buffer,"A1-A1A3-A3J1-J1C9-C9J3-J4H3-H4H7-H8G10-I10C1-E1A5-D5");
            break;
        case 6:
            strcpy(buffer,"B1-B1H2-H2J5-J5H9-H9D2-D3F1-F2G7-H7J1-J3B6-B8E7-E10");
            break;
        case 7:
            strcpy(buffer,"B1-B1D1-D1H9-H9B5-B5I1-I2J8-J9B10-C10B3-D3G6-I6D5-D8");
            break;
        case 8:
            strcpy(buffer,"F1-F1H3-H3F4-F4A6-A6C2-C3E8-F8H10-I10I5-I7A10-C10C5-C8");
            break;
        case 9:
            strcpy(buffer,"J10-J10J7-J7G6-G6D10-D10G8-H8B8-C8A6-B6D1-F1G3-I3E4-E7");
            break;
        default:
            strcpy(buffer,"A1-A1A10-A10J10-J10J1-J1C1-C2E1-E2G1-G2C8-C10E8-E10J3-J6");
            
    }
    while(*action != '\0')
    {
        i = checkColomn(*action);
        action++;
        if(action[1] == '0')
        {
            j = 10;
            action++;
        }
        else
            j = charIntoInt(*action);
            action++;
            action++;
            iMax = checkColomn(*action);
            action++;
            if(action[1] == '0')
            {
                jMax = 10;
                action++;
            }
        else
            jMax = charIntoInt(*action);
        action++;
        
    if (i == iMax)
        for(;j<=jMax;j++)
                fillSqare(One,i,j);
    
    if(j == jMax)
        for(;i<=iMax;i++)
            fillSqare(One,i,j);
        
    
    }
    return One;
}

void MovesVS_AI(Board FirstPlayer,Board SecondPlayer,FILE *out)           //functiom of PC VS Player
{
    int dummy = 0;
    int *dummyptr = & dummy;
    Board HitsOfUser = (Board)malloc(sizeof(Board));
    HitsOfUser = Create();
    Board HitsOfAI = (Board)malloc(sizeof(Board));
    HitsOfAI = Create();
    char buffer[256],bufferAI[16];
    srand(time(NULL));
    strcpy(bufferAI,"x");
    //char bufferHuge[8192];
    //char *PtrToMainBuffer = bufferHuge;
    int i = -1,j = -1,hit = 99,countForAI = 0,MoveResoultForAI = 99,iForAI = -1,jForAI = -1,AIMissed = 0,AIHit = 0,HitShipAI = 0,right = 0,left = 0,bot = 0,top = 0,skiprand = 0;
    int *HitOrNot = &hit;

    strcpy(buffer,"rly?");
    printf("You can end the game at all given times by typing <End>\n");
    while (!ScanIfShipsLeft(FirstPlayer) && !ScanIfShipsLeft(SecondPlayer))
    {
        while(strcmp(buffer,"End") != 0)
        {
                if(1)           //user moves
                {
            do                                                                                          //added
            {
                printf("Please Enter good coordinates to fire on <[][]>\n");
                scanf("%s",buffer);
                if(strcmp(buffer,"End") == 0)
                    break;
                if(buffer[2] == '\0')
                    buffer[3] = '\0';
                if(buffer[1] == '0')
                {
                    buffer[3] = '1';
                }
            }while(!(checkColomn(buffer[0]) > 0) || buffer[3] != '\0' ||  (buffer[2] != '0' && buffer[2] != '\0'));
            if(strcmp(buffer,"End") == 0)
                continue;
            i = checkColomn(buffer[0]);
            if(buffer[1] == '1' && buffer[2] == '0')
                j = 10;
            else
                j = buffer[1] - '0';
            SecondPlayer = PlayerMove(SecondPlayer,i,j,HitOrNot);
            switch (*HitOrNot) {
                case 1:
                    HitShip(HitsOfUser,i,j);
                    printf("Hit!\n\n");
                    printf("                           Enemy Board\n");
                    printBoard(HitsOfUser);
                    break;
                case 0:
                    printf("Missed!\n\n");
                    Missed(HitsOfUser,i,j);
                    printf("                           Enemy Board\n");
                    printBoard(HitsOfUser);
                    break;
                case -1:
                    printf("You already hit here,turn is passed to player 2\n\n");
                    printf("                           Enemy Board\n");
                    printBoard(HitsOfUser);

                    break;
            }
            if(ScanIfShipsLeft(SecondPlayer))
            {
                printf("You won!\n");
                strcpy(buffer,"End");
                continue;
            }
            }
            printf("\nComputer Fires\n");
            
            if(HitShipAI >= 2)                                                                  //if the PC hit random and after that hit one more time
            {
                if(iForAI == 10 && right)
                {
                    if(Check(FirstPlayer, iForAI, jForAI,bufferAI))                          //
                    {
                        FirstPlayer = PlayerMove(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1)
                            HitShip(HitsOfAI,iForAI,jForAI);
                        else
                            Missed(HitsOfAI,iForAI,jForAI);
                        
                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        goto Switchlabel;
                    }
                    else
                    {
                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        goto randLable;
                    }
                }
                if(jForAI == 10 && bot)
                {
                    if(Check(FirstPlayer, iForAI, jForAI,bufferAI))                          //
                    {
                        FirstPlayer = PlayerMove(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1)
                            HitShip(HitsOfAI,iForAI,jForAI);
                        else
                            Missed(HitsOfAI,iForAI,jForAI);
                        

                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        goto Switchlabel;
                    }
                    else
                    {
                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        goto randLable;
                    }
                }
                if(iForAI == 1 && left)
                {
                    if(Check(FirstPlayer, iForAI, jForAI,bufferAI))                          //
                    {
                        FirstPlayer = PlayerMove(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1)
                            HitShip(HitsOfAI,iForAI,jForAI);
                        else
                            Missed(HitsOfAI,iForAI,jForAI);
                        

                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        goto Switchlabel;
                    }
                    else
                    {
                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        goto randLable;
                    }
                }
                if(jForAI == 1 && top)
                {
                    if(Check(FirstPlayer, iForAI, jForAI,bufferAI))                          //
                    {
                        FirstPlayer = PlayerMove(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1)
                            HitShip(HitsOfAI,iForAI,jForAI);
                        else
                            Missed(HitsOfAI,iForAI,jForAI);
                        

                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        goto Switchlabel;
                    }
                    else
                    {
                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        goto randLable;
                    }
                }
                if(right)
                {
                    if(Check(FirstPlayer, iForAI+1, jForAI,bufferAI))                          //if hits
                    {
                        FirstPlayer = HitRight(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot != 1)
                        {
                            HitShipAI = 0;
                            AIMissed = 0;
                            AIHit = 0;
                            Missed(HitsOfAI,iForAI+1,jForAI);
                            goto Switchlabel;
                        }
                        if(*HitOrNot == 1)
                        {
                            if(iForAI != 1 && iForAI != 10 && jForAI != 1 && jForAI != 10 )
                            {
                                HitShip(HitsOfAI,iForAI+1,jForAI);
                                HitTop(FirstPlayer,iForAI,jForAI,dummyptr);
                                HitBot(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            if(iForAI == 1 && jForAI != 1 && jForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI+1,jForAI);
                                HitTopRight(FirstPlayer,iForAI,jForAI,dummyptr);
                                HitBotRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            if(iForAI == 10 && jForAI != 1 && jForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI+1,jForAI);
                                HitTopLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                                HitBotLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            if(jForAI == 1 && iForAI != 1 && iForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI+1,jForAI);
                                HitBot(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            if(jForAI == 10 && iForAI != 1 && iForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI+1,jForAI);
                                HitTop(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            iForAI -= 1;
                            goto Switchlabel;
                        }
                        iForAI += 1;
                        goto Switchlabel;
                    }
                    else
                    {
                        skiprand = 1;
                        goto BackHitLable;
                    }
                }
                if(left)
                {
                    if(Check(FirstPlayer, iForAI-1, jForAI,bufferAI))                          //if hits
                    {
                        FirstPlayer = HitLeft(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot != 1)
                            {
                            Missed(HitsOfAI,iForAI-1,jForAI);
                            HitShipAI = 0;
                            AIMissed = 0;
                            AIHit = 0;
                            goto Switchlabel;
                        }
                        if(*HitOrNot == 1)
                            {
                            if(iForAI != 1 && iForAI != 10 && jForAI != 1 && jForAI != 10 )
                                    {
                                        HitShip(HitsOfAI,iForAI-1,jForAI);
                                        HitTop(FirstPlayer,iForAI,jForAI,dummyptr);
                                        HitBot(FirstPlayer,iForAI,jForAI,dummyptr);
                                    }
                                if(iForAI == 1 && jForAI != 1 && jForAI != 10)
                                    {
                                        HitShip(HitsOfAI,iForAI-1,jForAI);
                                        HitTopRight(FirstPlayer,iForAI,jForAI,dummyptr);
                                        HitBotRight(FirstPlayer,iForAI,jForAI,dummyptr);
                                    }
                                if(iForAI == 10 && jForAI != 1 && jForAI != 10)
                                    {
                                        HitShip(HitsOfAI,iForAI-1,jForAI);
                                        HitTopLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                                        HitBotLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                                    }
                                if(jForAI == 1 && iForAI != 1 && iForAI != 10)
                                    {
                                        HitShip(HitsOfAI,iForAI-1,jForAI);
                                        HitBot(FirstPlayer,iForAI,jForAI,dummyptr);
                                    }
                                if(jForAI == 10 && iForAI != 1 && iForAI != 10)
                                    {
                                        HitShip(HitsOfAI,iForAI-1,jForAI);
                                        HitTop(FirstPlayer,iForAI,jForAI,dummyptr);
                                    }
                                iForAI -= 1;
                                goto Switchlabel;
                            }
                    }
                    else
                    {
                        skiprand = 1;
                        goto BackHitLable;
                    }

                }
                if(bot)
                {
                    if(Check(FirstPlayer, iForAI, jForAI+1,bufferAI))                          //if hits
                    {
                        FirstPlayer = HitBot(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot != 1)
                        {
                            Missed(HitsOfAI,iForAI,jForAI+1);
                            HitShipAI = 0;
                            AIMissed = 0;
                            AIHit = 0;
                            goto Switchlabel;
                        }
                        if(*HitOrNot == 1)
                        {
                            if(iForAI != 1 && iForAI != 10 && jForAI != 1 && jForAI != 10 )
                            {
                                HitShip(HitsOfAI,iForAI,jForAI+1);
                                HitRight(FirstPlayer,iForAI,jForAI,dummyptr);
                                HitLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            if(iForAI == 1 && jForAI != 1 && jForAI != 10)
                            {
                                
                                HitShip(HitsOfAI,iForAI,jForAI+1);
                                HitBotRight(FirstPlayer,iForAI,jForAI,dummyptr);
                                
                            }
                            if(iForAI == 10 && jForAI != 1 && jForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI,jForAI+1);
                                HitBotLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            if(jForAI == 1 && iForAI != 1 && iForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI,jForAI+1);
                                HitBotLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                                HitBotRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            if(jForAI == 10 && iForAI != 1 && iForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI,jForAI+1);
                                HitTopLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                                HitTopRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            }

                        }

                        jForAI += 1;
                        goto Switchlabel;
                    }
                    else
                    {
                        skiprand = 1;
                        goto BackHitLable;
                    }
                }
                if(top)
                {
                    if(Check(FirstPlayer, iForAI, jForAI-1,bufferAI))                          //if hits
                    {
                        FirstPlayer = HitTop(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot != 1)
                        {
                            Missed(HitsOfAI,iForAI,jForAI-1);
                            HitShipAI = 0;
                            AIMissed = 0;
                            AIHit = 0;
                            goto Switchlabel;
                        }
                        if(*HitOrNot == 1)
                        {
                            if(iForAI != 1 && iForAI != 10 && jForAI != 1 && jForAI != 10 )
                            {
                                HitShip(HitsOfAI,iForAI,jForAI-1);
                                HitRight(FirstPlayer,iForAI,jForAI,dummyptr);
                                HitLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            if(iForAI == 1 && jForAI != 1 && jForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI,jForAI-1);
                                HitLeft(FirstPlayer,iForAI,jForAI,dummyptr);
        
                            }
                            if(iForAI == 10 && jForAI != 1 && jForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI,jForAI-1);
                                HitRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            if(jForAI == 1 && iForAI != 1 && iForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI,jForAI-1);
                                HitBotLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                                HitBotRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                            if(jForAI == 10 && iForAI != 1 && iForAI != 10)
                            {
                                HitShip(HitsOfAI,iForAI,jForAI-1);
                                HitTopLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                                HitTopRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            }
                        }
                        jForAI -= 1;
                        goto Switchlabel;
                    }
                    else
                    {
                        skiprand = 1;
                        goto BackHitLable;
                    }
                }
            }
            if(AIHit == 1)                          //after 1 random hit
            {
                if(iForAI!= 10 && jForAI != 10 && iForAI != 1 && jForAI != 1)                  //if in the middle of the board
                {
                    if (AIMissed == 0)
                    {
            
                        FirstPlayer = HitBot(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 10)                           //if AI hits twise
                        {
                            HitShip(HitsOfAI,iForAI,jForAI+1);
                            HitLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitTopRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitTopLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                            bot = 1;
                            HitShipAI++;
                            jForAI +=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI+1);
                            goto Switchlabel;
                        }

                    }
                    if(AIMissed == 1)
                    {
                        FirstPlayer = HitTop(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 1)
                        {
                            HitShip(HitsOfAI,iForAI,jForAI-1);
                            HitLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitBotRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitBotLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                            top = 1;
                            HitShipAI++;
                            jForAI -=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            HitShip(HitsOfAI,iForAI,jForAI-1);
                            goto Switchlabel;
                        }

                    }
                    if(AIMissed == 2)
                    {
                        FirstPlayer = HitLeft(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 1)
                        {
                            HitShip(HitsOfAI,iForAI-1,jForAI);
                            HitTop(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitBot(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitTopRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitBotRight(FirstPlayer,iForAI,jForAI,dummyptr);
                            left = 1;
                            HitShipAI++;
                            iForAI -=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI-1,jForAI);
                            goto Switchlabel;
                        }
                    }
                    if(AIMissed == 3)
                    {
                        FirstPlayer = HitRight(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 10)
                        {
                            HitShip(HitsOfAI,iForAI+1,jForAI);
                            HitTop(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitBot(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitTopLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                            HitBotLeft(FirstPlayer,iForAI,jForAI,dummyptr);
                            right = 1;
                            HitShipAI++;
                            iForAI +=1;
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                            
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI+1,jForAI);
                            AIMissed = 0;
                            AIHit = 0;
                            goto Switchlabel;
                        }
                    }

                }
                if(iForAI == 10 && jForAI == 10)                                              //if in the bot right corner
                {
                    if(AIMissed == 0)
                    {
                        FirstPlayer = HitTop(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 1)
                        {
                            HitShip(HitsOfAI,iForAI,jForAI-1);
                            HitTopLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            top = 1;
                            HitShipAI++;
                            jForAI -=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI-1);
                            HitTopLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            goto Switchlabel;
                        }

                    }
                    if(AIMissed == 1)
                    {
                        FirstPlayer = HitLeft(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 1)
                        {
                            HitShip(HitsOfAI,iForAI-1,jForAI);
                            HitTopLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            left = 1;
                            HitShipAI++;
                            iForAI -=1;
                            AIMissed = 0;
                            AIHit = 0;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI-1);
                            AIMissed = 0;
                            AIHit = 0;
                            goto Switchlabel;
                        }
                    }
                    
                }
                if(iForAI == 1 && jForAI == 1)                                                //if in the top left corner
                {
                    if (AIMissed == 0)
                    {
                        FirstPlayer = HitBot(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 10)
                        {
                            HitShip(HitsOfAI,iForAI,jForAI+1);
                            HitBotRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            bot = 1;
                            HitShipAI++;
                            jForAI +=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI+1);
                            HitBotRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            goto Switchlabel;
                        }
                    }
                    if(AIMissed == 1)
                    {
                        FirstPlayer = HitRight(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 10)
                        {
                            HitShip(HitsOfAI,iForAI+1,jForAI);
                            HitBotRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            right = 1;
                            HitShipAI++;
                            AIHit = 0;
                            AIMissed = 0;
                            iForAI +=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI+1,jForAI);
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }
                    }
                    
                }
                if(iForAI == 1 && jForAI == 10)                                               //if in the bot left corner
                {
                    if (AIMissed == 0)
                    {
                        FirstPlayer = HitTop(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 1)
                        {
                            HitShip(HitsOfAI,iForAI,jForAI-1);
                            HitTopLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            right = 1;
                            HitShipAI++;
                            jForAI -=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI-1);
                            goto Switchlabel;
                        }
                    }
                    if(AIMissed == 1)
                    {
                        
                        FirstPlayer = HitRight(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 10)
                        {
                            HitShip(HitsOfAI,iForAI+1,jForAI);
                            right = 1;
                            HitShipAI++;
                            iForAI +=1;
                            AIMissed = 0;
                            AIHit = 0;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI+1,jForAI);
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }
                    }
                    
                }
                if(iForAI == 10 && jForAI == 1)                                               //if in the top right corner
                {
                    if (AIMissed == 0)
                    {
                        FirstPlayer = HitLeft(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 1)
                        {
                            HitShip(HitsOfAI,iForAI-1,jForAI);
                            HitBotRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            left = 1;
                            HitShipAI++;
                            iForAI -=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI-1,jForAI);
                            goto Switchlabel;
                        }
                        
                    }
                    if(AIMissed == 1)
                    {
                        FirstPlayer = HitBot(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 10)
                        {
                            HitShip(HitsOfAI,iForAI,jForAI+1);
                            bot = 1;
                            HitShipAI++;
                            AIHit = 0;
                            AIMissed = 0;
                            jForAI +=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI+1);
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }
                    }
                    
                }
                if(iForAI == 10 && jForAI != 1 && jForAI != 10)
                {
                    if (AIMissed == 0)
                    {
                        FirstPlayer = HitBot(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 10)
                        {
                            //HitBotRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitBotLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitShip(HitsOfAI,iForAI,jForAI+1);
                            bot = 1;
                            HitShipAI++;
                            jForAI +=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI+1);
                            goto Switchlabel;
                        }
                    }
                    if(AIMissed == 1)
                    {
                        FirstPlayer = HitLeft(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 1)
                        {
                            HitBotLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitTopLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitShip(HitsOfAI,iForAI-1,jForAI);
                            left = 1;
                            HitShipAI++;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI-1,jForAI);
                            goto Switchlabel;
                        }
                    }
                    if(AIMissed == 2)
                    {
                        FirstPlayer = HitTop(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 10)
                        {
                            //HitTopRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitTopLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitShip(HitsOfAI,iForAI,jForAI-1);
                            top = 1;
                            HitShipAI++;
                            jForAI -=1;
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI-1);
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }

                    
                }
                }
                if(jForAI == 10 && iForAI != 1 && iForAI != 10)
                {
                    if(AIMissed == 0)
                    {
                        FirstPlayer = HitTop(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 10)
                        {
                
                            HitTopRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitTopLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitShip(HitsOfAI,iForAI,jForAI+1);
                            bot = 1;
                            HitShipAI++;
                            jForAI +=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI+1);
                            goto Switchlabel;
                        }

                    }
                    if(AIMissed == 1)
                    {
                        FirstPlayer = HitLeft(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 1)
                        {
                            HitShip(HitsOfAI,iForAI-1,jForAI);
                            HitTopLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            left = 1;
                            HitShipAI++;
                            iForAI -=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI-1,jForAI);
                            goto Switchlabel;
                        }

                    }
                    if(AIMissed == 2)
                    {
                        FirstPlayer = HitRight(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 10)
                        {
                            HitShip(HitsOfAI,iForAI+1,jForAI);
                            HitTopRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            right = 1;
                            HitShipAI++;
                            iForAI +=1;
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI+1,jForAI);
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }
                    }
                }
                if(iForAI == 1 && jForAI != 1 && jForAI != 10)
                {
                    if (AIMissed == 0)
                    {
                        FirstPlayer = HitBot(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 10)
                        {
                            HitShip(HitsOfAI,iForAI,jForAI+1);
                            HitBotRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitTopRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            bot = 1;
                            HitShipAI++;
                            jForAI +=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI+1);
                            goto Switchlabel;
                        }
                    }
                    if(AIMissed == 1)
                    {
                        FirstPlayer = HitTop(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 1)
                        {
                            HitShip(HitsOfAI,iForAI,jForAI-1);
                            HitTopRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            top = 1;
                            HitShipAI++;
                            jForAI -=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI-1);
                            goto Switchlabel;
                        }
                    }
                    if(AIMissed == 2)
                    {
                        FirstPlayer = HitRight(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 10)
                        {
                            HitShip(HitsOfAI,iForAI+1,jForAI);
                            HitTopRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitBotRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            right = 1;
                            HitShipAI++;
                            iForAI +=1;
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }
                        else
                        {
                            HitShip(HitsOfAI,iForAI+1,jForAI);
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }
                    }
                }
                if(jForAI == 1 && iForAI != 1 && iForAI != 10)
                {
                    if(AIMissed == 0)
                    {
                        FirstPlayer = HitBot(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && jForAI != 10)
                        {
                            HitShip(HitsOfAI,iForAI,jForAI+1);
                            HitBotLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            HitBotRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            bot = 1;
                            HitShipAI++;
                            jForAI +=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI,jForAI+1);
                            goto Switchlabel;
                        }

                        
                    }
                    if(AIMissed == 1)
                    {
                        FirstPlayer = HitLeft(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 1)
                        {
                            HitShip(HitsOfAI,iForAI-1,jForAI);
                            HitBotLeft(FirstPlayer,iForAI, jForAI,dummyptr);
                            left = 1;
                            HitShipAI++;
                            iForAI -=1;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI-1,jForAI);
                            goto Switchlabel;
                        }

                    }
                    if(AIMissed == 2)
                    {
                        FirstPlayer = HitRight(FirstPlayer,iForAI,jForAI,HitOrNot);
                        if(*HitOrNot == 1 && iForAI != 10)
                        {
                            HitShip(HitsOfAI,iForAI+1,jForAI);
                            HitBotRight(FirstPlayer,iForAI, jForAI,dummyptr);
                            right = 1;
                            HitShipAI++;
                            iForAI +=1;
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }
                        else
                        {
                            Missed(HitsOfAI,iForAI+1,jForAI);
                            AIHit = 0;
                            AIMissed = 0;
                            goto Switchlabel;
                        }
                    }
                }
            }
randLable:  if(!skiprand)
            {
                do
                {
                i =  rand();
                while(i > 10)
                {
                    i = i%10 + 1;
                    if(i == 0)
                        i = 1;
                }
                j =  rand();
                while(j > 10)
                {
                    j = j%10 + 1;
                    if(i == 0)
                        i = 1;
                }
                strcpy(bufferAI,"x");
            }while(!Check(FirstPlayer,i,j,bufferAI));
                FirstPlayer = PlayerMove(FirstPlayer,i,j,HitOrNot);
                if(*HitOrNot == 1)                                                          //If hit 1 time
                {
                    if(i != 10 && i != 1 && j != 10 && j != 1)
                    {
                        HitShip(HitsOfAI,i,j);
                        HitTopLeft(FirstPlayer,i,j,dummyptr);
                        HitTopRight(FirstPlayer,i,j,dummyptr);
                        HitBotRight(FirstPlayer,i,j,dummyptr);
                        HitBotLeft(FirstPlayer,i,j,dummyptr);
                    }
                
                    if(i == 1 && j == 1)
                    {
                        HitShip(HitsOfAI,i,j);
                        HitBotRight(FirstPlayer,i,j,dummyptr);
                    }
                    if(i == 1 && j == 10)
                    {
                        HitShip(HitsOfAI,i,j);
                        HitTopRight(FirstPlayer,i,j,dummyptr);
                    }
                    if(i == 10 && j == 1)
                    {
                        HitShip(HitsOfAI,i,j);
                        HitBotLeft(FirstPlayer,i,j,dummyptr);
                    }
                    if(i == 10 && j == 10)
                    {
                        HitShip(HitsOfAI,i,j);
                        HitTopLeft(FirstPlayer,i,j,dummyptr);
                    }
                }
                else
                    Missed(HitsOfAI,i,j);
                
                skiprand = 0;
                goto Switchlabel;
            }
            else
                if(Check(FirstPlayer,iForAI,jForAI, bufferAI))
                {
                    FirstPlayer = PlayerMove(FirstPlayer,iForAI,jForAI,HitOrNot);
                    if(*HitOrNot == 1)                                                          //If hit 1 time
                    {
                        if(i != 10 && i != 1 && j != 10 && j != 1)
                        {
                            HitShip(HitsOfAI,i,j);
                            HitTopLeft(FirstPlayer,i,j,dummyptr);
                            HitTopRight(FirstPlayer,i,j,dummyptr);
                            HitBotRight(FirstPlayer,i,j,dummyptr);
                            HitBotLeft(FirstPlayer,i,j,dummyptr);
                        }
                        
                        if(i == 1 && j == 1)
                        {
                            HitShip(HitsOfAI,i,j);
                            HitBotRight(FirstPlayer,i,j,dummyptr);
                        }
                        if(i == 1 && j == 10)
                        {
                            HitShip(HitsOfAI,i,j);
                            HitTopRight(FirstPlayer,i,j,dummyptr);
                        }
                        if(i == 10 && j == 1)
                        {
                            HitShip(HitsOfAI,i,j);
                            HitBotLeft(FirstPlayer,i,j,dummyptr);
                        }
                        if(i == 10 && j == 10)
                        {
                            HitShip(HitsOfAI,i,j);
                            HitTopLeft(FirstPlayer,i,j,dummyptr);
                        }
                    }
                    else
                        Missed(HitsOfAI,i,j);
                }
                else
                    skiprand = 0;
                    goto randLable;
BackHitLable:
            if(skiprand)
            {
                
                if(top)
                {
                    while(!Check(FirstPlayer,jForAI,iForAI,bufferAI) && jForAI > 2)
                        jForAI--;
                    if(jForAI < 1)
                    {
                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        goto Switchlabel;
                    }
                    top = 0;
                    AIHit = 0;
                    skiprand = 1;
                    goto Switchlabel;
                }
                if(bot)
                {
                    while(!Check(FirstPlayer,jForAI,iForAI,bufferAI) && jForAI < 9)
                        jForAI++;
                    if(jForAI > 10)
                    {
                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        goto Switchlabel;
                    }
                    bot = 0;
                    AIHit = 0;
                    skiprand = 1;
                    goto Switchlabel;

                }
                if(left)
                {
                    while(!Check(FirstPlayer,jForAI,iForAI,bufferAI) && iForAI < 9)
                        iForAI++;
                    if(iForAI > 10)
                    {
                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        skiprand = 1;
                        goto Switchlabel;
                    }
                    left = 0;
                    AIHit = 0;
                    skiprand = 0;
                    goto Switchlabel;

                }
                if(right)
                {
                    while(!Check(FirstPlayer,jForAI,iForAI,bufferAI) && iForAI > 2)
                        iForAI--;
                    if(iForAI < 1)
                    {
                        HitShipAI = 0;
                        AIMissed = 0;
                        AIHit = 0;
                        skiprand = 1;
                        goto Switchlabel;
                    }
                    right = 0;
                    skiprand = 0;
                    goto Switchlabel;

                }

                
                HitShipAI = 0;
                AIMissed = 0;
                AIHit = 0;
                skiprand = 0;
            }
            
            
Switchlabel:
        switch (*HitOrNot) {
                case 1:
                    printf("Hit!\n\n");
                    MoveResoultForAI = 1;
                    if(AIHit == 0)
                    {
                        iForAI = i;
                        jForAI = j;
                    }
                    AIMissed = 0;
                    AIHit = 1;
                    HitShipAI++;
                
                    printf("                     Computer Hits!\n\n");
                    //printBoard(HitsOfAI);
                    printBoard(FirstPlayer);
                    break;
                case 0:
                    printf("Missed!\n\n");
                    MoveResoultForAI = 0;
                    printf("                     Computer Hits!\n\n");
                    //printBoard(HitsOfAI);
                    printBoard(FirstPlayer);
                    AIMissed++;
                    break;
                default:
                    MoveResoultForAI = 0;
                    AIMissed++;
                    printf("                     Computer Hits!\n\n");
                    //printBoard(HitsOfAI);
                    printBoard(FirstPlayer);
                    printf("Missed!\n\n");
                    break;
            }

            if(ScanIfShipsLeft(FirstPlayer))
            {
                printf("Computer won!\n");
                printf("%d",countForAI);
                strcpy(buffer,"End");
                continue;
            }
            countForAI++;
        }
        
        while(strcmp(buffer,"Exit") != 0)
        {
            printf("To see boards type<Print_Boards>\nTo exit game type <Exit>\n");
            scanf("%s",buffer);
            if(strcmp(buffer,"Exit") == 0)
                return;
            if(!strcmp(buffer,"Print_Boards"))
            {
                printf("\n                  Your board\n");
                printBoard(FirstPlayer);
                filePrintBoard(FirstPlayer,out);
                printf("\n                  Computer's board\n");
                printBoard(SecondPlayer);
                filePrintBoard(SecondPlayer,out);
            }
        }
        return;
    }
    return;
}


Board HitTop(Board One,int i,int j,int *Hit)
{
    int hit = -1;
    int *hitOrNot = &hit;
    One = PlayerMove(One,i,j-1,hitOrNot);
    *Hit = hit;
    return One;
}
Board HitBot(Board One,int i,int j,int *Hit)
{
    int hit = -1;
    int *hitOrNot = &hit;
    One = PlayerMove(One,i,j+1,hitOrNot);
    
    *Hit = hit;
    return One;
}
Board HitLeft(Board One,int i,int j,int *Hit)
{
    int hit = -1;
    int *hitOrNot = &hit;
    One = PlayerMove(One,i-1,j,hitOrNot);
    *Hit = hit;
    return One;
}
Board HitRight(Board One,int i,int j,int *Hit)
{
    int hit = -1;
    int *hitOrNot = &hit;
    One = PlayerMove(One,i+1,j,hitOrNot);
    *Hit = hit;
    return One;
}
Board HitBotRight(Board One,int i,int j,int *Hit)
{
    int hit = -1;
    int *hitOrNot = &hit;
    One = PlayerMove(One,i+1,j+1,hitOrNot);
    *Hit = hit;
    return One;
}
Board HitBotLeft(Board One,int i,int j,int *Hit)
{
    int hit = -1;
    int *hitOrNot = &hit;
    One = PlayerMove(One,i-1,j+1,hitOrNot);
    *Hit = hit;
    return One;
}
Board HitTopRight(Board One,int i,int j,int *Hit)
{
    int hit = -1;
    int *hitOrNot = &hit;
    One = PlayerMove(One,i+1,j-1,hitOrNot);
    *Hit = hit;
    return One;
}
Board HitTopLeft(Board One,int i,int j,int *Hit)
{
    int hit = -1;
    int *hitOrNot = &hit;
    One = PlayerMove(One,i-1,j-1,hitOrNot);
    *Hit = hit;
    return One;
}
