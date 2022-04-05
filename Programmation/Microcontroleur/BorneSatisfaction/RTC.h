/**
 * @Author : Alexandre PERETJATKO
 */
/*
  capteur RTC pcf8523
  Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
*/
#include <RTClib.h>
RTC_PCF8523 rtc;
DateTime now;



/**
  ----------------------------------------------------------------------------------
  Initialise "now" avec la RTC
  ----------------------------------------------------------------------------------*/
String RTC_setTime() {
  rtc.begin();
  rtc.start();

  now = rtc.now();
  /*
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    //Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
    Serial.println();
  */
  return String(now.unixtime());
}


/**
  ----------------------------------------------------------------------------------
   Renvoie la date sous forme de chaine de caractères.
  ----------------------------------------------------------------------------------*/
String RTC_getDate() {
  rtc.begin();
  rtc.start();

  DateTime now = rtc.now();
  char jour[3]; sprintf(jour, "%02i", now.day());
  char mois[3]; sprintf(mois, "%02i", now.month());

  return String(now.year() ) + "/" + String(mois) + "/" + String(jour);
}


/**
  ----------------------------------------------------------------------------------
   Renvoie l'heure sous forme de chaine de caractères.
  ----------------------------------------------------------------------------------*/
String RTC_getTime() {
  rtc.begin();
  rtc.start();

  DateTime now = rtc.now();
  char hour[3]; sprintf(hour, "%02i", now.hour());
  char minute[3]; sprintf(minute, "%02i", now.minute());
  char second[3]; sprintf(second, "%02i", now.second());
 
  return String(hour) + ":" + String(minute) + ":" + String(second);
}
