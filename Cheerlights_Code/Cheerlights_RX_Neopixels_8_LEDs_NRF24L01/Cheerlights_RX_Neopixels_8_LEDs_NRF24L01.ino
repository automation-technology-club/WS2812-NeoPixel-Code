
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <nRF24L01.h>
#include <RF24.h>
int response;

// Variable Setup
#define CE_PIN 10
#define CSN_PIN 9

const uint64_t pipe = 0xE8E8F0F0E1LL;
int colornumber = 2;
int wait = 50;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, 6, NEO_GRB + NEO_KHZ800);
RF24 radio(CE_PIN, CSN_PIN);
// Initialize Arduino Ethernet Client

void setup() {
delay(100);
radio.begin();
radio.openReadingPipe(2,pipe);
radio.startListening();;
// Setup Serial
Serial.begin(9600);
delay(100);
Serial.flush();
delay(100);

strip.begin();
strip.show();

}

void loop() {
// Process CheerLights Commands
if(radio.available() )
{
	bool done = false;
	while (!done)
	{
		done = radio.read( &response, sizeof(response));
	}
delay(100);
Serial.print("Got from Radio: ");
Serial.println(response);
}


	if (response == 1 )
{

colorWipe(strip.Color(255,255,255),50);
}
else if (response == 2)
{

colorWipe(strip.Color(0,0,0),50);
}
else if (response == 3)
{

colorWipe(strip.Color(255,0,0),50);
}
else if (response == 4)
{

colorWipe(strip.Color(0, 255, 0), 50);
}
else if (response == 5)
{

colorWipe(strip.Color(0,0,255),50);
}
else if (response == 6)
{

colorWipe(strip.Color(0,255,255),50);
}
else if (response == 7)
{

colorWipe(strip.Color(255,0,255),50);
}
else if (response == 8)
{

colorWipe(strip.Color(255,255,0),50);
}
else if (response == 9)
{

colorWipe(strip.Color(102,51,204),50);
}
else if (response == 10)
{

colorWipe(strip.Color(255,153,0),50);
}
else if (response == 11)
{

colorWipe(strip.Color(255,53,153),50);
}

delay(400);
}


void colorWipe(uint32_t c, uint8_t wait) {

		for(uint16_t i=0; i<8; i++) {
			strip.setPixelColor(i, c);
			strip.show();
strip.setPixelColor(i, 0, 0 ,0);
delay(wait);

}

for(uint16_t i=8; i>0; i--) {
strip.setPixelColor(i, c);
strip.show();
strip.setPixelColor(i, 0, 0 ,0);
delay(wait);

}
}




