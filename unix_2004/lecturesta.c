#define PRINCIPAL 0
#include "4c19.h"

/*lecture du fichier de resultat statique si il existe*/

int lecturesta(char *nomfichier)
	{
  	char tonom[1000];
  	int j,tmp,elem,itmp,panel;
  	double elongation,tempo;
  	FILE *f1;

  	strcpy(tonom,nomfichier);
        j=strlen(tonom);
        while ((tonom[j])!='.' && j>0) j--;
        if (tonom[j]=='.') tonom[j]=0;

  	strcat(tonom,".sta");
  	f1 = fopen(tonom,"r");


  	if (f1 == NULL) 
  		{
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom," don't exist");
    		/*fclose(f1);*/
    		return 0;
  		} 
  	else
  		{
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom," exists ");
    
    		/* lecture des nouvelles coordonnees des noeuds du maillage. */
    		/*for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    			{
			itmp = fscanf(f1,"%d %lf %lf %lf",&tmp,&Noeud[elem].x,&Noeud[elem].y,&Noeud[elem].z);
    			}*/
   		for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    			{
			itmp = fscanf(f1,"%d ",&tmp);
			if (Noeud[elem].fixx != 1)	itmp = fscanf(f1,"%lf ",&Noeud[elem].x);
			else				itmp = fscanf(f1,"%lf ",&tempo);
			if (Noeud[elem].fixy != 1)	itmp = fscanf(f1,"%lf ",&Noeud[elem].y);
			else				itmp = fscanf(f1,"%lf ",&tempo);
			if (Noeud[elem].fixz != 1)	itmp = fscanf(f1,"%lf ",&Noeud[elem].z);
			else				itmp = fscanf(f1,"%lf ",&tempo);
			//printf("elem %d   ",elem);	
			//printf("Noeud x %lf   ",Noeud[elem].x);	
			//printf(" y %lf   ",Noeud[elem].y);	
			//printf(" z %lf   \n",Noeud[elem].z);	
    			}
    			    
    		/* Lecture de la longueur tendue des bouts */
    		for (elem=1;elem<=NOMBRE_ELEMENTS;elem++)
    			{ 
      			//Element[elem].lgrepos = (Element[elem].pro[2] - Element[elem].pro[1]) * TypeElement[Element[elem].type].lgrepos;
			if (Element[elem].netting2ropes_panel == 0)
				{
				Element[elem].lgrepos	= (Element[elem].pro[2] - Element[elem].pro[1]) * TypeElement[Element[elem].type].lgrepos;/**/
				}
			else
				{
				panel = Element[elem].netting2ropes_panel;
				Element[elem].lgrepos	= panneau[panel].longueur_repos * panneau[panel].netting_2_ropes_period / panneau[panel].netting_2_ropes_bar_nb;
				}
    			}
      			itmp = fscanf(f1,"%lf",&elongation);
      			Element[elem].lgtendue = Element[elem].lgrepos * (1.0 + elongation);
	
    
    		/* Lecture de la longueur tendue des coulisses */
    		for (elem=1;elem<=NOMBRE_COULISSES;elem++)
    			{ 
      			itmp = fscanf(f1,"%lf",&elongation);
      			Coulisse[elem].lgtendue = Coulisse[elem].lgrepos * (1.0 + elongation);
    			}
  	
  		/*lecture de la longueur des mailles selon u et v dans chaque triangle a l equilibre statique */
  		for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
  			{
       			itmp = fscanf(f1,"%lf",&Surface[elem].mx);
      			itmp = fscanf(f1,"%lf",&Surface[elem].my);
      			itmp = fscanf(f1,"%lf",&Surface[elem].mz);
     			itmp = fscanf(f1,"%lf",&Surface[elem].nx);
      			itmp = fscanf(f1,"%lf",&Surface[elem].ny);
      			itmp = fscanf(f1,"%lf",&Surface[elem].nz);
  			}
  
  		/*lecture des longueurs l, m et n  des fils composants les mailles hexagonales a l equilibre statique */
  		for (elem = 1 ; elem<= NOMBRE_SURF_HEXA ; elem++) 
  			{
      			itmp = fscanf(f1,"%lf",&Surf_Hexa[elem].lx);
      			itmp = fscanf(f1,"%lf",&Surf_Hexa[elem].ly);
      			itmp = fscanf(f1,"%lf",&Surf_Hexa[elem].lz);
      			itmp = fscanf(f1,"%lf",&Surf_Hexa[elem].mx);
      			itmp = fscanf(f1,"%lf",&Surf_Hexa[elem].my);
      			itmp = fscanf(f1,"%lf",&Surf_Hexa[elem].mz);
      			itmp = fscanf(f1,"%lf",&Surf_Hexa[elem].nx);
      			itmp = fscanf(f1,"%lf",&Surf_Hexa[elem].ny);
      			itmp = fscanf(f1,"%lf",&Surf_Hexa[elem].nz);
			}
  		/*les fils l m n des mailles hexagonales ont ete calcules*/
  		Structure.lmn_calcules = 1;

  		/*lecture de la position du front */
  		itmp = fscanf(f1,"%lf",&Prise.front);
      
    		fclose(f1);
    		return 1;
  		}
	}	


