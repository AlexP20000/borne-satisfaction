/**
   ----------------------------------------------------------------------------------
   Défintion du deep sleep pour la mise ne palce du wake up lorsqu'on appuie sur un bouton.
   @see https://randomnerdtutorials.com/esp32-deep-sleep-arduino-ide-wake-up-sources/
   ---------------------------------------------------------------------------------- */
void DEEPSLEEP_start() {
  // Calcul du mask de bits pour les GPIO utilisés par les boutons
  int somme = pow(2, BTN_ROUGE) + pow(2, BTN_VERT) + pow(2, BTN_JAUNE); // 33554432 + 67108864 + 268435456 = 234881024
  String chaine = "0x" + String( somme, HEX);
  DEBUG(chaine);

  // On authorise l'appuie sur les boutons à réveiller l'ESP32
  esp_sleep_enable_ext1_wakeup(0xe000000, ESP_EXT1_WAKEUP_ANY_HIGH);

  // Mise en deep sleep
  esp_deep_sleep_start();
}



/**
   ----------------------------------------------------------------------------------
   Renvoie le numéro du GPIO qui a sortie l'ESP du Deep sleep.
   @see https://randomnerdtutorials.com/esp32-deep-sleep-arduino-ide-wake-up-sources/
   ---------------------------------------------------------------------------------- */
int DEEPSLEEP_getGPIOWakeUp(){
  uint64_t GPIO_reason = esp_sleep_get_ext1_wakeup_status();
  
  return (log(GPIO_reason))/log(2); 
}
