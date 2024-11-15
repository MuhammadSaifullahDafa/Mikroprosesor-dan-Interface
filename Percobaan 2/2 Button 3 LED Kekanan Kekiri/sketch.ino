// Pin definisi
const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int button1Pin = 2;
const int button2Pin = 3;

int button1State = 0;
int button2State = 0;

void setup() {
  // Atur pin LED sebagai output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Atur pin push button sebagai input
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
}

void loop() {
  // Baca status push button
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  // Jika tombol 1 ditekan, LED blink ke kanan
  if (button1State == HIGH) {
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);

    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);

    digitalWrite(led3, HIGH);
    delay(500);
    digitalWrite(led3, LOW);
  } 
  // Jika tombol 2 ditekan, LED blink ke kiri
  else if (button2State == HIGH) {
    digitalWrite(led3, HIGH);
    delay(500);
    digitalWrite(led3, LOW);

    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);

    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
  }
  // Jika tidak ada tombol ditekan, matikan semua LED
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
}
