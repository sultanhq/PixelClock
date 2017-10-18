#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define DATAPIN            6

#define NUMPIXELS      40

Adafruit_NeoPixel clock = Adafruit_NeoPixel(NUMPIXELS, DATAPIN, NEO_GRB + NEO_KHZ800);

int r = 49;
int g = 49;
int b = 49;

int secondBrightness = 49;
int minuteBrightness = 49;


uint32_t RED = clock.Color(r, 0, 0);
uint32_t GREEN = clock.Color(0, g, 0);
uint32_t BLUE = clock.Color(0, 0, b);

int delayval = 1000; // delay for half a second
int8_t second = 0;
int8_t minute = 0;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(9600);
  clock.begin();
  hour_mark();
  minuteHand();
}

void loop() {

  unsigned long secondMillis = millis();

  if (secondMillis - previousMillis >= interval) {
    previousMillis = secondMillis;
    secondHand();
  }

  clock.show();
}

void hour_mark() {
  for (int i = 0; i <= NUMPIXELS; i = (i + 5 )) {
    clock.setPixelColor(i, RED);
    clock.show();
  };
}

void secondHand() {

  Serial.println("____________");
  Serial.print("Pixel: ");
  Serial.println(second);

  uint8_t red0 = clock.getPixelColor(pixelPosition(second - 1))   >> 16;
  uint8_t red  = clock.getPixelColor(pixelPosition(second))   >> 16;
  Serial.print("red: ");
  Serial.println(red);
  uint8_t green0 = clock.getPixelColor(pixelPosition(second - 1)) >> 8;
  uint8_t green = clock.getPixelColor(pixelPosition(second))      >> 8;
  Serial.print("green: ");
  Serial.println(green);
  uint8_t blue0 = clock.getPixelColor(pixelPosition(second - 1))  >> 0;
  uint8_t blue  = clock.getPixelColor(pixelPosition(second))  >> 0;
  Serial.print("blue: ");
  Serial.println(blue);

  int bc = secondBrightness;
  for (uint8_t p = 0; p < secondBrightness; p++) {
    clock.setPixelColor(pixelPosition(second - 1) , red0, green0, bc * 0.8);
    clock.setPixelColor(pixelPosition(second)     , red,  green, p);
    clock.show();
    delay(10);
    bc--;
  }

  if (second == clock.numPixels() - 1)  {
    second = 0;
    minuteHand();
  }
  else {
    second++;
  }


}

int pixelPosition(int position) {
  return ((position + clock.numPixels() ) % clock.numPixels() );
}

void minuteHand() {
  uint8_t red20 = clock.getPixelColor(pixelPosition(minute - 1))   >> 16;
  uint8_t red2  = clock.getPixelColor(pixelPosition(minute))       >> 16;
  uint8_t green20 = clock.getPixelColor(pixelPosition(minute - 1)) >> 8;
  uint8_t green2 = clock.getPixelColor(pixelPosition(minute))      >> 8;
  uint8_t blue20 = clock.getPixelColor(pixelPosition(minute - 1))  >> 0;
  uint8_t blue2  = clock.getPixelColor(pixelPosition(minute))      >> 0;

  int bc = minuteBrightness;
  for (uint8_t p = 0; p < minuteBrightness; p++) {
    clock.setPixelColor(pixelPosition(minute - 1) , red20, bc * 0.8 , blue20);
    clock.setPixelColor(pixelPosition(minute)     , red2, p , blue2);
    clock.show();
    delay(10);
    bc--;
  }

  if (minute == clock.numPixels() - 1 )  {
    minute = 0;
  }
  else {
    minute++;
  }

}

