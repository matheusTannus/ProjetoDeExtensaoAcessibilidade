#include <Ultrasonic.h>

// Configuração do sensor ultrassônico
Ultrasonic ultrasonic(4, 5); // Trigger = 4, Echo = 5

// Definição dos pinos
#define LED 11
#define BUZZER 12

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  long distancia = ultrasonic.read(); // mede a distância em cm

  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Faixa útil de detecção (2 a 50 cm)
  if (distancia > 2 && distancia < 50) {

    // Caso esteja MUITO PERTO (até 5 cm)
    if (distancia <= 6) {
      tone(BUZZER, 1500);        // som contínuo de 1500Hz
      digitalWrite(LED, HIGH);   // LED aceso direto
      delay(100);
    } 
    else {
      // Cria o efeito "sensor de ré": quanto mais perto, mais rápido
      int intervalo = map(distancia, 6, 50, 80, 700);

      tone(BUZZER, 1000);        // apita
      digitalWrite(LED, HIGH);   // acende LED
      delay(50);                 // duração do beep curto

      noTone(BUZZER);            // para o som
      digitalWrite(LED, LOW);    // apaga LED
      delay(intervalo);          // tempo até o próximo beep
    }

  } else {
    // Fora da faixa (objeto longe)
    noTone(BUZZER);
    digitalWrite(LED, LOW);
  }
}
