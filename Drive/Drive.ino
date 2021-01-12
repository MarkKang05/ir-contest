#include <Servo.h>
Servo gripSV;
Servo liftSV;

#define Line_Sensor 11
#define LEFT_SPD 3
#define LEFT_A1 4
#define LEFT_B1 5
#define RIGHT_A2 7
#define RIGHT_B2 8
#define RIGHT_SPD 6
#define F_E_Pin A0
#define F_T_Pin A1
#define L_E_Pin A3
#define L_T_Pin A2
#define R_E_Pin A4
#define R_T_Pin A5



void setup() {
  pinMode(Line_Sensor, INPUT);
  pinMode(LEFT_SPD, OUTPUT);
  pinMode(LEFT_A1, OUTPUT);
  pinMode(RIGHT_A2, OUTPUT);
  pinMode(LEFT_B1, OUTPUT);
  pinMode(RIGHT_B2, OUTPUT);
  pinMode(RIGHT_SPD, OUTPUT);
  pinMode(F_E_Pin, INPUT);
  pinMode(F_T_Pin, OUTPUT);
  pinMode(L_E_Pin, INPUT);
  pinMode(L_T_Pin, OUTPUT);
  pinMode(R_E_Pin, INPUT);
  pinMode(R_T_Pin, OUTPUT);
  Serial.begin(9600);

  gripSV.attach(9);  
  liftSV.attach(10);
  liftSV.write(180);
  gripSV.write(0);
  delay(1000);
  gripSV.detach();
  liftSV.detach();
  delay(1000);
}

void loop() {

  int wall = 4.5;

  if (L_distance() < wall) { // Detecting Left
    while (1) {
      if (L_distance() > 3.75) {
        stop();
        break;
      }
      motors(2, 88, 0, 0, 2);
    }
  }

  else if (R_distance() < wall) { // Detecting Right
    while (1) {
      if (R_distance() > 4.5) {
        stop();
        break;
      }
      motors(0, 0, 2, 88, 2);
    }
  }

  else if (L_distance() > 28) { // Detecting Left Whole
    stop();
    motors(2, 100, 2, 100, 200);
    stop();
    while (1) {
      if (R_distance() > 14 ) {
        stop();
        break;
      }
      motors(0, 0, 2, 88, 2);
    }
    motors(2, 90, 2, 90, 250);
    stop();
    while (1) {
      if (L_distance() < 7 ) { //
        stop();
        break;
      }
      motors(0, 0, 2, 88, 2);
    }
    motors(2, 100, 2, 100, 350);
    stop();
  }

  else if (R_distance() > 28) { // De, 0, 0, tecting Right Whole
    stop();
    motors(2, 100, 2, 100, 200);
    stop();
    while (1) {
      if (L_distance() > 14 ) { //16
        stop();
        break;
      }
      motors(2, 88, 0, 0, 2);
    }
    motors(2, 90, 2, 90, 250);////
    stop();
    while (1) { 
      if (R_distance() < 7) {  //R_distance() < 7
        stop();
        break;
      }
      motors(2, 88, 0, 0, 2);
    }
    motors(2, 100, 2, 100, 350);
    stop();
  }

  else {
    motors(2, 85, 2, 85, 2);
  }

  //Serial.println(digitalRead(Line_Sensor));

}



float F_distance() {

  float duration_a, F_distance;
  digitalWrite(F_T_Pin, HIGH);
  delay(10);
  digitalWrite(F_T_Pin, LOW);
  duration_a = pulseIn(F_E_Pin, HIGH);
  F_distance = ((float)(340 * duration_a) / 10000) / 2;

  return (int)F_distance;
}


float L_distance() {
  float duration_b, L_distance;
  digitalWrite(L_T_Pin, HIGH);
  delay(10);
  digitalWrite(L_T_Pin, LOW);
  duration_b = pulseIn(L_E_Pin, HIGH);
  L_distance = ((float)(340 * duration_b) / 10000) / 2;

  return (int)L_distance;
}

float R_distance() {
  float duration_c, R_distance;
  digitalWrite(R_T_Pin, HIGH);
  delay(10);
  digitalWrite(R_T_Pin, LOW);
  duration_c = pulseIn(R_E_Pin, HIGH);
  R_distance = ((float)(340 * duration_c) / 10000) / 2;

  return (int)R_distance;
}

bool LineSensor() {
  return digitalRead(Line_Sensor);
}

void stop() {
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, LOW);
  analogWrite(LEFT_SPD, 0);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, LOW);
  analogWrite(RIGHT_SPD, 0);
  delay(200);
}

void motors(int d_l, int s_l, int d_r, int s_r, int delay_time) {
 
  if (d_l == 0) {
    digitalWrite(LEFT_A1, LOW);
    digitalWrite(LEFT_B1, LOW);
    analogWrite(LEFT_SPD, 0);
  } else if (d_l == 1) {
    digitalWrite(LEFT_A1, HIGH);
    digitalWrite(LEFT_B1, LOW);
    analogWrite(LEFT_SPD, s_l);
  } else if (d_l == 2) {
    digitalWrite(LEFT_A1, LOW);
    digitalWrite(LEFT_B1, HIGH);
    analogWrite(LEFT_SPD, s_l);
  } else {}

  if (d_r == 0) {
    digitalWrite(RIGHT_A2, LOW);
    digitalWrite(RIGHT_B2, LOW);
    analogWrite(RIGHT_SPD, 0);
  } else if (d_r == 1) {
    digitalWrite(RIGHT_A2, HIGH);
    digitalWrite(RIGHT_B2, LOW);
    analogWrite(RIGHT_SPD, s_r+30);
  } else if (d_r == 2) {
    digitalWrite(RIGHT_A2, LOW);
    digitalWrite(RIGHT_B2, HIGH);
    analogWrite(RIGHT_SPD, s_r+30);
  } else {}

  delay(delay_time);
}
