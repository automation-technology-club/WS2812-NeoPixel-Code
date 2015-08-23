// Low power NeoPixel goggles example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!
 
/*10/10/14 Mario - Mario.Mtechcreations.com
 
Added code to allow the NeoPixels to work with a 5V Trinket.
Also added third lighting effect, which I call broken mode\
as it looks as thought the lights are starting to fail before\
the lights go to sparks
 
*/
#include <Adafruit_NeoPixel.h>
 #ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  #include <avr/power.h>
#endif
#define PIN 3
  
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(21, PIN);
  
uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFF0000; // Start red
uint32_t prevTime;
  
void setup() {
   #ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
  // Seed random number generator from an unused analog input:
  randomSeed(analogRead(2));
#else
  randomSeed(analogRead(A0));
#endif
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
  prevTime = millis();
}
  
void loop() {
  uint8_t  i;
  uint8_t  i2;
  uint32_t t;
  
  switch(mode) {
  
   case 0:                         // Random sparks - just one LED on at a time!
    i = random(32);                //Pick Pixle at Random
    pixels.setPixelColor(i, color);//Set random pixel to current color
    pixels.show();//Update
    delay(10);
    pixels.setPixelColor(i, 0);     //Clear
    break;
  
   case 1: // Spinny wheels (8 LEDs on at a time)
    for(i=0; i<16; i++) {
      uint32_t c = 0;
      if(((offset + i) & 7) < 2) c = color; // 4 pixels on...
      pixels.setPixelColor(   i, c);        // First eye
      pixels.setPixelColor(31-i, c);        // Second eye (flipped)
    }
    pixels.show();
    offset--;
    delay(50);
    break;
     
    case 2: // Spinny wheels (8 LEDs on at a time) with sparks of next Color
     
     
    for(i=0; i<16; i++) {
      uint32_t c = 0;
      if(((offset + i) & 7) < 2) c = color; // 4 pixels on...
      pixels.setPixelColor(   i, c);        // First eye
      pixels.setPixelColor(31-i, c);        // Second eye (flipped)
      if(random(10)>4)                      //adds extra pixel of a different color randomly
      {
          i2 = random(32);
          pixels.setPixelColor(i2, check(color>>8));//Sets random Pixel to next color
      }
    }
    pixels.show();
    pixels.setPixelColor(i2, 0);
    offset--;
    delay(50);
    break;
  }
  
  t = millis();
  if((t - prevTime) > 8000) {      // Every 8 seconds...
    mode++;                        // Next mode
    if(mode > 2) {                 // End of modes?
      mode = 0;                    // Start modes over
      color >>= 8;                 // Next color R->G->B
      if(!color) color = 0xFF0000; // Reset to red
    }
    for(i=0; i<32; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
  }
}
uint32_t check(uint32_t ctest)//Used to check if current color is not 0x00 or off and if it is
//Return Red or the starting color
{
  if(ctest==0x00)
  {
    return 0xFF0000;//returns Red
  }
  else return ctest;//returns Hex which was past to the function
}


