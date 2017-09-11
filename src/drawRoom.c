#include "readFile.h"
#include "drawRoom.h"
#include "heroMove.h"


void drawRoom(struct room **roomPtr, struct door **doorPtr, struct gold **goldPtr, struct weap **weapPtr, struct mon **monPtr, struct equip **equipPtr, struct pot **potPtr, struct hero **heroPtr, struct stair **stairPtr)
{
    //printf("IN DRAWROOM %d\n", roomPtr[0] ->col);

    int row;  //initialize variables
    int col;
    int totGold;
    int sGold;
    int bGold;
    int i;
    
    totGold = 0;
    sGold = 0;
    bGold = 0;
    
    initscr(); //initalize ncurses
    
    getmaxyx(stdscr, row, col); //get size of screen
    
     if (row < 45 || col < 86 )
    {
        printw("Screen too small. Press anything to continue"); //ensures the window size is large enough to accomodate the largest room sizes
        getch();
        endwin();
        exit(1);
    }
    
    for (i = 0; i < 6; i++)
    {
        if (i ==0)
        {           //calls printroom for each room individually passing through essential information
            printRoom(2,3,roomPtr[i]->col,roomPtr[i]->row,0,roomPtr, doorPtr, goldPtr, weapPtr, monPtr, equipPtr, potPtr, heroPtr, stairPtr);
        }
        else if (i ==1)
        {
            printRoom(2,33,roomPtr[i]->col,roomPtr[i]->row,1,roomPtr, doorPtr, goldPtr, weapPtr, monPtr, equipPtr, potPtr, heroPtr, stairPtr);
        }
        else if (i ==2)
        {
            printRoom(2,63,roomPtr[i]->col,roomPtr[i]->row,2,roomPtr, doorPtr, goldPtr, weapPtr, monPtr, equipPtr, potPtr, heroPtr, stairPtr);
        }
        else if (i ==3)
        {
            printRoom(28,3,roomPtr[i]->col,roomPtr[i]->row,3,roomPtr, doorPtr, goldPtr, weapPtr, monPtr, equipPtr, potPtr, heroPtr, stairPtr);
        }
        else if (i ==4)
        {
            printRoom(28,33,roomPtr[i]->col,roomPtr[i]->row,4,roomPtr, doorPtr, goldPtr, weapPtr, monPtr, equipPtr, potPtr, heroPtr, stairPtr);
        }
        else if (i ==5)
        {
            printRoom(28,63,roomPtr[i]->col,roomPtr[i]->row,5,roomPtr, doorPtr, goldPtr, weapPtr, monPtr, equipPtr, potPtr, heroPtr, stairPtr);
        }
    }
    
  
  //draws hallways for each individual room
        drawHall( 2,3,0, roomPtr[0]->col, roomPtr[0]->row,doorPtr);
        
        drawHall( 2,33,1, roomPtr[1]->col, roomPtr[1]->row,doorPtr);
        
        drawHall( 2,63,2, roomPtr[2]->col, roomPtr[2]->row,doorPtr);
        
        drawHall( 28,3,3, roomPtr[3]->col, roomPtr[3]->row,doorPtr);
        
        drawHall( 28,33,4, roomPtr[4]->col, roomPtr[4]->row,doorPtr);
        
        drawHall( 28,63,5, roomPtr[5]->col, roomPtr[5]->row,doorPtr);
        
        
    
    
    //call heroMove passing through parameters to obtain position of the hero
    heroMove(roomPtr, doorPtr, goldPtr, weapPtr, monPtr, equipPtr, potPtr, heroPtr, stairPtr);
    
    
    endwin(); //end ncurses
    
    bGold = getRand2(goldPtr[1]->bnumGold); //calls getRand and assignes random number to the number of gold
    sGold = getRand3(goldPtr[1]->snumGold); 
    
    totGold = sGold + bGold;
    
    printf("\nGAME STATS\nCollected %d in gold\n", totGold); //prints out the total gold
    
    for (i = 0; i<roomPtr[0]->inventory; i++)
    {
        printf("Picked up %c\n", roomPtr[i]->inInventory);
        
    }
    
}

void printRoom(int y, int x, int h, int w, int roomNum, struct room **roomPtr, struct door **doorPtr, struct gold **goldPtr, struct weap **weapPtr, struct mon **monPtr, struct equip **equipPtr, struct pot **potPtr, struct hero **heroPtr, struct stair **stairPtr)
{
    int m;
    
    m = roomNum;
    
    for (int i=x; i<=w+x; i++)  //print the north wall starting at x and going w units wide
        {
            mvaddch(y, i, '-');  

                for (int l=0; l< doorPtr[m]->numDoor; l++ )  //goes through the array and if at anypoint the door position equals the particular point in the wall print a door
                {
                    if ( (doorPtr[m]->doorPos[l]+x) == (i) && doorPtr[m]->doorWall[l] == 'n')
                    {
                        mvaddch(y, i, '+');
                    }
                }
        }

        for (int i=y+1; i<h+y; i++)  //prints a wall starting at Y and going h units down
        {
            mvaddch(i, x, '|');
        
            for (int l=0; l<(doorPtr[m]->numDoor); l++ )
            {
                if ( ( doorPtr[m]->doorPos[l]+y) == (i) && ( doorPtr[m]->doorWall[l]) == 'w')  //goes through the array and if at anypoint the door position equals the particular point in the wall print a door
                {
                    mvaddch(i, x, '+');
                }
            }

            for (int j=1; j<w; j++)  //prints the floors for every part insude the box
            {
                mvaddch(i, x+j, '.');

                for(int k=0; k<(monPtr[m]->snumMon); k++)  //if a particular point inside the box is equal to any of the icon positions print the icon instead
                {
                    if( (monPtr[m]->sMonx[k]+x)  == (x+j) && (monPtr[m]->sMony[k] + y) == i)
                    {
                        mvaddch(i, x+j, 'T');
                    }
                }
                for(int k=0; k<(goldPtr[m]->snumGold); k++) //if a particular point inside the box is equal to any of the icon positions print the icon instead
                {
                    if( (goldPtr[m]->sGoldx[k]+x)  == (x+j) && (goldPtr[m]->sGoldy[k] + y) == i)
                    {
                        mvaddch(i, x+j, '*');
                    }
                }
                for(int k=0; k<(goldPtr[m]->bnumGold); k++) //if a particular point inside the box is equal to any of the icon positions print the icon instead
                {
                    if( (goldPtr[m]->bGoldx[k]+x)  == (x+j) && (goldPtr[m]->bGoldy[k] + y) == i)
                    {
                        mvaddch(i, x+j, '8');
                    }
                }
                for(int k=0; k<(weapPtr[m]->comnumWeap); k++) //if a particular point inside the box is equal to any of the icon positions print the icon instead
                {
                    if( (weapPtr[m]->comWeapx[k]+x)  == (x+j) && (weapPtr[m]->comWeapy[k] + y) == i)
                    {
                        mvaddch(i, x+j, ')');
                    }
                }
                for(int k=0; k<(weapPtr[m]->rarnumWeap); k++) //if a particular point inside the box is equal to any of the icon positions print the icon instead
                {
                    if( (weapPtr[m]->rarWeapx[k]+x)  == (x+j) && (weapPtr[m]->rarWeapy[k] + y) == i)
                    {
                        mvaddch(i, x+j, '(');
                    }
                }
                for(int k=0; k<(monPtr[m]->wnumMon); k++)
                {
                    if( (monPtr[m]->wMonx[k]+x)  == (x+j) && (monPtr[m]->wMony[k] + y) == i) //if a particular point inside the box is equal to any of the icon positions print the icon instead
                    {
                        
                        int rand;
                        
                        rand=0;
                        
                        rand = getRand(); //get a random number 
                        
                        if (rand == 1) //if 1 print A, if 2 print B, if 3 print S, else print Z at the particular position 
                        {
                            mvaddch(i, x+j, 'A');
                            monPtr[0] -> monType = 'A';
                        }
                        else if (rand == 2)
                        {
                            mvaddch(i, x+j, 'B');
                            monPtr[0] -> monType = 'B';
                        }
                        else if (rand == 3)
                        {
                            mvaddch(i, x+j, 'S');
                            monPtr[0] -> monType = 'S';
                        }
                        else
                        {
                            mvaddch(i, x+j, 'Z');
                            monPtr[0] -> monType = 'Z';
                        }
                        
                        
                    }
                    
                }
                for(int k=0; k<(equipPtr[m]->numEquip); k++)
                {
                    if( (equipPtr[m]->equipX[k]+x)  == (x+j) && (equipPtr[m]->equipY[k] + y) == i) //if a particular point inside the box is equal to any of the icon positions print the icon instead
                    {
                        mvaddch(i, x+j, ']');
                    }
                }
                for(int k=0; k<(potPtr[m]->numPot); k++)
                {
                    if( (potPtr[m]->potX[k]+x)  == (x+j) && (potPtr[m]->potY[k] + y) == i) //if a particular point inside the box is equal to any of the icon positions print the icon instead
                    {
                        mvaddch(i, x+j, '!');
                    }
                }
                if( (heroPtr[m]->heroX+x)  == (x+j) && (heroPtr[m]->heroY+ y) == i) //if a particular point inside the box is equal to any of the icon positions print the icon instead
                {
                        mvaddch(i, x+j, '@');
                }
                for(int k=0; k<(stairPtr[m]->unumStair); k++)
                {
                    if( (stairPtr[m]->uStairx[k]+x)  == (x+j) && (stairPtr[m]->uStairy[k] + y) == i) //if a particular point inside the box is equal to any of the icon positions print the icon instead
                    {
                        mvaddch(i, x+j, '>');
                    }
                }
                for(int k=0; k<(stairPtr[m]->dnumStair); k++)
                {
                    if( (stairPtr[m]->dStairx[k]+x)  == (x+j) && (stairPtr[m]->dStairy[k] + y) == i) //if a particular point inside the box is equal to any of the icon positions print the icon instead
                    {
                        mvaddch(i, x+j, '<');
                    }
                }
                
                
            }
        
            mvaddch(i, w+x, '|');
        
            for (int l=0; l<(doorPtr[m]->numDoor); l++ )
            {
                
                if ( (doorPtr[m]->doorPos[l]+y) == (i) && ( doorPtr[m]->doorWall[l]) == 'e') //if anyelement in the array equals e and the position print a door there
                {
                    mvaddch(i, w+x, '+');
                }
                
            }
        }

        for (int i=x; i<=w+x; i++) 
        {
            mvaddch(h+y, i, '-');
        
            for (int l=0; l<doorPtr[m]->numDoor; l++ )
            {
                if ( (doorPtr[m]->doorPos[l]+x) == (i) && doorPtr[m]->doorWall[l] == 's') //if anyelement in the array equals e and the position print a door there
                {
                    mvaddch(h+y, i, '+');
                }
            }
        }
    
}

void drawHall(int y, int x, int roomNum ,int h, int w ,struct door **doorPtr)
{ 
    int i;
    int j;
    int k;
    int l;
    
    k = roomNum;    
    
    mvprintw(24, 0,"############################################################################################################");
    
    for ( i =0; i < doorPtr[k]->numDoor; i++)
    {
        ///////////for room 1////////////////////////////////
        if (roomNum == 0)
        {
            if (doorPtr[k]->doorWall[i] == 'n')
            {
                for (j = doorPtr[k]->doorPos[i] + x; j< 26 + x; j++ )
                {
                    mvaddch( 1,j,'#');
                }

                for (l = 1; l < 24; l++)
                {
                    mvaddch(l, 28,'#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'e')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j <24; j++ )
                {
                    mvaddch(j, w+x+1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'w')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j <24; j++ )
                {
                    mvaddch(j, x-1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 's')
            {
                for (l = y+h+1; l<24; l++ )
                {
                    mvaddch(l,x+doorPtr[k]->doorPos[i], '#');
                }
            }
        }
 //////////////////for room 2//////////////////////////////////       
        if (roomNum == 1)
        {
            if (doorPtr[k]->doorWall[i] == 'n')
            {
                for (j = doorPtr[k]->doorPos[i] + x; j< 26 + x; j++ )
                {
                    mvaddch( 1,j,'#');
                }

                for (l = 1; l < 24; l++)
                {
                    mvaddch(l, 28 + x,'#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'e')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j <24; j++ )
                {
                    mvaddch(j, w+x+1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'w')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j <24; j++ )
                {
                    mvaddch(j, x-1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 's')
            {
                for (l = y+h+1; l<24; l++ )
                {
                    mvaddch(l,x+doorPtr[k]->doorPos[i], '#');
                }
            }
        }
 ////////////////////for room 3////////////////////////////////       
        if (roomNum == 2)
        {
            if (doorPtr[k]->doorWall[i] == 'n')
            {
                for (j = doorPtr[k]->doorPos[i] + x; j< 28 + x; j++ )
                {
                    mvaddch( 1,j,'#');
                }

                for (l = 1; l < 24; l++)
                {
                    mvaddch(l, 28 + x,'#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'e')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j <24; j++ )
                {
                    mvaddch(j, w+x+1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'w')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j <24; j++ )
                {
                    mvaddch(j, x-1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 's')
            {
                for (l = y+h+1; l<24; l++ )
                {
                    mvaddch(l,x+doorPtr[k]->doorPos[i], '#');
                }
            }
        }
 /////////////////////for room 4////////////////////////
         if (roomNum == 3)
        {
            if (doorPtr[k]->doorWall[i] == 's')
            {
                for (j = doorPtr[k]->doorPos[i] + x; j< 28 + x; j++ )
                {
                    mvaddch( y+h+1,j,'#');
                }

                for (l = y+h+1; l > 24; l--)
                {
                    mvaddch(l, 28 + x,'#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'e')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j >24; j-- )
                {
                    mvaddch(j, w+x+1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'w')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j >24; j-- )
                {
                    mvaddch(j, x-1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'n')
            {
                for (l = y-1; l>24; l-- )
                {
                    mvaddch(l,x+doorPtr[k]->doorPos[i], '#');
                }
            }
        }
  ///////////////////for room 5///////////////////////////////////////
        if (roomNum == 4)
        {
            if (doorPtr[k]->doorWall[i] == 's')
            {
                for (j = doorPtr[k]->doorPos[i] + x; j< 28 + x; j++ )
                {
                    mvaddch( y+h+1,j,'#');
                }

                for (l = y+h+1; l > 24; l--)
                {
                    mvaddch(l, 28 + x,'#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'e')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j >24; j-- )
                {
                    mvaddch(j, w+x+1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'w')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j >24; j-- )
                {
                    mvaddch(j, x-1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'n')
            {
                for (l = y-1; l>24; l-- )
                {
                    mvaddch(l,x+doorPtr[k]->doorPos[i], '#');
                }
            }
        }
        ////////////for room 6//////////////////////////
        if (roomNum == 5)
        {
            if (doorPtr[k]->doorWall[i] == 's')
            {
                for (j = doorPtr[k]->doorPos[i] + x; j< 28 + x; j++ )
                {
                    mvaddch( y+h+1,j,'#');
                }

                for (l = y+h+1; l > 24; l--)
                {
                    mvaddch(l, 28 + x,'#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'e')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j >24; j-- )
                {
                    mvaddch(j, w+x+1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'w')
            {
                for (j = doorPtr[k]->doorPos[i] + y; j >24; j-- )
                {
                    mvaddch(j, x-1, '#');
                }
            }
            else if (doorPtr[k]->doorWall[i] == 'n')
            {
                for (l = y-1; l>24; l-- )
                {
                    mvaddch(l,x+doorPtr[k]->doorPos[i], '#');
                }
            }
        }
        
    }

}


int getRand2(int run)
{
    int num; //variable declarations
    int i;
    num=0;
    
    srand(time(NULL));
    
    for (i =0; i< run; i++)
    {
        num = num + (rand()%(200))+50 ; //produces random number between 50-200
    }

    return(num);
}

int getRand3(int run)
{
    int num;
    int i;
    num = 0;
     
    srand(time(NULL));
     
    for (i =0; i< run; i++)
    {
        num = num + rand() % 50; //produces random number between 0-50
    }

    return(num);
}



int getRand()
{
    int num;
    
    srand(time(NULL));
     
    num = rand()%4 + 1; //produces random number between 1-4
    
    return(num);
}
