const int trigPin = 3;
const int echoPin = 2;
const int IRProx = 4;
const int buzzer = 5;
const int button = 6;
const int ledPins[10] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

unsigned long ii = 0;
unsigned long millinum;
const int maxD = 180;
bool buttonState = false;
bool piezoState = false;
bool isOn = false;
long duration;
int distance = 0;
double timer1;
double timer2;
// Turn on LEDS to the specified number; turn the rest off
void ledOnTo(byte num){
  for (int i = 0; i < num; i++){
    digitalWrite(ledPins[i], HIGH);
  }
  for (int i = num; i < 9; i++){
    digitalWrite(ledPins[i], LOW);
  }
}
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
  isOn = true;
  indicatorsOn();
}

void loop() {
  selfStart();
  
  millinum = millis();

  if ((millinum) > 100*ii) {
    millinum = millis();
    Serial.print(millinum);
    Serial.print(' ');
    Serial.println(distance);
    ii = ii + 1;
  } 
  
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
  distance = duration*0.034/2;
  
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
  
  // Indicators of Distance
   if (distance == 0 || distance >= 80) {
    noTone(buzzer);
    ledOnTo(1);
  } else if (distance < 80 && distance >= 60) {
    timer1 = millis();
    tone(buzzer, 1600);
    ledOnTo(2);
  } else if (distance < 60 && distance >= 45) {
    timer1 = millis();
    tone(buzzer, 1800);
    ledOnTo(3);
  } else if (distance < 40 && distance >= 25) {
    timer1 = millis();
    tone(buzzer, 2000);
    ledOnTo(4);
  } else if (distance < 25 && distance >= 15) {
    timer1 = millis();
    tone(buzzer, 2200);
    ledOnTo(5);
  } else if (distance < 15 && distance >= 10) {
    timer1 = millis();
    tone(buzzer, 2400);
    ledOnTo(6);   
  } else if (distance < 10 && distance >= 7) {
    timer1 = millis();
    tone(buzzer, 2600);
    ledOnTo(7);
  } else if (distance < 7 && distance >= 3) {
    timer1 = millis();
    tone(buzzer, 2800);
    ledOnTo(8);
  } else if (distance < 3 && distance >= 0) {
    timer1 = millis();
    tone(buzzer, 3000);
    ledOnTo(9);
  } 
}


void indicatorsOff(){
  digitalWrite(ledPins[9],LOW);
  ledoff();
  noTone(buzzer);
}

