
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
radio.openWritingPipe(pipe);
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
for (int i=0; i<11; i++) {
	radio.write(&i,sizeof(i));
	delay(8000);
}
}
