#define PRINCIPAL 0
#include "4c19.h"
static int ifdstk = 1;

void misezero4()
	{
  	int i, li,co,pa,elem;
	int n = 9*NOMBRE_NOEUDS*NOMBRE_NOEUDS;
	int m = 3*NOMBRE_NOEUDS;
	if (Structure.type_solver == 1)
		{
	  	/*mise a zero de la matrice raideur ze */
	  	if (ifdstk != 0) 
			{
	    		ifdstk = 0;
	    		for (li = 1 ; li<= 3*NOMBRE_NOEUDS ; li++) 
				{
	      			for (co = 1; co<= 2*eca-1; co++) 
					{ 
		        		ze[li][co] = (double) 0; 
		        		/*ze_modif[li][co] = (double) 0; */
		        		ze_contact[li][co] = (double) 0; 
					}
				}
			} 
	  	else 
			{
	    		for (li = 1 ; li<= 3*NOMBRE_NOEUDS ; li++) 
				{
	      			for (co = rang[4][li]; co<= rang[2][li]; co++)
				{ 
	        			ze[li][eca-li+co] = (double) 0;
	        			/*ze_modif[li][eca-li+co] = (double) 0; */
	        			ze_contact[li][eca-li+co] = (double) 0; 
				}
			}
		}
	}
	else if (Structure.type_solver == 2)
	{
	/*	if (Nnonnul == 0)
		{
			for (i = 0; i< n ; i++)
			{
				a[i] = (double) 0;
				ja[i] = 0;
				ka[i] = 0;
				P[i] = -1;
			}
			for (i=0; i<m; i++){ia[i] = 0;}
		}
		else
		{
			for (i=0; i<n; i++){P[i] = -1;}
			for (i=0; i<=m; i++){ia[i] = 0;}
			for (i = 0; i< Nnonnul ; i++)
			{
				a[i] = (double) 0;
				ja[i] = 0;
				ka[i] = 0;
			}
			Nnonnul = 0;
			ja = realloc(ja, sizeof(int) * n);  
			ka = realloc(ka, sizeof(int) * n);  
			a = realloc(a, sizeof(double) * n);*/
	
			for (i=0; i<n; i++)
			{
				P[i] = -1.0;
				A[i] = 0.0;
			}
			for (i=0; i<=m; i++){ia[i] = 0;}
	/*		for (i = 0; i< Nnonnul ; i++)
			{
				a[i] = (double) 0;
				ja[i] = 0;
				ka[i] = 0;
			}*/
			Nnonnul = 0;
	
		//}
	}
	
  	/* mise a zero du vecteur wa, wasurf, waelem, wanoeud*/
  	/* wasurf est le vecteur effort agissant sur les surfaces et affecte aux noeuds.
     	waelem est le vecteur effort agissant sur les elements et affecte aux noeuds.
     	wanoeud est le vecteur effort agissant directement sur les noeuds.
     	wa est le vecteur effort total .
     	rang[1][li]: borne basse de la colonne li de la matrice.
     	rang[2][li]: borne droite de la ligne li de la matrice.
     	rang[3][li]: borne haute de la colonne li de la matrice.
     	rang[4][li]: borne gauche de la ligne li de la matrice.*/
     
  	for (li = 1 ; li<= 3*NOMBRE_NOEUDS ; li++) 
	{
    		wa[li] = 0.0;
    		wasurf[li] = 0.0; 
    		waecontact[li] = 0.0; 
    		waemodif[li] = 0.0; 
    		waelem[li] = 0.0;
    		wanoeud[li] = 0.0;
    		rang[1][li] = li; 
    		rang[2][li] = li; 
    		rang[3][li] = li; 
    		rang[4][li] = li;
		Noeud[li].volume_ballast = 0.0;
	}


  	/* mise a zero des energies elastiques*/
     
  	for (li = 1 ; li<= NOMBRE_SURFACES ; li++) 
	{
    		Surface[li].energy_pliage = 0.0;
    		Surface[li].energy_ouverture = 0.0;
    		Surface[li].energy_elastique = 0.0;
    		Surface[li].energy_contact = 0.0;
	}

  	/* mise a zero des trainees*/
     	Structure.surface_drag = 0.0;
	Structure.element_drag = 0.0;
	Structure.node_drag = 0.0;
     	Structure.surface_energy = 0.0;
	Structure.element_energy = 0.0;
	Structure.node_energy = 0.0;
     	Structure.surface_power = 0.0;
	Structure.element_power = 0.0;
	Structure.node_power = 0.0;
	Bottom.drag = 0.0;
	Bottom.energy = 0.0;
	Bottom.power = 0.0;
	Prise.drag = 0.0;
	if (Sortie_texte.panel_drag == 1)
	{
		for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
	    		panneau[pa].drag = 0.0;
		}
	  	for (pa = 1 ; pa<= NOMBRE_SURFACES ; pa++) 
		{
	    		Surface[pa].panel_drag = 0.0;
	    		Surface[pa].panel_dragxyz = 0.0;
		}
	}
	if (Sortie_texte.cable_drag == 1)
		{
		for (pa=1;pa<=Structure.NbTypeelem;pa++)
			{
	    		TypeElement[pa].cable_drag = 0.0;
			}
	  	for (pa = 1 ; pa<= NOMBRE_ELEMENTS ; pa++) 
			{
	    		Element[pa].cable_drag = 0.0;
			}
		}
  	for (elem = 1 ; elem<= NOMBRE_NOEUDS ; elem++) 
  		{
  		Noeud[elem].fhx = 0.0;
  		Noeud[elem].fhy = 0.0;
  		Noeud[elem].fhz = 0.0;
  		}
	if (Prise.angle_tensions > 0)
		{	
		Prise.angle_twines = 0.0;
		Prise.tension_u = 0.0;
		Prise.tension_v = 0.0;	
		Prise.angle_tensions = 1;
		}
	if (Prise.angle_tensions > 0)
		{	
		Structure.boat_energy = 0.0;
		Structure.boat_power = 0.0;
		}
	}

