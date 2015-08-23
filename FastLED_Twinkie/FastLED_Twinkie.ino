#include <FastLED.h>                                           // FastLED library

#define NUM_LEDS 27                                           // Number of LED's
#define datapin 3                                             // Data pin
#define LED_TYPE NEOPIXEL                                        // What kind of strip are you using?
#define BRIGHTNESS  100                                        // How bright do we want to go

struct CRGB ledsA[NUM_LEDS];                                    // Initializxe our array

// Initialize global variables for sequences
int thisdelay = 8;                                                 // A delay value for the sequence(s)


void setup(){
  LEDS.setBrightness(BRIGHTNESS);
  LEDS.addLeds<NEOPIXEL, datapin>(ledsA, NUM_LEDS);
  memset(ledsA, 0,  NUM_LEDS * sizeof(struct CRGB));
}

unsigned long functionDuration = 10*60UL;//30*60000UL; 
unsigned long cycleStart;
int state;


void loop () {
  twinkle();
}

void twinkle() {
  int i = random(NUM_LEDS);                                           // A random number. Higher number => fewer twinkles. Use random16() for values >255.
  if (i < NUM_LEDS) ledsA[i] = CHSV(random(255), random(255), random(255));              // Only the lowest probability twinkles will do. You could even randomize the hue/saturation. .
  for (int j = 0; j < NUM_LEDS; j++) ledsA[j].fadeToBlackBy(8);
  
  LEDS.show();                                                // Standard FastLED display
  //show_at_max_brightness_for_power();                          // Power managed FastLED display

  //delay(10);                                            // Standard delay
  LEDS.delay(50);                                     // FastLED delay 
  //delay_at_max_brightness_for_power(thisdelay);              // Power managed FastLED delay
} // twinkle()
