#define PRINCIPAL 0
#include "phobos.h"

void nb_maille_total()
	{
	int pa,mode;
	
	if (Structure.graphic == 1)
		{
		mode = GetMenuItemChecked(w[88]);
		if (mode == 0) numerotation_balls();
		}
	
  	Structure.surface_fils = 0.0;
  	for ( pa = 1 ; pa <= Structure.NbTypesurf ; pa++ )
  		{
  		nbmaille_triangle(pa);
		Structure.surface_fils = Structure.surface_fils + panneau[pa].surf_fils;
		/*printf("Structure.surface_fils  = %f \n",Structure.surface_fils);*/
  		}
  	for ( pa = 1 ; pa <= Structure.NbTypesurf_hexa ; pa++ )
  		{
  		nbmaille_tri_hexa(pa);
		Structure.surface_fils = Structure.surface_fils + pan_hexa[pa].surf_fils;
		printf("Structure.surface_fils  = %f \n",Structure.surface_fils);
  		} 
	printf("Structure.surface_fils  = %f \n",Structure.surface_fils);
	if (Structure.graphic == 1)
		{
		SetMenuItemChecked(w[59],1);
		}
	}

void nbmaille_triangle(int pa)
	{
	/* 
	Cette procedure calcule le nombre de cotes de maille, en u ou v, contenues dans le triangle de numero elem.
	le nb de cote de maille u = le nb de cote de maille en v pour tous les triangles
   	(u1,v1), (u2,v2), (u3,v3) sont les coordonnees filaires des trois sommets. 
   	A la fin de cette procedure, on sauvegarde le nombre de cotes de mailles selon u ou v
   	dans surface[elem].nb_cote_u_ou_v
   	*/ 

  	float u2,u3,v2,v3;
  	int elem,sommet1,sommet2,sommet3;
  	float somme;
  
	somme = 0.0;
  	for ( elem = 1 ; elem <= Structure.nombreSurfaces ; elem++ )
  		{  
		if (surface[elem].type == pa)
			{
		/* Calcul du nombre de cotes de maille selon u et selon v par l'appel de la procedure nbmaille_triangle */
 		/* Coordonnees filaires des sommets 1,2 et 3 du triangle. Le sommet 1 est pris comme origine.*/
     		/* u2 : coordonnee du noeud 2 en nb maille selon fil u*/
     		/* u3 : coordonnee du noeud 3 en nb maille selon fil u*/
     		/* v2 : coordonnee du noeud 2 en nb maille selon fil v*/
     		/* v3 : coordonnee du noeud 3 en nb maille selon fil v*/
     		sommet1 = surface[elem].extremite[1];
     		sommet2 = surface[elem].extremite[2];
     		sommet3 = surface[elem].extremite[3];
		u2 =  noeud[sommet2].U+noeud[sommet2].V -noeud[sommet1].V-noeud[sommet1].U;
		u3 =  noeud[sommet3].U+noeud[sommet3].V -noeud[sommet1].V-noeud[sommet1].U;
		v2 = -noeud[sommet2].U+noeud[sommet2].V -noeud[sommet1].V+noeud[sommet1].U;
		v3 = -noeud[sommet3].U+noeud[sommet3].V -noeud[sommet1].V+noeud[sommet1].U;
    		
    		/*u1 =  Surface[elem].lon[1]+Surface[elem].lon[2]-Surface[elem].lon[2]-Surface[elem].lon[1];
    		u2 =  Surface[elem].lon[3]+Surface[elem].lon[4]-Surface[elem].lon[2]-Surface[elem].lon[1];
    		u3 =  Surface[elem].lon[5]+Surface[elem].lon[6]-Surface[elem].lon[2]-Surface[elem].lon[1];
    		v1 = -Surface[elem].lon[1]+Surface[elem].lon[2]-Surface[elem].lon[2]+Surface[elem].lon[1];
    		v2 = -Surface[elem].lon[3]+Surface[elem].lon[4]-Surface[elem].lon[2]+Surface[elem].lon[1];
    		v3 = -Surface[elem].lon[5]+Surface[elem].lon[6]-Surface[elem].lon[2]+Surface[elem].lon[1];*/
 
  
		/* calcul de l'aire du triangle courant - l'element d'aire est defini par u et v (coordonnees filaires) et
    		correspond a une demi-maille de filet - */

   		surface[elem].nb_cote_u_ou_v = fabs(u2*v3 - u3*v2) / 2.0 ;
   		somme = somme + surface[elem].nb_cote_u_ou_v;
			}

  		}   
	panneau[pa].surf_fils = 2*somme*panneau[pa].longueur_repos*panneau[pa].diam_hydro;
	printf("panneau = %d ",pa);
	printf("nb cote de maille u  = %f ",somme);
	printf("surface de fils  = %f \n",panneau[pa].surf_fils);
 	}
 	
void nbmaille_tri_hexa(int pa)
	{
	/* 
	Cette procedure calcule le nombre de cotes de maille, en l, m ou n, contenues dans le triangle de numero elem.
   	(U1,V1), (U2,V2), (U3,V3) sont les coordonnees filaires des trois sommets. 
   	A la fin de cette procedure, on sauvegarde le nombre de cotes de mailles selon u ou v
   	dans surf_hexa[elem].nb_cote_l_m_ou_n
   	*/ 

  	float U2,U3,V2,V3;
  	int elem,sommet1,sommet2,sommet3;
  	float somme;
  
	somme = 0.0;
  	for ( elem = 1 ; elem <= Structure.nombreSurfHexa ; elem++ )
  		{ 
		if (surf_hexa[elem].type == pa)
			{
  	/*printf("nombreSurfHexa  = %d\n",Structure.nombreSurfHexa);
  	exit(0);*/
		/* Calcul du nombre de cotes de maille selon l m et n par l'appel de la procedure nbmaille_tri_hexa */
 		/* Coordonnees filaires des sommets 1,2 et 3 du triangle. Le sommet 1 est pris comme origine.*/
     		/* U2 : coordonnee du noeud 2 en nb maille selon fil U*/
     		/* U3 : coordonnee du noeud 3 en nb maille selon fil U*/
     		/* V2 : coordonnee du noeud 2 en nb maille selon fil V*/
     		/* V3 : coordonnee du noeud 3 en nb maille selon fil V*/
     		sommet1 = surf_hexa[elem].extremite[1];
     		sommet2 = surf_hexa[elem].extremite[2];
     		sommet3 = surf_hexa[elem].extremite[3];
		U2 =  noeud[sommet2].U - noeud[sommet1].U;
		U3 =  noeud[sommet3].U - noeud[sommet1].U;
		V2 =  noeud[sommet2].V - noeud[sommet1].V;
		V3 =  noeud[sommet3].V - noeud[sommet1].V;
    		
		/* calcul de l'aire du triangle courant - l'element d'aire est defini par U et V et
    		correspond a une maille de filet - */

   		surf_hexa[elem].nb_cote_l_m_ou_n = fabs(U2*V3 - U3*V2);
   		somme = somme + surf_hexa[elem].nb_cote_l_m_ou_n;
			}

  		}   
	pan_hexa[pa].surf_fils += somme * pan_hexa[pa].lo_repos * pan_hexa[pa].diam_hydro_l;
	pan_hexa[pa].surf_fils += somme * pan_hexa[pa].mo_repos * pan_hexa[pa].diam_hydro_m;
	pan_hexa[pa].surf_fils += somme * pan_hexa[pa].no_repos * pan_hexa[pa].diam_hydro_n;
	printf("pan_hexa = %d ",pa);
	printf("nb cote de maille l_m_n  = %f ",somme);
	printf("surface de fils  = %f \n",pan_hexa[pa].surf_fils);
 	}
