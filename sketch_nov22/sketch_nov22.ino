#include <Stepper.h>

Stepper stepper_x(2048, 8, 10, 9, 11);
Stepper stepper_y(2048, 2, 5, 3, 6);

void setup() {
  // put your setup code here, to run once:
  stepper_x.setSpeed(10);         // set initial speed
  stepper_y.setSpeed(10);         // set initial speed
  stepper_y.step(-34*2);
//  stepper_x.step(34*2);

}

void loop() {
  // put your main code here, to run repeatedly:

}
