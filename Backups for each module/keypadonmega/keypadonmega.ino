#include "Keypad.h"
#include "SPI.h"
#include "MFRC522.h"
#include "String.h"
#define SS_PIN 9
#define RST_PIN 8
String Key;
byte var;
const byte Rows= 4; //number of rows on the keypad i.e. 4
const byte Cols= 4; //number of columns on the keypad i,e, 3
char pass[3];
int i=0;
String iotpass="1234";
char key_pressed = 0; // Variable to store incoming keys
//we will definne the key map as on the key pad:
String strID = "";



MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

char keymap[Rows][Cols]=
{
{'1', '2', '3','A'},
{'4', '5', '6','B'},
{'7', '8', '9','C'},
{'*', '0', '#','D'}
};

//  a char array is defined as it can be seen on the above

char pass[3];
int i=0;
String iotpass="1234";
char key_pressed = 0;
//keypad connections to the arduino terminals is given as:

byte rPins[Rows]= {A4,A5,A6,A7}; //Rows 0 to 3
byte cPins[Cols]= {A0,A1,A2,A3}; //Columns 0 to 2

// command for library forkeypad
//initializes an instance of the Keypad class
Keypad kpd= Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);

void setup()
{
     Serial.begin(9600);  // initializing serail monitor
     SPI.begin();
     rfid.PCD_Init();
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
void loop()
{

Rfid();
if(strID=="65:C4:EB:1F")
{
  Serial.println("asv is here"); 
  action();
}
else
{
  Serial.println("this is not asv");
  Serial.println("please enter the key: ");
  Key=keyPad();
  if (Key==iotpass)//this should be variable because it will get from IOT
  {
    Serial.println("accessed!");
    digitalWrite(LED_BUILTIN,HIGH);delay(500);digitalWrite(LED_BUILTIN,LOW);delay(500);
    delay(1000);
    action(); 
  }
}

}
String keyPad()
{
    while( i<4){
      key_pressed=  kpd.getKey();
         if(key_pressed!=NULL){
        pass[i++]=key_pressed;
        Serial.print(key_pressed);
        key_pressed==NULL;
        
         } 
       }
      Serial.print("...........");
      Serial.println(pass);
      return pass;
      /*delay(1000);
          if(iotpass.equals(pass)){
            Serial.println("hi vinay");
          }
          else{
          Serial.println("sorry");
}*/
}
void Rfid()
{while(1){
   if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
  Serial.println("Tap card key: ");
  Serial.println(strID);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  Serial.println("stage pass");
  break;
 /* if (strID=="54:C0:20:3B")
  {
    Serial.println("welcome vidya balan");
     Serial.print("enter the student no: ");
     
  }
  else
  {
    Serial.println("you nibba, not allowed");
  }*/
 }
 }
void action(){
  Serial.println("welcome you are ready to do furthr programming");
delay(1000);
return;
}
