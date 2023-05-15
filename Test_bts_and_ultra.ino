#include <HCSR04.h>

UltraSonicDistanceSensor sensorFrente (45, 44);
UltraSonicDistanceSensor sensorEsq (49, 48);
UltraSonicDistanceSensor sensorDir (46, 47);
int distace, distaceLatEsq, distaceLatDir;
int alvo = 10;
int LED_green  = 9;
int LED_redEsq = 8;
int LED_redDir = 10;

int BTN_f4 = 35;
int estadoBtn = 0;

void setup () {
  pinMode(LED_green, OUTPUT);
  pinMode(LED_redEsq, OUTPUT);
  pinMode(LED_redDir, OUTPUT);
  pinMode(BTN_f4, INPUT_PULLUP);
  Serial.begin(1200);
}

void loop () {
  distace = sensorFrente.measureDistanceCm();
  distaceLatEsq = sensorEsq.measureDistanceCm();
  distaceLatDir = sensorDir.measureDistanceCm();

  estadoBtn = digitalRead(BTN_f4);
  
  if (estadoBtn == HIGH){
      digitalWrite(LED_green, HIGH);
      digitalWrite(LED_redDir, HIGH);
      digitalWrite(LED_redEsq, HIGH);
      delay(150);
      digitalWrite(LED_green, LOW);
      digitalWrite(LED_redDir, LOW);
      digitalWrite(LED_redEsq, LOW);
      delay(150);
      return;
  }

  if (estadoBtn == LOW) {
  
    if (distace <= alvo && distace > 5) {
      Serial.println(distace);
      digitalWrite(LED_green, HIGH);
      delay (100);
      
      if (distaceLatEsq <= alvo && distaceLatEsq > 4) {
        Serial.print(distaceLatEsq);
        digitalWrite(LED_redEsq, HIGH);
        delay (100);
      } else if (distaceLatDir <= alvo && distaceLatDir > 4) {
        Serial.print(distaceLatDir);
        digitalWrite(LED_redDir, HIGH);
        delay (100);
      } else {
        digitalWrite(LED_redDir, LOW);
        digitalWrite(LED_redEsq, LOW);
        delay(100);
      }
    }
    else if (distace < 5) {
      digitalWrite(LED_green, LOW);
      digitalWrite(LED_redDir, HIGH);
      digitalWrite(LED_redEsq, HIGH);
      delay(150);
      digitalWrite(LED_redDir, LOW);
      digitalWrite(LED_redEsq, LOW);
      delay(150);
    }

    while (digitalRead(BTN_f4) == LOW);
    delay(100);
  }
}
