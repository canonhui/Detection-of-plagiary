Dététection de plagiat avec distance d'édition

Questions venant du site suivant:
  https://perso.esiee.fr/~coustyj/Sequences/IT-4301E-TDm2.html

Pour compiler le programme et tester le résultat, il n'y a rien de plus simple que ça. Tout ce qu'il faut c'est justement de passer au programme deux fichier, comprenant au dedans deux textes que vous voulez tester. Il faut faire attention que l'on ne peut pas tester les deux questions en une même compilation. Le programme peut décider automatiquement de faire la question 3 ou la question 4, selon le contenu des textes. Alors pour tester question 3, il ne faut pas mettre aucun symbol '\n' dans tous les deux textes. Une fois que le programme détecte l'existance de '\n' dans quelconque texte, il va exécuter des phrases répondant question 4. 

Pour question 3, le programme affichera les textes originaux, avec la fonction "affiche". Et puis il affichera le score d'un alignement optimal et en final l'alignement optimal avec le formattage simultané.

Alors pour question 4, le programme affichera aussi les textes originaux, mais justement avec la fonction "printf", car c'est pas très joli d'imprimer un texte contenant de symbols '\n' en formattage simultané. après vous apercevrez fortement le même résultat du figure 2 sur le site du TDm.

Il y a 8 fichiers de texte dans le répertoire pour tester le résultat. Les fichiers a31, a32, b31, b32 sont réservé au question 3, alors que a41, a42, b41, b42 sont pour question 4. Normalement, il faut mettre les fichiers débutant avec le même caractère dans le même groupe de teste, mais vous pourriez absolument aussi regrouper quelconques 2 fichiers. (Attention: les textes b41 et b42 sont un peu lourds, veuillez jeter un oeil　au-dessus avant d'en servir pour tester.)

Une petite note: comme le programme traite plusieurs symbols '\n' consécutifs comme un seul '\n', dans le résultat de question 4, la longueur du texte ne prend pas en compte de symbols '\n'.

Commandes pour compiler le programme:
	$ cd <chemin du fichier C>
	$ gcc -o plagiat plagiat.c
	$ ./plagiat <fichier1> <fichier2> 

S'il y a des questions ou des bugs dans le programme, veuillez me les avertir ^O^

