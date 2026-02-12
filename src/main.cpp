#include "driver.h"
#include <Wire.h>

//ADXL345 Definitions:
#define X_Reg1 0x32
#define X_Reg2 0x33
#define Y_Reg1 0x34
#define Y_Reg2 0x35
#define Z_Reg1 0x36
#define Z_Reg2 0x37
#define PWR_CTL 0x2D

int X0;
int X1;

driver stepper(4, 5, 3, 6, 200);

std::vector<int> get_adx();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(50);
  Wire.beginTransmission(0x53);
  Wire.write(PWR_CTL);
  Wire.write(8);
  Wire.endTransmission();
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(10, 1);
  Wire.beginTransmission(0x53);
  Wire.write(X_Reg1);
  Wire.write(X_Reg2);
  Wire.endTransmission();
  Wire.requestFrom(0x53, 2);
  if(Wire.available() <= 2){
    X0 = Wire.read();
    X1 = Wire.read();
  }
  Serial.print("X0=");
  Serial.print(X0);
  Serial.print("X1=");
  Serial.println(X1);
}

std::vector<int> get_adx(){
  std::vector<int> vals;
  Wire.beginTransmission(0x53);
  Wire.write(X_Reg1);
  Wire.write(X_Reg2);
  Wire.endTransmission();
  Wire.requestFrom(0x53, 2);
  if(Wire.available() <= 2){
    X0 = Wire.read();
    X1 = Wire.read();
  }
  vals.push_back(X0);
  vals.push_back(X1);

  return vals;
}