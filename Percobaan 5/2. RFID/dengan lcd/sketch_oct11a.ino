#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin konfigurasi RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Pin LED
#define LED_PIN 8

// Inisialisasi LCD I2C (alamat I2C biasanya 0x27 atau 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// UID Tag RFID yang diizinkan
byte allowedUID[7] = {0x04, 0x44, 0x18, 0xBA, 0x19, 0x6D, 0x80};  // Ganti dengan UID yang diperbolehkan
// UID Tag RFID yang ditolak
byte deniedUID[4] = {0x23, 0xB8, 0xAE, 0xFE};   // Ganti dengan UID yang ditolak

void setup() {
  // Inisialisasi Serial
  Serial.begin(9600);

  // Inisialisasi RFID
  SPI.begin();
  mfrc522.PCD_Init();

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan RFID");

  // Inisialisasi LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Periksa apakah ada kartu yang tersedia
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Periksa apakah kartu bisa dibaca
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Membaca UID dari tag RFID
  byte readUID[4];
  for (byte i = 0; i < 4; i++) {
    readUID[i] = mfrc522.uid.uidByte[i];
  }

  // Periksa apakah UID yang terbaca termasuk UID yang diizinkan
  if (compareUID(readUID, allowedUID)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access: ALLOW");
    digitalWrite(LED_PIN, HIGH); // LED menyala terus
    delay(3000);                 // Tunggu 3 detik
    digitalWrite(LED_PIN, LOW);
  } 
  // Periksa apakah UID yang terbaca termasuk UID yang ditolak
  else if (compareUID(readUID, deniedUID)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access: DENY");
    for (int i = 0; i < 6; i++) { // Blink selama 3 detik
      digitalWrite(LED_PIN, HIGH);
      delay(250);
      digitalWrite(LED_PIN, LOW);
      delay(250);
    }
  }
  // Jika UID tidak dikenal
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access: UNKNOWN");
    digitalWrite(LED_PIN, LOW); // LED tetap mati
  }

  // Hentikan komunikasi dengan kartu
  mfrc522.PICC_HaltA();
}

// Fungsi untuk membandingkan UID yang terbaca dengan daftar UID
boolean compareUID(byte *readUID, byte *listUID) {
  for (byte i = 0; i < 4; i++) {
    if (readUID[i] != listUID[i]) {
      return false;
    }
  }
  return true;
}
