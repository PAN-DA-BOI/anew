# Arm
better limbs are a must

the arm kit is to enhance general connectivity. Adding lora, meshtastic, wifi, and bluetooth.

## Server
having a server for testing right on your arm enables you to make quick changes to anythign without the hassle of pulling other equiptment out

## Connectivity
sending a message over discord or mechtastic, starting a deauth atack, or bluetoothing to a speaker to share some tunes. all of these require wireless connectivity.

## BOM

* Raspberry Pi 3B+ (or in my case, an AML-S905X-CC)
* Meshtastic T-Beam
* Waveshare 240x240, General 1.3inch LCD display
* 40mm fan
* 2X 18650 batteries
* general hardware (screws, nuts, washers, and heatsinks)

## Hardware guide
* print out "hardware/gauntlet.stl"
* print out "hardware/mesh-case.stl"
* print out "hardware/pi-case.stl"
* put the pi in its place
* wire the screen
* add the T-beam
* add the batteries

## Software guide
* enable SPI on the pi using the command below
```
sudo raspi-config
```
* use the arrow keys in the menu and enter to select the following
   * Interfacing Options
   * SPI
   * Select "Yes" to enable SPI
* run "arm//setup.sh" using the commands below
```
chmod +x ./arm/arm.sh
./arm/arm.sh
```

## Links
Pi options:
* [Raspberry pi 3 B+](https://www.raspberrypi.com/products/raspberry-pi-3-model-b-plus/)
* [aml-s905x-cc](https://libre.computer/products/aml-s905x-cc/)

Display References:
* [waveshare 2in display](https://www.waveshare.com/wiki/2inch_LCD_Module)
* [display pinout](https://www.waveshare.com/2inch-lcd-module.htm#:~:text=Connecting%20With%20Raspberry%20Pi)

Meshtastic Device:
* [T-Beam] (https://lilygo.cc/products/t-beam-meshtastic?variant=51708927738037)

3D files:
* [Tinkercad](https://www.tinkercad.com/things/ffUa8IlDIRD-v3/edit?returnTo=%2Fdashboard%2Fdesigns%2F3d)
* [thingiverse] (https://www.thingiverse.com/thing:7260150)
