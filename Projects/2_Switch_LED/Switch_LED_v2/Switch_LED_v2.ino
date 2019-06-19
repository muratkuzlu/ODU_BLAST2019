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

int ledpin = 5; // D1(gpio5)
int button = 4; //D2(gpio4)
int buttonState=0;

#define LED D1            // Led in NodeMCU at pin GPIO5 (D1).
void setup()
{
       Serial.begin(115200);
       delay(10);

        pinMode(ledpin, OUTPUT);
        pinMode(button, INPUT);

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
 buttonState=digitalRead(button); // put your main code here, to run repeatedly:
 if (buttonState == 1)
 {
 digitalWrite(ledpin, HIGH); 
 Serial.print("Button Status is :");  
 Serial.print(buttonState);
 ThingSpeak.writeField(myChannelNumber, 4, buttonState, myWriteAPIKey);  
 delay(1000); 
 }
 else
 {
 digitalWrite(ledpin, LOW); 
 Serial.print("Button Status is :");  
 Serial.print(buttonState);
 ThingSpeak.writeField(myChannelNumber, 4, buttonState, myWriteAPIKey);  
 delay(1000); // ThingSpeak will only accept updates every 15 seconds. 
 }
}
