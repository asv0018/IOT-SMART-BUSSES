#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include<SoftwareSerial.h>
#include<WiFiClient.h>
#include<String>

SoftwareSerial dack(12,13);//rx,tx d6 , d7
WiFiManager wifiManager;
HTTPClient http;
WiFiClient client;
void setup(){
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  Serial.begin(9600);
  dack.begin(9600);
Reconnect:
  Serial.print("WifiManager begins...");
  wifiManager.autoConnect("Schoolie Cambus","admin");
  Serial.println("Connected.");
} 

void loop(){
   int key;
   String dackvalue="";
   while(dack.available()){
    Serial.println("I AM RECIEVING");
    delay(10);
    int _temp=dack.read();
    Serial.println(_temp);
    if(_temp==42){// it means *
      int key=1;
      Serial.println("A is given as key");
      continue;
    }
    if(_temp==94){//it means ^
      int key=2;
      Serial.println("B is given as key");
      continue;
    }
    dackvalue.concat(_temp);
    dackvalue.concat(",");
    }
    
    switch (key){
        case 1 :{
          Serial.println("am in A");
    dackvalue.remove((dackvalue.length())-1);
    Serial.println(dackvalue);
    CHECKRFIDFORDISPLAYINGDATA(dackvalue);}
    break;
  
        case 2 :{
          Serial.println("am in B");
    dackvalue.remove((dackvalue.length())-1);
    Serial.println(dackvalue);
    CHECKRFID(dackvalue);}
    break;
    }
}
  
  
void CHECKRFID(String dackvalue){
  String request="http://asvsharma.ml/SchoolieCambus/checkrfid.php?rfid=";
if(dackvalue.length()>0){ 
  Serial.println(request+dackvalue);
  http.begin(request+dackvalue);
  int httpCode;
  httpCode = http.GET();
  Serial.println(httpCode);
  String response = http.getString();
  Serial.println(response);
  dack.println(response);
 }
}
void CHECKRFIDFORDISPLAYINGDATA(String dackvalue){
  String request="http://asvsharma.ml/SchoolieCambus/fetchdata.php?rfid=";
if(dackvalue.length()>0){ 
  Serial.println(request+dackvalue);
  http.begin(request+dackvalue);
  int httpCode;
  httpCode = http.GET();
  Serial.println(httpCode);
  String response = http.getString();
  Serial.println(response);
  dack.println(response);
 }
}




 
 void sisi(){
 String dackvalue;
  while(dack.available()){
    delay(100);
    char _temp=dack.read();
    dackvalue.concat(_temp);
 
 }
 }
void connectdack()
{
  if (dack.available())
    Serial.write(dack.read());
  if (Serial.available())
    dack.write(Serial.read()); 
}
String checkpass(String pass)
{
  HTTPClient http;
  String subRequest,request;
  String macadd=WiFi.macAddress();
  macadd.replace(":","");
  subRequest="pass="+pass+"&macadd="+macadd;
  request = "http://asvsharma.ml/SchoolieCambus/checkpass.php?"+subRequest;
  http.begin(request);     //Specify request destination
  int httpCode = http.GET();            //Send the request
  String response = http.getString();//Get the response payload
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(response);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(response);
  /*if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }*/
  String present=root["authorised"];
  http.end();
  return present;
}
String checkrfid(String uid)
{
  HTTPClient http;
  String subRequest,request;
  String macadd=WiFi.macAddress();
  macadd.replace(":","");
  subRequest="uid="+uid+"&macadd="+macadd;
  request = "http://asvsharma.ml/SchoolieCambus/checkrfid.php?"+subRequest;
  http.begin(request);     //Specify request destination
  int httpCode = http.GET();            //Send the request
  String response = http.getString();//Get the response payload
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(response);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(response);
  /*if (!root.success()) {
    Serial.println("parseObject() failed");
    return 0;
  }*/
  String present=root["authorised"];
  String srn=root["srn"];
  http.end();
  if(present)
  {
    return srn;
  }
  else{
    String nothing="$";
    return nothing;
  }
}
