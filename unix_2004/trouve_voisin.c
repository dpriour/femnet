#define PRINCIPAL 0
#include "4c19.h"

void trouve_voisin()
	{
	//find out neigbhor triangles
  	int elem1,elem2,za,z1,z2,z3,z4,trouve;
  	double U1,U2,U3,U4,V1,V2,V3,V4;
  	
	/*printf("trouveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee  \n");*/
	
  	for (elem1 = 1; elem1<= NOMBRE_SURFACES-1; elem1++)
  		{
  		for (za = 1; za<= 3; za++)
  			{
  			/*faire pour les 3 sommets du triangle elem1, z1 est le sommet 1 z3 et z4 les sommets 3 et 4*/
    			if (za == 1) 
				{
				/*le point z1 est sur le sommet 1 => le point z4 (z3) sur le sommet 2 (3)*/
				z1 = yc(elem1,1);  z4 = yc(elem1,4);  z3 = yc(elem1,7);
				trouve = trouver2(elem1,z1,&elem2,&z2,&U2,&V2);
				if (trouve == 1)
					{
					Surface[elem1].voisin_1.exist 		= 1;
					Surface[elem1].voisin_1.elem_voisin 	= elem2;
					Surface[elem1].voisin_1.sommet_oppose 	= z2;
					Surface[elem1].voisin_1.U_oppose 	= U2;
					Surface[elem1].voisin_1.V_oppose 	= V2;
					}
				else
					{
					Surface[elem1].voisin_1.exist = 0;
					}
				}
    			if (za == 2) 
				{
				/*le point z1 est sur le sommet 2 => le point z4 (z3) sur le sommet 3 (1)*/
				z1 = yc(elem1,4);  z4 = yc(elem1,7);  z3 = yc(elem1,1);
				trouve = trouver2(elem1,z1,&elem2,&z2,&U2,&V2);
				if (trouve == 1)
					{
					Surface[elem1].voisin_2.exist 		= 1;
					Surface[elem1].voisin_2.elem_voisin 	= elem2;
					Surface[elem1].voisin_2.sommet_oppose 	= z2;
					Surface[elem1].voisin_2.U_oppose 	= U2;
					Surface[elem1].voisin_2.V_oppose 	= V2;
					}
				else
					{
					Surface[elem1].voisin_2.exist = 0;
					}
				}
    			if (za == 3) 
				{
				/*le point z1 est sur le sommet 3 => le point z4 (z3) sur le sommet 1 (2)*/
				z1 = yc(elem1,7);  z4 = yc(elem1,1);  z3 = yc(elem1,4);
				trouve = trouver2(elem1,z1,&elem2,&z2,&U2,&V2);
				if (trouve == 1)
					{
					Surface[elem1].voisin_3.exist 		= 1;
					Surface[elem1].voisin_3.elem_voisin 	= elem2;
					Surface[elem1].voisin_3.sommet_oppose 	= z2;
					Surface[elem1].voisin_3.U_oppose 	= U2;
					Surface[elem1].voisin_3.V_oppose 	= V2;
					}
				else
					{
					Surface[elem1].voisin_3.exist = 0;
					}
				}
			}
		}
	}


int trouver2(int elem1, int sommet1, int *elem2, int *sommet2, double *U2, double *V2)
	{
	int trouve,elem3,zb,zc,zd,sommet3,sommet4;
	
	if (sommet1 == yc(elem1,1))  {	sommet3 = yc(elem1,4);  sommet4 = yc(elem1,7);	}
	if (sommet1 == yc(elem1,4))  {	sommet3 = yc(elem1,7);  sommet4 = yc(elem1,1);	}
	if (sommet1 == yc(elem1,7))  {	sommet3 = yc(elem1,1);  sommet4 = yc(elem1,4);	}
	
  	trouve = 0;			
  	elem3 = elem1;
  	while ((trouve == 0) && (elem3 <= NOMBRE_SURFACES))
  		{
  		/*recherche d un triangle voisin de elem1 par les sommets sommet3 et sommet4 et de meme type que elem1*/
  		/*printf("elem1 = %5d elem3 = %5d       \n",elem1,elem3);*/
  		elem3 = elem3 + 1;
  		if (Surface[elem3].type == Surface[elem1].type)
  			{
  			zb = yc(elem3,1);  zc = yc(elem3,4);  zd = yc(elem3,7);
  			/*printf("elem1 = %5d elem3 = %5d       ",elem1,elem3);
   			printf("sommet3 = %5d sommet4 = %5d        ",sommet3,sommet4);
   			printf("zb = %5d zc = %5d zd = %5d \n",zb,zc,zd);*/
  			if((zb == sommet3) && (zc == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zd; /*sommet 3 (zd) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[5] + Surface[*elem2].lon[6];
				*V2 = - Surface[*elem2].lon[5] + Surface[*elem2].lon[6];
   				/*printf("1 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			if((zc == sommet3) && (zb == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zd; /*sommet 3 (zd) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[5] + Surface[*elem2].lon[6];
				*V2 = - Surface[*elem2].lon[5] + Surface[*elem2].lon[6];
   				/*printf("2 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			if((zc == sommet3) && (zd == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zb; /*sommet 1 (zb) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[1] + Surface[*elem2].lon[2]; 
				*V2 = - Surface[*elem2].lon[1] + Surface[*elem2].lon[2]; 
   				/*printf("3 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			if((zd == sommet3) && (zc == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zb; /*sommet 1 (zb) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[1] + Surface[*elem2].lon[2]; 
				*V2 = - Surface[*elem2].lon[1] + Surface[*elem2].lon[2]; 
   				/*printf("4 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			if((zd == sommet3) && (zb == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zc; /*sommet 2 (zc) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[3] + Surface[*elem2].lon[4]; 
				*V2 = - Surface[*elem2].lon[3] + Surface[*elem2].lon[4]; 
   				/*printf("5 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			if((zb == sommet3) && (zd == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zc; /*sommet 2 (zc) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[3] + Surface[*elem2].lon[4]; 
				*V2 = - Surface[*elem2].lon[3] + Surface[*elem2].lon[4]; 
   				/*printf("6 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			}
  		}
	return trouve;	
	}
					



