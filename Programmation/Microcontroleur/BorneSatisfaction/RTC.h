/*
  capteur RTC pcf8523
  Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
*/
#include <RTClib.h>
RTC_PCF8523 rtc;
DateTime now;



/**
  ----------------------------------------------------------------------------------
  Renvoie le timestamp actuel sous forme de chaine de 10 caractères.
  ----------------------------------------------------------------------------------*/
String RTC_getTimestamp() {
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
   Renvoie la date et l'heure sous forme de chaine de caractères.
   @return integer
   librairie adafruit RTClib
  ----------------------------------------------------------------------------------*/
String RTC_getDate() {
  rtc.begin();
  rtc.start();

  DateTime now = rtc.now();
  char jour[3]; sprintf(jour, "%02i", now.day());
  char mois[3]; sprintf(mois, "%02i", now.month());
  String date = String(jour) + "-" + String(mois) + "-" + String(now.year() );


  char hour[3]; sprintf(hour, "%02i", now.hour());
  char minute[3]; sprintf(minute, "%02i", now.minute());
  char second[3]; sprintf(second, "%02i", now.second());
  String heure = String(hour) + ":" + String(minute) + ":" + String(second);

  return date + " " + heure;
}
