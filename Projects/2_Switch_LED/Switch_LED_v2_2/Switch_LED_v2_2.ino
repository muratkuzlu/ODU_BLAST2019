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

WiFiClient client;

#define LED 5 // D1(gpio5)
#define BUTTON 4 //D2(gpio4)

int buttonState=0;

int switchState = 0; // actual read value from pin4
int oldSwitchState = 0; // last read value from pin4
int lightsOn = 0; // is the switch on = 1 or off = 0

void setup()
{
       Serial.begin(115200);
       delay(10);

        pinMode(BUTTON, INPUT); // push button 
        pinMode(LED, OUTPUT); // anything you want to control using a switch e.g. a Led

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
 switchState = digitalRead(BUTTON); // read the pushButton State
 if (switchState != oldSwitchState) // catch change
 {
 oldSwitchState = switchState;
 if (switchState == HIGH)
 {
 // toggle
 lightsOn = !lightsOn;
 }
 }
 if(lightsOn)
 {
 digitalWrite(LED, HIGH); // set the LED on
 buttonState = HIGH;
 } else {
 digitalWrite(LED, LOW); // set the LED off
  buttonState = LOW;
 }
 Serial.print("Button Status is :");  
 Serial.print(buttonState);
 ThingSpeak.writeField(myChannelNumber, 4, buttonState, myWriteAPIKey);  
 delay(1000);  

 }
