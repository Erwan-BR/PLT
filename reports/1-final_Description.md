# Jalon 1.2 : Description et Conception des états

## Les états d'une partie

Pendant la partie, il y a trois phases possibles :

- DRAF

- PLANIFICATION

- PRODUCTION

### Phase de DRAFT

Pendant cette phase, il va y avoir 7 étapes consécutives qui seront les mêmes, à la différence près du nombre de cartes.

Chaque joueur voit afficher à son écran 7 cartes, et il doit en choisir une qu'il décidera d'ajouter à son empire par la suite. Une fois que chaque joueur a fait et validé son choix, les mains tournent dans le sens horaire (ou anti-horaire selon le numéro du tour actuel), puis chaque joueur doit faire un choix similaire avec 6 cartes, puis 5, etc.
Une fois toutes les cartes sélctionnées, on passe automatiquement en phase de PLANIFICATION.

### Phase de PLANIFICATION

Pendant cette phase, chaque joueur a la possibilité de défausser autant de cartes qu'il le souhaite afin de gagner les gains de défausse associés aux cartes. Ces jetons lui sont utiles pour construire les différents bâtiments qu'il possède. Une fois que chaque joueur a validé le fait qu'il ne veut plus défausser de carte, on passe à la phase suivante.

### Phase de PRODUCTION

Pendant cette phase, il y aura une production de 5 ressources à la suite. Pour chaque ressource, chaque joueur reçoit la quantité qu'il est capable de produire, et il peut placer ses ressources ou il le souhaite. Il y a une particularité pour le joueur produisant le plus d'une ressource, car il gagne un point de victoire en plus. Une fois que chaque joueur confirme avoir terminé, la ressource suivante est produite, et ce, jusqu'à avoir terminé de produire les 5 types de ressources. Une fois terminé, un nouveau tour commence et on retourne à la phase de DRAFT.

## Les états d'un joueur

Il y a deux états possibles pour un joueur :

- PENDING

- PLAYING

### PENDING

Cet état est actif si lorsqu'un joueur a terminé de jouer ([choix de la carte de draft/choix des cartes à défausser/placement des ressources] terminé). Il est dans cet état lorsqu'il a validé ses actions, et qu'au moins un autre joueur n'a pas terminé les siennes. Une fois que tous les joueurs sont dans cet état, la partie va alors effectuer l'action suivante quelle que soit la phase, et mettre chaque joueur dans l'état PLAYING.

### PLAYING

Cet état est actif si le joueur n'a pas encore validé son action en cours (choix de la carte de draft, choix des cartes à défausser, placement des ressources). Cet état est quitté lorsque le joueur confirme avoir terminé son action en cours.
