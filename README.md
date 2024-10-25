# Clock and Temperature Project

## Overview
This project, created by Simon Lendvai, displays time and temperature using a DS3231 RTC module and an analog temperature sensor. The time is shown on a 1306 OLED display, and an LED flashes every ten seconds as an indicator. The system also measures ambient temperature and maps it to a servo motor, which rotates to reflect the current temperature.

## Features
- **Real-time Clock (DS3231)**: Displays accurate time on an OLED display.
- **Temperature Monitoring**: Measures temperature with an analog sensor and displays it on the serial monitor.
- **Servo Temperature Indicator**: Maps the temperature to an angle on a 9g servo motor.
- **LED Blinking**: Blinks every 10 seconds to signal that the system is running.

## Components Used
- **DS3231 RTC Module**: Provides precise timekeeping.
- **SSD1306 OLED Display**: Displays time in `hh:mm:ss` format.
- **Analog Temperature Sensor**: Measures ambient temperature.
- **Servo Motor (9g)**: Rotates to indicate temperature.
- **LED**: Flashes every 10 seconds to indicate system activity.

## Installation

### Required Libraries
Ensure the following libraries are installed:
- `RTClib`: Handles DS3231 communication.
- `Wire`: Manages I2C communication.
- `U8glib`: Controls OLED display.
- `Servo`: Controls servo motor rotation.

Install these libraries via the Arduino IDE Library Manager or manually place them in the `libraries` folder.

### Circuit Diagram
- **Temperature Sensor**: Connect to analog pin `A0`.
- **OLED Display**: Connect to I2C pins (`SDA` and `SCL`).
- **Servo Motor**: Connect control signal to pin `9`.
- **LED**: Connect to pin `8`.

## Code Overview
- **Setup (`setup()`)**: Initializes communication, configures pins, and prepares all modules.
- **Loop (`loop()`)**: Runs the core functions:
  - Displays temperature on the serial monitor.
  - Moves the servo based on temperature.
  - Updates and displays time on the OLED screen.
  - Flashes the LED every 10 seconds.

### Core Functions
- **`getTime()`**: Reads the time from the DS3231 module and formats it as `hh:mm:ss`.
- **`getTemp()`**: Reads and calculates temperature from the analog sensor using the Steinhart-Hart equation.
- **`oledWrite(String text)`**: Displays text on the OLED screen.
- **`servoWrite(float value)`**: Maps the temperature to a servo angle, with constraints to ensure a valid range.

## Usage
1. Upload the code to your microcontroller.
2. Open the serial monitor to view the temperature readings.
3. Observe the OLED display for the current time.
4. Watch the servo adjust according to ambient temperature and the LED flash every 10 seconds.

## License
This project is licensed under the MIT License. Feel free to use, modify, and distribute as per the license terms.
