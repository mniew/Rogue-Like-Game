#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef __NIEWIADM_READFILE__
#define __NIEWIADM_READFILE__

//struct room
//{
    ///int row;
    ///int col;
//
    ///char doorWall[3];
    ///int doorPos[3];
    ///int numDoor;
//
    ///int sGoldx[10];
    ///int sGoldy[10];
    ///int snumGold;
//
    ///int bGoldx[10];
    ///int bGoldy[10];
    ///int bnumGold;
//
    ///int comWeapx[10];
    ///int comWeapy[10];
    ///int comnumWeap;
    ///
    ///int rarWeapx[10];
    ///int rarWeapy[10];
    ///int rarnumWeap;
    //
    ///int wMonx[10];
    ///int wMony[10];
    ///int wnumMon;
    //
    ///int sMonx[10];
    ///int sMony[10];
    ///int snumMon;
    //
    ///int equipX[10];
    ///int equipY[10];
    ///int numEquip;
    //
    ///int potX[10];
    ///int potY[10];
    ///int numPot;
    //
    ///int heroX;
    ///int heroY;
    //
    ///int uStairx[10];
    ///int uStairy[10];
    ///int unumStair;
    //
    //int dStairx[10];
    //int dStairy[10];
    //int dnumStair;
//
//};

struct room
{
    int col;
    int row;
    int inventory;
    char inInventory;
};

struct door
{
    char doorWall[3];
    int doorPos[3];
    int numDoor; 
};

struct gold
{
    int sGoldx[9];
    int sGoldy[9];
    int snumGold;

    int bGoldx[9];
    int bGoldy[9];
    int bnumGold;
};

struct weap
{
    int comWeapx[9];
    int comWeapy[9];
    int comnumWeap;
    
    int rarWeapx[9];
    int rarWeapy[9];
    int rarnumWeap;
    
};

struct mon
{
    int wMonx[9];
    int wMony[9];
    char monType;
    int wMonhp[9];
    int wnumMon;
    
    int sMonx[9];
    int sMony[9];
    int sMonhp[9];
    int snumMon;
};

struct equip
{
    int equipX[9];
    int equipY[9];
    int numEquip;
};

struct pot
{
    int potX[9];
    int potY[9];
    int numPot;  
};

struct hero
{
    int heroX;
    int heroY;
    int attack;
};

struct stair
{
    int uStairx[9];
    int uStairy[9];
    int unumStair; 
    
    int dStairx[9];
    int dStairy[9];
    int dnumStair; 
};

/**
 * readFile
 * parses the particular line and stores information in appropriate struct
 * IN: Takes in the file
 * OUT: returnes zero
 * POST: no known side effects 
 * ERROR: no known errors
 */
int readFile(char **argv);
/**
 * inRoom
 * parses the particular line and stores information in appropriate struct
 * IN: Takes in the file
 * OUT: returnes the pointer that was malloced
 * POST: no known side effects 
 * ERROR: no known errors
 */
struct room* inRoom(char str[149]);
/**
 * inDoor
 * parses the particular line and stores information in appropriate struct
 * IN: Takes in the file
 * OUT: returnes the pointer that was malloced
 * POST: no known side effects 
 * ERROR: no known errors
 */
struct door* inDoor(char str[149]);
/**
 * inGold
 * parses the particular line and stores information in appropriate struct
 * IN: Takes in the file
 * OUT: returnes the pointer that was malloced
 * POST: no known side effects 
 * ERROR: no known errors
 */
struct gold* inGold(char str[149]);
/**
 * inWeap
 * parses the particular line and stores information in appropriate struct
 * IN: Takes in the file
 * OUT: returnes the pointer that was malloced
 * POST: no known side effects 
 * ERROR: no known errors
 */
struct weap* inWeap(char str[149]);
/**
 * inMon
 * parses the particular line and stores information in appropriate struct
 * IN: Takes in the file
 * OUT: returnes the pointer that was malloced
 * POST: no known side effects 
 * ERROR: no known errors
 */
struct mon* inMon(char str[149]);
/**
 * inEquip
 * parses the particular line and stores information in appropriate struct
 * IN: Takes in the file
 * OUT: returnes the pointer that was malloced
 * POST: no known side effects 
 * ERROR: no known errors
 */
struct equip* inEquip(char str[149]);
/**
 * inPot
 * parses the particular line and stores information in appropriate struct
 * IN: Takes in the file
 * OUT: returnes the pointer that was malloced
 * POST: no known side effects 
 * ERROR: no known errors
 */
struct pot* inPot(char str[149]);
/**
 * inHero
 * parses the particular line and stores information in appropriate struct
 * IN: Takes in the file
 * OUT: returnes the pointer that was malloced
 * POST: no known side effects 
 * ERROR: no known errors
 */
struct hero* inHero(char str[149]);
/**
 * inHero
 * parses the particular line and stores information in appropriate struct
 * IN: Takes in the file
 * OUT: returnes the pointer that was malloced
 * POST: no known side effects 
 * ERROR: no known errors
 */
struct stair* inStair(char str[149]);

 #endif
