
// Robo India Tutorial 
// Simple code upload the tempeature and humidity data using thingspeak.com
// Hardware: NodeMCU,DHT11

#include "DHTesp.h"

int temperature, humidity, k=0, l=0;

#define DHTPIN D4         //pin where the dht11 is connected
DHTesp dht;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       //dht.begin();
       dht.setup(DHTPIN, DHTesp::DHT11); // data pin 4
 
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
  delay(5000); 
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
