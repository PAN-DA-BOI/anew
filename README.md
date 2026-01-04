# anew

I will be born anew. This project is a compromise. Yes, it's a little silly, but I've been repeatedly told I'm explicitly *not* allowed to remove parts of my body just to replace them with metal. In this light, I (and my smartest/best friends) are making gadgets to help me become the cyborg I was truly meant to be.

Edit from Alchemicdumbass: "you can replace parts of your body with metal, I'm just not ok with you removing 20% of your body mass in one fell swoop to accomplish that. If you want to progressively replace portions of your arm with robotic parts, so long as you were responsible about it, thats fine, even to the point where its eventually replaced entirely. I just don't want you to have to deal with the medical complications that a major limb amputation entails unless the benefit outweighs the risk (Such as, most of or the entire limb has died, become infected, or otherwise not safe to keep any longer.). Anyways lets ship of theseus your ass"

## getting started

start by getting and sorting the project! first, git the project and then follow the instructions for each part your building! Each "part" of the project is sorted into how many PIs your willing to use, were tring to cut down on as many as possible. But bare minimum the arm and headgear need a pi each. 

```
git clone https://github.com/PAN-DA-BOI/anew.git
```

## Headgear
run the commands below to set a pi up for the headgear

```
chmod +x ./anew/headgear/headgear.sh
./anew/headgear/headgear.sh
```

read more about the [headgear](https://github.com/PAN-DA-BOI/anew/blob/development/headgear/headgear.md) here.

## Arm
run the commands below to set the pi up as the arm kit

```
chmod +x ./anew/arm/arm.sh
./anew/arm/arm.sh
```

read more about the [ARM kit](https://github.com/PAN-DA-BOI/anew/blob/development/arm/arm.md) here.

## Sensekit
the sense kit is an arduino addon to get more sensor data.

read more about the [sensekit](https://github.com/PAN-DA-BOI/anew/blob/development/sensekit/sensekit.md) here.