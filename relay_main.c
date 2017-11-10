// Docs em http://www.rinkydinkelectronics.com/library.php?id=73  
// The following lines can be uncommented to set the date and time
// (Add to setup() when needed)
//rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
//rtc.setTime(5, 6, 40);     // Set the time to 12:00:00 (24hr format)
//rtc.setDate(8, 11, 2017);
#include <DS3231.h>
#include <string.h>
#define N_R 4

typedef struct {
  int pin; // Pino do rele
  bool states[7]; // Estado em que ele vai estar no dia
} dow_schedule; // Cronograma de dia da semana

int day_to_num(char *d) {
  char days[7][5] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  for(int i=0; i<7; i++) {
    if(!strcmp(days[i], d)) return i;
  }
  return -1;
}

DS3231 rtc(SDA, SCL); //MEGA: SDA, SCL / Uno: A4, A5

int c;

dow_schedule relays[N_R] = {{.pin = 4, .states = {0,0,1,0,1,0,0}},
                            {.pin = 5, .states = {0,1,0,1,0,0,1}},
                            {.pin = 6, .states = {1,0,1,0,0,1,0}},
                            {.pin = 7, .states = {0,1,0,0,1,0,1}}};

void setup()
{ // Ligar um rele por dia. Pode-se escolher ligar mais de um
  // tambem, eh so deixar os dias iguais e o state como true
  
  for(int i=0; i<N_R; i++) pinMode(relays[i].pin, OUTPUT);
  
  Serial.begin(9600);
  rtc.begin(); // Initalize RTC object

  c = 0; // Variavel contadora para loop
}
void loop()
{
  // Send Day-of-Week
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
  digitalWrite(relays[c].pin, relays[c].states[day_to_num(rtc.getDOWStr(FORMAT_SHORT))]);
  
  delay (1000); // Gerenciar esse delay para um valor razoavel
  c += c==3 ? -3 : 1; // Resetar (ou incrementar) a variavel
}
