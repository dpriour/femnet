#define PRINCIPAL 0
#include "4c19.h"


void modification4()
{
	/* prend en compte les conditions aux limites sur la matrice raideur (ze) et sur le vecteur effort (wa)*/
  	int zr,zg,zi,zj;

  	for (zr = 1; zr<= 3*NOMBRE_NOEUDS; zr++)
	{
    		if ( wl[zr]!=99 )  /*condition au limite fixe sur la coordonnee zr*/
		{
			if (Structure.type_solver == 1)
			{
	      			for (zg = zr-1; zg >= rang[4][zr]; zg--) ze[zr][eca-zr+zg] = 0.0;/*traitement de la partie gauche de la ligne zr */
      				for (zg = zr+1; zg <= rang[2][zr]; zg++) ze[zr][eca-zr+zg] = 0.0;/*traitement de la partie droite de la ligne zr */
      				for (zg = zr-1; zg >= rang[3][zr]; zg--) ze[zg][eca-zg+zr] = 0.0;/*traitement de la partie superieure a la ligne zr */
      				for (zg = zr+1; zg <= rang[1][zr]; zg++) ze[zg][eca-zg+zr] = 0.0;/*traitement de la partie inferieure a la ligne zr */
      				ze[zr][eca] = 1.0;
			}
			else if (Structure.type_solver == 2)
      			{
				//for (zg = zr-1; zg >= rang[4][zr]; zg--) modif_pardiso(0.0, zr, zg);
      				//for (zg = zr+1; zg <= rang[2][zr]; zg++) modif_pardiso(0.0, zr, zg);
      				//for (zg = zr-1; zg >= rang[3][zr]; zg--) modif_pardiso(0.0, zg, zr);
      				//for (zg = zr+1; zg <= rang[1][zr]; zg++) modif_pardiso(0.0, zg, zr);
				//modif_pardiso(1.0, zr, zr);
		      	}	
      			wa[zr] = 0.0;
		}
	}
	
  	for (zr = 3*NOMBRE_NOEUDS; zr>= 1; zr--)
	{
    		if ( wl[zr]!=99 )  /*condition au limite fixe sur la coordonnee zr*/
		{
      			for (zg = rang[4][zr]; zg <= zr-1; zg++) 
			{
    				if (rang[1][zg] == zr) rang[1][zg] = zr-1;
			}
		}
	}
  		
  	for (zr = 3*NOMBRE_NOEUDS; zr>= 1; zr--)
	{
    		if ( wl[zr]!=99 )  /*condition au limite fixe sur la coordonnee zr*/
    			{
      			for (zg = rang[4][zr]; zg <= zr-1; zg++) 
      				{
    				if (rang[1][zg] == zr) rang[1][zg] = zr-1;
      				}
    			}
  		}
  		
  	for (zr = 3*NOMBRE_NOEUDS; zr>= 1; zr--)
  		{
    		if ( wl[zr]!=99 )  /*condition au limite fixe sur la coordonnee zr*/
    			{
      			for (zg = rang[3][zr]; zg <= zr+1; zg++) 
      				{
    				if (rang[2][zg] == zr) rang[2][zg] = zr-1;
			}
		}
	}
  		
  	for (zr = 1; zr<= 3*NOMBRE_NOEUDS; zr++)
	{
    		if ( wl[zr]!=99 )  /*condition au limite fixe sur la coordonnee zr*/
		{
      			/*printf("zr = %d rang[3][zr] = %d\n",zr,rang[3][zr]);*/
      			for (zg = zr; zg <= 3*NOMBRE_NOEUDS; zg++) 
			{
    				if (rang[3][zg] == zr) rang[3][zg] = zr+1;
			}
		}
	}
  		
  	for (zr = 1; zr<= 3*NOMBRE_NOEUDS; zr++)
	{
    		if ( wl[zr]!=99 )  /*condition au limite fixe sur la coordonnee zr*/
		{
      			/*printf("zr = %d rang[3][zr] = %d\n",zr,rang[3][zr]);*/
      			for (zg = zr; zg <= 3*NOMBRE_NOEUDS; zg++) 
			{
    				if (rang[4][zg] == zr) rang[4][zg] = zr+1;
			}
		}
	}
  		
  	for (zr = 1; zr<= 3*NOMBRE_NOEUDS; zr++)
	{
    		if ( wl[zr]!=99 )  /*condition au limite fixe sur la coordonnee zr*/
		{
    			rang[1][zr] = zr;
    			rang[2][zr] = zr;
    			rang[3][zr] = zr;
    			rang[4][zr] = zr;
		}
	}
}


