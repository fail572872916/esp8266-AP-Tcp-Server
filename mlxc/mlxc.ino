
#include <ArduinoJson.h>
/*
  Name:    麦轮小车.ino
  Created: 2017/7/7 14:48:33
  Author:  Administrator
*/
String readString = "";
StaticJsonBuffer<200> jsonBuffer;
long  rightTopCount = 0;
long  leftTopCount = 0;
long  rightBottomCount = 0;
long  leftBottomCount = 0;


#define leftTopPinA 2 //外部中断1
#define rightTopPinB 22 //编码器的OUTB信号连接到数字端口
#define rightTopA 3 //外部中断0
#define rightTopB 23 //编码器的OUTB信号连接到数字端口

#define leftBottomPinA 18 //外部中断5
#define leftBottomPinB 24 //编码器的OUTB信号连接到数字端口

#define rightBottomPinA 19 //外部中断4
#define rightBottomPinB 25 //编码器的OUTB信号连接到数字端口
// the setup function runs once when you press reset or power the board
void setup() {
  //pwm
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  //方向
  pinMode(47, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(53, OUTPUT);
  //使能
  pinMode(46, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(52, OUTPUT);

  Serial.begin(9600);
  Serial1.begin(115200);

}

// the loop function runs over and over again until power down or reset
void loop() {
  //go_ahead();
  // serial_read();
  //  serial_read();
  read();
}
void read() {
  if (Serial1.available() > 0)
  {
    char a = Serial1.read();
    readString += a;
    if (a == '\n') {
      Serial.println(readString);
      Serial1.println(readString);

      JsonObject& root = jsonBuffer.parseObject(readString);
      if (!root.success()) {
        Serial3.println("failed");
        return;
      }
      Serial.println(readString);
       //ToDo 这里要改为 char
//      serial_read(readString);
      readString = "";
    }
  }
}


void serial_read(char a) {
  //ToDo 这里要改为 char
  switch (a)
  {
    case 'w':
      go_ahead(45, 55, 55, 55);
      delay(33);
      Serial.println('w');
      break;
    case 'a':
      go_left(45, 55, 55, 55);
      delay(33);
      Serial.println('a');
      break;
    case 'd':
      go_right(45, 55, 55, 55);
      delay(33);
      Serial.println('d');
      break;
    case 's': go_back(45, 55, 55, 55);
      delay(33);
      Serial.println('s');
      break;
    case 'l': right_rotate(45, 55, 55, 55);
      delay(33);
      Serial.println('l');
      break;
    case 'r':
      left_rotate(45, 55, 55, 55);
      delay(33);
      Serial.println('r');
      break;
  }

  //  else {
  //    go_ahead(0, 0, 0, 0);
  //  }
}
//前进
void go_ahead(int s1, int s2, int s3, int s4) {
  digitalWrite(47, HIGH);
  digitalWrite(46, LOW);
  analogWrite(8, s1);

  digitalWrite(53, LOW);
  digitalWrite(52, LOW);
  analogWrite(9, s2);

  digitalWrite(51, HIGH);
  digitalWrite(50, LOW);
  analogWrite(10, s3);

  digitalWrite(49, LOW);
  digitalWrite(48, LOW);
  analogWrite(11, s4);
}

void go_back(int s1, int s2, int s3, int s4) {
  digitalWrite(47, LOW);
  digitalWrite(46, LOW);
  analogWrite(8, s1);

  digitalWrite(53, HIGH);
  digitalWrite(52, LOW);
  analogWrite(9, s2);

  digitalWrite(51, LOW);
  digitalWrite(50, LOW);
  analogWrite(10, s3);

  digitalWrite(49, HIGH);
  digitalWrite(48, LOW);
  analogWrite(11, s4);
}

void go_left(int s1, int s2, int s3, int s4) {
  digitalWrite(47, HIGH);
  digitalWrite(46, LOW);
  analogWrite(8, s1);

  digitalWrite(53, HIGH);
  digitalWrite(52, LOW);
  analogWrite(9, s2);

  digitalWrite(51, LOW);
  digitalWrite(50, LOW);
  analogWrite(10, s3);

  digitalWrite(49, LOW);
  digitalWrite(48, LOW);
  analogWrite(11, s4);
}
//右
void go_right(int s1, int s2, int s3, int s4) {
  digitalWrite(47, LOW);
  digitalWrite(46, LOW);
  analogWrite(8, s1);

  digitalWrite(53, LOW);
  digitalWrite(52, LOW);
  analogWrite(9, s2);

  digitalWrite(51, HIGH);
  digitalWrite(50, LOW);
  analogWrite(10, s3);

  digitalWrite(49, HIGH);
  digitalWrite(48, LOW);
  analogWrite(11, s4);
}



//旋转-右
void right_rotate(int s1, int s2, int s3, int s4) {
  digitalWrite(47, HIGH);
  digitalWrite(46, LOW);
  analogWrite(8, s1);

  digitalWrite(53, HIGH);
  digitalWrite(52, LOW);
  analogWrite(9, s2);

  digitalWrite(51, HIGH);
  digitalWrite(50, LOW);
  analogWrite(10, s3);

  digitalWrite(49, HIGH);
  digitalWrite(48, LOW);
  analogWrite(11, s4);
}

//旋转-左
void left_rotate(int s1, int s2, int s3, int s4) {
  digitalWrite(47, LOW);
  digitalWrite(46, LOW);
  analogWrite(8, s1);

  digitalWrite(53, LOW);
  digitalWrite(52, LOW);
  analogWrite(9, s2);

  digitalWrite(51, LOW);
  digitalWrite(50, LOW);
  analogWrite(10, s3);

  digitalWrite(49, LOW);
  digitalWrite(48, LOW);
  analogWrite(11, s4);
}








//90goLeft
void goLeft_90()
{
  //  可能需要在这增加编码器
  if ( rightTopCount  <= 390 || leftTopCount >= -390)
  {

    go_left(45, 55, 55, 55);
    return;
  }
  else   {
    go_ahead(0, 0, 0, 0);
    leftTopCount = 0;
    rightTopCount = 0;
    //Todo
    
    delay(1500);

  }
}

//90掳goRight
void goRight_90() {
  if (leftTopCount <= 392 || rightTopCount >= -392)
  {

    go_right(45, 55, 55, 55);

    return;
  } else {
    go_ahead(0, 0,0,0);
    leftTopCount = 0;
    rightTopCount = 0;
   

    delay(1500);
  }
}

//180goLeft
void goLeft_180() {
  //  todo
  if ( rightTopCount  <= 790 || leftTopCount >= -790)
  {

  go_left(45, 55, 55, 55);
    return;
  } else {
    go_ahead(0, 0,0,0);
    leftTopCount = 0;
    rightTopCount = 0;
   
    delay(1500);
  }
}







