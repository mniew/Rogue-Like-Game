#include "readFile.h"
#include "drawRoom.h"

int readFile(char **argv)
{

    char str[256]; //initializations
    int i;
    int len;

    i = 0;
    len =0;

    struct room ** roomPtr;
    struct door ** doorPtr;
    struct gold ** goldPtr;
    struct weap ** weapPtr;
    struct mon ** monPtr;
    struct equip ** equipPtr;
    struct pot ** potPtr;
    struct hero ** heroPtr;
    struct stair ** stairPtr;
    
    roomPtr = malloc(sizeof(struct room*)*6);
    doorPtr = malloc(sizeof(struct door*)*6);
    goldPtr = malloc(sizeof(struct gold*)*6);
    weapPtr = malloc(sizeof(struct weap*)*6);
    monPtr = malloc(sizeof(struct mon*)*6);
    equipPtr = malloc(sizeof(struct equip*)*6);
    potPtr = malloc(sizeof(struct pot*)*6);
    heroPtr = malloc(sizeof(struct hero*)*6);
    stairPtr = malloc(sizeof(struct stair*)*6);

    FILE* dataFile;         //file pointer named dataFile

    dataFile  = fopen(argv[1], "r");    //opens file for reading

    while (fgets(str,255,dataFile) != NULL)  //aslong as it doesnt reach the end of the file continue reading in new strings
    {
        
        roomPtr[i] = inRoom(str);
        
        //for (int k = 0; k< roomPtr[i] -> wnumMon; k++)
        //{
            //printf("\n WMON X:%d\n", roomPtr[i] -> wMonx[k]);
            //printf("\n WMON Y:%d\n", roomPtr[i] -> wMony[k]);
        //}
        //
        //for (int k = 0; k< roomPtr[i] -> wnumMon; k++)
        //{
            //printf("\n COL :%d\n", roomPtr[i] -> col);
            //printf("\n ROW :%d\n", roomPtr[i] -> row);
        //}
        //
        //for (int k = 0; k< roomPtr[i] -> bnumGold; k++)
        //{
            //printf("\n BGOLD X:%d\n", roomPtr[i] -> bGoldx[k]);
            //printf("\n BGOLD Y:%d\n", roomPtr[i] -> bGoldy[k]);
        //}
        
        doorPtr[i] = inDoor(str);
        
        len = strlen(str); // get length of the string
        
        for (int j = 0; j<len; j++)
        {

            if (str[j] == 'd') // if there is a d
            {
                if (str[j+3] == ' ') //if it is a single digit
                {
                    str[j+1] = '.'; //repalce with . so that the letter is not mistaken for a room icon
                }
                else  //separate and add the two digits to get the exact position fo the door
                {
                    str[j+1] = '.';
                }
            }

        }
        
        //printf("\n%s\n", str);
        
        goldPtr[i] = inGold(str);
        
        weapPtr[i] = inWeap(str);
        
        monPtr[i] = inMon(str);
        
        equipPtr[i] = inEquip(str);
        
        potPtr[i] = inPot(str);
        
        heroPtr[i] = inHero(str);
        
        stairPtr[i] = inStair(str);
        
        i++;
    }
    
    drawRoom(roomPtr, doorPtr, goldPtr, weapPtr, monPtr, equipPtr, potPtr, heroPtr, stairPtr);
    
    free(roomPtr);
    
    for (int i= 0; i < doorPtr[i] -> numDoor; i++)
    {
        free(doorPtr[i]);
    }
    
    free(doorPtr);
    
    free(goldPtr);
    
    free(weapPtr);
    
    free(monPtr);
    
    for (int i= 0; i < equipPtr[i] -> numEquip; i++)
    {
        free(equipPtr[i]);
    }
    
    free(equipPtr);
    
    for (int i= 0; i < potPtr[i] -> numPot; i++)
    {
        free(potPtr[i]);
    }
    
    free(potPtr);
    
    free(heroPtr);
    
    free(stairPtr);
    
    fclose(dataFile);
    
    return (0);
}

struct room* inRoom(char str[149])
{
        int i;
        char temp[10];
        char tempR[10];
    
        i = 0;
        
        struct room* inRoom = malloc(sizeof(struct room));
        
        if (str[2] == 'X')  //if the 3rd element of the string is equal to a X
        {
            for ( i = 0; i<2; i++ )
            {
                temp[i] = str[i]; //take string up to that point and set it equal to the temporary one
            }
            
            inRoom -> row = temp[0] - '0';
            inRoom -> row = 10 + (temp[1] - '0');  //get the actual number at that point

            if (str[4] != ' ')
            {
                tempR[0] = str[3];   //if the fifth position is equal to a space
                tempR[1] = str[4];    //seperate the individual numbers and make it equal and add together

                inRoom -> col = tempR[0] - '0';  
                inRoom -> col = (10*inRoom->col) + (tempR[1] - '0');  //if there are two numbers multiply the first by 10 for the tens column and just add the second since its in the 1s
            }
            else
            {
                tempR[0] = str[3];

                inRoom -> col = tempR[0] - '0';  //gives col a value
                
            }

        }

        else if (str[1] == 'X') //if the 2nd element is equal to a X
        {
            for ( i = 0; i<1; i++ )
            {
                temp[i] = str[i];
            }

            inRoom -> row = temp[0] - '0'; //there is one number to add
            

            if (str[3] != ' ')  //if there is 2 numbers after the X do this
            {
                tempR[0] = str[2];
                tempR[1] = str[3];

                inRoom -> col = tempR[0] - '0'; //take the first number subtract zero for the actual number and make let it equal col
                inRoom -> col = (10*inRoom -> col) + (tempR[1] - '0'); //if there are two numbers multiple the first by 10 for the tens column and just add the second since its in the 1s
                
            }
            else //else there is ome and just add to the column total
            {
                tempR[0] = str[2];

                inRoom -> col = tempR[0] - '0'; //take the first number subtract zero for the actual number and make let it equal col
                
            }

        }

        //printf("COL:%d\n", inRoom -> col);
        //printf("ROW:%d\n", inRoom -> row);

        
        return inRoom;
    }
    
struct door* inDoor(char str[149])
{
    struct door* inDoor = malloc(sizeof(struct door));
    
        int len;
        int track; //tracks the number of particular icons storred in a particular array so that they can be accessed later.
        int k;

        track = 0;
        k = 0;
        
        len = strlen(str); // get length of the string

        for (int j = 0; j<len; j++)
        {
            inDoor->numDoor = 0;

            if (str[j] == 'd') // if there is a d
            {

                track= track +1;
                
                if (str[j+3] == ' ' || str[j+3] == '\n') //if it is a single digit
                {
                    inDoor->doorWall[k] = str[j+1];
                    str[j+1] = '.'; //repalce with . so that the letter is not mistaken for a room icon
                    inDoor->doorPos[k] = str[j+1+1] - '0';
                    k++;
                }
                else  //separate and add the two digits to get the exact position fo the door
                {
                    inDoor->doorWall[k] = str[j+1];
                    str[j+1] = '.';
                    inDoor->doorPos[k] = str[j+1+1] - '0';
                    inDoor->doorPos[k] =  (inDoor->doorPos[k]*10) + (str[j+1+1+1] - '0');
                    k++;
                }
            }

        }

    inDoor->numDoor = track;
        
    return inDoor;
}

struct gold* inGold(char str[149])
{
    struct gold* inGold = malloc(sizeof(struct gold));
    
    int len;
    int track; //tracks the number of particular icons storred in a particular array so that they can be accessed later.
    int k;

    track = 0;
    k = 0;
    
    len = strlen(str); // get length of the string
    
    for (int j = 0; j<len; j++)
        {
            inGold->snumGold = 0;
            
            if (str[j] == 'g')  // if a g is incountered
            {
                
                track= track +1; // add 1 to track the total number of g's
                
                if (str[j+2] == ',') //means first number in 1 digit
                {
                    if (str[j+4] == (' ') || str[j+4] == ('\n'))  //if secend number is also 1 digit
                    {
                        inGold->sGoldx[k] = (str[j+1] - '0');  // using ascii values get the real number in the string
                        inGold->sGoldy[k] = (str[j+3] - '0'); 
                        k++;
                    } 
                    else if (str[j+4] != (' ') || str[j+4] != ('\n')) //if second number is 2 digits
                    {
                        inGold->sGoldx[k] = (str[j+1] - '0');
                        inGold->sGoldy[k] = (str[j+3] - '0');
                        inGold->sGoldy[k] = (inGold->sGoldy[k]*10) + (str[j+4] - '0');  //with two digits you split the 2 up and add them together, however multiply the number in the tens column by 10
                        k++;
                    }
                }
                if (str[j+3] == ',') //first numbe is two digits
                {
                    if (str[j+5] == (' ') || str[j+5] == ('\n')) //second number is 1 digit 
                    {
                        inGold->sGoldx[k] = (str[j+1] - '0');  
                        inGold->sGoldx[k] = (inGold->sGoldx[k]*10) + (str[j+2] - '0');  //with two digits you split the 2 up and add them together, however multiply the number in the tens column by 10
                        inGold->sGoldy[k] = str[j+4] - '0';
                        k++;
                    }
                    else if (str[j+5] != (' ')||str[j+5] != ('\n'))  //second number is two digits
                    {
                        inGold->sGoldx[k] = (str[j+1] - '0');
                        inGold->sGoldx[k] = (inGold->sGoldx[k]*10) + (str[j+2] - '0'); //with two digits you split the 2 up and add them together, however multiply the number in the tens column by 10
                        inGold->sGoldy[k] = (str[j+4] - '0');
                        inGold->sGoldy[k] = (inGold->sGoldy[k]*10) + (str[j+5] - '0'); //with two digits you split the 2 up and add them together, however multiply the number in the tens column by 10
                        k++; 
                    }
                    
                }
            }
        }

    inGold->snumGold = track; //saves the number of small gold in that particular room
    track = 0;//sets track and k to zero as to be reused in the next loop
    k = 0;  
        
    for (int j = 0; j<len; j++)
        {
            inGold->bnumGold = 0;
            
            if (str[j] == 'G')
            {
                
                track= track +1;
                
                if (str[j+2] == ',')
                {
                    if (str[j+4] == (' ')||str[j+4] == ('\n'))
                    {
                        inGold->bGoldx[k] = (str[j+1] - '0');
                        inGold->bGoldy[k] = (str[j+3] - '0');
                        k++;
                    } 
                    else if (str[j+4] != (' ')||str[j+4] != ('\n'))
                    {
                        inGold->bGoldx[k] = (str[j+1] - '0');
                        inGold->bGoldy[k] = (str[j+3] - '0');
                        inGold->bGoldy[k] = (inGold->bGoldy[k]*10) + (str[j+4] - '0');
                        k++;
                    }
                }
                if (str[j+3] == ',')
                {
                    if (str[j+5] == (' ')||str[j+5] == ('\n'))
                    {
                        inGold->bGoldx[k] = (str[j+1] - '0');
                        inGold->bGoldx[k] = (inGold->bGoldx[k]*10) + (str[j+2] - '0');
                        inGold->bGoldy[k] = (str[j+4] - '0');
                        k++;
                    }
                    else if (str[j+5] != (' ')||str[j+5] != ('\n'))
                    {
                        inGold->bGoldx[k] = (str[j+1] - '0');
                        inGold->bGoldx[k] = (inGold->bGoldx[k]*10) + (str[j+2] - '0');
                        inGold->bGoldy[k] = (str[j+4] - '0');
                        inGold->bGoldy[k] = (inGold->bGoldy[k]*10) + (str[j+5] - '0');
                        k++; 
                    }
                    
                }
            }
        }

    inGold->bnumGold = track;
        
    return inGold;
}

struct weap* inWeap(char str[149])
{
    int k;
    int track;
    int j;
    int len;
    
    struct weap* inWeap = malloc(sizeof(struct weap));
    
    track = 0;
    k = 0;
    len = strlen(str);

    for (j = 0; j<len; j++)
    {
        inWeap->comnumWeap = 0;
        
        if (str[j] == 'w')
        {
        
            track= track +1;
            
            if (str[j+2] == ',')
            {
                if (str[j+4] == (' ')||str[j+4] == ('\n'))
                {
                    inWeap->comWeapx[k] = str[j+1] - '0';
                    inWeap->comWeapy[k] = (str[j+3] - '0');
                    k++;
                } 
                else if (str[j+4] != (' '))
                {
                    inWeap->comWeapx[k] = str[j+1] - '0';
                    inWeap->comWeapy[k] = str[j+3] - '0';
                    inWeap->comWeapy[k] = (inWeap->comWeapy[k]*10) + (str[j+4] - '0');
                    k++;
                }
            }
            if (str[j+3] == ',')
            {
                if (str[j+5] == (' ')||str[j+5] == ('\n'))
                {
                    inWeap->comWeapx[k] = str[j+1] - '0';
                    inWeap->comWeapx[k] = (inWeap->comWeapx[k]*10) + (str[j+2] - '0');
                    inWeap->comWeapy[k] = str[j+4] - '0';
                    k++;
                }
                else if (str[j+5] != (' ')||str[j+5] != ('\n'))
                {
                    inWeap->comWeapx[k] = str[j+1] - '0';
                    inWeap->comWeapx[k] = (inWeap->comWeapx[k]*10) + (str[j+2] - '0');
                    inWeap->comWeapy[k] = str[j+4] - '0';
                    inWeap->comWeapy[k] = (inWeap->comWeapy[k]*10) + (str[j+5] - '0');
                    k++; 
                }
                
            }
        }
    }
    
    inWeap->comnumWeap = track;
    track = 0;
    k = 0;
    
    for (j = 0; j<len; j++)
    {
        inWeap->rarnumWeap = 0;
    
        if (str[j] == 'W')
        {
            
            track= track +1;
            
            if (str[j+2] == ',')
            {
                if (str[j+4] == (' ')||str[j+4] == ('\n'))
                {
                    inWeap->rarWeapx[k] = str[j+1] - '0';
                    inWeap->rarWeapy[k] = (str[j+3] - '0');
                    k++;
                } 
                else if (str[j+4] != (' ')||str[j+4] != ('\n'))
                {
                    inWeap->rarWeapx[k] = str[j+1] - '0';
                    inWeap->rarWeapy[k] = str[j+3] - '0';
                    inWeap->rarWeapy[k] = (inWeap->rarWeapy[k]*10) + (str[j+4] - '0');
                    k++;
                }
            }
            if (str[j+3] == ',')
            {
                if (str[j+5] == (' ')||str[j+5] == ('\n'))
                {
                    inWeap->rarWeapx[k] = str[j+1] - '0';
                    inWeap->rarWeapx[k] = (inWeap->rarWeapx[k]*10) + (str[j+2] - '0');
                    inWeap->rarWeapy[k] = str[j+4] - '0';
                    k++;
                }
                else if (str[j+5] != (' ')||str[j+5] != ('\n'))
                {
                    inWeap->rarWeapx[k] = str[j+1] - '0';
                    inWeap->rarWeapx[k] = (inWeap->rarWeapx[k]*10) + (str[j+2] - '0');
                    inWeap->rarWeapy[k] = str[j+4] - '0';
                    inWeap->rarWeapy[k] = (inWeap->rarWeapy[k]*10) + (str[j+5] - '0');
                    k++; 
                }
                
            }
        }
    }

    inWeap->rarnumWeap = track;
    
    return inWeap;
}

struct mon* inMon(char str[149])
{
    int k;
    int track;
    int j;
    int len;
    
    struct mon* inMon = malloc(sizeof(struct mon));
    
    track = 0;
    k = 0;
    len = strlen(str);

    for (j = 0; j<len; j++)
    {
        inMon->wnumMon = 0;
        
        if (str[j] == 'm')
        {
            
            track= track +1;
            
            if (str[j+2] == ',')
            {
                if (str[j+4] == (' ')||str[j+4] == ('\n'))
                {
                    inMon->wMonx[k] = str[j+1] - '0';
                    inMon->wMony[k] = (str[j+3] - '0');
                    k++;
                } 
                else if (str[j+4] != (' ')||str[j+4] != ('\n'))
                {
                    inMon->wMonx[k] = str[j+1] - '0';
                    inMon->wMony[k] = str[j+3] - '0';
                    inMon->wMony[k] = (inMon->wMony[k]*10) + (str[j+4] - '0');
                    k++;
                }
            }
            if (str[j+3] == ',')
            {
                if (str[j+5] == (' ')||str[j+5] == ('\n'))
                {
                    inMon->wMonx[k] = str[j+1] - '0';
                    inMon->wMonx[k] = (inMon->wMonx[k]*10) + (str[j+2] - '0');
                    inMon->wMony[k] = str[j+4] - '0';
                    k++;
                }
                else if (str[j+5] != (' ')||str[j+5] != ('\n'))
                {
                    inMon->wMonx[k] = str[j+1] - '0';
                    inMon->wMonx[k] = (inMon->wMonx[k]*10) + (str[j+2] - '0');
                    inMon->wMony[k] = str[j+4] - '0';
                    inMon->wMony[k] = (inMon->wMony[k]*10) + (str[j+5] - '0');
                    k++; 
                }
                
            }
        }
    }
    inMon->wnumMon = track;
    track = 0;
    k = 0;
    
    for (j = 0; j<len; j++)
    {
        inMon->snumMon = 0;
        if (str[j] == 'M')
        {
            
            track= track +1;
            
            if (str[j+2] == ',')
            {
                if (str[j+4] == (' ')||str[j+4] == ('\n'))
                {
                    inMon->sMonx[k] = str[j+1] - '0';
                    inMon-> sMony[k] = (str[j+3] - '0');
                    k++;
                } 
                else if (str[j+4] != (' ')||str[j+4] != ('\n'))
                {
                    inMon->sMonx[k] = str[j+1] - '0';
                    inMon-> sMony[k] = str[j+3] - '0';
                    inMon-> sMony[k] = (inMon-> sMony[k]*10) + (str[j+4] - '0');
                    k++;
                }
            }
            if (str[j+3] == ',')
            {
                if (str[j+5] == (' ')||str[j+5] == ('\n'))
                {
                    inMon->sMonx[k] = str[j+1] - '0';
                    inMon->sMonx[k] = (inMon->sMonx[k]*10) + (str[j+2] - '0');
                    inMon-> sMony[k] = str[j+4] - '0';
                    k++;
                }
                else if (str[j+5] != (' ')||str[j+5] != ('\n'))
                {
                    inMon->sMonx[k] = str[j+1] - '0';
                    inMon->sMonx[k] = (inMon->sMonx[k]*10) + (str[j+2] - '0');
                    inMon-> sMony[k] = str[j+4] - '0';
                    inMon-> sMony[k] = (inMon-> sMony[k]*10) + (str[j+5] - '0');
                    k++; 
                }
                
            }
        }
    }
    inMon->snumMon = track;
    
    return inMon;
}

struct equip* inEquip(char str[149])
{
    struct equip* inEquip = malloc(sizeof(struct equip));
    
    int len;
    int track; //tracks the number of particular icons storred in a particular array so that they can be accessed later.
    int k;
    int j;
    
    track = 0;
    k = 0;
        
    len = strlen(str); // get length of the string

    for (j = 0; j<len; j++)
    {
        inEquip->numEquip = 0;

        if (str[j] == 'e')
        {
            
            track= track +1;
            
            if (str[j+2] == ',')
            {
                if (str[j+4] == (' ')||str[j+4] == ('\n'))
                {
                    inEquip->equipX[k] = str[j+1] - '0';
                    inEquip->equipY[k] = (str[j+3] - '0');
                    k++;
                } 
                else if (str[j+4] != (' ')||str[j+4] != ('\n'))
                {
                    inEquip->equipX[k] = str[j+1] - '0';
                    inEquip->equipY[k] = str[j+3] - '0';
                    inEquip->equipY[k] = (inEquip->equipY[k]*10) + (str[j+4] - '0');
                    k++;
                }
            }
            if (str[j+3] == ',')
            {
                if (str[j+5] == (' ')||str[j+5] == ('\n'))
                {
                    inEquip->equipX[k] = str[j+1] - '0';
                    inEquip->equipX[k] = (inEquip->equipX[k]*10) + (str[j+2] - '0');
                    inEquip->equipY[k] = str[j+4] - '0';
                    k++;
                }
                else if (str[j+5] != (' ')||str[j+5] != ('\n'))
                {
                    inEquip->equipX[k] = str[j+1] - '0';
                    inEquip->equipX[k] = (inEquip->equipX[k]*10) + (str[j+2] - '0');
                    inEquip->equipY[k] = str[j+4] - '0';
                    inEquip->equipY[k] = (inEquip->equipY[k]*10) + (str[j+5] - '0');
                    k++; 
                }
                
            }
        }
    }
    
    inEquip->numEquip = track;
        
    return inEquip;
}

struct pot* inPot(char str[149])
{
    struct pot* inPot = malloc(sizeof(struct pot));
    
    int len;
    int track; //tracks the number of particular icons storred in a particular array so that they can be accessed later.
    int k;
    int j;
    
    track = 0;
    k = 0;
        
    len = strlen(str); // get length of the string

    for (j = 0; j<len; j++)
    {
        inPot->numPot = 0;
        
        if (str[j] == 'p')
        {
            
            track= track +1;
            
            if (str[j+2] == ',')
            {
                if (str[j+4] == (' ')||str[j+4] == ('\n'))
                {
                    inPot->potX[k] = str[j+1] - '0';
                    inPot->potY[k] = (str[j+3] - '0');
                    k++;
                } 
                else if (str[j+4] != (' ')||str[j+4] != ('\n'))
                {
                    inPot->potX[k] = str[j+1] - '0';
                    inPot->potY[k] = str[j+3] - '0';
                    inPot->potY[k] = (inPot->potY[k]*10) + (str[j+4] - '0');
                    k++;
                }
            }
            if (str[j+3] == ',')
            {
                if (str[j+5] == (' ')||str[j+5] == ('\n'))
                {
                    inPot->potX[k] = str[j+1] - '0';
                    inPot->potX[k] = (inPot->potX[k]*10) + (str[j+2] - '0');
                    inPot->potY[k] = str[j+4] - '0';
                    k++;
                }
                else if (str[j+5] != (' ')||str[j+5] != ('\n'))
                {
                    inPot->potX[k] = str[j+1] - '0';
                    inPot->potX[k] = (inPot->potX[k]*10) + (str[j+2] - '0');
                    inPot->potY[k] = str[j+4] - '0';
                    inPot->potY[k] = (inPot->potY[k]*10) + (str[j+5] - '0');
                    k++; 
                }
            }
        }
    }

    inPot->numPot = track;
        
    return inPot;
}

struct hero* inHero(char str[149])
{
    struct hero* inHero = malloc(sizeof(struct hero));
    
    int len;
    int k;
    int j;
    
    k = 0;

        
    len = strlen(str); // get length of the string

    for (j = 0; j<len; j++)
    {

        if (str[j] == 'h')
        {
                
            if (str[j+2] == ',')
            {
                if (str[j+4] == (' ')||str[j+4] == ('\n'))
                {
                    inHero->heroX = str[j+1] - '0';
                    inHero->heroY = (str[j+3] - '0');
                    k++;
                } 
                else if (str[j+4] != (' ')||str[j+4] != ('\n'))
                {
                    inHero->heroX = str[j+1] - '0';
                    inHero->heroY = str[j+3] - '0';
                }
            }
        }
    }
        
    return inHero;
}

struct stair* inStair(char str[149])
{
    struct stair* inStair = malloc(sizeof(struct stair));
    
    int len;
    int track; //tracks the number of particular icons storred in a particular array so that they can be accessed later.
    int k;
    int j;
    
    track = 0;
    k = 0;
        
    len = strlen(str); // get length of the string

    for (j = 0; j<len; j++)
    {
        inStair->unumStair = 0;

        if (str[j] == 'a')
        {
                
            track= track +1;
                
            if (str[j+2] == ',')
            {
                if (str[j+4] == (' ')||str[j+4] == ('\n'))
                {
                    inStair->uStairx[k] = str[j+1] - '0';
                    inStair->uStairy[k] = (str[j+3] - '0');
                    k++;
                } 
                else if (str[j+4] != (' ')||str[j+4] != ('\n'))
                {
                    inStair->uStairx[k] = str[j+1] - '0';
                    inStair->uStairy[k] = str[j+3] - '0';
                    inStair->uStairy[k] = (inStair->uStairy[k]*10) + (str[j+4] - '0');
                    k++;
                }
            }
            if (str[j+3] == ',')
            {
                if (str[j+5] == (' ')||str[j+5] == ('\n'))
                {
                    inStair->uStairx[k] = str[j+1] - '0';
                    inStair->uStairx[k] = (inStair->uStairx[k]*10) + (str[j+2] - '0');
                    inStair->uStairy[k] = str[j+4] - '0';
                    k++;
                }
                else if (str[j+5] != (' ')||str[j+5] != ('\n'))
                {
                    inStair->uStairx[k] = str[j+1] - '0';
                    inStair->uStairx[k] = (inStair->uStairx[k]*10) + (str[j+2] - '0');
                    inStair->uStairy[k] = str[j+4] - '0';
                    inStair->uStairy[k] = (inStair->uStairy[k]*10) + (str[j+5] - '0');
                    k++; 
                }
                
            }
        }
    }

    inStair->unumStair = track;
    track = 0;
    k = 0;
        
    for (j = 0; j<len; j++)
    {
        inStair->dnumStair = 0;

        if (str[j] == 'z')
        {
            track= track +1;
            
            if (str[j+2] == ',')
            {
                if (str[j+4] == (' ')||str[j+4] == ('\n'))
                {
                    inStair->dStairx[k] = str[j+1] - '0';
                    inStair->dStairy[k] = (str[j+3] - '0');
                    k++;
                } 
                else if (str[j+4] != (' ')||str[j+4] != ('\n'))
                {
                    inStair->dStairx[k] = str[j+1] - '0';
                    inStair->dStairy[k] = str[j+3] - '0';
                    inStair->dStairy[k] = (inStair->dStairy[k]*10) + (str[j+4] - '0');
                    k++;
                }
            }
            if (str[j+3] == ',')
            {
                if (str[j+5] == (' ')||str[j+5] == ('\n'))
                {
                    inStair->dStairx[k] = str[j+1] - '0';
                    inStair->dStairx[k] = (inStair->dStairx[k]*10) + (str[j+2] - '0');
                    inStair->dStairy[k] = str[j+4] - '0';
                    k++;
                }
                else if (str[j+5] != (' ')||str[j+5] != ('\n'))
                {
                    inStair->dStairx[k] = str[j+1] - '0';
                    inStair->dStairx[k] = (inStair->dStairx[k]*10) + (str[j+2] - '0');
                    inStair->dStairy[k] = str[j+4] - '0';
                    inStair->dStairy[k] = (inStair->dStairy[k]*10) + (str[j+5] - '0');
                    k++; 
                }
                
            }
        }
    }
        inStair->dnumStair = track;
        
    return inStair;
}
