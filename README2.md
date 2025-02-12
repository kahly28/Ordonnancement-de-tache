Bienvenue dans notre projet 

Voila comment compiler ou executer.

- script :

	Pour compiler ./expe il suffit de se trouver dans le dossier project, puis de faire make expe. L'exe se trouvera dans le dossier script, où on pourra lancer les diffèrents scripts.

	- ./run_experiments : nom_du_répertoire nom_fichier_resultat nombre_min_machine nombre_max_machine pas_nombre_machine 

	- ./generate_instance :filename number_of_tasks pareto_parameter

	- ./generate_collection : 



Pour la partie java :

Pour compiler le JNI et obtenir le .dylib il faut faire make jni, le fichier se trouvera dans le dossier java.

Ensuite otut se passera dans le dossier java.

Pour executer le programme il faut ouvrir avec eclipse le dossier Program qui se trouve dans project/java/application. Le programme Java utilisera un script qui lancera la commande qui utiliser le JNI pour calculer l'ordonnancement.

Il faudra placer une instance généré dans le dossier application/src, c'est ici que se trouve un script ( qui sera éxecuter par le projet JavaFX ) qui va effectuer l'ordonnancement et placer le fichier solution dans application/result. 

Dans Eclipse, vous pourrez éxecuter le programme, le fichier instance demandé devra obligatoirement se trouver dans le application/src comme dit précédement et vous generera le diagramme de Gantt.
