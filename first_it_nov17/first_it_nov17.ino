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
int x_angle_size = 3; 
int y_step_size = 18;
int y_angle_size = 3;
int col = 7;
//int row = 6;
int row = 16;
int x = -18; //(-18, 18)
int y = 0; // (0, 30)

int setup_rotation = 12;

void setup() {
  // put your setup code here, to run once:
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
//  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
//  Serial.println("with Arduino UNO R3");
  // Serial.println("x,y,Distance");
}

void loop() {
   buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
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
  // Serial.println(read());
  delay(250);
}


// rotate clockwise = negative rotate counter clockwise = positive  
void scan() {
  x = -1 * setup_rotation;
  y = 0;
  delay(2000);
  stepper_x.step(-1*x_step_size*setup_rotation);
  while (x <= 12){
    while (y <= 15){
      distance = read();
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.print(",");
      Serial.println(distance);
      stepper_y.step(-y_step_size);
      delay(250);
      y++;
    }
    stepper_y.step(y_step_size*(row));
    delay(250);
    y = 0;
    stepper_x.step(x_step_size);
    delay(250);
    x++; 
  }
  stepper_x.step(-1*int(x_step_size*(setup_rotation+1))); //setup_rotation = 3
  Serial.println("end");
  delay(5000);
}
float read() { // store data if needed 
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
      // Displays the distance on the Serial Monitor
      values[i] = distance;
    }
    for(int i = 0; i < 5; i++){
      average += values[i];
    }
    return average/5;

  /*Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");*/
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
