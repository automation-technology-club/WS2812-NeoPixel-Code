
#include <Adafruit_NeoPixel.h>
int pixels = 30;
int wait = 5;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixels, 3, NEO_GRB + NEO_KHZ800);


void setup() {
strip.begin();
strip.show();

}

void loop() {

colorWipe(strip.Color(255,255,255),50);
//delay(50);
colorWipe(strip.Color(0,0,0),50);
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

for(uint16_t i=strip.numPixels(); i>0; i--) {
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





