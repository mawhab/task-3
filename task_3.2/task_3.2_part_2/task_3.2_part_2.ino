#define PPR 2048

// encoder pins
#define B1 2
#define A1 3

#define B2 18
#define A2 19

#define B3 20
#define A3 21

#define led 8

int counter[]= {0, 0, 0}; // counters for encoders

// interrupt functions that calulate encoder movement
void ISR_A1(){
  if(digitalRead(A1)!= digitalRead(B1)){
    counter[0]++;
  }else{
    counter[0]--;
  }
}
void ISR_B1(){
  if(digitalRead(A1)!= digitalRead(B1)){
    counter[0]--;
  }else{
    counter[0]++;
  }
}

void ISR_A2(){
  if(digitalRead(A2)!= digitalRead(B2)){
    counter[1]++;
  }else{
    counter[1]--;
  }
}
void ISR_B2(){
  if(digitalRead(A2)!= digitalRead(B2)){
    counter[1]--;
  }else{
    counter[1]++;
  }
}

void ISR_A3(){
  if(digitalRead(A3)!= digitalRead(B3)){
    counter[2]++;
  }else{
    counter[2]--;
  }
}
void ISR_B3(){
  if(digitalRead(A3)!= digitalRead(B3)){
    counter[2]--;
  }else{
    counter[2]++;
  }
}

void setup() {
  // setting pin modes and attaching interrupts to encoders
  pinMode(A1, INPUT_PULLUP);
  pinMode(B1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(A1), ISR_A1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(B1), ISR_B1, CHANGE);

  pinMode(A2, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(A2), ISR_A2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(B2), ISR_B2, CHANGE);

  pinMode(A3, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(A3), ISR_A3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(B3), ISR_B3, CHANGE);

  pinMode(led, OUTPUT);

}

void loop() {
  // calculating degrees moved relative to start
  int degree1 = counter[0] / 4 / PPR * 360;
  int degree2 = counter[1] / 4 / PPR * 360;
  int degree3 = counter[2] / 4 / PPR * 360;
  
  if(degree1 == 37 && degree2 == 10 && degree3 == 54){ // if the correct degrees are set
    digitalWrite(led, HIGH); // turn on led
  }else{
    digitalWrite(led, LOW);// else turn off led
  }

}
