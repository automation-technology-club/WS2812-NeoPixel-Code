#include<FastLED.h>
 
// Red, White, and Blue stripes with "glitter" flashes
// Mark Kriegsman, June 30, 2014
// requires FastLED v2.1 or later

#define NUM_LEDS    27
#define LED_PIN     3
#define LED5v_PIN	2
#define COLOR_ORDER GRB
#define BRIGHTNESS  64
 
CRGB    leds[NUM_LEDS];
uint8_t data[NUM_LEDS];
 
void setup() {
  delay(3000);
	FastLED.addLeds<WS2811, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(LED5v_PIN, OUTPUT);
  digitalWrite(LED5v_PIN, HIGH);
}
 
void loop() {
  fill_data_array();
  render_data_with_palette();   
  add_glitter();
  
  FastLED.show();
  FastLED.delay(20);
}
 
void fill_data_array()
{
  static uint8_t startValue = 0;
  startValue = startValue + 2;
  
  uint8_t value = startValue;  
  for( int i = 0; i < NUM_LEDS; i++) {
    data[i] = triwave8( value); // convert value to an up-and-down wave
    value += 7;
  }
}
 
 
CRGBPalette16 gPalette ( 
    CRGB::Black, CRGB::Black, 
    CRGB::Red,   CRGB::Red,  CRGB::Red,  CRGB::Red, 
    CRGB::Gray,  CRGB::Gray, CRGB::Gray, CRGB::Gray,
    CRGB::Blue,  CRGB::Blue, CRGB::Blue, CRGB::Blue,
    CRGB::Black, CRGB::Black
);
 
void render_data_with_palette()
{
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( gPalette, data[i], 128, BLEND);
  }
}
 
void add_glitter()
{
  int chance_of_glitter =  5; // percent of the time that we add glitter
  int number_of_glitters = 3; // number of glitter sparkles to add
  
  int r = random8(100);
  if( r < chance_of_glitter ) {
    for( int j = 0; j < number_of_glitters; j++) {
      int pos = random16( NUM_LEDS);
      leds[pos] = CRGB::White; // very bright glitter
    }
  }
}
