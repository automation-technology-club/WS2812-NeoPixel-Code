
#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_NeoPixel.h>
#include <nRF24L01.h>
#include <RF24.h>

// Local Network Settings
byte mac[] = { 0xD4, 0x28, 0xB2, 0xFF, 0x48, 0x84 }; // Must be unique on local network

#define thingSpeakInterval 18000 // Time interval in milliseconds to get data from ThingSpeak (number of seconds * 1000 = interval)
// Variable Setup
#define CE_PIN 8
#define CSN_PIN 7

long lastConnectionTime = 0;

String lastCommandString = "black";
boolean lastConnected = false;
int failedCounter = 0;
int pattern;
const uint64_t pipe = 0xE8E8F0F0E1LL;
int colornumber = 2;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 6, NEO_GRB + NEO_KHZ800);
RF24 radio(CE_PIN, CSN_PIN);
// Initialize Arduino Ethernet Client
EthernetClient client;

void setup() {
delay(100);
radio.begin();
radio.openWritingPipe(pipe);
// Setup Serial
Serial.begin(9600);
delay(100);
Serial.flush();
delay(100);

strip.begin();
strip.show();

// Start Ethernet on Arduino
startEthernet();
}

void loop() {
// Process CheerLights Commands
if(client.available() > 0)
{
delay(100);
//pattern = random(0,9);

pattern = pattern+1;
if (pattern >=10) {pattern = 0;}

//Serial.println(client.available());
String response;
char charIn;
do {
charIn = client.read(); // read a char from the buffer
response += charIn; // append that char to the string response
} while (client.available() > 0);
//Serial.println(response.length());
Serial.println(response);

	if (response == "white" || response == "warmwhite" || response == "oldlace")
{
lastCommandString = "white";
colornumber = 1;
colorWipe(strip.Color(255,255,255),50);
}
else if (response == "black" || response == "off")
{
lastCommandString = "black";
colornumber = 2;
colorWipe(strip.Color(0,0,0),50);
}
else if (response == "red")
{
lastCommandString = "red";
colornumber = 3;
colorWipe(strip.Color(255,0,0),50);
}
else if (response == "green")
{
lastCommandString = "green";
colornumber = 4;
colorWipe(strip.Color(0, 255, 0), 50);
}
else if (response == "blue")
{
lastCommandString = "blue";
colornumber = 5;
colorWipe(strip.Color(0,0,255),50);
}
else if (response == "cyan")
{
lastCommandString = "cyan";
colornumber = 6;
colorWipe(strip.Color(0,255,255),50);
}
else if (response == "magenta")
{
lastCommandString = "magenta";
colornumber = 7;
colorWipe(strip.Color(255,0,255),50);
}
else if (response == "yellow")
{
lastCommandString = "yellow";
colornumber = 8;
colorWipe(strip.Color(255,255,0),50);
}
else if (response == "purple")
{
lastCommandString = "purple";
colornumber = 9;
colorWipe(strip.Color(102,51,204),50);
}
else if (response == "orange")
{
lastCommandString = "orange";
colornumber = 10;
colorWipe(strip.Color(255,153,0),50);
}
else if (response == "pink")
{
	lastCommandString = "pink";
colornumber = 11;
colorWipe(strip.Color(255,53,153),50);
}

delay(200);
Serial.print("CheerLight Command Received: ");
Serial.println(lastCommandString);
radio.write( &colornumber,sizeof(colornumber));
Serial.println(colornumber);
delay(200);
}
// Disconnect from ThingSpeak
if (!client.connected() && lastConnected)
{
Serial.println("...disconnected");
client.stop();
}
// Subscribe to ThingSpeak Channel and Field
if(!client.connected() && (millis() - lastConnectionTime > thingSpeakInterval))
{subscribeToThingSpeak();
} 
checkcolor(lastCommandString);
delay(500);
// Check if Arduino Ethernet needs to be restarted
if (failedCounter > 3 ) {startEthernet();}
lastConnected = client.connected();
delay(100);
} // End loop

void subscribeToThingSpeak()
{
if (client.connect("api.thingspeak.com", 80))
{
Serial.println("Connecting to ThingSpeak...");
failedCounter = 0;
Serial.println("Sending Request");
client.println("GET /channels/1417/field/1/last.txt");
client.println();
lastConnectionTime = millis();
}
else
{
failedCounter++;
Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");
Serial.println();
lastConnectionTime = millis();
}
}
void startEthernet()
{
client.stop();
Serial.println("Connecting Arduino to network...");
Serial.println();
delay(1000);
// Connect to network amd obtain an IP address using DHCP
if (Ethernet.begin(mac) == 0)
{
Serial.println("DHCP Failed, reset Arduino to try again");
Serial.println();
}
else
{
Serial.println("Arduino connected to network using DHCP");
Serial.println();
}
delay(1000);
}

void colorWipe(uint32_t c, uint8_t wait) {
//criss cross across top, left and right up and down (default)
	
		for(uint16_t i=0; i<16; i++) {
			strip.setPixelColor(i, c);
			strip.setPixelColor(i+1, c);
			strip.show();
strip.setPixelColor(i, 0, 0 ,0);
strip.setPixelColor(i+1, 0, 0, 0);
delay(wait);
}

for(uint16_t i=16; i>0; i--) {
			strip.setPixelColor(i, c);
			strip.setPixelColor(i+1, c);
			strip.show();
strip.setPixelColor(i, 0, 0 ,0);
strip.setPixelColor(i+1, 0, 0, 0);
delay(wait);
}

}

void checkcolor(String colors) {
	if (colors == "white")
{
colorWipe(strip.Color(255,255,255),50);
}
else if (colors == "black")
{
colorWipe(strip.Color(0,0,0),50);
}
else if (colors == "red")
{
colorWipe(strip.Color(255,0,0),50);
}
else if (colors == "green")
{
colorWipe(strip.Color(0, 255, 0), 50);
}
else if (colors == "blue")
{
colorWipe(strip.Color(0,0,255),50);
}
else if (colors == "cyan")
{
colorWipe(strip.Color(0,255,255),50);
}
else if (colors == "magenta")
{
colorWipe(strip.Color(255,0,255),50);
}
else if (colors == "yellow")
{
colorWipe(strip.Color(255,255,0),50);
}
else if (colors == "purple")
{
colorWipe(strip.Color(102,51,204),50);
}
else if (colors == "orange")
{
colorWipe(strip.Color(255,153,0),50);
}
else if (colors == "pink")
{
	colorWipe(strip.Color(255,53,153),50);
}

}






