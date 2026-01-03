# Arm
better limbs are a must

the arm kit is to enhance general connectivity. Adding lora, meshtastic, wifi, and bluetooth.

## server
having a server for testing right on your arm enables you to make quick changes to anythign without the hassle of pulling other equiptment out

## connectivity
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
* run "software/setup.sh" using the commands below
```
git clone https://github.com/PAN-DA-BOI/Gauntlet-v3.git
chmod +x ./software/setup.sh
./software/setup.sh