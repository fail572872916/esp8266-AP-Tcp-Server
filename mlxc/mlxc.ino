
/*
  Name:    麦轮小车.ino
  Created: 2017/7/7 14:48:33
  Author:  Administrator
*/
String readString = "";
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
    //  { i += char(Serial1.read());
    char a = Serial1.read();
    readString += a;
    if (a == '\n') {
      Serial.println(readString);
      Serial1.println(readString);
      readString = "";
    }

  }
}


void serial_read() {
  if (Serial1.available() > 0)
  {
    //  { i += char(Serial1.read());
    char a = char( Serial1.read());
    //delay(10);
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
      case 'e': go_right_up(45, 0, 0, 55);
        delay(33);
        Serial.println('e');
        break;
      case 'c': go_right_down(45, 0, 0, 55);
        delay(33);
        Serial.println('c');
        break;
      case 'q': go_left_up(0, 55, 55, 0);
        delay(33);
        Serial.println('q');
        break;
      case 'z': go_left_down(0, 55, 55, 0);
        delay(33);
        Serial.println('z');
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
  }
  else {
    go_ahead(0, 0, 0, 0);
  }
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


//右上
void go_right_up(int s1, int s2, int s3, int s4) {
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

//右下
void go_right_down(int s1, int s2, int s3, int s4) {
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
//左上
void go_left_up(int s1, int s2, int s3, int s4) {
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
//左下
void go_left_down(int s1, int s2, int s3, int s4) {
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
