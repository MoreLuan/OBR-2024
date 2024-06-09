#define LeftEngine1 3
#define LeftEngine2 4
#define RightEngine1 5
#define RightEngine2 6
#define LeftDirectionSensor 7
#define LeftSensor 8
#define RightSensor 9
#define RightDirectionSensor 10
void setup() {
  // Engine
  pinMode(LeftEngine1, OUTPUT);
  pinMode(LeftEngine2, OUTPUT);
  pinMode(RightEngine1, OUTPUT);
  pinMode(RightEngine2, OUTPUT);
  // Line Follower Sensor
  pinMode(LeftSensor, INPUT);
  pinMode(RightSensor, INPUT);
  //Direction Sensor
  pinMode(LeftDirectionSensor, INPUT);
  pinMode(RightDirectionSensor, INPUT);
}

void loop() {
  // Verificating if infrareds are working together
  if (((digitalRead(LeftDirectionSensor)) < (1) && (digitalRead(RightDirectionSensor)) < (1))) {
      //Turning each Engine On
      analogWrite(LeftEngine1, 0);
      analogWrite(LeftEngine2, 95);
      analogWrite(RightEngine1, 0);
      analogWrite(RightEngine2, 75);
      delay(200);
    //Align ajust by engine
    if ((digitalRead(LeftSensor)) < (1)) {
      analogWrite(LeftEngine1, 0);
      analogWrite(LeftEngine2, 95);
    } else {
      analogWrite(LeftEngine1, 0);
      analogWrite(LeftEngine2, 0);
    }
    if ((digitalRead(RightSensor)) < (1)) {
      analogWrite(RightEngine1, 0);
      analogWrite(RightEngine2, 75);
    } else {
      analogWrite(RightEngine1, 0);
      analogWrite(RightEngine2, 0);
    }
  } else {
  //Direction ajust by engine
  if ((digitalRead(LeftDirectionSensor)) == (1)) {
    analogWrite(LeftEngine1, 0);
    analogWrite(LeftEngine2, 100);
    delay(500);
  }
  if ((digitalRead(RightDirectionSensor)) == (1)) {
    analogWrite(RightEngine1, 0);
    analogWrite(RightEngine2, 100);
    delay(500);
  }
}
}
