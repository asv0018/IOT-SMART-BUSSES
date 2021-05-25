#include <SomeSerial.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <String.h>
#include <ArduinoJson.h>
SomeSerial iot(A11,A10);
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);
#define SS_PIN 9
#define RST_PIN 8
int temp=1;
String rfidvalue;
int ci;
char tem;
int i=0;
int len,leni=0;
String reply;
char iotname[300];
int kei=0;
const byte Rows= 4; //number of rows on the keypad
const byte Cols= 4; //number of columns on the keypad
char   key_pressed;
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
//keypad connections to the arduino terminals is given as:
byte rPins[Rows]= {A0,A1,A2,A3};
byte cPins[Cols]= {A4,A5,A6,A7};
// command for library forkeypad
//initializes an instance of the Keypad class
Keypad kpd= Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);
int rfi=1;
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key rfkey;

void setup() {
  iot.begin(9600);
  pinMode(22,OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  lcd.begin(20,4);
  rfid.PCD_Init();
  //welcome screen
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("SCHOOLIECAMBUS");
  lcd.setCursor(3,1);
  lcd.setCursor(0,2);
  lcd.print("version:1.0.1");
  delay(3000);
  lcd.clear();
}
char tempchar=NULL;String bt;
void loop() 
{
  mainloop();
}
//Here Functions only and nothing else//
void mainloop()
{
  lcd.setCursor(0,0);
  lcd.print("SELECT OPTION :");
  lcd.setCursor(0,1);
  lcd.print("A> LOGIN");
  lcd.setCursor(0,2);
  lcd.print("B> STUDENT DETAILS");
  lcd.setCursor(0,3);
  lcd.print("C> ID CARD SCANING");
  char mainBack=NULL;
  char var=keypod();
  switch(var){
      case 'A':
          lcd.clear();
          Serial.println("A is pressed \n opens Student login function");
          while(mainBack!='#'){
                loginloop();
                mainBack=keypod();
          }
          Serial.println("switch case A released");
          lcd.clear();
          break;
      case 'B':
          lcd.clear();
          Serial.println("B is pressed \n opens display student information");
          while(mainBack!='#'){
               // stdadd();
                mainBack=keypod();
          }
          Serial.println("Switch case B released");
          lcd.clear();
          break;
      case 'C':
          lcd.clear();
          Serial.println("C is pressed \n id card scanning during adding students procedure");
          while(mainBack!='#'){
                rfidread();
                mainBack =kpd.getKey();
                }
          Serial.println("Switch case C released");lcd.clear();
          break;
      case 'D':

          break;
  }
}

void loginloop(){
  // if( rfi!=0){
    loginwithrfid();
  //}
}

void loginwithrfid(){
beginningofloginwithrfid:
  lcd.setCursor(5,1);
  lcd.print("WElCOME");
  lcd.setCursor(3,2);
  lcd.print("PLACE ID CARD");
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()){
       return;
  }
  //maybe useful in future
  //Serial.print(F("PICC type: ")); 
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));
  //Check is the PICC of Classic MIFARE type
  /*if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
              Serial.println(F("Your tag is not of type MIFARE Classic."));
              return;
  }*/
  String strID = "";
  for (byte rfi = 0; rfi < 4; rfi++) {
      strID +=
      (rfid.uid.uidByte[rfi] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[rfi], HEX) +
      (rfi!=3 ? "" : "");
  }
 
  Serial.print("Tap card rfkey:");
  if(strID){
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("ID CARD PLACED");
    lcd.setCursor(4,2);
    lcd.print("PLEASE WAIT");
    }
  Serial.println(strID);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  String response=connectiot(strID);
  Serial.println(response);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(response);
  String isAuthorised=root["status"];
  int isAuthorisedinint=atoi(isAuthorised.c_str());
  Serial.println(isAuthorisedinint);
  if(isAuthorisedinint==1){
    String names=root["name"];
    names.toUpperCase();
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("WELCOME");
    lcd.setCursor(0,2);
    lcd.print(names);
    Serial.println(names);
    digitalWrite(22,HIGH);
    delay(250);
    digitalWrite(22,LOW);
    delay(2750);
    lcd.clear();
    }
    else if(isAuthorisedinint==0){
      lcd.clear();
      lcd.setCursor(0,2);
      lcd.print("YOU ARE UNAUTHORISED");
      int _count=1;
      while(_count<7){
      digitalWrite(22,HIGH);
      delay(250);
      digitalWrite(22,LOW);
      delay(250);_count++;
      }
      lcd.clear();
      }
    else if(isAuthorisedinint== -1 ){
        lcd.clear();
        lcd.setCursor(3,1);
        lcd.print("NETWORK ISSUES");
        lcd.setCursor(5,2);
        lcd.print("TRY AGAIN");
        digitalWrite(22,HIGH);
        delay(1500);
        digitalWrite(22,LOW);
        delay(500);
        lcd.clear();
        }
        goto beginningofloginwithrfid;
  }
  /*}else{
    lcd.clear();
    Serial.println("unAutherised card please enter pin to conform");
    lcd.setCursor(0,0);
lcd.print("unauthorised access");
delay(1000);lcd.clear();lcd.print("enter key to login");
   keym();
  }*/


String connectiot(String value){
      String result;
      Serial.println(value);
      iot.println(value);
      bool Ready=false;
      unsigned long previousMillis=millis();
      Serial.println(previousMillis);
      Serial.println("DDD");
      while(Ready==false){
      unsigned long currentSecondInMillis=millis();
      Serial.println(currentSecondInMillis);
      if((currentSecondInMillis-previousMillis)>=3000){
         Serial.println("timeout");
         result="{\"success\":-1,\"message\":\"TRY AGAIN\"}";
         break;
      }
      if(iot.available()){
        result=iot.readString();
        Ready=true;
      }
      }

      Serial.print(result);
      return result;
}



char keypodA(){
    char keypressed = kpd.getKey();
     if (!(keypressed))
     { 
      delay(2000);
      keypressed=kpd.getKey();
      if(!(keypressed)){
        return 'A';
      }
          //Serial.println(keypressed);
     }
     return keypressed;
  }
  
  char keypod(){
    char keypressed = kpd.getKey();
     if (!(keypressed)){
      
     }
   
     return keypressed;
  }
void welcomeName(String value){
  Serial.println("it came here too");
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("WELCOME");
  lcd.setCursor(0,1);
  lcd.print(value);
  delay(2000);
  lcd.clear();
}

void rfidread(){
fornewscan:
  
  lcd.setCursor(2,0);
  lcd.print("RFID SCANNING ON");
  lcd.setCursor(3,1);
  lcd.print("PLACE ID CARD");
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()){
       return;
  }
  //maybe useful in future
  Serial.print(F("PICC type: ")); 
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));
  //Check is the PICC of Classic MIFARE type
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
  
  Serial.print("Tap card rfkey: ");
  Serial.println(strID);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  lcd.clear();
  delay(10);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("RFID SCANNING ON");
  lcd.setCursor(3,1);
  lcd.print("ID CARD PLACED");
  lcd.setCursor(6,3);
  lcd.print(strID);
  delay(5000);
  lcd.clear();
  char val = kpd.getKey();
     if (!(val)==NO_KEY){           
      //Serial.println(val);
      }
      if(val=='#')
      {
       goto fornewscan; 
      }
      if(val=='*'){
        return ;
      }
      }
 



  

  
