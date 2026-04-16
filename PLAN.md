# Plan d'Action - cub3D

Ce document détaille l'analyse exhaustive du projet et définit la feuille de route pour sa finalisation et sa stabilisation.

## 1. Analyse Technique & État des Lieux

### Architecture
- **Parsing :** Basé sur une lecture ligne par ligne (`GNL`). Les paramètres (textures, couleurs) sont extraits avant la carte.
- **Rendu :** Moteur DDA standard implémenté dans `to_3d.c`. Le dessin se fait colonne par colonne dans `draw.c`.
- **Mouvement :** Gestion multi-touches via un tableau `keys[1024]` dans `keyhook.c`.

### Problèmes Critiques Identifiés
- [ ] **Validation de la Carte (Incomplète) :** La fonction `verify_border` dans `verify_map.c` est commentée. Le projet accepte actuellement des cartes ouvertes, ce qui est contraire au sujet.
- [ ] **Textures Hardcodées :** La taille des textures est fixée à 1024x1024 dans `draw.c`. Si une texture a une dimension différente, l'affichage sera erroné ou causera un crash.
- [ ] **Contrôles Non Standard :** Les touches A et D tournent la caméra au lieu de "strafer" (pas de côté). Les flèches directionnelles devraient gérer la rotation.
- [ ] **Performance du Rendu :** L'utilisation de `mlx_get_image_pixel` dans la boucle de rendu est inefficace. Il est préférable d'accéder directement au buffer de données de l'image.
- [ ] **Robustesse du Parsing :** Pas de vérification pour les doublons d'identifiants (ex: deux lignes `NO`).
- [ ] **Gestion de la Mémoire :** Certains `exit(1)` dans `init_mlx.c` pourraient court-circuiter le nettoyage des ressources déjà allouées.

## 2. Feuille de Route (Plan de Développement)

### Étape 1 : Robustesse du Parsing (Priorité Haute)
- [ ] Réactiver et implémenter `verify_border` (via un algorithme de Flood Fill ou vérification de voisinage).
- [ ] Ajouter une détection de doublons pour les textures et couleurs.
- [ ] S'assurer que chaque paramètre obligatoire (NO, SO, WE, EA, F, C) est présent une et une seule fois.
- [ ] Gérer les dimensions dynamiques des textures (récupérer `width`/`height` lors du chargement).

### Étape 2 : Amélioration du Moteur de Rendu (Priorité Moyenne)
- [ ] Optimiser l'accès aux pixels des textures (utiliser `mlx_get_image_data`).
- [ ] Implémenter le "strafing" (touches A et D pour le mouvement latéral).
- [ ] Mapper les flèches gauche/droite pour la rotation de la caméra.
- [ ] Ajouter une gestion propre des erreurs de chargement de fichiers JPG.

### Étape 3 : Finalisation & Nettoyage (Priorité Basse)
- [ ] Centraliser toutes les sorties d'erreurs vers `cleanup_and_exit`.
- [ ] Vérifier la conformité à la Norme 42 (fonctions < 25 lignes, max 5 fonctions/fichier).
- [ ] Tests intensifs avec `valgrind` pour garantir l'absence de fuites mémoire.

## 3. Guide de Test
- `maps/valid.cub` : Doit se lancer normalement.
- `maps/open.cub` : Doit être rejeté avec une erreur explicite.
- `maps/wrong_ext.txt` : Doit être rejeté (extension invalide).
- `maps/duplicate.cub` : Doit être rejeté (doublons de configuration).
