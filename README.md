## Le projet ##
Le projet consiste à faire une borne avec 3 boutons poussoirs pouvant enregistrer les appuies sur "Oui", "Non" ou "Ne sait pas" sur une carte SD afin de recueillir des résultats pour une enquête de satisfaction.

### Conventions ###
La carte SD contient 2 fichiers :
- Fichier de paramétrage (Modifiable par le **gestionnaire**)
- Fichier d'enregistrement des résultats (Non modifiable par le **gestionnaire**).


### Format des fichiers ###

#### Fichier paramétrage ####
fichier : **params.ini** formaté comme suit :
```
[configuration]
; le siteID est votre identifiant comme il vous a été donnée par **l'enquêteur**, ne le modifiez pas s'il ne vous le demande pas.
siteID=OpenFactory

; Cette phrase apparaitra dans le fichier résultat à votre questionnaire mais n'est pas visible sur la borne.
; Il est conseillé de définir ici une phrase courte.
question=Aimez-vous les artichauds ?
```


#### Fichier de synthèse ####
Fichier **YYYYMMDD_Synthese.csv** (par exemple 20220208.csv) formaté comme suit :

A définir.

```
[Synthese]
Nombre Oui= 15
Nombre Non= 10
Nombre indefini= 3
Nombre totale de réponse: 28
```




#### Fichiers CSV ####
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
