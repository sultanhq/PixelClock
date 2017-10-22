#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define DATAPIN    6

#define NUMPIXELS  60

#define STARTPIXEL 0

Adafruit_NeoPixel clock = Adafruit_NeoPixel(NUMPIXELS, DATAPIN, NEO_GRBW + NEO_KHZ800);

int r = 49;
int g = 49;
int b = 49;
int w = 1;

int secondBrightness = 49;
int minuteBrightness = 49;
int hourBrightness = 49;




uint32_t RED = clock.Color(r, 0, 0, 0);
uint32_t GREEN = clock.Color(0, g, 0, 0);
uint32_t BLUE = clock.Color(0, 0, b, 0);
uint32_t YELLOW = clock.Color(255, 100, 0, 0);
uint32_t WHITE = clock.Color(0, 0, 0, w);


int8_t second = 55;
int8_t minute = 59;
int8_t hour = 11;
uint8_t lastPixel = (clock.numPixels() - 1 );


unsigned long previousMillis = 0;
const long interval = 100;
union ArrayToInteger {
  byte array[4];
  uint32_t integer;
};

void setup() {
  Serial.begin(9600);
  Serial.println("Clock started");
  clock.begin();
  hour_mark();
  minuteHand();
  //  ArrayToInteger converter = {r, 0, 0, 0}; //Create a converter
  //  Serial.println(converter.integer); //Read the 32bit integer value.

}

void loop() {
  unsigned long secondMillis = millis();
  if (secondMillis - previousMillis >= interval) {
    previousMillis = secondMillis;
    secondHand();
  }
  clock.show();
}

int pixelPosition(int position) {
  return abs((position - 60 ) % 60);
}



void hour_mark() {
  for (int i = 0; i <= NUMPIXELS; i = (i + 5 )) {
    clock.setPixelColor(i, WHITE);
    //    clock.show();
  };
}

void secondHand() {
  Serial.print("Second: ");
  Serial.println(abs(second % 60));
  uint8_t red0 = clock.getPixelColor(pixelPosition(second - 1))   >> 16;
  uint8_t red  = clock.getPixelColor(pixelPosition(second))       >> 16;
  uint8_t green0 = clock.getPixelColor(pixelPosition(second - 1)) >> 8;
  uint8_t green = clock.getPixelColor(pixelPosition(second))      >> 8;
  uint8_t blue0 = clock.getPixelColor(pixelPosition(second - 1))  >> 0;
  uint8_t blue  = clock.getPixelColor(pixelPosition(second))      >> 0;
  uint8_t white0 = clock.getPixelColor(pixelPosition(second - 1))  >> 24;
  uint8_t white  = clock.getPixelColor(pixelPosition(second))      >> 24;


  // Serial.println("____________");
  // Serial.print("Pixel: ");
  // Serial.println(second);
  // Serial.print("red: ");
  // Serial.println(red);
  // Serial.print("green: ");
  // Serial.println(green);
  // Serial.print("blue: ");
  // Serial.println(blue);

  int bc = secondBrightness;
  for (uint8_t p = 0; p < secondBrightness; p++) {
    clock.setPixelColor(pixelPosition(second - 1), red0, green0, bc * 0.8, white0);
    clock.setPixelColor(pixelPosition(second), red,  green, p, white);
    clock.show();
    delay(10);
    bc--;
  }
  if (second == 59)  {
    second = 0;
    minuteHand();
    hourHand();
  }
  else {
    second++;
  }
}

void minuteHand() {
  Serial.print("Minute: ");
  Serial.println(abs(minute % 60));
  uint8_t red20 = clock.getPixelColor(pixelPosition(minute - 1))   >> 16;
  uint8_t red2  = clock.getPixelColor(pixelPosition(minute))       >> 16;
  uint8_t green20 = clock.getPixelColor(pixelPosition(minute - 1)) >> 8;
  uint8_t green2 = clock.getPixelColor(pixelPosition(minute))      >> 8;
  uint8_t blue20 = clock.getPixelColor(pixelPosition(minute - 1))  >> 0;
  uint8_t blue2  = clock.getPixelColor(pixelPosition(minute))      >> 0;
  uint8_t white20 = clock.getPixelColor(pixelPosition(minute - 1))  >> 24;
  uint8_t white2  = clock.getPixelColor(pixelPosition(minute))      >> 24;


  int bc = minuteBrightness;
  for (uint8_t p = 0; p < minuteBrightness; p++) {
    clock.setPixelColor(pixelPosition(minute - 1), red20, bc * 0.8, blue20, white20);
    clock.setPixelColor(pixelPosition(minute), red2, p, blue2, white2);
    bc--;
    delay(10);
  }
  if (minute == 59)  {
    minute = 0;
    //    hourHand();
  }
  else {
    minute++;
  }
}

void hourHand() {
  Serial.print("Hour: ");
  Serial.println(abs(hour % 60));
  Serial.println(hour);

  uint8_t red30 = clock.getPixelColor(pixelPosition((hour * 5) - 5))   >> 16;
  uint8_t red3  = clock.getPixelColor(pixelPosition((hour * 5)))       >> 16;
  uint8_t green30 = clock.getPixelColor(pixelPosition((hour * 5) - 5)) >> 8;
  uint8_t green3 = clock.getPixelColor(pixelPosition((hour * 5)))      >> 8;
  uint8_t blue30 = clock.getPixelColor(pixelPosition((hour * 5) - 5))  >> 0;
  uint8_t blue3  = clock.getPixelColor(pixelPosition((hour * 5)))      >> 0;
  uint8_t white30 = clock.getPixelColor(pixelPosition((hour * 5) - 5))  >> 24;
  uint8_t white3  = clock.getPixelColor(pixelPosition((hour * 5)))      >> 24;


  int bc = hourBrightness;
  for (uint8_t p = 0; p < hourBrightness; p++) {
    clock.setPixelColor(pixelPosition((hour * 5) - 5), bc * 0.8, green30, blue30, white30);
    clock.setPixelColor(pixelPosition((hour * 5)), p, green3, blue3, white3);
    bc--;
  }

  if (hour == 11)  {
    hour = 0;
  }
  else {
    hour++;
  }
}
