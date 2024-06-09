int trig = 11; // Trigger Pin 
int echo = 12; //Echo Pin
#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 3
#define greenpin 5
#define bluepin 6
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
// Setting arduino ports
void setup(){
  Serial.begin(9600);
  //Serial.println("Color View Test!");

  if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  // use these three pins to drive an LED
#if defined(ARDUINO_ARCH_ESP32)
  ledcAttach(redpin, 12000, 8);
  ledcAttach(greenpin, 12000, 8);
  ledcAttach(bluepin, 12000, 8);
#else
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
#endif

  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
    //Serial.println(gammatable[i]);
  }
}

// The commented out code in loop is example of getRawData with clear value.
// Processing example colorview.pde can work with this kind of data too, but It requires manual conversion to 
// [0-255] RGB value. You can still uncomments parts of colorview.pde and play with clear value.
  // Engine
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
  // Line Follower Sensor
    pinMode(8,INPUT);
    pinMode(9,INPUT);
}

//Verification function to see if there is an object in front of the robot
float getDistance(int trig,int echo){
    pinMode(trig,OUTPUT);
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    pinMode(echo, INPUT);
    return pulseIn(echo,HIGH,30000)/58.0;
}

//Changing the route of the robot to deflect the object
void ObstacleDerailleur(){
  //Turning Right
  analogWrite(5,0);
  analogWrite(6,100);
  delay(100);

  //Running 15cm
  analogWrite(3,0);
  analogWrite(4,100);
  analogWrite(5,0);
  analogWrite(6,100);
  delay(50);

  //Turning Left
  analogWrite(3,0);
  analogWrite(4,100);
  delay(100);

  //Running 30cm
  analogWrite(3,0);
  analogWrite(4,100);
  analogWrite(5,0);
  analogWrite(6,100);
  delay(100);

  //Turning Left
  analogWrite(3,0);
  analogWrite(4,100);
  delay(100);
  
  //Running 15cm
  analogWrite(3,0);
  analogWrite(4,100);
  analogWrite(5,0);
  analogWrite(6,100);
  delay(50);

  //Turning Right
  analogWrite(5,0);
  analogWrite(6,100);
  delay(100);
}

// Verificating if infrareds are working together
void lineFollower() {
    if((((digitalRead(8)) && (digitalRead(9)))==(1))){
      //Turning each Engine On
        analogWrite(3,0);
        analogWrite(4,100);
        analogWrite(5,0);
        analogWrite(6,100);
        delay(200);
    }
    //Direction ajust by engine
    if((digitalRead(8)) < (1)){
        analogWrite(3,0);
        analogWrite(4,100);
    }else{
        analogWrite(3,0);
        analogWrite(4,0);
    }
    if((digitalRead(9)) < (1)){
        analogWrite(5,0);
        analogWrite(6,100);
    }else{
        analogWrite(5,0);
        analogWrite(6,0);
    }  
}

void loop(){
  float red, green, blue;
  
  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);
  
  tcs.setInterrupt(true);  // turn off LED

  Serial.print("R:\t"); Serial.print(int(red)); 
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  Serial.print("\tB:\t"); Serial.print(int(blue));

//  Serial.print("\t");
//  Serial.print((int)red, HEX); Serial.print((int)green, HEX); Serial.print((int)blue, HEX);
  Serial.print("\n");

//  uint16_t red, green, blue, clear;
//  
//  tcs.setInterrupt(false);  // turn on LED
//
//  delay(60);  // takes 50ms to read
//
//  tcs.getRawData(&red, &green, &blue, &clear);
//  
//  tcs.setInterrupt(true);  // turn off LED
//
//  Serial.print("C:\t"); Serial.print(int(clear)); 
//  Serial.print("R:\t"); Serial.print(int(red)); 
//  Serial.print("\tG:\t"); Serial.print(int(green)); 
//  Serial.print("\tB:\t"); Serial.print(int(blue));
//  Serial.println();


#if defined(ARDUINO_ARCH_ESP32)
  ledcWrite(1, gammatable[(int)red]);
  ledcWrite(2, gammatable[(int)green]);
  ledcWrite(3, gammatable[(int)blue]);
#else
  analogWrite(redpin, gammatable[(int)red]);
  analogWrite(greenpin, gammatable[(int)green]);
  analogWrite(bluepin, gammatable[(int)blue]);
#endif
  //Verifing if there is an object in front of the robot 
    if((getDistance(13,12)) < (10)){
        ObstacleDerailleur();
        lineFollower();
    }
  //Line Following
  lineFollower();
}
