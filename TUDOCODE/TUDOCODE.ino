#include <Wire.h>
#include "Adafruit_TCS34725.h"
int TUDO(A, B, C, D, Green, Red, Silver){
  if (Green == 0 && Red == 0 && Silver == 0){
      if (B == 1 && C == 1) {
        //Turning each Engine On
        analogWrite(3, 0);
        analogWrite(4, 85);
        analogWrite(5, 0);
        analogWrite(6, 75);
        delay(200);
      }
      //Direction ajust by engine
      if (A == 1 && B == 1) {
        analogWrite(3, 0);
        analogWrite(4, 0);
        delay(100);
        analogWrite(5, 0);
        analogWrite(6, 100);
        delay(100);
      }
      if (B == 1 && C == 1 && D == 1) {
        analogWrite(3, 0);
        analogWrite(4, 100);
        delay(100);
        analogWrite(5, 0);
        analogWrite(6, 0);
        delay(100);
      }
      //Align ajust by engine
      if (B < 1) {
        analogWrite(3, 0);
        analogWrite(4, 75);
      } else {
        analogWrite(3, 0);
        analogWrite(4, 0);
      }
      if (C < 1) {
        analogWrite(5, 0);
        analogWrite(6, 75);
      } else {
        analogWrite(5, 0);
        analogWrite(6, 0);
      }
  } else if (Green == 0 && Red == 1 && Silver == 0){
       delay(10000)
  } else if (Green == 0 && Red == 0 && Silver == 1){
       analogWrite(3, 0);
       analogWrite(4, 85);
       analogWrite(5, 0);
       analogWrite(6, 75);
  } else if (Green == 1 && Red == 0 && Silver == 0){
       analogWrite(3, 0);
       analogWrite(4, 100);
       delay(100);
       analogWrite(5, 0);
       analogWrite(6, 0);
       delay(100);
  }
}
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

#define commonAnode true

// Gamma conversion table
byte gammatable[256];

// Instance of the TCS34725 sensor with integration time and gain parameters
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  // Engine
  pinMode(3, OUTPUT); //Left Engine
  pinMode(4, OUTPUT); //Left Engine
  pinMode(5, OUTPUT); //Right Engine
  pinMode(6, OUTPUT); //Right Engine
  // Line Follower Sensor
  pinMode(8, INPUT); //Right
  pinMode(9, INPUT); //Left
  // 90 degres curve Sensor
  pinMode(7, INPUT); //Right
  pinMode(10, INPUT); //Left
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
  TUDO(digitalRead(7), digitalRead(8), digitalRead(9), digitalRead(10), Green((int)red, (int)green, (int)blue), Red((int)red, (int)green, (int)blue), Silver((int)red, (int)green, (int)blue))
}
