#include<Servo.h>

Servo servo_wing_right;
Servo servo_wing_left;
Servo servo_rudder;

int sum = 0, deg = 0, flag = 0;

void servo_write(int number, int degree)
{
  int micro_sec;

  // 度数からマイクロ秒に変換
  if(degree>=0 && degree<=22)
    micro_sec = degree*10+550;
  else if(degree <= 54)
    micro_sec = degree*10+560;
  else if(degree <= 86)
    micro_sec = degree*10+570;
  else if(degree <= 118)
    micro_sec = degree*10+580;
  else if(degree <= 151)
    micro_sec = degree*10+590;
  else if(degree <= 180)
    micro_sec = degree*10+600;

  switch (number) {
    case 0:  // 右翼
      Serial.println("ok");
      servo_wing_right.writeMicroseconds(micro_sec);
      break;
      
    case 1:  // 左翼
      servo_wing_left.writeMicroseconds(micro_sec);
      break;
      
    case 2:  // 舵
      servo_rudder.writeMicroseconds(micro_sec);
      break;
      
    default:
      break;
  }

  Serial.println(micro_sec);
}

void setup()
{
  servo_wing_right.attach(3);
  servo_wing_left.attach(4);
  servo_rudder.attach(5);

  Serial.begin(9600);
}

void loop()
{
  readSerial();

  if (flag == 1) {
    servo_write(0,deg);
    flag = 0;
  }
}

void readSerial() {
  char str;
  if (Serial.available()) {
    str = Serial.read();
    
    switch (str) {
      case '0'...'9':
        sum = sum * 10 + (str - 48);
        break;
        
      case 's':
        deg = sum;
        flag = 1;
        Serial.println(deg);
        sum = 0;
        break;
        
      default:
        sum = 0;
        break;
    }
  }
}
