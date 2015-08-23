
#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_NeoPixel.h>

// Local Network Settings
byte mac[] = { 0xD4, 0x28, 0xB2, 0xFF, 0x48, 0x84 }; // Must be unique on local network

#define thingSpeakInterval 18000 // Time interval in milliseconds to get data from ThingSpeak (number of seconds * 1000 = interval)
// Variable Setup
long lastConnectionTime = 0;

String lastCommandString = "black";
boolean lastConnected = false;
int failedCounter = 0;
int pattern;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(27, 6, NEO_RGB + NEO_KHZ800);

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
colorWipe(strip.Color(255,255,255),50);
}
else if (response == "black" || response == "off")
{
lastCommandString = "black";
colorWipe(strip.Color(0,0,0),50);
}
else if (response == "red")
{
lastCommandString = "red";
colorWipe(strip.Color(255,0,0),50);
}
else if (response == "green")
{
lastCommandString = "green";
colorWipe(strip.Color(0, 255, 0), 50);
}
else if (response == "blue")
{
lastCommandString = "blue";
colorWipe(strip.Color(0,0,255),50);
}
else if (response == "cyan")
{
lastCommandString = "cyan";
colorWipe(strip.Color(0,255,255),50);
}
else if (response == "magenta")
{
lastCommandString = "magenta";
colorWipe(strip.Color(255,0,255),50);
}
else if (response == "yellow")
{
lastCommandString = "yellow";
colorWipe(strip.Color(255,255,0),50);
}
else if (response == "purple")
{
lastCommandString = "purple";
colorWipe(strip.Color(102,51,204),50);
}
else if (response == "orange")
{
lastCommandString = "orange";
colorWipe(strip.Color(255,153,0),50);
}
else if (response == "pink")
{
	lastCommandString = "pink";
colorWipe(strip.Color(255,53,153),50);
}

delay(200);
Serial.print("CheerLight Command Received: ");
Serial.println(lastCommandString);
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
	if (pattern == 1) {
		for(uint16_t i=0; i<27; i++) {
			strip.setPixelColor(i, c);
			strip.setPixelColor(i+1, c);
			strip.setPixelColor(i+2, c);
			strip.setPixelColor(i+30, c);
			strip.setPixelColor(i+31, c);
			strip.setPixelColor(i+32, c);
			strip.setPixelColor(58-i, c);
			strip.setPixelColor(59-i, c);
			strip.setPixelColor(60-i, c);
			strip.setPixelColor(90-i,c);
			strip.setPixelColor(89-i,c);
			strip.setPixelColor(88-i,c);
			strip.show();
strip.setPixelColor(i, 0, 0 ,0);
strip.setPixelColor(i+1, 0, 0, 0);
strip.setPixelColor(i+2, 0, 0, 0);
strip.setPixelColor(i+30, 0, 0, 0);
strip.setPixelColor(i+31, 0, 0, 0);
strip.setPixelColor(i+32, 0, 0, 0);
strip.setPixelColor(58-i, 0, 0, 0);
strip.setPixelColor(59-i, 0, 0, 0);
strip.setPixelColor(60-i, 0, 0, 0);
strip.setPixelColor(90-i, 0, 0, 0);
strip.setPixelColor(89-i, 0, 0, 0);
strip.setPixelColor(88-i, 0, 0, 0);
delay(wait);

}

for(uint16_t i=27; i>0; i--) {
strip.setPixelColor(i, c);
strip.setPixelColor(i+1, c);
strip.setPixelColor(i+2, c);
strip.setPixelColor(i+30, c);
strip.setPixelColor(i+31, c);
strip.setPixelColor(i+32, c);
strip.setPixelColor(58-i, c);
strip.setPixelColor(59-i, c);
strip.setPixelColor(60-i, c);
strip.setPixelColor(90-i,c);
strip.setPixelColor(89-i,c);
strip.setPixelColor(88-i,c);
strip.show();
strip.setPixelColor(i, 0, 0 ,0);
strip.setPixelColor(i+1, 0, 0, 0);
strip.setPixelColor(i+2, 0, 0, 0);
strip.setPixelColor(i+30, 0, 0, 0);
strip.setPixelColor(i+31, 0, 0, 0);
strip.setPixelColor(i+32, 0, 0, 0);
strip.setPixelColor(58-i, 0, 0, 0);
strip.setPixelColor(59-i, 0, 0, 0);
strip.setPixelColor(60-i, 0, 0, 0);
strip.setPixelColor(90-i, 0, 0, 0);
strip.setPixelColor(89-i, 0, 0, 0);
strip.setPixelColor(88-i, 0, 0, 0);
delay(wait);

}
}

//chaser lights from right to left
if (pattern == 2) {
	for (uint16_t i=0; i<90; i++) {
		strip.setPixelColor(i, c);
		strip.setPixelColor(i+1, c);
		strip.setPixelColor(i+2, c);
		strip.show();
		delay (25);
		strip.setPixelColor(i, 0,0,0);
		strip.setPixelColor(i+1, 0, 0, 0);
		strip.setPixelColor(i+2, 0, 0, 0);
		delay (25);
		strip.show();
	}
}

//fire fly effect (sudo random pixels)
if (pattern == 3) {
	for (uint16_t i=0; i<150; i++) {
		int randNumber = random(0,89);
		strip.setPixelColor(randNumber, c);
		strip.show();
		delay(50);
		strip.setPixelColor(randNumber, 0, 0, 0);
	}
}

//chaser lights from left to right
if (pattern == 4) {
	for (uint16_t i=90; i>0; i--) {
		strip.setPixelColor(i, c);
		strip.setPixelColor(i+1, c);
		strip.setPixelColor(i+2, c);
		strip.show();
		delay (25);
		strip.setPixelColor(i, 0,0,0);
		strip.setPixelColor(i+1, 0, 0, 0);
		strip.setPixelColor(i+2, 0, 0, 0);
		delay (25);
		strip.show();
	}
}

//knight rider style 
if (pattern == 5) {
	for (uint16_t i=0; i<90; i++) {
		strip.setPixelColor(i, c);
		strip.setPixelColor(i+1, c);
		strip.setPixelColor(i+2, c);
		strip.show();
		delay (25);
		strip.setPixelColor(i, 0,0,0);
		strip.setPixelColor(i+1, 0, 0, 0);
		strip.setPixelColor(i+2, 0, 0, 0);
		delay (25);
		strip.show();
	}
for (uint16_t i=90; i>0; i--) {
		strip.setPixelColor(i, c);
		strip.setPixelColor(i+1, c);
		strip.setPixelColor(i+2, c);
		strip.show();
		delay (25);
		strip.setPixelColor(i, 0,0,0);
		strip.setPixelColor(i+1, 0, 0, 0);
		strip.setPixelColor(i+2, 0, 0, 0);
		delay (25);
		strip.show();
	}
}

//top criss cross
if (pattern == 6) {
		for(uint16_t i=0; i<27; i++) {
			
			strip.setPixelColor(i+30, c);
			strip.setPixelColor(i+31, c);
			strip.setPixelColor(i+32, c);
			strip.setPixelColor(58-i, c);
			strip.setPixelColor(59-i, c);
			strip.setPixelColor(60-i, c);
			
			strip.show();

strip.setPixelColor(i+30, 0, 0, 0);
strip.setPixelColor(i+31, 0, 0, 0);
strip.setPixelColor(i+32, 0, 0, 0);
strip.setPixelColor(58-i, 0, 0, 0);
strip.setPixelColor(59-i, 0, 0, 0);
strip.setPixelColor(60-i, 0, 0, 0);
delay(wait);
}

for(uint16_t i=27; i>0; i--) {

strip.setPixelColor(i+30, c);
strip.setPixelColor(i+31, c);
strip.setPixelColor(i+32, c);
strip.setPixelColor(58-i, c);
strip.setPixelColor(59-i, c);
strip.setPixelColor(60-i, c);
strip.show();
strip.setPixelColor(i+30, 0, 0, 0);
strip.setPixelColor(i+31, 0, 0, 0);
strip.setPixelColor(i+32, 0, 0, 0);
strip.setPixelColor(58-i, 0, 0, 0);
strip.setPixelColor(59-i, 0, 0, 0);
strip.setPixelColor(60-i, 0, 0, 0);
delay(wait);
}
}

//both sides up and down
if (pattern == 7) {
		for(uint16_t i=0; i<27; i++) {
			strip.setPixelColor(i, c);
			strip.setPixelColor(i+1, c);
			strip.setPixelColor(i+2, c);
			
			strip.setPixelColor(90-i,c);
			strip.setPixelColor(89-i,c);
			strip.setPixelColor(88-i,c);
			strip.show();
strip.setPixelColor(i, 0, 0 ,0);
strip.setPixelColor(i+1, 0, 0, 0);
strip.setPixelColor(i+2, 0, 0, 0);

strip.setPixelColor(90-i, 0, 0, 0);
strip.setPixelColor(89-i, 0, 0, 0);
strip.setPixelColor(88-i, 0, 0, 0);
delay(wait);

}

for(uint16_t i=27; i>0; i--) {
strip.setPixelColor(i, c);
strip.setPixelColor(i+1, c);
strip.setPixelColor(i+2, c);

strip.setPixelColor(90-i,c);
strip.setPixelColor(89-i,c);
strip.setPixelColor(88-i,c);
strip.show();
strip.setPixelColor(i, 0, 0 ,0);
strip.setPixelColor(i+1, 0, 0, 0);
strip.setPixelColor(i+2, 0, 0, 0);

strip.setPixelColor(90-i, 0, 0, 0);
strip.setPixelColor(89-i, 0, 0, 0);
strip.setPixelColor(88-i, 0, 0, 0);
delay(wait);

}
}

//right side up and down
if (pattern == 8) {
		for(uint16_t i=0; i<27; i++) {
			strip.setPixelColor(i, c);
			strip.setPixelColor(i+1, c);
			strip.setPixelColor(i+2, c);
			
			strip.show();
strip.setPixelColor(i, 0, 0 ,0);
strip.setPixelColor(i+1, 0, 0, 0);
strip.setPixelColor(i+2, 0, 0, 0);

delay(wait);

}

for(uint16_t i=27; i>0; i--) {
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

//left side up and down
if (pattern == 9) {
		for(uint16_t i=0; i<27; i++) {
			
			strip.setPixelColor(90-i,c);
			strip.setPixelColor(89-i,c);
			strip.setPixelColor(88-i,c);
			strip.show();

strip.setPixelColor(90-i, 0, 0, 0);
strip.setPixelColor(89-i, 0, 0, 0);
strip.setPixelColor(88-i, 0, 0, 0);
delay(wait);

}

for(uint16_t i=27; i>0; i--) {

strip.setPixelColor(90-i,c);
strip.setPixelColor(89-i,c);
strip.setPixelColor(88-i,c);
strip.show();

strip.setPixelColor(90-i, 0, 0, 0);
strip.setPixelColor(89-i, 0, 0, 0);
strip.setPixelColor(88-i, 0, 0, 0);
delay(wait);

}
}

//knight rider style across top
if (pattern == 0) {
		for(uint16_t i=0; i<27; i++) {
			
			strip.setPixelColor(i+30, c);
			strip.setPixelColor(i+31, c);
			strip.setPixelColor(i+32, c);
			
			strip.show();

strip.setPixelColor(i+30, 0, 0, 0);
strip.setPixelColor(i+31, 0, 0, 0);
strip.setPixelColor(i+32, 0, 0, 0);

delay(wait);

}

for(uint16_t i=27; i>0; i--) {

strip.setPixelColor(i+30, c);
strip.setPixelColor(i+31, c);
strip.setPixelColor(i+32, c);

strip.show();

strip.setPixelColor(i+30, 0, 0, 0);
strip.setPixelColor(i+31, 0, 0, 0);
strip.setPixelColor(i+32, 0, 0, 0);

delay(wait);

}
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

