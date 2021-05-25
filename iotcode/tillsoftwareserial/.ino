#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>   
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

WiFiManager wifiManager;
void setup(){
 StaticJsonBuffer<200> jsonBuffer;
Reconnect:
  delay(1000);
  Serial.begin(115200);
  Serial.print("WifiManager begins...");
  wifiManager.autoConnect("Schoolie Cambus","admin");
  Serial.println("Connected.");
}
void loop()
{
  checpass();
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
}
