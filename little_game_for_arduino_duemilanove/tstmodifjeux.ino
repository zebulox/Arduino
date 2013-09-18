/* Programme : little_game_for_arduino_duemilanove                             
/*                                                                         
/* Objective : creating a little game with animations with an                                          
/*             arduino duemilanove and a TFT Touch Shield (ITDB32).                                                          
/* Autor    : Hadrien Grimont                   
/* Date      : 02/07/2013                                         
/* Version   : Version initiale v0.3                                   
/*******************************************/

//TODO -> make a counter function and display de player score.
//     -> redefine player's hitbox.

#include <UTFT.h>
#include <UTouch.h>
#include "imagesLibrary.h"

//declaring which sreen is used.
UTFT myGLCD(ITDB32S,38,39,40,41);   
UTouch      myTouch(6,5,4,3,2);


int posx = 100;//the x position of the sprite.
int posy = 163;//the y position of the sprite.
int compt = 1;//is the number of the corresponding sprite for player we have to draw.
int apparitionbebette = 0; //flag used to know if a "monster" is already on the screen or not.
int posbebettex, posbebettey;//the positions of the "monster".
int chute = 1;//flag used to know if a "monster" is falling or not.


/*
/* homemade function which manage the "monster" behaviour (i.e. random spawning, falling, vanishing)
*/
void gestionbebettes()
{
  if(apparitionbebette == 0)//if there is no "monster" on the screen.
  {
    posbebettex = random(15, 220);//randomly set the x position (15, 220) are the game screen limits.
    posbebettey = 0;//set the y position to top.
    apparitionbebette = 1;//let us know there is a "monster" on the screen.
  }
  else//if there is already a "monster".
  {
     if(posbebettey < 180) //if the "monster" is not on the ground (i.e. falling).
     {
       posbebettey +=5;//we make it fall.
       myGLCD.drawBitmap(posbebettex, posbebettey, 20, 20, bebette);//we draw the "monster" on the screen.
     }
     else //if the "monster" is on the ground.
     {
         apparitionbebette = 0; //we make it desapear.
         myGLCD.drawBitmap(posbebettex-posbebettex%60, posbebettey-18, 60, 45, black);//fill the anciens "monster" position with black.
     }
  }
  
  
}

//initializing function.
void setup()
{
  myGLCD.InitLCD();//initializing screen.
  myGLCD.clrScr();// clear screen in order to avoid unwanted prints.

  myTouch.InitTouch();//initializing the touch functionality.
  myTouch.setPrecision(PREC_MEDIUM);//setting the touch precision.  
}

/*
/* homemade function which manage the initialization of the game
*/

void initjeux()
{
  myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja1);//display the player 's sprite.
  myGLCD.setColor(200, 200, 200);// background color (dark grey).
  myGLCD.drawRoundRect(241, 0, 319, 199);//filling the background with dark grey.
  
  for(int i = 0; i<8; i++)//loop used for drawing the floor
  {
      myGLCD.drawBitmap(i*40, 200, 40, 40, brique);
  }
  myGLCD.drawBitmap(280, 200, 40, 40, flecheD);//adding the control panel (wich is 2 arrows for mouvement) 
  myGLCD.drawBitmap(240, 200, 40, 40, flecheG);
}

//MAIN FUNCTION
void loop()
{
  int i;
  long temps;
  int x, y;//used for the data capture.
  int points = 0;//not used yet but i plan to add a counter.
  
  int flagflip = 0;//flag used to know if the player is going right or left in order to draw appropriate sprite 0 -> right srites (n°1->7) 1-> left sprites (n°8->14).
  
  //calling the initializing function.
  initjeux();
  
  delay(100);
  
  while(true)
 {    
      //calling the monster's managing function.
      //there is a call here because if not until the player is touching the creen nothing will happen.
      gestionbebettes();
      //while the player is sending data (i.e. touching the creen)
      while (myTouch.dataAvailable() == true)
      {
        delay(42);
        
        //saving the position where the screen is touched.
        myTouch.read();
        x = myTouch.getX();
        y = myTouch.getY();
        
        //calling the monster's managing function.
        gestionbebettes();
        
        if((x>240)&&(x<280)&&(y>200)&&(y<240))//the left arrow.
        {
          if(posx>0)//if player is not on the left limit of the screen.
          {
             posx-=10;//we make the sprite move.
             flagflip = 1;//we know that this is a left type sprite.
             
             if((compt>7)&&(compt<14))//if we already are in the left type sprites.
             {
               compt++;//next sprite.
             }
             
             else if(compt == 14)//if we are at the 14 sprite.
             {
               compt=8;//go back to the 8 which is the first of the seven frames for the animation.
             }
             
             else if(compt<8)//if we displayed a right movement sprite juste changing it to te corresponding left movement sprite (it will just flip the sprite).
             {
               compt+=7;
             }
          }
        }
        
        if((x>280)&&(x<320)&&(y>200)&&(y<240))//the right arrow.
        {
           if(posx<180)//if player is not on the right limit of the screen.
          {
             posx+=10; //we make the sprite move.
             flagflip = 0;//we know that this is a right type sprite.
             
             if((compt>0)&&(compt<7))//if we already are in the right type sprites.
             {
               compt++;//next sprite.
             }
             
             else if(compt == 7)//if we are at the 7 sprite.
             {
               compt=1;//go back to the first
             }
             
             else if(compt>7)//if we displayed a left movement sprite juste changing it to te corresponding right movement sprite (it will just flip the sprite).
             {
               compt-=7;
             }
          }
        }
        
        if((posx +50 < posbebettex)&&(posx-10 > posbebettex))//hit box definition (i have to work on it as it seems a little buggy) 
        {
          if(posbebettey > 100)//to of player's head
          {
              points++;//adding a point to player's score.
              apparitionbebette = 0;//we make the monster desapear.
          }
        }
        
        //drawing player's sprite and clearing the ancient position of the player's sprite.
        switch (compt)
        {
           case 1:
              myGLCD.drawBitmap(posx-10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja1);
           break; 
           
           case 2:
              myGLCD.drawBitmap(posx-10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja2);
           break;
           
           case 3:
              myGLCD.drawBitmap(posx-10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja3);
           break;
           
           case 4:
              myGLCD.drawBitmap(posx-10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja4);
           break;
           
           case 5:
              myGLCD.drawBitmap(posx-10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja5);
           break;
           
           case 6:
              myGLCD.drawBitmap(posx-10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja6);
           break;
           
           case 7:
              myGLCD.drawBitmap(posx-10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja7);
           break;
           
           case 8:
              myGLCD.drawBitmap(posx+10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja8);
           break;
           
           case 9:
              myGLCD.drawBitmap(posx+10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja9);
           break;
           
           case 10:
              myGLCD.drawBitmap(posx+10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja10);
           break;
           
           case 11:
              myGLCD.drawBitmap(posx+10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja11);
           break;
           
           case 12:
              myGLCD.drawBitmap(posx+10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja12);
           break;
           
           case 13:
              myGLCD.drawBitmap(posx+10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja13);
           break;
           
           case 14:
              myGLCD.drawBitmap(posx+10, posy-1, 60, 45, black);
              myGLCD.drawBitmap(posx, posy, 60, 44, ninjaja14);
           break;
        }
        
      }  

 }  

}
