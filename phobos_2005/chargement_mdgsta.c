#define PRINCIPAL 0
#include "phobos.h"

void charger_mdgsta()
	
	/* 
	cette procedure effectue les lectures respectives d un fichier .mdg et du fichier .sta correspondant
	afin d obtenir certaines informations utiles a l ecriture d un nouveau .sta ; a savoir : sur les elements,
	sur les surfaces (pour .mdg) et sur les noeuds (pour .sta).
	
	ATTENTION : pour l utilisation de cette procedure il est necessaire de modifier la localisation du .sta, 
	            a savoir sous quelle repertoire il se trouve ! (cf autour de la ligne 26)             
	*/



	{
	char tonom[128],t1[256],can[128],*buffer;
	char *pr,c;
	int i,j,tmp,mode,itmp;
	FILE *fic1, *fic2, *fic3;

	if (Structure.graphic == 1)
		{
		/*creer le fichier .mdg SI CE N EST PAS FAIT*/
		mode = GetMenuItemChecked(w[22]);
		if (mode == 0) creer_fichier_phobos();
		strcpy(oldfic , (char *) GetFile("../data_2001"));
		}
	if ((Structure.graphic == 2) || (Structure.graphic == 3))
		{
  		strcpy(oldfic,Structure.nomfichier2);
		}


	if(oldfic[0])
		{
		/*printf(stdout,"%s\n",oldfic);*/
		printf("Fichier selectionne: 			%s\n" , oldfic);
		Flag_Fichier_charge_mdg = 1;
		}
	else
		{
		printf("fichier non trouve\n");
		return;
		}
     	strcpy(fname2,oldfic);
        j=strlen(fname2);
        while ((fname2[j])!='.' && j>0) j--;
        if (fname2[j]=='.') fname2[j]=0;
		
	/* Lecture d une partie du fichier .mdg selectionne */	

  	strcpy(oldfic,fname2);
  	strcat(oldfic,".mdg");
  	printf("%s 				%s \n","fichier ",oldfic);

	fic1 = fopen(oldfic,"r");

  	if (fic1 == NULL) 
  		{ 
  		printf("charger_mdgsta: impossible d ouvrir le fichier %s\n",oldfic);
  	  	exit(0);
  		}
	printf("lecture du fichier 			%s\n",oldfic);
	
	buffer = fgets(t1,256,fic1);  /* t1 contient la premiere  ligne du fichier .mdg*/
	buffer = fgets(t1,256,fic1);  /* t1 contient la seconde   ligne du fichier .mdg*/
	buffer = fgets(t1,256,fic1);  /* t1 contient la troisieme ligne du fichier .mdg*/
	buffer = fgets(t1,256,fic1);  /* t1 contient la quatrieme ligne du fichier .mdg*/
	itmp = fscanf(fic1,"%d\n",&struct_old.nb_total);
	printf("Nombre de noeuds %d\n",struct_old.nb_total);

	do  pr=fgets(t1,256,fic1); while (pr == NULL || *pr =='\n');
	
	/* noeuds (non lus car lus directement dans le fichier .sta) ******/
	for (i=1;i<=struct_old.nb_total;i++) buffer = fgets(t1,256,fic1);
								     	
	/* éléments *******************************************************/
	do  pr=fgets(t1,256,fic1); while (pr == NULL || *pr =='\n');
	itmp = fscanf(fic1,"%d",&struct_old.nb_barre);
	printf("Nombre d elements %d\n",struct_old.nb_barre);
        do  pr=fgets(t1,256,fic1); while (pr == NULL || *pr =='\n');
	for (i=1;i<=struct_old.nb_barre;i++)
	 	{
	 	itmp = fscanf(fic1,"%d",&j);
	  	itmp = fscanf(fic1,"%d",&barre_old[i].noeud[1]);
	  	itmp = fscanf(fic1,"%d",&barre_old[i].noeud[2]);
	  	itmp = fscanf(fic1,"%f",&barre_old[i].pro[1]);
	  	itmp = fscanf(fic1,"%f",&barre_old[i].pro[2]);
	  	itmp = fscanf(fic1,"%d",&barre_old[i].type);
	  	/*itmp = fscanf(fic1,"%f\n",&barre_old[i].longueur_repos);*/
         	} 

  	/* coulisses ***********************************************************/
        do  pr=fgets(t1,256,fic1); while (pr == NULL || *pr =='\n');
        do  pr=fgets(t1,256,fic1); while (pr == NULL || *pr =='\n');
  	itmp = fscanf(fic1,"%d",&struct_old.nombreCoulisses);
	printf("Nombre de coulisses %d\n",struct_old.nombreCoulisses);
  	do  pr=fgets(t1,256,fic1); while (pr == NULL || *pr =='\n');
  	for (i=1;i<=struct_old.nombreCoulisses;i++)
  		{ 
    		itmp = fscanf(fic1,"%d %d %d %d ",&tmp,&coulisse_old[i].extremite[1],&coulisse_old[i].extremite[2],&coulisse_old[i].nb_noeud);
       		/**********************************************/
       		/*ici il y a +3 pour avoir suffisament de place pour mettre les extremites pour serie.c*/
       		coulisse_old[i].noeud = (int *) malloc((3 + coulisse_old[i].nb_noeud) * sizeof(int));
       		if (coulisse_old[i].noeud    == NULL)
               		{
               		printf("coulisse_old[i].noeud  1 = NULL  \n" );
               		exit(0);
               		}
       		/**********************************************/
  		for (j=1;j<=coulisse_old[i].nb_noeud;j++)
  			{ 
    			itmp = fscanf(fic1,"%d  ",&coulisse_old[i].noeud[j]);
    			}
 		}


  	for (i=1;i<=struct_old.nombreCoulisses;i++)
  		{ 
  		printf("coulisse %d   nb noeud %d \n",i,coulisse_old[i].nb_noeud);
  		for (j=1;j<=coulisse_old[i].nb_noeud;j++)
  			{ 
  			printf(" %d ",coulisse_old[i].noeud[j]);
    			}
  		printf(" \n");
 		}


        /* surfaces *********************************************************/
        do  pr=fgets(t1,256,fic1); while (pr == NULL || *pr =='\n');
	itmp = fscanf(fic1,"%d",&struct_old.nombreSurfaces);
	printf("Nombre de surfaces %d\n",struct_old.nombreSurfaces);
        do  pr=fgets(t1,256,fic1); while (pr == NULL || *pr =='\n');
	for (i=1;i<=struct_old.nombreSurfaces;i++)
	 	{
	 	itmp = fscanf(fic1,"%d",&j);
	  	itmp = fscanf(fic1,"%d",&surface_old[i].extremite[1]);
	  	itmp = fscanf(fic1,"%d",&surface_old[i].extremite[2]);
	  	itmp = fscanf(fic1,"%d",&surface_old[i].extremite[3]);
	  	itmp = fscanf(fic1,"%lf",&surface_old[i].U[1]);
	  	itmp = fscanf(fic1,"%lf",&surface_old[i].V[1]);
	  	itmp = fscanf(fic1,"%lf",&surface_old[i].U[2]);
	  	itmp = fscanf(fic1,"%lf",&surface_old[i].V[2]);
	  	itmp = fscanf(fic1,"%lf",&surface_old[i].U[3]);
	  	itmp = fscanf(fic1,"%lf",&surface_old[i].V[3]);
	  	itmp = fscanf(fic1,"%d",&surface_old[i].type);
	  	itmp = fscanf(fic1,"%d",&surface_old[i].type);
		/*printf("surface_old[%d].type = %d\n",i,surface_old[i].type);*/
	 	}
        
        /* surfaces hexagonales**********************************************/
        do  pr=fgets(t1,256,fic1); while (pr == NULL || *pr =='\n');
	itmp = fscanf(fic1,"%d",&struct_old.nombreSurfHexa);
	printf("Nombre de surfaces hexagonales %d\n",struct_old.nombreSurfHexa);
        do  pr=fgets(t1,256,fic1); while (pr == NULL || *pr =='\n');
	for (i=1;i<=struct_old.nombreSurfHexa;i++)
	 	{
	 	itmp = fscanf(fic1,"%d",&j);
	  	itmp = fscanf(fic1,"%d",&surf_hexa_old[i].extremite[1]);
	  	itmp = fscanf(fic1,"%d",&surf_hexa_old[i].extremite[2]);
	  	itmp = fscanf(fic1,"%d",&surf_hexa_old[i].extremite[3]);
	  	itmp = fscanf(fic1,"%lf",&surf_hexa_old[i].U[1]);
	  	itmp = fscanf(fic1,"%lf",&surf_hexa_old[i].V[1]);
	  	itmp = fscanf(fic1,"%lf",&surf_hexa_old[i].U[2]);
	  	itmp = fscanf(fic1,"%lf",&surf_hexa_old[i].V[2]);
	  	itmp = fscanf(fic1,"%lf",&surf_hexa_old[i].U[3]);
	  	itmp = fscanf(fic1,"%lf",&surf_hexa_old[i].V[3]);
	  	itmp = fscanf(fic1,"%d",&surf_hexa_old[i].type);
	  	itmp = fscanf(fic1,"%d",&surf_hexa_old[i].type);
		/*printf("surf_hexa_old[%d].type = %d\n",i,surf_hexa_old[i].type);*/
	 	}
	fclose(fic1);
	printf("fin de lecture du fichier 		%s\n",oldfic);

	
	
	
	/* Lecture d une partie de l ancien fichier .sta correspondant (s il existe) sous le repertoire approprie */	
	
	strcpy(tonom,fname2);
	strcat(tonom,".sta");
	fic2 = fopen(tonom,"r");
	if (fic2 == NULL) 
	 	{ 
	 	printf("* charger_mdgsta * Impossible d ouvrir le fichier %s\n",tonom);
	   	exit(0);
	 	}
	printf("lecture du fichier 			%s\n",tonom);
	
	for (i=1;i<=struct_old.nb_total;i++)
	  	itmp = fscanf(fic2,"%d %lf %lf %lf\n",&j,&noeud_old[i].x,&noeud_old[i].y,&noeud_old[i].z);
	
	for (i=1;i<=struct_old.nb_barre;i++)
		itmp = fscanf(fic2,"%f\n",&barre_old[i].elongation);
	
	for (i=1;i<=struct_old.nombreSurfaces;i++)
		buffer = fgets(can,80,fic2);

	for (i=1;i<=struct_old.nombreSurfHexa;i++)
		buffer = fgets(can,80,fic2);

	itmp = fscanf(fic2,"%lf",&Prise.front);	  

	fic3 = fopen("end_sta.txt","w");
    	while((c = getc(fic2)) != EOF)	putc(c, fic3);	
	fclose(fic3);

	printf("fin de lecture du fichier 		%s\n",tonom);
	Flag_Fichier_charge_sta = 1;
	fclose(fic2);
	if (Structure.graphic == 1)
		{
		SetMenuItemChecked(w[98],1);
		}
	}  
	
	
void creer_fichier_sta()
	{
	/*
	cree un fichier *.sta a partir de *.mdg, **.mdg et **.sta, ou **.don et *.don sont des fichiers differant
	juste par leur pas de maillage. Cela permet d'accelerer la convergence du code 4ch19 pour **.mdg,a partir du 
	moment ou un equilibre statique est prealablement obtenu pour le fichier *.mdg .
	ATTENTION : pour l utilisation de cette procedure il est necessaire de modifier la localisation du .sta, 
	            a savoir sous quelle repertoire il sera cree !              
	*/

	char tonom[126],c,command[1000];
	int mode;
  	FILE   *f3,*f2;
	
	if (Structure.graphic == 1)
		{
		/*CHARGER LES FICHIERS .mdg et .sta SI CE N EST PAS FAIT*/
		mode = GetMenuItemChecked(w[98]);
		if (mode == 0) charger_mdgsta();
		}

	if ( (Flag_Fichier_cree_mdg == 0) || (Flag_Fichier_charge_sta == 0) )
		{
		printf(" selectionnez un fichier *.mdg ");
		exit(0);
		}

	strcpy(tonom,fname1);
	strcat(tonom,".sta");
	f3 = fopen(tonom,"w");
  	if (f3 == NULL) 
  		{ 
  		printf("* creer_fichier_sta * impossible d ouvrir le fichier %s\n",tonom);
  	  	exit(0);
  		}
	/*calcul des nouvelles coordonnees des noeuds se trouvant sur les elements*/
	noeud_element();

	/*calcul des nouvelles coordonnees des noeuds se trouvant sur les panneaux*/
	noeud_panneau();

	/*ecriture des nouvelles coordonnees des noeuds et des longueurs tendues des nouveaux elements*/
	printf("ecriture de ce fichier 			%s\n",tonom);
	ecriture_sta(f3);	
	printf("fin d ecriture de ce fichier 		%s\n",tonom);
	
	f2 = fopen("end_sta.txt","r");
    	while((c = getc(f2)) != EOF)	putc(c, f3);	
	fclose(f2);

	fclose(f3);
	sprintf(command,"rm end_sta.txt");	
	int retsystem = system(command);/*delete end_sta.txt file*/
	if (retsystem == -1) 
		{
		perror("system");
		}
	//system(command);	/*delete end_sta.txt file*/


	if (Structure.graphic == 1)
		{
		SetMenuItemChecked(w[97],1);
		}
	}
	


void noeud_element()
	{
	/* 
	cette procedure determine les nouvelles coordonnees d un noeud de **.mdg se trouvant sur un element
	*/
	
	int i,j,k,no_barre_old[3],no_new;
	float t[3],d[3],l[3];
	
	for (i=1;i<=Structure.nb_barre;i++) 
		{
		for (k=1;k<=2;k++)
	  		{
	    		/* determination du numero de la barre d un element de *.mdg contenant le noeud courant*/
	    		no_new = total2global[barre[i].noeud[k]];
	    		for (j=1;j<=struct_old.nb_barre;j++)
	    			{
	      			if ((barre_old[j].type == barre[i].type)  && (barre_old[j].pro[1] <= barre[i].pro[k]) && (barre_old[j].pro[2] >= barre[i].pro[k]))
	      				{ 
	      				no_barre_old[k] = j;
		  	  	  	break;
	      	  	  	  	}
	    	  	  	}
	
	      	  	/* determination de la position de ce noeud courant sur la barre de numero no_barre et calcul des nouvelles coordonnees*/
	      	  	if ( noeud_global[no_new].flag_sta == 0 )
	      	  	  	{ 
	      	  	  	l[k] =   barre_old[no_barre_old[k]].pro[2] - barre_old[no_barre_old[k]].pro[1];
	        	  	d[k] = - barre_old[no_barre_old[k]].pro[1] + barre[i].pro[k];
	      			t[k] = d[k] / l[k];
	      			noeud_global[no_new].x = (1. - t[k]) * noeud_old[barre_old[no_barre_old[k]].noeud[1]].x
	      			       			     + t[k]  * noeud_old[barre_old[no_barre_old[k]].noeud[2]].x;
	      			noeud_global[no_new].y = (1. - t[k]) * noeud_old[barre_old[no_barre_old[k]].noeud[1]].y
	      			       			     + t[k]  * noeud_old[barre_old[no_barre_old[k]].noeud[2]].y;
	      			noeud_global[no_new].z = (1. - t[k]) * noeud_old[barre_old[no_barre_old[k]].noeud[1]].z
	      			       			     + t[k]  * noeud_old[barre_old[no_barre_old[k]].noeud[2]].z;
	      			noeud_global[no_new].flag_sta = 1;
	    			}
	  		}
		}
	}
	

void noeud_panneau()
	{
	/* 
	cette procedure determine les nouvelles coordonnees d un noeud de **.mdg se trouvant a l interieur d un panneau
	*/
	
	/*int appartient_triangle(int noe,int typ,int notri);*/
	/*int appartient_triangle2(int noe,int typ);*/
	int i,j,sommet,num_old,numero,inter_Type;
/* debut modifdp du 4 mars 2010*/
	/*float u1,v1,u2,v2,u3,v3,um,vm,alpha,beta,denom;*/
	float u1,v1,u2,v2,u3,v3,um,vm,alpha,beta,denom,tempx,tempy,tempz;
/* fin modifdp du 4 mars 2010*/
	
	/*printf("noeud_panneau Structure.nombreSurfaces = %d\n",Structure.nombreSurfaces);*/
	for (i=1;i<=Structure.nombreSurfaces;i++)
		{
		for (j=1;j<=3;j++)
			{
	        	/*printf("j = %d \n",j); */
			sommet = surface[i].extremite[j];
			numero = total2global[sommet];

			/*if (numero == 461) 
				{
				printf("j = %d \n",j);
				printf("surface = %d, sommet_total = %d, sommet_global = %d noeud_global[%d].flag_sta = %d ",i,sommet,numero,numero,noeud_global[numero].flag_sta); 
				printf("surface[%d].type = %d \n",i,surface[i].type);
				}*/

			if (noeud_global[numero].flag_sta == 0)
				{  
	       			/* determination du triangle de *.mdg contenant le sommet courant de **.mdg*/
				/*num_old = appartient_triangle(sommet,surface[i].type,i);*/
				num_old = appartient_triangle2(sommet,surface[i].type);
				/*printf("num_old = %d\n",num_old); */

				/*if (numero == 461) 
					{
					printf("num_old = %d\n",num_old);
					}*/

				/* determination des coefficients alpha et beta definis tels que 1m = alpha*12 + beta*13 */
				u1 = surface_old[num_old].U[1];  
				u2 = surface_old[num_old].U[2];  
				u3 = surface_old[num_old].U[3];  
				v1 = surface_old[num_old].V[1];  
				v2 = surface_old[num_old].V[2];  
				v3 = surface_old[num_old].V[3];  
				um = noeud[sommet].U;  
				vm = noeud[sommet].V; 

				/*if (numero == 461) 
					{
					printf("u1 u2 u3 = %lf %lf %lf\n",u1,u2,u3);
					printf("v1 v2 v3 = %lf %lf %lf\n",v1,v2,v3);
					printf("um vm = %lf %lf \n",um,vm);
					}*/

				denom = (u2-u1)*(v3-v1) - (u3-u1)*(v2-v1);

				/* precautions en cas de denominateur nul*/
				if (fabs(denom) <= 0.00001)
	       				 {  
	         			 printf(" * noeud_panneau * denom = %f\n",denom);  
	         			 printf("u1= %f, v1= %f, u2= %f, v2= %f, u3= %f, v3= %f\n",u1,v1,u2,v2,u3,v3);
					 printf("um vm = %lf %lf \n",um,vm);
					 exit(0);
	       				 } 
				else
	       				 {
	         			 alpha =   ( vm*(u1-u3) + um*(v3-v1) - (u1*v3-v1*u3) ) / denom;
	         			 beta  =   ( vm*(u2-u1) + um*(v1-v2) + (u1*v2-u2*v1) ) / denom;
	       				 }

				/*if (numero == 461) 
					{
					printf("denom = %lf %lf %lf\n",denom);
					printf("alpha beta = %lf %lf \n",alpha,beta);
					}*/

	       			if (alpha<0.0) alpha = 0.0;
	       			if (alpha>1.0) alpha = 1.0;
	       			if (beta <0.0) beta  = 0.0;
	       			if (beta >1.0) beta  = 1.0;

				/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
				inter_Type = noeud_global[numero].type;
/* debut modifdp du 4 mars 2010*/
				if (Structure.orientation == 1)		/*in case of symmetry plane keep the data value*/
					{
					if (TypeNoeud[inter_Type].symx == 1)	tempx = noeud_global[numero].z;
					if (TypeNoeud[inter_Type].symy == 1)	tempy = noeud_global[numero].x;
					if (TypeNoeud[inter_Type].symz == 1)	tempz = noeud_global[numero].y;
					}
				if (Structure.orientation == 2)
					{
					if (TypeNoeud[inter_Type].symx == 1)	tempx = noeud_global[numero].y;
					if (TypeNoeud[inter_Type].symy == 1)	tempy = noeud_global[numero].z;
					if (TypeNoeud[inter_Type].symz == 1)	tempz = noeud_global[numero].x;
					}
				if (Structure.orientation == 3)
					{
					if (TypeNoeud[inter_Type].symx == 1)	tempx = noeud_global[numero].x;
					if (TypeNoeud[inter_Type].symy == 1)	tempy = noeud_global[numero].y;
					if (TypeNoeud[inter_Type].symz == 1)	tempz = noeud_global[numero].z;
					}
					
				if (TypeNoeud[inter_Type].symy == 1)
					{
	         			printf("numero %4d avant x     = %10.3f y     = %10.3f z     = %10.3f  ",numero,noeud_global[numero].x,noeud_global[numero].y,noeud_global[numero].z); 
					}
/* fin modifdp du 4 mars 2010*/
				noeud_global[numero].x = alpha * ( noeud_old[surface_old[num_old].extremite[2]].x - noeud_old[surface_old[num_old].extremite[1]].x )
	       						+ beta * ( noeud_old[surface_old[num_old].extremite[3]].x - noeud_old[surface_old[num_old].extremite[1]].x )
	       			                		 + noeud_old[surface_old[num_old].extremite[1]].x;
				noeud_global[numero].y = alpha * ( noeud_old[surface_old[num_old].extremite[2]].y - noeud_old[surface_old[num_old].extremite[1]].y )
	       						+ beta * ( noeud_old[surface_old[num_old].extremite[3]].y - noeud_old[surface_old[num_old].extremite[1]].y )
	       				        		+ noeud_old[surface_old[num_old].extremite[1]].y;
				noeud_global[numero].z = alpha * ( noeud_old[surface_old[num_old].extremite[2]].z - noeud_old[surface_old[num_old].extremite[1]].z )
	       						+ beta * ( noeud_old[surface_old[num_old].extremite[3]].z - noeud_old[surface_old[num_old].extremite[1]].z )
	       				        		+ noeud_old[surface_old[num_old].extremite[1]].z;
				noeud_global[numero].flag_sta = 1; 				      
/* debut modifdp du 4 mars 2010*/
				if (TypeNoeud[inter_Type].symx == 1)	noeud_global[numero].x = tempx;
				if (TypeNoeud[inter_Type].symy == 1)	noeud_global[numero].y = tempy;
				if (TypeNoeud[inter_Type].symz == 1)	noeud_global[numero].z = tempz;
				
				if (TypeNoeud[inter_Type].symy == 1)
					{
	         			printf("apres x     = %10.3f y     = %10.3f z     = %10.3f\n",noeud_global[numero].x,noeud_global[numero].y,noeud_global[numero].z); 
					}
/* fin modifdp du 4 mars 2010*/
				/*
				if(surface[i].type == 6)
					{
	         			printf("sommet_global = %d num_old = %d\n",numero,num_old); 
	         			printf("alpha = %f beta = %f\n",alpha,beta); 
	         			printf("u1 = %f v1 = %f\n",u1,v1); 
	         			printf("u2 = %f v2 = %f\n",u2,v2); 
	         			printf("u3 = %f v3 = %f\n",u3,v3); 
	         			printf("um = %f vm = %f\n",um,vm); 
	         			printf("xold1 = %f yold1 = %f zold1 = %f\n",noeud_old[surface_old[num_old].extremite[1]].x,noeud_old[surface_old[num_old].extremite[1]].y,noeud_old[surface_old[num_old].extremite[1]].z); 
	         			printf("xold2 = %f yold2 = %f zold2 = %f\n",noeud_old[surface_old[num_old].extremite[2]].x,noeud_old[surface_old[num_old].extremite[2]].y,noeud_old[surface_old[num_old].extremite[2]].z); 
	         			printf("xold3 = %f yold3 = %f zold3 = %f\n",noeud_old[surface_old[num_old].extremite[3]].x,noeud_old[surface_old[num_old].extremite[3]].y,noeud_old[triangle_old[num_old].extremite[3]].z); 
	         			printf("x     = %f y     = %f z     = %f\n",noeud_global[numero].x,noeud_global[numero].y,noeud_global[numero].z); 
					}
				*/
				}

			}
		}
	
	for (i=1;i<=Structure.nombreSurfHexa;i++)
	{
	  for (j=1;j<=3;j++)
	  {
	    sommet = surf_hexa[i].extremite[j];
	    numero = total2global[sommet];
	    if (noeud_global[numero].flag_sta == 0)
	    {  
	       /* determination du surf_hexa de *.mdg contenant le sommet courant de **.mdg*/
		num_old = appartient_tri_hexa2(sommet,surf_hexa[i].type);
		
	       /* determination des coefficients alpha et beta definis tels que 1m = alpha*12 + beta*13 */
	       u1 = surf_hexa_old[num_old].U[1];  
	       u2 = surf_hexa_old[num_old].U[2];  
	       u3 = surf_hexa_old[num_old].U[3];  
	       v1 = surf_hexa_old[num_old].V[1];  
	       v2 = surf_hexa_old[num_old].V[2];  
	       v3 = surf_hexa_old[num_old].V[3];  
	       um = noeud[sommet].U;  
	       vm = noeud[sommet].V; 
	       
	       denom = (u2-u1)*(v3-v1) - (u3-u1)*(v2-v1);

	       /* precautions en cas de denominateur nul*/
	       if (fabs(denom) <= 0.00001)
	       		{  
	         	printf(" * noeud_panneau * denom = %f\n",denom);exit(0);  
	         	printf("u1= %f, v1= %f, u2= %f, v2= %f, u3= %f, v3= %f\n",u1,v1,u2,v2,u3,v3);
	       		} 
	       else
	       		{
	         	alpha =   ( vm*(u1-u3) + um*(v3-v1) - (u1*v3-v1*u3) ) / denom;
	         	beta  =   ( vm*(u2-u1) + um*(v1-v2) + (u1*v2-u2*v1) ) / denom;
	       		}
	       /*if ( (alpha<0.0) || (alpha>1.) || (beta<0.0) || (beta>1.0)) 
	       		printf("alpha = %f , beta = %f du(s) a l imprecision machine\n",alpha,beta);*/
	       if ((numero == 83) || (numero == 100)) 
	       	{
	       	printf(" numero = %4d ",numero);
	       	printf("alpha = %f  %f  \n",alpha,beta);  
	       	}
	       	if (alpha<0.0) alpha = 0.0;
	       	if (alpha>1.0) alpha = 1.0;
	       	if (beta <0.0) beta  = 0.0;
	       	if (beta >1.0) beta  = 1.0;
	       		       
	       /* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
	       noeud_global[numero].x = alpha * ( noeud_old[surf_hexa_old[num_old].extremite[2]].x - noeud_old[surf_hexa_old[num_old].extremite[1]].x )
	       			       + beta * ( noeud_old[surf_hexa_old[num_old].extremite[3]].x - noeud_old[surf_hexa_old[num_old].extremite[1]].x )
	       			                + noeud_old[surf_hexa_old[num_old].extremite[1]].x;
	       noeud_global[numero].y = alpha * ( noeud_old[surf_hexa_old[num_old].extremite[2]].y - noeud_old[surf_hexa_old[num_old].extremite[1]].y )
	       			       + beta * ( noeud_old[surf_hexa_old[num_old].extremite[3]].y - noeud_old[surf_hexa_old[num_old].extremite[1]].y )
	       				        + noeud_old[surf_hexa_old[num_old].extremite[1]].y;
	       noeud_global[numero].z = alpha * ( noeud_old[surf_hexa_old[num_old].extremite[2]].z - noeud_old[surf_hexa_old[num_old].extremite[1]].z )
	       			       + beta * ( noeud_old[surf_hexa_old[num_old].extremite[3]].z - noeud_old[surf_hexa_old[num_old].extremite[1]].z )
	       				        + noeud_old[surf_hexa_old[num_old].extremite[1]].z;
	       noeud_global[numero].flag_sta = 1; 				      
	    }
	    
	  }
	}
	
	}


int appartient_triangle(int noe,int typ,int notri)
	{
	int k;
	float u1,u2,u3,v1,v2,v3,um,vm,p1,p2,p3,orient;
	
	
	for (k=1;k<=struct_old.nombreSurfaces;k++)
		{
		printf("k = %d  \n",k);
	  	if (surface_old[k].type == typ)	
	  		{
	  		/*
	  		pour qu un sommet appartienne a un triangle de "old".mdg, 
	  		il est necessaire que les types des triangles correspondent
	  		*/
	    		u1 = surface_old[k].U[1];
	    		u2 = surface_old[k].U[2];
	    		u3 = surface_old[k].U[3];
	    		v1 = surface_old[k].V[1];
	    		v2 = surface_old[k].V[2];
	    		v3 = surface_old[k].V[3];
	    		um = noeud[noe].U;
	    		vm = noeud[noe].V;
	  
	    		/* 
	    		pour que M soit dans le triangle 123 , 
	    		il est necessaire et suffisant que les produits vectoriels 12-1M, 23-2M et 31-3M 
	    		(calcules en nombre de mailles U*V) soient du signe defini par 
	    		l orientation des triangles dans "old".mdg
	    		*/
	    		p1 = (u2-u1) * (vm-v1) - (v2-v1) * (um-u1);
	    		p2 = (u3-u2) * (vm-v2) - (v3-v2) * (um-u2);
	    		p3 = (u1-u3) * (vm-v3) - (v1-v3) * (um-u3);
	    		orient = (u2-u1) * (v3-v1) - (v2-v1) * (u3-u1); 
	    		if(total2global[noe]==190)
	    			{
				printf(" \n");
				printf("k %d \n",k);
				printf("u1 %f u2 %f u3 %f \n",u1,u2,u3);
				printf("v1 %f v2 %f v3 %f \n",v1,v2,v3);
				printf("um %f vm %f \n",um,vm);
				printf("p1 %f p2 %f p3 %f \n",p1,p2,p3);
				printf("orient %f \n",orient);
	    			}
	    
	    		/* si bien que ... */
	    		if ( ( p1*orient/fabs(orient) >= -0.4) && 
	         	     ( p2*orient/fabs(orient) >= -0.4) && 
	         	     ( p3*orient/fabs(orient) >= -0.4) ) return(k);
	  		}

		}
		printf("* appartient_triangle *\n");
		printf("le noeud %d du triangle %d n appartient a aucun triangle du maillage de %s \n",total2global[noe],notri,oldfic);
		printf("Ce noeud est probablement sur le bord d'un panneau, s'il tel est le cas MODIFIER les valeurs proches de 0 dans chargement_mdgsta.c\n");
		exit(0);
	}
	
	
int appartient_triangle2(int noe,int typ)
	{
	int k,tri_min;
	double u1,u2,u3,v1,v2,v3,um,vm,p1,p2,p3,orient;
	double q1,q2,q3;
	float surface_min,surface_courante,surf_ref,ratio;

	/*
	float surface_triangle(float X1, float Y1, float X2, float Y2, float X3, float Y3 );
	*/
	
	um = (double) noeud[noe].U;
	vm = (double) noeud[noe].V;
	tri_min = 0;	/*numero du triangle old auquel appartient le point m*/
	for (k=1;k<=struct_old.nombreSurfaces;k++)
		{
		/*printf("surface_old[%d].type = %d \n",k,surface_old[k].type);*/
	  	if (surface_old[k].type == typ)	
	  		{
	  		/*
	  		pour qu un sommet appartienne a un triangle de "old".mdg, 
	  		il est necessaire que la surface du triangle de old = la somme des 
	  		surfaces des 3 triangles 12m m23 et 1m3
	  		en fait comme il est difficile de verifier l egalite entre 2 floats
	  		m appartient au triangle de old dont la somme des 3 triangles 12m m23 et 1m3
	  		rapporte a la surface de ref est la plus petite
	  		*/
	  		
	    		u1 = (double) surface_old[k].U[1];
	    		u2 = (double) surface_old[k].U[2];
	    		u3 = (double) surface_old[k].U[3];
	    		v1 = (double) surface_old[k].V[1];
	    		v2 = (double) surface_old[k].V[2];
	    		v3 = (double) surface_old[k].V[3];
	  
	    		surf_ref = surface_triangle((float) u1, (float) v1, (float) u2, (float) v2, (float) u3, (float) v3 );
	    		surface_courante  = surface_triangle((float) u1, (float) v1, (float) u2, (float) v2, (float) um, (float) vm );
	    		/*if ((noe == 504) && (typ == 4))
	    			{
				printf("k %d surf_ref %f surface_courante %f u %lf %lf %lf %lf %lf %lf ",k,surf_ref,surface_courante,u1, v1, u2, v2, um, vm);
	    			}*/
	    		surface_courante += surface_triangle((float) um, (float) vm, (float) u2, (float) v2, (float) u3, (float) v3 );
	    		/*if ((noe == 504) && (typ == 4))
	    			{
				printf(" %f ",surface_courante);
	    			}*/
	    		surface_courante += surface_triangle((float) u1, (float) v1, (float) um, (float) vm, (float) u3, (float) v3 );
	    		/*if ((noe == 504) && (typ == 4))
	    			{
				printf(" %f ",surface_courante);
	    			}*/
			if(surf_ref == 0.0)
				{
				printf("surface ref %d = %f \n",k,surf_ref);
				surf_ref = 0.1;
				/*exit(0);*/
				}
	    		ratio = surface_courante / surf_ref;
	    		if (tri_min == 0)	
	    			{
	    			surface_min = ratio;
	    			tri_min = k;
				/*printf("noe = %d typ = %d k = %d surface_min = %lf   \n",noe,typ,k,surface_min);*/
	    			}
	    		if (surface_min > ratio)
	    			{
	    			surface_min = ratio;
	    			tri_min = k;
				/*printf("noe = %d typ = %d k = %d surface_min = %lf   \n",noe,typ,k,surface_min);*/
	    			}
	    		/*if ((noe == 504) && (typ == 4))
	    			{
				printf("tri_min %d\n",tri_min);
	    			}*/
	  		}
		}
		return(tri_min);
	}
	
void position_interieur_triangle(double um,double vm,double u1,double v1,double u2,double v2,double u3,double v3, double *alpha,double *beta)
	{
	/*1m = alpha 12 + beta 13*/
	double denom;
       	denom = (u3-u1)*(v2-v1) - (u2-u1)*(v3-v1);
       	/* precautions en cas de denominateur nul*/
       	if (fabs(denom) <= 0.00001)
	       	{ 
		printf("denominateur =  %lf\n",denom);
	       	exit(0);
	       	} 
     	*alpha =   ( (vm-v1)*(u3-u1) - (um-u1)*(v3-v1) ) / denom;
     	*beta  =   ( (um-u1)*(v2-v1) - (vm-v1)*(u2-u1) ) / denom;
	}
	
int position_interieur_triangle2(double um,double vm,double u1,double v1,double u2,double v2,double u3,double v3, double *alpha,double *beta)
	{
	/*1m = alpha 12 + beta 13*/
	int result;
	double denom;
	result = 99;
	
       	denom = (u3-u1)*(v2-v1) - (u2-u1)*(v3-v1);
       	/* precautions en cas de denominateur nul*/
       	if (fabs(denom) <= 0.00001)
	       	{ 
		printf("denominateur =  %lf\n",denom);
	       	exit(0);
	       	} 
     	*alpha =   ( (vm-v1)*(u3-u1) - (um-u1)*(v3-v1) ) / denom;
     	*beta  =   ( (um-u1)*(v2-v1) - (vm-v1)*(u2-u1) ) / denom;
	printf("   um %5.2lf vm %5.2lf ", um,vm);
	printf("alpha_beta %5.2lf %5.2lf ",*alpha,*beta);
     	if ((*alpha > 0.0) && (*alpha < 1.0) && (*beta > 0.0) && (*beta < (1.0-*alpha)))	
     		{
     		result = 0;	/*m is inside the triangle 123*/
		printf("0  um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha == 0.0) && (*beta == 0.0))							
     		{
     		result = 1;	/*m on 1*/
		printf("1  um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha == 1.0) && (*beta == 0.0))
     		{
     		result = 2;	/*m on 2*/
		printf("2  um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha == 0.0) && (*beta == 1.0))
     		{
     		result = 3;	/*m on 3*/
		printf("3  um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha > 0.0) && (*alpha < 1.0) && (*beta == (1.0-*alpha)))
     		{
     		result = 4;	/*m on 23*/
		printf("4  um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha == 0.0) && (*beta > 0.0) && (*beta < (1.0-*alpha)))
     		{
     		result = 5;	/*m on 31*/
		printf("5  um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha > 0.0) && (*alpha < 1.0) && (*beta == 0.0))					
     		{
     		result = 6;	/*m on 12*/
		printf("6  um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha > 0.0) && (*alpha < 1.0) && (*beta > (1.0-*alpha)))
     		{
     		result = 7;	/*m out side 23*/
		printf("71 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
    	if ((*alpha >= 1.0) && (*beta > 0.0))
     		{
     		result = 7;	/*m out side 23*/
		printf("72 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha < 0.0) && (*beta > 0.0) && (*beta < (1.0-*alpha)))
     		{
     		result = 8;	/*m out side 31*/
		printf("8  um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha > 0.0) && (*alpha < 1.0) && (*beta < 0.0))
     		{
     		result = 9;	/*m out side 12*/
		printf("91 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha >= 1.0) && (*beta < (1.0-*alpha)))
     		{
     		result = 9;	/*m out side 12*/
		printf("92 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha < 0.0) && (*beta < 0.0))
     		{
     		result = 10;	/*m out side 1*/
		printf("10 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha > 1.0) && (*beta > (1.0-*alpha)))
     		{
     		result = 11;	/*m out side 2*/
		printf("11 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha < 0.0) && (*beta > (1.0-*alpha)))
     		{
     		result = 12;	/*m out side 3*/
		printf("12 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha > 1.0) && (*beta == (1.0-*alpha)))
     		{
     		result = 13;	/*m on 23 out side 2*/
		printf("13 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha < 0.0) && (*beta == (1.0-*alpha)))
     		{
     		result = 14;	/*m on 23 out side 3*/
		printf("14 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha == 0.0) && (*beta > (1.0-*alpha)))
     		{
     		result = 15;	/*m on 31 out side 3*/
		printf("15 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
     	if ((*alpha == 0.0) && (*beta < 0.0))
     		{
     		result = 16;	/*m on 31 out side 1*/
		printf("16 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
    	if ((*alpha < 0.0) && (*beta == 0.0))
     		{
     		result = 17;	/*m on 12 out side 1*/
		printf("17 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
    	if ((*alpha > 1.0) && (*beta == 0.0))
     		{
     		result = 18;	/*m on 12 out side 2*/
		printf("18 um %5.2lf vm %5.2lf ", um,vm);
		printf("alpha_beta %5.2lf %5.2lf result %3d  ",*alpha,*beta,result);
     		}
    	return result;
	}
	
int appartient_triangle_contour(double um,double vm,int pa)
	{
	int k,tri_min,sommet1,sommet2,sommet3;
	double u1,u2,u3,v1,v2,v3,p1,p2,p3,orient;
	double q1,q2,q3;
	float surface_min,surface_courante,surf_ref,ratio;

	/*
	float surface_triangle(float X1, float Y1, float X2, float Y2, float X3, float Y3 );
	*/
	
	tri_min = 0;	/*numero du triangle auquel appartient le point m*/
	for (k=1;k<=panneau[pa].nb_triangle_contour;k++)
  		{
  		/*
  		pour qu un sommet appartienne a un triangle contour, 
  		il est necessaire que la surface du triangle contour = la somme des 
  		surfaces des 3 triangles 12m m23 et 1m3
  		en fait comme il est difficile de verifier l egalite entre 2 floats
  		m appartient au triangle de old dont la somme des 3 triangles 12m m23 et 1m3
  		rapporte a la surface de ref est la plus petite
  		*/
		sommet1 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[k][1]];
		sommet2 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[k][2]];
		sommet3 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[k][3]];
  		
    		u1 = (double) noeud[sommet1].U;	v1 = (double) noeud[sommet1].V;
    		u2 = (double) noeud[sommet2].U;	v2 = (double) noeud[sommet2].V;
    		u3 = (double) noeud[sommet3].U;	v3 = (double) noeud[sommet3].V;
  
    		surf_ref = surface_triangle((float) u1, (float) v1, (float) u2, (float) v2, (float) u3, (float) v3 );
    		surface_courante  = surface_triangle((float) u1, (float) v1, (float) u2, (float) v2, (float) um, (float) vm );
		/*printf("k %d surf_ref %f surface_courante %f u %lf %lf %lf %lf %lf %lf ",k,surf_ref,surface_courante,u1, v1, u2, v2, um, vm);*/
   		surface_courante += surface_triangle((float) um, (float) vm, (float) u2, (float) v2, (float) u3, (float) v3 );
		/*printf(" %f ",surface_courante);*/
    		surface_courante += surface_triangle((float) u1, (float) v1, (float) um, (float) vm, (float) u3, (float) v3 );
		/*printf(" %f \n",surface_courante);*/
		if(surf_ref == 0.0)
			{
			printf("surface ref %d = %f \n",k,surf_ref);
			surf_ref = 0.1;
			/*exit(0);*/
			}
    		ratio = surface_courante / surf_ref;
    		if (tri_min == 0)	
    			{
    			surface_min = ratio;
    			tri_min = k;
			/*printf("noe = %d typ = %d k = %d surface_min = %lf   \n",noe,typ,k,surface_min);*/
    			}
    		if (surface_min > ratio)
    			{
    			surface_min = ratio;
    			tri_min = k;
			/*printf("noe = %d typ = %d k = %d surface_min = %lf   \n",noe,typ,k,surface_min);*/
    			}
    		/*if ((noe == 504) && (typ == 4))
    			{
			printf("tri_min %d\n",tri_min);
    			}*/
  		}
		return(tri_min);
	}
	
int appartient_triangle2_old(int noe,int typ)
	{
	int k;
	double u1,u2,u3,v1,v2,v3,um,vm,p1,p2,p3,orient;
	double q1,q2,q3;
	
	um = (double) noeud[noe].U;
	vm = (double) noeud[noe].V;
	for (k=1;k<=struct_old.nombreSurfaces;k++)
		{
	  	if (surface_old[k].type == typ)	
	  		{
	  		/*
	  		pour qu un sommet appartienne a un triangle de "old".mdg, 
	  		il est necessaire que les types des triangles correspondent
	  		*/
	  		
	    		u1 = (double) surface_old[k].U[1];
	    		u2 = (double) surface_old[k].U[2];
	    		u3 = (double) surface_old[k].U[3];
	    		v1 = (double) surface_old[k].V[1];
	    		v2 = (double) surface_old[k].V[2];
	    		v3 = (double) surface_old[k].V[3];
	  
	    		/* 
	    		pour que M soit dans le triangle 123 , 
	    		il est necessaire et suffisant que les produits vectoriels 12-1M, 23-2M et 31-3M 
	    		(calcules en nombre de mailles U*V) soient du signe defini par 
	    		l orientation des triangles dans "old".mdg
	    		*/
	    		p1 = (double) (u2-u1) * (vm-v1) - (v2-v1) * (um-u1);
	    		p2 = (double) (u3-u2) * (vm-v2) - (v3-v2) * (um-u2);
	    		p3 = (double) (u1-u3) * (vm-v3) - (v1-v3) * (um-u3);
	    		orient = (double) (u2-u1) * (v3-v1) - (v2-v1) * (u3-u1); 
	    		q1 = p1*orient/fabs(orient);
	    		q2 = p2*orient/fabs(orient);
	    		q3 = p3*orient/fabs(orient);
	    
	    		/* si bien que ... */
	    		/*if ( ( p1*orient/fabs(orient) >= -0.3) && 
	         	     ( p2*orient/fabs(orient) >= -0.3) && 
	         	     ( p3*orient/fabs(orient) >= -0.3) ) return(k);*/
	    		if ( ( q1 >= -0.3) && 
	         	     ( q2 >= -0.3) && 
	         	     ( q3 >= -0.3) ) return(k);
	  		}
		}
		printf("* appartient_triangle2 *\n");
		printf("le noeud %d  n appartient a aucun triangle du maillage de %s \n",total2global[noe],oldfic);
		printf("Ce noeud est probablement sur le bord d'un panneau, s'il tel est le cas MODIFIER les valeurs proches de 0 dans chargement_mdgsta.c\n");
		printf("Ce noeud appartient au panneau %d \n",typ);
		exit(0);
	}
	
int appartient_triangle3(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3)
	{
	double p1,p2,p3,orient,q1,q2,q3;
	
	/* 
	pour que le point M : u,v soit dans le triangle 1,2,3 : u1,v1, u2,v2, u3,v3
	il est necessaire et suffisant que les produits vectoriels 12-1M, 23-2M et 31-3M 
	(calcules en nombre de mailles U*V) soient du signe defini par 
	l orientation des triangles dans "old".mdg
	*/
	
	p1 = (double) (u2-u1) * (vm-v1) - (v2-v1) * (um-u1);
	p2 = (double) (u3-u2) * (vm-v2) - (v3-v2) * (um-u2);
	p3 = (double) (u1-u3) * (vm-v3) - (v1-v3) * (um-u3);
	orient = (double) (u2-u1) * (v3-v1) - (v2-v1) * (u3-u1); 
	q1 = p1*orient/fabs(orient);
	q2 = p2*orient/fabs(orient);
	q3 = p3*orient/fabs(orient);
	
	/* si bien que ... */
	
	if(( q1 >= -0.0) && ( q2 >= -0.0) && ( q3 >= -0.0))
		{
		return(1);
		}
	else
		{
		return(0);
		}
	}
	
int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3)
	{
	float  S, S_ref ;
	int inside;
	float surface_triangle(float X1, float Y1, float X2, float Y2, float X3, float Y3 );

	/*
	printf(" ");
	printf("um   : %8.2lf ,vm  :  %8.2lf ",um,vm);
	RECHERCHE SI LE NOEUD M DE COORDONNEES FILAIRE um ET vm EST A L INTERIEUR DU CONTOUR  DU triangle 1 2 3 
	de coordonnees u1,v1, u2,v2, u3,v3
	SI A L INTERIEUR DU CONTOUR RETURN = 1
	SI A L EXTERIEUR DU CONTOUR RETURN = 0
	*/

	/*S_REF = SURFACE DU TRIANGLE u1,v1, u2,v2, u3,v3*/
	S_ref = surface_triangle( (float) u1, (float) v1, (float) u2, (float) v2, (float) u3, (float) v3);
	/*S = somme des 3 SURFACEs des TRIANGLEs 12M 13M 23M*/
	S = 0.0;
	S    += surface_triangle( (float) u1, (float) v1, (float) u2, (float) v2, (float) um, (float) vm);
	S    += surface_triangle((float)  u2, (float) v2, (float) u3, (float) v3, (float) um, (float) vm);
	S    += surface_triangle( (float) u3, (float) v3, (float) u1, (float) v1, (float) um, (float) vm);
	/*printf("S_ref   : %8.2lf , S :  %8.2lf \n",S_ref,S);*/
	if ((S / S_ref > 0.999) && (S / S_ref < 1.001))
		{
		/*LE NOEUD M EST A L INTERIEUR DU triangle*/
		inside = 1;
		}
	else
		{
		/*LE NOEUD M EST A L exterieur DU triangle*/
		inside = 0;
		}
	return(inside);
	}
	
int segment_secant(double a1, double b1, double a2, double b2, double x1, double y1, double x2, double y2)
	{
	float  S, S_ref ;
	int secant;
	float surface_triangle(float X1, float Y1, float X2, float Y2, float X3, float Y3 );

	/*
	RECHERCHE SI LE segment a1,b1 a a2,b2 coupe le segment x1,y1 a x2,y2
	SI les segments sont secants RETURN = 1
	SI non RETURN = 0
	*/

	/*S_REF = somme des SURFACEs du TRIANGLE a1,b1, x1,y1, x2,y2 et du triangle a2,b2, x1,y1, x2,y2*/
	/*S     = somme des SURFACEs du TRIANGLE x1,y1, a1,b1, a2,b2 et du triangle x2,y2, a1,b1, a2,b2*/
	
	S_ref 	= 0.0;
	S_ref += surface_triangle( (float) a1, (float) b1, (float) x1, (float) y1, (float) x2, (float) y2);
	S_ref += surface_triangle( (float) a2, (float) b2, (float) x1, (float) y1, (float) x2, (float) y2);
	S 	= 0.0;
	S    += surface_triangle( (float) x1, (float) y1, (float) a1, (float) b1, (float) a2, (float) b2);
	S    += surface_triangle( (float) x2, (float) y2, (float) a1, (float) b1, (float) a2, (float) b2);
	
	/*printf("S_ref   : %8.5f , S :  %8.5f \n",S_ref,S);*/
	
	if (S_ref != 0.0)
		{
		if ((S / S_ref > 0.999) && (S / S_ref < 1.001))
			{
			/*les segments sont secants*/
			secant = 1;
			}
		else
			{
			/*les segments ne sont pas secants*/
			secant = 0;
			}
		}
	else
		{
		/*les 2 segments sont alignes il faudrait verifier s ils se chevauchent*/
		secant = 0;
		}
	/*printf("secant   : %d d \n",secant);*/
	return(secant);
	}
	
void intersection_segment(double a1, double b1, double a2, double b2, double x1, double y1, double x2, double y2, double *x,double *y)
  	{
  	/*calcule le point d intersection x y de 2 segments a1,b1 a a2,b2 et de x1,y1 a x2,y2*/
  	
  	int zh,zi,zj;
  	
	*x = a1;
	*y = b1;
	
	if (b2 != b1)
		{
		if ((a2-a1)*(y2-y1) != (b2-b1)*(x2-x1))
			{
			*y = (b1*(a2-a1)/(b2-b1)*(y2-y1) - y1*(x2-x1) - (a1-x1)*(y2-y1)) / ((a2-a1)/(b2-b1)*(y2-y1) - (x2-x1));
			*x = a1 + (a2-a1)/(b2-b1) * (*y-b1);
			}
		else
			{
			/*pas sur du tout : A VERIFIER*/
			*x = a1;
			*y = b1;
			}
		}
	else
		{
		*y = b1;
		if (y2 != y1)
			{
			*x = x1 +(x2-x1)/(y2-y1)*(*y-y1);
			}
		else
			{
			/*pas sur du tout : A VERIFIER*/
			*x = a1;
			}
		}
	
  	}
  	

int intersection_segment2(double a1, double b1, double a2, double b2, double x1, double y1, double x2, double y2, double *alpha,double *beta)
  	{
  	/*calcule l intersection M de 2 segments A (a1,b1) a B (a2,b2) et de  C (x1,y1) a D (x2,y2)
  	et renvoie un code selon l intersection
  	code = 1  si les 2 segments ne sont pas parallèles
  	code = 2  si les 2 segments sont parallèles
  	si les 2  segments ne sont pas parallèles, AM = alpha AB et CM = beta CD
  	si les 2 segments sont parallèles AC = alpha AB + beta N. Avec N = AB ^ k. k étant le vecteur (0 0 1)
  	*/
  	int elem,zh,zi,zj,code;
  	code = 0;
  	
	if ((a2-a1)*(y2-y1) != (b2-b1)*(x2-x1))
		{
		/*segments non parallèles*/
  		code = 1;
		*alpha = ((y2-y1)*(x1-a1)-(x2-x1)*(y1-b1)) / ((y2-y1)*(a2-a1)-(x2-x1)*(b2-b1));
		*beta  = ((b2-b1)*(x1-a1)-(a2-a1)*(y1-b1)) / ((y2-y1)*(a2-a1)-(x2-x1)*(b2-b1));
		}
	else
		{
		/*segments parallèles*/
  		code = 2;
		*alpha = ((a2-a1)*(x1-a1)+(b2-b1)*(y1-b1)) / ((a2-a1)*(a2-a1)+(b2-b1)*(b2-b1));
		*beta  = ((b2-b1)*(x1-a1)-(a2-a1)*(y1-b1)) / ((a2-a1)*(a2-a1)+(b2-b1)*(b2-b1));
		}
		
	return code;
  	}
  	

void distance_segment_point(double a1, double b1, double a2, double b2, double x1, double y1, double *alpha,double *beta)
  	{
  	/*calcule la distance entre un segment A (a1,b1) a B (a2,b2) et le point C (x1,y1)*/
  	double distance,numerateur,denominateur,norm_N;
  	numerateur = ((b2-b1)*(x1-a1)-(a2-a1)*(y1-b1));
  	denominateur = ((a2-a1)*(a2-a1)+(b2-b1)*(b2-b1));
	distance  = ((b2-b1)*(x1-a1)-(a2-a1)*(y1-b1)) / ((a2-a1)*(a2-a1)+(b2-b1)*(b2-b1));
	norm_N = sqrt((b2-b1)*(b2-b1) + (a1-a2)*(a1-a2));
	*alpha = ((a2-a1)*(x1-a1)+(b2-b1)*(y1-b1)) / ((a2-a1)*(a2-a1)+(b2-b1)*(b2-b1));
	*beta  = ((b2-b1)*(x1-a1)-(a2-a1)*(y1-b1)) / ((a2-a1)*(a2-a1)+(b2-b1)*(b2-b1)) * norm_N;
	if ((x1 == 220.0) && (y1 == 20.0))
		{
		printf("a1 %lf b1 %lf a2 %lf b2 %lf x1 %lf y1 %lf\n",a1, b1, a2, b2, x1, y1);
		printf("distance %lf numerateur %lf denominateur %lf norm_N %lf\n",distance,numerateur,denominateur,norm_N);
		//exit(0);
 		}
 	}
  	

int appartient_tri_hexa2(int noe,int typ)
	{
	int k;
	double u1,u2,u3,v1,v2,v3,um,vm,p1,p2,p3,orient;
	double q1,q2,q3;
	
	um = (double) noeud[noe].U;
	vm = (double) noeud[noe].V;
	for (k=1;k<=struct_old.nombreSurfHexa;k++)
		{
	  	if (surf_hexa_old[k].type == typ)	
	  		{
	  		/*
	  		pour qu un sommet appartienne a un surf_hexa de "old".mdg, 
	  		il est necessaire que les types des triangles correspondent
	  		*/
	  		/*if(total2global[noe] == 4)
	  			{
				printf("typ = %4d ",typ);
				printf("k = %4d \n",k);
	  			}*/
	  		
	    		u1 = (double) surf_hexa_old[k].U[1];
	    		u2 = (double) surf_hexa_old[k].U[2];
	    		u3 = (double) surf_hexa_old[k].U[3];
	    		v1 = (double) surf_hexa_old[k].V[1];
	    		v2 = (double) surf_hexa_old[k].V[2];
	    		v3 = (double) surf_hexa_old[k].V[3];
	  
	    		/* 
	    		pour que M soit dans le surf_hexa 123 , 
	    		il est necessaire et suffisant que les produits vectoriels 12-1M, 23-2M et 31-3M 
	    		(calcules en nombre de mailles U*V) soient du signe defini par 
	    		l orientation des triangles dans "old".mdg
	    		*/
	    		p1 = (double) (u2-u1) * (vm-v1) - (v2-v1) * (um-u1);
	    		p2 = (double) (u3-u2) * (vm-v2) - (v3-v2) * (um-u2);
	    		p3 = (double) (u1-u3) * (vm-v3) - (v1-v3) * (um-u3);
	    		orient = (double) (u2-u1) * (v3-v1) - (v2-v1) * (u3-u1); 
	    		q1 = p1*orient/fabs(orient);
	    		q2 = p2*orient/fabs(orient);
	    		q3 = p3*orient/fabs(orient);
	    
	    		/* si bien que ... */
	    		/*if ( ( p1*orient/fabs(orient) >= -0.3) && 
	         	     ( p2*orient/fabs(orient) >= -0.3) && 
	         	     ( p3*orient/fabs(orient) >= -0.3) ) return(k);*/
	    		if ( ( q1 >= -0.2) && 
	         	     ( q2 >= -0.2) && 
	         	     ( q3 >= -0.2) ) return(k);
	         	
	  		/*
	  		if(total2global[noe] == 106)
	  			{
				printf("typ = %4d ",typ);
				printf("k = %4d ",k);
				printf("q1,q2,q3 =  %8.2lf  %8.2lf  %8.2lf   \n",q1,q2,q3);
	  			}
	  		*/
	  		}
		}
		printf("* appartient_surf_hexa2 *\n");
		printf("le noeud %d  n appartient a aucun surf_hexa du maillage de %s \n",total2global[noe],oldfic);
		printf("Ce noeud est probablement sur le bord d'un panneau, s'il tel est le cas MODIFIER les valeurs proches de 0 dans chargement_mdgsta.c\n");
		printf("Ce noeud appartient au panneau %d \n",typ);
		exit(0);
	}
	
void ecriture_sta(FILE *f3)
	
	{
	/* ecriture dans le fichier **.sta des coordonnees des noeuds de **.mdg, proche d une position d equilibre 
	   prealablement calculee a l aide de *.mdg */
	   
	int    i;
	float X,Y,Z,L,elongation;
	
	/*ecriture des coordonnees a l equilibre statique dans le meme ordre que dans le fichier de donnees*/
	for (i = 1 ; i<= Structure.nb_global ; i++) 
	{
		fprintf(f3,"  %5d",i);
    		fprintf(f3,"  %17.9lf",noeud_global[i].x);
    		fprintf(f3,"  %17.9lf",noeud_global[i].y);
    		fprintf(f3,"  %17.9lf",noeud_global[i].z);
    		fprintf(f3,"\n");
	}

	/*ecriture des elongations des nouvelles barres*/
	for (i = 1 ; i<= Structure.nb_barre ; i++) 
	{	X = noeud_global[total2global[barre[i].noeud[2]]].x -  noeud_global[total2global[barre[i].noeud[1]]].x;
		Y = noeud_global[total2global[barre[i].noeud[2]]].y -  noeud_global[total2global[barre[i].noeud[1]]].y;
    		Z = noeud_global[total2global[barre[i].noeud[2]]].z -  noeud_global[total2global[barre[i].noeud[1]]].z;
    		barre[i].longueur_tendue = sqrt(X*X + Y*Y + Z*Z);
    		elongation = (barre[i].longueur_tendue - barre[i].longueur_repos) / barre[i].longueur_repos;
    		fprintf(f3," %17.9f \n",elongation);
	}
    	fprintf(f3,"\n");
	
  	/*ecriture de l elongation des nouvelles coulisses */
  	for (i = 1 ; i<= Structure.nombreCoulisses ; i++)
    		{
    		elongation = (coulisse[i].lgtendue - coulisse[i].lgrepos) / coulisse[i].lgrepos;
    		fprintf(f3," %12.7f \n",elongation);
    		}
  	fprintf(f3,"\n");

	/*ecriture des valeurs nx,ny,nz,mx,my,mz (ces valeurs sont arbitraires!!!)*/
	for (i = 1 ; i<= Structure.nombreSurfaces ; i++) 
	{
    		fprintf(f3,"  %17.9lf",panneau[surface[i].type].longueur_repos);
		fprintf(f3,"  0.000");
		fprintf(f3,"  0.000");
    		fprintf(f3,"  %17.9lf",panneau[surface[i].type].longueur_repos);
		fprintf(f3,"  0.000");
		fprintf(f3,"  0.000");
		fprintf(f3,"\n");
    	}
	fprintf(f3,"\n");

	/*ecriture des valeurs nx,ny,nz,mx,my,mz,lx,ly,lz (ces valeurs sont arbitraires!!!)*/
	for (i = 1 ; i<= Structure.nombreSurfHexa ; i++) 
	{
		fprintf(f3,"  0.000");
		fprintf(f3,"  0.000");
		fprintf(f3,"  0.000");
		fprintf(f3,"  0.000");
		fprintf(f3,"  0.000");
		fprintf(f3,"  0.000");
		fprintf(f3,"\n");
    	}
	fprintf(f3,"\n");

	/*ecriture de la position du front*/
	fprintf(f3," %12.3lf\n",Prise.front);
	}

void nothing()
	{
	}
