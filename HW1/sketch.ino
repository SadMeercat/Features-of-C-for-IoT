const int redLed = 8;
const int yellowLed = 7;
const int greenLed = 6;
const int buttonPin = 2;

int buttonState = 0;
unsigned long lastButtonPress = 0;
unsigned long pedestrianWaitTime = 5000; // Время ожидания для пешеходов (5 секунд)
unsigned long greenBlinkInterval = 1000; // Интервал мигания зеленого светодиода (1 секунда)
unsigned long redLightTime = 10000; // Время горения красного светодиода для пешеходов (10 секунд)

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW && (millis() - lastButtonPress) > pedestrianWaitTime) {
    lastButtonPress = millis();
    pedestrianCycle();
  }

  trafficCycle();
  
  if (Serial.available() > 0) {
    int command = Serial.parseInt();
    if (command == 1) {
      digitalWrite(greenLed, HIGH);
    } else if (command == 0) {
      digitalWrite(greenLed, LOW);
    }
  }
}

void trafficCycle() {
  // Зеленый сигнал
  digitalWrite(greenLed, HIGH);
  delay(5000);
  
  // Зеленый мигающий сигнал
  for (int i = 0; i < 3; i++) {
    digitalWrite(greenLed, LOW);
    delay(greenBlinkInterval / 2);
    digitalWrite(greenLed, HIGH);
    delay(greenBlinkInterval / 2);
  }
  digitalWrite(greenLed, LOW);
  
  // Желтый сигнал
  digitalWrite(yellowLed, HIGH);
  delay(3000);
  digitalWrite(yellowLed, LOW);
  
  // Красный сигнал
  digitalWrite(redLed, HIGH);
  delay(5000);
  digitalWrite(redLed, LOW);
}

void pedestrianCycle() {
  // Мигающий желтый сигнал
  for (int i = 0; i < 3; i++) {
    digitalWrite(yellowLed, HIGH);
    delay(500);
    digitalWrite(yellowLed, LOW);
    delay(500);
  }
  
  // Красный сигнал для машин и зеленый для пешеходов
  digitalWrite(redLed, HIGH);
  delay(redLightTime);
  digitalWrite(redLed, LOW);
}