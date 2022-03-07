#include "libs/FS/src/FS.h";
#include "libs/SD/src/SD.h";
#include "libs/SPI/src/SPI.h";


/**
   ----------------------------------------------------------------------------------
   Ajout d'une ligne à la fin du fichier.
  ---------------------------------------------------------------------------------- */
void SD_appendFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    DEBUG("Failed to open file for appending");
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
   Ex : SD_readFile(SD, "/hello.txt")
  ---------------------------------------------------------------------------------- */
void SD_readFile(fs::FS &fs, const char * path){
  File file = fs.open(path);
  if(!file){
    DEBUG("Failed to open file for reading");
    return;
  }

  DEBUG("Read from file: ");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}


/**
   ----------------------------------------------------------------------------------
   test l'existance d'un fichier.
   Ex : SD_existeFile(SD, "/hello.txt")
  ---------------------------------------------------------------------------------- */
boolean SD_existeFile(fs::FS &fs, const char * path){
  File file = fs.open(path);
  if(!file){
    DEBUG("Failed to open file for reading");
    return false;
  } else {
    return true;
  }
}
