#include "SD.h";
#include "libs/inifile/src/IniFile.h";

/**
   ----------------------------------------------------------------------------------
   Ajout d'une ligne à la fin du fichier des mesures.
  ---------------------------------------------------------------------------------- */
void CARTESD_appendFile(const char * path, const char * message) {
  // Constrction du nom du fichier
  char fileName[strlen(fileName_Mesures) + 1];
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
   test l'existance d'un fichier.
   Ex : CARTESD_existeFile("/hello.txt");
  ---------------------------------------------------------------------------------- */
boolean CARTESD_existeFile(const char * path) {
  File file = SD.open(path);
  if (!file) {
    DEBUG("Fil <" + String(path) + "> doesn't exist");
    return false;
  } else {
    return true;
  }
}

/**
   ----------------------------------------------------------------------------------
   Renvoie une chaine aléatoire avec nbCaract caractères.
  ---------------------------------------------------------------------------------- */
char * _getRandomChar(int nbCaract) {
  const char caracts[] = {"AZERTYUIOPQSDFGHJKLMWXCVBN "};
  char *Chaine;

  for ( int i = 0; i <= nbCaract; i++) {
    Chaine[i] = caracts[random(0, 26)];
  }
  return Chaine;
}



/**
   ----------------------------------------------------------------------------------
   Ecriture d'un fichier de configuration.
   Ex : CARTESD_existeFile("/config.ini");
  ---------------------------------------------------------------------------------- */
void CARTESD_writeConfigFile(const char * path) {
  char fileName[strlen(fileName_Config) + 1];
  strcpy(fileName, "/");
  strcat(fileName, path);

  // Ouverture du fichier en écriture (et réinitialisation)
  File myFile = SD.open(fileName, FILE_WRITE);
  if (myFile) {
    myFile.println("# Ceci est le fichier de configuration pour l'application.");
    myFile.println("# Ne modifiez pas le nom des variables (ce qui se trouve avant le signe égale sur une ligne).");
    myFile.println();

    myFile.println("#Le siteID est votre identifiant comme il vous a été donnée par l'enquêteur, ne le modifiez pas s'il ne vous le demande pas.");
    myFile.println("siteID=Cool Food " + String(_getRandomChar(10)) );
    myFile.println();

    myFile.println("# Cette phrase apparaitra dans le fichier résultat à votre questionnaire mais n'est pas visible sur la borne.");
    myFile.println("# Il est conseillé de définir ici une phrase courte.");
    myFile.println("question= Aimez-vous les brocolis ?");
    myFile.println();


  } else {
    DEBUG("Impossible d'ouvrir le fichier '" + String(fileName) + "' sur la carte SD pour écrire dedans");
  }
  myFile.close();
}
