// Docs em http://www.rinkydinkelectronics.com/library.php?id=73
#include <DS3231.h>
#include <string.h>

struct dow_schedule {
  int pin; // Pino do rele
  char day[5]; // String com o dia
  bool state; // Estado em que ele vai estar no dia
}; // Cronograma de dia da semana

DS3231 rtc(SDA, SCL);

dow_schedule relays[4];
int c;

void setup()
{ // Ligar um rele por dia. Pode-se escolher ligar mais de um
  // tambem, eh so deixar os dias iuais e o state como true
  relays[0].pin = 7;
  strcpy(relays[0].day, "Fri");
  relays[0].state = true;
  
  relays[1].pin = 6;
  strcpy(relays[1].day, "Mon");
  relays[1].state = true;
  
  relays[2].pin = 5;
  strcpy(relays[2].day, "Wed");
  relays[2].state = true;
  
  relays[3].pin = 4;
  strcpy(relays[3].day, "Mon");
  relays[3].state = true;
  
  for(int i=0; i<4; i++) pinMode(relays[i].pin, OUTPUT);
  
  Serial.begin(9600);
  // Comentarios abaixo para configurar o RTC (so usar uma vez)
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  
  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(5, 6, 40);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(8, 11, 2017);

  c = 0; // Variavel contadora para loop
}
void loop()
{
  // Send Day-of-Week
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
  if(!strcmp(rtc.getDOWStr(FORMAT_SHORT), relays[c].day)) {
    if(relays[c].state) digitalWrite(relays[c].pin, HIGH);
    else digitalWrite(relays[c].pin, LOW);
  }
  
  // Wait one second before repeating
  delay (1000); // Gerenciar esse delay para um valor razoavel
  c += c==3 ? -3 : 1; // Resetar (ou incrementar) a variavel
}
