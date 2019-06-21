// Robo India Tutorial 
// Simple code upload the tempeature and humidity data using thingspeak.com
// Hardware: NodeMCU,LED


#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Keypad.h>
 
const char *ssid =  "AS2L-Room";     // replace with your wifi ssid 
const char *pass =  "ODU_BLAST";     // replace with your wifi password

const char* server = "api.thingspeak.com"; 
 const char * myWriteAPIKey = "3M0SBN71PI6UD1A4"; 
   //  Enter your Write API key from ThingSpeak
unsigned long myChannelNumber = 803487;

WiFiClient client;

const byte n_rows = 4;
const byte n_cols = 4;
 
char keys[n_rows][n_cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
byte colPins[n_rows] = {D3, D2, D1, D0};
byte rowPins[n_cols] = {D7, D6, D5, D4};
 
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols); 

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
  char myKey = myKeypad.getKey();
 
  if (myKey != NULL){
    Serial.print("Key pressed: ");
    Serial.println(myKey);
    ThingSpeak.writeField(myChannelNumber, 6, myKey, myWriteAPIKey);  
    delay(3000); // ThingSpeak will only accept updates every 15 seconds.
  }

 
}
