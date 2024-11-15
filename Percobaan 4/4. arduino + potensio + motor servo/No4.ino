int potPin = A0;  // Potensiometer terhubung ke pin analog A0
float potValue = 0; // Variabel untuk menyimpan nilai dari potensiometer
float voltage = 0;  // Variabel untuk menyimpan hasil konversi tegangan

void setup() {
  // Inisialisasi Serial Monitor dengan baud rate 9600
  Serial.begin(9600);
}

void loop() {
  // Baca nilai analog dari potensiometer (nilai dari 0 hingga 1023)
  potValue = analogRead(potPin);
  
  // Konversi nilai potensiometer ke tegangan (0 hingga 5V)
  voltage = potValue * (5.0 / 1023.0);
  
  // Tampilkan nilai tegangan di Serial Monitor
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");  // Tambahkan satuan volt
  
  // Tambahkan jeda 100 ms
  delay(100);
}
