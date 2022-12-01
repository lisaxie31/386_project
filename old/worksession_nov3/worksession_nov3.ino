#include <Stepper.h>
#define STEP_PER_REVOLUTION 2048
#define STEP_PER_ROTATION 34

#define echoPin 12 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 13 //attach pin D3 Arduino to pin Trig of HC-SR04

Stepper stepper_x(STEP_PER_REVOLUTION, 8, 10, 9, 11);

Stepper stepper_y(STEP_PER_REVOLUTION, 2, 5, 3, 6);

long duration; // variable for the duration of sound wave travel
float distance; // variable for the distance measurement

int step_size = 34;
int angle_size = 6; 
int col = 7;
int row = 6;
int x = -18; //(-18, 18)
int y = 0; // (0, 30)

int setup_rotation = step_size;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  stepper_x.setSpeed(10);         // set initial speed
  stepper_y.setSpeed(10);         // set initial speed

 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
//  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
//  Serial.println("with Arduino UNO R3");
  Serial.println("x,y,Distance");
  setup_rotation = col/2;
}

void loop() {
  stepper_x.step(-1*step_size*setup_rotation);
  while (x <= 18){
    while (y <= 30){
      distance = read();
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.print(",");
      Serial.println(distance);
      stepper_y.step(step_size);
      delay(1000);
      y = y + angle_size;
    }
    stepper_y.step(-1*step_size*(row-1));
    delay(1000);
    y = 0;
    stepper_x.step(step_size);
    delay(1000);
    x = x + angle_size; 
    
  }
  stepper_x.step(-1*step_size*setup_rotation);
  delay(1000);
  stepper_y.step(-1*step_size*row);
  delay(5000);

  /* starting position 0 
   *  - rotate 18 degrees CW
   *  - y scan up 30 degrees, return to 0
   *  - x rotates 6 degrees CCW x 6
   *  reset to the middle position 18 degrees CW
   */

}

float read() { // store data if needed 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  return distance;
  /*Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");*/
}
