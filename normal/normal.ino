#include <Servo.h>
Servo gripSV;
Servo liftSV;

#define Line_Sensor_L 11
#define Line_Sensor_R 12
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
  pinMode(Line_Sensor_L, INPUT);
  pinMode(Line_Sensor_R, INPUT);
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
  //  liftSV.detach();
  delay(1000);
}

//dark ==> 0
int black = 0;
int white = 1;

void loop() {

  while (1) {
    if (LineSensor_L() == white) {
      stop();
      while (1) {
        if (LineSensor_L() == white) {
          stop();
          goal();
          escape();
          delay(10000);
          drive();
          break;
        }
        motors(1, 88, 1, 88, 2);
      }
    }
    drive();
  }



  //////////////////
  //  escape();

  //  drive2();
  //  delay(1000);

  //  Serial.println(LineSensor_L());

  //
  //  gotoline();
  //  LineTracing();
  //        Line();
}

void goal() {
  motors(2, 88, 2, 88 - 7, 270);
  //  delay(
  stop();
  delay(199);
  motors(1, 88, 1, 88 - 7, 380);
  stop();

  delay(1000);
  while (1) {
    if (L_distance() < 10) {
      stop();
      break;

    }
    motors(1, 90, 0, 0, 2);
  }
  while (1) {
    if (R_distance() < 10) {
      stop();

      break;
    }
    motors(2, 90, 1, 88, 2);
  }
  while (1) {
    if (R_distance() > 20) {
      stop();
      break;
    }
    motors(2, 90, 1, 88, 2);
  }
  while (1) {
    if (R_distance()  < 10) {
      stop();

      break;
    }
    motors(2, 90, 1, 88, 0);

  }
  motors(2, 90, 1, 88, 150);
  
  stop();
  while (1) {
    if (F_distance() <= 12) {
      stop();
      break;
    }
    motors(1, 85, 0, 0, 2);
  }
  delay(100);
  liftSV.write(72);
  delay(1000);
  motors(0, 0, 1, 88,320);
  stop();
  
  //motors(1, 90, 1, 110, 750);
  motors(1, 95, 1, 106, 350);
  stop();
  motors(1, 95, 0, 0, 350);
  stop();
  motors(0, 0, 1, 110, 360);
  //  motors(1, 90, 1, 110, 750);
  stop();

  stop();


  stop();
  delay(100);





  //  motors(1, 90, 1, 110, 750);
  motors(1, 90, 1, 110, 200);

  stop();
  delay(600);

  gripSV.attach(9);
  gripSV.write(145);
  delay(1000);

  liftSV.write(180);
  delay(1000);
  motors(0, 0, 2, 88, 850);
  stop();
  motors(1, 90, 1, 97, 900);
  stop();
  gripSV.write(0);// put
  delay(1000);

  /////////////////////////////////////////////////////////////////


}


void escape() {
  while (1) {
    if (LineSensor_L() == white || LineSensor_R() == white) {
      stop();
      motors(2, 90, 2, 90, 500);
      stop();
      break;
    }
    motors(2, 90, 2, 90, 2);
  }


  while (1) {
    if (L_distance() < 5.5) {
      stop();
      break;
    }
    motors(2, 88, 1, 88, 2);
  }

  while (1) {
    if (L_distance() > 6) {
      stop();
      break;
    }
    motors(0, 0, 1, 88, 2);
  }
  while (1) {
    if (F_distance() < 10) {
      stop();
      break;
    }
    motors(1, 90, 1, 97, 2);
  }

  while (1) {
    if (F_distance() > 50) {
      stop();
      break;
    }
    motors(1, 90, 2, 97, 2);
  }

  //  while (1) {
  //    if (L_distance() > 15) {
  //      stop();
  //      break;
  //    }
  //    motors(1, 90, 2, 88, 2);
  //  }
  //  while (1) {
  //    if (L_distance() < 16) {
  //      stop();
  //      break;
  //    }
  //    motors(1, 90, 2, 88, 2);
  //  }



}


int cc = 7;
void drive() {
  int wall = 4.5;
  int cnt = 0;


  if (L_distance() < 4.5) { // Detecting Left
    while (1) {
      if (LineSensor_L() == white) {
        stop();
        break;
      }

      if (L_distance() > 4) {
        stop();
        break;
      }
      motors(2, 88 , 0, 0, 2);

    }
  }

  else if (R_distance() < wall) { // Detecting Right
    while (1) {
      if (LineSensor_L() == white) {
        stop();
        break;
      }

      if (R_distance() > 3.8) {
        stop();
        break;
      }
      motors(0, 0, 2, 88, 100);
      stop();

    }
  }

  else if (L_distance() > 28) { // Detecting Left Whole
    stop();
    motors(2, 90, 2, 90, 180);
    stop();
    while (1) {
      if (R_distance() > 14 ) {
        stop();
        break;
      }
      motors(0, 0, 2, 88, 2);
    }
    motors(2, 90, 2, 90, 280);
    stop();
    while (1) {
      if (L_distance() < 6.5 ) { //
        stop();
        break;
      }
      motors(0, 0, 2, 88, 2);
    }
    motors(2, 100, 2, 100, 100);
    stop();
  }

  else if (R_distance() > 28) { // Detecting Right Whole
    stop();
    delay(30);
    motors(2, 90, 2, 90, 250);
    stop();
    delay(30);
    while (1) {
      if (L_distance() > 14) {
        stop();
        break;
      }
      motors(2, 88, 0, 0, 2);
    }
    delay(80);
    motors(2, 90, 2, 90, 250);
    stop();
    while (1) {
      if (R_distance() < 8) {
        stop();
        break;
      }
      motors(2, 88, 0, 0, 2);
    }
    //    cnt++;
    //    if (cnt >= 2) {
    //      cc = 3;
    //    }
    //    stop();
    //    motors(2, 100, 2, 100, 100);
    //    stop();
    //    while (1) {
    //      if (L_distance() > 14 ) { //16
    //        stop();
    //        break;
    //      }
    //      motors(2, 88, 0, 0, 2);
    //    }
    //    motors(2, 90, 2, 90, 170);
    //    stop();
    //    while (1) {
    //      if (R_distance() < cc) {  //R_distance() < 7
    //        stop();
    //        break;
    //      }
    //      motors(2, 88, 0, 0, 2);
    //    }
    //    if (cnt == 2) {
    //      motors(2, 88, 0, 0, 500);
    //      stop();
    //
    //    }
    //    //    motors(2, 100, 2, 100, 100);//350
    //    stop();
  }

  else {
    motors(2, 80, 2, 105, 2);
  }

}

void drive2() {
  if (R_distance() < 40) {
    if (L_distance() < 4) {
      while (1) {
        if (L_distance() > 6.5) {
          stop();
          break;
        }
        motors(2, 90, 0, 0, 2);
      }
      while (1) {
        if (L_distance() < 6.3) {
          stop();
          break;
        }
        motors(0, 0, 2, 90, 2);
      }
    }
    motors(1, 85, 1, 88, 1);
  } else {
    stop();
    while (1) {
      if (L_distance() > 16) {
        stop();
        break;
      }
      motors(1, 88, 2, 85, 2);
    }
    while (1) {
      if (L_distance() < 7) {
        stop();
        break;
      }
      motors(1, 88, 0, 0, 2);
    }
    return;
  }
}



void gotoline() {
  while (1) {
    if (LineSensor_L() == 0) {
      if (LineSensor_R() == 0) {//forward
        motors(1, 83, 1, 83, 0);
      } else {//left
        motors(2, 83, 1, 83, 0);
      }

    } else {
      if (LineSensor_R() == 0) { //right
        motors(1, 83, 2, 83, 0);
      } else {//stop
        stop();
        break;

      }

    }
  }
}

void Line() {
  while (1) {
    if (LineSensor_L() == 0) {
      motors(2, 88, 1, 88, 0);
    }
    else {
      motors(1, 88, 0, 0, 0);
    }
  }


}

void LineTracing() {
  while (1) {
    //    Serial.print(LineSensor_L());
    //    Serial.print("  ");
    //    Serial.println(LineSensor_R());
    if (LineSensor_L() == 0) {
      if (LineSensor_R() == 0) {//stop
        stop();
        while (1) {
          if (LineSensor_L() == 1) {
            stop();
            break;
          }
          motors(2, 83, 1, 83, 0);
        }

        while (1) {
          if (LineSensor_R() == 1) {
            stop();
            break;
          }
          motors(0, 0, 1, 83, 0);
        }
        //        while (1) {
        //          if (LineSensor_R() == 1) {
        //            stop();
        //            break;
        //          }
        //          motors(0, 0, 1, 88, 0);
        //        }
        //
        //        while (1) {
        //          if (LineSensor_R() == 0) {
        //            stop();
        //            break;
        //          }
        //          motors(0, 0, 1, 88, 0);
        //
        //        }
        //        while (1) {
        //          if (LineSensor_L() == 1) {
        //            stop();
        //            break;
        //          }
        //          motors(1, 83, 0, 0, 0);
        //        }
        //        while (1) {
        //          if (LineSensor_L() == 0) {
        //            stop();
        //            break;
        //          }
        //          motors(1, 83, 0, 0, 0);
        //        }
      } else {//left
        motors(2, 78, 1, 78, 0);
      }
      //      motors(0, 0, 1, 90, 2);
    } else {
      if (LineSensor_R() == 0) { //right
        motors(1, 83, 2, 83, 0);
      } else {//forward
        motors(1, 83, 1, 83, 0);
      }

    }
  }
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

bool LineSensor_L() {
  return digitalRead(Line_Sensor_L);
}

bool LineSensor_R() {
  return digitalRead(Line_Sensor_R);
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
    analogWrite(LEFT_SPD, s_l - 3);
  } else if (d_l == 2) {
    digitalWrite(LEFT_A1, LOW);
    digitalWrite(LEFT_B1, HIGH);
    analogWrite(LEFT_SPD, s_l - 3);
  } else {}

  if (d_r == 0) {
    digitalWrite(RIGHT_A2, LOW);
    digitalWrite(RIGHT_B2, LOW);
    analogWrite(RIGHT_SPD, 0);
  } else if (d_r == 1) {
    digitalWrite(RIGHT_A2, HIGH);
    digitalWrite(RIGHT_B2, LOW);
    analogWrite(RIGHT_SPD, s_r + 21 - 3); //45
  } else if (d_r == 2) {
    digitalWrite(RIGHT_A2, LOW);
    digitalWrite(RIGHT_B2, HIGH);
    analogWrite(RIGHT_SPD, s_r + 21 - 3);
  } else {}

  delay(delay_time);
}
