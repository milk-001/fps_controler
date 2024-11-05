#include <Keyboard.h>   
#include <Mouse.h>
#include <Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int mouse_moving = 13;
int shift = 9;
int mouse_r = 8;
int mouse_l = 5;
int r = 12;
int q = 10;
int f = 11;
const int sw=7;
int x=0;
int y=0;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(115200);
  Mouse.begin();
  Keyboard.begin();
  Serial.println("Mouse Start!!");
  pinMode(mouse_r, INPUT);
  pinMode(mouse_l, INPUT);
  pinMode(r, INPUT);
  pinMode(q, INPUT);
  pinMode(f, INPUT);
  pinMode(1, INPUT);
  pinMode(shift, INPUT);
  pinMode (sw, INPUT_PULLUP);
  pinMode(mouse_moving, INPUT);
}

void loop(){
  x=analogRead(A0);
  y=analogRead(A1);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();
  
  int16_t gyroX, gyroZ;
  int Sensitivity = 300;
  gyroX = GyX / Sensitivity / 1.1 * -1;
  gyroZ = GyZ / Sensitivity * -1;

  if(digitalRead(mouse_moving) == HIGH){
    Mouse.move(gyroZ, gyroX);
  }
  if(digitalRead(mouse_l) == HIGH){
    Mouse.press(MOUSE_LEFT);
  }else{
    Mouse.release(MOUSE_LEFT);
  }

  if(digitalRead(mouse_r) == HIGH){
    Mouse.press(MOUSE_RIGHT);
  }else{
    Mouse.release(MOUSE_RIGHT);
  }
  if(digitalRead(shift) == HIGH){
    Keyboard.press(KEY_LEFT_SHIFT);
  }else{
    Keyboard.release(KEY_LEFT_SHIFT);
  }
  if(digitalRead(r) == HIGH){
    Keyboard.press('r');
  }else{
    Keyboard.release('r');
  }
  if(digitalRead(q) == HIGH){
    Keyboard.press('q');
  }else{
    Keyboard.release('q');
  }
  if(digitalRead(f) == HIGH)
    Keyboard.press('f');
  }else{
    Keyboard.release('f');
  }
  if (x==0) {
    Keyboard.press('s');
  }else{
    Keyboard.release('s');
  }
  if (x > 1000) {
    Keyboard.press('w');
  }else{
    Keyboard.release('w');
  }
  if (y==0) {
    Keyboard.press('a');
  }else{
    Keyboard.release('a');
  }
  if (y > 1000) {
    Keyboard.press('d');
  }else{
    Keyboard.release('d');
  }
  if (digitalRead(sw)==LOW) {
    Keyboard.press(' ');
  }else{
    Keyboard.release(' ');
  }
}
