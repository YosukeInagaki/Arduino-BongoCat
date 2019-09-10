// Use Adafruit's GFX and SSD1306 (display driver) library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

boolean bongoState = false;
unsigned long bongoPreviousMillis = 0;
const long bongoInterval = 100; 

#define BONGO_HEIGHT   64
#define BONGO_WIDTH    64

// 'bongoup' and 'bongodown', 128x64px
const unsigned char bongodown [] PROGMEM =
{ B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B10000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000001,B01000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000010,B00100000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00001100,B00011000,B00000000,B10000000,B00000000,B00000000,
  B00000000,B00000000,B00010000,B00000111,B10000001,B10000000,B00000000,B00000000,
  B00000000,B00000000,B00100000,B00000000,B01110010,B10000000,B00000000,B00000000,
  B00000000,B00000000,B01000000,B00000000,B00001100,B10000000,B00000000,B00000000,
  B00000000,B00000000,B10000000,B00000000,B00000000,B10000000,B00000000,B00000000,
  B00000000,B00000001,B00000000,B00000000,B00000000,B10000000,B00000000,B00000000,
  B00000000,B00000001,B00000110,B00000000,B00000000,B10000000,B00000000,B00000000,
  B00000000,B00000010,B00000110,B00000000,B00000000,B10000000,B00000000,B00000000,
  B10000000,B00000100,B00000001,B01010011,B00000000,B10000000,B00000000,B00000000,
  B01111110,B00001000,B00000000,B10100011,B00000000,B01000000,B00000000,B00000000,
  B00000001,B11010000,B00000000,B00000000,B00000000,B00100000,B00000000,B00000000,
  B00000000,B00010000,B00001000,B00000000,B00000000,B00100000,B00000000,B00000000,
  B00000000,B00010000,B00110111,B11100000,B10000000,B00010000,B00000000,B00000000,
  B00000000,B00001000,B11000000,B00011111,B00000000,B00010000,B00000000,B00000000,
  B00000000,B00000111,B00000000,B00000001,B00000001,B00010000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000010,B00000110,B01111110,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000001,B00001000,B00000001,B11111000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B11110000,B00000000,B00000111,B11100000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00011111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000 };
  
const unsigned char bongoup [] PROGMEM =
{ B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B10000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000001,B01000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000010,B00100000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00001100,B00011000,B00000000,B10000000,B00000000,B00000000,
  B00000000,B00000000,B00010000,B00000111,B10000001,B10000000,B00000000,B00000000,
  B00000000,B00000000,B00100000,B00000000,B01110010,B10000000,B00000000,B00000000,
  B00000000,B00001000,B01000000,B00000000,B00001100,B10000000,B00000000,B00000000,
  B00000000,B00010110,B10000000,B00000000,B00000000,B10000000,B00000000,B00000000,
  B00000000,B00100001,B00000000,B00000000,B00000000,B10000000,B00000000,B00000000,
  B00000000,B00100001,B00000110,B00000000,B00111000,B10000000,B00000000,B00000000,
  B00000000,B00100000,B00000110,B00000000,B01000100,B10000000,B00000000,B00000000,
  B10000000,B00100000,B00000001,B01010011,B10000010,B10000000,B00000000,B00000000,
  B01111110,B00010000,B00000000,B10100011,B10000000,B01000000,B00000000,B00000000,
  B00000001,B11101100,B00000000,B00000000,B10000000,B00100000,B00000000,B00000000,
  B00000000,B00000011,B11110000,B00000000,B10000000,B00100000,B00000000,B00000000,
  B00000000,B00000000,B00001111,B11000000,B01000000,B00010000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00111111,B00000000,B00010000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00111111,B10010000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B01111110,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000001,B11111000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111,B11100000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00011111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000 };
void setup()
{
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.invertDisplay(true);
}

void loop()
{
  updateBongo();
  delay(20);
}

void updateBongo()
{
  unsigned long currentMillis = millis();
  if (currentMillis - bongoPreviousMillis >= bongoInterval)
  {
    bongoPreviousMillis = currentMillis;
    bongoState = !bongoState;
    if (bongoState == true)
    {
      display.clearDisplay();
      display.drawBitmap(
      (display.width()  - BONGO_WIDTH ) / 2,
      (display.height() - BONGO_HEIGHT) / 2,
      bongodown, BONGO_WIDTH, BONGO_HEIGHT, 1);
      display.display();
    }
    else
    {
      display.clearDisplay();
      display.drawBitmap(
      (display.width()  - BONGO_WIDTH ) / 2,
      (display.height() - BONGO_HEIGHT) / 2,
      bongoup, BONGO_WIDTH, BONGO_HEIGHT, 1);
      display.display();
    }
  }
}
