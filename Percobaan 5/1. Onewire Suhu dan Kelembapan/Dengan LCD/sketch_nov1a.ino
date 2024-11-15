#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2         // Pin data sensor DHT22 dihubungkan ke D2
#define DHTTYPE DHT22    // Jenis sensor DHT22
#define LED_PIN 8        // LED dihubungkan ke pin D8

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD dengan 16 kolom dan 2 baris

void setup() {
  pinMode(LED_PIN, OUTPUT); // Mengatur pin LED sebagai output
  lcd.begin(16, 2);  
  lcd.init();       // Inisialisasi LCD dengan 16 kolom dan 2 baris
  lcd.backlight();          // Menghidupkan backlight LCD
  dht.begin();              // Memulai sensor DHT
}

void loop() {
  // Membaca suhu dan kelembapan dari sensor DHT22
  float Kelembapan = dht.readHumidity();
  float Suhu = dht.readTemperature();
  
  // Cek apakah pembacaan gagal
  if (isnan(Kelembapan) || isnan(Suhu)) {
    lcd.setCursor(0, 0);
    lcd.print("Error Reading");
    return;
  }

  // Tampilkan suhu dan kelembapan di LCD
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(Suhu);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Kelembapan: ");
  lcd.print(Kelembapan);
  lcd.print("%");

  // Nyalakan LED jika suhu lebih dari 30°C
  if (Suhu > 33.5) {
    digitalWrite(LED_PIN, HIGH); // Nyalakan LED
  } else {
    digitalWrite(LED_PIN, LOW);  // Matikan LED
  }

  delay(1000); // Tunggu 2 detik sebelum pembacaan berikutnya
}