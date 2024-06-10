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
}

void loop() {
  // Verificating if infrareds are working together
  if ((((digitalRead(8)) && (digitalRead(9))) == (1))) {
    //Turning each Engine On
    analogWrite(3, 0);
    analogWrite(4, 85);
    analogWrite(5, 0);
    analogWrite(6, 75);
    delay(200);
  }
  //Direction ajust by engine
  if ((digitalRead(7)) < (1)) {
    analogWrite(3, 0);
    analogWrite(4, 100);
  }
  if ((digitalRead(10)) < (1)) {
    analogWrite(5, 0);
    analogWrite(6, 100);
  }
  //Align ajust by engine
  if ((digitalRead(8)) < (1)) {
    analogWrite(3, 0);
    analogWrite(4, 85);
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
