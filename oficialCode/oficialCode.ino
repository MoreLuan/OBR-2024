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
  if (digitalRead(8) == 0 && digitalRead(9)== 0) {
    //Turning each Engine On
    analogWrite(3, 0);
    analogWrite(4, 85);
    analogWrite(5, 0);
    analogWrite(6, 73);
    delay(100);
  }
  //Direction ajust by engine
  else if (digitalRead(7) == 0 && digitalRead(10) == 1) {
    delay(200);
    analogWrite(3, 0);
    analogWrite(4, 85);
    analogWrite(5, 0);
    analogWrite(6, 0);
    delay(700);
  }
  else if (digitalRead(10) == 0 && digitalRead(7) == 1) {
    delay(200);
    analogWrite(3, 0);
    analogWrite(4, 0);
    analogWrite(5, 0);
    analogWrite(6, 73);
    delay(700);
  }
  //Align ajust by engine
  else if (digitalRead(8) == 0 && digitalRead(9) == 1 && digitalRead(10) == 1 && digitalRead(7) == 1) {
    analogWrite(3, 0);
    analogWrite(4, 85);
    analogWrite(5, 0);
    analogWrite(6, 0);
  }
  else if (digitalRead(9) == 0 && digitalRead(8) == 1 && digitalRead(10) == 1 && digitalRead(7) == 1) {
    analogWrite(3, 0);
    analogWrite(4, 0);
    analogWrite(5, 0);
    analogWrite(6, 73);
  }
  else{
    analogWrite(3, 0);
    analogWrite(4, 85);
    analogWrite(5, 0);
    analogWrite(6, 73);
    delay(100);
  }
}
