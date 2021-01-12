/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo gripSV;  // create servo object to control a servo
Servo liftSV;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  gripSV.attach(9);  
  liftSV.attach(10);
  liftSV.write(180);//up
}

void loop() {
  liftSV.write(180);//up
  delay(1000);
  gripSV.write(0);// put
  delay(2500);
  liftSV.write(72); //down
  delay(1000);
  gripSV.write(145);// catch
  delay(2500);
}
