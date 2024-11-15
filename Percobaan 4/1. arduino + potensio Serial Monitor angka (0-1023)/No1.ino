int potPin = A0;  // Potensiometer terhubung ke pin analog A0
int ledPin = 9;   // LED terhubung ke pin digital 9 (PWM)
int potValue = 0; // Variabel untuk menyimpan nilai dari potensiometer
int ledBrightness = 0; // Variabel untuk menyimpan nilai PWM (0-255)

void setup() {
  // Tidak perlu inisialisasi untuk LED karena kita menggunakan pin PWM
}

void loop() {
  // Baca nilai analog dari potensiometer (0 hingga 1023)
  potValue = analogRead(potPin);
  
  // Konversi nilai potensiometer (0-1023) ke rentang PWM (0-255)
  ledBrightness = map(potValue, 0, 1023, 0, 255);
  
  // Atur kecerahan LED menggunakan PWM
  analogWrite(ledPin, ledBrightness);
  
  // Tambahkan sedikit jeda untuk stabilitas
  delay(10);
}
