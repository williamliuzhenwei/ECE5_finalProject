const int trigPin = 3;
const int echoPin = 2;
const int IRProx = 4;
const int buzzer = 5;
const int button = 6;
const int ledPins[10] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

const int maxD = 180;
bool buttonState = false;
bool piezoState = false;
bool isOn = false;
long duration;
int distance;
double timer1;
double timer2;
// Turn off every LED
void ledoff(){
  for (int i = 0; i < 9; i ++){
    digitalWrite(ledPins[i], LOW);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IRProx, INPUT);
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);

  // Initialize all LEDs
  for (int i = 0; i < 10; i++){
    pinMode(ledPins[i], OUTPUT);
  }

  //Visually check all Leds working properly
  digitalWrite(ledPins[0], HIGH);
  for (int i = 0; i < 9; i++){
    delay(50);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[i+1],HIGH);
  }
  delay(50);
  digitalWrite(ledPins[10], LOW);
  
}

void loop() {
  selfStart();
  buttonState = digitalRead(button);
  if (buttonState == HIGH && isOn == false){
    isOn = true;
    timer1 = millis();
  } else if (buttonState == HIGH && isOn == true){
    isOn = false;
  }

  if (isOn == true){
    indicatorsOn();
  }

  if (isOn == false){
    indicatorsOff();
  }

  timer2 = millis();
  Serial.println(timer2 - timer1); //Time Elapsed since not detected

  // System turned off after 10s not detecting anything within 80cm
  if (timer2 - timer1 >= 10000){
    indicatorsOff();
    isOn = false;
  }
  delay(100);
}

// Start the system itself when detect things within 10 cm
void selfStart() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  
  bool appr = digitalRead(IRProx);
  if (distance < 10 && appr == LOW){
    isOn = true;
    timer1 = millis();
    indicatorsOn();
  }
}

void indicatorsOn() {
  digitalWrite(ledPins[9],HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;

  bool appr = digitalRead(IRProx);   // HIGH = Not Detected
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Indicators of Distance
  if (distance == 0 || distance >= 80) {
    ledoff();
    noTone(buzzer);
    digitalWrite(ledPins[0], HIGH);
  } else if (distance < 80 && distance > 60) {
    timer1 = millis();
    ledoff();
    noTone(buzzer);
    digitalWrite(ledPins[1], HIGH);
  } else if (distance < 60 && distance > 45) {
    timer1 = millis();
    ledoff();
    noTone(buzzer);
    digitalWrite(ledPins[2], HIGH);
  } else if (distance < 40 && distance > 25) {
    timer1 = millis();
    ledoff();
    noTone(buzzer);
    digitalWrite(ledPins[3], HIGH);
  } else if (distance < 25 && distance > 15) {
    timer1 = millis();
    ledoff();
    noTone(buzzer);
    digitalWrite(ledPins[4], HIGH);
  } else if (distance < 15 && distance > 10) {
    timer1 = millis();
    ledoff();
    noTone(buzzer);
    digitalWrite(ledPins[5], HIGH);
  } else if (distance < 10 && distance > 7) {
    timer1 = millis();
    ledoff();
    tone(buzzer,4000);
    digitalWrite(ledPins[6], HIGH);
  } else if (distance < 7 && distance > 3) {
    timer1 = millis();
    ledoff();
    tone(buzzer,5000);
    digitalWrite(ledPins[7], HIGH);
  } else if (distance < 3 && distance > 0) {
    timer1 = millis();
    ledoff();
    tone(buzzer,8000);
    digitalWrite(ledPins[8], HIGH);
  } 
}

void indicatorsOff(){
  digitalWrite(ledPins[9],LOW);
  ledoff();
  noTone(buzzer);
}
