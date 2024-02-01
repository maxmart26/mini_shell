# mini_shell

chose a faire 
Afficher une invite lors de l'attente d'une nouvelle commande.

• Avoir un historique fonctionnel.

• Rechercher et lancer l'exécutable approprié (en se basant sur la variable PATH ou en utilisant un chemin relatif ou absolu).

• Éviter d'utiliser plus d'une variable globale pour indiquer la réception d'un signal. Considérez les implications : cette approche garantit que votre gestionnaire de signaux n'accédera pas à vos principales structures de données.

Ne pas interpréter les guillemets non fermés ni les caractères spéciaux qui ne sont pas requis par le sujet, tels que \ (barre oblique inverse) ou ; (point-virgule).

• Gérer ' (apostrophe) pour empêcher le shell d'interpréter les métacaractères dans la séquence entre guillemets.

• Gérer " (guillemet double) pour empêcher le shell 
d'interpréter les métacaractères dans la séquence entre guillemets, à l'exception de $ (signe dollar).

• Mettre en œuvre les redirections :
  ◦ < doit rediriger l'entrée.
  ◦ > doit rediriger la sortie.
  ◦ << doit être suivi d'un délimiteur, puis lire l'entrée jusqu'à ce qu'une ligne contenant le délimiteur soit rencontrée. Cependant, cela n'a pas à mettre à jour l'historique !
  ◦ >> doit rediriger la sortie en mode ajout.

• Mettre en œuvre les pipes (caractère |). La sortie de chaque commande dans la canalisation est connectée à l'entrée de la commande suivante via un tube.

• Gérer les variables d'environnement ($ suivi d'une séquence de caractères) qui doivent se développer à leurs valeurs.

• Gérer $? qui doit se développer jusqu'à l'état de sortie de la dernière canalisation avant-plan exécutée.

• Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent se comporter comme dans bash.

• En mode interactif :
  ◦ ctrl-C affiche une nouvelle invite sur une nouvelle ligne.
  ◦ ctrl-D quitte le shell.
  ◦ ctrl-\ ne fait rien.
  
• Votre shell doit mettre en œuvre les commandes intégrées suivantes :
  ◦ echo avec l'option -n
  ◦ cd avec uniquement un chemin relatif ou absolu
  ◦ pwd sans options
  ◦ export sans options
  ◦ unset sans options
  ◦ env sans options ni arguments
  ◦ exit sans options