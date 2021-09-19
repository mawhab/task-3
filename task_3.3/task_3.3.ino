#include <Wire.h>

#define led 5


#define IMU_ADDR 0x68
int16_t raw_gyro_x, raw_gyro_z; // variables for gyro raw data
int16_t gyro_x=0, gyro_z=0; // variables for gyro proccessed data
float gyro_raw_error_x, gyro_raw_error_z; //Here we store the initial gyro data error
float currTime, elapsedTime, prevTime; // variables used for tracking time

// read 2 bytes from a give registry
uint16_t read2Bytes(uint8_t reg){
  uint16_t data=0;
  Wire.beginTransmission(IMU_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDR, 2);
  while(Wire.available() < 2);
  data = Wire.read() << 8 | Wire.read();
  return data;
}

// write to a given registry
// used for setting configurations
void setReg(uint8_t reg, uint8_t val){
  Wire.beginTransmission(IMU_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void blinkRed(){
  for(int i=0;i<30;i++)
    digitalWrite(led, !digitalRead(led));
}

int errorCalc(){
  /*Here we calculate the gyro data error before we start the loop
  I make the mean of 200 values, that should be enough*/
  for(int i=0; i<200; i++)
  {

    // request and read c and z values from register
    raw_gyro_x = (read2Bytes(0x43)); 
    raw_gyro_z = (read2Bytes(0x47));

    
    // add all values read to one varuable
    /*---X---*/
    gyro_raw_error_x += (raw_gyro_x/65.5); 
    /*---Z---*/
    gyro_raw_error_z += (raw_gyro_z/65.5);
  }

  // get the mean error
  gyro_raw_error_x /= 200;
  gyro_raw_error_z /= 200;
}

void setup() {
  pinMode(led, OUTPUT); // led set as output
  
  Serial.begin(9600); // init serial

  // begin serial communication
  Wire.begin();
  Wire.beginTransmission(IMU_ADDR); // begin sommunication with mpu
  Wire.write(0x6B); // select pwr management register
  Wire.write(0); // set to 0 to wake up mpu
  Wire.endTransmission(true); // end communication

  setReg(0x1B, 0x08); // setting gyro settings to 500

  errorCalc(); // calculate stationary error

  currTime = millis();
}

void loop() {
  // calculating time elapsed
  prevTime = currTime;
  currTime = millis();
  elapsedTime = (currTime-prevTime) / 1000;

  // getting raw data in degrees/sec - the error calculated
  raw_gyro_x = (read2Bytes(0x43) / 65.5) - gyro_raw_error_x;
  raw_gyro_z = (read2Bytes(0x47) / 65.5) - gyro_raw_error_z;

  // integrating raw data to get degrees and adding onto accumulative variables
  gyro_x += raw_gyro_x*elapsedTime;
  gyro_z += raw_gyro_z*elapsedTime;

  if(gyro_x>=60 || gyro_z>=60 || gyro_x>=-60 || gyro_z>=-60)blinkRed(); // if there is a pitch or roll degree of 60 ormore blink red led
  digitalWrite(led, LOW);

}
