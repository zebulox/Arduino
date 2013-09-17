/*******************************************/
/* Programme : Paint_for_arduino_duemilanove                             
/*                                                                         
/* Objective : creating a small paint like app with an                                          
/*             arduino duemilanove and a TFT Touch Shield (ITDB32).                                                          
/* Autor    : Hadrien Grimont                   
/* Date      : 01/07/2013                                         
/* Version   : Version initiale v0.1                                   
/*******************************************/

#include <UTFT.h>
#include <UTouch.h>

//declaring which sreen is used.
UTFT myGLCD(ITDB32S,38,39,40,41);   
UTouch      myTouch(6,5,4,3,2);

//you can put unsigned short tools[0x17C] and unsigned short chromatique[0x190] in differents files (.C source files not .ino files)
//just remember to include them in the source code.

//the bitmap corresponding to the tools icon.
unsigned short tools[0x17C] ={
0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xA534, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE79, 0x8C92, 0x7BCF, 0x8C71, 0xAD75, 0xEF5D, 0xFFFF, 0xFFFF,   // 0x0010 (16)
0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x7BCF, 0xDEDB, 0x8C71, 0xC638, 0xFFFF, 0xC618, 0xB5B6, 0x8410, 0x31A6,   // 0x0020 (32)
0x5B2C, 0x7C10, 0xB5B6, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x9CD3, 0x9D13, 0xDEFB, 0xB595, 0x9492,   // 0x0030 (48)
0xFFFF, 0xFFFF, 0xFFFF, 0xD6BA, 0x3A08, 0x5B0C, 0x8C51, 0xB596, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x73AE, 0xEF7D, 0xFFFF,   // 0x0040 (64)
0x9CD3, 0xA534, 0xD6DA, 0xB596, 0xCE79, 0xFFFF, 0xFFFF, 0xFFFF, 0x8C71, 0x1904, 0x632C, 0x8C51, 0xB5B6, 0xFFFF, 0xFFFF, 0xFFFF,   // 0x0050 (80)
0x9492, 0xE73C, 0x738E, 0xF79E, 0xEF7D, 0x8410, 0xBDF7, 0x9CF3, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0x8430, 0x4A8A, 0x1924, 0x632C,   // 0x0060 (96)
0x8431, 0xCE79, 0xFFFF, 0xFFFF, 0xD6BA, 0xBDF7, 0xE71B, 0x7BEF, 0x8430, 0xB5D6, 0xAD75, 0x8430, 0xFFFF, 0xFFFF, 0xFFFF, 0xBDD7,   // 0x0070 (112)
0xBDF7, 0xA555, 0x52AA, 0x1924, 0x632C, 0x8430, 0xFFFF, 0xFFFF, 0xFFFF, 0x9CF3, 0xE71C, 0xE71C, 0xDEDA, 0xCE59, 0xBDF7, 0x9CF3,   // 0x0080 (128)
0xA535, 0xFFFF, 0xBDD7, 0xB595, 0xFFDE, 0xDEFA, 0x7BCF, 0x4A8A, 0x2165, 0x634D, 0x6B6D, 0xBDF7, 0xFFFF, 0xFFFF, 0x8C71, 0xC638,   // 0x0090 (144)
0x94B2, 0x840F, 0xBDD6, 0xC618, 0xAD54, 0x6B6D, 0xB5D6, 0xF7DE, 0xD6B9, 0x9492, 0xF79E, 0xF79E, 0x6B8E, 0x2145, 0x632D, 0x7BEF,   // 0x00A0 (160)
0xFFFF, 0xFFFF, 0xEF5D, 0xBDF7, 0xEF7D, 0xFFFF, 0x8C30, 0x9CD2, 0x6B4D, 0xBDD6, 0xFFDE, 0xD6DA, 0x8C71, 0xFFFF, 0xFFFF, 0xFFFF,   // 0x00B0 (176)
0x5ACB, 0x1904, 0x4A69, 0xEF7D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE38, 0x3AAF, 0x4BD6, 0xC67B, 0xE71B, 0x5289,   // 0x00C0 (192)
0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xBDF7, 0x738E, 0xEF5D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xC617, 0x4B52, 0x7CD8,   // 0x00D0 (208)
0x4352, 0x11CD, 0x4249, 0x73AE, 0x9492, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,   // 0x00E0 (224)
0xBDD6, 0x4352, 0x7CD8, 0x4352, 0x19ED, 0x19CB, 0x5AEB, 0xBDF7, 0xAD75, 0x8430, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,   // 0x00F0 (240)
0xFFFF, 0xFFFF, 0xFFFF, 0xBD95, 0x4353, 0x7CF8, 0x4352, 0x19ED, 0x19CB, 0x8C50, 0x8C50, 0xCE79, 0xBDD6, 0xAD95, 0x840F, 0xFFFF,   // 0x0100 (256)
0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xB575, 0x4353, 0x7CF8, 0x4352, 0x19ED, 0x19AB, 0x8C51, 0xFFFF, 0xEF5D, 0x7BCE,   // 0x0110 (272)
0xCE59, 0xBDD6, 0xB595, 0x7BEF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xAD34, 0x4373, 0x7CF9, 0x4353, 0x19ED, 0x19AB, 0x7C10,   // 0x0120 (288)
0xFFFF, 0xFFFF, 0xFFFF, 0xDEFC, 0x7BEF, 0xCE79, 0xBDD6, 0xB595, 0x7BCF, 0xF7BE, 0xFFFF, 0xFFFF, 0xD678, 0x4353, 0x8519, 0x4B53,   // 0x0130 (304)
0x1A0D, 0x11AB, 0x73CF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xD6BA, 0x8410, 0xCE79, 0xB5D6, 0xB5D6, 0x7BEF, 0xF79E, 0xFFFF,   // 0x0140 (320)
0xEF3C, 0x4B51, 0x4353, 0x19ED, 0x118B, 0x6B8E, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xCE59, 0x8430, 0xD699,   // 0x0150 (336)
0x9CD3, 0x9CF3, 0x9CD3, 0xFFFF, 0xFFFF, 0xDEDA, 0x3A6D, 0x118B, 0x634D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,   // 0x0160 (352)
0xFFFF, 0xFFFF, 0xC618, 0x9491, 0xA554, 0x9CD3, 0xAD55, 0xFFFF, 0xFFFF, 0xFFFF, 0xEF5C, 0xB595, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,   // 0x0170 (368)
};

//the bitmap corresponding to the color chart icon.
unsigned short chromatique[0x190] ={
0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFBF, 0xFF5F, 0xFE7D, 0xFD5A, 0xFCB7, 0xFC53, 0xFC52, 0xFCB2, 0xFD94, 0xFED9, 0xFFBC, 0xFFDD,   // 0x0010 (16)
0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFF9F, 0xFE7E, 0xE4B7, 0xF497, 0xFC36, 0xFB92, 0xFB0F, 0xFAEC, 0xFB8D,   // 0x0020 (32)
0xFCD1, 0xF531, 0xE572, 0xFF39, 0xFFDD, 0xFFFE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFF7F, 0xFDBE, 0xF45A, 0xFBD8, 0xEA91, 0xE9CD,   // 0x0030 (48)
0xF9CC, 0xFA0B, 0xF9E8, 0xFA07, 0xEAC8, 0xE369, 0xFD4F, 0xFE33, 0xF695, 0xFFBB, 0xFFFE, 0xFFFF, 0xFFDF, 0xFF9F, 0xFDDF, 0xF43C,   // 0x0040 (64)
0xFB3A, 0xF215, 0xF9D2, 0xF94E, 0xE8A9, 0xE886, 0xE042, 0xE0C1, 0xF244, 0xF326, 0xE386, 0xECCB, 0xFEB2, 0xFF57, 0xFFFC, 0xFFFE,   // 0x0050 (80)
0xFFBF, 0xFE9F, 0xF49F, 0xFB5E, 0xF1F9, 0xF9B8, 0xE872, 0xE84F, 0xE84B, 0xE046, 0xD862, 0xE942, 0xE1A0, 0xFB23, 0xF3C5, 0xF487,   // 0x0060 (96)
0xFE2D, 0xFEF2, 0xFFB9, 0xFFFD, 0xFF5F, 0xD49C, 0xF3FF, 0xE23D, 0xF9FE, 0xE898, 0xE075, 0xD010, 0xC00A, 0xB805, 0xB000, 0xB8A0,   // 0x0070 (112)
0xDA00, 0xF362, 0xFC83, 0xFDA7, 0xEDA7, 0xFEEE, 0xFFB6, 0xFFFA, 0xFE9F, 0xDC7E, 0xC27D, 0xD1DF, 0xD89D, 0xD87C, 0xC836, 0xB010,   // 0x0080 (128)
0xA00A, 0x9004, 0x9000, 0xA920, 0xBA80, 0xC380, 0xFDC2, 0xF5E1, 0xFF47, 0xFFAC, 0xFFD2, 0xFFF7, 0xE53F, 0xD45F, 0xA9FD, 0xB15F,   // 0x0090 (144)
0xB01D, 0xB83B, 0xA036, 0x8830, 0x7009, 0x6804, 0x7040, 0x70E0, 0x9280, 0xB440, 0xDDE0, 0xFFA4, 0xFFC6, 0xFFEA, 0xF7F0, 0xF7F3,   // 0x00A0 (160)
0xD4BF, 0xAB3E, 0x899D, 0x809C, 0x907D, 0x8019, 0x7014, 0x600F, 0x5029, 0x3802, 0x3800, 0x5980, 0x7300, 0xAD22, 0xADA0, 0xE7C4,   // 0x00B0 (176)
0xCF83, 0xCFA6, 0xD7CC, 0xE7F1, 0xC47F, 0x9B5F, 0x81DF, 0x609C, 0x607C, 0x4818, 0x4013, 0x380E, 0x2007, 0x1802, 0x2060, 0x2960,   // 0x00C0 (192)
0x5BA1, 0x6480, 0x7DC0, 0xB7E3, 0xB7E4, 0xB7E6, 0xC7EC, 0xD7F0, 0xAC5F, 0x82FE, 0x61FF, 0x281B, 0x303B, 0x2017, 0x1812, 0x100E,   // 0x00D0 (208)
0x0007, 0x0043, 0x0080, 0x0960, 0x2B60, 0x3460, 0x4DC0, 0x7762, 0x77A2, 0x87A5, 0xA7AB, 0xC7F1, 0xACBF, 0x839F, 0x5A1F, 0x209C,   // 0x00E0 (224)
0x185B, 0x0818, 0x0013, 0x002E, 0x00EB, 0x0126, 0x01A3, 0x0281, 0x0380, 0x2520, 0x1DA0, 0x5FC3, 0x67E5, 0x77E8, 0x9FEE, 0xBFF2,   // 0x00F0 (240)
0xBD9F, 0x8BFF, 0x399C, 0x295E, 0x0019, 0x0079, 0x0136, 0x0172, 0x01CE, 0x130E, 0x0348, 0x0383, 0x0461, 0x0DA0, 0x1680, 0x3FE3,   // 0x0100 (256)
0x47A4, 0x67A8, 0x9FF0, 0xBFF4, 0xD69F, 0x8C7E, 0x4A7C, 0x3A3F, 0x113C, 0x09BD, 0x01D8, 0x02B6, 0x0B95, 0x0C52, 0x048C, 0x0529,   // 0x0110 (272)
0x05A5, 0x0602, 0x1F83, 0x1F41, 0x4FE7, 0x6FCB, 0xA7D2, 0xCFF7, 0xF7DF, 0x845A, 0x847F, 0x329C, 0x2ABF, 0x0A5D, 0x13DF, 0x041B,   // 0x0120 (288)
0x0497, 0x0595, 0x05B0, 0x05AB, 0x06CA, 0x1788, 0x1F85, 0x37C5, 0x4FA8, 0x7FAE, 0xB7D5, 0xE7FB, 0xF7FF, 0xD71F, 0x8D1E, 0x641E,   // 0x0130 (304)
0x331C, 0x33DF, 0x03BD, 0x1DBF, 0x169E, 0x27BD, 0x1F97, 0x1792, 0x17AE, 0x178A, 0x2FC9, 0x47C9, 0x6FAD, 0x9791, 0xCFF9, 0xEFFC,   // 0x0140 (320)
0xF7FF, 0xF7FF, 0xAE1D, 0x957F, 0x6CBE, 0x239A, 0x3D5F, 0x1D9E, 0x26FF, 0x279C, 0x1FB6, 0x1FD2, 0x27CF, 0x3FEE, 0x47AC, 0x67AE,   // 0x0150 (336)
0x97B3, 0xBFD7, 0xE7FC, 0xF7FD, 0xFFFF, 0xF7FF, 0xF7FF, 0xBE9F, 0x95FF, 0x7DFF, 0x55BF, 0x359C, 0x57DF, 0x3FFD, 0x3FF8, 0x47F5,   // 0x0160 (352)
0x3F91, 0x57B1, 0x77D2, 0x97F5, 0xBFD8, 0xE7FC, 0xF7FE, 0xF7FE, 0xFFDF, 0xFFFF, 0xFFFF, 0xF7FF, 0xCF5F, 0xA69E, 0x96DF, 0x7F3F,   // 0x0170 (368)
0x6FBF, 0x6FFF, 0x67DB, 0x6FF9, 0x87F8, 0x97D8, 0xA797, 0xCFFA, 0xE7FD, 0xEFFE, 0xF7FE, 0xF7FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,   // 0x0180 (384)
0xEFFF, 0xE7FF, 0xBFFF, 0xA7DF, 0x8FFF, 0x7FFF, 0x7FFD, 0x8FFC, 0x9FFB, 0xBFFD, 0xE7FE, 0xEFFE, 0xF7FE, 0xEFFE, 0xF7FE, 0xFFFF,   // 0x0190 (400)
};

//initializing function 
void setup()
{
  //initializing display screen
  myGLCD.InitLCD();
  //clear the screen to avoid unwanted print
  myGLCD.clrScr();
    
  //initializing touch capture 
  myTouch.InitTouch();
  //setting capture precision
  myTouch.setPrecision(PREC_MEDIUM);
  //filling screen with dark grey fillScr(<R>, <G>, <B>) where R, G and B >=0, <= 255.
  myGLCD.fillScr(100, 100, 100);
}

/*
* homemade function which display : - a color chart used for picking differents colors for drawing.
*                                   - surrounding color chart and drawing zone with a white square.
*                                   - drawing the tools and color chart icons.
*/
void initcouleurs()
{
  int i ;


 for(i = 0; i<50; i++)
{
   myGLCD.setColor (i*5,0,0);//adding red.
   myGLCD.drawLine(i, 0, i, 40);//drawing the new color in a new line next to the previous one.
} 

 for(i = 0; i<50; i++)
{
   myGLCD.setColor (255,i*5,0); // red maxed adding green.
   myGLCD.drawLine(i+50, 0, i+50,40);
} 
 for(i = 0; i<50; i++)
{
   myGLCD.setColor (255-(i*5),255,0);//green maxed decreasing red.
   myGLCD.drawLine(i+100, 0, i+100,40);
} 

 for(i = 0; i<50; i++)
{
   myGLCD.setColor (0,255,i*5);//green maxed increasing blue.
   myGLCD.drawLine(i+150, 0, i+150,40);
}

 for(i = 0; i<50; i++)
{
   myGLCD.setColor (0,255-(i*5),255);//blue maxed decreasing green.
   myGLCD.drawLine(i+200, 0, i+200,40);
}

 for(i = 0; i<50; i++)
{
   myGLCD.setColor (i*5,0,255);//blue maxed increasing red.
   myGLCD.drawLine(i+250, 0, i+250,40);
}

myGLCD.setColor (255,255,255);//white color
myGLCD.drawRoundRect(1, 40, 319, 239);//surrounding both color chart and drawing zone with a white square.
myGLCD.drawRoundRect(2, 41, 318, 238);

myGLCD.drawBitmap(300, 0, 20, 19, tools);//drawing the tool icon.
myGLCD.drawBitmap(300, 20, 20, 20, chromatique);//drawing the color chart icon. 
}

/*
* homemade function which display the tools section.
*/
void inittools()
{
  /*TODO FUNCTIONS*/
  /*
    drawLine(x1, y1, x2, y2);
    drawRect(x1, y1, x2, y2);
    drawRoundRect(x1, y1, x2, y2);
    fillRect(x1, y1, x2, y2);
    fillRoundRect(x1, y1, x2, y2);
    drawCircle(x, y, radius); 
    fillCircle(x, y, radius);
    
    en garder 6 maximum -> enlever le draw ligne qu'il est possible d'obtenir avec drawRect?
    
    faire des "boites" de 50X40 représentant les fonctions.
  */
  int i;
  
  //drawing 6 white boxes where we will put all our tools.
  myGLCD.setColor (255,255,255);

  //TODO make a single for loop.
  myGLCD.drawRoundRect(1  ,1,49 ,40);
  myGLCD.drawRoundRect(51 ,1,100,40);
  myGLCD.drawRoundRect(101,1,150,40);
  myGLCD.drawRoundRect(151,1,200,40);
  myGLCD.drawRoundRect(201,1,250,40);
  myGLCD.drawRoundRect(251,1,300,40);
  
  //drawing a green rect.
  myGLCD.setColor (0,255,0);  
  myGLCD.drawRect(6, 6, 45, 35);
  //drawing a blue roundrect.
  myGLCD.setColor (0,0,255); 
  myGLCD.drawRoundRect(56, 6, 95, 35);
  //drawing a turquoise filled rect.
  myGLCD.setColor (0,255,255);
  myGLCD.fillRect(106, 6, 145, 35);
  //drawing a purple filled roundrect.
  myGLCD.setColor (255,0,255); 
  myGLCD.fillRoundRect(156, 6, 195, 35);
  //drawing a yellow circle.
  myGLCD.setColor (255,255,0); 
  myGLCD.drawCircle(225, 20, 15);
  //drawing a red filled circle.
  myGLCD.setColor (255,0,0); 
  myGLCD.fillCircle(275, 20, 15);
  
  
  //surrounding both color chart and drawing zone with a white square.
  myGLCD.setColor (255,255,255);
  myGLCD.drawRoundRect(1, 40, 319, 239);
  myGLCD.drawRoundRect(2, 41, 318, 238);
  
  //drawing tools and color chart icons.
  myGLCD.drawBitmap(300, 0, 20, 19, tools); 
  myGLCD.drawBitmap(300, 20, 20, 20, chromatique); 
}

/*
* Home made function which draw the selected shape in the tools section at the coord fixed by the user
* where int type is the selected shape
*/
void fdrawform(int type)
{
 int x1,y1,x2,y2;//used to define the shape's position where (x1, y1) is the start position and (x2, y2) the ending position 
 x1=0; 
 x2=0; 
 y1=0; 
 y2=0;
 
 //adding a timer between to data capture
 //preventing the case x1=x2 and y1=y2 
 delay(250);
 
 while(x2==0)
 {
     // while the screen can send data (i.e. the screen is touched).
     while(myTouch.dataAvailable() == true)
     {
       myTouch.read();
       //checking if the data are the first position of the shape 
       if(x1 == 0)
       {
          x1 = myTouch.getX();//saving the position selected by user
          y1 = myTouch.getY();
          delay(250);
       }
       //if this is not the first position saving data in the "coord" 2
       else
       {
          x2 = myTouch.getX();
          y2 = myTouch.getY();  
       }
      }
 }
 //cheking type shape selected and drawing the good one in the selected coord
 if(type == 0)
 {
   myGLCD.drawRect(x1, y1, x2, y2);
 }
 else if(type == 1)
 {
   myGLCD.drawRoundRect(x1, y1, x2, y2);
 }
  else if(type == 2)
 {
   myGLCD.fillRect(x1, y1, x2, y2);
 }
  else if(type == 3)
 {
   myGLCD.fillRoundRect(x1, y1, x2, y2);
 }
  else if(type == 4)
 {
   myGLCD.drawCircle(x1, y1,sqrt(pow(x2-x1,2)+pow(y2-y1,2)));
 }
  else if(type == 5)
 {
   myGLCD.fillCircle(x1, y1,sqrt(pow(x2-x1,2)+pow(y2-y1,2)))  ;
 }
}

/*
* MAIN FUNCTION
*/
void loop()
{
  long x, y;
  int groupecolor, tools;
  int r, g, b, i;

  tools = 0;//color chart will be displayed.

  //display color chart.
  initcouleurs();
  
        //main loop 
       while(true)
       {
         while (myTouch.dataAvailable() == true)
        {
          myTouch.read();
          x = myTouch.getX();
          y = myTouch.getY();
          if ((x!=-1) and (y!=-1))
          {
            if(y<51)//if user is selecting a color or a shape
            {
                groupecolor = x/50;//it will allow us to know the color type or the shape selected 
                
                switch(groupecolor)
                {
                  case 0:
                        if(tools == 0)//if we are in the color chart 
                        {
                            r = x*5;
                            g = 0;
                            b = 0;
                        }
                        else//we are in the tools section
                        {
                          delay(250);
                          //here groupecolor is actually the shape number
                          fdrawform(groupecolor);
                        }
                  break; 
                  
                  case 1:
                        if(tools == 0)
                        {
                            r = 255;
                            g = (x-50)*5;
                            b = 0;
                        }
                        else
                        {
                            delay(250);
                          fdrawform(groupecolor);
                        }
                  break;
                  
                  case 2:
                        if(tools == 0)
                        {
                            r = 255-((x-100)*5);
                            g = 255;
                            b = 0;
                        }
                        else
                        {
                            delay(250);
                          fdrawform(groupecolor);
                        }
                  break;
                  
                  case 3:
                        if(tools == 0)
                        {
                            r = 0;
                            g = 255;
                            b = (x-150)*5;
                        }
                        else
                        {
                            delay(250);
                          fdrawform(groupecolor);
                        }
                  break;
                  
                  case 4:
                        if(tools == 0)
                        {
                            r = 0;
                            g = 255-((x-200)*5);
                            b = 255;
                        }
                        else
                        {
                            delay(250);
                          fdrawform(groupecolor);
                        }
                  break;
                  
                  case 5:
                        if(tools == 0)
                        {
                            r = (x-250)*5;
                            g = 0;
                            b = 255;
                        }
                        else
                        {
                            delay(250);
                          fdrawform(groupecolor);
                        }
                  break;
                  
                  case 6://if groupecolor == 6 user has switch between color chart and tools section .
                        if(tools == 0)//if we are in the color chart.
                        {
                           inittools();//displaying the tools section.
                           delay(250);//avoiding quick switch between menus.
                           tools = 1;//setting the "toolIsSelected" flag to one.
                           
                        }
                        else if (tools == 1)//if we are in the tools section
                        {
                          
                          initcouleurs();//displaying the color chart.
                          delay(250);//avoiding quick switch between menus.
                          tools = 0;//setting the "toolIsSelected" flag to zero.
                        }
                  break;
                  
                  default://in the delault case we are defining the drawing color to white
                      r=255;
                      g=255;
                      b=255;
                  break;
                }
                
                //setting the drawing color with the user's selected color (in case where the user is selecting a shape it will draw it with the last selected color).
                myGLCD.setColor (r,g,b);      
            }//end of the switch.
            
            //if the user is in the drawing zone 
            if(y>41)
            {
              //draw a pixel where he want with le last selected color
              //there is no delay here in order to allow user to draw continuous lines.
              myGLCD.drawPixel (x, y);
            }
          }
        }
      }
}

