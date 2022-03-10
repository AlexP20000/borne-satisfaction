/**
 * Every globale variables are initiate here.
 * 
 * @Author : Alexandre PERETJATKO
 */
#define DEBUG(message) \
  Serial.print("[DEBUG:"); \
  Serial.print(__func__); \
  Serial.print("("); \
  Serial.print(__LINE__); \
  Serial.print(")]-> "); \
  Serial.println(message);

// Mode prod = décommenter la ligne suivante
//#define DEBUG(message);

// Mode prod = ModeDebug false
// Lorsque = true, le port série n'est pas initialisé, ce qui permet de gagner de la vitesse d'execution au boot.
#define ModeDebug true

// Definition des noms des fichiers
// La synthese et les mesuress seront modifiés avec la date courante.
char *fileName_Config       = "/configuration.ini";
char *postfixeFileSynthese  = "_synthese.txt";
char *postfixeFileMesures   = "_mesures.csv";


// Brochage des PIN
#define LED_VERT  4
#define LED_JAUNE 12
#define LED_ROUGE 14

#define BTN_ROUGE 25
#define BTN_JAUNE 26
#define BTN_VERT  27

#define PIN_PWR_EN 13

// Délais d'extinction des lEDs lors du test et des message d'erreur = 1 seconde
const int DelayExtinctionLEDs = 1000;

// Gestion des erreurs
boolean BOO_ProblemeBatterie;
boolean BOO_ProblemeCarteSD;
boolean BOO_FichierParamsManquant;
boolean BOO_Clignote;
