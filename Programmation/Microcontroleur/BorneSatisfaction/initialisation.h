/**
 * Every globale variables are initiate here.
 * 
 * @Author : Alexandre PERETJATKO
 */

// Definition des noms des fichiers
// La synthese et les mesuress seront modifiés avec la date courante.
char *fileName_Config       = "/configuration.ini";
char *postfixeFileSynthese  = "_recap.txt";
char *postfixeFileMesures   = "_detail.csv";


// Brochage des PIN
#define LED_VERT  4
#define LED_JAUNE 12
#define LED_ROUGE 14

#define BTN_ROUGE 25
#define BTN_JAUNE 26
#define BTN_VERT  27

#define PIN_PWR_EN 13

// Délais d'extinction des lEDs lors du test et des messages d'erreur = 1 seconde
const int DelayExtinctionLEDs = 1000;


#ifdef ModeDebug
#define DEBUG(message) \
  Serial.print("[DEBUG:"); \
  Serial.print(__func__); \
  Serial.print("("); \
  Serial.print(__LINE__); \
  Serial.print(")]-> "); \
  Serial.println(message);
#else
#define DEBUG(message);
#endif