void setup() {
  // put your setup code here, to run once:
  pinMode(6,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(6);
  Serial.println(a);
  delay(10);
}
