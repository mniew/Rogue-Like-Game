#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

#ifndef __NIEWIADM_DRAWROOM__
#define __NIEWIADM_DRAWROOM__

/**
 * drawRoom
 * initializes ncurses, verifies the size of the screen ensuring it is appropriate. Calls function printRoom and heroMove. Will also print out the amount of gold collected after ncurses is done with.
 * IN: takes in the struct pointers 1-6
 * OUT: N/A
 * POST: no known side effects
 * ERROR: no known errors
 */
 void drawRoom(struct room **roomPtr, struct door **doorPtr, struct gold **goldPtr, struct weap **weapPtr, struct mon **monPtr, struct equip **equipPtr, struct pot **potPtr, struct hero **heroPtr, struct stair **stairPtr);
 
 /**
 * printRoom
 * prints the rooms using the y,x origin and width/height. It will then over right the necessary positions with other icons
 * IN: takes in the x and y as a reference to start printing each room from, height and width aswell as pointers 1 through 6 for other icons like potions,gold etc...
 * OUT: N/A
 * POST: no known side effects
 * ERROR: no known errors
 */
 void printRoom(int y, int x, int h, int w, int roomNum,struct room **roomPtr, struct door **doorPtr, struct gold **goldPtr, struct weap **weapPtr, struct mon **monPtr, struct equip **equipPtr, struct pot **potPtr, struct hero **heroPtr, struct stair **stairPtr);
 
 
 /**
 * drawHall
 * prints the hallways using the y,x origin and width/height.
 * IN: y,x used in combination with the room number height,width and door position to produce 
 * OUT: N/A
 * POST: no known side effects
 * ERROR: no known errors
 */
 void drawHall( int y, int x, int roomNum,int h, int w, struct door **doorPtr);
 
 
 /**
 * getRand
 * generates random number for the weak monsters
 * IN: N/A
 * OUT: returns the random number generated
 * POST: no known side effects
 * ERROR: no known errors
 */
 int getRand();
 
 /**
 * getRand2
 * generates random number for Big Gold
 * IN: howe manytimes it should generate a random number
 * OUT: the number generated
 * POST: will sometimes return 0, eventho 50 is added to the total nomatter what
 * ERROR: no known errors
 */
 int getRand2(int run);

 /**
 * getRand2
 * generates number for small gold
 * IN: how manytimes it should generate a random number
 * OUT: returnes the number generated
 * POST: has a tendency to return numbers > 50
 * ERROR: no known errors
 */
 int getRand3(int run);
 
 #endif
