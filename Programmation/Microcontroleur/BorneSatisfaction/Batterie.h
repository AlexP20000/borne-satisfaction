/**
   @Author : Alexandre PERETJATKO
*/
/**
 -----------------------------------------------------------------------------------------
Renvoie le niveau de la batterie en pourcentage (sans le signe).
issue 10 :
  Protection contre des valeurs négatifs du pourcentage (si < 0, on renvoie 0 ) et si on a 
  un pourcent > 100
------------------------------------------------------------------------------------------ */
int BATTERIE_getBatterieLevel() {
  float mesureTensionMAX = 2425;
  float mesureTensionMIN = 1725;

  // Renvoie la tension
  int tension = (int) analogRead(A0);
  DEBUG ("Mesure analogique renvoyee par la batterie:  " + String(tension));


  // Calcul du pourcentage
  // On ne garde que la partie entière de la valeur
  int pourcent = (int) 100 / (mesureTensionMAX - mesureTensionMIN) * (tension - mesureTensionMIN);
  if( pourcent < 0 ) {
    return 0;
  }
  if( pourcent > 100 ) {
    return 100;
  }
  return pourcent;
}
