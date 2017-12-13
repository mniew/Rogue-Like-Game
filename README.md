# Rogue-Like-Game

**************************************
Marek Niewiadomski    
**************************************

            ***********
            Compilation
            ***********

 the program is compiled using:
  type 'make' to compile

            ******
            Usage
            ******

 To run the program enter:
    
  ./Rogue (and the arguments you would like to pass through, arguments provided can be acessed using "assests/level")
    
 The program will then run, printing out the rooms with the required icons inside including the HERO. Press q to quit or enter a stair well.
 You cannot maually use potions in this game you can regenerate your health by walking on a potion. To fight you have to intercept the monster 
 and continue moving into it. As stated in the specifications only a can start combat. If the hero dies stats will be printed to the screen.
 
![image](https://i.imgur.com/Oq409aY.png)
 
             *********
             Testing
             *********
             
Multiple test where performed to ensure the program worked consistently.
             
             TEST 1
             
13X9 de7 dw5 dn11 g4,8 M7,6 p3,4 m5,4 g1,2
18X23 de17 dw13 ds4 g17,3 M2,2 m16,6 p1,1
18X23 de4 dw9 g13,13 M3,3 p3,3 h5,6
16X12 de4 dw9 dn6 G3,8 W14,4 p9,10 e12,11 p1,1
18X23 ds4 G8,9 g6,2 p17,21 M5,5 p9,3 a8,3
18X23 de8 G6,6 z12,1 p6,6 M12,16 w6,6 a4,19

             Test 2
             
18X23 de12 dw14 dn13 h1,17 M7,9 p3,4 m17,5 g1,1
18X23 de17 dw13 ds4 g17,3 M2,2 m16,6 p1,1
18X23 de4 dw9 g13,13 M3,3 p3,3 m1,1
18X23 de4 dw9 dn6 G3,8 W14,4 p9,10 e12,11 p1,1
18X23 ds4 G8,9 g6,2 p17,21 M5,5 p9,3 a1,1
18X23 de8 G6,6 z12,1 p6,6 M12,16 w6,6 a1,1

             Test 3
             
6X6 de1 dw4 dn3 g1,5 M4,2 p5,2 m2,5 g2,2
6X6 de3 dw3 ds4 g5,3 M2,2 m7,2 p1,2
6X6 de4 dw2 g3,3 M2,3 p4,3 h1,1
6X6 de4 dw5 dn6 G3,4 W4,4 p5,5 e2,4 p1,1
6X6 ds4 G5,4 g1,2 p2,4 M4,3 p1,2 a1,1
6X6 de5 G5,5 z3,1 p4,5 M1,1 w2,1 a1,2


            *******************
             Known Limitations
            *******************
 
 Pressing any other button other then w/a/s/d or q will cause a glitch moving the cursor to an unwanted position, which is why you cannot press p to use a potion. This bug appeared after i
 implemented my movement code. If there are more then one monster ina room they will both die if the other dies in combat. 
 
            ***********
            References
            ***********
        
 The code for moving was derived from code used in my lab.
 
 The lectures lead by Justin Carvalho also provided code examples for drawing rooms.
