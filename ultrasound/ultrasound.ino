#include <Stepper.h>
#define STEP_PER_REVOLUTION 2048
#define STEP_PER_ROTATION 34

#define echoPin 12 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 13 //attach pin D3 Arduino to pin Trig of HC-SR04

#define buttonPin 7
#define xNegButton A0
#define xPosButton A1
#define yNegButton A2
#define yPosButton A3

Stepper stepper_x(STEP_PER_REVOLUTION, 8, 10, 9, 11);
Stepper stepper_y(STEP_PER_REVOLUTION, 2, 5, 3, 6);

int buttonState = 0;
int xState = 0;
int yState = 0;

long duration; // variable for the duration of sound wave travel
float distance; // variable for the distance measurement

int x_step_size = 18; // 3 degrees 
int y_step_size = 18; // 3 degrees 
int x_range = 12; 
int y_range = 15;

int setup_rotation = 12;
int x = -1 * setup_rotation; //(-12, 12)
int y = 0; // (0, 15)


void setup() {
  Serial.begin(9600);

  stepper_x.setSpeed(10);         // set initial speed
  stepper_y.setSpeed(10);         // set initial speed

  pinMode(buttonPin, INPUT);
  pinMode(xNegButton, INPUT);
  pinMode(xPosButton, INPUT);
  pinMode(yNegButton, INPUT);
  pinMode(yPosButton, INPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    scan();
  }
  if (digitalRead(xPosButton) == HIGH) {
    moveXPos();
  }
  if (digitalRead(xNegButton) == HIGH) {
    moveXNeg();
  }
  if (digitalRead(yPosButton) == HIGH) {
    moveYPos();
  }
  if (digitalRead(yNegButton) == HIGH) {
    moveYNeg();
  }

  delay(250);
}


// rotate clockwise = negative rotate counter clockwise = positive  
void scan() {
  x = -1 * setup_rotation;
  y = 0;
  delay(2000);
  stepper_x.step(-1 * x_step_size * setup_rotation);
  while (x <= x_range){
    while (y <= y_range){
      distance = read();
      
      // print x, y angles and distance
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.print(",");
      Serial.println(distance);

      // increment y
      stepper_y.step(-y_step_size);
      delay(250);
      y++;
    }
    // reset y to 0
    stepper_y.step(y_step_size*(y_range + 1));
    delay(250);
    y = 0;

    // increment x 
    stepper_x.step(x_step_size);
    delay(250);
    x++; 
  }
  // reset x motor to 0
  stepper_x.step(-1*int(x_step_size*(setup_rotation+1))); 
  Serial.println("end");
  delay(5000);
}

float read() { 
  float average = 0.0;
  float values[5] = {0.0,0.0,0.0,0.0,0.0};  
  for(int i = 0; i < 5; i++){
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
      values[i] = distance;
    }

    //returns average of 5 distance readings
    for(int i = 0; i < 5; i++){
      average += values[i];
    }
    return average/5;
}

void moveXPos(){
  stepper_x.step(x_step_size);
  delay(500);
}
void moveXNeg(){
  stepper_x.step(-x_step_size);
  delay(500);
}
void moveYPos(){
  stepper_y.step(-y_step_size);
  delay(500);
}
void moveYNeg(){
  stepper_y.step(y_step_size);
  delay(500);
}
