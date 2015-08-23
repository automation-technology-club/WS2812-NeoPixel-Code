// scrolls data read from serial to matrix
// the following libraries are required for the sketch to work
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#define PIN 3
String readString; // creates the string scrolling text will be held in
// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
// NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
// Position of the FIRST LED in the matrix; pick two, e.g.
// NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
// NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
// rows or in vertical columns, respectively; pick one or the other.
// NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
// in the same order, or alternate lines reverse direction; pick one.
// See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// Example for NeoPixel Shield. In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino. When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order. The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 4, PIN,
NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
NEO_GRB + NEO_KHZ800);
//sets up colors for scrolling text - in this sketch only the first one is used
const uint16_t colors[] =
{
matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};
void setup()
{
Serial.begin(9600); //turn on the serial connection
matrix.begin(); //initalize the matrix
matrix.setTextWrap(false);
matrix.setBrightness(40);
matrix.setTextColor(colors[0]);
}
int x = matrix.width(); //holds the width of the matrix for counting colums
int pass = 0; //used to calculate the number of characters read from the serial input
void loop ()
{
matrix.fillScreen(0); //clear the screen
matrix.setCursor(x, 0); //set the begining cursor position
serialtochar();
chartoscreen();
} //end loop
void serialtochar()
{
while (Serial.available()) //if serial data is available, run the loop
{
delay(10);
if (Serial.available() > 0) //if there is serial data continue
{
char c = Serial.read(); //read the next byte of data
readString += c; //append the data to the char variable readString
}
}
}
void chartoscreen()
{
if (readString.length() > 0) //if the number of bytes in readString are greater than 0
{
matrix.println(readString); //print the data in readString
pass = -abs(readString.length()); //set pass to the negative value of the number of characters
if(--x < pass * 6) //reserve 6 spaces for each character - continue looping until x = pass * 6
{
x = matrix.width(); //set x to the number of colums in the matrix
readString = ""; //set the data to blank
}
matrix.show(); //show the data stored
delay(500); //wait a bit - sets scrolling speed
}
}

