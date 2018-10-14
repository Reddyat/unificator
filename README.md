# Énoncé

* A partir d’un répertoire (chemin en argument) pouvant contenir plusieurs milliers de fichiers texte (.txt) qui arrivent au fur et à mesure (atomicité implicite)  avec un « débit » nominal de plusieurs centaines de fichiers par seconde

* Chaque fichier contient une liste de nombres entiers séparés par un retour chariot

* L'objectif est d'identifier le plus rapidement possible si pour chaque fichier traité il existe un élément dupliqué

* Communiquer via UDP (ip et port en argument) « au fil de l'eau » le nom des fichiers qui possèdent au moins un élément (nombre) dupliqué, la liste des nombres dupliqués et le temps de traitement du fichier

* Nous attendons un programme C compilable sous Linux


### Quelques indications :

 
* Il n'y a pas de bonne ou mauvaise réponse

* Si besoin de précisions, nous sommes disponibles

* Si possible mettre le code à disposition sur un github (même en cours de développement)

* Il n’y a pas d’impératif de temps : nous préférons disposer d’une base fonctionnelle


# Documentation

## generator

### Description

Type : binaire C

Permet de créer environ un millier de fichiers par seconde dans un répertoire passé en argument.
Chacun de ces fichiers contient 5000 nombres séparés par des sauts de ligne.
Les nombres vont de 0 à la valeur maximale renvoyée par la fonction rand() (RAND_MAX).

### Usage

./generator -o <output_directory>

**Remarque** :

  * l'option -o est obligatoire ;

  * si le répertoire spécifié n'existe pas, il sera créé.
 
### Exemple

./generator -o working

## unificator

### Description

Type : binaire C

Effectue les actions suivantes pour chaque fichier présent dans le répertoire spécifié en paramètre :

  * lis le contenu du fichier ;
  * cherche des nombres dupliqués ;
  * si des duplicats sont trouvés :
    - envoie le nom du fichier, les duplicats et le temps de traitement sur l'ip et le port spécifiés en paramètre (UDP) ; 
  * supprime le fichier.

### Usage

./unificator -d <input_directory> -i <ip> -p <port>

**Remarque** :

  * les trois options sont obligatoires ;
  * si le répertoire indiqué n'existe pas il sera créé.

### Exemple

./unificator -d working -i 127.0.0.1 -p 4242

## tablodebor.py

### Description

Type : script python3

Ecoute sur l'ip et le port spécifié en paramètre et écrit sur la sortie standard
tous les messages reçus séparés par des sauts de ligne.

### Usage

./tablodebor.py -i <ip> -p <port>

### Exemple

./tabblodebor.py -i 127.0.0.1 -p 4242

# Compilation

1 - git clone https://github.com/Reddyat/unificator.git
2 - cd unificator
3 - make

# Lancement

Ouvrez trois terminals différents et exécutez un outil par terminal dans l'ordre suivant :

1 - ./tablodebor.py -i 127.0.0.1 -p 4242
2 - ./unificator/unificator -d working -i 127.0.0.1 -p 4242
3 - ./generator/generator -o working

Dans le terminal de tablodebor devrait s'afficher les duplicats trouvés par unificator.