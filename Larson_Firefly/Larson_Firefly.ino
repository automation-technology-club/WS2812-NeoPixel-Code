#include <Adafruit_NeoPixel.h>
 
#define N_LEDS 20
#define PIN 3
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
strip.begin();
strip.setBrightness(3);
}
 
int pos = 0, dir = 1; // Position, direction of "eye"
 
void loop() {
uint32_t firefly = strip.Color(221, 228, 20);
int j;
 
// Draw 5 pixels centered on pos. setPixelColor() will clip any
// pixels off the ends of the strip, we don't need to watch for that.
//strip.setPixelColor(pos - 2, 205,219,45); // Dark red
//strip.setPixelColor(pos - 1, 214,220, 37); // Medium red
strip.setPixelColor(pos , 228,221,20); // Center pixel is brightest
//strip.setPixelColor(pos + 1, 214,220, 37); // Medium red
//strip.setPixelColor(pos + 2, 0x100000); // Dark red
 
strip.show();
//delay(30);
delay(150);
 
// Rather than being sneaky and erasing just the tail pixel,
// it's easier to erase it all and draw a new one next time.
for(j=-2; j<= 2; j++) strip.setPixelColor(pos+j, 0);
 
// Bounce off ends of strip
pos += dir;
if(pos < 0) {
pos = 1;
 dir = -dir;
} else if(pos >= strip.numPixels()) {
pos = strip.numPixels() - 2;
dir = -dir;
}
}
