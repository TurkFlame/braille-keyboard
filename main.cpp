#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define VOLUME 30
#define DEBOUNCE_DELAY 50

SoftwareSerial mySerial(50, 51);
DFRobotDFPlayerMini player;

const int numButtons = 36;
struct ButtonConfig {
  int pin;
  int folder;
  int track;
};

ButtonConfig buttons[] = {
  // Letras (Pasta 1: A=1, B=2, ..., Z=26)
  {13, 1, 1},    // A
  {12, 1, 2},    // B
  {11, 1, 3},    // C
  {10, 1, 4},    // D
  {9, 1, 5},     // E
  {8, 1, 6},     // F
  {7, 1, 7},     // G
  {6, 1, 8},     // H
  {5, 1, 9},     // I
  {4, 1, 10},    // J
  {3, 1, 11},    // K
  {52, 1, 12},   // L
  {50, 1, 13},   // M
  {48, 1, 14},   // N
  {46, 1, 15},   // O
  {44, 1, 16},   // P
  {42, 1, 17},   // Q
  {40, 1, 18},   // R
  {38, 1, 19},   // S
  {36, 1, 20},   // T
  {34, 1, 21},   // U
  {32, 1, 22},   // V
  {30, 1, 23},   // W
  {28, 1, 24},   // X
  {26, 1, 25},   // Y
  {24, 1, 26},   // Z

  // Números (Pasta 2: 1=1, 2=2, ..., 10=10)
  {22, 2, 1},    // 1
  {53, 2, 2},    // 2
  {51, 2, 3},    // 3
  {49, 2, 4},    // 4
  {47, 2, 5},    // 5
  {45, 2, 6},    // 6
  {43, 2, 7},    // 7
  {41, 2, 8},    // 8
  {39, 2, 9},    // 9
  {37, 2, 10}    // 10
};

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  if (!player.begin(mySerial)) {
    Serial.println("Falha ao iniciar DFPlayer!");
    while(true);
  }
  player.volume(VOLUME);

  for (int i = 0; i < numButtons; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(buttons[i].pin) == LOW) {
      delay(DEBOUNCE_DELAY);
      player.playFolder(buttons[i].folder, buttons[i].track);
      Serial.print("Tocando: Pasta ");
      Serial.print(buttons[i].folder);
      Serial.print(", Track ");
      Serial.println(buttons[i].track);
      
      while (digitalRead(buttons[i].pin) == LOW);
    }
  }
}
