#include "driver.h"
#include <Wire.h>
#include "DFRobot_ADXL345.cpp"

//ADXL345 Definitions:
#define X_Reg1 0x32
#define X_Reg2 0x33
#define Y_Reg1 0x34
#define Y_Reg2 0x35
#define Z_Reg1 0x36
#define Z_Reg2 0x37
#define PWR_CTL 0x2D
#define cs_pin 10

int X0;
int X1;

driver stepper(4, 5, 3, 6, 200);
DFRobot_ADXL345_I2C ADXL345_thigh(&Wire,0x53);
DFRobot_ADXL345_I2C ADXL345_calf(&Wire,0x1D);

int accval_thigh[3];
int accval_calf[3];


void setup() {
  Serial.begin(9600);
  ADXL345_thigh.begin();
  ADXL345_thigh.powerOn();
  ADXL345_calf.begin();
  ADXL345_calf.powerOn();
}

void loop() {
  ADXL345_thigh.readAccel(accval_thigh);
  ADXL345_calf.readAccel(accval_calf);
  ADXL345_thigh.RPCalculate(accval_thigh);
  ADXL345_calf.RPCalculate(accval_calf);

  
  Serial.print("Thigh Roll:"); Serial.println( ADXL345_thigh.RP.roll );
  Serial.print("Thigh Pitch:"); Serial.println( ADXL345_thigh.RP.pitch );
  Serial.print("calf Roll:"); Serial.println( ADXL345_calf.RP.roll );
  Serial.print("calf Pitch:"); Serial.println( ADXL345_calf.RP.pitch );
  delay(500);
}