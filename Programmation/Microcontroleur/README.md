# Programme microcontrolleur #
Dans ce répertoire, se trouvent les programmes et librairies utilisées par l'ESP32.


# Compilation du programme #
Afin de pouvoir compiler le programme, il est nécessaire d'installer [l'IDE Arduino](https://www.arduino.cc/en/software) et les cartes ESP32.

## Installation des cartes ESP32 ##
Dans les préférences de l'IDE Arduino (Fichier>Préférences ou [Ctrl] + [,]), ajouter l'URL :
``` https://dl.espressif.com/dl/package_esp32_index.json ``` dans les URL de cartes suplémentaires (il est possible d'avoir plusieurs jeux de cartes, il faut les séparer par des virgules), comme sur l'image ci-dessous.
![Ajout des cartes ESP32](./illustrations/Arduino_preferences.png)

Ensuite, dans le menu Tools > Boards manager Recherchez "ESP32" et installez les cartes trouvées.
![Ajout des cartes ESP32](./illustrations/Arduino_ESP32.png)


Dans le menu Tools > Boards, choississez la carte **FireBeetle-ESP32**
![Choix de la carte ESP32](./illustrations/Arduino_CardChoice.png)

## Installation des librairies utilesnt à la compilation ##
Toutes les librairies utiles se [trouvent ici](./libs/README.md)


# Fichiers sur la carte SD #
La carte SD contient plusieurs type de fichiers :
- Fichier de paramétrage (Modifiable par le **gestionnaire**)
- Fichier d'enregistrements des résultats (Non modifiable par le **gestionnaire**).
- Fichier de synthèse des résultats (Non modifiable par le **gestionnaire**).


## Format des fichiers ##

### Fichier paramétrage ###
fichier : **params.ini** formaté comme suit :
```
[configuration]
; le siteID est votre identifiant comme il vous a été donnée par **l'enquêteur**, ne le modifiez pas s'il ne vous le demande pas.
siteID=OpenFactory

; Cette phrase apparaitra dans le fichier résultat à votre questionnaire mais n'est pas visible sur la borne.
; Il est conseillé de définir ici une phrase courte.
question=Aimez-vous les artichauds ?
```


### Fichier de synthèse ###
Fichier **YYYYMMDD_Synthese.csv** (par exemple 20220208.csv) formaté comme suit :

A définir.

```
[Synthese]
Nombre Oui= 15
Nombre Non= 10
Nombre indefini= 3
Nombre totale de réponse: 28
```




### Fichiers CSV ###
Fichier **YYYYMMDD_Mesures.csv** (par exemple 20220208.csv) formaté comme suit :


Exemple d'un fichier 20220208_Mesures.csv

| ID du site | Date | Heure | Question | Oui | Non | Ne sait pas | Niveau Batterie
| ---------- | ---- | ----- | -------- | --- | --- | ----------- | ---------------
| OpenFactory | 08/02/2022 | 12:45:52 | Aimez-vous les artichauds | 1 | 0 | 0 | 90%
| OpenFactory | 08/02/2022 | 12:45:53 | Aimez-vous les artichauds | 1 | 0 | 0 | 90%
| OpenFactory | 08/02/2022 | 12:45:55 | Aimez-vous les artichauds | 0 | 0 | 1 | 90%
| OpenFactory | 08/02/2022 | 20:12:15 | Aimez-vous les artichauds | 0 | 1 | 0 | 50%


Exemple d'un fichier 20220209_Mesures.csv

| ID du site | Date | Heure | Question | Oui | Non | Ne sait pas | Niveau Batterie
| ---------- | ---- | ----- | -------- | --- | --- | ----------- | ---------------
| OpenFactory | 09/02/2022 | 20:12:15 | Aimez-vous les plats gratinés | 0 | 1 | 0 | 40%
| OpenFactory | 09/02/2022 | 20:12:15 | Aimez-vous les plats gratinés | 1 | 0 | 0 | 40%
| OpenFactory | 09/02/2022 | 20:12:15 | Aimez-vous les plats gratinés | 1 | 0 | 0 | 30%



# Programmes #




## Algorithme du microcontrôleur ##
![Algorithme du microcontrôleur](./illustrations/Diagrams.png)
