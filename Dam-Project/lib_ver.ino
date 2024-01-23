#include <LedController.h>
#include <SpeakerController.h>
#include <LcdController.h>
#include <HcSr04Controller.h>
#include <MotorController.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

// Bileşenlerin Pin Tanımlamaları
LedController redLed(5);
LedController yellowLed(4);
LedController greenLed(3);
SpeakerController speaker(8);
LcdController lcd(0x27, 16, 2);
HcSr04Controller hcSr04(7, 6);
MotorController motor(10, 11);
SoftwareSerial BTSerial(0, 1); 

float litre;
bool alarmState = false; // Speaker ve RedLed için
bool systemState = false;  // Sistemin durumunu takip etmek için yeni bir değişken
bool motorState = false; // Motor çalışırken red led, speakerda çalışmaya decam etmesi için

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  // Bileşenleri Başlat (Kütüphaneden)
  redLed.initialize();
  yellowLed.initialize();
  greenLed.initialize();
  speaker.initialize();
  lcd.initialize();
  hcSr04.initialize();
  motor.initialize();

// TİMER
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 10000; // 0.7 saniye üret
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

  sei();

  restoreLastWaterLevel();
}

ISR(TIMER1_COMPA_vect) { // KESME
  if (motorState){
    if (systemState) {
      if (alarmState) {
        digitalWrite(5, HIGH);
        speaker.playTone(440);
        alarmState = false;
      } else {
        digitalWrite(5, LOW);
        speaker.stopTone();
        alarmState = true;
      }
    }
  }if (!motorState){
    digitalWrite(5,LOW);
    speaker.stopTone();
  }
}

void loop() {

  if (BTSerial.available() > 0) {
    char command = BTSerial.read(); // Bluetooth üzerinden komutu oku

    if (command == 'O') {
      systemState = true; // Sistemi aç
      lcd.clear();
      lcd.printString("Sistem acildi", 0, 0);
      Serial.println("Sistem acildi");
      delay(1500);
    } else if (command == 'C') {
      systemState = false; // Sistemi kapat
      turnOffAllComponents(); // Tüm bileşenleri kapat
      Serial.println("Sistem kapatildi");
      delay(1500);
    }
  }
  
  if(systemState) {
    readSensor();
    updateLcdWithWaterLevel();
    controlLedsBasedOnWaterLevel();
    controlMotorBasedOnWaterLevel();
    delay (500);
  }
}

void turnOffAllComponents() {
  redLed.turnOff();
  yellowLed.turnOff();
  greenLed.turnOff();
  speaker.stopTone();
  motor.stopMotor();
  alarmState = false;
  lcd.clear();
  lcd.printString("Sistem kapali", 0, 0);
  restoreLastWaterLevel();
}

void restoreLastWaterLevel() {
  // EEPROM'dan son su seviyesini geri yükle
  EEPROM.get(0, litre);
  lcd.clear();
  if (litre >= 0 && litre <= 5 ){
      lcd.printString("Son su seviye: ",0,0);
      lcd.printString(String(litre) + " L", 0, 1);
      delay(3000); // Ekranda son su seviyesini bir süre göster
  }else {
      lcd.printString("Son su seviye: ",0,0);
      lcd.printString("0 L", 0, 1);
      delay(3000); // Ekranda son su seviyesini bir süre göster
  }

}

void readSensor() {
  float distance = hcSr04.getDistance(); //Trig pini aç kapa
  litre = (30 - distance) / 5;
  // EEPROM'a yeni su seviyesini kaydet
  EEPROM.put(0, litre);
}

void updateLcdWithWaterLevel() {
  if (litre >= 0 && litre <= 5 ){
    lcd.clear();
    lcd.printString("Su Seviyesi: ",0,0);
    lcd.printString(String(litre) + " L", 10, 1);
  }
}

void controlLedsBasedOnWaterLevel() {
  yellowLed.turnOnOff(litre <= 4 && litre >= 2.5); // ilgili aralıkta açma işlemleri
  greenLed.turnOnOff(litre < 2.5 && litre >= 1);
}

void controlMotorBasedOnWaterLevel() {
  if (litre > 4) {
    motorState = true;
    motor.startMotor();
    lcd.printString("Tahliye...", 0, 1);
  } if (litre <= 2.5) {
    motorState = false;
      motor.stopMotor();
  }
}
