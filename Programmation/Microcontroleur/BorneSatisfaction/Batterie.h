/**
   @Author : Alexandre PERETJATKO
*/
/**
   ----------------------------------------------------------------------------------
   Renvoie le niveau de la batterie en pourcentage (sans le signe).
   Protection contre des valeurs négatifs du pourcentage (si < 0, on renvoie 0 )
   ---------------------------------------------------------------------------------- */
int BATTERIE_getBatterieLevel() {
  float mesureTensionMAX = 2368;   // <- A fixer
  float mesureTensionMIN = 250; // <- A fixer

  // Renvoie la tension
  int tension = (int) analogRead(A0);
  DEBUG ("Mesure analogique renvoyee par la batterie:  " + String(tension));


  // Calcul du pourcentage
  // On ne garde que la partie entière de la valeur
  int pourcent = (int) 100 / (mesureTensionMAX - mesureTensionMIN) * (tension - mesureTensionMIN);
  if( pourcent < 0 ) {
    pourcent = 0;
  }
  
  return pourcent;
}
