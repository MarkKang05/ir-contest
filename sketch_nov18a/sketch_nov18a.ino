void setup() {

  pinMode(7, OUTPUT);       // Motor A 방향설정1

  pinMode(8, OUTPUT);       // Motor A 방향설정2

  pinMode(4, OUTPUT);       // Motor B 방향설정1

  pinMode(5, OUTPUT);       // Motor B 방향설정2

}


void loop() {

  /*모터A설정*/

  digitalWrite(7, HIGH);     // Motor A 방향설정1

  digitalWrite(8, LOW);      // Motor A 방향설정2

  analogWrite(9, 100);       // Motor A 속도조절 (0~255)

  /*모터B설정*/

  digitalWrite(4, LOW);      // Motor B 방향설정1

  digitalWrite(5, HIGH);     // Motor B 방향설정2

  analogWrite(3, 100);        // Motor B 속도조절 (0~255)

  delay(3000);                   // 3초 유지


  /*모터A설정*/

  digitalWrite(7, LOW);      // Motor A 방향설정1

  digitalWrite(8, HIGH);     // Motor A 방향설정2

  analogWrite(9, 100);      // Motor A 속도조절 (0~255)

  /*모터B설정*/

  digitalWrite(4, HIGH);    // Motor B 방향설정1

  digitalWrite(5, LOW);     // Motor B 방향설정2

  analogWrite(3, 100);      // Motor B 속도조절 (0~255)

  delay(3000);                    // 3초 유지

}
