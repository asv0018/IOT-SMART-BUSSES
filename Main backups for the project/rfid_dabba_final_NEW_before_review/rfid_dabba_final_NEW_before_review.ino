#include "SPI.h"
#include "MFRC522.h"
#include<String.h>
#include<SD.h>
#include <Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);
#define SS_PIN 9
#define RST_PIN 8
int temp=1;
String rfidvalue;
const int chipSelect=4;
File file;
int ci;
char bt[9];char tem;
int i=0;
int len,leni=0;
char tempchar;
char iotname[300];
/////////////////////////////////
#include "Keypad.h"
int kei=0;
const byte Rows= 4; //number of rows on the keypad i.e. 4
const byte Cols= 4; //number of columns on the keypad i,e, 3
char   key_pressed;
//we will definne the key map as on the key pad:
char  kepass[5];
char optkey[0];
String iotpass="1234";
String optchar="#";
char keymap[Rows][Cols]=
{
{'1', '2', '3','A'},
{'4', '5', '6','B'},
{'7', '8', '9','C'},
{'*', '0', '#','D'}
};

//  a char array is defined as it can be seen on the above


//keypad connections to the arduino terminals is given as:

byte rPins[Rows]= {A0,A1,A2,A3}; //Rows 0 to 3
byte cPins[Cols]= {A4,A5,A6,A7};

// command for library forkeypad
//initializes an instance of the Keypad class
Keypad kpd= Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);

////////////////////////////////
int rfi=1;
MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key rfkey;

void setup() {
  Serial.begin(9600);
  SPI.begin();lcd.begin(20,4);
  rfid.PCD_Init();
   Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}
void loop() {
  
  char var=keypod();
  switch(var)
{
  case 'A':
  Serial.println("A is pressed \n this opens normal program");
   while(1){
   pseudoloop();}
  break;
  case 'B':
  Serial.println("B p");
  while(1){
  stdadd();
  }
  break;
  case 'C':
  Serial.println("C p");
  break;
  case 'D':
  Serial.println("D p");
  break;
  }
  
}
void pseudoloop(){
   if( rfi!=0){
    rf();
  }
}
void rf(){
  
  lcd.setCursor(2,0);
  lcd.print("welcome student");
  lcd.setCursor(1,2);
  lcd.print("place the id card");
  //Serial.println("welcome student");
//Serial.println("place the id card");
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

  String strID = "";
  for (byte rfi = 0; rfi < 4; rfi++) {
    
    strID +=
    (rfid.uid.uidByte[rfi] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[rfi], HEX) +
    (rfi!=3 ? "" : "");
  }
  strID.toUpperCase();
//not reqd Serial.println("place the card");
// thMis too lcd.setCursor(3,0);
// this as well lcd.print("place the card");

 Serial.print("Tap card rfkey: ");
  Serial.println(strID);
strID.concat(".txt");
Serial.print("this is concated file name: ");Serial.println(strID);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  if (SD.exists(strID))
  {lcd.clear();
  File dataFile = SD.open(strID);
  if (dataFile) {
    leni=0;
    while ((tempchar =dataFile.read()) != -1) {
     Serial.println(tempchar);
      iotname[leni++]=tempchar;
   
    }
    dataFile.close();len=strlen(iotname);
    //iotname[len-1]='\0';
    Serial.print(".......");
    Serial.println(iotname);
  }
    Serial.print("welcome ");Serial.println(iotname);
    lcd.clear();
   action();
  }
  else
  {lcd.clear();
    Serial.println("unAutherised card please enter pin to conform");
    lcd.setCursor(0,0);
lcd.print("unauthorised access");
delay(1000);lcd.clear();lcd.print("enter key to login");
   keym();
  }
}
void keym(){
  kepass=="";
  //Serial.println("repeat");
  kei=0;
    while(kei<4){
    
      key_pressed=  kpd.getKey();
         if(key_pressed!=NULL){
        kepass[kei]=key_pressed;
        kei= kei+1;
        Serial.println(key_pressed);
       lcd.setCursor(8 + kei,3);lcd.print("*");
        key_pressed==NULL;
        
         } 
       }
      Serial.print("..........."); Serial.print(kepass[2]);
       Serial.print("...........");
      Serial.println(kepass);
    
      if (iotpass.equals(kepass))
      {
        Serial.println("password accepted");
        action();
      }
      else 
      {lcd.clear();lcd.setCursor(0,0);lcd.print("key rejected");lcd.setCursor(1,1);lcd.print("[#] to enter again?");
        Serial.println("password rejected");
      Serial.println(" [#] to enter again?");
      optkey=="";
  //Serial.println("repeat");
 int optkei=0;
   temp==1;
    while(temp<5){
      //Serial.println("temp stage");
    while( optkei<1){
      key_pressed=  kpd.getKey();
         if(key_pressed!=NULL){
       optkey[optkei++]=key_pressed;
        Serial.print(key_pressed);
        key_pressed==NULL;
     if (optkey[0]=='#')
      {
       conform();
      }
      Serial.println("stage overrided // you are blocked");
      //lcd.setCursor(16,1);lcd.print("3");
     lcd.setCursor(0,3);lcd.print("overriding cancelled"); lcd.clear();
       } 
     } 
   break; }
     
   }
}
void action(){
  lcd.clear();
  lcd.setCursor(6,0);
lcd.print("welcome" );
lcd.setCursor(6,1);
lcd.print(iotname);
  Serial.println("pgm under const");
lcd.setCursor(2,3);lcd.print("pgm under const");
   
  while(1){
 key_pressed = kpd.getKey();
 Serial.println(key_pressed);
    if(key_pressed=='#'){
      temp=67;
      lcd.clear();
      return 0;
      }
  }
 
}
void conform(){

  Serial.println("stage coform");
  while(temp!=5){
    Serial.println("stage wwhile");
for(ci=0;ci<3;ci++){
  lcd.clear();
  Serial.println("stage for");
if(temp!=67){
  Serial.println("stage before 589");
 lcd.setCursor(0,1);Serial.println("stage 67");
lcd.print("no.of.attempt=");
  //Serial.print("no of attempt =");
  lcd.setCursor(16,1);
 lcd.print(ci);
  //Serial.print(ci);
  lcd.setCursor(17,1);
  lcd.print(":3");
  //Serial.println(": out of 3");
  lcd.setCursor(2,2);
  lcd.print("Enter pin again");
  Serial.println("stage before");
  keymaction();Serial.println("stage after");
}
else{
return 0;}
}
Serial.println("stage end");
return 0;

}}
void keymaction(){
  kepass=="";
  //Serial.println("repeat");
  kei=0;
    while(kei<4){
        key_pressed=  kpd.getKey();
        if(key_pressed!=NULL){
        kepass[kei++]=key_pressed;
        lcd.setCursor(7 + kei,3);lcd.print("*");
        Serial.print("*");
        key_pressed==NULL;
        
         } 
       }
      Serial.print("...........");
      Serial.println(kepass);
    
      if (iotpass.equals(kepass))
      { lcd.clear();lcd.setCursor(0,1);lcd.print("password accepted!!!");
        Serial.println("password accepted!!!");
        temp=67;
        action();
      }
      temp=0;
      return;
}
char keypod(){
    char keypressed = kpd.getKey();
     if (keypressed != NO_KEY)
     {
          Serial.println(keypressed);
     }
     return keypressed;
  }
void stdadd() {
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

  String strID = "";
  for (byte rfi = 0; rfi < 4; rfi++) {
    
    strID +=
    (rfid.uid.uidByte[rfi] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[rfi], HEX) +
    (rfi!=3 ? "" : "");
  }
  strID.toUpperCase();
//not reqd Serial.println("place the card");
// thMis too lcd.setCursor(3,0);
// this as well lcd.print("place the card");

 Serial.print("Tap card rfkey: ");
  Serial.println(strID);
strID.concat(".txt");
Serial.print("this is concated file name: ");Serial.println(strID);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  File dataFile;
  dataFile= SD.open(strID,FILE_WRITE);
  char rec=bluetooth();
  dataFile.write(rec);
  dataFile.close();
  }

  char bluetooth()
  {
    int leni=0;
while(((tem=Serial.read())!=-1)&&(leni<8))
{
  Serial.println(tem);
  bt[leni++]=tem;
}
Serial.println(bt);
return bt;
  }
