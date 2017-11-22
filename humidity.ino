/* This code uses example code from the Adafruit examples
 * of using the AM2302 humidity sensor.
 * It shows the time too! (Using an RTC)
 * The LM35 is also tested here.
 * Esse codigo usa exmplos do codigo da Adafruit, em relacao
 * ao sensor de umidade AM2302.
 * Ele tambem mostra a hora! (Usando um RTC)
 * O LM35 tambem eh testado aqui.
 */
#include <DS3231.h>
#include <DHT.h>

#define DHTPIN 8     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define LM35 A0
 
DHT dht(DHTPIN, DHTTYPE);

DS3231 rtc(SDA, SCL); // A4 and A5 cannot be used, they're i2c

void setup() {
  Serial.begin(9600); 
  dht.begin();
}
 
void loop() {
  rtc.begin();
  // Wait a few seconds between measurements.
  delay(1000);
 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    Serial.println(h);
    Serial.println(t);
    delay(500);
    return;
  }

  Serial.println(rtc.getTimeStr());
  Serial.println(rtc.getDateStr());
  
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

  Serial.print("LM35: ");
  Serial.print((float(analogRead(LM35))*5/(1023))/0.01);
  Serial.println(" *C ");
}
