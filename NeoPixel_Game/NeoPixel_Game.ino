#include <Adafruit_NeoPixel.h>

#define PIN 3

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(21, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

const uint32_t Red = strip.Color(255, 0, 0);
const uint32_t Crimson = strip.Color(254, 0, 0);
const uint32_t Green = strip.Color(0, 255, 0);
const uint32_t Teal = strip.Color(0, 0, 254);
const uint32_t Blue = strip.Color(0, 0, 255);
const uint32_t Dark = strip.Color(0, 0, 0);

int playerx;
int playerd;
int t;


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
    //strip.setBrightness(127);
  
  playerx = 60;
  playerd = 1;
  t = 0;
}


void loop() {
  if (t%3 == 0)
    MovePlayer();
    
  MoveLasers();
  
  Shoot();
  
  if (t%10 == 0)
    MoveEnemies();
    
  if (t%10 == 0)
    GenerateEnemies();
    
  strip.show();
  t ++;
  delay(10);
}


void MovePlayer() {
  if (digitalRead(1)) {
    strip.setPixelColor(playerx, Dark);
    playerx ++;
    strip.setPixelColor(playerx, Green);
  }
  
  if (digitalRead(3)) {
    strip.setPixelColor(playerx, Dark);
    playerx --;
    strip.setPixelColor(playerx, Green);
  }
}


void MoveLasers() {
  for (int i = 119; i >= 0; i --)
    if (strip.getPixelColor(i) == Blue)
    {
      strip.setPixelColor(i, Dark);
      strip.setPixelColor(i+1, Blue);
    }
  
  for (int i = 0; i < 120; i ++)
    if (strip.getPixelColor(i) == Teal)
    {
      strip.setPixelColor(i, Dark);
      strip.setPixelColor(i-1, Teal);
    }
}


void Shoot() {
  if (digitalRead(2)) {
    if (playerd == 1)
      strip.setPixelColor(playerx+playerd, Blue);
    else
      strip.setPixelColor(playerx+playerd, Teal);
  }
}


void MoveEnemies() {
  for (int i = 119; i >= 0; i --)
    if (strip.getPixelColor(i) == Red)
    {
      strip.setPixelColor(i, Dark);
      strip.setPixelColor(i+1, Red);
    }
  
  for (int i = 0; i < 120; i ++)
    if (strip.getPixelColor(i) == Crimson)
    {
      strip.setPixelColor(i, Dark);
      strip.setPixelColor(i-1, Crimson);
    }
}


void GenerateEnemies() {
  if (random(10) == 0)
    strip.setPixelColor(0, Red);
  if (random(10) == 0)
    strip.setPixelColor(119, Crimson);
}


void Death() {
  for (int t = 0; t < 10; t ++) {
    for (int i = 59 - t%3; i >= 0; i -= 3)
      strip.setPixelColor(i, Red);
    for (int i = 60 + t%3; i < 120; i +=3)
      strip.setPixelColor(i, Red);
    delay(50);
  }
}

