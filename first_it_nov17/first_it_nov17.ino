#include <Stepper.h>
#define STEP_PER_REVOLUTION 2048
#define STEP_PER_ROTATION 34

#define echoPin 12 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 13 //attach pin D3 Arduino to pin Trig of HC-SR04

Stepper stepper_x(STEP_PER_REVOLUTION, 8, 10, 9, 11);

Stepper stepper_y(STEP_PER_REVOLUTION, 2, 5, 3, 6);

const int buttonPin = 7;
int buttonState = 0;

long duration; // variable for the duration of sound wave travel
float distance; // variable for the distance measurement

int step_size = 34; // 6 degrees 
int angle_size = 6; 
int y_step_size = 18;
int y_angle_size = 3;
int col = 7;
//int row = 6;
int row = 12;
int x = -18; //(-18, 18)
int y = 0; // (0, 30)

int setup_rotation = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  stepper_x.setSpeed(10);         // set initial speed
  stepper_y.setSpeed(10);         // set initial speed

  pinMode(buttonPin, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
//  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
//  Serial.println("with Arduino UNO R3");
  Serial.println("x,y,Distance");
  setup_rotation = col/2;
}

void loop() {
   buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    scan();
  }

  delay(100);
}


// rotate clockwise = negative rotate counter clockwise = positive  
void scan() {
  x = -18;
  y = 0;
  delay(2000);
  stepper_x.step(-1*step_size*setup_rotation);
  while (x <= 18){
    while (y <= 30){
      distance = read();
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.print(",");
      Serial.println(distance);
      stepper_y.step(-y_step_size);
      delay(250);
      y = y + y_angle_size;
    }
    stepper_y.step(y_step_size*(row-1));
    delay(250);
    y = 0;
    stepper_x.step(step_size);
    delay(1000);
    x = x + angle_size; 
  }
  stepper_x.step(-1*int(step_size*(setup_rotation+1))); //setup_rotation = 3
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
