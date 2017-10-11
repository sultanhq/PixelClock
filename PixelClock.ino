// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      6

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel clock = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int r = 49;
int g = 49;
int b = 49;

int secondBrightness = 49;
int minuteBrightness = 49;


uint32_t RED = clock.Color(r, 0, 0);
uint32_t GREEN = clock.Color(0, g, 0);
uint32_t BLUE = clock.Color(0, 0, b);

int delayval = 1000; // delay for half a second
int8_t secondPixel = 0;
int8_t minutePixel = 0;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(9600);
  //  uint8_t B = (uint8_t)A;


  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

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
  Serial.println(secondPixel);

  uint8_t red0 = clock.getPixelColor(secondPixel - 1) >> 16;
  uint8_t red  = clock.getPixelColor(secondPixel)     >> 16;
  Serial.print("red: ");
  Serial.println(red);
  uint8_t green0 = clock.getPixelColor(secondPixel - 1) >> 8;
  uint8_t green = clock.getPixelColor(secondPixel)     >> 8;
  Serial.print("green: ");
  Serial.println(green);
  uint8_t blue0 = clock.getPixelColor(secondPixel - 1) >> 0;
  uint8_t blue  = clock.getPixelColor(secondPixel)     >> 0;
  Serial.print("blue: ");
  Serial.println(blue);

  int bc = secondBrightness;
  for (uint8_t p = 0; p < secondBrightness; p++) {
    clock.setPixelColor(secondPixel - 1 , red0, green0, bc * 0.8);
    clock.setPixelColor(secondPixel     , red,  green, p);
    clock.show();
    delay(10);
    bc--;
  }

  if (secondPixel >= clock.numPixels())  {
    secondPixel = 0;
    minuteHand();
  }
  else {
    secondPixel++;
  }
}

void minuteHand() {
  Serial.print("minutePixel: ");
  Serial.println(minutePixel);
  uint8_t red0 = clock.getPixelColor(minutePixel - 1) >> 16;
  uint8_t red  = clock.getPixelColor(minutePixel)     >> 16;
  uint8_t green0 = clock.getPixelColor(minutePixel - 1) >> 8;
  uint8_t green = clock.getPixelColor(minutePixel)     >> 8;
  uint8_t blue0 = clock.getPixelColor(minutePixel - 1) >> 0;
  uint8_t blue  = clock.getPixelColor(minutePixel)     >> 0;

  for (uint8_t p = minuteBrightness; p > 0; p--) {
    clock.setPixelColor(minutePixel - 1 , red0, p , blue0);
    clock.setPixelColor(minutePixel , red, p , blue);
    clock.show();
    delay(10);
  }
  clock.setPixelColor(minutePixel , red, minuteBrightness , blue);
  if (minutePixel >= clock.numPixels())  {
    minutePixel = 0;
  }
  else {
    minutePixel++;
  }
}

