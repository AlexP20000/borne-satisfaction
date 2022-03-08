#include "SD.h";
#include "libs/inifile/src/IniFile.h";

/**
   ----------------------------------------------------------------------------------
   Ajout d'une ligne à la fin du fichier des mesures.
  ---------------------------------------------------------------------------------- */
void CARTESD_appendFile(const char * path, const char * message) {
  // Construction du nom du fichier
  char fileName[strlen(path) + 1];
  strcpy(fileName, "/");
  strcat(fileName, path);

  // ajout de la ligne à la fin du fichier
  File file = SD.open(fileName, FILE_APPEND);
  if (!file) {
    DEBUG("Failed to open <" + String(path) + "> for reading");
    return;
  }
  if (file.print(message)) {
    DEBUG("Message appended");
  } else {
    DEBUG("Append failed");
  }
  file.close();
}


/**
   ----------------------------------------------------------------------------------
   Ajout d'une ligne à la fin du fichier.
   Ex : CARTESD_readFile( "/hello.txt");
  ---------------------------------------------------------------------------------- */
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



/**
   ----------------------------------------------------------------------------------
   Lecture du fichier de configuration.
   @return
    String siteID:    le Site ID du boitier de vote
    String question:  la question écrite dans le ficheir de configuration.
  ---------------------------------------------------------------------------------- */
void CARTESD_readConfigFile(const char * path, String &p_STR_siteID, String &p_STR_question) {
  // Construction du nom du fichier
  char fileName[strlen(path) + 1];
  strcpy(fileName, "/");
  strcat(fileName, path);

  IniFile ini(fileName);
  // Si on ne peut pas ouvrir le fichier de configuration
  if (!ini.open()) {
    DEBUG("Failed to open <" + String(fileName) + "> for reading");

    // Cannot do anything else
    while (1)
      ;
  }


  // Check the file is valid. This can be used to warn if any lines
  // are longer than the buffer.
  const size_t bufferLen = 80;
  char buffer[bufferLen];
  if (!ini.validate(buffer, bufferLen)) {
    DEBUG("ini file " + String(ini.getFilename()) + " not valid");

    // Cannot do anything else
    while (1)
      ;
  }


  // Lecture des variables
  if (ini.getValue("", "siteID", buffer, bufferLen)) {
    DEBUG("section 'network' has an entry 'siteID' with value ");
    DEBUG(buffer);
    p_STR_siteID = buffer;
    
  }  else {
    DEBUG("Could not read 'siteID' from section ''");
  }


  p_STR_question = "";
}




/**
   ----------------------------------------------------------------------------------
   test l'existance d'un fichier.
   Ex : CARTESD_existeFile("/hello.txt");
  ---------------------------------------------------------------------------------- */
boolean CARTESD_existeFile(const char * path) {
  // Ajout du "/" avant le nom du fichier
  char fileName[strlen(path) + 1];
  strcpy(fileName, "/");
  strcat(fileName, path);

  File file = SD.open(fileName);
  if (!file) {
    DEBUG("File <" + String(path) + "> doesn't exist");
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
void CARTESD_writeConfigFile(const char * path) {
  // Ajout du "/" avant le nom du fichier
  char fileName[strlen(path) + 1];
  strcpy(fileName, "/");
  strcat(fileName, path);

  DEBUG("Ecriture du fichier de configuration: " + String(fileName));

  // Ouverture du fichier en écriture (et réinitialisation)
  File myFile = SD.open(fileName, FILE_WRITE);
  if (myFile) {
    myFile.println("# Ceci est le fichier de configuration pour l'application.");
    myFile.println("# Ne modifiez pas le nom des variables (ce qui se trouve avant le signe égale sur une ligne).");
    myFile.println("#____________________________________________________________________________________________");

    myFile.println("#Le siteID est votre identifiant comme il vous a ete donnee par l'enqueteur, ne le modifiez pas s'il ne vous le demande pas.");
    myFile.println("siteID=Cool Food " + _getRandomChar(10) );
    myFile.println("");

    myFile.println("# Cette phrase apparaitra dans le fichier resultat à votre questionnaire mais n'est pas visible sur la borne.");
    myFile.println("# Il est conseille de definir ici une phrase courte.");
    myFile.println("question=Aimez-vous les brocolis ?");
    myFile.println("");

    myFile.close();
  } else {
    DEBUG("Impossible d'ouvrir le fichier '" + String(fileName) + "' sur la carte SD pour écrire dedans");
  }
}
