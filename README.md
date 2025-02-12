Simulation de l'Exécution Parallèle de Tâches avec Préemption

Réalisé par : Ahmet KALYONCU et Ahlem BELHADJ

Ce projet porte sur la simulation d'ordonnancement de tâches sur un système avec plusieurs machines parallèles. L'accent est mis sur la gestion de la préemption, qui consiste à interrompre l'exécution d'une tâche pour l'affecter ultérieurement, afin d'optimiser l'utilisation des ressources et de réduire la durée totale des ordonnancements.

Fonctionnalités principales

Simulation de l'ordonnancement en utilisant deux modes :
- Préemptif : les tâches peuvent être interrompues et déplacées vers d'autres machines.
- Non-préemptif : les tâches sont exécutées jusqu'à leur achèvement sans interruption.

Algorithmes utilisés :
- Shortest Processing Time (SPT) : priorité donnée aux tâches avec la plus courte durée.
- Shortest Remaining Processing Time (SRPT) : priorité aux tâches ayant le temps restant le plus court.

Structures de données :
- Listes doublement chaînées : pour représenter les tâches et leur état.
- Arbres binaires de recherche (équilibrés et non équilibrés) : utilisés pour gérer la file d'attente et les événements.

Ce projet a permis d'explorer les complexités de la planification des tâches avec préemption et de mieux comprendre les défis liés à l'ordonnancement.
