#include <arduino-timer.h>

// setting pins for leds and button
#define BTN 2
#define WHITE 10
#define GREEN 11
#define RED 12

Timer<5> timer; // creating timer

void start_routine(){ // method to start everything
  timer.cancel(); // cancel all to start from the beginning
  digitalWrite(RED, HIGH); // turns on red led
  timer.in(15*60*1000, redOff); // turn redd led off in 15 minutes
  timer.every(2*60*1000, blinkGreen); // blink green led every 2 minutes
  timer.in(5*60*1000, blinkWhite); // blink white led in 5 minutes
  timer.in(8*60*1000, blinkWhite); // blink white led in 8 minutes
}

void redOff(){ // turn red led off
  digitalWrite(RED, LOW);
}

// white led blinks for 10 seconds
void blinkWhite(){
  for(int i=0;i<20;i++){
    digitalWrite(WHITE, HIGH);
    delay(250);
    digitalWrite(WHITE, LOW);
    delay(250);
  }
}


// green led blinks for 5 seconds
void blinkGreen(){
  for(int i=0;i<10;i++){
    digitalWrite(GREEN, HIGH);
    delay(250);
    digitalWrite(GREEN, LOW);
    delay(250);
  }
}


void setup()
{
  pinMode(WHITE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN), start_routine, FALLING);
}

void loop()
{
  timer.tick();
}
