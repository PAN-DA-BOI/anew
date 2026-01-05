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

## Hardware Guide
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

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

**Modules:**
* [NEO-6M GPS Module](https://lastminuteengineers.com/neo6m-gps-arduino-tutorial/)
* [MQ2 Gas/Smoke Sensor](https://lastminuteengineers.com/mq2-gas-senser-arduino-tutorial/)
* [DS3231 Precision RTC Module](https://lastminuteengineers.com/ds3231-rtc-arduino-tutorial/)
* [DHT11 Module](https://lastminuteengineers.com/dht11-module-arduino-tutorial/)
