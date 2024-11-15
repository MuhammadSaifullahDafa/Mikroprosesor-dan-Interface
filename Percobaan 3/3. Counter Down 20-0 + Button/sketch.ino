// Definisikan pin untuk Seven Segment Puluhan
int a1 = 2;
int b1 = 3;
int c1 = 4;
int d1 = 5;
int e1 = 6;
int f1 = 7;
int g1 = 8;

// Definisikan pin untuk Seven Segment Satuan
int a2 = 9;
int b2 = 10;
int c2 = 11;
int d2 = 12;
int e2 = 13;
int f2 = A0;
int g2 = A1;

// Definisikan pin untuk push button
int buttonPin = A2;
int buttonState = 0;
int lastButtonState = HIGH;  // Untuk mendeteksi perubahan status tombol
bool countdownStarted = false;  // Flag untuk mengetahui apakah hitung mundur sudah dimulai
bool isPaused = false;  // Flag untuk mengecek apakah dalam kondisi pause
int countdown = 20;  // Mulai dari 20

// Daftar angka 0-9 dalam bentuk biner untuk seven segment
byte angka[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

// Fungsi menampilkan angka di Seven Segment Puluhan
void tampilkanPuluhan(byte angka) {
  digitalWrite(a1, bitRead(angka, 0));
  digitalWrite(b1, bitRead(angka, 1));
  digitalWrite(c1, bitRead(angka, 2));
  digitalWrite(d1, bitRead(angka, 3));
  digitalWrite(e1, bitRead(angka, 4));
  digitalWrite(f1, bitRead(angka, 5));
  digitalWrite(g1, bitRead(angka, 6));
}

// Fungsi menampilkan angka di Seven Segment Satuan
void tampilkanSatuan(byte angka) {
  digitalWrite(a2, bitRead(angka, 0));
  digitalWrite(b2, bitRead(angka, 1));
  digitalWrite(c2, bitRead(angka, 2));
  digitalWrite(d2, bitRead(angka, 3));
  digitalWrite(e2, bitRead(angka, 4));
  digitalWrite(f2, bitRead(angka, 5));
  digitalWrite(g2, bitRead(angka, 6));
}

void setup() {
  // Set pin output untuk Seven Segment Puluhan
  pinMode(a1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(f1, OUTPUT);
  pinMode(g1, OUTPUT);

  // Set pin output untuk Seven Segment Satuan
  pinMode(a2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(g2, OUTPUT);

  // Set pin input untuk tombol
  pinMode(buttonPin, INPUT_PULLUP); // Menggunakan internal pull-up resistor
}

void loop() {
  // Baca status tombol
  buttonState = digitalRead(buttonPin);

  // Cek apakah tombol ditekan (logika LOW karena internal pull-up)
  if (buttonState == LOW && lastButtonState == HIGH) {
    if (!countdownStarted) {
      countdownStarted = true;  // Mulai hitung mundur
    } else if (isPaused) {
      // Jika dalam kondisi pause, lanjutkan countdown
      isPaused = false;  // Lanjutkan hitungan dari tempat terakhir (bisa 0 atau angka lain)
    }
  }

  lastButtonState = buttonState;  // Simpan status tombol sebelumnya

  // Jika hitung mundur dimulai dan belum mencapai 0
  if (countdownStarted && !isPaused) {
    int puluhan = countdown / 10; // Hitung digit puluhan
    int satuan = countdown % 10;  // Hitung digit satuan
    
    // Tampilkan digit puluhan dan satuan
    tampilkanPuluhan(angka[puluhan]);
    tampilkanSatuan(angka[satuan]);
    
    delay(1000); // Tunda 1 detik sebelum menampilkan angka berikutnya

    countdown--;  // Kurangi nilai countdown

    // Pause ketika mencapai 0
    if (countdown < 0) {
      countdown = 0;  // Jangan biarkan countdown menjadi negatif
      isPaused = true;  // Set flag pause ketika hitungan mencapai 0
    }
  }
}
