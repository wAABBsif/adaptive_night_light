# Adaptive Night Light
An adaptive night light written in C for an ESP32 microcontroller (Final project for BEEP in Embedded Systems @ Purdue)

## Usage
- The brightness of the light is adjusted depending upon the brightness of the room.
- The room brightness thresholds can be adjusted using the calibration buttons.
  - Press the minimum button to set the minimum room brightness, where the LED will be brightest.
  - Press the maximum button to set the maximum room brightness, where the LED will be darkness.
- Use the potentiometer to adjust the warmness of the LED.

## Wiring
- **Calibrate minimum button:** GPIO pin 18
- **Calibrate maximum button:** GPIO pin 19
- **10 kΩ photoresistor:** GPIO pin 34 (through 10 kΩ resistor)
- **4-pin RGB LED:** GPIO pin 25 (red, through 220 Ω resistor), GPIO Pin 26 (green, through 220 Ω resistor), GPIO Pin 27 (blue, through 220 Ω resistor)
- **10 kΩ potentiometer:** GPIO pin 32

## Roadmap
- [x] Get photoresistors working
- [x] Get light working
- [x] Get color potentiometer working
- [x] Get calibration buttons working
- [x] Set color of LED based on potentiometer
- [x] Detect light based on calibration
- [x] Set brightness of LED based on light detection
- [x] Add smoothness to brightness change
