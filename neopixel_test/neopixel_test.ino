#include <Adafruit_NeoPixel.h>

// referanced by... : http://cafe.naver.com/neozcom/112
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel neoPixel24 = Adafruit_NeoPixel(24, 13, NEO_GRB+NEO_KHZ800);

#define RED      0xFF0000
#define GREEN    0x00FF00
#define BLUE     0x0000FF
#define YELLOW   0xFFFF00
#define CYAN     0x00FFFF
#define MAGENTA  0xFF00FF
#define WHITE    0xFFFFFF
#define FULL_OFF 0x000000

void setup() {
  neoPixel24.begin();  
  neoPixel24.show(); // Initialize all pixels to 'off'
}

void neoPixel24Sample1() {
  neoPixel24.setPixelColor(0, 0xFF0000); // Red
  neoPixel24.setPixelColor(1, 0x00FF00); // Green
  neoPixel24.setPixelColor(2, 0x0000FF); // Blue 
  neoPixel24.setPixelColor(3, 0xFFFF00); // Yellow
  neoPixel24.setPixelColor(4, 0x00FFFF); // Cyan
  neoPixel24.setPixelColor(5, 0xFF00FF); // Magenta
      
  neoPixel24.setPixelColor(6, 0xFF0000); // Red
  neoPixel24.setPixelColor(7, 0x00FF00); // Green
  neoPixel24.setPixelColor(8, 0x0000FF); // Blue 
  neoPixel24.setPixelColor(9, 0xFFFF00); // Yellow
  neoPixel24.setPixelColor(10, 0x00FFFF); // Cyan
  neoPixel24.setPixelColor(11, 0xFF00FF); // Magenta
      
  neoPixel24.setPixelColor(12, 0xFF0000); // Red
  neoPixel24.setPixelColor(13, 0x00FF00); // Green
  neoPixel24.setPixelColor(14, 0x0000FF); // Blue 
  neoPixel24.setPixelColor(15, 0xFFFF00); // Yellow
  neoPixel24.setPixelColor(16, 0x00FFFF); // Cyan
  neoPixel24.setPixelColor(17, 0xFF00FF); // Magenta
      
  neoPixel24.setPixelColor(18, 0xFF0000); // Red
  neoPixel24.setPixelColor(19, 0x00FF00); // Green
  neoPixel24.setPixelColor(20, 0x0000FF); // Blue 
  neoPixel24.setPixelColor(21, 0xFFFF00); // Yellow
  neoPixel24.setPixelColor(22, 0x00FFFF); // Cyan
  neoPixel24.setPixelColor(23, 0xFF00FF); // Magenta  
  neoPixel24.show();
}

void neoPixel24Sample2() {
  // Some example procedures showing how to display to the pixels:
  colorWipe24(neoPixel24.Color(0xFF, 0x00, 0x00), 100); // Red
  colorWipe24(neoPixel24.Color(0x00, 0xFF, 0x00), 100); // Green
  colorWipe24(neoPixel24.Color(0x00, 0x00, 0xFF), 100); // Blue 
  colorWipe24(neoPixel24.Color(0xFF, 0xFF, 0x00), 100); // Yellow
  colorWipe24(neoPixel24.Color(0x00, 0xFF, 0xFF), 100); // Cyan
  colorWipe24(neoPixel24.Color(0xFF, 0x00, 0xFF), 100); // Magenta
  colorWipe24(neoPixel24.Color(0xFF, 0xFF, 0xFF), 100); // White
  colorWipe24(neoPixel24.Color(0x00, 0x00, 0x00), 100); // Off
}

// rotate function
void rotate(uint32_t color, uint8_t wait) {
  for(uint16_t i= 0; i<neoPixel24.numPixels(); i++) {
    neoPixel24.setPixelColor(i, color); // 
    neoPixel24.show();
    delay(wait);
    neoPixel24.setPixelColor(i, FULL_OFF); // Off
  }
}

void loop() {
//  rainbow(20);
//  rainbowCycle(20);
  //for(uint16_t i= 100; i>0; i -= 10) { rotate(CYAN, i); }    
  //for(uint16_t j= 0; j<100; j += 10) { rotate(CYAN, j); }
  comet(0x0000FF, 100);
}

/*
int array1[24]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
int array2[24]= {23,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
int array3[24]= {22,23,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
int array4[24]= {21,22,23,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
int array5[24]= {20,21,22,23,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
int array6[24]= {19,20,21,22,23,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};

void comet(uint32_t color, uint8_t wait) {
  for(uint16_t i= 0; i<neoPixel24.numPixels(); i++) {
    neoPixel24.setPixelColor(array1[i], 0x0000FF); 
    neoPixel24.setPixelColor(array2[i], 0x0000AA); 
    neoPixel24.setPixelColor(array3[i], 0x000077); 
    neoPixel24.setPixelColor(array4[i], 0x000055); 
    neoPixel24.setPixelColor(array5[i], 0x000033); 
    neoPixel24.setPixelColor(array6[i], 0x000011);     
    neoPixel24.show();
    delay(wait);
    neoPixel24.setPixelColor(array1[i], FULL_OFF); 
    neoPixel24.setPixelColor(array2[i], FULL_OFF); 
    neoPixel24.setPixelColor(array3[i], FULL_OFF); 
    neoPixel24.setPixelColor(array4[i], FULL_OFF); 
    neoPixel24.setPixelColor(array5[i], FULL_OFF); 
    neoPixel24.setPixelColor(array6[i], FULL_OFF);
  }
}
*/

void comet(uint32_t color, uint8_t wait) {
  uint8_t MAX_PIXEL= neoPixel24.numPixels();
  for(uint16_t i= 0; i<neoPixel24.numPixels(); i++) {
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-0))%MAX_PIXEL, 0x0000FF); 
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-1))%MAX_PIXEL, 0x0000AA); 
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-2))%MAX_PIXEL, 0x000077);
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-3))%MAX_PIXEL, 0x000055); 
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-4))%MAX_PIXEL, 0x000033); 
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-5))%MAX_PIXEL, 0x000011); 
    neoPixel24.show();
    delay(wait);
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-0))%MAX_PIXEL, FULL_OFF); 
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-1))%MAX_PIXEL, FULL_OFF); 
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-2))%MAX_PIXEL, FULL_OFF);
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-3))%MAX_PIXEL, FULL_OFF); 
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-4))%MAX_PIXEL, FULL_OFF); 
    neoPixel24.setPixelColor((i+((MAX_PIXEL-1)-5))%MAX_PIXEL, FULL_OFF); 
  }
}
// Fill the dots one after the other with a color
void colorWipe24(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<neoPixel24.numPixels(); i++) {
      neoPixel24.setPixelColor(i, c);
      neoPixel24.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i= 0;
  uint16_t j= 0;

  for(j=0; j<256; j++) {
    for(i=0; i<neoPixel24.numPixels(); i++) {
      neoPixel24.setPixelColor(i, Wheel((i+j) & 255));
    }
    neoPixel24.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i= 0;
  uint16_t j= 0;

  for(j=0; j<256; j++) {
    for(i=0; i<neoPixel24.numPixels(); i++) {
      neoPixel24.setPixelColor(i, Wheel(((i * 256 / neoPixel24.numPixels()) + j) & 255));
    }
    neoPixel24.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r-g-b-back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return neoPixel24.Color(WheelPos*3, 255-WheelPos*3, 0);
  } 
  else if(WheelPos < 170) {
   WheelPos -= 85;
   return neoPixel24.Color(255-WheelPos*3, 0, WheelPos*3);
  } 
  else {
   WheelPos -= 170;
   return neoPixel24.Color(0, WheelPos*3, 255-WheelPos*3);
  }
}

