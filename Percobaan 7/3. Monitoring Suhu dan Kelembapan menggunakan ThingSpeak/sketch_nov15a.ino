#include <ESP8266WiFi.h>
#include <DHT.h>

// Konfigurasi DHT22
#define DHTPIN D4  // Pin data DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Koneksi Wi-Fi
const char* ssid = "PP";  // Ganti dengan SSID Wi-Fi Anda
const char* password = "asu12345";  // Ganti dengan password Wi-Fi Anda

// Konfigurasi ThingSpeak
const char* server = "api.thingspeak.com";
String apiKey = "TRGRS23J0CWOSBH3";  // Ganti dengan API Key ThingSpeak Anda

// Pin untuk potensiometer
#define POT_PIN A0

void setup() {
  Serial.begin(115200);
  delay(10);

  // Memulai sensor DHT22
  dht.begin();

  // Menghubungkan ke Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi terhubung!");
}

void loop() {
  // Membaca suhu dan kelembaban dari DHT22
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();

  // Membaca nilai potensiometer
  int nilaiPot = analogRead(POT_PIN);
  float teganganPot = (nilaiPot / 1023.0) * 3.3;  // Mengonversi ke voltase

  // Mengecek apakah pembacaan sensor DHT berhasil
  if (isnan(suhu) || isnan(kelembaban)) {
    Serial.println("Gagal membaca sensor DHT!");
    return;
  }

  // Membuat URL untuk request HTTP ke ThingSpeak
  String url = "/update?api_key=" + apiKey + "&field1=" + String(suhu) + "&field2=" + String(kelembaban) + "&field3=" + String(teganganPot);

  // Mengirim data ke ThingSpeak
  WiFiClient client;
  if (client.connect(server, 80)) {
    Serial.println("Mengirim data ke ThingSpeak...");

    client.print("GET " + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Connection: close\r\n\r\n");

    // Menunggu respon dari server
    while (client.connected() || client.available()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }

    client.stop();
    Serial.println("Data terkirim!\n");
  } else {
    Serial.println("Koneksi ke ThingSpeak gagal.");
  }

  delay(20000);  // Kirim data setiap 20 detik
}
