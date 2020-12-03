
//main.ino
#include <NewPing.h>

String val;
char val_move;
char val_button;

const int TRIGGER_PIN = 4;
const int ECHO_PIN = 2;
const int MAX_DISTANCE = 200;
/*const int BUZZER_PIN = 6;
  const int VOLUME = 200;*/
const int LED_PIN = 13;

const int out_one = 9;//PWM
const int out_two = 7;
const int out_three = 10;//PWM
const int out_four = 8;

void go_forward(int sped);
void go_backward(int sped);
void go_leftF(int sped);
void go_rightF(int sped);
void go_leftB(int sped);
void go_rightB(int sped);
void fstop();


bool buz;//BUZZER, состояние звукового сигнала
bool led;// LED, состояние фар
int del;//DELAY, промежуток между сигналами приближения
bool by = 1; //БУ, сигнал при приближении
int ll;
bool muting = 0;//MUTING, реакция динамика на приближение(???)

//ALPHA VARIABLES
int sped = 255;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  pinMode(out_one, OUTPUT);
  pinMode(out_two, OUTPUT);
  pinMode(out_three, OUTPUT);
  pinMode(out_four, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

}
void loop() {
  if (Serial.available()) {
    val = Serial.readStringUntil('#');
    val_move = (val.substring(0, 1))[0];
    val_button = (val.substring(1, 2))[0];
    Serial.println(val_move);
    Serial.println(val_button);
    if (sonar.ping_cm() <= 30) {
      sped=sonar.ping_cm();
    }
    else
    sped= 255;

    switch (val_move) {
      case '0':
        go_forward(0);
        break;
      case 'W':
        go_forward(sped);
        break;
      case 'E':
      if(sped==30){
      	go_backward(255);}
        go_backward(sped);
        break;
      case 'S':
        go_leftF(2*sped);
        break;
      case 'B':
        go_leftB(sped/2);
        break;
      case 'C':
        go_leftF(sped/2);
        break;
      case 'D':
        go_rightF(sped/2);
        break;
      case 'N':
        go_rightF(sped*2);
        break;
      case 'A':
        go_rightB(sped/2);
        break;

    }
  }
  switch (val_button) {
    case '4':
      fstop();
      break;
    case '3':
      digitalWrite(LED_PIN, 1);
      break;
    case '2':
      digitalWrite(LED_PIN, 0);
      break;
    case '1':
      if (ll == 0) {
        digitalWrite(3, 0);
        digitalWrite(5, 0);
        ll =1;
        //break;
      }
      else {
        digitalWrite(3, 1);
        digitalWrite(5, 1);
        ll=0;
        // break;
      }

      break;
  }
}
void go_forward(int sped/*0-255*/) {
  analogWrite(out_one, sped);
  digitalWrite(out_two, 0);
  analogWrite(out_three, sped);
  digitalWrite(out_four, 0);
}


void go_backward(int sped/*1-255*/) {
  analogWrite(out_one, 255 - sped);
  digitalWrite(out_two, 1);
  analogWrite(out_three, 255 - sped);
  digitalWrite(out_four, 1);
}


void go_leftF(int sped/*1-510*/) {
  if (sped <= 255) {
    analogWrite(out_one, 255 - sped);
    digitalWrite(out_two, 0);
  }
  else {
    analogWrite(out_one, 510 - sped);
    digitalWrite(out_two, 1);
  }
  analogWrite(out_three, 255);
  digitalWrite(out_four, 0);
}


void go_rightF(int sped/*1-510*/) {

  analogWrite(out_one, 255);
  digitalWrite(out_two, 0);
  if (sped <= 255) {
    analogWrite(out_three, 255 - sped);
    digitalWrite(out_four, 0);
  }
  else {
    analogWrite(out_three, 510 - sped);
    digitalWrite(out_four, 1);
  }
}


void go_leftB(int sped/*1-255*/) {
  analogWrite(out_one, 0);
  digitalWrite(out_two, 1);
  analogWrite(out_three, 255 - sped);
  digitalWrite(out_four, 1);
}


void go_rightB(int sped/*1-255*/) {
  analogWrite(out_one, 255 - sped);
  digitalWrite(out_two, 1);
  analogWrite(out_three, 0);
  digitalWrite(out_four, 1);
}


void fstop() {
  digitalWrite(out_one, 0);
  digitalWrite(out_two, 0);
  digitalWrite(out_three, 0);
  digitalWrite(out_four, 0);
}
//void Son() {
//  unsigned int uS = sonar.ping_cm();
//  Serial.print(uS);
//  Serial.println("cm");
//  if (uS <= 30 && uS > 3) {
//    del = uS * 2.5;
//    //if(!muting)
//    //analogWrite(BUZZER_PIN, VOLUME);
//    if (led == 1)/* {*/
//      /*for (int i = 0; i < 10; ++i) {*/
//      digitalWrite(LED_PIN, 1);
//
//
//    /* }*/
//    /* }*/
//    delay(45 + del);
//    digitalWrite(LED_PIN, 0);
//    // digitalWrite(BUZZER_PIN, 0);
//
//  }
//  delay(5);
//}*/
