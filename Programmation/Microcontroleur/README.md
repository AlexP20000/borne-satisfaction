## Programme microcontrolleur ##
Dans ce répertoire, se trouve les programmes et librairies du programme du microcontroleur.

## Compilation du programme ##
Afin de pouvoir compiler le programme, il est nécessaire d'installer [l'IDE Arduino](https://www.arduino.cc/en/software) et les cartes ESP32.

### Installation des cartes ESP32 ###
Dans les préférences de l'IDE Arduino (Fichier>Préférences ou [Ctrl] + [,]), ajouter l'URL :
``` https://dl.espressif.com/dl/package_esp32_index.json``` dans les URL de cartes suplémentaires (il est possible d'avoir plusieurs jeux de cartes, il faut les séparer par des virgules), comme sur l'image ci-dessous.
![Ajout des cartes ESP32](./illustrations/Arduino_preferences.png)


Ensuite, dans le menu Tools > Boards manager Recherchez "ESP32" et installez les cartes trouvées.
![Ajout des cartes ESP32](./illustrations/Arduino_ESP32.png)


Dans le menu Tools > Boards, choississez la carte **FireBeetle-ESP32**
![Choix de la carte ESP32](./illustrations/Arduino_CardChoice.png)

### Algorithme du microcontrôleur ###
![Algorithme du microcontrôleur](./illustrations/Diagrams.png)
