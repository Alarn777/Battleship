//
//  gameActions.c
//  Game
//
//  Created by Michael Rokitko on 5/27/17.
//  Copyright © 2017 misha rok. All rights reserved.
//

#include "gameActions.h"

Board AddShip(Board OneToAddTo,char* action,int* AddedOrNot,int *ShipSize)   //adds 1 ship to board
{
    int i = -1,iMax = -1,j = -1,jMax = -1,check = -1;
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
    if((j != jMax) && (i != iMax))                      //checking your input
       {
       printf("Not A valid position for the ship\n");
           return OneToAddTo;
       }
    if(*ShipSize != -1)
    {
        if(*ShipSize == 0)
        {
            if(!((jMax - j) == *ShipSize && (iMax - i) == *ShipSize))
            {
                printf("Not A valid size for the ship\n");
                return OneToAddTo;
            }
        }
        if(*ShipSize != 0)
        {
            if(!(((jMax - j) == *ShipSize) || ((iMax - i) == *ShipSize)))
            {
            printf("Not A valid size for the ship\n");
            return OneToAddTo;
            }
        }
    }
         
    check = checkPositioning(OneToAddTo,i,j,iMax,jMax);
    if(check != 0)
    {
        printf("Not A valid position for the ship\n");
        return OneToAddTo;
    }
    if (i == iMax)
    {
        for(;j<=jMax;j++)
        {
        fillSqare(OneToAddTo,i,j);
        }
    }
    if(j == jMax)
    {
        for(;i<=iMax;i++)
        {
            fillSqare(OneToAddTo,i,j);
        }
    }
    *AddedOrNot -= 1;
    return OneToAddTo;
}
Board Ships(Board One)              //interactive game ships adding
{
    int Shipcount = 0;
    int *AddOrNot = &Shipcount;
    char buffer[256];
    int ShipSize = -1;
    int *PtrSize = &ShipSize;
    for(*AddOrNot = 4;*AddOrNot;)                       //Adding 4 [] ships
    {
        printf("Enter coordinates <[][]-[][]> for Single-Decker ship, You have %d left\n",*AddOrNot);
        scanf("%s",buffer);
        ShipSize = 0;
        One = AddShip(One,buffer,AddOrNot,PtrSize);
    }
    printBoard(One);
    for(*AddOrNot = 3;*AddOrNot;)                       //Adding 3 [][] ships
    {
        printf("Enter coordinates <[][]-[][]> for Double-Decker ship, You have %d left\n",*AddOrNot);
        scanf("%s",buffer);
        ShipSize = 1;
        One = AddShip(One,buffer,AddOrNot,PtrSize);
    }
    printBoard(One);
    for(*AddOrNot = 2;*AddOrNot;)                       //Adding 2 [][][] ships
    {
        printf("Enter coordinates <[][]-[][]> for Triple-Decker ship, You have %d left\n",*AddOrNot);
        scanf("%s",buffer);
        ShipSize = 2;
        One = AddShip(One,buffer,AddOrNot,PtrSize);
    }
    printBoard(One);
    for(*AddOrNot = 1;*AddOrNot;)                       //Adding 1 [][][][] ship
    {
        printf("Enter coordinates <[][]-[][]> for Quadruple-Decker ship, You have %d left\n",*AddOrNot);
        scanf("%s",buffer);
        ShipSize = 3;
        One = AddShip(One,buffer,AddOrNot,PtrSize);
    }
    
    return One;
}

Board ShipsFromFile(Board One,FILE* file)
{
    char buffer[256];
    int falseValue = 100;
    int *falsePoint = &falseValue;
    int falseSize = -1;
    int *falseSuizePoint = &falseSize;
    while ((fgets(buffer, sizeof(buffer),file))!= NULL)
    {
        if(*buffer == '#')
            continue;
        One = AddShip(One,buffer,falsePoint,falseSuizePoint);
    }
    return One;
}
void MoveFromFile(Board FirstPlayer,Board SecondPlayer,FILE* simulation,int *HitOrNot,FILE *out)
{
    char bufferHuge[2048];
    char *PtrToMainBuffer = bufferHuge;
    char buffer[256];
    char *ptr = buffer;
    char player[8];
    int i = -1,j = -1,count = 9;
    while ((fgets(buffer, sizeof(buffer),simulation))!= NULL)
    {
        if(*buffer == '#' || *buffer == ' ')
            continue;
        strncpy(player,buffer,7);
        player[7] = '\0';            //null termination string to avoid errors
        i = checkColomn(buffer[8]);
        for(;count;ptr++,count--);  //we increase pointer to get to the numbers
        
        if(buffer[9] == '1' && buffer[10] == '0')
                j = 10;
        else
            j = *ptr - '0';
        if(!strcmp(player,"Player1"))
            {
                PtrToMainBuffer = addtobuff(PtrToMainBuffer, buffer);
                SecondPlayer = PlayerMove(SecondPlayer,i,j,HitOrNot);
                switch (*HitOrNot) {
                    case 1:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer,"Hit\n\0");
                        break;
                    case 0:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer,"Missed\n\0");
                        break;
                    case -1:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer,"You already hit here,Choose different move\n\0");
                        break;
                                    }

                    if(ScanIfShipsLeft(SecondPlayer))
                    {
                        
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer,"Player 1 won!\n\0");
                        continue;
                    }
            }
        if(!strcmp(player,"Player2"))
            {
                PtrToMainBuffer = addtobuff(PtrToMainBuffer, buffer);
                FirstPlayer = PlayerMove(FirstPlayer,i,j,HitOrNot);
                switch (*HitOrNot) {
                    case 1:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer,"Hit\n\0");
                        break;
                    case 0:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer,"Missed\n\0");
                        break;
                    case -1:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer,"You already hit here,Choose different move\n\0");
                        break;
                }

                if(ScanIfShipsLeft(FirstPlayer))
                {
                   
                    PtrToMainBuffer = addtobuff(PtrToMainBuffer,"Player 2 won!\n\0");
                    continue;
                }

            }
        if(!strcmp(buffer,"Print_Movements\n"))
        {
            *HitOrNot = -3;
            fprintf(out,"%s",bufferHuge);
             return;
        }
        if(!strcmp(buffer,"Print_Boards\n"))
        {
            fprintf(out,"Player 1 board\n");
            filePrintBoard(FirstPlayer,out);
            fprintf(out,"Player 2 board\n");
            filePrintBoard(SecondPlayer,out);
        }
    }
        if(!strcmp(buffer,"Print_Boards"))
        {
            fprintf(out,"Player 1 board\n");
            filePrintBoard(FirstPlayer,out);
            fprintf(out,"Player 2 board\n");
            filePrintBoard(SecondPlayer,out);
            return;
        }
    return;
}
void MovesLive(Board FirstPlayer,Board SecondPlayer,int *HitOrNot,FILE *out)
{
    char buffer[256];
    char bufferHuge[4096];
    char *PtrToMainBuffer = bufferHuge;
    int i = -1,j = -1;
    strcpy(buffer,"rly?");
    printf("Any player can end the game at all given times by typing <End>\n");
    while (!ScanIfShipsLeft(FirstPlayer) && !ScanIfShipsLeft(SecondPlayer))
    {
        while(strcmp(buffer,"End") != 0)
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
                }while(!(checkColomn(buffer[0]) > 0) || buffer[3] != '\0' ||  (buffer[2] != '0' && buffer[2] != '\0'));                if(strcmp(buffer,"End") == 0)
                    continue;
                i = checkColomn(buffer[0]);
                if(buffer[1] == '1' && buffer[2] == '0')
                    j = 10;
                else
                    j = buffer[1] - '0';
                PtrToMainBuffer = addtobuff(PtrToMainBuffer,"Player 1 move is:\n\0");
                PtrToMainBuffer = addtobuff(PtrToMainBuffer, buffer);
                SecondPlayer = PlayerMove(SecondPlayer,i,j,HitOrNot);
                switch (*HitOrNot) {
                    case 1:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer," Hit\n\0");
                        printf("Hit!\n");
                        break;
                    case 0:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer," Missed!\n\0");
                        printf("Missed!\n");
                        break;
                    case -1:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer," You already hit here,Choose different move\n\0");
                        printf("You already hit here,turn is passed to player 2\n");
                        break;
                }
                if(ScanIfShipsLeft(SecondPlayer))
                {
                    PtrToMainBuffer = addtobuff(PtrToMainBuffer,"Player 1 won!\n\0");
                    printf("Player 1 won!\n");
                    strcpy(buffer,"End");
                    continue;
                }
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
                }while(!(checkColomn(buffer[0]) > 0) || buffer[3] != '\0' ||  (buffer[2] != '0' && buffer[2] != '\0'));                if(strcmp(buffer,"End") == 0)
                    continue;
                i = checkColomn(buffer[0]);
                if(buffer[1] == '1' && buffer[2] == '0')
                    j = 10;
                else
                    j = buffer[1] - '0';
                PtrToMainBuffer = addtobuff(PtrToMainBuffer,"Player 2 move is:\n\0");
                PtrToMainBuffer = addtobuff(PtrToMainBuffer, buffer);
                FirstPlayer = PlayerMove(FirstPlayer,i,j,HitOrNot);
                switch (*HitOrNot) {
                    case 1:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer," Hit\n\0");
                        printf("Hit!\n");
                        break;
                    case 0:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer," Missed\n\0");
                        printf("Missed\n!");
                        break;
                        case -1:
                        PtrToMainBuffer = addtobuff(PtrToMainBuffer," You already hit here,Choose different move\n\0");
                        printf("You already hit here,turn is passed to player 1\n");
                        break;
                }
                if(ScanIfShipsLeft(FirstPlayer))
                {
                    PtrToMainBuffer = addtobuff(PtrToMainBuffer,"Player 2 won!\n\0");
                    printf("Player 2 won!\n");
                    strcpy(buffer,"End");
                    continue;
                }
            }
        
        while(strcmp(buffer,"Exit") != 0)
        {
            printf("To see board type<Print_Boards>\nTo see moves type <Print_Movements>\nTo exit game enter <Exit>\n");
            scanf("%s",buffer);
            if(strcmp(buffer,"Exit") == 0)
                return;
            if(!strcmp(buffer,"Print_Movements"))
            {
                printf("%s",bufferHuge);
                fprintf(out,"%s",bufferHuge);
            }
            if(!strcmp(buffer,"Print_Boards"))
            {
                fprintf(out,"Player 1 board\n");
                printf("Player 1 board\n");
                printBoard(FirstPlayer);
                filePrintBoard(FirstPlayer,out);
                
                printf("Player 2 board\n");
                fprintf(out,"Player 2 board\n");
                printBoard(SecondPlayer);
                filePrintBoard(SecondPlayer,out);
            }
        }
        return;

    }
    return;
}
