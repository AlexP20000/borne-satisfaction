## Le projet ##
Le projet consiste à faire une borne avec 3 boutons poussoirs pouvant enregistrer les appuies sur "Oui", "Non" ou "Ne sait pas" sur une carte SD afin de recueillir des résultats pour une enquête de satisfaction.

### Conventions ###
La carte SD contient plusieurs type de fichiers :
- Fichier de paramétrage (Modifiable par le **gestionnaire**)
- Fichier d'enregistrements des résultats (Généré par le programme).
- Fichier de synthèse des résultats (Généré par le programme).


### Format des fichiers ###

### Fichier paramétrage ###
fichier : **configuration.ini** formaté comme suit :
```
[configuration]
; le siteID est votre identifiant comme il vous a été donnée par **l'enquêteur**, ne le modifiez pas s'il ne vous le demande pas.
siteID=OpenFactory

; Cette phrase apparaitra dans le fichier résultat à votre questionnaire mais n'est pas visible sur la borne.
; Il est conseillé de définir ici une phrase courte.
question=Aimez-vous les artichauds ?
```


### Fichier de synthèse ###
Fichier **YYYYMMDD_recap.txt** (par exemple 20220208_recap.csv) formaté comme suit :


```
Etablissement = Cool Food I23I5V242Q
Date          = 2022/04/05
Question      = Voulez vous manger un plat végétarien une fois par semaine ?
Batterie      = 96%
Nombre d'appuie sur les boutons :
  Rouge = 2
  Vert  = 4
  Jaune = 3
  TOTAL = 9
Pourcentage d'appuie sur les boutons :
  Rouge = 22%
  Vert  = 44%
  Jaune = 33%

```




### Fichiers CSV ###
Fichier **YYYYMMDD_detail.csv** (par exemple 20220208_detail.csv) formaté comme suit :


Exemple d'un fichier 20220208_Mesures.csv

| ID du site | Date | Heure | Question | Oui | Non | Indécis | Niveau Batterie
| ---------- | ---- | ----- | -------- | --- | --- | ----------- | ---------------
| OpenFactory | 08/02/2022 | 12:45:52 | Aimez-vous les artichauds | 1 | 0 | 0 | 90%
| OpenFactory | 08/02/2022 | 12:45:53 | Aimez-vous les artichauds | 1 | 0 | 0 | 90%
| OpenFactory | 08/02/2022 | 12:45:55 | Aimez-vous les artichauds | 0 | 0 | 1 | 90%
| OpenFactory | 08/02/2022 | 20:12:15 | Aimez-vous les artichauds | 0 | 1 | 0 | 50%

