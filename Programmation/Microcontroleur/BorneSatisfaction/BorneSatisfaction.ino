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

const int LED_ROUGE = 14;
const int LED_VERT  = 4;
const int LED_JAUNE = 12;
const int BTN_ROUGE = 25;
const int BTN_VERT  = 27;
const int BTN_JAUNE = 26;

const int DelayExtinctionLEDs = 500; // 0.5 secondes

boolean BOO_ProblemeBatterie      = false;
boolean BOO_ProblemeCarteSD       = false;
boolean BOO_FichierParamsManquant = false;
boolean BOO_Clignote = false;

char *fileName_Config   = "configuration.ini";
char *fileName_Synthese = "synthese.txt";
char *fileName_Mesures  = "mesures.csv";


#include "Batterie.h";
#include "carteSD.h";


void setup() {
  // -------------------------------------------------------------------------------------------------------------
  // Definition des LEDS et BOUTONS.
  //
  pinMode(LED_ROUGE,  OUTPUT);
  pinMode(LED_VERT,   OUTPUT);
  pinMode(LED_JAUNE,  OUTPUT);
  pinMode(BTN_ROUGE,  INPUT_PULLUP);
  pinMode(BTN_VERT,   INPUT_PULLUP);
  pinMode(BTN_JAUNE,  INPUT_PULLUP);


  // -------------------------------------------------------------------------------------------------------------
  // Récupération de la cause du wake up
  //
  esp_sleep_wakeup_cause_t wakeupCause = esp_sleep_get_wakeup_cause();



  /** -------------------------------------------------------------------------------------------------------------
      A-t-om une mise sous tension ?
     (on fait les tests de bon fonctionnements)
  */
  if (wakeupCause == ESP_SLEEP_WAKEUP_EXT1
      or wakeupCause == ESP_SLEEP_WAKEUP_EXT0) {
    // .......................................................................
    // Batterie faible
    if (BATTERIE_getBatterieLevel() <= 20) {
      BOO_ProblemeBatterie = true;

      if (BATTERIE_getBatterieLevel() <= 5) {
        BOO_Clignote = true;
      }


    } else {
      // .......................................................................
      // Carte SD manquante
      if (!SD.begin()) {
        BOO_ProblemeCarteSD = true;

      } else {
        // .......................................................................
        // Fichier params manquant
        // (on test l'existance du fichier de configuration).
        if (!SD_existeFile( fileName_Config )) {
          BOO_ProblemeCarteSD = true;
          BOO_Clignote = true;

          SD_writeConfigFile( fileName_Config );

        } else {
          // .......................................................................
          // Tout est ok
          digitalWrite(LED_VERT, HIGH);
          delay( DelayExtinctionLEDs );
          digitalWrite(LED_VERT, LOW);
        }
      }
    }

  } else {
    /** -------------------------------------------------------------------------------------------------------------
       On vient de réveiller la borne en appuyant sur un des boutons
    */
  }
}



/**
 * ****************************************************************************************************************
 * ****************************************************************************************************************
   Boocle principale.
   On entre à l'interieur que pour la gestion des erreurs au démarrage du boitier de vote.
*/
void loop() {

  // Allumage led ROUGE
  if ( BOO_ProblemeBatterie ) {
    digitalWrite(LED_ROUGE, HIGH);
  }

  // Allumage led JAUNE
  if ( BOO_ProblemeCarteSD ) {
    digitalWrite(LED_JAUNE, HIGH);
  }

  // Extinction des leds
  if ( BOO_Clignote ) {
    digitalWrite(LED_ROUGE, LOW);
    digitalWrite(LED_VERT,  LOW);
    digitalWrite(LED_JAUNE, LOW);

    delay( DelayExtinctionLEDs );
  }

  delay( DelayExtinctionLEDs );
}
