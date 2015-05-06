#include <Adafruit_NeoPixel.h>

const int tempPin= A0;

// referanced by... : http://cafe.naver.com/neozcom/112
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel neoPixel24 = Adafruit_NeoPixel(24, 13, NEO_GRB + NEO_KHZ800);
//uint32_t temperature= 0;
int adcValue= 0;
uint32_t convAdcValue= 0; // 0-255 convert
uint32_t colorValue= 0;
unsigned char ledPos= 0;

void setup() {
  neoPixel24.begin();  
  neoPixel24.show();   
}

void loop() {
  /*
  rainbow(10);
  // Some example procedures showing how to display to the pixels:
  colorWipe24(neoPixel24.Color(255, 64, 64), 50);
  colorWipe24(neoPixel24.Color(0, 0, 0), 50);
  colorWipe24(neoPixel24.Color(32, 32, 255), 50);
  rainbow(20);
  */
  /*
  neoPixel24.setPixelColor(1, 0xFF0000);
  neoPixel24.setPixelColor(2, 0xCC0000);
  neoPixel24.setPixelColor(3, 0xAA0000);
  neoPixel24.setPixelColor(4, 0x880000);
  neoPixel24.setPixelColor(5, 0x660000);
  neoPixel24.setPixelColor(6, 0x440000);
  neoPixel24.setPixelColor(7, 0x220000);
  neoPixel24.setPixelColor(8, 0x110000);
  neoPixel24.setPixelColor(9, 0x80000);
  neoPixel24.setPixelColor(10, 0x020000);
  neoPixel24.show();
  */
  adcValue= analogRead(tempPin);
  convAdcValue= map(adcValue, 0, 1023, 0, 255);  

  // red
  if((convAdcValue>0)&&(convAdcValue<=50)) {
    colorValue = (convAdcValue << 16)*5;
  }
  // ju whang
  else if((convAdcValue>50)&&(convAdcValue<=100)) {
    colorValue = convAdcValue << 8;
    colorValue |= 0xFF0000;
  }
  else if((convAdcValue>100)&&(convAdcValue<=150)) {
    colorValue |= 0xFFFF00;
  }  
  
  else if((convAdcValue>100)&&(convAdcValue<=150)) {
    colorValue = convAdcValue<<8;
  }   

  else if((convAdcValue>150)&&(convAdcValue<=200)) {
    colorValue = convAdcValue/5;
  } 

  neoPixel24.setPixelColor(ledPos, colorValue);
  ledPos++;
  if(ledPos==neoPixel24.numPixels()+1) {ledPos= 0;}
  neoPixel24.show();
  delay(50);
      
  if(ledPos != 0) { 
    neoPixel24.setPixelColor(ledPos-1, 0);
  }
  else if(ledPos == 0) { 
    neoPixel24.setPixelColor(neoPixel24.numPixels(), 0);         
  }
  neoPixel24.show();
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
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<neoPixel24.numPixels(); i++) {
      neoPixel24.setPixelColor(i, Wheel((i+j) & 255));
    }
    neoPixel24.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return neoPixel24.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
   WheelPos -= 85;
   return neoPixel24.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
   WheelPos -= 170;
   return neoPixel24.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

