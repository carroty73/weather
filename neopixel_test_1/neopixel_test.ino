#include <Adafruit_NeoPixel.h>

// referanced by... : http://cafe.naver.com/neozcom/112
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel circle_24 = Adafruit_NeoPixel(24, 13, NEO_GRB + NEO_KHZ800);

void setup() {
  circle_24.begin();  
  circle_24.show();   
}

void loop() {
  rainbow(10);
  // Some example procedures showing how to display to the pixels:
  colorWipe24(circle_24.Color(255, 64, 64), 50);
  colorWipe24(circle_24.Color(0, 0, 0), 50);
  colorWipe24(circle_24.Color(32, 32, 255), 50);
  rainbow(20);
}

// Fill the dots one after the other with a color
void colorWipe24(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<circle_24.numPixels(); i++) {
      circle_24.setPixelColor(i, c);
      circle_24.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<circle_24.numPixels(); i++) {
      circle_24.setPixelColor(i, Wheel((i+j) & 255));
    }
    circle_24.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return circle_24.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
   WheelPos -= 85;
   return circle_24.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
   WheelPos -= 170;
   return circle_24.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

