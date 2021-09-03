const int trigPin = 3;
const int echoPin = 2;
const int buzzer = 5;
const int ledPins[10] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

const int maxD = 180;
bool piezoState = false;
bool isOn = false;
long duration;
int distance;

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
  indicatorsOn();
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

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Indicators of Distance (Piezo Sound and LED lights up)
   if (distance == 0 || distance >= 80) {
    noTone(buzzer);
    ledOnTo(1);
  } else if (distance < 80 && distance >= 60) {
    tone(buzzer, 1600);
    ledOnTo(2);
  } else if (distance < 60 && distance >= 45) {
    tone(buzzer, 1800);
    ledOnTo(3);
  } else if (distance < 40 && distance >= 25) {
    tone(buzzer, 2000);
    ledOnTo(4);
  } else if (distance < 25 && distance >= 15) {
    tone(buzzer, 2200);
    ledOnTo(5);
  } else if (distance < 15 && distance >= 10) {
    tone(buzzer, 2400);
    ledOnTo(6);   
  } else if (distance < 10 && distance >= 7) {
    tone(buzzer, 2600);
    ledOnTo(7);
  } else if (distance < 7 && distance >= 3) {
    tone(buzzer, 2800);
    ledOnTo(8);
  } else if (distance < 3 && distance >= 0) {
    tone(buzzer, 3000);
    ledOnTo(9);
  } 
}
