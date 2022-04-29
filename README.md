## Le projet ##
Le projet consiste à faire une borne avec 3 boutons poussoirs pouvant enregistrer les appuis 
sur une carte SD afin de recueillir des résultats pour une enquête de satisfaction.

### Conventions ###
La carte SD contient plusieurs type de fichiers :
- Fichier de configuration (Modifiable par le **gestionnaire**)
- Fichier d'enregistrements des résultats (Généré par le programme).
- Fichier de synthèse des résultats (Généré par le programme).


### Fichier de configuration ###
fichier : **configuration.ini** formaté comme suit :
```
# Ceci est le fichier de configuration pour l'application 'Compteur de vote'.
# Ne modifiez pas le nom des variables (ce qui se trouve avant le signe egale sur une ligne).
# Vous pouvez modifier le texte se trouvant apres le signe egale a votre guise.
#____________________________________________________________________________________________
[config]

# Le siteID est votre identifiant comme il vous a ete donnee par l'enqueteur,
# ne le modifiez pas s'il ne vous le demande pas.
siteID=Cool Food UOF

# Cette phrase apparaitra dans le fichier resultat à votre questionnaire mais n'est pas visible sur la borne.
# Il est conseille de definir ici une phrase courte.
question=Aimez-vous faire des tests sur cette borne ?

# Si vous avez besoin de mettre la date à l'heure dans la borne, c'est ici.
# Pour la mise à l'heure, décommentez (supprimez le # en début de ligne) et 
# remplissez les champs suivant avec des valeurs numériques uniquement.
# Une fois la mise à l'heure faite, les lignes seront automatiquement commentées.
#year=2022
#month=04
#day=27
#hour=14
#minute=56
```


### Fichier de synthèse ###
Fichier **YYYY-MM-DD_recap.txt** (par exemple 2022-04-27_recap.txt) formaté comme suit :


```
Etablissement = Cool Food I23I5V242Q
Date          = 2022/04/05
Question      = Voulez vous manger un plat végétarien une fois par semaine ?
Batterie      = 96%
Nombre d'appui sur les boutons :
  Rouge = 2
  Vert  = 4
  Jaune = 3
  TOTAL = 9
Pourcentage d'appui sur les boutons :
  Rouge = 22%
  Vert  = 44%
  Jaune = 33%

```




### Fichiers CSV ###
Fichier **YYYY-MM-DD_detail.csv** (par exemple 2022-04-27_detail.csv) formaté comme suit :


Exemple d'un fichier 20220208_Mesures.csv

| ID du site | Date | Heure | Question | Vert | Rouge | Jaune | Niveau Batterie
| ---------- | ---- | ----- | -------- | --- | --- | ----------- | ---------------
| OpenFactory | 08/02/2022 | 12:45:52 | Aimez-vous les artichauds | 1 | 0 | 0 | 90%
| OpenFactory | 08/02/2022 | 12:45:53 | Aimez-vous les artichauds | 1 | 0 | 0 | 90%
| OpenFactory | 08/02/2022 | 12:45:55 | Aimez-vous les artichauds | 0 | 0 | 1 | 90%
| OpenFactory | 08/05/2022 | 20:12:15 | Aimez-vous les artichauds | 0 | 1 | 0 | 50%