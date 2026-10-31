//------------------------------------------------------------------------------------------------------------------------------------
/* Fonction determinant les nouvelles coordonnees de la matrice de raideur globale a partir des indices, des noeuds et de la matrice 
raideur locale.
Elle prend pour parametre d'entree :
	- i qui est l'indice de la matrice raideur locale
	- zi qui est l'indice du noeud 1
	- zj qui est l'indice du noeud 2
	- zk qui est l'indice du noeud 3

et elle retourne une seule valeur (en fonction du test) qui est la nouvelle coordonnee.
*/

//int new_coor(int i, int zi, int zj, int zk);


int new_coor(int i, int zi, int zj, int zk, int zl)
{
	int j, za, zb, zc, zd;
	za = 3*zi-2;
	zb = 3*zj-2;
	zc = 3*zk-2;
	zd = 3*zl-2;
	j = i+1;	// i+1 car i demarre de zero.

	if (j == 1) return (za);
	if (j == 2) return (za+1);
	if (j == 3) return (za+2);

	if (j == 4) return (zb);
	if (j == 5) return (zb+1);
	if (j == 6) return (zb+2);

	if (j == 7) return (zc);
	if (j == 8) return (zc+1);
	if (j == 9) return (zc+2);

	if (j == 10) return (zd);
	if (j == 11) return (zd+1);
	if (j == 12) return (zd+2);
}
