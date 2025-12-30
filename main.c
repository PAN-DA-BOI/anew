#include <SPI.h>
#include <uRTCLib.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <dht.h>

#define dht11Pin 9
#define MQ2pin A0
#define Threshold 400
#define SS_PIN 10

uRTCLib rtc(0x68);
dht DHT;
TinyGPSPlus gps;
SoftwareSerial gpsSerial(2, 3); // RX, TX

// Data structure to send
struct SensorData {
  float temperature;
  float humidity;
  float gasValue;
  float latitude;
  float longitude;
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
};

SensorData data;

void setup() {
  pinMode(SS_PIN, INPUT_PULLUP);
  SPI.begin();
  SPCR |= _BV(SPE); // Enable SPI in slave mode
  gpsSerial.begin(9600);
  URTCLIB_WIRE.begin();
  rtc.set(0, 0, 12, 1, 1, 1, 26); // Set RTC initial time
}

void loop() {
  // Read sensors
  data.humidity = DHT.humidity;
  data.temperature = DHT.temperature;
  data.gasValue = analogRead(MQ2pin);
  rtc.refresh();
  data.year = rtc.year();
  data.month = rtc.month();
  data.day = rtc.day();
  data.hour = rtc.hour();
  data.minute = rtc.minute();
  data.second = rtc.second();

  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        data.latitude = gps.location.lat();
        data.longitude = gps.location.lng();
      }
    }
  }

  // Wait for SPI request from Raspberry Pi
  if (digitalRead(SS_PIN) == LOW) {
    // Send data as bytes
    byte* dataBytes = (byte*)&data;
    for (int i = 0; i < sizeof(data); i++) {
      SPDR = dataBytes[i];
      while (!(SPSR & (1 << SPIF)));
    }
  }
}
