#define PRINCIPAL 0
#include "4c19.h"

void nbmaille_triangle()
	{
	/* 
	Cette procedure calcule le nombre de cotes de maille, en u ou v, contenues dans le triangle de numero elem.
	le nb de cote de maille u = le nb de cote de maille en v pour tous les triangles
   	(u1,v1), (u2,v2), (u3,v3) sont les coordonnees filaires des trois sommets. 
   	A la fin de cette procedure, on sauvegarde le nombre de cotes de mailles selon u ou v
   	dans Surface[elem].nb_cote_u_ou_v
   	*/ 

  	double u2,v2,u3,v3;
  	double U2,V2,U3,V3;
  	int elem;
  

  	for ( elem = 1 ; elem <= NOMBRE_SURFACES ; elem++ )
  		{  
    		/* Calcul du nombre de cotes de maille selon u et selon v par l'appel de la procedure nbmaille_triangle */
 		/* Coordonnees filaires des sommets 1,2 et 3 du triangle. Le sommet 1 est pris comme origine.*/
     		/* u2 : coordonnee du noeud 2 en nb maille selon fil u*/
     		/* u3 : coordonnee du noeud 3 en nb maille selon fil u*/
     		/* v2 : coordonnee du noeud 2 en nb maille selon fil v*/
     		/* v3 : coordonnee du noeud 3 en nb maille selon fil v*/
    		u2 =  Surface[elem].lon[3]+Surface[elem].lon[4]-Surface[elem].lon[2]-Surface[elem].lon[1];
    		u3 =  Surface[elem].lon[5]+Surface[elem].lon[6]-Surface[elem].lon[2]-Surface[elem].lon[1];
    		v2 = -Surface[elem].lon[3]+Surface[elem].lon[4]-Surface[elem].lon[2]+Surface[elem].lon[1];
    		v3 = -Surface[elem].lon[5]+Surface[elem].lon[6]-Surface[elem].lon[2]+Surface[elem].lon[1];
 
  
		/* calcul de l'aire du triangle courant - l'element d'aire est defini par u et v (coordonnees filaires) et
    		correspond a une demi-maille de filet - */

   		Surface[elem].nb_cote_u_ou_v = fabs(u2*v3 - u3*v2) / 2.0 ;
/*		printf("elem %d u2 %lf u3 %lf v2 %lf v3 %lf \n",elem, u2,u3,v2,v3);
		printf("lon1 %lf lon2 %lf\n",Surface[elem].lon[1],Surface[elem].lon[2]);
		printf("lon3 %lf lon4 %lf\n",Surface[elem].lon[3],Surface[elem].lon[4]);
		printf("lon5 %lf lon6 %lf\n",Surface[elem].lon[5],Surface[elem].lon[6]);
		exit(0);*/
  		}   
	/* 
	Cette procedure calcule aussi le nombre de cotes de mailles en l, m ou n, contenues dans le triangle de numero elem.
	Ceci dans le cas de filet a mailles hexagonales.
	le nb de cote de maille l = le nb de cote de maille en m = le nb de cote de maille en n pour tous les triangles
   	(U1,V1), (U2,V2), (U3,V3) sont les coordonnees filaires des trois sommets. 
   	A la fin de cette procedure, on sauvegarde le nombre de cotes de mailles selon l, m ou n 
   	dans Surf_Hexa[elem].nb_cote_l_m_ou_v
   	*/ 
  	
  	for ( elem = 1 ; elem <= NOMBRE_SURF_HEXA ; elem++ )
  		{  
    		/* Calcul du nombre de cotes de maille selon u et selon v par l'appel de la procedure nbmaille_triangle */
 		/* Coordonnees filaires des sommets 1,2 et 3 du triangle. Le sommet 1 est pris comme origine.*/
     		/* U2 : coordonnee du noeud 2 en nb maille selon fil U*/
     		/* U3 : coordonnee du noeud 3 en nb maille selon fil U*/
     		/* V2 : coordonnee du noeud 2 en nb maille selon fil V*/
     		/* V3 : coordonnee du noeud 3 en nb maille selon fil V*/
    		U2 =  Surf_Hexa[elem].lon[3]+Surf_Hexa[elem].lon[4]-Surf_Hexa[elem].lon[2]-Surf_Hexa[elem].lon[1];
    		U3 =  Surf_Hexa[elem].lon[5]+Surf_Hexa[elem].lon[6]-Surf_Hexa[elem].lon[2]-Surf_Hexa[elem].lon[1];
    		V2 = -Surf_Hexa[elem].lon[3]+Surf_Hexa[elem].lon[4]-Surf_Hexa[elem].lon[2]+Surf_Hexa[elem].lon[1];
    		V3 = -Surf_Hexa[elem].lon[5]+Surf_Hexa[elem].lon[6]-Surf_Hexa[elem].lon[2]+Surf_Hexa[elem].lon[1];
 
  
		/* calcul de l'aire du triangle courant - l'element d'aire est defini par U et V (coordonnees filaires) et
    		correspond a une demi-maille de filet - */

   		Surf_Hexa[elem].nb_cote_l_m_ou_n = fabs(U2*V3 - U3*V2) /2.0 ;
  		}   
 	}
