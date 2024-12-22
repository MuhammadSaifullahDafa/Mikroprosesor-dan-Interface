#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

// Ganti dengan SSID dan password Wi-Fi Anda
const char* ssid = "PP";       
const char* password = "asu12345"; 

// Pin untuk mengontrol LED
const int ledPin = D4;  // GPIO2 pada NodeMCU atau pin PWM lainnya

// Membuat server web dan WebSocket
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);  // Port WebSocket adalah 81

void setup() {
  Serial.begin(115200);   // Untuk debugging di Serial Monitor
  pinMode(ledPin, OUTPUT); // Set pin LED sebagai output
  analogWrite(ledPin, 0);  // Memulai LED dalam keadaan mati (kecerahan 0)

  // Menghubungkan ke Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Menampilkan IP di Serial Monitor setelah berhasil terhubung ke Wi-Fi
  Serial.println();
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // Tampilkan alamat IP ESP8266

  // Mengatur rute untuk server web (halaman HTML)
  server.on("/", HTTP_GET, []() {
    String html = "<html><body><h1>Kontrol Kecerahan LED</h1>";
    html += "<input type='range' min='0' max='1023' value='0' id='brightness' style='width:100%' />";
    html += "<p>Kecerahan: <span id='level'>0</span></p>";
    html += "<script>";
    html += "var socket = new WebSocket('ws://' + window.location.hostname + ':81/');";
    html += "socket.onopen = function() { console.log('WebSocket connected'); };";
    html += "document.getElementById('brightness').oninput = function() {";
    html += "  document.getElementById('level').innerText = this.value;";
    html += "  socket.send(this.value);";
    html += "};";
    html += "</script>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  // Memulai WebSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  // Memulai server HTTP
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Menangani permintaan dari server web
  server.handleClient();
  // Menangani komunikasi WebSocket
  webSocket.loop();
}

// Fungsi untuk menangani event WebSocket
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  int pwmValue = 0;  // Deklarasi variabel di luar switch

  switch (type) {
    case WStype_TEXT:
      // Mengubah nilai PWM LED berdasarkan nilai dari slider
      pwmValue = atoi((char*)payload);  // Mendapatkan nilai dari WebSocket payload
      analogWrite(ledPin, pwmValue);  // Mengatur kecerahan LED sesuai dengan nilai PWM
      Serial.println("PWM Value: " + String(pwmValue));  // Menampilkan nilai PWM di Serial Monitor
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket Connected");
      break;
    case WStype_DISCONNECTED:
      Serial.println("WebSocket Disconnected");
      break;
    default:
      break;
  }
}
