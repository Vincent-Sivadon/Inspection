# Inspection

Projet d'Architecture Interne des Sytèmes d'Exploitation


## Installation

Pour installer la librairie Inspection :
```
sudo make install
```
Les fichiers suivant vont être installés comme :
```
/usr/local/lib/libinspection.so
/usr/local/include/Inspection (toutes les entêtes)
/usr/local/bin/inspection (le binaire à exécuter)
```
La désinstallation se fait par :
```
sudo make uninstall
```
et va supprimer tout les fichiers créés.

## Utilisation

Pour lancer l'analyse d'Inspection sur un executable *bin.exe* :
```
inspection bin.exe
```
On peut ensuite rentrer des commandes parmis :
* `run` : lance le programme bin.exe
* `i` : affiche des informations globales sur le programme lancé
* `getpid`, `getppid`, `getname` : donne les informations mentionnées
* `help` : aide sur l'utilisation (à faire)
* `quit` : ferme l'analyse et nettoie la mémoire (à faire)