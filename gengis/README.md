# Geometry Editor

Éditeur graphique de géométrie utilisant la bibliothèque libsx.

## Fonctionnalités

### 1. Mode Création de Polygones
- Cliquez pour ajouter des sommets au polygone
- Pour fermer un polygone : cliquez près du premier point
- Les polygones sont dessinés en **bleu**

### 2. Mode Création de Segments
- Cliquez sur deux points pour créer un segment
- Vous pouvez cliquer sur des points existants ou créer de nouveaux points
- Les segments sont dessinés en **vert**

### 3. Mode Création de Liens
- Cliquez sur deux points **existants** pour créer un lien
- Les liens sont dessinés en **rouge pointillé**
- Utile pour connecter des sommets de différents polygones ou extrémités de segments

## Utilisation

### Compilation
```bash
make
```

### Exécution
```bash
./geometry_editor
```
ou
```bash
make run
```

### Nettoyage
```bash
make clean
```

## Interface

### Menu "Actions"
- **Créer Polygones** : Active le mode création de polygones
- **Créer Segments** : Active le mode création de segments
- **Créer Liens** : Active le mode création de liens
- **Effacer Tout** : Efface tous les objets de la zone de dessin
- **Quitter** : Ferme l'application

### Zone de dessin
- **Points** : Affichés en noir avec un petit carré
- **Polygones** : Lignes bleues reliant les sommets
- **Segments** : Lignes vertes entre deux points
- **Liens** : Lignes rouges pointillées entre deux points

## Structure du code

- `main.c` : Programme principal et initialisation de l'interface
- `main.h` : Définitions des structures de données
- `callbacks.c` : Implémentation des callbacks et logique du programme
- `callbacks.h` : Prototypes des fonctions callbacks
- `Makefile` : Configuration de compilation

## Limites

- Maximum 1000 points
- Maximum 100 polygones
- Maximum 100 segments
- Maximum 200 liens
- Maximum 50 sommets par polygone

## Dépendances

- libsx (bibliothèque graphique X11)
- X11, Xaw, Xmu, Xt
- Bibliothèque mathématique (libm)

## Auteur

Créé avec Claude Code
