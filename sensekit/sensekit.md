# Sensekit
add GPS, gas sensor, DHT11, and offline clock. all to get accurate information constantly.

## information
this give realtime info about the enviroment to help with a better course of action. 

## BOM
* ATmega328
* NEO-6M GPS Module
* MQ2 Gas/Smoke Sensor
* DS3231 Precision RTC Module
* DHT11 Module

## Hardware guide
* print out "hardware/sensekit-case.stl"
* solder together the board
* run the wire to the external modules
* run the RX/TX, Ground, and 5v lines to the pi

## setting up the headgear with sensekit

* Enable SPI on the Pi using the command below:
```
sudo raspi-config
```
  * Use the arrow keys in the menu and enter to select the following:
    * Interfacing Options
    * SPI
    * Select "Yes" to enable SPI
* Run the setup script using the commands below:
```
chmod +x ./anew/sensekit/headgear.sh
./anew/sensekit/headgear.sh
```

## setting up the ARM kit with sensekit

* Enable SPI on the Pi using the command below:
```
sudo raspi-config
```
  * Use the arrow keys in the menu and enter to select the following:
    * Interfacing Options
    * SPI
    * Select "Yes" to enable SPI
* Run the setup script using the commands below:
```
chmod +x ./anew/sensekit/arm.sh
./anew/sensekit/arm.sh
```

## Links
**microcontroller:**
* [ATmega328](https://www.microchip.com/wwwproducts/en/ATmega328)

**NEO-6M GPS Module:**
* [how I learned about this module](https://lastminuteengineers.com/neo6m-gps-arduino-tutorial/)
* [purchase link (amazon)](https://a.co/d/eaIDu7a)
* [datasheet](https://www.mantech.co.za/datasheets/products/GY-NEO6MV2.pdf?srsltid=AfmBOor0Y0DsKqGpDZc8DZeQU3oq6dDmILLN76AJ43DxfM7IGO_tq0W3)

**MQ2 Gas/Smoke Sensor:**
* [how I learned about this module](https://lastminuteengineers.com/mq2-gas-senser-arduino-tutorial/)
* [purchase link (amazon)](https://a.co/d/fkaDYwG)
* [datasheet](https://www.handsontec.com/dataspecs/MQ2-Gas%20Sensor.pdf)

**DS3231 Precision RTC Module**
* [[how I learned about this module](https://lastminuteengineers.com/ds3231-rtc-arduino-tutorial/)
* [purchase link (amazon)](https://a.co/d/eqo5VmE)
* [datasheet](https://components101.com/modules/ds3231-rtc-module-pinout-circuit-datasheet)

**DHT11 Module**
* [how I learned about this module](https://lastminuteengineers.com/dht11-module-arduino-tutorial/)
* [purchase link (amazon)](https://a.co/d/6rRFbFv)
* [datasheet](https://www.handsontec.com/dataspecs/sensor/DHT11%20Humidity%20Temp%20Sensor.pdf)

**3D Files:**
* [Tinkercad](https://www.tinkercad.com/things/bYOG9SPf1Zd-sensekit?sharecode=1UXfmP689aCw8aezX2LEzINphimJ06rz1puhpxoYT78)
* [Thingiverse](https://www.thingiverse.com/thing:7263738)
