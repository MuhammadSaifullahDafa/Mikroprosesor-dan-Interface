// Definisikan pin segment
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

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

// Fungsi menampilkan angka di seven segment
void tampilkanAngka(byte angka) {
  digitalWrite(a, bitRead(angka, 0));
  digitalWrite(b, bitRead(angka, 1));
  digitalWrite(c, bitRead(angka, 2));
  digitalWrite(d, bitRead(angka, 3));
  digitalWrite(e, bitRead(angka, 4));
  digitalWrite(f, bitRead(angka, 5));
  digitalWrite(g, bitRead(angka, 6));
}

void setup() {
  // Set pin output
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop() {
  // Loop untuk menampilkan angka 0 sampai 9
  for (int i = 0; i < 10; i++) {
    tampilkanAngka(angka[i]);
    delay(1000); // Tampilkan setiap angka selama 1 detik
  }
}
