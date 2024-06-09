int trig = 11; // Trigger Pin
int echo = 12; //Echo Pin

void setup() {
  // Engine
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  // Line Follower Sensor
  pinMode(8, INPUT);
  pinMode(9, INPUT);
}

//Verification function to see if there is an object in front of the robot
float getDistance(int trig, int echo) {
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH, 300) / 58.0;
}

void loop() {
  if ((((digitalRead(8)) && (digitalRead(9))) == (1))) {
    //Turning each Engine On
    analogWrite(3, 0);
    analogWrite(4, 75);
    analogWrite(5, 0);
    analogWrite(6, 75);
    delay(200);
  }
  //Direction ajust by engine
  if ((digitalRead(8)) < (1)) {
    analogWrite(3, 0);
    analogWrite(4, 75);
  } else {
    analogWrite(3, 0);
    analogWrite(4, 0);
  }
  if ((digitalRead(9)) < (1)) {
    analogWrite(5, 0);
    analogWrite(6, 75);
  } else {
    analogWrite(5, 0);
    analogWrite(6, 0);
  }
}
