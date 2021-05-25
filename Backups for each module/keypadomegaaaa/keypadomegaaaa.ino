#include "Keypad.h"
int kei=0;
const byte Rows= 4; //number of rows on the keypad i.e. 4
const byte Cols= 4; //number of columns on the keypad i,e, 3
char   key_pressed;
//we will definne the key map as on the key pad:
char  kepass[3];
String iotpass="1234";
char keymap[Rows][Cols]=
{
{'1', '2', '3','A'},
{'4', '5', '6','B'},
{'7', '8', '9','C'},
{'*', '0', '#','D'}
};

//  a char array is defined as it can be seen on the above


//keypad connections to the arduino terminals is given as:

byte rPins[Rows]= {A4,A5,A6,A7}; //Rows 0 to 3
byte cPins[Cols]= {A0,A1,A2,A3};

// command for library forkeypad
//initializes an instance of the Keypad class
Keypad kpd= Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);

void setup()
{
     Serial.begin(9600);  // initializing serail monitor
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
void loop()
{
  kepass=="";
  Serial.println("repeat");
  kei=0;
    while( kei<4){
      
      key_pressed=  kpd.getKey();
         if(key_pressed!=NULL){
        kepass[kei++]=key_pressed;
        Serial.print(key_pressed);
        key_pressed==NULL;
        
         } 
       }
      Serial.print("...........");
      Serial.println(kepass);
    
      if (iotpass.equals(kepass))
      {
        Serial.println("hi bonda");
      }
      else 
      {
        Serial.println("naa bonda");
      }
}
