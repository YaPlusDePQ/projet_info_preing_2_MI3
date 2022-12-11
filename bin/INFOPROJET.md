<!--








 /!\ Faire Ctrl-Maj-V /!\ 
 
 
 
 
 
 
 
 
 
 
 -->
# Convention de code du projet

* On ne va pas bidouiller sur le travail des autres sans leurs autorisations.
* Le langage du code est **l'anglais**.
* Nomenclature
    * On utilise le CamelCase pour tous les noms (variables, fonctions, types, fichier....).
    ```C
    void MyFonction(...){}; 
    int MyVariable;
    ```
    * Les defines et macros sont strictement en majuscule.
    * Les fonctions qui sont créées spécifiquement pour une autre fonction (sous fonction) et qui ne doivent pas être appelées dans un autre contexte 
    possèderont le préfixe '\_'. exemple: 
    ```C
    int _SousFonctionRecurcive(...){}
    ```
    * **TABULATION À CHAQUE OUVERTURE DE {.**
* Commentaires
    * Commenter régulièrement surtout les codes complexes.
    * Toutes les fonctions doivent posséder une description de la forme suivante:
    ```C
    /**
    *  \brief [resumé de la fonction]
    *
    *  \param [nom paramètre 1] [info sur le paramètre 1]
    *  ...
    *
    *  \return [info sur la valeur retourné]
    */
    ```
    * Tout édit fait par quelqu'un sur la partie d'un autre devra être précisé par un commentaire avec l'auteur, la raison et la date+h.
    ```C 
    // seg fault si -1 -- Razu 11/12 1:09
    ```
* Lisibilité de l'exécution
    * Des printf réguliers dans les fonctions pour afficher la progression dans du code dans la console et détecter rapidement des seg. fault.
    * Chaque printf qui **n'est pas dans le main** devra indiquer sa fonction d'origine. 
    ```C 
    printf("[MyFonction] ...");
    ```

# GitHub
_git doit être installé bien sur. si c'est pas le cas c'est ici_

## Set up
Le lien de la repositorie git est la https://github.com/YaPlusDePQ/projet_info_preing_2_MI3.git.<br />
Une fois placé dans le dossier voulu, éxécuter la commande suivante pour charger la repositorie.
```
git clone https://github.com/YaPlusDePQ/projet_info_preing_2_MI3.git
```
Puis utiliser la commande suivante pour créé un mot de référence à la repositorie pour les future commande.
```
git remote add [nom] https://github.com/YaPlusDePQ/projet_info_preing_2_MI3.git
```

## Liste des commandes 
    
| Commande  | Action |
| ------------- |:-------------:|
| git add [fichier(s) ou . (pour inclure le dossier entier)] |ajoute les fichiers indiqués au prochain commit |
| git commit -m "[message]" | crée le commit prêt à être push sur la repositorie |
| git push [remote nom] master | publie le commit |
| git clone [url] | télécharge la repositorie |
| git remote -v | donne le nom de référence |

Si personne travaille en même sur le meme fichier (ce qui devrait normalement jamais arriver) **ne pas** forcer avec les pull et push et aller manuellment sur la repositorie pour constater les differents changements. 

# Conseils de développements

* On teste son code régulièrement aka on le compile régulièrement.
* Quand on écrit une fonction on l'a test **individuellement**.
* Question => Google **toujours rechercher en anglais et en précisant son langage à la fin**. Penser à prioriser StackOverflow pour les résultats.
* La phrase "c'est pas possible" n'existe pas en C.
* S'il y a blocage sur un code prendre une pause de 10 min.