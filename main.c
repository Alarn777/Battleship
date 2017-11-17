//
//  main.c
//  Game
//
//  Created by Michael Rokitko on 5/26/17.
//  Copyright © 2017 misha rok. All rights reserved.
//
#include "grid.h"
#include "gameActions.h"
#include "HelperFunctions.h"
#include "AI.h"
int main(int argc, const char * argv[])
{
    int hit = 0;
    char buffer[48];
    int *HitOrNot = &hit;
    int decision = -1;
    Board Player1 = (Board)malloc(sizeof(Board));       //creating empty board for player 1
    Player1 = Create();
    Board Player2 = (Board)malloc(sizeof(Board));
    Player2 = Create();                                 //creating empty board for player 2
    FILE *output,*PlayerFirst,*PlayerSecond,*simulation;
    output = fopen(argv[4],"w");
    PlayerFirst = fopen(argv[1],"r");
    PlayerSecond = fopen(argv[2],"r");
    simulation = fopen(argv[3],"r");
    printf("                    <Welcome to Battleship>\nFor Player VS Player game press 1\nFor file based game press 2\nFor Player VS PC game press 3\n");
    do                                                  //protection from wrong intput
     {
         scanf("%d",&decision);
         if(decision != 1 && decision != 2 && decision != 3 && decision != 4 && decision != 5 && decision != 6 && decision != 0)
             {
                 printf("Not a valid choice, please enter menu number\n\n");
                 decision = 32;
                 fgets(buffer,48,stdin);
                 continue;
             }
    
     }while(decision != 1 && decision != 2 && decision != 3);
        switch (decision)
        {
        case 1:
                printf("You have to put:\n4 \u25A2 ships\n3 \u25A2\u25A2  ships\n2 \u25A2\u25A2\u25A2 ships\n1 \u25A2\u25A2\u25A2\u25A2 ships\n----------------------------\n");
                printf("First Player filles his grid:\n");
                Player1 = Ships(Player1);
                printf("Second Player filles his grid:\n");
                Player2 = Ships(Player2);
                printf("We're all set, lets play!\n");
                MovesLive(Player1, Player2, HitOrNot, output);              // <-----all interactive game is here
                break;
        case 2:
                Player1 = ShipsFromFile(Player1,PlayerFirst);
                Player2 = ShipsFromFile(Player2,PlayerSecond);
                printf("         <Player 1 board ready>\n");
                printBoard(Player1);
                printf("         <Player 2 board ready>\n");
                printBoard(Player2);
                if (!ScanIfShipsLeft(Player1) && !ScanIfShipsLeft(Player2))     // checking for ships left on board
                    MoveFromFile(Player1,Player2,simulation,HitOrNot,output);   // <-----all FILE based game is here
                break;
        case 3:
                printf("First Player filles his grid:\n");
                //Player1 = Ships(Player1);
                Player1 = ShipsFromFile(Player1,PlayerFirst);
                printBoard(Player1);
                printf("         <Player 1 board ready>\n");
                //Player1 = ShipsFromFile(Player1,PlayerFirst);    for test only
                Player2 =  ShipPlacement(Player2);
                printf("PC filled his grid:\n");
                MovesVS_AI(Player1, Player2, output);
                break;
        }
    destroyBoard(Player1);
    destroyBoard(Player2);
    fclose(output);
    fclose(PlayerFirst);
    fclose(PlayerSecond);
    fclose(simulation);
    return 0;
}
