#include "FS.h"
#include "SD.h"
#include "SPI.h"


/**
   ----------------------------------------------------------------------------------
   Ajout d'une ligne à la fin du fichier.
  ---------------------------------------------------------------------------------- */
void SD_appendFile(fs::FS &fs, const char * path, const char * message) {
  DEBUG("Appending to file: %s\n", path);

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
