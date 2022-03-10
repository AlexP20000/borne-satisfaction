/**
 * @Author : Alexandre PERETJATKO
 */
/**
   ----------------------------------------------------------------------------------
   Renvoie le niveau de la batterie en pourcentage (sans le signe).
   ---------------------------------------------------------------------------------- */
int BATTERIE_getBatterieLevel() {
  float mesure_MAX = 603;
  float mesure_MIN = 250; // <- A fixer

  // Renvoie la tension
  int tension = (int) analogRead(A0);
  DEBUG ("Mesure analogique renvoyee par la batterie:  " + String(tension));


  // Calcul du pourcentage
  // On ne garde que la partie entière de la valeur
  int pourcent = (int) 100 / (mesure_MAX - mesure_MIN) * (tension - mesure_MIN);

  return pourcent;
}
