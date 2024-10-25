/* 
* Name: Clock and Temperature Project
* Author: Simon Lendvai
* Date: 2024-10-25
* Description: This project uses a DS3231 to measure time and display it on a 1306 OLED display, as well as flashing an LED every ten seconds.
* Additionally, it measures temperature with an analog temperature sensor and maps the value to a 9g servo motor to indicate the temperature.
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include "U8glib.h"
#include <Servo.h>

// Init constants
const int tmpPin = A0;
const int ledPin = 8;

// Init global variables
char t[32];

// Construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
Servo servo;

void setup() {
  // Initialize communication
  Serial.begin(9600);
  pinMode(tmpPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Wire.begin();
  rtc.begin();

  // Initialize hardware
  u8g.setFont(u8g_font_6x10);
  servo.attach(9);
}

/*
* This loop runs all the core functions:
* - The measured temperature is printed on the serial monitor.
* - The servo moves based on the corresponding temperature.
* - The time string is generated.
* - The time is displayed on the OLED screen.
* - An LED is flashed every ten seconds for 0.5 seconds.
* - There is a delay of 0.5 seconds to reduce performance overhead.
* - There's a total delay of one second regardless if the LED is flashed or not.
*/
void loop() {
  Serial.println(getTemp());
  servoWrite(getTemp());
  DateTime now = rtc.now();
  String time = getTime();
  oledWrite(time);
  
  if (now.second() % 10 == 0) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  delay(500);
}

/*
* This function reads the time from the DS3231 module and formats it as a string.
* Parameters: None
* Returns: Time in hh:mm:ss format as a String
*/
String getTime() {
  DateTime now = rtc.now();
  return "The time is: " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

/*
* This function reads the value from an analog temperature sensor and calculates the temperature.
* Parameters: None
* Returns: Temperature as a float in Celsius
*/
float getTemp() {
  int Vo;
  float R1 = 10000; // Value of R1 on board
  float logR2, R2, T;
  float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; // Steinhart-Hart coefficients for thermistor

  // Read the analog value from the temperature sensor
  Vo = analogRead(tmpPin);

  // Avoid division by zero if Vo is 0
  if (Vo == 0) {
    return -999; // Return an error value if reading fails
  }

  // Calculate resistance of the thermistor
  R2 = R1 * (1023.0 / (float)Vo - 1.0);

  // Calculate the natural log of R2
  logR2 = log(R2);

  // Calculate temperature using the Steinhart-Hart equation (in Kelvin)
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));

  // Convert temperature from Kelvin to Celsius
  T = T - 273.15;

  return T;
}

/*
* This function displays a given string on the OLED display.
* Parameters: - text: String to display
* Returns: void
*/
void oledWrite(String text) {
  u8g.firstPage();
  do {
    u8g.drawStr(0, 30, text.c_str());
  } while (u8g.nextPage());
}

/*
* This function takes a temperature value and maps it to a corresponding servo angle.
* Parameters: - value: Temperature in Celsius
* Returns: void
*/
void servoWrite(float value) {
  int angle = map(value, -10, 40, 0, 180); // Map temperature range to servo angle
  angle = constrain(angle, 0, 180);        // Constrain angle to servo's valid range
  servo.write(angle);
}