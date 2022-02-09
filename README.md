## Le projet ##
Le projet consiste � faire une borne avec 3 boutons poussoirs pouvant enregistrer les appuies sur "Oui", "Non" ou "Ne sait pas" sur une carte SD afin de recueillir des r�sultats pour une enqu�te de satisfaction.

### Conventions ###
La carte SD contient 2 fichiers :
- Fichier de param�trage (Modifiable par le '''gestionnaire''')
- Fichier d'enregistrement des r�sultats (Non modifiable par le '''gestionnaire''').


### Format des fichiers ###
#### Fichier param�trage ####
fichier : '''params.ini''' format� comme suit :
```
[configuration]
; le siteID est votre identifiant comme il vous a �t� donn�e par '''l'enqu�teur''', ne le modifiez pas s'il ne vous le demande pas.
siteID#OpenFactory

; Cette phrase apparaitra dans le fichier r�sultat � votre questionnaire mais n'est pas visible sur la borne.
; Il est conseill� de d�finir ici une phrase courte.
question#Aimez-vous les artichauds
```



#### Fichier csv ####
Fichier '''YYYMMDD.csv''' (par exemple 20220208.csv) format� comme suit :


Exemple d'un fichier 20220208.csv

| ID du site | Timestamp | Question | Oui | Non | Ne sait pas | Niveau Batterie
| ---------- | --------- | -------- | --- | --- | ----------- | ---------------
| OpenFactory | 08/02/2022 12:45:52 | Aimez-vous les artichauds | 1 | 0 | 0 | 90%
| OpenFactory | 08/02/2022 12:45:53 | Aimez-vous les artichauds | 1 | 0 | 0 | 90%
| OpenFactory | 08/02/2022 12:45:55 | Aimez-vous les artichauds | 0 | 0 | 1 | 90%
| OpenFactory | 08/02/2022 20:12:15 | Aimez-vous les artichauds | 0 | 1 | 0 | 50%


Exemple d'un fichier 20220209.csv

| ID du site | Timestamp | Question | Oui | Non | Ne sait pas | Niveau Batterie
| ---------- | --------- | -------- | --- | --- | ----------- | ---------------
| OpenFactory | 09/02/2022 20:12:15 | Aimez-vous les plats gratin�s | 0 | 1 | 0 | 40%
| OpenFactory | 09/02/2022 20:12:15 | Aimez-vous les plats gratin�s | 1 | 0 | 0 | 40%
| OpenFactory | 09/02/2022 20:12:15 | Aimez-vous les plats gratin�s | 1 | 0 | 0 | 30%



## Programmes ##
### Clignotement des LEDs ###
Il y a 3 LEDs sur la borne, chacune au-dessus d'un bouton afin d'indiquer que le vote d'un '''utilisateur''' a bien �t� pris en compte. Il est �galement possible d'afficher des alarmes en fonction du clignotement des LEDs.



| Leds clignotante (une � la fois) | Signification
|----------------------------------|---------------
| Vert | tout est OK
| Rouge | Batterie faible
| Rouge, Jaune | Pas de carte SD
| Rouge, Vert | Fichier param�trage non valide.
| Rouge, Vert, Jaune | Erreur inconnue.




### Algorithme du microcontr�leur ###
![Algorithme du microcontr�leur](./doc/Diagrams.png)


fonctionnement :
* si bouton appuy�.
  * Wake up.
  * Allumage de la LED du bouton
  * Lecture "Time + Date" via RTC
  * Lecture niveau batterie (conversion en %)
  * Lecture fichier params.ini pour r�cup�rer la question + siteID
  * Ouverture fichier csv : YYYYMMDD.csv en append (�criture � la fin)
  * Formatage et �criture la ligne dans le fichier CSV
  * Pause "anti-rebond".
* Eteind les LEDs (On �teint toutes les Leds, sans chercher laquelle est allum�e).


Pour la partie '''Faut-il faire les tests''' voir les possibilit�s techniques :

# Voir s'il est possible de savoir qu'on vient de mettre sous tension le microcontr�leur (et non pas qu'on sort d'un Deep sleep).
Oui, la fonction esp_sleep_get_wakeup_cause() permet de savoir pourquoi l'ESP � reboot� : 
* ESP_SLEEP_WAKEUP_EXT0 : r�veil de deep sleep � partir d'un  signal ext�rieur (RTC IO)
* ESP_SLEEP_WAKEUP_EXT1 : r�veil de deep sleep � partir d'un parmi plusieurs signaux ext�rieurs (RTC IO) (Utilis� par la borne)
* ESP_SLEEP_WAKEUP_TIMER : r�veil par le timer interne (au bout d'un certain temps
* ESP_SLEEP_WAKEUP_TOUCHPAD : r�veil par une touche tactile
* ESP_SLEEP_WAKEUP_ULP : r�veil par un programme de l'ULP
* Si aucune des autres : reboot du � une coupure d'alimentation
