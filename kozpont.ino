/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
String  sensor11;
String  sensor12;
String  sensor1;
String  sensor2;
unsigned long rft;
unsigned long oldt;
IPAddress staticIP324_140(192,168,0,140);
IPAddress gateway324_140(192,168,0,1);
IPAddress subnet324_140(255,255,255,0);

WiFiServer server(80);

String  httpurl;
String  TheHiddenAnswerOfClient;
HTTPClient http;

String SendWithAnswer(String IPcache, String monmessagecache) {
httpurl = "http://";
httpurl+=IPcache;
httpurl+="/";
httpurl+=monmessagecache;
http.begin(httpurl);
http.GET();
TheHiddenAnswerOfClient = (http.getString());
http.end();
return TheHiddenAnswerOfClient;
}

void setup()
{
  sensor1 = "";
  sensor2 = "";

  Serial.begin(9600);
    WiFi.disconnect();
  delay(5000);
  Serial.println(" ");
  Serial.println("START");
  
   WiFi.begin("Emelet");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");
  }
  Serial.println("Connected");
  WiFi.config(staticIP324_140, gateway324_140, subnet324_140);
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  server.begin();

}


void loop()
{
 // rft=(millis()-oldt);     
//Serial.print("Fissitesi ido =");
//Serial.println((rft/1000));

    sensor11 = (SendWithAnswer("192.168.0.148","Yes"));
    sensor1 = sensor11;
    sensor1.remove(0, 21);
    sensor1.remove(4,19);
    sensor2 = (SendWithAnswer("192.168.0.143","Yes"));
    sensor2.remove(0, 25);
    sensor2.remove(sensor2.length()-11,11);

    //Serial.println(sensor1);
    //Serial.println("sensor2");
   // Serial.println(sensor2);
    //Serial.println("");
    kijelzo();
    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    client.flush();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<meta http-equiv='refresh' content='10'/>");
    client.println("<title> Kijelzo</title>");
    client.println("</head>");
    client.println("<body>");
      client.println("<h1 style=""color:#ff0000"">");
      client.println("proba oldal");
      client.println("</h1>");
      //client.println("<span style=""color:#ff0000;font-size:14px"">");
      //client.println("Refress time");
      //client.println("</span>");
      //client.println("<span style=""color:#ff0000;font-size:14px"">");
      //client.println("   ");
      client.println("</span>");
      client.println("<h1 style=""color:#ff0000"">");
      client.println("sensor1");
      client.println("</h1>");
      client.println("<span style=""color:#ff0000;font-size:14px"">");
      client.println(sensor1);
      client.println("<h1 style=""color:#ff0000"">");
      client.println("sensor2");
      client.println("</h1>");
      client.println("<span style=""color:#ff0000;font-size:14px"">");
      client.println(sensor2);
      client.println("</span>");
      client.println("</body>");
      client.println("</html>");
      client.stop();
     delay(1);
     oldt=millis();
}

void kijelzo(){
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write("t9.txt=");
      Serial.write(34);
      Serial.print(sensor1);
      Serial.write(34);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
          
      Serial.write("t10.txt=");
      Serial.write(34);
      Serial.print(sensor2);
      Serial.write(34);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
     Serial.println();
   
}


