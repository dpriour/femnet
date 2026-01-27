#define PRINCIPAL 0
#include "phobos.h"

void charger_sta()
	
	/* 
	cette procedure effectue les lectures respectives d un fichier .mdg 
	et du fichier .sta correspondant
	afin d obtenir certaines informations utiles a l ecriture d un nouveau .sta ; 
	a savoir : sur les elements,
	sur les surfaces (pour .mdg) et sur les noeuds (pour .sta).
	
	ATTENTION : pour l utilisation de cette procedure il est necessaire de modifier 
	la localisation du .sta, 
	a savoir sous quelle repertoire il se trouve ! (cf autour de la ligne 26)             
	*/

	{
	int i,j,itmp,pa;
	char c;
	FILE *fic;
	
	/*newfic = (char *) GetFile(NULL);*/
	strcpy(newfic , (char *) GetFile("../data_2001"));
	/*strcpy(newfic , (char *) GetFile("/home/langevin/perso/dpriour/texte/hexa2/data_2001"));*/
	/*strcpy(newfic , (char *) GetFile("../../../hexa2/data_2001"));*/

	if(newfic[0])
		{
		printf("Fichier selectionne:\n %s\n" , newfic);
		}
	else
		{
		printf("fichier non trouve\n");
		return;
		}
        strcpy(fname3,newfic);
        j=strlen(fname3);
        while ((fname3[j])!='.' && j>0) j--;
        if (fname3[j]=='.') fname3[j]=0;

	printf("fname3 = %s \n",fname3);
	
	/* Lecture du fichier selectionne */	
	strcpy(newfic,fname3);
	strcat(newfic,".sta");
	fic = fopen(newfic,"r");
	printf("debut de lecture du fichier %s\n",newfic);
	
	
	for (i=1;i<=Structure.nb_total;i++)
		{
	  	itmp = fscanf(fic,"%d %lf %lf %lf\n",&j,&noeud[i].xcal,&noeud[i].ycal,&noeud[i].zcal);
	  	}
	
	for (i=1;i<=Structure.nb_barre;i++)
		{
		itmp = fscanf(fic,"%f\n",&barre[i].longueur_tendue);
		}
	
	for (i=1;i<=Structure.nombreSurfaces;i++)
		{
	  	itmp = fscanf(fic,"%lf %lf %lf  ",&surface[i].n[1],&surface[i].n[2],&surface[i].n[3]);
	  	itmp = fscanf(fic,"%lf %lf %lf\n",&surface[i].m[1],&surface[i].m[2],&surface[i].m[3]);
	  	}

	for (i=1;i<=Structure.nombreSurfHexa;i++)
		{
	  	itmp = fscanf(fic,"%lf %lf %lf  ",&surf_hexa[i].l[1],&surf_hexa[i].l[2],&surf_hexa[i].l[3]);
	  	itmp = fscanf(fic,"%lf %lf %lf  ",&surf_hexa[i].m[1],&surf_hexa[i].m[2],&surf_hexa[i].m[3]);
	  	itmp = fscanf(fic,"%lf %lf %lf\n",&surf_hexa[i].n[1],&surf_hexa[i].n[2],&surf_hexa[i].n[3]);
	  	}

	itmp = fscanf(fic,"%lf",&Prise.front);	  /**/
	printf("Prise.front %8.2lf \n",Prise.front);

	for( pa = 1 ; pa <= Sortie_texte.nb_distance ; pa++ )
		{
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf ",&Sortie_texte.valeur_distance[pa]);
		printf("Sortie_texte.valeur_distance[pa] %8.2lf \n",Sortie_texte.valeur_distance[pa]);
		}
  		
	for( pa = 1 ; pa <= Sortie_texte.nb_effort ; pa++ )
		{
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf ",&Sortie_texte.valeur_effort[pa]);
		printf("Sortie_texte.valeur_effort[pa] %8.2lf \n",Sortie_texte.valeur_effort[pa]);
		}
	
	for( pa = 1 ; pa <= Sortie_texte.nb_tension_element ; pa++ )
		{
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf ",&Sortie_texte.valeur_tension[pa]);
		printf("Sortie_texte.valeur_tension[pa] %8.2lf \n",Sortie_texte.valeur_tension[pa]);
		}
	
	for( pa = 1 ; pa <= Sortie_texte.nb_tension_coulisse ; pa++ )
		{
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf ",&Sortie_texte.valeur_tension_coulisse[pa]);
		printf("Sortie_texte.valeur_tension_coulisse[pa] %8.2lf \n",Sortie_texte.valeur_tension_coulisse[pa]);
		}
	
	for( pa = 1 ; pa <= Sortie_texte.nb_position ; pa++ )
		{
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf ",&Sortie_texte.valeur_position[pa]);
		printf("Sortie_texte.valeur_position[pa] %8.2lf \n",Sortie_texte.valeur_position[pa]);
		}
  			
	if(Sortie_texte.bottom_drag == 1)
		{
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf ",&Sortie_texte.valeur_bottom_drag);
		printf("Sortie_texte.valeur_bottom_drag %8.2lf \n",Sortie_texte.valeur_bottom_drag);
		}
  		
  	printf("fin de lecture du fichier %s\n",newfic);
	fclose(fic);
	}  
	
	
