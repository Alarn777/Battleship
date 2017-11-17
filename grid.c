//
//  grid.c
//  Game
//
//  Created by Michael Rokitko on 5/26/17.
//  Copyright © 2017 misha rok. All rights reserved.
//

#include "grid.h"
struct grid{
    int height;
    int width;
    char tableSymbol[7];
}grid;
struct PlayerBoard{
    Section Board[11][11];
};
enum Binary{
    True,False
};
Section CreateSect(void)
{
    Section New;
    New = (Section)malloc(sizeof(grid));
    checkmemory(&New);
    return New;
}
Board Create(void)        //creates blank board for player
{
    int i = -1,j = -1;
    Board New = NULL;
    New = (Board)malloc(sizeof(struct PlayerBoard));
    checkmemory(New->Board[i][j]);
    clearBoard(New);
    for (i = 0,j = 0;j < 11 && i < 11;)
    {
        for(;i == 0 && j == 0;)
        {
         if(i == 0 && j == 0)
         {
             New->Board[i][j] = (Section)malloc(sizeof(grid));
             checkmemory(New->Board[i][j]);
             strncpy(New->Board[i][j]->tableSymbol," ",2);
             New->Board[i][j]->height = 0;
             New->Board[i][j]->width = 0;
             i++;
         }
            char AtoZ = 65;
            char Number = 49;
            while(i < 11)
            {
            New->Board[i][j] = (Section)malloc(sizeof(grid));
            checkmemory(New->Board[i][j]);
            strncpy(New->Board[i][j]->tableSymbol,&AtoZ,1);
            New->Board[i][j]->tableSymbol[1] = '\0';
            New->Board[i][j]->height = j;
            New->Board[i][j]->width = i;
            i++;
            AtoZ++;                               //put A-J above our table
            }
            j++;                                   //skip the start
            
            for(i = 0;j < 11;j++,Number++)
            {
                if(j == 10)
            {
                
                New->Board[i][j] = (Section)malloc(sizeof(grid));
                checkmemory(New->Board[i][j]);
                strncpy(New->Board[i][j]->tableSymbol,"10",3);
                New->Board[i][j]->height = j;
                New->Board[i][j]->width = i;
                j++;
                continue;
            }
                New->Board[i][j] = (Section)malloc(sizeof(grid));
                checkmemory(New->Board[i][j]);
                strncpy(New->Board[i][j]->tableSymbol,&Number,1);
                New->Board[i][j]->tableSymbol[1] = '\0';
                New->Board[i][j]->height = j;
                New->Board[i][j]->width = i;
                }
            }
        }
        for(j = 1;j < 11;)    //put cubes inside the grid
        {
            i = 1;
            for(; i< 11 ;i++)
            {
                New->Board[i][j] = (Section)malloc(sizeof(grid));
                checkmemory(New->Board[i][j]);
                strncpy(New->Board[i][j]->tableSymbol,"\u25C7",5);
                New->Board[i][j]->height = j;
                New->Board[i][j]->width = i;
            }
            j++;
        }
    return New;
}


void printBoard(Board OneToPrint)
{
    int i = 0,j = 0;
    for(j = 0;j<11;j++)
    {
        for(i = 0;i<11;i++)
        {
            if(j == 10 && i == 0)
            {
                printf("%s",OneToPrint->Board[i][j]->tableSymbol);
                i++;
            }
            printf("%s ",OneToPrint->Board[i][j]->tableSymbol);
            
        }
     printf("\n");
    }
    
}
void filePrintBoard(Board OneToPrint,FILE *out)
{
    int i = 0,j = 0;
    for(j = 0;j<11;j++)
    {
        for(i = 0;i<11;i++)
        {
            if(j == 10 && i == 0)
            {
                fprintf(out,"%s",OneToPrint->Board[i][j]->tableSymbol);
                i++;
            }
            fprintf(out,"%s ",OneToPrint->Board[i][j]->tableSymbol);
            
        }
        fprintf(out,"\n");
    }
    
}

void clearBoard(Board One)
{
    int i = 0,j = 0;
    for(j = 0;j<11;j++)
        for(i = 0;i<11;i++)
            One->Board[i][j] = NULL;
}
void destroyBoard(Board OneToDestroy)
{
    int i = 0,j = 0;
    for(j = 0;j<11;j++)
        for(i = 0;i<11;i++)
            free(OneToDestroy->Board[i][j]);
    
    free(OneToDestroy);
}
Board fillSqare(Board One,int i, int j)
{
    strcpy(One->Board[i][j]->tableSymbol,"\u25C6");
    return One;
}
Board PlayerMove(Board Enemy,int i, int j,int *hitOrNot)
{
    if(!strcmp(Enemy->Board[i][j]->tableSymbol,"x"))    //if there is a hit already in the section
       {
            *hitOrNot = -1;
            return Enemy;
       }
    if(!strcmp(Enemy->Board[i][j]->tableSymbol,"\u25C6")) //if there is a ship in the section
    {
        strncpy(Enemy->Board[i][j]->tableSymbol,"x",2);
        *hitOrNot = 1;
    }
    else
    {
        strncpy(Enemy->Board[i][j]->tableSymbol,"x",2);
        *hitOrNot = 0;
    }
    return Enemy;
}

int checkPositioning(Board One,int i,int j,int iMax,int jMax)
{
        if (i == iMax)
        {
           for(;j<=jMax;j++)
           {
               if(i == 10 && j == 10 )
               {
                   if(strcmp(One->Board[i][j]->tableSymbol,"\u25C6"));    // check i;j
                   else
                       return False;
                   if(strcmp(One->Board[i][j-1]->tableSymbol,"\u25C6"));  //check i;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j-1]->tableSymbol,"\u25C6")); //check i-1;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j]->tableSymbol,"\u25C6"));   //check i-1;j
                   else
                       return False;
                if(i == 10 && j == 10 && iMax == 10 && jMax == 10)
                    return True;
               }
               if(i == 10)
               {
                   if(strcmp(One->Board[i][j]->tableSymbol,"\u25C6"));    // check i;j
                   else
                       return False;
                   if(strcmp(One->Board[i][j+1]->tableSymbol,"\u25C6"));  //check i;j+1
                   else
                       return False;
                   if(strcmp(One->Board[i][j-1]->tableSymbol,"\u25C6"));  //check i;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j-1]->tableSymbol,"\u25C6")); //check i-1;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j]->tableSymbol,"\u25C6"));   //check i-1;j
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j+1]->tableSymbol,"\u25C6"));   //check i-1;j+1
                   else
                       return False;
               }
               if(j == 10)
               {
                   if(strcmp(One->Board[i][j]->tableSymbol,"\u25C6"));    // check i;j
                   else
                       return False;
                   if(strcmp(One->Board[i+1][j-1]->tableSymbol,"\u25C6"));  //check i+1;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i][j-1]->tableSymbol,"\u25C6"));  //check i;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i+1][j]->tableSymbol,"\u25C6")); //check i+1;j
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j]->tableSymbol,"\u25C6"));   //check i-1;j
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j-1]->tableSymbol,"\u25C6"));   //check i-1;j-1
                   else
                       return False;
               }
               if(i != 10 && j != 10)
               {
               if(strcmp(One->Board[i][j]->tableSymbol,"\u25C6"));    // check i;j
               else
                   return False;
               if(strcmp(One->Board[i+1][j+1]->tableSymbol,"\u25C6"));  //check i+1;j+1
               else
                   return False;
               if(strcmp(One->Board[i][j-1]->tableSymbol,"\u25C6"));  //check i;j-1
               else
                   return False;
               if(strcmp(One->Board[i+1][j]->tableSymbol,"\u25C6")); //check i+1;j
               else
                   return False;
               if(strcmp(One->Board[i-1][j]->tableSymbol,"\u25C6"));   //check i-1;j
               else
                   return False;
               if(strcmp(One->Board[i-1][j-1]->tableSymbol,"\u25C6"));   //check i-1;j-1
               else
                   return False;
               if(strcmp(One->Board[i-1][j+1]->tableSymbol,"\u25C6"));   //check i-1;j+1
               else
                   return False;
               if(strcmp(One->Board[i][j+1]->tableSymbol,"\u25C6"));   //check i;j+1
               else
                   return False;
               if(strcmp(One->Board[i+1][j-1]->tableSymbol,"\u25C6"));   //check i+1;j-1
               else
                   return False;
               }
              
           }
        }
       if(j == jMax)
       {
           for(;i<=iMax;i++)
           {
               if(i == 10 && j == 10)
               {
                   if(strcmp(One->Board[i][j]->tableSymbol,"\u25C6"));    // check i;j
                   else
                       return False;
                   if(strcmp(One->Board[i][j-1]->tableSymbol,"\u25C6"));  //check i;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j-1]->tableSymbol,"\u25C6")); //check i-1;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j]->tableSymbol,"\u25C6"));   //check i-1;j
                   else
                       return False;
                   
                   
               }
               if(i == 10 && j != 10)
               {
                   if(strcmp(One->Board[i][j]->tableSymbol,"\u25C6"));    // check i;j
                   else
                       return False;
                   if(strcmp(One->Board[i][j+1]->tableSymbol,"\u25C6"));  //check i;j+1
                   else
                       return False;
                   if(strcmp(One->Board[i][j-1]->tableSymbol,"\u25C6"));  //check i;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j-1]->tableSymbol,"\u25C6")); //check i-1;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j]->tableSymbol,"\u25C6"));   //check i-1;j
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j+1]->tableSymbol,"\u25C6"));   //check i-1;j+1
                   else
                       return False;
                   
                
               }
               if(j == 10 && i != 10)
               {
                   if(strcmp(One->Board[i][j]->tableSymbol,"\u25C6"));    // check i;j
                   else
                       return False;
                   if(strcmp(One->Board[i+1][j]->tableSymbol,"\u25C6")); //check i+1;j
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j]->tableSymbol,"\u25C6"));   //check i-1;j
                   else
                       return False;
                   if(strcmp(One->Board[i][j-1]->tableSymbol,"\u25C6"));  //check i;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i-1][j-1]->tableSymbol,"\u25C6"));   //check i-1;j-1
                   else
                       return False;
                   if(strcmp(One->Board[i+1][j-1]->tableSymbol,"\u25C6"));  //check i+1;j-1
                   else
                       return False;
               }
               if(j != 10 && i != 10)
               {
               if(strcmp(One->Board[i][j]->tableSymbol,"\u25C6"));    // check i;j
               else
                   return False;
               if(strcmp(One->Board[i][j-1]->tableSymbol,"\u25C6"));  //check i;j-1
               else
                   return False;
               if(strcmp(One->Board[i][j+1]->tableSymbol,"\u25C6"));   //check i;j+1
               else
                   return False;
               if(strcmp(One->Board[i+1][j+1]->tableSymbol,"\u25C6"));  //check i+1;j+1
               else
                   return False;
               if(strcmp(One->Board[i+1][j-1]->tableSymbol,"\u25C6"));  //check i+1;j-1
               else
                   return False;
               if(strcmp(One->Board[i+1][j]->tableSymbol,"\u25C6"));    //check i+1;j
               else
                   return False;
               if(strcmp(One->Board[i-1][j]->tableSymbol,"\u25C6"));   //check i-1;j
               else
                   return False;
               if(strcmp(One->Board[i-1][j-1]->tableSymbol,"\u25C6"));   //check i-1;j-1
               else
                   return False;
               if(strcmp(One->Board[i-1][j+1]->tableSymbol,"\u25C6"));   //check i-1;j+1
               else
                   return False;
               }
           }
       }
   
    return True;
}

int ScanIfShipsLeft(Board One)
{
    int i = 0,j = 0;
    for(j = 0;j<11;j++)
        for(i = 0;i<11;i++)
            if((strcmp(One->Board[i][j]->tableSymbol,"\u25C6")) == 0)
                    return True;
    
    return False;
}

int Check(Board One,int i, int j, char *value)
{
    if(strcmp(value,One->Board[i][j]->tableSymbol))
        return 1;
    else
        return 0;
}

Board HitShip(Board One,int i, int j)
{
    strcpy(One->Board[i][j]->tableSymbol,"\u25CF");
    return One;
}

Board Missed(Board One,int i, int j)
{
    strcpy(One->Board[i][j]->tableSymbol,"x");
    return One;
}

