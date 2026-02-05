#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "cat.h"
#include "overlay.h"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

TinyGPSPlus gps;
SoftwareSerial SerialGPS(2, 3); // RX=D2, TX=D3 (TX unused for GPS)

// Button settings
const int buttonPin = 5;
int buttonState = 0;
int lastButtonState = 0;
bool displayMode = false;

void setup() {
  Serial.begin(9600);
  SerialGPS.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }

  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50);
    displayMode = !displayMode;
  }
  lastButtonState = buttonState;

  display.clearDisplay();
  display.setCursor(0, 0);

  if (!displayMode) {
    if (gps.location.isValid()) {
      display.print("Lat: ");
      display.println(gps.location.lat(), 6);
      display.print("Long: ");
      display.println(gps.location.lng(), 6);
    } else {
      display.println("No GPS data");
    }
  } else {
    if (gps.date.isValid() && gps.time.isValid()) {
      display.print("Date: ");
      display.print(gps.date.day());
      display.print("/");
      display.print(gps.date.month());
      display.print("/");
      display.println(gps.date.year());

      display.print("Time: ");
      if (gps.time.hour() < 10) display.print("0");
      display.print(gps.time.hour());
      display.print(":");
      if (gps.time.minute() < 10) display.print("0");
      display.print(gps.time.minute());
      display.print(":");
      if (gps.time.second() < 10) display.print("0");
      display.println(gps.time.second());
    } else {
      display.println("No GPS data");
    }
  }

  display.display();
  delay(100);
}
