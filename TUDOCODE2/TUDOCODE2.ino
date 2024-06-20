#include <Wire.h>
#include "Adafruit_TCS34725.h"
int TUDO(int A, int B, int C, int D, int Green1, int Red1, int Silver1, int Green2, int Red2, int Silver2){
  if (Green1 == 0 && Red1 == 0 && Silver1 == 0 && Green2 == 0 && Red2 == 0 && Silver2 == 0){
      if (B == 1 && C == 1) {
        //Turning each Engine On
        analogWrite(3, 0);
        analogWrite(4, 85);
        analogWrite(5, 0);
        analogWrite(6, 75);
        delay(200);
      }
      //Direction ajust by engine
      if (A == 1 && B == 1 && C == 1) {
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
      if (B == 1) {
        analogWrite(3, 0);
        analogWrite(4, 75);
      } else {
        analogWrite(3, 0);
        analogWrite(4, 0);
      }
      if (C == 1) {
        analogWrite(5, 0);
        analogWrite(6, 75);
      } else {
        analogWrite(5, 0);
        analogWrite(6, 0);
      }
  } else if ((Green1 == 0 && Red1 == 1 && Silver1 == 0) || (Green2 == 0 && Red2 == 1 && Silver2 == 0)){
       delay(10000);
  } else if ((Green1 == 0 && Red1 == 0 && Silver1 == 1) || (Green2 == 0 && Red2 == 0 && Silver2 == 1)){
       analogWrite(3, 0);
       analogWrite(4, 85);
       analogWrite(5, 0);
       analogWrite(6, 75);
  } else if (Green1 == 1 && Red1 == 0 && Silver1 == 0 && Green2 == 0 && Red2 == 0 && Silver2 == 0){
       analogWrite(3, 0);
       analogWrite(4, 100);
       delay(100);
       analogWrite(5, 0);
       analogWrite(6, 0);
       delay(100);
    else if (Green1 == 0 && Red1 == 0 && Silver1 == 0 && Green2 == 1 && Red2 == 0 && Silver2 == 0){
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
Adafruit_TCS34725_W0 sensor1 = Adafruit_TCS34725_W0(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_4X);
Adafruit_TCS34725_W1 sensor2 = Adafruit_TCS34725_W1(TCS34725_INTEGRATIONTIME_700MS2, TCS34725_GAIN_4X2);

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
  float red1, green1, blue1;
  float red2, green2, blue2;
  int S1, S2;
  // Turn on the sensor LED
  tcs.setInterrupt(false);
  delay(60);  // takes 60ms to read

  // Initialize the TCS34725 sensor
  if (sensor1.begin()) {

    // Sensor initialized successfully
    S1 = 1;

  } else {

    // Sensor not found, display error message
    Serial.println("No TCS34725(1) found ... check your connections");
    while (1)
      ;  // Halt the execution
    S1 = 0;
  } 
  if (sensor2.begin()){
    
    // Sensor initialized successfully
    S2 = 1;
  } else {

    // Sensor not found, display error message
    Serial.println("No TCS34725(2) found ... check your connections");
    while (1)
      ;  // Halt the execution
    S2 = 0;
  }
  if (S1 == 1){
    sensor1.getRawData(&red1, &green1, &blue1);
  }
  if (S2 == 1){
    sensor2.getRawData2(&red2, &green2, &blue2);
  }
  
  // Turn off the sensor LED
  tcs.setInterrupt(true);
  TUDO(digitalRead(7), digitalRead(8), digitalRead(9), digitalRead(10), Green((int)red1, (int)green1, (int)blue1), Red((int)red1, (int)green1, (int)blue1), Silver((int)red1, (int)green1, (int)blue1), Green((int)red2, (int)green2, (int)blue2), Red((int)red2, (int)green2, (int)blue2), Silver((int)red2, (int)green2, (int)blue2));
}
