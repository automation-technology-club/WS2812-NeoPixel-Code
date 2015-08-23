// NeoPixel functions
#include <Adafruit_NeoPixel.h>
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
// Set Neopixel data-in pin
#define NEOPIN 3

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(21, NEOPIN, NEO_GRB + NEO_KHZ800);

RTC_DS1307 RTC;


void setup () {
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
 // RTC.adjust(DateTime(__DATE__, __TIME__));
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    
  }
 {
  strip.begin ();
  strip.show (); // Initialize all pixels to 'off'
}
}
 
void loop () {
    DateTime now = RTC.now();
    strip.setPixelColor(map (millis() % 1000, 0, 1000, 0, strip.numPixels()), 5, 20, 15);
    // strip.setPixelColor(map (millis() % 1000, 0, 1000, 0, strip.numPixels())-1, 5, 10, 5);
	strip.setPixelColor(map (now.second(), 0, 60, 0, strip.numPixels()), 0, 0, 20);
    strip.setPixelColor(map (now.minute(), 0, 60, 0, strip.numPixels()), 20, 0, 0);
    strip.setPixelColor(map (now.hour() % 12, 0, 12, 0, strip.numPixels()), 0, 20, 0);
    strip.show();
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay (15);
for(uint16_t i=0; i<strip.numPixels (); i++) {
      strip.setPixelColor (i, 0, 0, 0);
}
strip.show ();
}
