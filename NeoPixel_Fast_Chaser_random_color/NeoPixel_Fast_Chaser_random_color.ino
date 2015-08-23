
#include <Adafruit_NeoPixel.h>
int pixels = 27;
int wait = 1000;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixels, 3, NEO_RGB + NEO_KHZ400);


void setup() {
strip.begin();
strip.show();

}

void loop() {
/*
colorWipe(strip.Color(255,255,255),50);
//delay(50);
//colorWipe(strip.Color(0,0,0),50);
//delay(50);
colorWipe(strip.Color(255,0,0),50);
//delay(50);
colorWipe(strip.Color(0, 255, 0), 50);
//delay(50);
colorWipe(strip.Color(0,0,255),50);
//delay(50);
colorWipe(strip.Color(0,255,255),50);
//delay(50);
colorWipe(strip.Color(255,0,255),50);
//delay(50);
colorWipe(strip.Color(255,255,0),50);
//delay(50);
colorWipe(strip.Color(102,51,204),50);
//delay(50);
colorWipe(strip.Color(255,153,0),50);
*/
colorWipe(strip.Color(random(255),random(255),random(255)),50);

}


void colorWipe(uint32_t c, uint8_t wait) {
for(uint16_t i=0; i<strip.numPixels(); i++) {
strip.setPixelColor(i, c);
delay(30);
//strip.setPixelColor(i+1, c);
//strip.setPixelColor(i+2, c);
strip.show();
strip.setPixelColor(i, 0, 0 ,0);
//strip.setPixelColor(i+1, 0, 0, 0);
//strip.setPixelColor(i+2, 0, 0, 0);

delay(30);

}

for(uint16_t i=strip.numPixels(); i>0; i--) {
strip.setPixelColor(i, c);
delay(30);
//strip.setPixelColor(i+1, c);
//strip.setPixelColor(i+2, c);
strip.show();
strip.setPixelColor(i, 0, 0 ,0);
//strip.setPixelColor(i+1, 0, 0, 0);
//strip.setPixelColor(i+2, 0, 0, 0);

delay(30);

}
}





