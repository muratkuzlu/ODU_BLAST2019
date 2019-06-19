// Robo India Tutorial 
// Simple code upload the tempeature and humidity data using thingspeak.com
// Hardware: NodeMCU


#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
 
String apiKey = "2SV8FRB305ES66B7";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "AS2L-Room";     // replace with your wifi ssid and wpa2 key
const char *pass =  "as2l214c";
const char* server = "api.thingspeak.com";
 const char * myWriteAPIKey = "3M0SBN71PI6UD1A4"; 
unsigned long myChannelNumber = 803487;

WiFiClient client;

void setup()
{
       Serial.begin(115200);
       delay(10);

       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");

      // Print the IP address  
      Serial.println(WiFi.localIP());  
      ThingSpeak.begin(client);  
 
}

void loop() {

  int sensorValue = analogRead(A0);   // read the input on analog pin 0

  float voltage = sensorValue * (5.0 / 1023.0);   // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)

  Serial.println(voltage);   // print out the value you read
  Serial.print("Photoresistir value is :");  
  Serial.print(voltage);
  ThingSpeak.writeField(myChannelNumber, 5, voltage, myWriteAPIKey);  
  delay(30000); // ThingSpeak will only accept updates every 15 seconds. 
}
