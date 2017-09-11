#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

#ifndef __NIEWIADM_HEROMOVE__
#define __NIEWIADM_HEROMOVE__

/**
 * heroMove
 * identifies where the hero is and moves the cursor there and activates game loop
 * IN: All struct information for each room
 * OUT: N/A
 * POST: no known sideffects
 * ERROR: no known errors
 */
void heroMove(struct room **roomPtr, struct door **doorPtr, struct gold **goldPtr, struct weap **weapPtr, struct mon **monPtr, struct equip **equipPtr, struct pot **potPtr, struct hero **heroPtr, struct stair **stairPtr);

/**
 * moveCurs
 * movement code for the HERO, and collision code
 * IN: All struct information for each room
 * OUT: N/A
 * POST: no known side effects
 * ERROR: no known errors
 */
int moveCurs(char *key,int *rotation, int *potn,int *hp, int *roomNum, struct room **roomPtr, struct door **doorPtr, struct gold **goldPtr, struct weap **weapPtr, struct mon **monPtr, struct equip **equipPtr, struct pot **potPtr, struct hero **heroPtr, struct stair **stairPtr);

/**
 * cheackRoomNumber 
 * determines the room that the hero is in
 * IN: pointer to roomNumber
 * OUT: N/A
 * POST: no known side effects
 * ERROR: Eno known errors
 */
void checkRoomNumber(int *roomNum);

/**
 * combat
 * when the hero and a monster come into contact this function determines who attacks and sustains damage
 * IN: required variables
 * OUT: N/A
 * POST: no known side effects
 * ERROR: Eno known errors
 */
void combat(struct mon **monPtr,struct hero **heroPtr, char type, int *roomNum, int oldy, int oldx, int *hp, char *key);

//void usePotion(int *potn, int *hp);

/**
 * moveBigMonster
 * moves the Trolls monsters through their cycle using the rotation number
 * IN: roatation and the big monster array
 * OUT: N/A
 * POST: no known side effects
 * ERROR: Eno known errors
 */
void moveBigMonster(int *rotation, struct mon **monPtr);

/**
 * moveMonster
 * moves the small monsters through their cycle using the rotation number
 * IN: rotation and monster struct
 * OUT: N/A
 * POST: no known side effects
 * ERROR: Eno known errors
 */
void moveMonster(int *rotation, struct mon **monPtr);

/**
 * pickUp
 * prints items picked up
 * IN: takes i the thing stepped on, room ptr, potins number, as well as health
 * OUT: N/A
 * POST: no known side effects
 * ERROR: Eno known errors
 */
int pickUp(char atPos,struct room **roomPtr, int *potn, int *hp);

/**
 * removeMessage
 * clears message at the top of the screen
 * IN: N/A
 * OUT: N/A
 * POST: no known side effects
 * ERROR: Eno known errors
 */
void removeMessage();

/**
 * random
 * produces random number
 * IN: N/A
 * OUT: returns that number
 * POST: no known side effects
 * ERROR: Eno known errors
 */
int Rand();

/**
 * random
 * produces random number
 * IN: N/A
 * OUT: returns that number
 * POST: no known side effects
 * ERROR: Eno known errors
 */
int random1();

/**
 * endGame
 * ends the ncurses window
 * IN: N/A
 * OUT: N/A
 * POST: no known side effects
 * ERROR: Eno known errors
 */
void endGame();

#endif
