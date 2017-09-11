#include "readFile.h"
#include "drawRoom.h"
#include "heroMove.h"

void heroMove(struct room **roomPtr, struct door **doorPtr, struct gold **goldPtr, struct weap **weapPtr, struct mon **monPtr, struct equip **equipPtr, struct pot **potPtr, struct hero **heroPtr, struct stair **stairPtr)
{
    
    char *key;
    char k;
                                            //initialized variables
    int roomNumber;
    int *roomNum;
    
    int i;
    
    int rotate;
    int *rotation;
    
    int potion;
    int *potn;
    
    int health;
    int *hp;
    
    k = 0;
    key = &k; 
    
    roomPtr[0]-> inventory = 0;
    
    roomNumber = 0;
    roomNum = &roomNumber; //makes pointer roomNum equal to desired integer adress
    
    rotate = 0;
    rotation = &rotate;  //point to desired integer value
    
    potion= 1;          //points to desired integer value
    potn = &potion;
    
    health = 50;        //points to desired integer value
    hp = &health;
    
    heroPtr[0] -> attack = 5;
    
    for (i=0; i<6; i++)
    {
        roomPtr[i]->inInventory = 0;
    }
    
    for (i = 0; i < 6; i++) //gives bigmonsters 50 hp
    {
        monPtr[i] -> sMonhp[0] = 50;
    }
    
    for (i = 0; i < 6; i++) // assigns health
    {
        int health;
        
        if (monPtr[0] -> monType == 'Z')
        {
            health = 15;
        }
        if (monPtr[0] -> monType == 'A')
        {
            health = 5;
        }
        if (monPtr[0] -> monType == 'B')
        {
            health = 2;
        }
        if (monPtr[0] -> monType == 'S')
        {
            health = 5;
        }
        
        for (int j =0; j< monPtr[i] -> wnumMon; j++)
        {
            monPtr[i] -> wMonhp[j] = health;
        }
    }
    
    
    goldPtr[1]->snumGold = 0;  //reusing the integers to store the number of gold collected so they no equal zero
    goldPtr[1]->bnumGold = 0;
    
    noecho();
    cbreak();
    
    mvprintw(50,1,"Health: %d, Potions: %d, Attack: %d, Inv: %d/5", *hp, *potn, 5, roomPtr[0]-> inventory);
    
    if (heroPtr[0]->heroX > 0 && heroPtr[0]->heroY > 0)  //if the hero is in this room print a . there so the cursor appears there
    {
        *roomNum = 1;
        mvaddch(heroPtr[0]->heroY + 2, heroPtr[0]->heroX +3, '.');
    }
    
    else if (heroPtr[1]->heroX > 0 && heroPtr[1]->heroY > 0) //if the hero is in this room print a . there so the cursor appears there
    {
        *roomNum = 2;
        mvaddch(heroPtr[1]->heroY + 2, heroPtr[1]->heroX +33, '.');
    }
    
    else if (heroPtr[2]->heroX > 0 && heroPtr[2]->heroY > 0) //if the hero is in this room print a . there so the cursor appears there
    {
        *roomNum = 3;
        mvaddch(heroPtr[2]->heroY + 2, heroPtr[2]->heroX +63, '.');
    }
    
    else if (heroPtr[3]->heroX > 0 && heroPtr[3]->heroY > 0) //if the hero is in this room print a . there so the cursor appears there
    {
        *roomNum = 4;
        mvaddch(heroPtr[3]->heroY + 28, heroPtr[3]->heroX +3, '.');
    }
    
    else if (heroPtr[4]->heroX > 0 && heroPtr[4]->heroY > 0) //if the hero is in this room print a . there so the cursor appears there
    {
        *roomNum = 5;
        mvaddch(heroPtr[4]->heroY + 28, heroPtr[4]->heroX +33, '.');
    }
    
    else if (heroPtr[5]->heroX > 0 && heroPtr[5]->heroY > 0) //if the hero is in this room print a . there so the cursor appears there
    {
        *roomNum = 6;
        mvaddch(heroPtr[5]->heroY + 28, heroPtr[5]->heroX +63, '.');
    }
    
    //game loop
    
    do{
        int stop;
        if (*rotation == 4)
        {
            *rotation = 0;
        }
        *key = getch(); //key equal to to any key clicked
        *rotation = *rotation +1;
        stop = moveCurs(key, rotation, potn, hp,roomNum, roomPtr, doorPtr, goldPtr, weapPtr, monPtr, equipPtr, potPtr, heroPtr, stairPtr); //stop is equal to the fnction
        checkRoomNumber(roomNum);
        refresh();  //updates the screen
        if (stop == 1) //stop is equal to 1 end the loop
        {
            *key = 'q';
        }
        
    }while ((*key != 'q'));
    
    endGame(); //ends the window
    
}

int moveCurs(char *key,int *rotation ,int *potn, int *hp, int *roomNum, struct room **roomPtr, struct door **doorPtr, struct gold **goldPtr, struct weap **weapPtr, struct mon **monPtr, struct equip **equipPtr, struct pot **potPtr, struct hero **heroPtr, struct stair **stairPtr)
{ 
    int xpos;  //variables used to identify position
    int ypos;
    int oldx;
    int oldy;
    
    char atPos; //character at that particular position
    
    getyx(stdscr, ypos, xpos); //gets the y and x position of the curser
    oldx = xpos;
    oldy = ypos;
    
    if (*key == 'w')  //what to do when W/A/S/D is pressed 
    {
        ypos--;
    }
    else if (*key == 'a')
    {
        xpos--;
    }
    else if (*key == 's')
    {
        ypos++;
    }
    else if (*key == 'd')
    {
        xpos++;
    }
    
    atPos = mvinch(ypos, xpos); //character at that postion
    
    //if (key == 'p')
    //{
        //usePotion(potn, hp);
    //}

    moveMonster(rotation, monPtr);
    moveBigMonster(rotation, monPtr);
    
    
    if (atPos == '.') // if it is a .
    {
        removeMessage();
        mvaddch(ypos, xpos, '@');
        mvaddch(oldy, oldx, '.');
        move(ypos,xpos);
    }
    else if (atPos == '#') // if it is a .
    {
        removeMessage();
        mvaddch(ypos, xpos, '@');
        mvaddch(oldy, oldx, '#');
        move(ypos,xpos);
    }
    else if (atPos == '*') //if it is a *
    {
        pickUp(atPos, roomPtr, potn, hp);
        mvaddch(ypos, xpos, '@');
        mvaddch(oldy, oldx, '.');
        move(ypos,xpos);
        goldPtr[1]->snumGold = goldPtr[1]->snumGold + 1;
    }
    else if (atPos == ')'|| atPos == '(') //strong or weak weapon
    {
        pickUp(atPos, roomPtr, potn, hp);
        mvaddch(ypos, xpos, '@');
        mvaddch(oldy, oldx, '.');
        move(ypos,xpos);
    }
    else if (atPos == ']' ) //equipment
    {
        pickUp(atPos, roomPtr, potn, hp);
        mvaddch(ypos, xpos, '@');
        mvaddch(oldy, oldx, '.');
        move(ypos,xpos);
    }
    else if (atPos == '!') //potion
    {
        pickUp(atPos, roomPtr, potn, hp);
        mvaddch(ypos, xpos, '@');
        mvaddch(oldy, oldx, '.');
        move(ypos,xpos);
    }
    else if (atPos == '8')  //if big gold is encountered
    {
        pickUp(atPos, roomPtr, potn, hp);
        mvaddch(ypos, xpos, '@');
        mvaddch(oldy, oldx, '.');
        move(ypos,xpos);
        goldPtr[1]->bnumGold = goldPtr[1]->bnumGold + 1;
    }
    else if (atPos == '-'||atPos == '|'||atPos == ' ')  //what to do if a wall is encountered
    {
        ypos = oldy;
        xpos = oldx;
        mvaddch(ypos, xpos,'@');
        move(ypos, xpos);
    }
    else if (atPos == 'T') // if a monster is encountered
    {
        char type = 'T';
        combat(monPtr, heroPtr, type, roomNum, oldy, oldx, hp, key);
        ypos = oldy;
        xpos = oldx;
        mvaddch(ypos, xpos,'@');
        move(ypos, xpos);
    }
    else if (atPos == 'B') // if a monster is encountered
    {
        char type = 'B';
        combat(monPtr, heroPtr, type, roomNum, oldy, oldx, hp, key);
        ypos = oldy;
        xpos = oldx;
        mvaddch(ypos, xpos,'@');
        move(ypos, xpos);
    }
    else if (atPos == 'S') // if a monster is encountered
    {
        char type = 'S';
        combat(monPtr, heroPtr, type, roomNum, oldy, oldx, hp, key);
        ypos = oldy;
        xpos = oldx;
        mvaddch(ypos, xpos,'@');
        move(ypos, xpos);
    }
    else if (atPos == 'Z') // if a monster is encountered
    {
        char type = 'Z';
        combat(monPtr, heroPtr, type, roomNum, oldy, oldx, hp, key);
        ypos = oldy;
        xpos = oldx;
        mvaddch(ypos, xpos,'@');
        move(ypos, xpos);
    }
    else if (atPos == 'A') // if a monster is encountered
    {
        char type = 'A';
        combat(monPtr, heroPtr, type, roomNum, oldy, oldx, hp, key);
        ypos = oldy;
        xpos = oldx;
        mvaddch(ypos, xpos,'@');
        move(ypos, xpos);
    }
    else if (atPos == '<'||atPos == '>')
    {
        return (1);
    }
    else if (atPos == '+')  //if a door is encountered
    {  
        pickUp(atPos, roomPtr, potn, hp);
        mvaddch(ypos, xpos, '@');
        mvaddch(oldy, oldx, '+');
        move(ypos,xpos);
        
    }

   return(0);
}

 void checkRoomNumber(int *roomNum)
{
    int ypos;
    int xpos;
    
    getyx(stdscr, ypos, xpos); //gets the y and x position of the curser
    
    if (xpos < 33 && xpos < 63) //if the curser is in the first 3rd
    {
        if (ypos < 28)
        {
            *roomNum = 1; ////it is either in 1/4 depending on the height
        }
        else if (ypos>33)
        {
            *roomNum = 4;
        }
    }
    if (xpos < 63 && xpos > 33)  //2nd 3rd
    {
        if (ypos < 28)
        {
            *roomNum = 2;
        }
        else if (ypos>33)
        {
            *roomNum = 5;
        }
    }
    if (xpos > 63) // and the last 3rd
    {
        if (ypos < 28)
        {
            *roomNum = 3;
        }
        else if (ypos>33)
        {
            *roomNum = 6;
        }
    }
    
}

void combat(struct mon **monPtr,struct hero **heroPtr, char type, int *roomNum, int oldy, int oldx, int *hp, char *key)
{ 
    int num; 
    int enemySpeed;
    
    num = random1();
    
    if (type == 'T')
    {
        int y;
        int x;
        enemySpeed = 3;
        
        if (*roomNum == 1)
        {
           y = 2;
           x = 3; 
        }
        else if (*roomNum == 2)
        {
            y = 2; 
            x = 33;
        }
        else if (*roomNum == 3)
        {
            y = 2; 
            x = 63;
        }

        if (num > enemySpeed)
        {
            monPtr[*roomNum -1] -> sMonhp[0] = monPtr[*roomNum -1] -> sMonhp[0] - heroPtr[0]-> attack;
            mvprintw(0,1, "Hero caused %d damage. The Troll is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> sMonhp[0]);
            if (monPtr[*roomNum -1] -> sMonhp[0] <= 0)
            {
                mvaddch(monPtr[*roomNum - 1] -> sMony[0] + y,monPtr[*roomNum - 1] -> sMonx[0] + x,'.'); //replaces troll position with tile
                monPtr[*roomNum - 1] -> sMony[0] = 0;
                monPtr[*roomNum - 1] -> sMonx[0] = 0;   //set to zero so it cannot be re-drawn
            }
        }
        else
        {
            *hp = *hp - 5;
            mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
            mvprintw(50,1,"Health: %d, ", *hp);
            if (*hp <= 0)
            {
                *key = 'q'; ////make the keyy equal to q
            }
        }
    }
    else if (type == 'A')
    {
        enemySpeed = 1;
        
        if (*roomNum == 1)
        {
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Aquator is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 3,'.'); //replaces monster position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = -0;
                    monPtr[*roomNum - 1] -> wMonx[0] = -0;
                    
                }
            }
            else
            {
                heroPtr[0] -> attack = heroPtr[0] -> attack - 1;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d attack                ", heroPtr[0] -> attack);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
    
        else if (*roomNum == 2)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Aquator is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 33,'.'); //replaces monster position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                heroPtr[0] -> attack = heroPtr[0] -> attack - 1;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d attack                ", heroPtr[0] -> attack);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        else if (*roomNum == 3)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Aquator is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 63,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                heroPtr[0] -> attack = heroPtr[0] -> attack - 1;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d attack                ", heroPtr[0] -> attack);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        
        else if (*roomNum == 4)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Aquator is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 3,'.'); //replaces aquator position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                heroPtr[0] -> attack = heroPtr[0] -> attack - 1;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d attack                ", heroPtr[0] -> attack);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
            
        }
        
        else if (*roomNum == 5)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Aquator is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0 || monPtr[*roomNum -1] -> wMonhp[1] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 33,'.'); //replaces monster position with tile
                    mvaddch(monPtr[*roomNum - 1] -> wMony[1] + 28,monPtr[*roomNum - 1] -> wMonx[1] + 33,'.');
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                heroPtr[0] -> attack = heroPtr[0] -> attack - 1;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d attack                ", heroPtr[0] -> attack);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        
        else if (*roomNum == 6)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Aquator is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0 || monPtr[*roomNum -1] -> wMonhp[1] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 63,'.'); //replaces bat position with tile
                    mvaddch(monPtr[*roomNum - 1] -> wMony[1] + 28,monPtr[*roomNum - 1] -> wMonx[1] + 63,'.');
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                heroPtr[0] -> attack = heroPtr[0] -> attack - 1;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d attack              ", heroPtr[0] -> attack);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        
    }
    else if (type == 'B')
    {
        enemySpeed = 4;
        
        if (*roomNum == 1)
        {
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Bat is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 3,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = -0;
                    monPtr[*roomNum - 1] -> wMonx[0] = -0;
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
    
        else if (*roomNum == 2)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Bat is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 33,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        else if (*roomNum == 3)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Bat is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 63,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        
        else if (*roomNum == 4)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Bat is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 3,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
            
        }
        
        else if (*roomNum == 5)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Bat is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0 || monPtr[*roomNum -1] -> wMonhp[1] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 33,'.'); //replaces bat position with tile
                    mvaddch(monPtr[*roomNum - 1] -> wMony[1] + 28,monPtr[*roomNum - 1] -> wMonx[1] + 33,'.');
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        
        else if (*roomNum == 6)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Bat is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0 || monPtr[*roomNum -1] -> wMonhp[1] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 63,'.'); //replaces bat position with tile
                    mvaddch(monPtr[*roomNum - 1] -> wMony[1] + 28,monPtr[*roomNum - 1] -> wMonx[1] + 63,'.');
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
    }
          
    else if (type == 'Z')
    {
        enemySpeed = 2;
        
        if (*roomNum == 1)
        {
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Zombie is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 3,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = -0;
                    monPtr[*roomNum - 1] -> wMonx[0] = -0;
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
    
        else if (*roomNum == 2)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Zombie is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 33,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        else if (*roomNum == 3)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Zombie is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 63,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        
        else if (*roomNum == 4)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Zombie is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 3,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
            
        }
        
        else if (*roomNum == 5)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Zombie is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0 || monPtr[*roomNum -1] -> wMonhp[1] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 33,'.'); //replaces bat position with tile
                    mvaddch(monPtr[*roomNum - 1] -> wMony[1] + 28,monPtr[*roomNum - 1] -> wMonx[1] + 33,'.');
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        
        else if (*roomNum == 6)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Zombie is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0 || monPtr[*roomNum -1] -> wMonhp[1] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 63,'.'); //replaces bat position with tile
                    mvaddch(monPtr[*roomNum - 1] -> wMony[1] + 28,monPtr[*roomNum - 1] -> wMonx[1] + 63,'.');
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
    }
    else if (type == 'S')
    {
        enemySpeed = 4;
        
        if (*roomNum == 1)
        {
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Snake is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 3,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = -0;
                    monPtr[*roomNum - 1] -> wMonx[0] = -0;
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
    
        else if (*roomNum == 2)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Snake is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 33,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d,", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        else if (*roomNum == 3)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Snake is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 2,monPtr[*roomNum - 1] -> wMonx[0] + 63,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        
        else if (*roomNum == 4)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Snake is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 3,'.'); //replaces bat position with tile
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
            
        }
        
        else if (*roomNum == 5)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Snake is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0 || monPtr[*roomNum -1] -> wMonhp[1] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 33,'.'); //replaces bat position with tile
                    mvaddch(monPtr[*roomNum - 1] -> wMony[1] + 28,monPtr[*roomNum - 1] -> wMonx[1] + 33,'.');
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
        
        else if (*roomNum == 6)
        {   
        
            if (num > enemySpeed)
            {
                monPtr[*roomNum -1] -> wMonhp[0] = monPtr[*roomNum -1] -> wMonhp[0] - heroPtr[0]-> attack;
                mvprintw(0,1, "Hero caused %d damage. The Snake is at %d health          ", heroPtr[0] -> attack, monPtr[*roomNum -1] -> wMonhp[0]);
                if (monPtr[*roomNum -1] -> wMonhp[0] <= 0 || monPtr[*roomNum -1] -> wMonhp[1] <= 0)
                {
                    mvaddch(monPtr[*roomNum - 1] -> wMony[0] + 28,monPtr[*roomNum - 1] -> wMonx[0] + 63,'.'); //replaces bat position with tile
                    mvaddch(monPtr[*roomNum - 1] -> wMony[1] + 28,monPtr[*roomNum - 1] -> wMonx[1] + 63,'.');
                    monPtr[*roomNum - 1] -> wMony[0] = 0;
                    monPtr[*roomNum - 1] -> wMonx[0] = 0;   //set to zero so it cannot be re-drawn
                    
                }
            }
            else
            {
                *hp = *hp - 5;
                mvprintw(0,1, "Hero was attacked, the Hero is at %d health                ", *hp);
                mvprintw(50,1,"Health: %d, ", *hp);
                if (*hp <= 0)
                {
                    *key = 'q'; ////make the keyy equal to q
                }
            }
        }
    }
    
}



//void usePotion(int *potn, int *hp)
//{
    //mvprintw(50,1,"IN USED POTION");
    //*potn = *potn -1;
    //*hp = 50;
    //mvprintw(50,1,"Health: %d, Potions: %d,",*hp, *potn);
     //
//}

void moveBigMonster(int *rotation, struct mon **monPtr)
{
    int i;
    int j;
    int y;
    int x;
    
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j< 1; j++)
        {
            
            //////////////room 1////////////////////
            if (i == 0)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                    
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';

                if (*rotation == 1 && monPtr[0] -> sMony[0] != 0) //moves up
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+3, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if ( atPosU == '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if (atPosU != '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }

                }
                
                if (*rotation == 2 && monPtr[0] -> sMony[0] != 0) //moves right
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+3, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if ( atPosR == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if (atPosR != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }

                }
                
                if (*rotation == 3 && monPtr[0] -> sMony[0] != 0) //moves down
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+3, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if ( atPosD == '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if (atPosD != '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }

                }
                if (*rotation == 4 && monPtr[0] -> sMony[0] != 0) //moves left
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+3, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if ( atPosL == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if (atPosL != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }

                }
            }
            
  ////////////////////for room 2/////////////////////////////          
            if (i == 1)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                    
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';

                if (*rotation == 1 && monPtr[1] -> sMony[0] != 0) //moves up
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+33, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {   
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosU == '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if (atPosU != '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }

                }
                
                if (*rotation == 2 && monPtr[1] -> sMony[0] != 0) //moves right
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+33, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosR == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if (atPosR != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }

                }
                
                if (*rotation == 3 && monPtr[1] -> sMony[0] != 0) //moves down
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+33, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosD == '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if (atPosD != '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }

                }
                if (*rotation == 4 && monPtr[1] -> sMony[0] != 0) //moves left
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+33, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosL == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if (atPosL != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }

                }
            }
 /////////////////////////room 3/////////////////           
            if (i == 2)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                    
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';

                if (*rotation == 1 && monPtr[2] -> sMony[0] != 0) //moves up
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+63, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }
                    else if ( atPosU == '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }
                    else if (atPosU != '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }

                }
                
                if (*rotation == 2 && monPtr[2] -> sMony[0] != 0) //moves right
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+63, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosR == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }
                    else if (atPosR != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }

                }
                
                if (*rotation == 3 && monPtr[2] -> sMony[0] != 0) //moves down
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+63, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosD == '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }
                    else if (atPosD != '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }

                }
                if (*rotation == 4 && monPtr[2] -> sMony[0] != 0) //moves left
                {
                    mvaddch(monPtr[i]->sMony[j]+2, monPtr[i]->sMonx[j]+63, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosL == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }
                    else if (atPosL != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }

                }
            }
            //////////////room 4/////////////////////
            if (i == 3 && monPtr[3] -> sMony[0] != 0)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                    
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';

                if (*rotation == 1) //moves up
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+3, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosU == '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if (atPosU != '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }

                }
                
                if (*rotation == 2 && monPtr[3] -> sMony[0] != 0) //moves right
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+3, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosR == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if (atPosR != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }

                }
                
                if (*rotation == 3 && monPtr[3] -> sMony[0] != 0) //moves down
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+3, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosD == '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if (atPosD != '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }

                }
                if (*rotation == 4 && monPtr[3] -> sMony[0] != 0) //moves left
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+3, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosL == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }
                    else if (atPosL != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 3;
                    }

                }
            }
  ////////////room 5///////////////          
            if (i == 4)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                    
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';

                if (*rotation == 1 && monPtr[4] -> sMony[0] != 0) //moves up
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+33, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosU == '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if (atPosU != '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }

                }
                
                if (*rotation == 2 && monPtr[4] -> sMony[0] != 0) //moves right
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+33, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosR == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if (atPosR != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }

                }
                
                if (*rotation == 3 && monPtr[4] -> sMony[0] != 0) //moves down
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+33, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosD == '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if (atPosD != '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }

                }
                if (*rotation == 4 && monPtr[4] -> sMony[0] != 0) //moves left
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+33, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosL == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if (atPosL != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }

                }
            }
            ///////////////////room 6////////////////
            if (i == 5)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                    
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';

                if (*rotation == 1 && monPtr[5] -> sMony[0] != 0) //moves up
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+63, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosU == '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }
                    else if (atPosU != '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }

                }
                
                if (*rotation == 2 && monPtr[5] -> sMony[0] != 0) //moves right
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+63, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosR == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }
                    else if (atPosR != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }

                }
                
                if (*rotation == 3 && monPtr[5] -> sMony[0] != 0) //moves down
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+63, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosD == '.')
                    {
                        monPtr[i]->sMony[j] = y+1;
                        monPtr[i]->sMonx[j] = x-1;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }
                    else if (atPosD != '.')
                    {
                        monPtr[i]->sMony[j] = y-1;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }

                }
                if (*rotation == 4 && monPtr[5] -> sMony[0] != 0) //moves left
                {
                    mvaddch(monPtr[i]->sMony[j]+28, monPtr[i]->sMonx[j]+63, '.');
                    getyx(stdscr, y, x);
                    
                    getyx(stdscr, ypos, xpos);
                        
                    atPosU = mvinch(ypos - 1, xpos -1);
                    atPosR = mvinch(ypos, xpos );
                    atPosD = mvinch(ypos +1, xpos -1 );
                    atPosL = mvinch(ypos, xpos -2 );
                    
                    if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-1;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 2;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 33;
                    }
                    else if ( atPosL == '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x-2;
                
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }
                    else if (atPosL != '.')
                    {
                        monPtr[i]->sMony[j] = y;
                        monPtr[i]->sMonx[j] = x;
                        
                        mvaddch(monPtr[i]->sMony[j], monPtr[i]->sMonx[j], 'T');
                        monPtr[i]->sMony[j] = monPtr[i]->sMony[j] - 28;
                        monPtr[i]->sMonx[j] = monPtr[i]->sMonx[j] - 63;
                    }

                }
            }
        }
    }
}

void moveMonster(int *rotation, struct mon **monPtr)
{
    int i;
    int j;
    int y;
    int x;
 
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j< monPtr[i] -> wnumMon; j++)
        {
            
  ////////////////////////for room 1/////////////////////////////          
            if (i == 0)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';
                if (monPtr[0] -> monType == 'B')
                {
                    int num;
                    
                    num = Rand();

                    if (num == 1 && monPtr[0] -> wMony[0] != 0) //moves right if the random numnber is 1
                    {
                        
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }

                        
                    } 
                    else if (num == 2 && monPtr[0] -> wMony[0] != 0) //moves left if the random number generated is 2
                    {
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x - 2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        
                        
                    }
                    else if (num == 3 && monPtr[0] -> wMony[0] != 0) //moves up if the random number generated is 3
                    {
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        
                    }
                    else if (num == 4 && monPtr[0] -> wMony[0] != 0) //moves down if the random number generated is 4
                    {
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        
                        
                    } 
                }
                
                if (monPtr[0] -> monType == 'S' && (*rotation < 3) && monPtr[0] -> wMony[0] != 0)
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                    
                }
                else if (monPtr[0] -> monType =='S' && (*rotation < 5) && monPtr[0] -> wMony[0] != 0 )
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                    
                }
                
                if (monPtr[0] -> monType == 'Z' && (*rotation%2 != 0) && monPtr[0] -> wMony[0] != 0)
                {
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                    
                }
                else if (monPtr[0] -> monType == 'Z' && (*rotation%2 == 0) && monPtr[0] -> wMony[0] != 0)
                {
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                }
                
                
            }
 ///////////////////////////for room 2/////////////////////////////////////////////////////////           
            if (i == 1)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';
                if (monPtr[0] -> monType == 'B')
                {
                    int num;
                    
                    num = Rand();

                    if (num == 1) //moves right if the random numnber is 1
                    {
                        
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }

                        
                    } 
                    else if (num == 2) //moves left if the random number generated is 2
                    {
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x - 2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        
                        
                    }
                    else if (num == 3) //moves up if the random number generated is 33
                    {
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        
                    }
                    else if (num == 4) //moves down if the random number generated is 4
                    {
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        
                        
                    } 
                }
                
                if (monPtr[0] -> monType == 'S' && (*rotation < 3))
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                    
                }
                else if (monPtr[0] -> monType =='S' && *rotation < 5 )
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                    
                }
                
                if (monPtr[0] -> monType == 'Z' && (*rotation%2 != 0))
                {
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                    
                }
                else if (monPtr[0] -> monType == 'Z' && (*rotation%2 == 0))
                {
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                }
                
                
            }
 /////////////////////////////for room 3///////////////////////////           
            if (i == 2)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';
                if (monPtr[0] -> monType == 'B')
                {
                    int num;
                    
                    num = Rand();

                    if (num == 1 && monPtr[2] -> wMony[0] != 0) //moves right if the random numnber is 1
                    {
                        
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }

                        
                    } 
                    else if (num == 2 && monPtr[2] -> wMony[0] != 0) //moves left if the random number generated is 2
                    {
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x - 2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        
                        
                    }
                    else if (num == 3 && monPtr[2] -> wMony[0] != 0) //moves up if the random number generated is 63
                    {
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        
                    }
                    else if (num == 4 && monPtr[2] -> wMony[0] != 0) //moves down if the random number generated is 4
                    {
                        mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        
                        
                    } 
                }
                
                if (monPtr[0] -> monType == 'S' && (*rotation < 3) && monPtr[2] -> wMony[0] != 0)
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                    
                }
                else if (monPtr[0] -> monType =='S' && (*rotation < 5) && monPtr[2] -> wMony[0] != 0 )
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                    
                }
                
                if (monPtr[0] -> monType == 'Z' && (*rotation%2 != 0) && monPtr[2] -> wMony[0] != 0)
                {
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                    
                }
                else if (monPtr[0] -> monType == 'Z' && (*rotation%2 == 0) && monPtr[2] -> wMony[0] != 0)
                {
                    mvaddch(monPtr[i]->wMony[j]+2, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 2;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                }
                
                
            }
 ///////////////////////////////for room 4////////////////////////////           
            if (i == 3)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';
                if (monPtr[0] -> monType == 'B')
                {
                    int num;
                    
                    num = Rand();

                    if (num == 1 && monPtr[3] -> wMony[0] != 0) //moves right if the random numnber is 1
                    {
                        
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }

                        
                    } 
                    else if (num == 2 && monPtr[3] -> wMony[0] != 0) //moves left if the random number generated is 28
                    {
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x - 2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        
                        
                    }
                    else if (num == 3 && monPtr[3] -> wMony[0] != 0) //moves up if the random number generated is 3
                    {
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        
                    }
                    else if (num == 4 && monPtr[3] -> wMony[0] != 0) //moves down if the random number generated is 4
                    {
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        
                        
                    } 
                }
                
                if (monPtr[0] -> monType == 'S' && (*rotation < 3) && monPtr[3] -> wMony[0] != 0)
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                    
                }
                else if (monPtr[0] -> monType =='S' && (*rotation < 5) && monPtr[3] -> wMony[0] != 0 )
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                    
                }
                
                if (monPtr[0] -> monType == 'Z' && (*rotation%2 != 0) && monPtr[3] -> wMony[0] != 0)
                {
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                    
                }
                else if (monPtr[0] -> monType == 'Z' && (*rotation%2 == 0) && monPtr[3] -> wMony[0] != 0)
                {
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+3, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 3;
                        }
                }
                
                
            }
////////////////////////for room 5///////////////////////////////////            
            if (i == 4)
            {
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';
                if (monPtr[0] -> monType == 'B')
                {
                    int num;
                    
                    num = Rand();

                    if (num == 1 && monPtr[4] -> wMony[0] != 0) //moves right if the random numnber is 1
                    {
                        
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }

                        
                    } 
                    else if (num == 2 && monPtr[4] -> wMony[0] != 0) //moves left if the random number generated is 28
                    {
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x - 2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        
                        
                    }
                    else if (num == 3 && monPtr[4] -> wMony[0] != 0) //moves up if the random number generated is 33
                    {
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        
                    }
                    else if (num == 4 && monPtr[4] -> wMony[0] != 0) //moves down if the random number generated is 4
                    {
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        
                        
                    } 
                }
                
                if (monPtr[0] -> monType == 'S' && (*rotation < 3) && monPtr[4] -> wMony[0] != 0)
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                    
                }
                else if (monPtr[0] -> monType =='S' && (*rotation < 5) && monPtr[4] -> wMony[0] != 0)
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                    
                }
                
                if (monPtr[0] -> monType == 'Z' && (*rotation%2 != 0) && monPtr[4] -> wMony[0] != 0)
                {
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                    
                }
                else if (monPtr[0] -> monType == 'Z' && (*rotation%2 == 0) && monPtr[4] -> wMony[0] != 0)
                {
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+33, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 33;
                        }
                }
                
                
            }
 ///////////////////////////for room 6///////////////////////////////////           
            if (i == 5)
            {
                
                int ypos;
                int xpos;
                char atPosD;
                char atPosU;
                char atPosL;
                char atPosR;
                
                atPosD = '-';
                atPosU = '-';
                atPosL = '-';
                atPosR = '-';
                if (monPtr[0] -> monType == 'B')
                {
                    int num;
                    
                    num = Rand();

                    if (num == 1 && monPtr[5] -> wMony[0] != 0) //moves right if the random numnber is 1
                    {
                        
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }

                        
                    } 
                    else if (num == 2 && monPtr[5] -> wMony[0] != 0) //moves left if the random number generated is 28
                    {
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x - 2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        
                        
                    }
                    else if (num == 3 && monPtr[5] -> wMony[0] != 0) //moves up if the random number generated is 63
                    {
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        
                    }
                    else if (num == 4 && monPtr[5] -> wMony[0] != 0) //moves down if the random number generated is 4
                    {
                        mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'B');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        
                        
                    } 
                }
                
                if (monPtr[0] -> monType == 'S' && (*rotation < 3) && monPtr[5] -> wMony[0] != 0)
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosR == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosR != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                    
                }
                else if (monPtr[0] -> monType =='S' && (*rotation < 5) && monPtr[5] -> wMony[0] != 0)
                {
                    
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosL == '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x -2;
                            
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosL != '.')
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'S');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                    
                }
                
                if (monPtr[0] -> monType == 'Z' && (*rotation%2 != 0) && monPtr[5] -> wMony[0] != 0)
                {
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosU == '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosU != '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                    
                }
                else if (monPtr[0] -> monType == 'Z' && (*rotation%2 == 0) && monPtr[5] -> wMony[0] != 0)
                {
                    mvaddch(monPtr[i]->wMony[j]+28, monPtr[i]->wMonx[j]+63, '.');
                        getyx(stdscr, y, x);
                        
                        getyx(stdscr, ypos, xpos);
                        
                        atPosU = mvinch(ypos - 1, xpos -1);
                        atPosR = mvinch(ypos, xpos );
                        atPosD = mvinch(ypos +1, xpos -1 );
                        atPosL = mvinch(ypos, xpos -2 );
                        
                        if ((atPosU == '@') || (atPosR =='@') ||(atPosD == '@')||(atPosL == '@'))
                        {
                            monPtr[i]->wMony[j] = y;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if ( atPosD == '.')
                        {
                            monPtr[i]->wMony[j] = y+1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                        else if (atPosD != '.')
                        {
                            monPtr[i]->wMony[j] = y-1;
                            monPtr[i]->wMonx[j] = x-1;
                            
                            mvaddch(monPtr[i]->wMony[j], monPtr[i]->wMonx[j], 'Z');
                            monPtr[i]->wMony[j] = monPtr[i]->wMony[j] - 28;
                            monPtr[i]->wMonx[j] = monPtr[i]->wMonx[j] - 63;
                        }
                }
                
                
            }
            
            
        }
        
    }
    
}

int pickUp(char atPos, struct room **roomPtr, int *potn, int *hp)
{
    if (atPos == '+')
    {
        mvprintw(0,1,"Hero opened a door", atPos);
    }
    else if (atPos == '*' || atPos == '8')
    {
        mvprintw(0,1,"Hero picked up %c item", atPos);
    }
    else if (atPos == '!')
    {
        mvprintw(0,1,"Hero picked up %c item", atPos);
        //*potn = *potn +1;
        *hp = 50;
        mvprintw(50,1,"Health: %d, Potions: %d, Attack: %d, Inv: %d/5", *hp, *potn, 5, roomPtr[0]-> inventory);
    }
    else if (roomPtr[0]-> inventory < 5)
    {
        mvprintw(0,1,"Hero picked up %c item", atPos);
        roomPtr[roomPtr[0]-> inventory]->inInventory = atPos;
        //mvprintw(50,50,"IN INVENTORY %c", roomPtr[roomPtr[0]-> inventory]->inInventory);
        roomPtr[0]-> inventory =  roomPtr[0]-> inventory + 1;
        mvprintw(50,1,"Health: %d, Potions: %d, Attack: %d, Inv: %d/5", *hp, *potn, 5, roomPtr[0]-> inventory);        
    }
    else
    {
        mvprintw(0,1,"Hero stepped on %c, and broke it", atPos);
    }
    return (0);
}

void removeMessage()
{
    mvprintw(0,1,"                                                                                                                   ");
    
}

int Rand()
{
    int num;
    
    srand(time(NULL));
     
    num = rand()%4 + 1; //produces random number between 1-4
    
    return(num);
}

int random1()
{
    int num;
    
    srand(time(NULL));
     
    num = rand()%10 + 1; //produces random number between 1-10
    
    return(num);
}

void endGame()
{
    endwin(); // ends ncurses
}
