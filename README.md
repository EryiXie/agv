This is the repository for the motion control code (python and C) of a AGV built up with Raspberry Pi, Arduino and encoded DC motor driven Mecanum wheels, which is controlled by a bluetooth joystick controller. 

### Arduino code upload

### Environment Setup for Raspberry Pi

Please install [mini-forge](https://github.com/conda-forge/miniforge) for Linux aarch64 (arm64) first, then:
```
conda activate
conda create -n agv python=3.10
conda activate agv
python -m pip install pygame, numpy
python -m pip install pyserial
```

## Controller - Raspberry Pi

### Connect Bluetooth controller to Raspiberry Pi
We have the controller 8Bitdo SN30 Pro, which is a third-party controller for Xbox. To start the controller, press "start". To start and enter pairing mode, press "start" and "Y" for 3-5 seconds. Search Bluetooth device on Raspberry Pi side and connect/pair it, once it is paired, you receive a virbration feedback from the controller.

To test the button and axis layout, run:
```
cd controller
python JoystickButtonFinder.py
```

## Raspberry Pi - Arduino
We simply use USB cable to serial communication between Pi and Arduino.
Run testing code on raspberry side
 

## Demo for Mecanum robot controll and 