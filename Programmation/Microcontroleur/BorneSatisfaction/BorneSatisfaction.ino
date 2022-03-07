/**
   Ce programme permet de compter le nombre d'appuye sur un bouton de vote.
   - La sauvegarde de chaque vote est faite dans un fichier CSV.
   - La sauvegarde du cumul de chaque vote est faite dans un fichier TXT.
*/
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



  /** -------------------------------------------------------------------------------------------------------------
      A-t-om une mise sous tension ?
     (on fait les tests de bon fonctionnements)
  */
  if () {
    // .......................................................................
    // Batterie faible
    if (BATTERIE_getBatterieLevel() <= 20) {
      BOO_ProblemeBatterie = true;

      if (BATTERIE_getBatterieLevel() <= 5) {
        BOO_Clignote = true;
      }


    } else {
      // .......................................................................
      // Carte SD manquant
      if () {
        BOO_ProblemeCarteSD = true;

      } else {
        // .......................................................................
        // Fichier params manquant
        if () {
          BOO_ProblemeCarteSD = true;
          BOO_Clignote = true;

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
