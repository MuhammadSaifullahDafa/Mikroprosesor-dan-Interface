#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10     // Pin SDA dihubungkan ke pin D10 Arduino
#define RST_PIN 9     // Pin RST dihubungkan ke pin D9 Arduino

MFRC522 rfid(SS_PIN, RST_PIN); // Inisialisasi instance dari MFRC522

// UID untuk tag deny dan allow (harus 4 byte untuk array ini)
byte denyUID[4] = {0xB3, 0x61, 0x23, 0x28}; // Ubah dengan UID kartu deny
byte allowUID[7] = {0x04, 0x44, 0x18, 0xBA, 0x19, 0x6D, 0x80}; // Ubah dengan UID KTP allow

void setup() {
  Serial.begin(9600);  // Inisialisasi komunikasi serial
  SPI.begin();         // Mulai komunikasi SPI
  rfid.PCD_Init();     // Inisialisasi modul RFID
  Serial.println("Scan a card...");
}

void loop() {
  // Cek apakah ada kartu baru yang didekatkan ke reader RFID
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Cek apakah bisa membaca kartu
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Tampilkan UID kartu
  Serial.print("UID Kartu: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Variabel untuk status
  String status;
  
  // Bandingkan UID dengan deny dan allow
  if (compareUID(rfid.uid.uidByte, denyUID)) {
    status = "DENY";
    Serial.println("Status: DENY");
  } 
  else if (compareUID(rfid.uid.uidByte, allowUID)) {
    status = "ALLOW";
    Serial.println("Status: ALLOW");
  } 
  else {
    status = "UNKNOWN";
    Serial.println("Status: UNKNOWN");
  }

  // Hentikan komunikasi dengan kartu
  rfid.PICC_HaltA();
}

// Fungsi untuk membandingkan UID
bool compareUID(byte* uid1, byte* uid2) {
  for (byte i = 0; i < 4; i++) { // Sesuaikan dengan panjang UID kartu
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}
