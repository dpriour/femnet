#define PRINCIPAL 0
#include "phobos.h"

void lire_fichier_mdgsta()
	
	{
	/* Pour cette procedure, on a besoin d'avoir effectue un premier calcul(avec convergence). 
	Nous sommes donc en possession d'un
   	fichier *.sta. Dans cette procedure, nous allons lire ce *.sta afin de pouvoir 
   	afficher dans phobos certaines
   	donnees calculees telles que la tension et la longueur tendue. */
	
	char tonom[128],t1[256],can[128],c;
	char *pr;
	int i,j,tmp,tmp2,numero_panneau,mode,nb_lu,itmp,itmq,pa,no;
	FILE *fic1, *fic2;
	float elongation,elongation1,elongation2,elongation3,lgrepos,raideur_traction,raideur_compression,ftmp1,ftmp2,ftmp3;
	float energie,temp1,temp2,temp3,norm_temp;
	double dtmp;
	
	mode = GetMenuItemChecked(w[59]);
	if (mode == 0) nb_maille_total();
	
	/***************Lecture d une partie du fichier .sta correspondant (s il existe) sous le repertoire approprie*************/	
	
	strcpy(tonom,fname1);
	strcat(tonom,".sta");
	fic2 = fopen(tonom,"r");
	if (fic2 == NULL) 
	 	{ 
	 	printf("* charger_mdgsta * Impossible d ouvrir le fichier %s\n",tonom);
	   	exit(0);
	 	}
	printf("debut de lecture du fichier %s\n",tonom);
	
	for (i=1;i<=Structure.nb_global;i++)
		{
	  	itmp = itmp = fscanf(fic2,"%d %f %f %f\n",&j,&ftmp1,&ftmp2,&ftmp3);
	  	}
	 	
	/* éléments *******************************************************/
	printf("Structure.nb_barre = %d\n",Structure.nb_barre);
	for (i=1;i<=Structure.nb_barre;i++)	       	               
    		{   		
    		itmp = fscanf(fic2,"%f\n",&barre[i].elongation);
		/*
		printf("i= %d elongation=%f\n",i,barre[i].elongation);
		*/
      		barre[i].longueur_tendue=(barre[i].elongation * barre[i].longueur_repos)+ barre[i].longueur_repos;   		
                if (barre[i].elongation >= 0.0) barre[i].tension = barre[i].elongation * element[barre[i].type].raideur_traction;
                /*energie potentielle*/	      barre[i].nrj= barre[i].tension * (barre[i].longueur_tendue - barre[i].longueur_repos)/2;
                
      		if (barre[i].elongation <  0.0) barre[i].tension = barre[i].elongation * element[barre[i].type].raideur_compression;
    		/*energie potentielle*/       barre[i].nrj= barre[i].tension * (barre[i].longueur_tendue - barre[i].longueur_repos)/2;
    		
		/*
		printf("%d longueur_repos=%.3g longueur_tendue=%f tension=%f nrjelem=%f\n",i,barre[i].longueur_repos,barre[i].longueur_tendue,barre[i].tension,barre[i].nrj);
		*/
		

	        }
	        
   	/*  coulisses**********************************************************/
    	printf("Structure.nombreCoulisses = %d\n",Structure.nombreCoulisses);
    	for (i=1;i<=Structure.nombreCoulisses;i++)
    		{ 
      		itmp = fscanf(fic2,"%f\n",&coulisse[i].elongation);
      		printf("elongation=%f\n ",coulisse[i].elongation);
      		coulisse[i].lgtendue = (coulisse[i].elongation * coulisse[i].lgrepos) + coulisse[i].lgrepos;
      		if (elongation >= 0.0) coulisse[i].wt = coulisse[i].elongation * coulisse[i].raideur_traction;
      			               coulisse[i].nrj=coulisse[i].wt*(coulisse[i].lgtendue-coulisse[i].lgrepos)/2;
      		if (elongation <  0.0) coulisse[i].wt = coulisse[i].elongation * coulisse[i].raideur_compression;
    				       coulisse[i].nrj=coulisse[i].wt*(coulisse[i].lgtendue-coulisse[i].lgrepos)/2;
 		/*printf("%d longueur_repos=%.3g longueur_tendue=%f tension=%f nrj=%f\n",i,coulisse[i].lgrepos,coulisse[i].lgtendue,coulisse[i].wt,coulisse[i].nrj);
 		*/
 		}
	        
		
	        
        /* surfaces *********************************************************/
        printf("Structure.nombreSurfaces = %d\n",Structure.nombreSurfaces);
	for (i=1;i<=Structure.nombreSurfaces;i++)
		{
      		itmp = fscanf(fic2,"%lf",&surface[i].m[1]);
      		itmp = fscanf(fic2,"%lf",&surface[i].m[2]);
      		itmp = fscanf(fic2,"%lf",&surface[i].m[3]);
      		itmp = fscanf(fic2,"%lf",&surface[i].n[1]);
      		itmp = fscanf(fic2,"%lf",&surface[i].n[2]);
      		itmp = fscanf(fic2,"%lf",&surface[i].n[3]);
      		surface[i].lg_tendue1 = sqrt(surface[i].n[1]*surface[i].n[1] + surface[i].n[2]*surface[i].n[2] + surface[i].n[3]*surface[i].n[3]);
      		surface[i].lg_tendue2 = sqrt(surface[i].m[1]*surface[i].m[1] + surface[i].m[2]*surface[i].m[2] + surface[i].m[3]*surface[i].m[3]);
      		numero_panneau = surface[i].type;
      		lgrepos = panneau[numero_panneau].longueur_repos;
      		raideur_traction = panneau[numero_panneau].raideur_traction;
      		raideur_compression = panneau[numero_panneau].raideur_compression;
        	
        	elongation1 = (surface[i].lg_tendue1 - lgrepos) / lgrepos;
        	/*calcul de l energie potentielle par fil m*/
      		if (elongation1 >= 0.0) 
      			{
      			surface[i].tension1 = elongation1 * raideur_traction;
      			surface[i].nrj1=surface[i].tension1*(surface[i].lg_tendue1 - lgrepos)/2.0;
      			}
      		else
      			{
      			surface[i].tension1 = elongation1 * raideur_compression;
      			surface[i].nrj1=surface[i].tension1*(surface[i].lg_tendue1 - lgrepos)/2.0;
      			}
      			
    		elongation2 = (surface[i].lg_tendue2 - lgrepos) / lgrepos;
        	/*calcul de l energie potentielle par fil n*/
      		if (elongation2 >= 0.0) 
      			{
      			surface[i].tension2 = elongation2 * raideur_traction;
      			surface[i].nrj2=surface[i].tension2*(surface[i].lg_tendue2- lgrepos)/2.0;
      			}
      		else
      			{
      			surface[i].tension2 = elongation2 * raideur_compression;
      			surface[i].nrj2=surface[i].tension2*(surface[i].lg_tendue2 - lgrepos)/2.0;
      			}
       					
      		/*somme des energies contenues dans un fil m et n*/
      		surface[i].nrj = surface[i].nrj2 + surface[i].nrj1;
      					
      		/*printf("%d lgrepos=%.3g lg_tendue1=%f tension1=%f nrj1=%f\n",i,lgrepos,surface[i].lg_tendue1,surface[i].tension1,surface[i].nrj1); 
		printf("%d lgrepos=%.3g lg_tendue2=%f tension2=%f nrj2=%f nrj=%f\n",i,lgrepos,surface[i].lg_tendue2,surface[i].tension2,surface[i].nrj2,surface[i].nrj);
		*/
		
    		temp1 = surface[i].n[2]*surface[i].m[3] - surface[i].n[3]*surface[i].m[2];
    		temp2 = surface[i].n[3]*surface[i].m[1] - surface[i].n[1]*surface[i].m[3];
    		temp3 = surface[i].n[1]*surface[i].m[2] - surface[i].n[2]*surface[i].m[1];
    		norm_temp = sqrt(temp1*temp1 + temp2*temp2 + temp3*temp3);
		/*printf("i = %d, temp1  = %f %f %f\n",i,temp1,temp2,temp3);
		if (i == 706) exit(0);*/
		if (norm_temp != 0.0)
			{
    			surface[i].Nx = temp1 / norm_temp;
    			surface[i].Ny = temp2 / norm_temp;
    			surface[i].Nz = temp3 / norm_temp;
			}
		else
			{
    			surface[i].Nx = 1.0;
    			surface[i].Ny = 0.0;
    			surface[i].Nz = 0.0;
			}
		} 
		
	/* surfaces hexagonales**********************************************/	
	printf("Structure.nombreSurfHexa = %d\n",Structure.nombreSurfHexa);
	for (i=1;i<=Structure.nombreSurfHexa;i++)
		{
      		itmp = fscanf(fic2,"%lf",&surf_hexa[i].l[1]);
      		itmp = fscanf(fic2,"%lf",&surf_hexa[i].l[2]);
      		itmp = fscanf(fic2,"%lf",&surf_hexa[i].l[3]);
      		itmp = fscanf(fic2,"%lf",&surf_hexa[i].m[1]);
      		itmp = fscanf(fic2,"%lf",&surf_hexa[i].m[2]);
      		itmp = fscanf(fic2,"%lf",&surf_hexa[i].m[3]);
      		itmp = fscanf(fic2,"%lf",&surf_hexa[i].n[1]);
      		itmp = fscanf(fic2,"%lf",&surf_hexa[i].n[2]);
      		itmp = fscanf(fic2,"%lf",&surf_hexa[i].n[3]);
		/*printf("i = %d, lx = %lf\n",i,surf_hexa[i].l[1]);*/
		
		/*calcul des 3 longueur tendues*/
      		surf_hexa[i].lg_tendue1 = sqrt(surf_hexa[i].l[1]*surf_hexa[i].l[1] + surf_hexa[i].l[2]*surf_hexa[i].l[2] + surf_hexa[i].l[3]*surf_hexa[i].l[3]);
      		surf_hexa[i].lg_tendue2 = sqrt(surf_hexa[i].m[1]*surf_hexa[i].m[1] + surf_hexa[i].m[2]*surf_hexa[i].m[2] + surf_hexa[i].m[3]*surf_hexa[i].m[3]);
      		surf_hexa[i].lg_tendue3 = sqrt(surf_hexa[i].n[1]*surf_hexa[i].n[1] + surf_hexa[i].n[2]*surf_hexa[i].n[2] + surf_hexa[i].n[3]*surf_hexa[i].n[3]);
	
      		numero_panneau = surf_hexa[i].type;
      		
        	/*calcul de l energie potentielle par fil l*/
      		elongation1 = (surf_hexa[i].lg_tendue1 - pan_hexa[numero_panneau].lo_repos) / pan_hexa[numero_panneau].lo_repos;
      		if (elongation1 >= 0.0) 
      			{
      			surf_hexa[i].tension1 = elongation1 * pan_hexa[numero_panneau].raideur_traction_l;
      			surf_hexa[i].nrj1=surf_hexa[i].tension1*(surf_hexa[i].lg_tendue1- pan_hexa[numero_panneau].lo_repos)/2.0;
      			}
      		else
      			{
      			surf_hexa[i].tension1 = elongation1 * pan_hexa[numero_panneau].raideur_compression_l;
			surf_hexa[i].nrj1=surf_hexa[i].tension1*(surf_hexa[i].lg_tendue1- pan_hexa[numero_panneau].lo_repos)/2.0;
			}
			                
        	/*calcul de l energie potentielle par fil m*/
      		elongation2 = (surf_hexa[i].lg_tendue2 - pan_hexa[numero_panneau].mo_repos) / pan_hexa[numero_panneau].mo_repos;
      		if (elongation2 >= 0.0) 
      			{
      			surf_hexa[i].tension2 = elongation2 * pan_hexa[numero_panneau].raideur_traction_m;
      			surf_hexa[i].nrj2=surf_hexa[i].tension2*(surf_hexa[i].lg_tendue2- pan_hexa[numero_panneau].mo_repos)/2.0;
      			}
      		else
      			{
      			surf_hexa[i].tension2 = elongation2 * pan_hexa[numero_panneau].raideur_compression_m;
      			surf_hexa[i].nrj2=surf_hexa[i].tension2*(surf_hexa[i].lg_tendue2- pan_hexa[numero_panneau].mo_repos)/2.0;
      			}
      					
        	/*calcul de l energie potentielle par fil n*/
      		elongation3 = (surf_hexa[i].lg_tendue3 - pan_hexa[numero_panneau].no_repos) / pan_hexa[numero_panneau].no_repos;
      		if (elongation3 >= 0.0) 
      			{
      			surf_hexa[i].tension3 = elongation3 * pan_hexa[numero_panneau].raideur_traction_n;
      			surf_hexa[i].nrj3=surf_hexa[i].tension3*(surf_hexa[i].lg_tendue3- pan_hexa[numero_panneau].no_repos)/2.0;
      			}
      		else 
      			{
      			surf_hexa[i].tension3 = elongation3 * pan_hexa[numero_panneau].raideur_compression_n;
      			surf_hexa[i].nrj3=surf_hexa[i].tension3*(surf_hexa[i].lg_tendue3- pan_hexa[numero_panneau].no_repos)/2.0;
      			}
      					
      		/*somme des energies contenues dans un fil l, m et n*/
		surf_hexa[i].nrj = surf_hexa[i].nrj1 + surf_hexa[i].nrj2 + surf_hexa[i].nrj3;	                
		}

	itmp = fscanf(fic2,"%lf",&Prise.front);	 
	printf("Prise.front %8.2lf \n",Prise.front);

	printf("Sortie_texte.nb_distance %d \n",Sortie_texte.nb_distance);
	printf("Sortie_texte.nb_effort %d \n",Sortie_texte.nb_effort);
	printf("Sortie_texte.nb_tension_element %d \n",Sortie_texte.nb_tension_element);
	printf("Sortie_texte.nb_tension_coulisse %d \n",Sortie_texte.nb_tension_coulisse);
	printf("Sortie_texte.nb_position %d \n",Sortie_texte.nb_position);
	printf("Sortie_texte.bottom_drag %d \n",Sortie_texte.bottom_drag);
	printf("Sortie_texte.catch_drag %d \n",Sortie_texte.catch_drag);
	printf("Sortie_texte.element_drag %d \n",Sortie_texte.element_drag);
	printf("Sortie_texte.node_drag %d \n",Sortie_texte.node_drag);
	printf("Sortie_texte.surface_drag %d \n",Sortie_texte.surface_drag);
	printf("Sortie_texte.effort_structure %d \n",Sortie_texte.effort_structure);
	printf("Sortie_texte.diametre_prise %d \n",Sortie_texte.diametre_prise);
	printf("Sortie_texte.epaisseur_prise %d \n",Sortie_texte.epaisseur_prise);
	printf("Sortie_texte.volume_capture %d \n",Sortie_texte.volume_capture);

	for( pa = 1 ; pa <= Sortie_texte.nb_distance ; pa++ )
		{
		do  
			{
			c=fgetc(fic2);
			/*printf("c = %c",c);*/
			}
		while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_distance[pa]);
		printf("Sortie_texte.valeur_distance[%d] %8.2lf \n",pa,Sortie_texte.valeur_distance[pa]);
		}
  		
	for( pa = 1 ; pa <= Sortie_texte.nb_effort ; pa++ )
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_effort[pa]);
		printf("Sortie_texte.valeur_effort[pa] %8.2lf \n",Sortie_texte.valeur_effort[pa]);
		}
	
	for( pa = 1 ; pa <= Sortie_texte.nb_tension_element ; pa++ )
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_tension[pa]);
		printf("Sortie_texte.valeur_tension[pa] %8.2lf \n",Sortie_texte.valeur_tension[pa]);
		}
	
	for( pa = 1 ; pa <= Sortie_texte.nb_tension_coulisse ; pa++ )
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_tension_coulisse[pa]);
		printf("Sortie_texte.valeur_tension_coulisse[pa] %8.2lf \n",Sortie_texte.valeur_tension_coulisse[pa]);
		}
	
	for( pa = 1 ; pa <= Sortie_texte.nb_position ; pa++ )
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_position[pa]);
		printf("Sortie_texte.valeur_position[pa] %8.2lf \n",Sortie_texte.valeur_position[pa]);
		}
  			
	if(Sortie_texte.bottom_drag == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_bottom_drag);
		printf("Sortie_texte.valeur_bottom_drag %8.2lf \n",Sortie_texte.valeur_bottom_drag);
		}
	
	if(Sortie_texte.catch_drag == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_catch_drag);
		printf("Sortie_texte.valeur_catch_drag %8.2lf \n",Sortie_texte.valeur_catch_drag);
		}
	
	if(Sortie_texte.element_drag == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_element_drag);
		printf("Sortie_texte.valeur_element_drag %8.2lf \n",Sortie_texte.valeur_element_drag);
		}
	
/*************************************************************/	
	if(Sortie_texte.surface_drag == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_surface_drag);
		printf("Sortie_texte.valeur_surface_drag %8.2lf \n",Sortie_texte.valeur_surface_drag);
		}
	
	if(Sortie_texte.node_drag == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_node_drag);
		printf("Sortie_texte.valeur_node_drag %8.2lf \n",Sortie_texte.valeur_node_drag);
		}
	
	if(Sortie_texte.effort_structure == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf %lf %lf",&Sortie_texte.valeur_effort_structure[1],&Sortie_texte.valeur_effort_structure[2],&Sortie_texte.valeur_effort_structure[3]);
		printf("Sortie_texte.valeur_effort_structure %lf %lf %lf \n",Sortie_texte.valeur_effort_structure[1],Sortie_texte.valeur_effort_structure[2],Sortie_texte.valeur_effort_structure[3]);
		}
		
	if(Sortie_texte.diametre_prise == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_diametre_prise);
		printf("Sortie_texte.valeur_diametre_prise %8.2lf \n",Sortie_texte.valeur_diametre_prise);
		}
	
	if(Sortie_texte.epaisseur_prise == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_epaisseur_prise);
		printf("Sortie_texte.valeur_epaisseur_prise %8.2lf \n",Sortie_texte.valeur_epaisseur_prise);
		}
	
	if(Sortie_texte.volume_capture == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_volume_capture);
		printf("Sortie_texte.valeur_volume_capture %8.2lf \n",Sortie_texte.valeur_volume_capture);
		}
	
	if(Sortie_texte.vitesse_courant == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_vitesse_courant);
		printf("Sortie_texte.valeur_vitesse_courant %8.2lf \n",Sortie_texte.valeur_vitesse_courant);
		}
	if(Sortie_texte.surface_filtree == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_surface_filtree);
		printf("Sortie_texte.valeur_surface_filtree %8.2lf \n",Sortie_texte.valeur_surface_filtree);
		}  	

	for( pa = 1 ; pa <= Sortie_texte.nb_longueur_cable ; pa++ )
		{
		do  
			{
			c=fgetc(fic2); 
			printf("%c",c);
			}
		while (c !=':');
		itmp = fscanf(fic2,"%lf ",&Sortie_texte.valeur_longueur_cable[pa]);
		printf("Sortie_texte.valeur_longueur_cable[pa] %8.2lf \n",Sortie_texte.valeur_longueur_cable[pa]);
		}/**/

 	if(Sortie_texte.inner_surface == 1)
  		{
		do  c=fgetc(fic2); while (c !=':');	
		printf("Sortie_texte.inner_surface");
		itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %8.2lf ",dtmp);
		itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %8.2lf ",dtmp);
		itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %8.2lf ",dtmp);
		itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %8.2lf ",dtmp);
		itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %8.2lf ",dtmp);
		itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %8.2lf ",dtmp);
		printf("\n");
  		}
 	if(Sortie_texte.inner_surface_triangulation == 1)
  		{
  		if (Sortie_texte.inner_surface == 0)
  			{
  			printf("ca va pas etre possible*****************************\n ");
  			}
  		else
  			{
  			printf("ca va  etre possible*****************************\n ");
			itmp = fscanf(fic2,"%d",&itmp);
  			printf("ca va  etre possible*****************************\n ");
			printf("triangulation inner surface: nb of points %d \n",itmp);
  			}
  		}
 	if(Sortie_texte.meridian == 1)
  		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%d",&itmq);		printf("nb points %d ",itmq);
		no = itmq;
		do  c=fgetc(fic2); while (c !=':');
  		for( pa = 1 ; pa <= no ; pa++ )
  			{
			itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %lf ",dtmp);
			itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %lf \n",dtmp);
  			}
  		}
 	if(Sortie_texte.meridian_X == 1)
  		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%d",&itmq);		printf("nb points %d ",itmq);
		no = itmq;
		do  c=fgetc(fic2); while (c !=':');
  		for( pa = 1 ; pa <= no ; pa++ )
  			{
			itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %lf ",dtmp);
			itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %lf \n",dtmp);
  			}
  		}
 	if(Sortie_texte.meridian_Y == 1)
  		{
		do  c=fgetc(fic2); while (c !=':');	
		itmp = fscanf(fic2,"%d",&itmq);		printf("nb points %d ",itmq);
		no = itmq;
		do  c=fgetc(fic2); while (c !=':');
  		for( pa = 1 ; pa <= no ; pa++ )
  			{
			itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %lf ",dtmp);
			itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %lf \n",dtmp);
  			}
  		}
 	if(Sortie_texte.meridian_Z == 1)
  		{
		do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%d",&itmq);		printf("nb points %d ",itmq);
		no = itmq;
		do  c=fgetc(fic2); while (c !=':');
  		for( pa = 1 ; pa <= no ; pa++ )
  			{
			itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %lf ",dtmp);
			itmp = fscanf(fic2,"%lf ",&dtmp);	printf(" %lf \n",dtmp);
  			}
  		}
 	if(Sortie_texte.curvilinear_codend_length == 1)
  		{
  		}
  	if(Opening_angle.nb_panel > 0)
    		{
		do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%d",&Opening_angle.nb_panel);	printf("nb points %d ",Opening_angle.nb_panel);
		do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%lf",&Opening_angle.pas);		printf(" %lf \n",Opening_angle.pas);
		for (pa = 1 ; pa <= Opening_angle.nb_panel ; pa++)
			{
			do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%d",&itmp);	printf("panel %d ",itmp);
			printf("Opening_angle.nb_tab %d ",Opening_angle.nb_tab);
			for (no = 1 ; no <= Opening_angle.nb_tab ; no++)
				{
				itmp = fscanf(fic2,"%lf",&dtmp);	printf(" %lf ",dtmp);
				}
			printf("\n");
			} 		
    		}

  	if(Opening_mesh.nb_panel > 0)
    		{
		do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%d",&Opening_mesh.nb_panel);	printf("nb points %d ",Opening_mesh.nb_panel);
		do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%lf",&Opening_mesh.pas);		printf(" %lf ",Opening_mesh.pas);
		do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%d",&Opening_mesh.nb_tab);		printf("nb points %d \n",Opening_mesh.nb_tab);

		for (pa = 1 ; pa <= Opening_mesh.nb_panel ; pa++)
			{
			do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%d",&itmq);	printf("panel %d ",itmq);
			for (no = 1 ; no <= Opening_mesh.nb_tab ; no++)
				{
				itmp = fscanf(fic2,"%lf",&dtmp);	printf(" %lf ",dtmp);
				}
			printf("\n");
			} 		
    		}
  	if(Opening_angle_stripe.nb_panel > 0)
    		{
		do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%d",&Opening_angle_stripe.nb_stripe);	printf("nb stripe %d ",Opening_angle_stripe.nb_stripe);
		do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%lf",&Opening_angle_stripe.pas);		printf("pas %lf \n",Opening_angle_stripe.pas);
		printf("nb_stripe %d \n",Opening_angle_stripe.nb_stripe);
		printf("nb_tab %d \n",Opening_angle_stripe.nb_tab);

		for (pa = 1 ; pa <= Opening_angle_stripe.nb_stripe ; pa++)
			{
			do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%d",&itmq);		printf("stripe %d ",itmq);
			do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%lf",&dtmp);	printf("from %lf ",dtmp);
			do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%lf",&dtmp);	printf("to %lf : ",dtmp);
			for (no = 1 ; no <= Opening_angle_stripe.nb_tab ; no++)
				{
				itmp = fscanf(fic2,"%lf",&dtmp);	printf(" %lf ",dtmp);
   				}
			printf("\n");
			} 		
    		}
  	if (Prise.dir_mesh_front > 0)
  		{
		do  c=fgetc(fic2); while (c !=':');	itmp = fscanf(fic2,"%lf",&dtmp);	printf("Prise.dir_mesh_front %lf\n",dtmp);
    		}

	if (Sortie_texte.panel_drag == 1)
		{
		do  c=fgetc(fic2); while (c !=':');	
		for (pa=1;pa<=Structure.NbTypesurf;pa++)
			{
			itmp = fscanf(fic2,"%d",&itmq);		printf("pa %d ",itmq);
			itmp = fscanf(fic2,"%lf",&panneau[pa].drag);	printf("drag %lf N\n",panneau[pa].drag);
			}
		}
	
	
	
	
	printf("fin de lecture du fichier %s\n",tonom);
	Flag_Fichier_charge_sta = 1;
	fclose(fic2);
		
	mesure_defaut_discretisation();
	
	SetMenuItemChecked(w[80],1);
	}  
	
	
void mesure_defaut_discretisation()
	{
	int ni,nj,nk,ng,nb,no,pa,voisin;
	int sommet1,sommet2,sommet3,som1,som2,som3;
	REEL defaut,defa[4],min_defa,nol,mol,nil,mil,defaut_max,defaut_mean;
	
	for (ni=1;ni<=Structure.nombreSurfaces;ni++)
		{
		nj = 0;		/*numero du premier   triangle voisin de ni*/
		nk = 0;		/*numero du second    triangle voisin de ni*/
		ng = 0;		/*numero du troisieme triangle voisin de ni*/
		nb = 0;		/*nb de triangles voisin de ni*/
		defaut = 0.0;	/*mesure de defaut de discretisation du triangle ni*/
 		sommet1 = surface[ni].extremite[1];
  		sommet2 = surface[ni].extremite[2];
  		sommet3 = surface[ni].extremite[3];
  		/*longueurs tendues des fils u et v*/
  		nil = sqrt(surface[ni].n[1]*surface[ni].n[1] + surface[ni].n[2]*surface[ni].n[2] + surface[ni].n[3]*surface[ni].n[3]);
  		mil = sqrt(surface[ni].m[1]*surface[ni].m[1] + surface[ni].m[2]*surface[ni].m[2] + surface[ni].m[3]*surface[ni].m[3]);
		for (no=1;no<=Structure.nombreSurfaces;no++)
			{
			if ((surface[no].type == surface[ni].type) && (no != ni))
				{
 				som1 = surface[no].extremite[1];
  				som2 = surface[no].extremite[2];
  				som3 = surface[no].extremite[3];
  				voisin = 0;
  				if ((sommet1 == som1) && (sommet2 == som2)) voisin = 1;
  				if ((sommet1 == som1) && (sommet2 == som3)) voisin = 1;
  				if ((sommet1 == som1) && (sommet3 == som2)) voisin = 1;
  				if ((sommet1 == som1) && (sommet3 == som3)) voisin = 1;
  				if ((sommet1 == som2) && (sommet2 == som1)) voisin = 1;
  				if ((sommet1 == som2) && (sommet2 == som3)) voisin = 1;
  				if ((sommet1 == som2) && (sommet3 == som1)) voisin = 1;
  				if ((sommet1 == som2) && (sommet3 == som3)) voisin = 1;
  				if ((sommet1 == som3) && (sommet2 == som1)) voisin = 1;
  				if ((sommet1 == som3) && (sommet2 == som2)) voisin = 1;
  				if ((sommet1 == som3) && (sommet3 == som1)) voisin = 1;
  				if ((sommet1 == som3) && (sommet3 == som2)) voisin = 1;
  				if ((sommet2 == som1) && (sommet3 == som2)) voisin = 1;
  				if ((sommet2 == som1) && (sommet3 == som3)) voisin = 1;
   				if ((sommet2 == som2) && (sommet3 == som1)) voisin = 1;
  				if ((sommet2 == som2) && (sommet3 == som3)) voisin = 1;
   				if ((sommet2 == som3) && (sommet3 == som1)) voisin = 1;
  				if ((sommet2 == som3) && (sommet3 == som2)) voisin = 1;
				if (voisin == 1)
  					{
  					nb = nb + 1;
  					/*
  					defa[nb] = surface[no].Nx*surface[ni].Nx + surface[no].Ny*surface[ni].Ny + surface[no].Nz*surface[ni].Nz;
  					*/
  				  	/*longueurs tendues des fils u et v*/
  					nol = sqrt(surface[no].n[1]*surface[no].n[1] + surface[no].n[2]*surface[no].n[2] + surface[no].n[3]*surface[no].n[3]);
  					mol = sqrt(surface[no].m[1]*surface[no].m[1] + surface[no].m[2]*surface[no].m[2] + surface[no].m[3]*surface[no].m[3]);
					defa[nb] = ((surface[no].n[1]*surface[ni].n[1] + surface[no].n[2]*surface[ni].n[2] + surface[no].n[3]*surface[ni].n[3]) /nol /nil
						 +  (surface[no].m[1]*surface[ni].m[1] + surface[no].m[2]*surface[ni].m[2] + surface[no].m[3]*surface[ni].m[3]) /mol /mil) 
						 / 2.0;
					}
				}
			}
 		if (nb > 1) 
 			{
 			min_defa = 1.0;
			for (no=1;no<=nb;no++)
				{
				/*recherche du voisin avec le defaut le plus eleve*/
				if (defa[no] < min_defa) min_defa = defa[no];
				}
			/*elimination du defaut le plus eleve*/
 			surface[ni].defaut_disc = - min_defa;
			for (no=1;no<=nb;no++)
				{
 				surface[ni].defaut_disc = surface[ni].defaut_disc + defa[no];
				}
 			surface[ni].defaut_disc = surface[ni].defaut_disc / (nb - 1);
 			}
 		else
 			{
 			surface[ni].defaut_disc = 1.0;
 			}
		}
	/*ecriture des defauts par panneaux*/
	for (no=1;no<=Structure.NbTypesurf;no++)
		{
		defaut_max  = 1.0;	/*mesure de defaut max  de discretisation du panneau no*/
		defaut_mean = 0.0;	/*mesure de defaut mean de discretisation du panneau no*/
		nb = 0;			/*nb surfaces dans le panneau*/
		for (ni=1;ni<=Structure.nombreSurfaces;ni++)
			{
			if (surface[ni].type == no)
				{
				nb++;
				if (surface[ni].defaut_disc < defaut_max) defaut_max = surface[ni].defaut_disc;
				defaut_mean = defaut_mean + surface[ni].defaut_disc;
				}
			}
		defaut_mean = defaut_mean / nb;
		printf("panneau = %5d  defaut max = %lf defaut mean = %lf\n",no,defaut_max,defaut_mean);
		}	
	}
	
	
	
	
