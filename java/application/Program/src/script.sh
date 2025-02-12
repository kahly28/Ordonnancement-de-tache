#!/bin/bash



#Vérif nombre de paramètre : 

echo "$#"

if [ $#  -ne 5 ]; then
	echo "Ce script necessite 3 parametre : "
    echo "fichier IN, fichier OUT , nbMachine , preemption , balance"
    exit 1
fi

if [ ! -e $1 ]; then
	echo "Le premier parametre doit etre un fichier texte existant"
	exit 1
fi

if [[ ! $4 =~ ^[0-9]+$ ]]; then
	echo "Preemption : 0 ou 1"
	exit 1
fi

if [[ ! $5 =~ ^[0-9]+$ ]]; then
	echo "balance : 0 ou 1"
	exit 1
fi



#java -Djava.library.path=. application.MyMain 10_0.1_1.txt result.txt 3 1 1
java -Djava.library.path=. application.MyMain $1 $2 $3 $4 $5

if [ $? -eq 0 ]; then
    # Déplacer le fichier de sortie vers un autre répertoire
    destination="application/result/"
    mv "$2" "$destination"
    echo "Le fichier a été déplacé vers $destination"
else
    echo "La commande Java a échoué"
fi
