#include <DHT.h>

// Konfigurasi DHT11
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Pin LED
int ledPin = 13;

void setup() {
  // Inisialisasi serial monitor
  Serial.begin(9600);

  // Inisialisasi DHT11
  dht.begin();

  // Inisialisasi LED sebagai output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Membaca suhu dari DHT11
  float suhu = dht.readTemperature();

  // Cek apakah pembacaan berhasil
  if (isnan(suhu)) {
    Serial.println("Gagal membaca dari DHT11");
    return;
  }

  // Tampilkan suhu di Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" C");

  // Cek apakah suhu >= 30 derajat, nyalakan LED jika ya
  if (suhu >= 30) {
    digitalWrite(ledPin, HIGH); // Nyalakan LED
  } else {
    digitalWrite(ledPin, LOW); // Matikan LED
  }

  // Tunggu 2 detik sebelum pembacaan berikutnya
  delay(2000);
}
