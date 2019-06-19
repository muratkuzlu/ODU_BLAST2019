// Robo India Tutorial 
// Simple code upload the tempeature and humidity data using thingspeak.com
// Hardware: NodeMCU,LED


#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
 
String apiKey = "2SV8FRB305ES66B7";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "AS2L-Room";     // replace with your wifi ssid and wpa2 key
const char *pass =  "as2l214c";
const char* server = "api.thingspeak.com";
 const char * myWriteAPIKey = "3M0SBN71PI6UD1A4"; 
unsigned long myChannelNumber = 803487;
uint8_t LED_Status, l=0;

WiFiClient client;

#define LED D1            // Led in NodeMCU at pin GPIO5 (D1).
void setup()
{
       Serial.begin(115200);
       delay(10);

       pinMode(LED, OUTPUT);    // LED D1 pin as output.

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
LED_Status = HIGH;
digitalWrite(LED, LED_Status);// turn the LED off.(Note that LOW is the voltage level but actually 
                        //the LED is on; this is because it is acive low on the ESP8266.
Serial.print("LED Status is :");  
Serial.print(LED_Status);
ThingSpeak.writeField(myChannelNumber, 3, LED_Status, myWriteAPIKey);  
delay(30000); // ThingSpeak will only accept updates every 15 seconds.

LED_Status = LOW;
digitalWrite(LED, LED_Status); // turn the LED on.
Serial.print("LED Status is :");  
Serial.print(LED_Status);
ThingSpeak.writeField(myChannelNumber, 3, LED_Status, myWriteAPIKey);  
delay(30000); // ThingSpeak will only accept updates every 15 seconds. 
}
