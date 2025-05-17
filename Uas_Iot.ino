// Definisikan pin untuk sensor dan komponen lainnya
const int flameSensorPin = 25; // Pin untuk sensor api
const int gasSensorPin = 15;    // Pin untuk sensor gas
const int ledPin = 14;          // Pin untuk LED
const int buzzerPin = 12;       // Pin untuk Buzzer
const int speakerPin = 26;      // Pin untuk Speaker

// Definisikan UART
#include <HardwareSerial.h>
HardwareSerial mySerial(1); // UART1

bool alarmActive = false; // Variabel untuk menandai status alarm

void setup() {
  // Inisialisasi pin sebagai input atau output
  pinMode(flameSensorPin, INPUT);
  pinMode(gasSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  // Inisialisasi serial komunikasi
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 17, 16); // RX = 16, TX = 17

  Serial.println("Sistem deteksi api dan gas aktif dengan DFPlayer Mini dan Speaker");
}

void playAlarmSound() {
  // Mengirim perintah untuk memainkan suara ke DFPlayer Mini
  byte command[] = {0x7E, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x01, 0xFE, 0xED, 0xEF};
  mySerial.write(command, sizeof(command));
}

void alarm() {
  // Menyalakan alarm (LED, Buzzer, Speaker, dan Suara)
  digitalWrite(ledPin, HIGH);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(speakerPin, HIGH);
  playAlarmSound();
}

void deactivateAlarm() {
  // Mematikan alarm
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(speakerPin, LOW);
  alarmActive = false; // Menandai alarm dimatikan
}

void loop() {
  int flameStatus = digitalRead(flameSensorPin); // Membaca status sensor api
  int gasStatus = digitalRead(gasSensorPin);     // Membaca status sensor gas

  // Tampilkan status di Serial Monitor untuk debugging
  Serial.print("Flame Status: ");
  Serial.println(flameStatus);
  Serial.print("Gas Status: ");
  Serial.println(gasStatus);

  if (flameStatus == LOW || gasStatus == LOW) { // Api atau gas terdeteksi
    if (!alarmActive) { // Jika alarm belum aktif
      Serial.println("Bahaya! Terdeteksi api atau gas berbahaya!");
      alarm();
      alarmActive = true; // Menandai alarm aktif
    }
  } else {
    deactivateAlarm(); // Mematikan alarm jika tidak ada deteksi
  }

  delay(1000); // Delay 1 detik
}
