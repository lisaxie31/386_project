#include <Stepper.h>

Stepper stepper_x(2048, 8, 10, 9, 11);
Stepper stepper_y(2048, 2, 5, 3, 6);

void setup() {
  // put your setup code here, to run once:
  stepper_x.setSpeed(10);         // set initial speed
  stepper_y.setSpeed(10);         // set initial speed
  stepper_y.step(34*2);
//  stepper_x.step(34*2);

}

void loop() {
  // digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  // // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  // digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin, LOW);
  // // Reads the echoPin, returns the sound wave travel time in microseconds
  // duration = pulseIn(echoPin, HIGH);
  // // Calculating the distance
  // distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // // Displays the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println(" cm");
  // delay(1000);
}
