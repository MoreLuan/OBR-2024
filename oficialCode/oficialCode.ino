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
