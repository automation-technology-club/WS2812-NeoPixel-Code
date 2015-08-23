
#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_NeoPixel.h>

// Local Network Settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Must be unique on local network

#define thingSpeakInterval 18000 // Time interval in milliseconds to get data from ThingSpeak (number of seconds * 1000 = interval)
// Variable Setup
long lastConnectionTime = 0;

String lastCommandString = "black";
boolean lastConnected = false;
int failedCounter = 0;
String color;
char server[] = "api.thingspeak.com";
IPAddress ip(192,168,1,177);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, 6, NEO_GRB + NEO_KHZ800);

// Initialize Arduino Ethernet Client
EthernetClient client;

void setup() {
delay(100);
// Setup Serial
Serial.begin(9600);
delay(100);
Serial.flush();
delay(100);
strip.begin();
strip.show();

// Start Ethernet on Arduino
if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  getThingSpeak();
  lastConnectionTime = millis();
}

void loop() {
// Process CheerLights Commands

if (!client.connected() && (millis() - lastConnectionTime > thingSpeakInterval)) 
{getThingSpeak(); lastConnectionTime = millis();}
if (client.available()) {
	char CharIn;
		do {	
			CharIn = client.read();
		char response += CharIn;
					} while (client.available() > 0);
					 Serial.println(response.length()); color = String(response);}
checkcolor(color);

}

void getThingSpeak() {
	if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /channels/1417/field/1/last.txt");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}


void colorWipe(uint32_t c, uint8_t wait) {
for(uint16_t i=0; i<strip.numPixels(); i++) {
strip.setPixelColor(i, c);
strip.setPixelColor(i+1, c);
strip.setPixelColor(i+2, c);
strip.show();
strip.setPixelColor(i, 0, 0 ,0);
strip.setPixelColor(i+1, 0, 0, 0);
strip.setPixelColor(i+2, 0, 0, 0);
delay(wait);

}
}

void checkcolor(String colors1) {
	//String colors1 = String(colors);
	//Serial.println(colors);
	//Serial.println(colors1);
	
	if (colors1 == "white")
{
colorWipe(strip.Color(255,255,255),50);
}
else if (colors1 == "black")
{
colorWipe(strip.Color(0,0,0),50);
}
else if (colors1 == "red")
{
colorWipe(strip.Color(255,0,0),50);
}
else if (colors1 == "green")
{
colorWipe(strip.Color(0, 255, 0), 50);
}
else if (colors1 == "blue")
{
colorWipe(strip.Color(0,0,255),50);
}
else if (colors1 == "cyan")
{
colorWipe(strip.Color(0,255,255),50);
}
else if (colors1 == "magenta")
{
colorWipe(strip.Color(255,0,255),50);
}
else if (colors1 == "yellow")
{
colorWipe(strip.Color(255,255,0),50);
}
else if (colors1 == "purple")
{
colorWipe(strip.Color(102,51,204),50);
}
else if (colors1 == "orange")
{
colorWipe(strip.Color(255,153,0),50);
}


}

