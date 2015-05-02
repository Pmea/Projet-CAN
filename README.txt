Avancement du projet :
L'insertion de noeud est terminée
L'insertion de valeur est terminée
La recherche de valeur est terminée
La suppression d'un noeud n'a pas été faite.

Le programme a été testé et toutes les erreurs trouvées ont étés résolues 

Cibles du Makefile :
make
make all
Compilent le programme

make run
Lance le programme avec 10 processus (dont le coordinateur)

make run5
make run10
make run50
make run100
make run200
Lance une execution avec 5, 10, 50, 100 ou 200 processus (dont le coordinateur)

make clean
Supprime les fichiers objets, les fichiers binaires, les sauvegardes et les
fichiers html


Affichage : 
Le noeud coordinateur appelle la fonction "exporter()" à chaque modification de
l'overlay qui demande à chaque noeud d'exporter ses coordonnées, ses zones et
ses données.
Le résultat peut être affichable par un navigateur internet, il suffit d'ouvrir
le fichier produit par l'exécution (execution_date de lancement) 
Attention, l'affichage provoque des ralentissements

