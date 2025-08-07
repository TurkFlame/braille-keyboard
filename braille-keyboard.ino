#include "DFRobotDFPlayerMini.h"

// Definições de pinos
#define BUTTON_PIN_1 12
#define BUTTON_PIN_2 13
#define MAX_VOLUME 30  // Volume máximo (0-30)

// Tempos de debounce e delays
#define DEBOUNCE_DELAY 50
#define INITIAL_DELAY 2000

// Instância do DFPlayer
DFRobotDFPlayerMini playerMP3;

void setup() {
  // Configuração dos pinos
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);

  // Inicialização das comunicações seriais
  Serial.begin(9600);  // Aumentei a velocidade para melhor debug
  Serial1.begin(9600);   // Comunicação com o DFPlayer

  Serial.println(F("\nInicializando DFPlayer Mini..."));
  Serial.println(F("Aguarde 3-5 segundos..."));

  // Delay inicial para estabilização
  delay(INITIAL_DELAY);

  // Tentativa de inicialização com tratamento de erros
  bool initializationSuccess = false;
  for (uint8_t attempt = 1; attempt <= 5; attempt++) {
    Serial.print(F("Tentativa "));
    Serial.print(attempt);
    Serial.println(F(" de inicialização..."));

    if (playerMP3.begin(Serial1)) {
      initializationSuccess = true;
      break;
    }
    delay(1000);
  }

  if (!initializationSuccess) {
    Serial.println(F("\nFalha na inicialização do DFPlayer!"));
    Serial.println(F("Possíveis causas:"));
    Serial.println(F("1. Conexões TX/RX invertidas (TX->RX e RX->TX)"));
    Serial.println(F("2. Cartão SD não formatado como FAT32"));
    Serial.println(F("3. Arquivos MP3 não estão na estrutura correta"));
    Serial.println(F("4. Problema de alimentação (use 5V estável)"));
    Serial.println(F("5. Módulo DFPlayer defeituoso"));

    while (true) {
      // Piscar LED para indicar erro (opcional)
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  }

  // Configurações do player
  playerMP3.volume(MAX_VOLUME);         // Volume máximo inicial
  playerMP3.EQ(DFPLAYER_EQ_NORMAL);     // Equalização padrão
  playerMP3.outputDevice(DFPLAYER_DEVICE_SD);  // Garante que está usando SD

  Serial.println(F("\nDFPlayer Mini inicializado com sucesso!"));
  Serial.println(F("Configurações:"));
  Serial.print(F("Volume: "));
  Serial.println(MAX_VOLUME);
  Serial.println(F("Dispositivo: SD Card"));
  Serial.println(F("Equalizador: Normal\n"));

  // Teste de áudio inicial
  testAudio();
}

void loop() {
  handleButton(BUTTON_PIN_1, 1, 1);  // Botão 1 toca pasta 1, arquivo 1
  handleButton(BUTTON_PIN_2, 1, 2);  // Botão 2 toca pasta 1, arquivo 2
}

// Função para tratamento dos botões
void handleButton(uint8_t buttonPin, uint8_t folder, uint8_t track) {
  if (digitalRead(buttonPin) == LOW) {
    // Debounce
    delay(DEBOUNCE_DELAY);
    if (digitalRead(buttonPin) == LOW) {
      Serial.print(F("Tocando: Pasta "));
      Serial.print(folder);
      Serial.print(F(", Arquivo "));
      Serial.println(track);
      
      playerMP3.playFolder(folder, track);
      
      // Espera soltar o botão
      while (digitalRead(buttonPin) == LOW) {
        delay(10);
      }
    }
  }
}

// Função de teste de áudio
void testAudio() {
  Serial.println(F("Iniciando teste de áudio..."));
  
  // Teste de volume crescente
  for (uint8_t vol = 10; vol <= MAX_VOLUME; vol += 5) {
    playerMP3.volume(vol);
    Serial.print(F("Testando volume: "));
    Serial.println(vol);
    
    playerMP3.playMp3Folder(1);  // Toca o primeiro arquivo na pasta mp3
    delay(2000);
    playerMP3.stop();
    delay(500);
  }
  
  // Configura volume máximo
  playerMP3.volume(MAX_VOLUME);
  Serial.println(F("Teste de áudio concluído\n"));
}