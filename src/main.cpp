#include "driver.h"
#include <Wire.h>
#include "DFRobot_ADXL345.cpp"

//ADXL345 Definitions:
#define THIGH_ADXL_ADDR 0x53
#define CALF_ADXL_ADDR 0x1D
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

String x, y, z;

driver stepper(4, 5, 3, 6, 200);

float getWireRead();


void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(THIGH_ADXL_ADDR);
  Wire.write(X_Reg1);
  Wire.endTransmission(false);
  Wire.requestFrom(THIGH_ADXL_ADDR, 6, true);

  x = getWireRead();
  y = getWireRead();
  z = getWireRead();

  Serial.println("X: " + x + " Y: " + y + " Z: " + z);
  delay(50);
}

float getWireRead(){
  float value = Wire.read() | (Wire.read() << 8);
  return value/256;
}