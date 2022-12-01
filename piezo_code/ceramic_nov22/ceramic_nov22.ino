#define buzzer 10 //connecting buzzer to pin 10
#define echoPin A0 
#define trigPin A1

bool BUZZER_STATE = false;
long duration;
int distance;
int p = 50; // pwm value, 50% duty cycle

void setup()
{ 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(buzzer, OUTPUT);  //setting up buzzer pin as output
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed

  TCCR1A = 0;
  TCCR2B = 0;
  TCCR2B |= B00000100; // prescaler = 256
                       // 1/(16 MHz/256)*10 = 0.16 ms = 160 us
  TIMSK2 |= B00000100; // enable compare match B

//  TCCR2B |= B00000100; // prescaler = 64
//                       // 1/(16 MHz/64)*14 = 56 us
//  TIMSK2 |= B00000100;
  sei();
}

void loop()
{
  OCR2B = 10; // 6kHz
  // OCR2B = 14; // 18 kHz
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.print(distance);
  Serial.println(" cm");
  delay(250);
  
}

ISR(TIMER2_COMPB_vect) {
  BUZZER_STATE = !BUZZER_STATE;
  digitalWrite(buzzer, BUZZER_STATE);
}
