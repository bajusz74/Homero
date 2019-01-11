/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include "OLED.h"
#include <DallasTemperature.h>
#include <Wire.h>
#define ONE_WIRE_BUS D1
#define RST_OLED 16
OLED display(4, 5);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
IPAddress staticIP383_148(192,168,0,148);
IPAddress gateway383_148(192,168,0,1);
IPAddress subnet383_148(255,255,255,0);

WiFiServer server(80);
char temperatureString[6];
float getTemperature() {
  float temp;
  
  do {
    DS18B20.requestTemperatures(); 
    temp = DS18B20.getTempCByIndex(0);
    delay(100);
  } while (temp == 85.0 || temp == (-127.0));
  
  return temp;
}


void setup()
{
  pinMode(RST_OLED, OUTPUT);
  digitalWrite(RST_OLED, LOW);   // turn D2 low to reset OLED
  delay(50);
  digitalWrite(RST_OLED, HIGH);    // while OLED is running, must set D2 in high
  Serial.begin(9600);
    WiFi.disconnect();
  delay(3000);
  display.begin();
display.print("Start");
  delay(3*1000);
  Serial.println("START");
   WiFi.begin("Belkin");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  WiFi.config(staticIP383_148, gateway383_148, subnet383_148);
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  display.print("192,168,0,148", 2, 0);
  delay(1000);  

  server.begin();
display.clear();
display.print("online", 0, 0);
}


void loop()
{
  display.print("++++++", 3, 0);
float temperature = getTemperature();
      dtostrf(temperature, 2, 1, temperatureString);
    Serial.println(temperature);
    display.print(temperatureString, 2, 0);
    display.print("------", 3, 0);
    delay(500);
    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    
    client.flush();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.print("<!DOCTYPE HTML>");
    client.print("<html>");
    client.print(temperatureString );
    client.print(" V1");
    client.print(" +");
    client.print(" A1");
    Serial.println(temperature);
    display.print(temperatureString, 2, 9);
    display.print("Sent",0,9);
    client.println("</html>");
    client.stop();
    delay(1);

}
