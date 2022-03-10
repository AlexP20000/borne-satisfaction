#include <SD.h>
#include <SPI.h>
#include <IniFile.h>

#include <Arduino.h>
#include "FS.h"
#include <LITTLEFS.h>

/**
   ----------------------------------------------------------------------------------
   Ajout d'une ligne à la fin du fichier.
   Ex : CARTESD_readFile( "/hello.txt");
  ----------------------------------------------------------------------------------
  void CARTESD_readFile(const char * path) {
  File file = SD.open(path);
  if (!file) {
    DEBUG("Failed to open <" + String(path) + "> for reading");
    return;
  }

  DEBUG("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
  }
*/


/**
   ----------------------------------------------------------------------------------
   Lecture du fichier de configuration.
   @param
    CHAR fileName: le nom du fichier (ne pas oublier le / en début de chaine).
   @return
    String siteID:    le Site ID du boitier de vote
    String question:  la question écrite dans le fichier de configuration.
  ---------------------------------------------------------------------------------- */
boolean CARTESD_readConfigFile(const char * fileName, String &p_STR_siteID, String &p_STR_question) {

  // test de la carte SD
  if (!SD.begin())
    while (1)
      DEBUG("SD.begin() failed");


  // Si on ne peut pas ouvrir le fichier de configuration
  IniFile ini(fileName);
  if (!ini.open()) {
    DEBUG("Failed to open <" + String(fileName) + "> for reading");

    // On ne fait rien d'autre
    return false;
  }


  // Check if the file is valid. This can be used to warn if any lines are longer than the buffer.
  const size_t bufferLen = 300;
  char buffer[bufferLen];
  if (!ini.validate(buffer, bufferLen)) {
    DEBUG("ini file " + String(ini.getFilename()) + " not valid");

    // On ne fait rien d'autre
    return false;
  }


  // Lecture du siteID
  if (ini.getValue("config", "siteID", buffer, bufferLen)) {
    p_STR_siteID = buffer;

  }  else {
    DEBUG("Could not read 'siteID' from section 'config'");
  }

  // Lecture de la question
  if (ini.getValue("config", "question", buffer, bufferLen)) {
    p_STR_question = buffer;

  }  else {
    DEBUG("Could not read 'question' from section 'config'");
  }
  return true;
}




/**
   ----------------------------------------------------------------------------------
   test l'existance d'un fichier.
   Ex : CARTESD_existeFile("/hello.txt");
  ---------------------------------------------------------------------------------- */
boolean CARTESD_existeFile(const char * fileName) {
  File file = SD.open(fileName);
  if (!file) {
    DEBUG("File <" + String(fileName) + "> doesn't exist");
    return false;
  } else {
    return true;
  }
}

/**
   ----------------------------------------------------------------------------------
   Renvoie une chaine aléatoire avec nbCaract caractères.
  ---------------------------------------------------------------------------------- */
String _getRandomChar(int nbCaract) {
  char caracts[38] = "AZERTYUIOPQSDFGHJKLMWXCVBN 0123456789";
  char Chaine[nbCaract];
  for (int i = 0; i < nbCaract; i++) {
    Chaine[i] = caracts[random(0, 38)];
  }

  // Ajout du caractère de fin de chaine
  Chaine[nbCaract] = '\0';

  return String(Chaine);
}



/**
   ----------------------------------------------------------------------------------
   Ecriture d'un fichier de configuration.
   Ex : CARTESD_existeFile("/config.ini");
  ---------------------------------------------------------------------------------- */
void CARTESD_writeConfigFile(const char * fileName) {

  DEBUG("Ecriture du fichier de configuration: " + String(fileName));

  // Ouverture du fichier en écriture (et réinitialisation)
  File myFile = SD.open(fileName, FILE_WRITE);
  if (myFile) {
    myFile.println("# Ceci est le fichier de configuration pour l'application 'Compteur de vote'.");
    myFile.println("# Ne modifiez pas le nom des variables (ce qui se trouve avant le signe egale sur une ligne).");
    myFile.println("# Vous pouvez modifier le texte se trouvant apres le signe egale a votre guise.");
    myFile.println("#____________________________________________________________________________________________");
    myFile.println("[config]");
    myFile.println("");

    myFile.println("# Le siteID est votre identifiant comme il vous a ete donnee par l'enqueteur, ne le modifiez pas s'il ne vous le demande pas.");
    myFile.println("siteID=Cool Food " + _getRandomChar(10) );
    myFile.println("");

    myFile.println("# Cette phrase apparaitra dans le fichier resultat à votre questionnaire mais n'est pas visible sur la borne.");
    myFile.println("# Il est conseille de definir ici une phrase courte.");
    myFile.println("question= Aimez-vous les brocolis ?");
    myFile.println("");

    myFile.close();
  } else {
    DEBUG("Impossible d'ouvrir le fichier '" + String(fileName) + "' sur la carte SD pour écrire dedans");
  }
}


/**
   ----------------------------------------------------------------------------------
   Ajout d'une ligne à la fin du fichier des mesures.
   Si le fichier n'existe pas, on le cré.
  ----------------------------------------------------------------------------------*/
void CARTESD_appendFileMesure(String date, const char *path, String message) {

  // Construction du nom du fichier avec la date en préfixe
  date.replace("/", "-"); // remplacment des / par des - dans la date
  String fileName = "/" + date + String(path);

  // Convertion du nom du fichier en Char
  char charFileName[25];
  fileName.toCharArray(charFileName, 25);

  // si le fichier n'existe pas
  if (!CARTESD_existeFile(charFileName) ) {
    DEBUG("Le fichier " + fileName + " n'existe pas, on l'initialise");

    // Ajoute la ligne d'entête des colonnes
    message = "Identifiant du site;Date;Heure;Question;Oui;Non;Indecis;Niveau Batterie\n" + message;
    DEBUG( message );
  }


  // ajout de la ligne à la fin du fichier
  File file = SD.open(fileName, FILE_APPEND);
  if (!file) {
    DEBUG("Failed to open <" + String(path) + "> for writing");
    return;
  }
  if (file.println(message)) {
    DEBUG("Message appended " + String(message) );
  } else {
    DEBUG("Append failed");
  }
  file.close();
}




/**
   ----------------------------------------------------------------------------------
   Mise à jour du fichier de synthese des votes.
   ----------------------------------------------------------------------------------*/
void CARTESD_miseAJourSynthese(const char *path, int rouge, int vert, int jaune, int batterieLevel, String date, String question, String siteID ) {

  // Remplacment des / par des - dans la date
  String l_STR_Date = date;
  l_STR_Date.replace("/", "-");
  char l_CHAR_Date[15];
  l_STR_Date.toCharArray(l_CHAR_Date, 15);

  // Construction du nom du fichier avec la date en préfixe
  char l_CHAR_fileName[25];
  strcpy( l_CHAR_fileName, "/");
  strcat( l_CHAR_fileName, l_CHAR_Date);
  strcat( l_CHAR_fileName, path );

  // Mise en place de LittleFS pour aller lire le fichier de synthese
  if (!LITTLEFS.begin(true)) {
    DEBUG("Il n'y a pas de file system little FS installé, lecture impossible !");
  }

  // Constructio ndu nom du fichier de synthese pour la ROM
  char littleFSFileName[25];
  strcpy( littleFSFileName, "/synthese_");
  strcat( littleFSFileName, now.month);


  // Lecture du fichier de synthses de la rom
  if ( LITTLEFS.exists(littleFSFileName) ) {
    LITTELFS.open(littleFSFileName, "r");
  }

  // Ecriture du fichier de synthese en ROM




  /*
    // si le fichier n'existe pas
    if (!CARTESD_existeFile(l_CHAR_fileName) ) {
      File file = SD.open(l_CHAR_fileName, FILE_APPEND);

      file.println("[synthese]");
      file.println("Etablissement = " + siteID);
      file.println("Date          = " + date);
      file.println("Question      = " + question);
      file.println("Batterie      = " + String(batterieLevel) + "%" );
      file.println("# Nombre d'appuie sur les boutons");
      file.println("Rouge = " + String(rouge, DEC) );
      file.println("Vert  = " + String(vert,  DEC) );
      file.println("Jaune = " + String(jaune, DEC) );

      file.close();

    } else {
      const size_t bufferLen = 80;
      char buffer[bufferLen];

      // Lecture du fichier de synthese
      IniFile ini(l_CHAR_fileName);
      int valRouge, valVert, valJaune;
      if (ini.getValue("synthese", "Rouge", buffer, bufferLen)) {
        valRouge = atol(buffer);
      }  else {
        DEBUG("Could not read 'Rouge' from section 'synthese'");
      }
      if (ini.getValue("synthese", "Vert", buffer, bufferLen)) {
        valVert = atol(buffer);
      }  else {
        DEBUG("Could not read 'Vert' from section 'synthese'");
      }
      if (ini.getValue("synthese", "Jaune", buffer, bufferLen)) {
        valJaune = atol(buffer);
      }  else {
        DEBUG("Could not read 'Jaune' from section 'synthese'");
      }
  */

  // Cumul des résultats

  // Calcul des moyennes

  // Enregistrement
}
}
