#include <Arduino.h>
#include "oled.h"
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#define ONE_WIRE_BUS D1
OLED display=OLED(4,5,16);
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

//static const uint8_t bitmap[] =
//{ 
 //   1,2,4,8,16,32,64,128,128,128,192,192,128,128,128,64,32,16,8,4,2,1, // first page (8 vertical bits, 22 columns)
 //   255,255,255,255,15,15,15,15,15,15,15,15,15,15,15,15,15,15,255,255,255,255 // second page (8 vertical bits, 22 columns)
//};

void setup()
{
    //delay(1000);
    display.init(); 

 Serial.begin(9600);
    WiFi.disconnect();
  //delay(3000);
 // display.begin();
    display.draw_string(4,2,"Hello");
    display.display();
    
  delay(1000);
  Serial.println("START");
   WiFi.begin("Emelet");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  WiFi.config(staticIP383_148, gateway383_148, subnet383_148);
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  //display.draw_string(4,2,"192,168,0,148");
  //  display.display();
    
    

  server.begin();
          
}


void loop()
{
   
    
    // Draw text from program memory with double size
    //delay(1000);
    //display.draw_string_P(16,15,PSTR("World!"),OLED::DOUBLE_SIZE);
    //display.display();
    float temperature = getTemperature();
    char buffer[4];
      dtostrf(temperature, 2, 1, temperatureString);
    Serial.println(temperatureString);
    itoa(temperature,buffer,10);
   display.draw_string_P(16,15,PSTR (buffer) ,OLED::DOUBLE_SIZE);
    //display.print(temperatureString, 3, 0);
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
    //display.print(temperatureString, 3, 8);
    //display.print("kapcsolat");
    client.println("</html>");
    client.stop();
    delay(1);
   
}
