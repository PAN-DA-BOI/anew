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
SoftwareSerial SerialGPS(3, 4); // RX=D0, TX=D1 software moves away from 0/1

// button
const int buttonPin = 5;
int buttonState = 0;
int lastButtonState = 0;
int displayMode = 0; // 0: lat/long, 1: date/time, 2: cat

// cat animation variables
unsigned long catStartTime = 0;
bool catState = false; // false: base1, true: base2
bool yawnState = false; // false: yawn1, true: yawn2
bool sleepState = false; // false: sleep1, true: sleep2

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

unsigned long previousMillis = 0;
const long interval = 1000; // Update display every second

void loop() {
  // Read GPS data if available
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }

  // Check button state
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    displayMode = (displayMode + 1) % 3; // cycle 0, 1, 2
    catStartTime = millis(); // reset cat animation
    delay(50); // Small debounce delay (optional)
  }
  lastButtonState = buttonState;

  // Non-blocking display update
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (displayMode == 0) {
      // Latitude and Longitude
      display.clearDisplay();
      display.drawBitmap(0, 0, coords, 128, 64, BLACK, WHITE);
      display.setTextSize(1);
      if (gps.location.isValid()) {
        display.setCursor(52, 4);
        display.print("Lat: ");
        display.setCursor(0, 20);
        display.println(gps.location.lat(), 6);
        display.setCursor(52, 52);
        display.print("Long: ");
        display.setCursor(0, 36);
        display.println(gps.location.lng(), 6);
      } else {
        display.setCursor(30, 18);
        display.println("No GPS data");
        display.setCursor(34, 40);
        display.println("available");
      }
    } else if (displayMode == 1) {
      // Date and Time
      display.clearDisplay();
      display.drawBitmap(0, 0, time, 128, 64, BLACK, WHITE);
      display.setCursor(0, 0);
      if (gps.date.isValid() && gps.time.isValid()) {
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.print("date: ");
        display.setTextSize(2);
        display.setCursor(0, 12);
        display.print("Date: ");
        display.print(gps.date.day());
        display.print("/");
        display.print(gps.date.month());
        display.print("/");
        display.println(gps.date.year());

        if (gps.time.hour() < 10) display.print("0");
        display.setTextSize(1);
        display.setCursor(0, 32);
        display.print("Time: ");
        display.setTextSize(2);
        display.setCursor(0, 42);
        display.print(gps.time.hour());
        display.print(":");
        if (gps.time.minute() < 10) display.print("0");
        display.print(gps.time.minute());
        display.print(":");
        if (gps.time.second() < 10) display.print("0");
        display.println(gps.time.second());
      } else {
        display.println("No time data");
      }
    } else if (displayMode == 2) {
      // Cat animation
      unsigned long elapsedTime = (currentMillis - catStartTime) / 1000;
      if (elapsedTime < 60) {
        if ((elapsedTime % 2) == 0) {
          display.clearDisplay();
          display.drawBitmap(0, 0, base1, 128, 64, BLACK, WHITE);
        } else {
          display.clearDisplay();
          display.drawBitmap(0, 0, base2, 128, 64, BLACK, WHITE);
        }
      } else if (elapsedTime < 62) {
        if (!yawnState) {
          display.clearDisplay();
          display.drawBitmap(0, 0, yawn1, 128, 64, BLACK, WHITE);
          yawnState = true;
        } else {
          display.clearDisplay();
          display.drawBitmap(0, 0, yawn2, 128, 64, BLACK, WHITE);
          yawnState = false;
        }
      } else {
        if (!sleepState) {
          display.clearDisplay();
          display.drawBitmap(0, 0, sleep1, 128, 64, BLACK, WHITE);
          sleepState = true;
        } else {
          display.clearDisplay();
          display.drawBitmap(0, 0, sleep2, 128, 64, BLACK, WHITE);
          sleepState = false;
        }
      }
    }
    display.display();
  }
}

