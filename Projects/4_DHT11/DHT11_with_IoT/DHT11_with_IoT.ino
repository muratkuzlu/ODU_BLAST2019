
// Robo India Tutorial 
// Simple code upload the tempeature and humidity data using thingspeak.com
// Hardware: NodeMCU,DHT11

#include "DHTesp.h"
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

const char *ssid =  "AS2L-Room";     // replace with your wifi ssid and wpa2 key
const char *pass =  "ODU_BLAST";
const char* server = "api.thingspeak.com";
 const char * myWriteAPIKey = "3M0SBN71PI6UD1A4";  //  Enter your Write API key from ThingSpeak
unsigned long myChannelNumber = 803487;
uint8_t temperature, humidity, k=0, l=0;

#define DHTPIN D4         //pin where the dht11 is connected
DHTesp dht;

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       //dht.begin();
       dht.setup(DHTPIN, DHTesp::DHT11); // data pin 2
 
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

 void loop()   
 {  
  static boolean data_state = false;  
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  temperature = CelsiusToFahrenheit(temperature);
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("F");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write to field 1.  
  if(temperature < 255)
  {
      k=temperature;  
  }
   if(humidity < 255)
  {
      l=humidity;  
  }
  if( data_state )  
  {  
   ThingSpeak.writeField(myChannelNumber, 1, k, myWriteAPIKey);  
   data_state = false;  
  }  
  else  
  {  
   ThingSpeak.writeField(myChannelNumber, 2, l, myWriteAPIKey);  
   data_state = true;
  }  
  delay(30000); // ThingSpeak will only accept updates every 15 seconds.  
 }  

//Functions
 float FahrenheitToCelsius(float fahrenheit)
 {
     float celsius;
 
     celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
     return celsius;
 }

 
 float CelsiusToFahrenheit(float celsius)
 {
     float fahrenheit;
 
     fahrenheit = (celsius * 9.0) / 5.0 + 32;
     return fahrenheit;
 }
