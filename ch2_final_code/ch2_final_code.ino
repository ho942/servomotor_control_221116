#include<Wire.h>
#include <Servo.h> // servo motor library

int test_LED = 7;//for lighting
Servo servo;


const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;




void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(test_LED, OUTPUT);
  
  servo.attach(9);      // Servo motor control #9 pin allocation
  //servo.write(90);     // Servomotor initial angle set to 90 degrees (door closed)
servo.write(90);

  
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(333);


if (AcX>=20000 || AcX<-20000 || AcY>=20000 || AcY<-20000){

//digitalWrite(test_LED, HIGH);

  //
  servo.write(90);
  delay(5000);

 // servo.write(180);//
 // delay(5000);//
  

  
  servo.write(100);
  delay(5000);
  servo.write(110);
  delay(5000);
    servo.write(120);
  delay(5000);
  digitalWrite(test_LED, HIGH);
      servo.write(130);
  delay(5000);
      servo.write(140);
  delay(5000);
      servo.write(150);
  delay(5000);
      servo.write(160);
  delay(5000)  ;  
  servo.write(170);
  delay(5000);

  servo.write(180);
  delay(5000);



//digitalWrite(test_LED, LOW);
//servo.write(90);
 //delay(5000);//
exit(0); //stop.
  
  
  
        
}


}
