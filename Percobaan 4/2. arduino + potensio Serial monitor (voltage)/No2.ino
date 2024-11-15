// Definisikan pin potensiometer
int potPin = A0;  // Menggunakan pin analog A0
int potValue = 0;  // Variabel untuk menyimpan nilai potensiometer

void setup() {
  // Inisialisasi Serial Monitor dengan baud rate 9600
  Serial.begin(9600);
}

void loop() {
  // Baca nilai analog dari potensiometer
  potValue = analogRead(potPin);
  
  // Tampilkan nilai di Serial Monitor
  Serial.println(potValue);
  
  // Tambahkan sedikit jeda
  delay(100);
}
