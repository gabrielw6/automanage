#include <DS3231.h>
#include <string.h>

#define NR 2 // Numero de reles

DS3231 rtc(SDA, SCL); // Pinos de I2C (conectar resistores pull-up
                  // de pelo menos 1k nos dois pinos, como
                  // define o protocolo
char dia[5], hoje[5];
int c = 1;
int reles[NR] = {4,5}; // Pinos dos reles
// Indice da matriz abaixo eh o dia da semana
// Somar 1 ao indice para corresponder ao literal da DS3231
int cronograma[NR][7] = {{1,0,1,0,1,0,1}, // Rele 1
                         {1,1,0,1,1,1,0}};// Rele 2
// Compara o dia char * retornado pelo RTC com o indice do vetor
// que descreve a numeracao dos dias e retorna igualdade ou nao
int getDia(char *d, int n) {
  char semana[7][4] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
  if(!strcmp(d, semana[n])) return 1;
  return 0;
}

void setup() {
  for(int i=0; i<NR; i++) pinMode(reles[i], OUTPUT);
  Serial.begin(9600); // Ou 115200
  strcpy(hoje, rtc.getDOWStr(FORMAT_SHORT));
}

void loop() {
  strcpy(dia, rtc.getDOWStr(FORMAT_SHORT));
  if(!strcmp(dia, hoje)) { // Checa se os reles ja foram ativados
    if(getDia(dia, c)) { // Descobre o numero do dia da semana
      for(int i=0; i<NR; i++) { // Estadia cada rele no estado descrito
        digitalWrite(reles[i], cronograma[i][c-1]);
        Serial.print("Rele ");
        Serial.print(i);
        Serial.print(" em estado");
        Serial.println(cronograma[i][c-1]);
      }
    }
    strcpy(hoje, dia); // Override do dia de hoje
  }

  c += (c==7) ? -6 : 1; // Reseta o contador;
  delay(1000);
}
