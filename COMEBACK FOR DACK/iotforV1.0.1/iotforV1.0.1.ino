#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
//#include<SoftwareSerial.h>
#include<WiFiClient.h>
#include<SomeSerial.h>
SomeSerial dack(12,13);
//SoftwareSerial dack(4,13);//rx,tx d2 , d7
WiFiManager wifiManager;
HTTPClient http;
WiFiClient client;
void setup(){
  pinMode(5,OUTPUT);//green led...
  pinMode(16,OUTPUT);//red led...
  digitalWrite(16,HIGH);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  Serial.begin(9600);
  dack.begin(9600);
Reconnect:
  Serial.print("WifiManager begins...");
  wifiManager.autoConnect("Schoolie Cambus","admin");
  digitalWrite(16,LOW);
  digitalWrite(5,HIGH);
  Serial.println("Connected.");
} 

void loop(){
     while(WiFi.status()==WL_CONNECTED){
      digitalWrite(16,LOW);
      digitalWrite(5,HIGH);
      iot_pipeline();
      if(WiFi.status()!=WL_CONNECTED){
        digitalWrite(16,HIGH);
        digitalWrite(5,LOW);
        int buz=2;
        for (int i=0;i<3;i++){
        digitalWrite(buz,HIGH);
        delay(200);
        digitalWrite(buz,LOW);
        delay(100);
        }
        Serial.println("this is from inside the loop if condition");
        wifiManager.autoConnect("Schoolie Cambus","admin");
      }
      
      
     }
     }
     

void iot_pipeline(){
  String dackvalue="";
  while(dack.available()){
    Serial.println("I AM RECIEVING");
    delay(10);
    int _temp=dack.read();
    Serial.println(_temp);
    dackvalue.concat(_temp);
    dackvalue.concat(",");
    }
  dackvalue.remove((dackvalue.length())-1);
  Serial.println(dackvalue);
  String request="http://innovations.thinkfinitylabs.com/schooliecambus/check-rfid.php?rfid=";
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
