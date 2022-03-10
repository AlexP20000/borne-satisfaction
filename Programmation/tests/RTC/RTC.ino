/*
  capteur RTC pcf8523
  Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
*/
#define DEBUG(message) \
  Serial.print("[DEBUG:"); \
  Serial.print(__func__); \
  Serial.print("("); \
  Serial.print(__LINE__); \
  Serial.print(")]-> "); \
  Serial.println(message);

#include <RTClib.h>
RTC_PCF8523 rtc;

#include <NTPClient.h>
#include <WiFiUdp.h>


#define PIN_PWR_EN 13


void setup() {
  pinMode(PIN_PWR_EN, OUTPUT);  // Pin de l'autorisation de l'alimentation des périphériques
  Serial.begin(115200);
  delay(1000);  // On attend que le port serie soit initialisé
  DEBUG("OK, let's go ******************************************");

  digitalWrite(PIN_PWR_EN, HIGH);
  delay(20); // pour laisser à l'alimentation le temps de s'établir 20 ms mini


  // On va chercher l'heure sur le serveur de temps de L'UBO
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP, "chronos.univ-brest.fr");
  timeClient.begin();
  timeClient.setTimeOffset(7200); // Heure de Paris GMT +2 (in secondes)
  timeClient.update();
  DEBUG("Connection au serveur NTP ok");

  // Get a Time structure for days, month and year
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm    = gmtime ((time_t *)&epochTime);
  String currentDate = String(ptm->tm_mday) + "/" + String(ptm->tm_mon + 1) + "/" + String(ptm->tm_year + 1900);

  // Si on a pas reussi a lire l'heure du serveur de temps
  if ( currentDate == "1/1/1970" ) {
    DEBUG("Impossible de lire l'heure sur le serveur chronos.univ-brest.fr, on essaie sur pool.ntp.org");
    timeClient.end();
    timeClient.setPoolServerName("pool.ntp.org");

    timeClient.begin();
    timeClient.setTimeOffset(7200); // Heure de Paris GMT +2 (in secondes)
    timeClient.update();

    epochTime = timeClient.getEpochTime();
    ptm    = gmtime ((time_t *)&epochTime);
    currentDate = String(ptm->tm_mday) + "/" + String(ptm->tm_mon + 1) + "/" + String(ptm->tm_year + 1900);
  }

  String formattedTime = timeClient.getFormattedTime();

  DEBUG("Il est : " + formattedTime);
  DEBUG("Nous sommes le : " + currentDate);
  // Si la RTC n'est pas trouvée
  if (!rtc.begin()) {
    DEBUG("Couldn't find RTC");


  } else {
    // Mise à l'heure de la RTC
    DEBUG("Mise à l'heure de la RTC");
    rtc.adjust(DateTime(timeClient.getEpochTime()));
    rtc.start();
  }
}

void loop() {
}
