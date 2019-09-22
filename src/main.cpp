#include <Arduino.h>
#include "motor.hh"

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  static L298N motor1(13, 22, 24);
  static L298N motor2(12, 26, 28);

  motor1.update(motor::dir::CW, 255);
  motor1.setDuration(1000);
  motor1.output();


}