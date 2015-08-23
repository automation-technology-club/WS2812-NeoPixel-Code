#include <Adafruit_NeoPixel.h>
int pixels = 30;
int wait = 1000;

//Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixels, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixels, 3, NEO_RGB + NEO_KHZ400);

void setup() {
strip.begin();
strip.show();


}

void loop() {

for(int r=0; r<255; r++){
	for (int b = 0; b<255; b++){
		for (int g = 0; g<255; g++) {
strip.setPixelColor(2, g,r,b);
strip.setPixelColor(4,g,r,b);
strip.setPixelColor(0,g,r,b);
strip.setPixelColor(6, g,r,b);
strip.setPixelColor(8, g,r,b);
strip.setPixelColor(9, g, r, b);
strip.setPixelColor(11, g, r, b);
strip.setPixelColor(13, g, r, b);
strip.setPixelColor(15, g, r, b);
strip.setPixelColor(17, g, r, b);
strip.setPixelColor(21, g, r, b);
strip.setPixelColor(22, g, r, b);
strip.setPixelColor(23, g, r, b);
strip.show();

}}}

}


void colorWipe(uint32_t c, uint8_t wait) {
for(uint16_t i=0; i<strip.numPixels(); i++) {
strip.setPixelColor(i, c);
delay(100);
//strip.setPixelColor(i+1, c);
//strip.setPixelColor(i+2, c);
strip.show();
strip.setPixelColor(i, 0, 0 ,0);
//strip.setPixelColor(i+1, 0, 0, 0);
//strip.setPixelColor(i+2, 0, 0, 0);

delay(wait);

}

for(uint16_t i=strip.numPixels(); i>0; i--) {
strip.setPixelColor(i, c);
delay(wait);
//strip.setPixelColor(i+1, c);
//strip.setPixelColor(i+2, c);
strip.show();
strip.setPixelColor(i, 0, 0 ,0);
//strip.setPixelColor(i+1, 0, 0, 0);
//strip.setPixelColor(i+2, 0, 0, 0);

delay(wait);

}
}





