#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // Pustaka WiFiManager untuk konfigurasi WiFi

// Inisialisasi Web Server di port 80
ESP8266WebServer server(80);

// Definisikan pin untuk LED
const int ledPin = 2; // GPIO 2 pada ESP8266 (D4 pada NodeMCU)

// Status LED awal
bool ledState = false;

// Fungsi untuk mengendalikan LED on/off melalui URL

void handleLEDControl() {
  String state = server.arg("state");

  if (state == "on") {
    ledState = true;
    digitalWrite(ledPin, HIGH);  // LED nyala
    server.send(200, "text/plain", "LED ON");
  } else if (state == "off") {
    ledState = false;
    digitalWrite(ledPin, LOW); // LED mati
    server.send(200, "text/plain", "LED OFF");
  } else {
    server.send(400, "text/plain", "Parameter 'state' tidak valid! Gunakan 'on' atau 'off'.");
  }
}


// Fungsi untuk halaman web utama
void handleRoot() {
  String html = "<h1>Kontrol LED ESP8266</h1>";
  html += "<p><a href=\"/led?state=on\"><button style='padding:10px; font-size:18px;'>Hidupkan LED</button></a></p>";
  html += "<p><a href=\"/led?state=off\"><button style='padding:10px; font-size:18px;'>Matikan LED</button></a></p>";
  server.send(200, "text/html", html);
}

void setup() {
  // Set pin LED sebagai output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // LED awalnya mati

  // Mulai Serial Monitor untuk debugging
  Serial.begin(115200);

  // Inisialisasi WiFi dengan WiFiManager
  WiFiManager wifiManager;

  // Reset konfigurasi WiFi jika diperlukan
  // wifiManager.resetSettings();

  // Buka portal konfigurasi jika tidak ada jaringan yang disimpan
  if (!wifiManager.autoConnect("ESP8266_LED_Control")) {
    Serial.println("Gagal terhubung ke jaringan, melakukan reset...");
    ESP.reset();
    delay(1000);
  }

  // Jika sudah terhubung, tampilkan alamat IP
  Serial.println("Terhubung ke WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Tentukan URL untuk halaman utama dan kontrol LED
  server.on("/", handleRoot);
  server.on("/led", handleLEDControl);

  // Mulai server web
  server.begin();
  Serial.println("Server web siap!");
}

void loop() {
  // Jalankan server web
  server.handleClient();
}
