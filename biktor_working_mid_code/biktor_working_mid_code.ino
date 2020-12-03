
//main.ino
#include <NewPing.h>

String val;
int val_xmove;
int val_ymove;
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


bool buz;//BUZZER, состояние звукового сигнала
bool led;// LED, состояние фар
int del;//DELAY, промежуток между сигналами приближения
bool by = 1; //БУ, сигнал при приближении
bool muting = 0;//MUTING, реакция динамика на приближение(???)

//ALPHA VARIABLES
int sped = 255;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(38400);
  pinMode(out_one, OUTPUT);
  pinMode(out_two, OUTPUT);
  pinMode(out_three, OUTPUT);
  pinMode(out_four, OUTPUT);
  pinMode(13, OUTPUT);

}
void loop() {
  if (Serial.available()) {
    val = Serial.readStringUntil('#');
    val_move = (val.substring(0, 1))[0];
    val_button = (val.substring(1, 2))[0];
    Serial.println("X-" + val_xmove);
    Serial.println("Y-" + val_ymove);
    Serial.println(val_button);

    int X = map(int val_xmove, -255, 255, 0, 223);
    int Y = map(int val_ymove, -255, 255, 0, 223);
   if(X>0){
    analogWrite()
    }

    switch (val_button) {
      case '4':
        break;
      case '3':
        digitalWrite(LED_PIN, 1);
        break;
      case '2':
        digitalWrite(LED_PIN, 0);
        break;
      case '1':

        break;
    }
  }
}

void Son() {
  unsigned int uS = sonar.ping_cm();
  Serial.print(uS);
  Serial.println("cm");
  if (uS <= 30 && uS > 3) {
    del = uS * 2.5;
    //if(!muting)
    //analogWrite(BUZZER_PIN, VOLUME);
    if (led == 1)/* {*/
      /*for (int i = 0; i < 10; ++i) {*/
      digitalWrite(LED_PIN, 1);


    /* }*/
    /* }*/
    delay(45 + del);
    digitalWrite(LED_PIN, 0);
    // digitalWrite(BUZZER_PIN, 0);

  }
  delay(5);
}
