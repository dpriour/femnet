# Phobos GTK3

Portage de l’interface graphique de `phobos_2005` vers GTK3 et Cairo. Les
algorithmes et les menus viennent des sources originales; la couche
`gtk3_compat.c` remplace l’API d’interface libsx utilisée par le code historique.

## Compilation

```sh
make
```

GTK3 doit être installé avec `pkg-config`. L’exécutable créé est `phobos`.
Lancer `./phobos` sans argument ouvre l’interface. Les modes de calcul en ligne
de commande avec un ou deux fichiers restent disponibles.

La boîte de sélection de fichiers et le réglage de période des fils utilisent
des dialogues GTK3. La zone de dessin est pilotée par Cairo.
Dans la zone de dessin, la molette zoome autour du pointeur : vers le haut pour
agrandir, vers le bas pour réduire.
