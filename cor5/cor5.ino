#include <Wire.h>
#include "Adafruit_TCS34725.h"
int Green(int R, int G, int B) {
  if ((R < 180 && R > 65 && B < 180 && B > 65 && G > 115) || (B * 10 < G && G > 35)){
    return 1;
  } else {
    return 0;
  }
}
int Red(int R, int G, int B) {
  if ((R > 130 && B < 180 && B > 55 && G > 55 && G < 180) || (B * 10 < R && R > 35)){
    return 1;
  } else {
    return 0;
  }
}
int Silver(int R, int G, int B) {
  if (R > 80 && R < 95 && 90 > B && B > 70 && G > 90 && G < 105){
    return 1;
  } else {
    return 0;
  }
}
#define redpin 3
#define greenpin 5
#define bluepin 6
#define commonAnode true
byte gammatable[256];


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  if (tcs.begin()) {
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

#if defined(ARDUINO_ARCH_ESP32)
  ledcAttach(redpin, 12000, 8);
  ledcAttach(greenpin, 12000, 8);
  ledcAttach(bluepin, 12000, 8);
#else
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
#endif
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

  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);

  tcs.setInterrupt(true);  // turn off LED
  Serial.print("R:\t"); Serial.print(int(red)); 
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  Serial.print("\tB:\t"); Serial.print(int(blue));
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
