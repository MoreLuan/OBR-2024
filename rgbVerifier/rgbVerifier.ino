#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Function to detect the green color
int Green(int R, int G, int B) {
  if ((R < 180 && R > 65 && B < 180 && B > 65 && G > 107) || (B * 10 < G && G > 35)) {
    return 1;
  } else {
    return 0;
  }
}

// Function to detect the red color
int Red(int R, int G, int B) {
  if ((R > 130 && B < 180 && B > 55 && G > 55 && G < 180) || (B * 10 < R && R > 35)) {
    return 1;
  } else {
    return 0;
  }
}

// Function to detect the silver color
int Silver(int R, int G, int B) {
  if (R > 90 && R < 109 && 95 > B && B > 70 && G > 100 && G < 113){
    return 1;
  } else {
    return 0;
  }
}

//ALTERAR PORTAS PARA ARDUINO MEGA
#define redpin 3
#define greenpin 5
#define bluepin 6


#define commonAnode true

// Gamma conversion table
byte gammatable[256];

// Instance of the TCS34725 sensor with integration time and gain parameters
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);

  // Initialize the TCS34725 sensor
  if (tcs.begin()) {

    // Sensor initialized successfully

  } else {

    // Sensor not found, display error message
    Serial.println("No TCS34725 found ... check your connections");
    while (1)
      ;  // Halt the execution
  }

// Pin configuration for ESP32 or other boards
#if defined(ARDUINO_ARCH_ESP32)
  ledcAttach(redpin, 12000, 8);
  ledcAttach(greenpin, 12000, 8);
  ledcAttach(bluepin, 12000, 8);
#else
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
#endif

  // Fill the gamma table
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }
}

void loop() {
  float red, green, blue;

  // Turn on the sensor LED
  tcs.setInterrupt(false);
  delay(60);  // takes 60ms to read

  // Get RGB values from the sensor
  tcs.getRGB(&red, &green, &blue);

  // Turn off the sensor LED
  tcs.setInterrupt(true);

  // Display the RGB values on the serial monitor
  Serial.print("R:\t");
  Serial.print(int(red));
  Serial.print("\tG:\t");
  Serial.print(int(green));
  Serial.print("\tB:\t");
  Serial.print(int(blue));

  // Check and display the detected color
  if (Green((int)red, (int)green, (int)blue) == 1 && Red((int)red, (int)green, (int)blue) == 0 && Silver((int)red, (int)green, (int)blue) == 0) {
    Serial.print("\nVerde");
  }
  if (Green((int)red, (int)green, (int)blue) == 0 && Red((int)red, (int)green, (int)blue) == 1 && Silver((int)red, (int)green, (int)blue) == 0) {
    Serial.print("\nVermelho");
  }
  if (Silver((int)red, (int)green, (int)blue) == 1 && Red((int)red, (int)green, (int)blue) == 0 && Green((int)red, (int)green, (int)blue) == 0) {
    Serial.print("\nPrata");
  }

  Serial.print("\n");
  delay(100);

  // Set the RGB values on the output pins
#if defined(ARDUINO_ARCH_ESP32)
  ledcWrite(1, gammatable[(int)red]);
  ledcWrite(2, gammatable[(int)green]);
  ledcWrite(3, gammatable[(int)blue]);
#else
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);
#endif
}
