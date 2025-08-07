#include "DFRobotDFPlayerMini.h"

// Definições de pinos para o Arduino Mega 2560
// Letras (A-Z) - usando pinos digitais 2-53
#define BUTTON_A 2
#define BUTTON_B 3
#define BUTTON_C 4
#define BUTTON_D 5
#define BUTTON_E 6
#define BUTTON_F 7
#define BUTTON_G 8
#define BUTTON_H 9
#define BUTTON_I 10
#define BUTTON_J 11
#define BUTTON_K 12
#define BUTTON_L 13
#define BUTTON_M 22
#define BUTTON_N 23
#define BUTTON_O 24
#define BUTTON_P 25
#define BUTTON_Q 26
#define BUTTON_R 27
#define BUTTON_S 28
#define BUTTON_T 29
#define BUTTON_U 30
#define BUTTON_V 31
#define BUTTON_W 32
#define BUTTON_X 33
#define BUTTON_Y 34
#define BUTTON_Z 35

// Números (0-9) - usando pinos 36-45
#define BUTTON_0 36
#define BUTTON_1 37
#define BUTTON_2 38
#define BUTTON_3 39
#define BUTTON_4 40
#define BUTTON_5 41
#define BUTTON_6 42
#define BUTTON_7 43
#define BUTTON_8 44
#define BUTTON_9 45

#define MAX_VOLUME 30  // Volume máximo (0-30)
#define DEBOUNCE_DELAY 50
#define INITIAL_DELAY 2000

DFRobotDFPlayerMini playerMP3;

void setup() {
  // Configura todos os pinos das letras
  for(int i = BUTTON_A; i <= BUTTON_Z; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  
  // Configura todos os pinos dos números
  for(int i = BUTTON_0; i <= BUTTON_9; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  // Inicialização serial
  Serial.begin(9600);
  Serial1.begin(9600);  // Usando Serial1 para o DFPlayer

  Serial.println(F("\nInicializando DFPlayer Mini..."));
  delay(INITIAL_DELAY);

  if (!playerMP3.begin(Serial1)) {
    Serial.println(F("Falha na inicialização! Verifique:"));
    Serial.println(F("1. Conexões TX/RX"));
    Serial.println(F("2. Cartão SD formatado FAT32"));
    Serial.println(F("3. Arquivos na estrutura correta"));
    
    while (true) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(500);
    }
  }

  playerMP3.volume(MAX_VOLUME);
  playerMP3.EQ(DFPLAYER_EQ_NORMAL);
  playerMP3.outputDevice(DFPLAYER_DEVICE_SD);

  Serial.println(F("Sistema pronto!"));
  Serial.println(F("Estrutura do SD Card:"));
  Serial.println(F("Pasta 01: Letras (001.mp3 = A, 002.mp3 = B, ...)"));
  Serial.println(F("Pasta 02: Números (001.mp3 = 0, 002.mp3 = 1, ...)"));
  
  testAudio();
}

void loop() {
  // Letras (Pasta 01)
  handleButton(BUTTON_A, 1, 1);   // A
  handleButton(BUTTON_B, 1, 2);   // B
  handleButton(BUTTON_C, 1, 3);   // C
  handleButton(BUTTON_D, 1, 4);   // D
  handleButton(BUTTON_E, 1, 5);   // E
  handleButton(BUTTON_F, 1, 6);   // F
  handleButton(BUTTON_G, 1, 7);   // G
  handleButton(BUTTON_H, 1, 8);   // H
  handleButton(BUTTON_I, 1, 9);   // I
  handleButton(BUTTON_J, 1, 10);  // J
  handleButton(BUTTON_K, 1, 11);  // K
  handleButton(BUTTON_L, 1, 12);  // L
  handleButton(BUTTON_M, 1, 13);  // M
  handleButton(BUTTON_N, 1, 14);  // N
  handleButton(BUTTON_O, 1, 15);  // O
  handleButton(BUTTON_P, 1, 16);  // P
  handleButton(BUTTON_Q, 1, 17);  // Q
  handleButton(BUTTON_R, 1, 18);  // R
  handleButton(BUTTON_S, 1, 19);  // S
  handleButton(BUTTON_T, 1, 20);  // T
  handleButton(BUTTON_U, 1, 21);  // U
  handleButton(BUTTON_V, 1, 22);  // V
  handleButton(BUTTON_W, 1, 23);  // W
  handleButton(BUTTON_X, 1, 24);  // X
  handleButton(BUTTON_Y, 1, 25);  // Y
  handleButton(BUTTON_Z, 1, 26);  // Z

  // Números (Pasta 02)
  handleButton(BUTTON_0, 2, 1);   // 0
  handleButton(BUTTON_1, 2, 2);   // 1
  handleButton(BUTTON_2, 2, 3);   // 2
  handleButton(BUTTON_3, 2, 4);   // 3
  handleButton(BUTTON_4, 2, 5);   // 4
  handleButton(BUTTON_5, 2, 6);   // 5
  handleButton(BUTTON_6, 2, 7);   // 6
  handleButton(BUTTON_7, 2, 8);   // 7
  handleButton(BUTTON_8, 2, 9);   // 8
  handleButton(BUTTON_9, 2, 10);  // 9
}

void handleButton(uint8_t buttonPin, uint8_t folder, uint8_t track) {
  if (digitalRead(buttonPin) == LOW) {
    delay(DEBOUNCE_DELAY);
    if (digitalRead(buttonPin) == LOW) {
      Serial.print(F("Botão pressionado: "));
      if(folder == 1) {
        Serial.print(char('A' + track - 1));  // Mostra a letra
      } else {
        Serial.print(track - 1);  // Mostra o número
      }
      Serial.print(F(" (Pasta "));
      Serial.print(folder);
      Serial.print(F(", Arquivo "));
      Serial.print(track);
      Serial.println(F(")"));
      
      playerMP3.playFolder(folder, track);
      
      // Espera soltar o botão
      while (digitalRead(buttonPin) == LOW) delay(10);
    }
  }
}

void testAudio() {
  Serial.println(F("\nTestando áudio..."));
  
  // Teste das primeiras letras
  playerMP3.playFolder(1, 1);  // A
  delay(1000);
  playerMP3.playFolder(1, 26); // Z
  delay(1000);
  
  // Teste dos números
  playerMP3.playFolder(2, 1);  // 0
  delay(1000);
  playerMP3.playFolder(2, 10); // 9
  delay(1000);
  
  playerMP3.stop();
  Serial.println(F("Teste concluído!\n"));
}