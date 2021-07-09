//Interfacing ultrasonic and gps with ESP8266 wifi module 
//Interfacing the output with BLYNK app


#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h> 

#include <Arduino.h>
#ifdef ARDUINO_ARCH_SAMD
#include <WiFi101.h>
#elif defined ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#elif defined ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <ESP8266HTTPClient.h>

#else
#endif

#include <WifiLocation.h>
#include <Ethernet.h>
char auth[] = "0gmT9Oamv-t_qDNOYnJfUwPPjq8NMU5C";
const char* googleApiKey = "AIzaSyDEpx1G1_UlbfKxg3DaLJXR53oZOQDasJY"; 
const char* ssid = "AndroidAP892F";
const char* passwd = "ytrams333";


// defines pins numbers

const int trigPin = 12;  //D6
const int echoPin = 13;  //D7

// defines variables
long duration;
int distance;

double latitude    = 0.0;
double longitude   = 0.0;
double accuracy    = 0.0;


WidgetMap myMap(V1);

WifiLocation location(googleApiKey); 
void setup() {
Serial.begin(9600);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//Serial.begin(9600); // Starts the serial communication

WiFiClientSecure client;

// Connect to WPA/WPA2 network 
#ifdef ARDUINO_ARCH_ESP32
WiFi.mode(WIFI_MODE_STA); 
#endif
#ifdef ARDUINO_ARCH_ESP8266
WiFi.mode(WIFI_STA);
#endif
 
WiFi.begin(ssid, passwd);
while (WiFi.status() != WL_CONNECTED) 
{ Serial.print("Attempting to connect to WPA SSID: "); 
Serial.println(ssid);
// wait 5 seconds for connection: 
Serial.print("Status = "); 
Serial.println(WiFi.status()); 
delay(500);
}

Blynk.begin(auth, ssid, passwd);
location_t loc = location.getGeoFromWiFi(); 
Serial.println("Location request data"); 
Serial.println(location.getSurroundingWiFiJson()); 
Serial.println("Latitude: " + String(loc.lat, 7)); 
Serial.println("Longitude: " + String(loc.lon, 7)); 
Serial.println("Accuracy: " + String(loc.accuracy));
}
void loop() 
{ 
  
  //getgps(); 
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(distance);
//delay(2000);
if(distance<=500)
{Serial.print("distance=");
Serial.println(distance);
Serial.print("\n\n\n\n");
 
 Blynk.virtualWrite(V5, distance);
  getgps();
  delay(200);
 Blynk.run();
}
 Blynk.run(); 
}
  
  
 void getgps()
 { 
  WiFiClientSecure client;
  WiFi.begin(ssid, passwd);
while (WiFi.status() != WL_CONNECTED)
{ Serial.print("Attempting to connect to WPA SSID: "); Serial.println(ssid);
// wait 5 seconds for connection: 
Serial.print("Status = "); 
Serial.println(WiFi.status()); 
delay(500);
}
if (WiFi.status()==WL_CONNECTED)
{ Serial.println("Connected.  ");
Serial.print("Status = "); 
Serial.println(WiFi.status()); 
delay(500);
}
 
location_t loc = location.getGeoFromWiFi(); 
Serial.println("Location request data"); 
Serial.println(location.getSurroundingWiFiJson()); 
Serial.println("Latitude: " + String(loc.lat, 7)); 
Serial.println("Longitude: " + String(loc.lon, 7)); 
Serial.println("Accuracy: " + String(loc.accuracy));


client.stop();
  int index = 1;
  double lat = latitude;
  double lon = longitude;
  double accura = accuracy;
  Serial.println(loc.lat);
  Serial.println(loc.lon);
myMap.location(index ,loc.lat,loc.lon,loc.accuracy);
}
