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


# Analyse

Il va falloir trois binaires pour avoir un système fonctionnel.

1. generator :
  * Obligatoire -> Créer les fichiers contenant les nombres entiers dans un répertoire donné en argument
  * Facultatif  -> Choisir la vitesse de création via les arguments

2. unificator :
  * Obligatoire -> Lire le répertoire contenant les fichiers et envoyer via une socket des informations de traitement (objet de l'énoncé)

3. tablodebor
  * Obligatoire -> Lire les informations envoyés par unificator et les afficher sur la console


# TODO

* Gérer les arguments en entrée des binaires
* Implémenter et utiliser les sockets
* Implémenter tablodebor
* Faire de unificator un daemon
* Faire de generator un daemon
* Tester le tout avec valgrind et cachegrind