/**
   Programme pour micro-controlleur ESP32

   Ce programme permet de compter le nombre d'appuye sur un bouton de vote.
   - La sauvegarde de chaque vote est faite dans un fichier CSV.
   - La sauvegarde du cumul de chaque vote est faite dans un fichier TXT.
*/
#define DEBUG(message) \
  Serial.print("[DEBUG:"); \
  Serial.print(__func__); \
  Serial.print("("); \
  Serial.print(__LINE__); \
  Serial.print(")]-> "); \
  Serial.println(message);
// Mode prod (sans aucune traces)
//#define DEBUG(message);
#define ModeDebug true

#define LED_VERT  4
#define LED_JAUNE 12
#define LED_ROUGE 14

#define BTN_ROUGE 25
#define BTN_JAUNE 26
#define BTN_VERT  27

#define PIN_PWR_EN 13

const int DelayExtinctionLEDs = 1000; // Délais d'extinction des lEDs lors du test = 1 seconde

boolean BOO_ProblemeBatterie      = false;
boolean BOO_ProblemeCarteSD       = false;
boolean BOO_FichierParamsManquant = false;
boolean BOO_Clignote = false;

char *fileName_Config   = "configuration.ini";
char *fileName_Synthese = "synthese.txt";
char *fileName_Mesures  = "mesures.csv";


#include "Batterie.h";
#include "carteSD.h";
#include "deepsleep.h";


void setup() {
  // -------------------------------------------------------------------------------------------------------------
  // initialisation de la liaison série.
  //
  if ( ModeDebug ) {
    Serial.begin(115200);
    delay(1000);  // On attend que le port serie soit initialisé
    DEBUG("OK, let's go ******************************************");
  }



  // -------------------------------------------------------------------------------------------------------------
  // Initialisation des PIN
  //
  pinMode(LED_ROUGE,  OUTPUT);  // Pin du bouton rouge
  pinMode(LED_VERT,   OUTPUT);  // Pin du bouton vert
  pinMode(LED_JAUNE,  OUTPUT);  // Pin du bouton jaune
  pinMode(BTN_ROUGE,  INPUT_PULLUP);  // Pin du bouton rouge
  pinMode(BTN_VERT,   INPUT_PULLUP);  // Pin du bouton vert
  pinMode(BTN_JAUNE,  INPUT_PULLUP);  // Pin du bouton jaune
  pinMode(PIN_PWR_EN, OUTPUT);  // Pin du ??????????
  digitalWrite(PIN_PWR_EN, HIGH);
  delay(20); // pour laisser à l'alimentation le temps de s'établir 20 ms mini


  // -------------------------------------------------------------------------------------------------------------
  // Récupération de la cause du wake up
  //
  esp_sleep_wakeup_cause_t wakeupCause = esp_sleep_get_wakeup_cause();
  DEBUG("Wake up reason : " + String(wakeupCause) );



  /** -------------------------------------------------------------------------------------------------------------
      A-t-om une mise sous tension ?
     (on fait les tests de bon fonctionnements)
  */
  if (wakeupCause != ESP_SLEEP_WAKEUP_EXT0
      and wakeupCause != ESP_SLEEP_WAKEUP_EXT1
      and wakeupCause != ESP_SLEEP_WAKEUP_TIMER
      and wakeupCause != ESP_SLEEP_WAKEUP_TOUCHPAD
      and wakeupCause != ESP_SLEEP_WAKEUP_ULP) {
    // .......................................................................
    // Batterie faible
    int batterieLevel = BATTERIE_getBatterieLevel();
    if (batterieLevel <= 20) {
      DEBUG("Batterie faible");
      BOO_ProblemeBatterie = true;

      if (batterieLevel <= 5) {
        DEBUG("Batterie Tres faible");
        BOO_Clignote = true;
      }


    } else {
      // .......................................................................
      // Carte SD manquante
      if (!SD.begin()) {
        DEBUG("Carte SD manquante");
        BOO_ProblemeCarteSD = true;

      } else {
        // .......................................................................
        // Fichier params manquant
        // (on test l'existance du fichier de configuration).
        if (! CARTESD_existeFile( fileName_Config )) {
          DEBUG("Fichier params manquant");
          BOO_ProblemeCarteSD = true;
          BOO_Clignote = true;

          CARTESD_writeConfigFile( fileName_Config );

        } else {
          // .......................................................................
          // Tout est ok
          DEBUG("Tout est ok");
          digitalWrite(LED_VERT, HIGH);
          delay( DelayExtinctionLEDs );
          digitalWrite(LED_VERT, LOW);

          DEEPSLEEP_start();
        }
      }
    }
  } else {
    /** -------------------------------------------------------------------------------------------------------------
       On vient de réveiller la borne en appuyant sur un des boutons
    */
    // .......................................................................
    //  Allumage de la LEDS correspondante au bouton appuyé
    int gpio = DEEPSLEEP_getGPIOWakeUp();

    switch ( gpio ) {
      case BTN_VERT:
        DEBUG("Bouton vert");
        digitalWrite(LED_VERT,  HIGH);
        break;
      case BTN_ROUGE:
        DEBUG("Bouton rouge");
        digitalWrite(LED_ROUGE,  HIGH);
        break;
      case BTN_JAUNE:
        DEBUG("Bouton jaune");
        digitalWrite(LED_JAUNE,  HIGH);
        break;
      default:
        DEBUG("Le GPIO " + String(gpio) + " a réveillé l'ESP32 : cas non traité (GPIO inconnu)");
    }



    // .......................................................................
    //  Lecture du fichier de configuration
    delay( DelayExtinctionLEDs );

    // .......................................................................
    //  Ecriture dans le fichier des mesures
    delay( DelayExtinctionLEDs );

    // .......................................................................
    //  Mise à jour de la synthèse des votes
    delay( DelayExtinctionLEDs );


    // .......................................................................
    //  Extinction des LEDs
    digitalWrite(LED_ROUGE, LOW);
    digitalWrite(LED_VERT,  LOW);
    digitalWrite(LED_JAUNE, LOW);


    // .......................................................................
    // Deep sleep
    DEEPSLEEP_start();
  }
}



/**
 * ****************************************************************************************************************
 * ****************************************************************************************************************
   Boocle principale.
   On n'entre à l'interieur que pour la gestion des erreurs au démarrage du boitier de vote.
*/
void loop() {
  // Allumage led ROUGE
  if ( BOO_ProblemeBatterie ) {
    DEBUG("ProblemeBatterie");
    digitalWrite(LED_ROUGE, HIGH);
  }

  // Allumage led JAUNE
  if ( BOO_ProblemeCarteSD ) {
    DEBUG("ProblemeCarteSD");
    digitalWrite(LED_JAUNE, HIGH);
  }

  // Extinction des leds
  delay( DelayExtinctionLEDs );
  if ( BOO_Clignote ) {
    DEBUG("Clignote");
    digitalWrite(LED_ROUGE, LOW);
    digitalWrite(LED_VERT,  LOW);
    digitalWrite(LED_JAUNE, LOW);

    delay( DelayExtinctionLEDs );
  }
}
