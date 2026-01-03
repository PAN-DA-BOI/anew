# Headgear
we deserve better sight

the headgear is the best way of communicating information to the user, visually.

## sight
using the IR-cut cameras makes it so we can see in the dark and don't have to give our location away by using lights that are in the human visible spectrum.

## information
we can also use the display to readout data from sensors elsewhere in the kit


## BOM
* Raspberry Pi 3B+ (or AML-S905X-CC)
* Bigeyes H1 USB-C Display
* IR-cut cameras
* General hardware (screws, nuts, washers, and heatsinks)


## Hardware Guide
* Print out "camera-mount.stl"
* Print out "pi-case.stl"
* Mount the Pi in its case
* Attach the IR-cut cameras
* Connect the Bigeyes H1 display


## Software Guide
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
chmod +x ./headgear/headgear.sh
./headgear/headgear.sh
```


## Links
**Pi Options:**
* [Raspberry Pi 3 B+](https://www.raspberrypi.com/products/raspberry-pi-3-model-b-plus/)
* [AML-S905X-CC](https://libre.computer/products/aml-s905x-cc/)

**Display:**
* [Bigeyes H1 USB-C](https://a.co/d/5KhfGGy)

**3D Files:**
* [Tinkercad](https://www.tinkercad.com/things/a97szCPA83t-headgear?sharecode=WnLmPbKwnU4mmVunEaWUQLv01R9VWd4EFG3OoEN0JlE)
* [Thingiverse](https://www.thingiverse.com/thing:7260150)

