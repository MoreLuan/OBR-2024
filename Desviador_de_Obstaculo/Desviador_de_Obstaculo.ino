int trig = 11; // Trigger Pin 
int echo = 12; //Echo Pin

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
void MANOBRA(){
  //Turning Right
  analogWrite(5,0);
  analogWrite(6,100);
  delay(200);

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
  delay(200);

  //Turning Right
  analogWrite(5,0);
  analogWrite(6,100);
  delay(200);
}

// Setting arduino ports
void setup(){
  // Engine
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
  // Line Follower Sensor
    pinMode(8,INPUT);
    pinMode(9,INPUT);
}

void loop(){
  //Verifing if there is an object in front of the robot 
    if((getDistance(13,12)) < (10)){
        MANOBRA();
    }
  // Verificating if infrareds are working together
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
