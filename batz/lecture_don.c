#define PRINCIPAL 0
#include "batz.h"

void modif_materiau_elem(int num_elem_choisi, double raideur_traction_choisie, double raideur_compression_choisie, double masse_volumique_choisie, double diam_hydro_choisi, double coeff_trainee_normal_choisi, double coeff_trainee_tangent_choisi)
{
	TypeElement[num_elem_choisi].raideur_traction=raideur_traction_choisie;
	TypeElement[num_elem_choisi].raideur_compression=raideur_compression_choisie;
	TypeElement[num_elem_choisi].rhoelement=masse_volumique_choisie;
	TypeElement[num_elem_choisi].diametrehydro=diam_hydro_choisi;
	TypeElement[num_elem_choisi].cdnormal=coeff_trainee_normal_choisi;
	TypeElement[num_elem_choisi].ftangent=coeff_trainee_tangent_choisi;
}

void lecture_don(char *nomfichier)
	{
	/*chargement du fichier *.don, le nom generique est stocke dans fname1*/
	char chaine[] = "                                               ";
	char chainebis[] = "                                               ";
	char comment[] = "                                               ";
	char c,t1[256],tonom[100],temp_char,temp1_char,temp2_char;
	int i,pa,no,nog,temp_int,temp1_int,temp2_int,temp3_int,type_maillage,NOMBRE_ORDRE_OBJET,zi,zj,tmp_i1,itmp;
	double PE3,WB,tmp_d1,tmp_d2,tmp_d3,tmp_d4,tmp_d5,time,dist;
	float temp_double;

	double xxp11,xxp12,xxp21,xxp22,xxp31,xxp32,xxp41,xxp42,xxp51,xxp52,xxp61,xxp62,xxp71,xxp72,xxp81,xxp82;
	double yyp11,yyp12,yyp21,yyp22,yyp31,yyp32,yyp41,yyp42,yyp51,yyp52,yyp61,yyp62,yyp71,yyp72,yyp81,yyp82;

	int add_number_cage =0;
	int temp_num;
	double add_cage_diam;
	double add_cage_xxo;
	double add_cage_yyo;
	int add_cage_nsegment;
	double add_cage_dist_ann;
	double add_cage_haut_ann;
	double add_hauteur_filet_elev;
	double add_taille_maille_elev;
	double add_hauteur_filet_pred;
	double add_taille_maille_pred;
	double diametre_pehd;
	double epaisseur_pehd;
	double rho_pehd;

	double add_filet_pred_diam;
	double add_diam_lest;
	double add_filet_pred_xxo;
	double add_filet_pred_yyo;
	int add_filet_pred_nsegment,E_numero;

	double txmin,txmax,tymin,tymax,tzmin,tzmax,S_Nb,S_Diam,S_Float,L_Float;


	int pan_inter_fond =1;
	int elem_inter =1;
	int nb_ele_depart=1;
	int nb_tot_elem=0;
	int nb_elem_cage=0;

	int immersion =0;

	int ele_inter_pred =0;
	double ff,ffprim,hlambda,aa,kk,dh;


/********************************** MODIF ARNAUD 07/10/09 **************************/

	double* coord_noeud_x = NULL;
	double* coord_noeud_y = NULL;
	double* coord_noeud_z = NULL;
	double* lg_lg = NULL;
	int* type_type_noeud = NULL;

	int deb;
	int fin;

	float z_pate;
	float z_masse1;
	float z_masse2;
	float pourc_lg_pate;
	float pourc_lg_masse1;
	float pourc_lg_masse2;
	int type_masse1;
	int type_masse2;
	float xxx;
	float yyy;
	float zzz;
	int pan_choisi1;
	int pan_choisi2;
	

	int num_elem_choisi;
	double raideur_traction_choisie;
	double raideur_compression_choisie;
	double masse_volumique_choisie;
	double diam_hydro_choisi;
	double coeff_trainee_normal_choisi;
	double coeff_trainee_tangent_choisi;

/************************************MODIF ARNAUD *******************/
	int node_type;
	double actual_foil_surface, model_foil_surface,model_mass_in_air,model_mass_in_water,foil_cd,foil_cl,foil_cz;
	double ref_length_model,ref_volume_model,ratio_mass_in_air_volume,ref_length_actual,ref_volume_actual;
	double actual_mass_in_air,model_density,actual_volume,Fd,Fl;
	RHO = 1025.0;                   	/*default value of the water density*/


	FILE *fic,*f3;
  	strcpy(tonom,nomfichier);

  	strcat(tonom,".don");

	fic = fopen(tonom,"r");
	/*printf("fichier ouvert \n");*/
  	if (fic == NULL) 
  		{
    		printf(" \n");
    		printf("%s %s %s \n","fichier ",tonom," n existe pas ?");
    		exit(0);
  		} 
  
	Structure.nb_winch = 0;
	Structure.version = 1;
	lecture_chaine(fic,chaine);		

	i = strlen(chaine);
	printf("chaine = %s  ",chaine);
	printf("longueur chaine = %d\n",i);/**/
	if (strcmp(chaine,"version_2") == 0)
		{
		Structure.version = 2;
		}

	if (strcmp(chaine,"version_3") == 0)
		{
		Structure.version = 3;
		}

	/*orientation du dessin****************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	fscanf(fic,"%d\n",&temp_int);
	if ( (temp_int != 1) && (temp_int != 2) && (temp_int != 3))
		{
		printf(" temp_int %4d doit etre = a 1 2 ou 3  \n",temp_int );
		exit(0);
		}
	
	/*panneaux*****************************************************/
	
    	do  c=fgetc(fic); while (c !=':'); 
    	fscanf(fic,"%d\n",&NbTypesurf );
    	
	for (pa=1;pa<=NbTypesurf;pa++)
		{
	    	do  c=fgetc(fic); while (c !=':'); 
	    	do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%d\n",&temp_int);
		fgets(t1,256,fic);
		/*printf("t1  : %s\n",t1);*/ 
		for (no=1;no<=temp_int;no++)
			{
			fscanf(fic,"%d",&temp2_int);
			fscanf(fic,"%f %f %f",&temp_double,&temp_double,&temp_double);
			fscanf(fic,"%f %f",&temp_double,&temp_double);
			fscanf(fic,"%d",&temp2_int);
			fscanf(fic,"%d",&temp2_int);
			}
		
		//fgets(t1,256,fic); 
		//fgets(t1,256,fic); 
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&panneau[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&panneau[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&panneau[pa].raideur_ouverture);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&panneau[pa].longueur_repos);
   		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&panneau[pa].rho);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&panneau[pa].diam_hydro);
     		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&panneau[pa].largeurnoeud);
   		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&panneau[pa].cdnormal);
   		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&panneau[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&temp_double);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%d\n",&temp_int);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%d\n",&temp_int);
    		
		panneau[pa].tarp = 0;
		}

	/*panneaux hexagonaux*******************************************/
	
    	do  c=fgetc(fic); while (c !=':'); 
    	fscanf(fic,"%d\n",&NbTypesurfHexa );
    	
	for (pa=1;pa<=NbTypesurfHexa;pa++)
		{
	    	do  c=fgetc(fic); while (c !=':'); 
	    	do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%d\n",&temp_int);
		fgets(t1,256,fic);
		/*printf("t1  : %s\n",t1);*/ 
		for (no=1;no<=temp_int;no++)
			{
			fscanf(fic,"%d",&temp2_int);
			fscanf(fic,"%f %f %f",&temp_double,&temp_double,&temp_double);
			fscanf(fic,"%f %f",&temp_double,&temp_double);
			fscanf(fic,"%d",&temp2_int);
			fscanf(fic,"%d",&temp2_int);
			}
		
		fgets(t1,256,fic); 
		fgets(t1,256,fic); 
    		do  c=fgetc(fic); while (c !=':'); 
    		fscanf(fic,"%lf%lf%lf\n",&TypeSurfHexa[pa].raideur_traction_l,&TypeSurfHexa[pa].raideur_traction_m,&TypeSurfHexa[pa].raideur_traction_n);
    		do  c=fgetc(fic); while (c !=':'); 
     		fscanf(fic,"%lf%lf%lf\n",&TypeSurfHexa[pa].raideur_compression_l,&TypeSurfHexa[pa].raideur_compression_m,&TypeSurfHexa[pa].raideur_compression_n);
    		do  c=fgetc(fic); while (c !=':'); 
    		fscanf(fic,"%lf%lf%lf\n",&TypeSurfHexa[pa].lo_repos,&TypeSurfHexa[pa].mo_repos,&TypeSurfHexa[pa].no_repos);
    		do  c=fgetc(fic); while (c !=':'); 
     		fscanf(fic,"%lf%lf%lf\n",&TypeSurfHexa[pa].diam_hydro_l,&TypeSurfHexa[pa].diam_hydro_m,&TypeSurfHexa[pa].diam_hydro_n);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%lf\n",&TypeSurfHexa[pa].rhosurface);
   		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%lf\n",&TypeSurfHexa[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%lf\n",&TypeSurfHexa[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%f\n",&temp_double);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%d\n",&temp_int);
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%d\n",&type_maillage);
    		
		TypeSurfHexa[pa].type = pa;
		if (type_maillage == 3)
			{
			/*le panneau est constitue d elements*/
    			TypeElement[1].raideur_traction 	= TypeSurfHexa[pa].raideur_traction_l;
    			TypeElement[1].raideur_compression 	= TypeSurfHexa[pa].raideur_compression_l;
    			TypeElement[1].lgrepos 			= TypeSurfHexa[pa].lo_repos;
    			TypeElement[1].rhoelement 		= TypeSurfHexa[pa].rhosurface;
    			TypeElement[1].diametrehydro 		= TypeSurfHexa[pa].diam_hydro_l;
    			TypeElement[1].cdnormal 		= TypeSurfHexa[pa].cdnormal;
    			TypeElement[1].ftangent 		= TypeSurfHexa[pa].ftangent;
    			
    			TypeElement[2].raideur_traction 	= TypeSurfHexa[pa].raideur_traction_m;
    			TypeElement[2].raideur_compression 	= TypeSurfHexa[pa].raideur_compression_m;
    			TypeElement[2].lgrepos 			= TypeSurfHexa[pa].lo_repos;
    			TypeElement[2].rhoelement 		= TypeSurfHexa[pa].rhosurface;
    			TypeElement[2].diametrehydro 		= TypeSurfHexa[pa].diam_hydro_m;
    			TypeElement[2].cdnormal 		= TypeSurfHexa[pa].cdnormal;
    			TypeElement[2].ftangent 		= TypeSurfHexa[pa].ftangent;
    			
    			TypeElement[3].raideur_traction 	= TypeSurfHexa[pa].raideur_traction_n;
    			TypeElement[3].raideur_compression 	= TypeSurfHexa[pa].raideur_compression_n;
    			TypeElement[3].lgrepos			= TypeSurfHexa[pa].lo_repos;
    			TypeElement[3].rhoelement 		= TypeSurfHexa[pa].rhosurface;
    			TypeElement[3].diametrehydro 		= TypeSurfHexa[pa].diam_hydro_n;
    			TypeElement[3].cdnormal 		= TypeSurfHexa[pa].cdnormal;
    			TypeElement[3].ftangent 		= TypeSurfHexa[pa].ftangent;
			}
		}
	/*******************************************************************************************************************************/
	/*******************************************************************************************************************************/
	
	/*elements*****************************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	fscanf(fic,"%d\n",&NbTypeelem);
    	
	for (pa=1;pa<=NbTypeelem;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); 
    		do  c=fgetc(fic); while (c !=':'); 
		for (no=1;no<=2;no++)
			{
			if (no ==1)
				{
				fscanf(fic,"%d %lf %lf %lf %d",&temp_num,&TypeElement[pa].x1,
				    		&TypeElement[pa].y1,
				     		&TypeElement[pa].z1,&temp_num);
						/*printf(" %lf %lf %lf \n",TypeElement[pa].x1,TypeElement[pa].y1,TypeElement[pa].z1);/**/

				}
			else if (no ==2)
				{
				fscanf(fic,"%d %lf %lf %lf %d",&temp_num,&TypeElement[pa].x2,
				    			&TypeElement[pa].y2,
				     			&TypeElement[pa].z2,&temp_num);
							/*printf(" %lf %lf %lf \n",TypeElement[pa].x2,TypeElement[pa].y2,TypeElement[pa].z2);*/
				}

			}
 		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&TypeElement[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&TypeElement[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&TypeElement[pa].lgrepos);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&TypeElement[pa].rhoelement);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&TypeElement[pa].diametrehydro);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&TypeElement[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&TypeElement[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&temp_int);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&temp_int);
    		TypeElement[pa].type = pa;
		}


/*******************************************************************************************************************************/
/*******************************************************************************************************************************/

	/*coulisses*****************************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	fscanf(fic,"%d\n",&pa);
	if (pa != NOMBRE_COULISSES)
		{
		printf(" nb de coulisses != entre fichiers don et mdh %d et %d  \n ",pa,NOMBRE_COULISSES );
		exit(0);
		}
    	
	for (pa=1;pa<=NOMBRE_COULISSES;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); 
    		do  c=fgetc(fic); while (c !=':'); 
		for (no=1;no<=2;no++)
			{
			fscanf(fic,"%d",&temp_int);
			fscanf(fic,"%f %f%f",&temp_double,&temp_double,&temp_double);
			fscanf(fic,"%d",&temp_int);
			}
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Coulisse[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Coulisse[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Coulisse[pa].lgrepos);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Coulisse[pa].rhocoulisse);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Coulisse[pa].diametrehydro);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Coulisse[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Coulisse[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&temp_int);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&temp_int);
		/*
		printf("coulisse  %5d \n",pa);
		printf("raideur traction  %lf \n",Coulisse[pa].raideur_traction);
		printf("raideur traction  %lf \n",Coulisse[pa].raideur_compression);
		printf("raideur traction  %lf \n",Coulisse[pa].lgrepos);
		printf("raideur traction  %lf \n",Coulisse[pa].rhocoulisse);
		printf("raideur traction  %lf \n",Coulisse[pa].diametrehydro);
		printf("raideur traction  %lf \n",Coulisse[pa].cdnormal);
		printf("raideur traction  %lf \n",Coulisse[pa].ftangent);
		*/
		}
	if (Structure.version == 2)
	{
	/*winchs*****************************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	fscanf(fic,"%d\n",&Structure.nb_winch);
	printf("Structure.nb_winch  = %8d\n", Structure.nb_winch); 
	for (pa=1;pa<=Structure.nb_winch;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); 
    		do  c=fgetc(fic); while (c !=':'); 
		for (no=1;no<=2;no++)
			{
			fscanf(fic,"%d",&temp_int);
			fscanf(fic,"%f %f %f",&temp_double,&temp_double,&temp_double);
			fscanf(fic,"%d",&temp_int);
			}
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Winch[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Winch[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Winch[pa].longueur_repos);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Winch[pa].rho);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Winch[pa].diam_hydro);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Winch[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Winch[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%lf\n",&Winch[pa].adjust_force);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Winch[pa].nb_barre);
    		do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Winch[pa].type_noeud);
		printf("length of winch %d = %lf m \n",pa,Winch[pa].longueur_repos);
		/**********************************************/
  		Winch[pa].exit = (int    *) malloc((2 + Winch[pa].nb_barre) * sizeof(int   ));
		if (Winch[pa].exit    == NULL)
			{
			printf(" Winch[pa].exit 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		Winch[pa].longueur = (double *) malloc((2 + Winch[pa].nb_barre) * sizeof(double));
		if (Winch[pa].longueur    == NULL)
			{
			printf(" Winch[pa].longueur 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
    		}
    	}	
    	
    	/*liaisons*****************************************************/
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&temp_int); 
	printf("nb_liaison  = %8d\n", temp_int);
	for (pa=1;pa<=temp_int;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%d",&temp2_int);
		/*printf(".nb_liaison = %4d ", lien[pa].nb_liaison);*/
		for (i=1;i<=temp2_int;i++)
			{
			do  c=fgetc(fic); while (c ==' '); temp_char = fgetc(fic);
			/*printf("c %c ",c);*/
    			do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%d",&temp3_int);
    			do  c=fgetc(fic); while (c !=':'); fscanf(fic,"%d",&temp3_int);
			/*printf("st %c %1d ",lien[pa].type[i],lien[pa].structure[i]);
			printf("no %1d    ",lien[pa].extremite[i] );printf("\n");*/
			}
		/*printf("\n");*/
		}
		
		
		
	/*ordre de maillage***************************************************/	
	NOMBRE_ORDRE_OBJET = NbTypesurf + NbTypeelem + NOMBRE_WINCHS +NOMBRE_COULISSES + NbTypesurfHexa;
	do  
		{
		c=fgetc(fic); 
		printf("%c",c);
		}
	while (c !=':'); 
	printf("\n");
		
		
	for (i=1;i<=NOMBRE_ORDRE_OBJET;i++)
		{ 
		do c=fgetc(fic); while ((c ==' ') || (c =='\n') || (c =='\t')); temp_char = c;
				
		if((temp_char != 'a') && (temp_char != 'p') && (temp_char != 'h') && (temp_char != 'e') && (temp_char !='c') && (temp_char !='w'))
			{
			printf("warning : object type %d is unknown\n",i);
			}
			
			
		if (c =='a')
			{
			printf("Meshing begins by elements, followed by diamond mesh panels, hexagonal mesh panels, sliders and winches\n");
			break;
			//exit(0);
			}
		else
			{
			//////////////////////////////////////////////////////////////////
	    		do  c=fgetc(fic); while (c !=':');     fscanf(fic,"%d",&temp_int);
	    		/*printf("type = %c indice = %d\n",temp_char,temp_int);*/
			if (temp_char == 'p')
				{
				if((temp_int<1) || (temp_int>NbTypesurf))
					{
					printf("warning :l'indice %d de l'objet %d est incompatible\n",temp_int,i);
					exit(0);
					}
				}
			if (temp_char == 'h')
				{
				if((temp_int<1) || (temp_int>NbTypesurfHexa))
					{
					printf("warning :l'indice %d de l'objet %d est incompatible\n",temp_int,i);
					exit(0);
					}
				}
			if (temp_char == 'e')
				{
				if((temp_int<1) || (temp_int>NbTypeelem))
					{
					printf("warning :l'indice %d de l'objet %d est incompatible\n",temp_int,i);
					exit(0);
					}
				}
			if (temp_char == 'c')
				{
				if((temp_int<1) || (temp_int>NOMBRE_COULISSES))
					{
					printf("warning :l'indice %d de l'objet %d est incompatible\n",temp_int,i);
					exit(0);
					}
				}
			if (temp_char == 'w')
				{
				if((temp_int<1) || (temp_int>NOMBRE_WINCHS))
					{
					printf("warning :l'indice %d de l'objet %d est incompatible\n",temp_int,i);
					exit(0);
					}
				}
			/////////////////////////////////////////////////////
			}
 	        }     
	
		
		
		
		
		
		
		
		
	/*Types de Noeuds*****************************************************/
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&NbTypeNoeud); 
	printf("NbTypeNoeud = %4d\n",NbTypeNoeud );
	for (pa=1;pa<=NbTypeNoeud;pa++)
		{
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].mx,&TypeNoeud[pa].my,&TypeNoeud[pa].mz);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].majx,&TypeNoeud[pa].majy,&TypeNoeud[pa].majz);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].sx,&TypeNoeud[pa].sy,&TypeNoeud[pa].sz);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].cdx,&TypeNoeud[pa].cdy,&TypeNoeud[pa].cdz);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].fx,&TypeNoeud[pa].fy,&TypeNoeud[pa].fz);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%d %d%d",&TypeNoeud[pa].fixx,&TypeNoeud[pa].fixy,&TypeNoeud[pa].fixz);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].limx,&TypeNoeud[pa].limy,&TypeNoeud[pa].limz);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%d %d%d",&TypeNoeud[pa].fmx,&TypeNoeud[pa].fmy,&TypeNoeud[pa].fmz);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%d %d%d",&TypeNoeud[pa].symx,&TypeNoeud[pa].symy,&TypeNoeud[pa].symz);
		}

	/*ENVIRONNEMENT NUMERIQUE*****************************************************/
		do  c=fgetc(fic);  while (c !=':');	
		fscanf(fic,"%lf\n",&Structure.diviseur); 
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Seuilconvergence); 
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Deplacement); 
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%10d\n",&Nbmaxiterations); 
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Pascalcul); 
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Passtockage);
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Debutstockage); 
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Finstockage); 

	/*ENVIRONNEMENT METEOROLOGIQUE ET OCEANIQUE***********************************/
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Courant.direction); 
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Courant.vitesse); 
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Houle.periode); 
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Houle.hauteur); 
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Houle.direction);
		
		/*printf("Houle.direction %8.2f\n",Houle.direction); */
		/*to ensure that Houle.direction is positive*/
		if (Houle.direction < 0.0)
			{
			do
				{
				Houle.direction = Houle.direction + 360;
				}
			while (Houle.direction < 0.0);
			}
		/*printf("Houle.direction %8.2f\n",Houle.direction); */
		
		
		
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Houle.depth);
		 
	/*DESCRIPTION DE LA PRISE*****************************************************/
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Prise.volume);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Prise.seuil);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Prise.cd);
		
	/*ENVIRONNEMENT DU FOND MARIN*************************************************/
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Bottom.coef_frottement);
		do  c=fgetc(fic); while (c !=':');	
		fscanf(fic,"%lf\n",&Bottom.raideur);




	/*sortie texte*****************************************************/
	Sortie_texte.nb_distance = 0;			/*nb de distance entre 2 points affichees*/
	Sortie_texte.nb_effort = 0;			/*nb d effort selon un axe a un point affiches*/
	Sortie_texte.nb_tension_element = 0;			/*nb de tension dans un element affichees*/
	Sortie_texte.nb_tension_coulisse = 0;		/*nb de tension dans une coulisse affichees*/
	Sortie_texte.nb_position = 0;			/*nb de position selon un axe a un point affichees*/
	Sortie_texte.nb_longueur = 0;			/*nb de longueur de barres affichees*/
	Sortie_texte.nb_longueur_cable = 0;		/*nb de longueur de cables affichees*/
	Sortie_texte.nb_energie_elong_diamond = 0;	/*nb d energies d elongation par panneaux de filets losange affichees*/
	Sortie_texte.nb_energie_fold_diamond = 0;	/*nb d energies d foldation par panneaux de filets losange affichees*/
	Sortie_texte.nb_energie_open_diamond = 0;	/*nb d energies d openation par panneaux de filets losange affichees*/
	Sortie_texte.nb_parametre = 0;			/*nb de position selon un axe a un point affichees*/
	
	/*sortie texte distance*****************************************************/
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.nb_distance); 
	/*printf("Sortie_texte.nb_distance  = %8d\n",Sortie_texte.nb_distance );*/
	Sortie_texte.noeud1_distance = 		(int *) Malloc_int(1 + Sortie_texte.nb_distance);
	Sortie_texte.noeud2_distance = 		(int *) Malloc_int(1 + Sortie_texte.nb_distance);
	Sortie_texte.decimale_distance = 	(int *) Malloc_int(1 + Sortie_texte.nb_distance);
	Sortie_texte.valeur_distance = 		(double *) Malloc_double(1 + Sortie_texte.nb_distance);
	Sortie_texte.comment_distance = 	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_distance);
	for (pa=1;pa<=Sortie_texte.nb_distance;pa++)
		{
    		do  c=fgetc(fic); while (c !=':');
    		do  c=fgetc(fic); while (c !=':');
    		
		c=fgetc(fic); 
		while ((c =='#') || (c ==' '))	c=fgetc(fic); 
		for (i=1;i<=155;i++)	Sortie_texte.comment_distance[pa].texte[i] = ' ';
		i = 0;
		while ((c !='#') && (i<155))
			{
			i++;
			Sortie_texte.comment_distance[pa].texte[i] = c;
			c=fgetc(fic);
			}
		i++;	Sortie_texte.comment_distance[pa].texte[i] = ':';
		i++;	Sortie_texte.comment_distance[pa].texte[i] = 0;
		 
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.noeud1_distance[pa]);
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.noeud2_distance[pa]);
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.decimale_distance[pa]);
		}

	/*sortie texte effort*****************************************************/
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.nb_effort); 
	/*printf("Sortie_texte.nb_effort  = %8d\n",Sortie_texte.nb_effort );*/
	Sortie_texte.noeud_effort = 		(int *) Malloc_int(1 + Sortie_texte.nb_effort);
	Sortie_texte.axe_effort = 		(int *) Malloc_int(1 + Sortie_texte.nb_effort);
	Sortie_texte.decimale_effort = 		(int *) Malloc_int(1 + Sortie_texte.nb_effort);
	Sortie_texte.valeur_effort = 		(double *) Malloc_double(1 + Sortie_texte.nb_effort);
	Sortie_texte.comment_effort = 	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_effort);
	for (pa=1;pa<=Sortie_texte.nb_effort;pa++)
		{
    		do  c=fgetc(fic); while (c !=':');
    		do  c=fgetc(fic); while (c !=':');
    		
		c=fgetc(fic); 
		while ((c =='#') || (c ==' '))	c=fgetc(fic); 
		for (i=1;i<=155;i++)	Sortie_texte.comment_effort[pa].texte[i] = ' ';
		i = 0;
		while ((c !='#') && (i<155))
			{
			i++;
			Sortie_texte.comment_effort[pa].texte[i] = c;
			c=fgetc(fic);
			}
		i++;	Sortie_texte.comment_effort[pa].texte[i] = ':';
		i++;	Sortie_texte.comment_effort[pa].texte[i] = 0;
		 
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.noeud_effort[pa]);
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.axe_effort[pa]);
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.decimale_effort[pa]);
		}

	/*sortie texte tension*****************************************************/
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.nb_tension_element); 
	/*printf("Sortie_texte.nb_tension_element  = %8d\n",Sortie_texte.nb_tension_element );*/
	Sortie_texte.element_tension = 		(int *) Malloc_int(1 + Sortie_texte.nb_tension_element);
	Sortie_texte.element_extremite = 	(int *) Malloc_int(1 + Sortie_texte.nb_tension_element);
	Sortie_texte.decimale_tension_element = 	(int *) Malloc_int(1 + Sortie_texte.nb_tension_element);
	Sortie_texte.valeur_tension = 		(double *) Malloc_double(1 + Sortie_texte.nb_tension_element);
	Sortie_texte.comment_tension_element = 		(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_tension_element);
	for (pa=1;pa<=Sortie_texte.nb_tension_element;pa++)
		{
    		do  c=fgetc(fic); while (c !=':');
    		do  c=fgetc(fic); while (c !=':');
    		
		c=fgetc(fic); 
		while ((c =='#') || (c ==' '))	c=fgetc(fic); 
		for (i=1;i<=155;i++)	Sortie_texte.comment_tension_element[pa].texte[i] = ' ';
		i = 0;
		while ((c !='#') && (i<155))
			{
			i++;
			Sortie_texte.comment_tension_element[pa].texte[i] = c;
			c=fgetc(fic);
			}
		i++;	Sortie_texte.comment_tension_element[pa].texte[i] = ':';
		i++;	Sortie_texte.comment_tension_element[pa].texte[i] = 0;
		 
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.element_tension[pa]);
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.element_extremite[pa]);
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.decimale_tension_element[pa]);
		}

	/*sortie texte tension coulisse*****************************************************/
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.nb_tension_coulisse); 
	/*printf("Sortie_texte.nb_tension_coulisse  = %8d\n",Sortie_texte.nb_tension_coulisse	);*/
	Sortie_texte.coulisse_tension = 	(int *) Malloc_int(1 + Sortie_texte.nb_tension_coulisse);
	Sortie_texte.coulisse_extremite = 	(int *) Malloc_int(1 + Sortie_texte.nb_tension_coulisse);
	Sortie_texte.decimale_tension_element = 	(int *) Malloc_int(1 + Sortie_texte.nb_tension_coulisse);
	Sortie_texte.valeur_tension_coulisse = 	(double *) Malloc_double(1 + Sortie_texte.nb_tension_coulisse);
	Sortie_texte.comment_tension_coulisse = (struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_tension_coulisse);
	for (pa=1;pa<=Sortie_texte.nb_tension_coulisse;pa++)
		{
    		do  c=fgetc(fic); while (c !=':');
    		do  c=fgetc(fic); while (c !=':');
    		
		c=fgetc(fic); 
		while ((c =='#') || (c ==' '))	c=fgetc(fic); 
		for (i=1;i<=155;i++)	Sortie_texte.comment_tension_coulisse[pa].texte[i] = ' ';
		i = 0;
		while ((c !='#') && (i<155))
			{
			i++;
			Sortie_texte.comment_tension_coulisse[pa].texte[i] = c;
			c=fgetc(fic);
			}
		i++;	Sortie_texte.comment_tension_coulisse[pa].texte[i] = ':';
		i++;	Sortie_texte.comment_tension_coulisse[pa].texte[i] = 0;
		 
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.coulisse_tension[pa]);
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.coulisse_extremite[pa]);
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&temp_int);
		}

	/*sortie texte position*****************************************************/
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.nb_position); 
	/*printf("Sortie_texte.nb_position  = %8d\n",Sortie_texte.nb_position );*/
	Sortie_texte.noeud_position = 		(int *) Malloc_int(1 + Sortie_texte.nb_position);
	Sortie_texte.axe_position = 		(int *) Malloc_int(1 + Sortie_texte.nb_position);
	Sortie_texte.decimale_position = 	(int *) Malloc_int(1 + Sortie_texte.nb_position);
	Sortie_texte.valeur_position = 		(double *) Malloc_double(1 + Sortie_texte.nb_position);
	Sortie_texte.comment_position = 	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_position);
	for (pa=1;pa<=Sortie_texte.nb_position;pa++)
		{
    		do  c=fgetc(fic); while (c !=':');
    		do  c=fgetc(fic); while (c !=':');
    		
		c=fgetc(fic); 
		while ((c =='#') || (c ==' '))	c=fgetc(fic); 
		for (i=1;i<=155;i++)	Sortie_texte.comment_position[pa].texte[i] = ' ';
		i = 0;
		while ((c !='#') && (i<155))
			{
			i++;
			Sortie_texte.comment_position[pa].texte[i] = c;
			c=fgetc(fic);
			}
		i++;	Sortie_texte.comment_position[pa].texte[i] = ':';
		i++;	Sortie_texte.comment_position[pa].texte[i] = 0;
		 
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.noeud_position[pa]);
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.axe_position[pa]);
		do  c=fgetc(fic); while (c !=':');	fscanf(fic,"%d\n",&Sortie_texte.decimale_position[pa]);
		}


	
	Sortie_texte.bottom_drag = 0;
	Sortie_texte.catch_drag = 0;
	Sortie_texte.element_drag = 0;
	Sortie_texte.surface_drag = 0;
	Sortie_texte.node_drag = 0;
	Sortie_texte.effort_structure = 0;
	Sortie_texte.diametre_prise = 0;
	Sortie_texte.epaisseur_prise = 0;
	Sortie_texte.vitesse_courant = 0;
	Sortie_texte.volume_capture = 0;
	Sortie_texte.surface_filtree = 0;
	Sortie_texte.volume_x = 0;
	Sortie_texte.volume_y = 0;
	Sortie_texte.volume_z = 0;
	Sortie_texte.volume_0 = 0;
	Sortie_texte.inner_surface = 0;
	Sortie_texte.inner_surface_triangulation = 0;
	Prise.nb_noeuds = 0;
	Prise.nb_noeuds_contour = 0;
	Prise.nb_triangles = 0;	

	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.effort_structure); 
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.diametre_prise); 
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.epaisseur_prise); 
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.volume_capture); 
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.surface_filtree); 
	do  c=fgetc(fic); while (c !=':');fscanf(fic,"%d\n",&Sortie_texte.vitesse_courant);
	for (pa=1;pa<=NbTypesurf;pa++)		
		{
		panneau[pa].flag_dessin = 2;	
		panneau[pa].netting_2_ropes_period = 0;
		}			
	for (pa=1;pa<=NbTypesurfHexa;pa++)	TypeSurfHexa[pa].flag_dessin = 1;
	for (pa=1;pa<=NbTypeelem;pa++)		TypeElement[pa].flag_dessin = 3;				
	for (pa=1;pa<=NOMBRE_COULISSES;pa++)	Coulisse[pa].flag_dessin = 1;
	for (pa=1;pa<=NOMBRE_WINCHS;pa++)	Winch[pa].flag_dessin = 1;
	
	/*
	printf("effort_structure = %d ",Sortie_texte.effort_structure);
	printf("diametre_prise = %d ",Sortie_texte.diametre_prise);
	printf("epaisseur_prise = %d ",Sortie_texte.epaisseur_prise);
	printf("volume_capture = %d ",Sortie_texte.volume_capture);
	printf("surface_filtree = %d ",Sortie_texte.surface_filtree);
	printf("vitesse_courant = %d ",Sortie_texte.vitesse_courant);
	*/

	chaine[1] = '\0';
	/*printf("chaine = %s\n",chaine);
	i = strlen(chaine);
	printf("longueur chaine = %d\n",i);
	i = lecture_chaine(fic,chaine);*/

	Structure.drawing = 0;	/*in colors*/
	Structure.visible_symmetry = 1;	/*symmetry is visible*/
	/* debut modifdp du 4 mars 2010*/
	Structure.nb_sphere_element = 0;
	/* fin modifdp du 4 mars 2010*/
	Structure.nb_value = 0;		/*nb of linear value*/
	Structure.wave_model = 1;		//default value, the wave model used is Airy finite depth. The alternatives are 2: Stokes 2d order finite depth and 3: Stokes 3d order infinite depth
  	lambda = G / 2.0 / PI * Houle.periode * Houle.periode;	//initial value
  	do  
  		{  
  		ff= G*Houle.periode*Houle.periode/2.0/PI*tanh(2.0*PI*Houle.depth/lambda)-lambda;
  		ffprim = -G*Houle.periode*Houle.periode*Houle.depth/lambda/lambda/cosh(2.0*PI*Houle.depth/lambda)/cosh(2.0*PI*Houle.depth/lambda)-1.0;
  		hlambda=-ff/ffprim;
  		lambda=lambda+hlambda;
  		}
  	while (fabs(ff)>0.0001);
  	Houle.lambda = G / 2.0 / PI * Houle.periode * Houle.periode; 	//value for large depth
  	printf("G/2/PI*T²                 = %lf m\n",Houle.lambda);
  	Houle.lambda = lambda;
  	printf("lambda Airy finite depth  = %lf m\n",Houle.lambda);
  	Houle.k     = 2.0 * PI / Houle.lambda;
  	Houle.omega = 2.0 * PI / Houle.periode;
	
	while (lecture_chaine(fic,chaine) != 0)
		{
		
		i = strlen(chaine);
		//printf("chaine = %s  ",chaine);
		//printf("longueur chaine = %d\n",i);/**/
	
		if (strcmp(chaine,"output") == 0)
			{
			/*printf("lecture d output  ");*/
			i = lecture_chaine(fic,chaine);
			printf("ch_output %s  ",chaine);
			if (strcmp(chaine,"ballast_altitude") == 0)
				{
				Structure.ballast_altitude = 1;
				printf("There is record a record of the ballasts altitude in sta file\n");
				}
			if (strcmp(chaine,"value") == 0)
				{
				printf("lecture value \n");
				Structure.nb_value++;
				if (Structure.nb_value == 1)
					{
       				 	/**********************************************/
       					Value.depth1 = (double *) malloc((1 + Structure.nb_value) * sizeof(double));
       					if (Value.depth1    == NULL)
						{
						printf("Value.depth1  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
       					Value.depth2 = (double *) malloc((1 + Structure.nb_value) * sizeof(double));
       					if (Value.depth2    == NULL)
						{
						printf("Value.depth2  1 = NULL  \n" );
						exit(0);
						}
       				 	/**********************************************/
       					Value.value1 = (double *) malloc((1 + Structure.nb_value) * sizeof(double));
       					if (Value.value1    == NULL)
						{
						printf("Value.value1  1 = NULL  \n" );
						exit(0);
						}
       				 	/**********************************************/
       					Value.value2 = (double *) malloc((1 + Structure.nb_value) * sizeof(double));
       					if (Value.value2    == NULL)
						{
						printf("Value.value2  1 = NULL  \n" );
						exit(0);
						}
       				 	/**********************************************/
					}
				else
					{
					Value.depth1 = 	(double *) Realloc_double(Value.depth1,1 + Structure.nb_value);
					Value.depth2 = 	(double *) Realloc_double(Value.depth2,1 + Structure.nb_value);
					Value.value1 = 	(double *) Realloc_double(Value.value1,1 + Structure.nb_value);
					Value.value2 = 	(double *) Realloc_double(Value.value2,1 + Structure.nb_value);
					}
				itmp = fscanf(fic,"%lf",&Value.depth1[Structure.nb_value]);	/*reading of the first depth*/
				itmp = fscanf(fic,"%lf",&Value.value1[Structure.nb_value]);	/*reading of the first depth*/
				itmp = fscanf(fic,"%lf",&Value.depth2[Structure.nb_value]);	/*reading of the first depth*/
				itmp = fscanf(fic,"%lf",&Value.value2[Structure.nb_value]);	/*reading of the first depth*/
				if (Value.depth1[Structure.nb_value] == Value.depth2[Structure.nb_value])
					{
					printf("value nb %d:",Structure.nb_value);
					printf("value %lf at depth %lf m and value %lf at depth %lf m\n",Value.value1[Structure.nb_value],Value.depth1[Structure.nb_value],Value.value2[Structure.nb_value],Value.depth2[Structure.nb_value]);
					printf("ERROR: the two depths (%lf m) can't be equal\n",Value.depth1[Structure.nb_value]);
					exit(0);
					}
				for (zi = 1; zi<=Structure.nb_value ; zi++)
					{
					/*
					printf("value nb %d:",zi);
					printf("value %lf at depth %lf m and value %lf at depth %lf m\n",Value.value1[zi],Value.depth1[zi],Value.value2[zi],Value.depth2[zi]);
					*/
					}
				}
			if (strcmp(chaine,"black_drawing") == 0)
				{
				printf("black_drawing\n");
				Structure.drawing = 1;	/*only black*/
				RED = BLACK;
				GREEN = BLACK;
				BLUE = BLACK;
				YELLOW = BLACK;
				}
			if (strcmp(chaine,"bottom_drag") == 0)
				{
				printf("lecture de bottom_drag\n");
				Sortie_texte.bottom_drag = 1;
				}
			if (strcmp(chaine,"catch_drag") == 0)
				{
				printf("lecture de catch_drag\n");
				Sortie_texte.catch_drag = 1;
				}
			if (strcmp(chaine,"element_drag") == 0)
				{
				printf("lecture de element_drag\n");
				Sortie_texte.element_drag = 1;
				}
			if (strcmp(chaine,"surface_drag") == 0)
				{
				printf("lecture de surface_drag\n");
				Sortie_texte.surface_drag = 1;
				}
			if (strcmp(chaine,"node_drag") == 0)
				{
				printf("lecture de node_drag\n");
				Sortie_texte.node_drag = 1;
				}
			if (strcmp(chaine,"catch_diameter") == 0)
				{
				printf("lecture de catch_diameter\n");
				Sortie_texte.diametre_prise = 1;
				}
			if (strcmp(chaine,"catch_volume") == 0)
				{
				printf("lecture de catch_volume\n");
				Sortie_texte.volume_capture = 1;
				}
			if (strcmp(chaine,"cable_length") == 0)
				{
				printf("lecture de cable_length ");
				Sortie_texte.nb_longueur_cable++;
				if (Sortie_texte.nb_longueur_cable == 1)
					{
					Sortie_texte.element_longueur_cable =	(int *) Malloc_int(1 + Sortie_texte.nb_longueur_cable);
					Sortie_texte.decimale_longueur_cable = 	(int *) Malloc_int(1 + Sortie_texte.nb_longueur_cable);
					Sortie_texte.comment_longueur_cable =	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_longueur_cable);
					Sortie_texte.valeur_longueur_cable = 	(double *) Malloc_double(1 + Sortie_texte.nb_longueur_cable);
					}
				else
					{
					Sortie_texte.element_longueur_cable =	(int *) Realloc_int(Sortie_texte.element_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
					Sortie_texte.decimale_longueur_cable = 	(int *) Realloc_int(Sortie_texte.decimale_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
					Sortie_texte.comment_longueur_cable =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
					Sortie_texte.valeur_longueur_cable = 	(double *) Realloc_double(Sortie_texte.valeur_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
					}
				i = lecture_commentaire(fic,comment);
				if (i == 0) printf("erreur dans l enonce de la longueur de cable\n");
 
				/*lecture du commentaire entre "*/
				for (zi=0;zi<=strlen(comment);zi++)
					Sortie_texte.comment_longueur_cable[Sortie_texte.nb_longueur_cable].texte[zi] = comment[zi];
				/*lecture du numero (int) de l element entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&Sortie_texte.element_longueur_cable[Sortie_texte.nb_longueur_cable]);
				/*lecture du nb (int) de decimale pour l affichage entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&Sortie_texte.decimale_longueur_cable[Sortie_texte.nb_longueur_cable]);
				/*
				printf("comment %s ",Sortie_texte.comment_longueur_cable[Sortie_texte.nb_longueur_cable].texte);
				printf("element %d ",Sortie_texte.element_longueur_cable[Sortie_texte.nb_longueur_cable]);
				printf("decimal %d\n",Sortie_texte.decimale_longueur_cable[Sortie_texte.nb_longueur_cable]);
				*/
				}
			if (strcmp(chaine,"energy_elongation_diamond") == 0)
				{
				printf("lecture de energy_elastic_diamond \n");
				Sortie_texte.nb_energie_elong_diamond++;
				Sortie_texte.panneau_energie_elong =	(int *) Realloc_int(Sortie_texte.panneau_energie_elong,1 + Sortie_texte.nb_energie_elong_diamond);
				Sortie_texte.decimale_energie_elong = 	(int *) Realloc_int(Sortie_texte.decimale_energie_elong,1 + Sortie_texte.nb_energie_elong_diamond);
				Sortie_texte.comment_energie_elong_diamond =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_energie_elong_diamond,1 + Sortie_texte.nb_energie_elong_diamond);
				i = lecture_commentaire(fic,comment);
				if (i == 0) printf("erreur dans l enonce de l ernegie d elongation filet losange\n");
 
				/*lecture du commentaire entre "*/
				for (zi=0;zi<=strlen(comment);zi++)
					Sortie_texte.comment_energie_elong_diamond[Sortie_texte.nb_energie_elong_diamond].texte[zi] = comment[zi];
				/*lecture du numero (int) du panneau entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&Sortie_texte.panneau_energie_elong[Sortie_texte.nb_energie_elong_diamond]);
				/*lecture du nb (int) de decimale pour l affichage entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&Sortie_texte.decimale_energie_elong[Sortie_texte.nb_energie_elong_diamond]);
				/*
				printf("comment %s ",Sortie_texte.comment_longueur_cable[Sortie_texte.nb_longueur_cable].texte);
				printf("element %d ",Sortie_texte.element_longueur_cable[Sortie_texte.nb_longueur_cable]);
				printf("decimal %d\n",Sortie_texte.decimale_longueur_cable[Sortie_texte.nb_longueur_cable]);
				*/
				}
			if (strcmp(chaine,"energy_foldind_diamond") == 0)
				{
				printf("lecture de energy_folding_diamond \n");
				Sortie_texte.nb_energie_fold_diamond++;
				Sortie_texte.panneau_energie_fold =	(int *) Realloc_int(Sortie_texte.panneau_energie_fold,1 + Sortie_texte.nb_energie_fold_diamond);
				Sortie_texte.decimale_energie_fold = 	(int *) Realloc_int(Sortie_texte.decimale_energie_fold,1 + Sortie_texte.nb_energie_fold_diamond);
				Sortie_texte.comment_energie_fold_diamond =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_energie_fold_diamond,1 + Sortie_texte.nb_energie_fold_diamond);
				i = lecture_commentaire(fic,comment);
				if (i == 0) printf("erreur dans l enonce de l ernegie d foldation filet losange\n");
 
				/*lecture du commentaire entre "*/
				for (zi=0;zi<=strlen(comment);zi++)
					Sortie_texte.comment_energie_fold_diamond[Sortie_texte.nb_energie_fold_diamond].texte[zi] = comment[zi];
				/*lecture du numero (int) du panneau entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&Sortie_texte.panneau_energie_fold[Sortie_texte.nb_energie_fold_diamond]);
				/*lecture du nb (int) de decimale pour l affichage entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&Sortie_texte.decimale_energie_fold[Sortie_texte.nb_energie_fold_diamond]);
				/*
				printf("comment %s ",Sortie_texte.comment_longueur_cable[Sortie_texte.nb_longueur_cable].texte);
				printf("element %d ",Sortie_texte.element_longueur_cable[Sortie_texte.nb_longueur_cable]);
				printf("decimal %d\n",Sortie_texte.decimale_longueur_cable[Sortie_texte.nb_longueur_cable]);
				*/
				}
			if (strcmp(chaine,"energy_opening_diamond") == 0)
				{
				printf("lecture de energy_opening_diamond \n");
				Sortie_texte.nb_energie_open_diamond++;
				Sortie_texte.panneau_energie_open =	(int *) Realloc_int(Sortie_texte.panneau_energie_open,1 + Sortie_texte.nb_energie_open_diamond);
				Sortie_texte.decimale_energie_open = 	(int *) Realloc_int(Sortie_texte.decimale_energie_open,1 + Sortie_texte.nb_energie_open_diamond);
				Sortie_texte.comment_energie_open_diamond =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_energie_open_diamond,1 + Sortie_texte.nb_energie_open_diamond);
				i = lecture_commentaire(fic,comment);
				if (i == 0) printf("erreur dans l enonce de l ernegie d openation filet losange\n");
 
				/*lecture du commentaire entre "*/
				for (zi=0;zi<=strlen(comment);zi++)
					Sortie_texte.comment_energie_open_diamond[Sortie_texte.nb_energie_open_diamond].texte[zi] = comment[zi];
				/*lecture du numero (int) du panneau entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&Sortie_texte.panneau_energie_open[Sortie_texte.nb_energie_open_diamond]);
				/*lecture du nb (int) de decimale pour l affichage entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&Sortie_texte.decimale_energie_open[Sortie_texte.nb_energie_open_diamond]);
				/*
				printf("comment %s ",Sortie_texte.comment_longueur_cable[Sortie_texte.nb_longueur_cable].texte);
				printf("element %d ",Sortie_texte.element_longueur_cable[Sortie_texte.nb_longueur_cable]);
				printf("decimal %d\n",Sortie_texte.decimale_longueur_cable[Sortie_texte.nb_longueur_cable]);
				*/
				}
			if (strcmp(chaine,"energy_contact_diamond") == 0)
				{
				printf("lecture de energy_contact_diamond \n");
				Sortie_texte.nb_energie_contact_diamond++;
				Sortie_texte.panneau_energie_contact =	(int *) Realloc_int(Sortie_texte.panneau_energie_contact,1 + Sortie_texte.nb_energie_contact_diamond);
				Sortie_texte.decimale_energie_contact = 	(int *) Realloc_int(Sortie_texte.decimale_energie_contact,1 + Sortie_texte.nb_energie_contact_diamond);
				Sortie_texte.comment_energie_contact_diamond =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_energie_contact_diamond,1 + Sortie_texte.nb_energie_contact_diamond);
				i = lecture_commentaire(fic,comment);
				if (i == 0) printf("erreur dans l enonce de l ernegie d de contact filet losange\n");
 
				/*lecture du commentaire entre "*/
				for (zi=0;zi<=strlen(comment);zi++)
					Sortie_texte.comment_energie_contact_diamond[Sortie_texte.nb_energie_contact_diamond].texte[zi] = comment[zi];
				/*lecture du numero (int) du panneau entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&Sortie_texte.panneau_energie_contact[Sortie_texte.nb_energie_contact_diamond]);
				/*lecture du nb (int) de decimale pour l affichage entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&Sortie_texte.decimale_energie_contact[Sortie_texte.nb_energie_contact_diamond]);
				/*
				printf("comment %s ",Sortie_texte.comment_longueur_cable[Sortie_texte.nb_longueur_cable].texte);
				printf("element %d ",Sortie_texte.element_longueur_cable[Sortie_texte.nb_longueur_cable]);
				printf("decimal %d\n",Sortie_texte.decimale_longueur_cable[Sortie_texte.nb_longueur_cable]);
				*/
				}
			if (strcmp(chaine,"volume_x") == 0)
				{
				printf("lecture de volume selon x\n");
				Sortie_texte.volume_x = 1;
				}
			if (strcmp(chaine,"volume_y") == 0)
				{
				printf("lecture de volume selon y\n");
				Sortie_texte.volume_y = 1;
				}
			if (strcmp(chaine,"volume_z") == 0)
				{
				printf("lecture de volume selon z\n");
				Sortie_texte.volume_z = 1;
				}
			if (strcmp(chaine,"volume_0") == 0)
				{
				printf("lecture de volume selon le courant\n");
				Sortie_texte.volume_0 = 1;
				}
			if (strcmp(chaine,"inner_surface") == 0)
				{
				printf("calculation of the ellipsoidal surface of the catch\n");
				Sortie_texte.inner_surface = 1;
				}
			if (strcmp(chaine,"inner_surface_triangulation") == 0)
				{
				printf("triangulation of the ellipsoidal surface of the catch\n");
				Sortie_texte.inner_surface_triangulation = 1;
				}
			if (strcmp(chaine,"no_visible_surface") == 0)
				{
				fscanf(fic,"%d",&temp_int);
				printf("no_visible_surface nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					fscanf(fic,"%d",&temp2_int);
					panneau[temp2_int].flag_dessin = 0;					
					}
				}
			if (strcmp(chaine,"no_visible_surface_hexa") == 0)
				{
				fscanf(fic,"%d",&temp_int);
				printf("no_visible_surface_hexa nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					fscanf(fic,"%d",&temp2_int);
					TypeSurfHexa[temp2_int].flag_dessin = 0;					
					}
				}
			if (strcmp(chaine,"no_visible_element_window") == 0)
				{
				itmp = fscanf(fic,"%lf",&txmin);
				itmp = fscanf(fic,"%lf",&txmax);
				itmp = fscanf(fic,"%lf",&tymin);
				itmp = fscanf(fic,"%lf",&tymax);
				itmp = fscanf(fic,"%lf",&tzmin);
				itmp = fscanf(fic,"%lf",&tzmax);
				printf("no_visible_element_window: %lf %lf %lf %lf %lf %lf \n",txmin,txmax,tymin,tymax,tzmin,tzmax);
				printf("NOMBRE_ELEMENTS: %d \n",NOMBRE_ELEMENTS);
				
				/* debut modifdp du 6 mars 2010*/				
				/*for (pa=1;pa<=NbTypeelem;pa++)
					{
					printf("TypeElement[%d].xyz12: %lf %lf %lf %lf %lf %lf \n",pa,TypeElement[pa].x1,TypeElement[pa].y1,TypeElement[pa].z1,TypeElement[pa].x2,TypeElement[pa].y2,TypeElement[pa].z2);
					}*/
				for (pa=1;pa<=NbTypeelem;pa++)
					{
					if ((TypeElement[pa].x1 > txmin) && (TypeElement[pa].x1 < txmax))
						{
						if ((TypeElement[pa].y1 > tymin) && (TypeElement[pa].y1 < tymax))
							{
							if ((TypeElement[pa].z1 > tzmin) && (TypeElement[pa].z1 < tzmax))
								{
								TypeElement[pa].flag_dessin = 0;				
								printf("no_visible_element: %d ",pa);
								}
							}								
						}
					if ((TypeElement[pa].x2 > txmin) && (TypeElement[pa].x2 < txmax))
						{
						if ((TypeElement[pa].y2 > tymin) && (TypeElement[pa].y2 < tymax))
							{
							if ((TypeElement[pa].z2 > tzmin) && (TypeElement[pa].z2 < tzmax))
								{
								TypeElement[pa].flag_dessin = 0;				
								printf("no_visible_element: %d ",pa);
								}
							}								
						}
					}
				}
			/* fin modifdp du 6 mars 2010*/				
			if (strcmp(chaine,"no_visible_element") == 0)
				{
				fscanf(fic,"%d",&temp_int);
				printf("no_visible_element nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					fscanf(fic,"%d",&temp2_int);
					TypeElement[temp2_int].flag_dessin = 0;					
					}
				}
			if (strcmp(chaine,"no_visible_coulisse") == 0)
				{
				fscanf(fic,"%d",&temp_int);
				printf("no_visible_coulisse nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					fscanf(fic,"%d",&temp2_int);
					Coulisse[temp2_int].flag_dessin = 0;					
					}
				}
			if (strcmp(chaine,"no_visible_winch") == 0)
				{
				fscanf(fic,"%d",&temp_int);
				printf("no_visible_winch nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					fscanf(fic,"%d",&temp2_int);
					Winch[temp2_int].flag_dessin = 0;					
					}
				}
			if (strcmp(chaine,"no_visible_symmetry") == 0)
				{
				Structure.visible_symmetry = 0;
				}
			if (strcmp(chaine,"eigenvalues") == 0)
				{
				itmp = fscanf(fic,"%d",&Structure.eigenvalues);
				}
			if (strcmp(chaine,"color_element") == 0)
				{
				fscanf(fic,"%d",&temp_int);
				fscanf(fic,"%d",&temp2_int);
				TypeElement[temp_int].flag_dessin = temp2_int;
				//printf("color_element %d is %d\n",temp_int,temp2_int);
				if (temp2_int == 0)	printf("color_element %d is invisible\n",temp_int);		
				if (temp2_int == 1)	printf("color_element %d is black\n",temp_int);		
				if (temp2_int == 2)	printf("color_element %d is blue\n",temp_int);		
				if (temp2_int == 3)	printf("color_element %d is red\n",temp_int);		
				if (temp2_int == 4)	printf("color_element %d is green\n",temp_int);		
				if (temp2_int == 5)	printf("color_element %d is yellow\n",temp_int);		
				if (temp2_int == 6)	printf("color_element %d is cyan\n",temp_int);		
				if (temp2_int == 7)	printf("color_element %d is purple\n",temp_int);		
				if (temp2_int == 8)	printf("color_element %d is light blue\n",temp_int);		
				if (temp2_int == 9)	printf("color_element %d is orange\n",temp_int);		
				if (temp2_int == 10)	printf("color_element %d is light purple\n",temp_int);	
				if (temp2_int > 10)	printf("color_element %d is invisible\n",temp_int);	
				}
			if (strcmp(chaine,"color_surface") == 0)
				{
				fscanf(fic,"%d",&temp_int);
				fscanf(fic,"%d",&temp2_int);
				panneau[temp_int].flag_dessin = temp2_int;
				//printf("color_surface %d is %d\n",temp_int,temp2_int);
				if (temp2_int == 0)	printf("color_surface %d is invisible\n",temp_int);		
				if (temp2_int == 1)	printf("color_surface %d is black\n",temp_int);		
				if (temp2_int == 2)	printf("color_surface %d is blue\n",temp_int);		
				if (temp2_int == 3)	printf("color_surface %d is red\n",temp_int);		
				if (temp2_int == 4)	printf("color_surface %d is green\n",temp_int);		
				if (temp2_int == 5)	printf("color_surface %d is yellow\n",temp_int);		
				if (temp2_int == 6)	printf("color_surface %d is cyan\n",temp_int);		
				if (temp2_int == 7)	printf("color_surface %d is purple\n",temp_int);		
				if (temp2_int == 8)	printf("color_surface %d is light blue\n",temp_int);		
				if (temp2_int == 9)	printf("color_surface %d is orange\n",temp_int);		
				if (temp2_int == 10)	printf("color_surface %d is light purple\n",temp_int);	
				if (temp2_int > 10)	printf("color_surface %d is invisible\n",temp_int);	
				}
			}
		if (strcmp(chaine,"input") == 0)
			{
			/*printf("lecture d input  ");*/
			i = lecture_chaine(fic,chaine);
			//printf("ch_input %s  ",chaine);
			if (strcmp(chaine,"netting2ropes") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				itmp = fscanf(fic,"%d",&panneau[temp_int].netting_2_ropes_period);
				itmp = fscanf(fic,"%lf",&panneau[temp_int].netting_2_ropes_gap_U);
				itmp = fscanf(fic,"%lf",&panneau[temp_int].netting_2_ropes_gap_V);
				itmp = fscanf(fic,"%lf",&panneau[temp_int].netting_2_ropes_accuracy);
				panneau[temp_int].type_maillage = 4;
				printf("netting2ropes panel %d\n",temp_int);
				printf("type_maillage %d\n",panneau[temp_int].type_maillage);
				printf("netting_2_ropes_period %d	",panneau[temp_int].netting_2_ropes_period);
				printf("netting_2_ropes_gap_U %lf	",panneau[temp_int].netting_2_ropes_gap_U);
				printf("netting_2_ropes_gap_V %lf\n",panneau[temp_int].netting_2_ropes_gap_V);
				printf("netting_2_ropes_accuracy %lf\n",panneau[temp_int].netting_2_ropes_accuracy);
				//modification of the order of meshing in order to put this panel in first position
				temp1_char = 'p';
				temp1_int = temp_int;
				pa = 0;
				//exit(0);
				}
			if (strcmp(chaine,"foil2") == 0)
				{
				itmp = fscanf(fic,"%d", &node_type);
				itmp = fscanf(fic,"%lf",&actual_foil_surface);
				itmp = fscanf(fic,"%lf",&foil_cd);
				itmp = fscanf(fic,"%lf",&foil_cl);
				itmp = fscanf(fic,"%lf",&foil_cz);
				printf("foil2\n");
				printf("node_type %d\n",node_type);
				printf("actual_foil_surface %lf (m²)\n",actual_foil_surface);
				printf("foil_cd %lf ",foil_cd);
				printf("foil_cl %lf ",foil_cl);
				printf("foil_cz %lf\n",foil_cz);

				Fd = 0.5*RHO*foil_cd*actual_foil_surface*Courant.vitesse*Courant.vitesse;
				Fl = 0.5*RHO*foil_cl*actual_foil_surface*Courant.vitesse*Courant.vitesse;
				TypeNoeud[node_type].fx = Fd*cos(PI/180*Courant.direction) - Fl*sin(PI/180*Courant.direction);
				TypeNoeud[node_type].fy = Fd*sin(PI/180*Courant.direction) + Fl*cos(PI/180*Courant.direction);
				TypeNoeud[node_type].fz = 0.5*RHO*foil_cz*actual_foil_surface*Courant.vitesse*Courant.vitesse;
				printf("TypeNoeud[%d].fextxyz (N)	%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].fx,TypeNoeud[node_type].fy,TypeNoeud[node_type].fz);	
				printf("Fd (N)				%lf 	Fl (N)		%lf\n",Fd,Fl);	
				//exit(0);
				}
			if (strcmp(chaine,"foil") == 0)
				{
				itmp = fscanf(fic, "%d", &node_type);
				itmp = fscanf(fic,"%lf",&actual_foil_surface);
				itmp = fscanf(fic,"%lf",&model_foil_surface);
				itmp = fscanf(fic,"%lf",&model_mass_in_air);
				itmp = fscanf(fic,"%lf",&model_mass_in_water);
				itmp = fscanf(fic,"%lf",&foil_cd);
				itmp = fscanf(fic,"%lf",&foil_cl);
				itmp = fscanf(fic,"%lf",&foil_cz);
				printf("foil\n");
				printf("node_type %d\n",node_type);
				printf("actual_foil_surface %lf (m²)\n",actual_foil_surface);
				printf("model_foil_surface %lf (m²)\n",model_foil_surface);
				printf("model_mass_in_air %lf (Kg) ",model_mass_in_air);
				printf("model_mass_in_water %lf (Kg)\n",model_mass_in_water);
				printf("foil_cd %lf ",foil_cd);
				printf("foil_cl %lf ",foil_cl);
				printf("foil_cz %lf\n",foil_cz);

				ref_length_model = sqrt(model_foil_surface);
				ref_volume_model = ref_length_model*ref_length_model*ref_length_model;
				ratio_mass_in_air_volume = model_mass_in_air / ref_volume_model;
				ref_length_actual = sqrt(actual_foil_surface);
				ref_volume_actual = ref_length_actual*ref_length_actual*ref_length_actual;
				actual_mass_in_air = ref_volume_actual*ratio_mass_in_air_volume;
				model_density = RHO*model_mass_in_air*(model_mass_in_air-model_mass_in_water);
				actual_volume = (model_mass_in_air-model_mass_in_water)/RHO/model_mass_in_air*actual_mass_in_air;
				TypeNoeud[node_type].mx = actual_mass_in_air;		TypeNoeud[node_type].my = actual_mass_in_air;		TypeNoeud[node_type].my = actual_mass_in_air;
				TypeNoeud[node_type].majx = actual_mass_in_air;		TypeNoeud[node_type].majy = actual_mass_in_air;		TypeNoeud[node_type].majy = actual_mass_in_air;
				TypeNoeud[node_type].sx = pow(actual_volume,1.0/3.0);	TypeNoeud[node_type].sy = pow(actual_volume,1.0/3.0);	TypeNoeud[node_type].sz = pow(actual_volume,1.0/3.0);
				TypeNoeud[node_type].cdx = 0.0;				TypeNoeud[node_type].cdy = 0.0;				TypeNoeud[node_type].cdz = 0.0;
				Fd = 0.5*RHO*foil_cd*actual_foil_surface*Courant.vitesse*Courant.vitesse;
				Fl = 0.5*RHO*foil_cl*actual_foil_surface*Courant.vitesse*Courant.vitesse;
				TypeNoeud[node_type].fx = Fd*cos(PI/180*Courant.direction) - Fl*sin(PI/180*Courant.direction);
				TypeNoeud[node_type].fy = Fd*sin(PI/180*Courant.direction) + Fl*cos(PI/180*Courant.direction);
				TypeNoeud[node_type].fz = 0.5*RHO*foil_cz*actual_foil_surface*Courant.vitesse*Courant.vitesse;
				printf("TypeNoeud[%d].mxyz (N)		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].mx,TypeNoeud[node_type].my,TypeNoeud[node_type].mz);	
				printf("TypeNoeud[%d].majxyz (N)		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].majx,TypeNoeud[node_type].majy,TypeNoeud[node_type].majz);	
				printf("TypeNoeud[%d].sxyz (m)		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].sx,TypeNoeud[node_type].sy,TypeNoeud[node_type].sz);	
				printf("TypeNoeud[%d].cdxyz		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].cdx,TypeNoeud[node_type].cdy,TypeNoeud[node_type].cdz);	
				printf("TypeNoeud[%d].fxyz (N)		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].fx,TypeNoeud[node_type].fy,TypeNoeud[node_type].fz);	
				printf("Fd (N)				%lf 	Fl (N)		%lf\n",Fd,Fl);	
				}
			if (strcmp(chaine,"wave_model") == 0)
				{
				itmp = fscanf(fic, "%d", &Structure.wave_model);
				if (Structure.wave_model == 1)
					{
			 		//Airy finite depth
				  	//calcul of lambda by Newton-Raphson with accuracy of  0.0001m/////////////////////////////////////////////
				  	lambda = G / 2.0 / PI * Houle.periode * Houle.periode;	//initial value
				  	do  
				  		{  
				  		ff= G*Houle.periode*Houle.periode/2.0/PI*tanh(2.0*PI*Houle.depth/lambda)-lambda;
				  		ffprim = -G*Houle.periode*Houle.periode*Houle.depth/lambda/lambda/cosh(2.0*PI*Houle.depth/lambda)/cosh(2.0*PI*Houle.depth/lambda)-1.0;
				  		hlambda=-ff/ffprim;
				  		lambda=lambda+hlambda;
				  		}
				  	while (fabs(ff)>0.0001);

				  	Houle.lambda = G / 2.0 / PI * Houle.periode * Houle.periode; 	//value for large depth
				  	printf("G/2/PI*T²                 = %lf m\n",Houle.lambda);
				  	Houle.lambda = lambda;
				  	printf("lambda Airy finite depth  = %lf m\n",Houle.lambda);
					}
				if (Structure.wave_model == 2)
					{
					//Stokes 2d order finite depth
				  	//calcul of lambda by Newton-Raphson with accuracy of  0.0001m/////////////////////////////////////////////
				  	lambda = G / 2.0 / PI * Houle.periode * Houle.periode;	//initial value
				  	do  
				  		{  
			  			ff= G*Houle.periode*Houle.periode/2.0/PI*tanh(2.0*PI*Houle.depth/lambda)-lambda;
			  			ffprim = -G*Houle.periode*Houle.periode*Houle.depth/lambda/lambda/cosh(2.0*PI*Houle.depth/lambda)/cosh(2.0*PI*Houle.depth/lambda)-1.0;
				  		hlambda=-ff/ffprim;
				  		lambda=lambda+hlambda;
				  		}
				  	while (fabs(ff)>0.0001);

				  	Houle.lambda = G / 2.0 / PI * Houle.periode * Houle.periode; 	//value for large depth
				  	printf("G/2/PI*T²                            = %lf m\n",Houle.lambda);
				  	Houle.lambda = lambda;
				  	printf("lambda Stokes 2d order finite depth  = %lf m\n",Houle.lambda);		
					}
				if (Structure.wave_model == 3)
					{
					//Stokes 3d order infinite depth
				  	//calcul of lambda by Newton-Raphson with accuracy of  0.0001m/////////////////////////////////////////////
				  	lambda = G / 2.0 / PI * Houle.periode * Houle.periode;	//initial value
				  	do  
				  		{  
						ff=lambda/Houle.periode-(((2.0*PI*PI*(Houle.hauteur/2.0)*(Houle.hauteur/2.0))/lambda/lambda+1.0)*sqrt(lambda*G))/(sqrt(2.0)*sqrt(PI));
						ffprim = (sqrt(8.0*PI*PI*PI)*(Houle.hauteur/2.0)*(Houle.hauteur/2.0)*sqrt(lambda*G))/lambda/lambda/lambda-(((2.0*PI*PI*(Houle.hauteur/2.0)*(Houle.hauteur/2.0))/lambda/lambda+1.0)*G)/(sqrt(8.0*PI)*sqrt(lambda*G))+1.0/Houle.periode;
						hlambda=-ff/ffprim;
						lambda=lambda+hlambda;
				  		//printf("lambda  %lf m \n",lambda);		
				  		}
				  	while (fabs(ff)>0.0001);

				  	Houle.lambda = G / 2.0 / PI * Houle.periode * Houle.periode; 	//value for large depth
				  	printf("G/2/PI*T²                              = %lf m\n",Houle.lambda);
				  	Houle.lambda = lambda;
				  	printf("lambda Stokes 3d order infinite depth  = %lf m\n",Houle.lambda);
					kk = 2.0*PI/Houle.lambda;
					aa = Houle.hauteur/2;
				  	printf("crest to trough will be  %lf m\n",Houle.hauteur*(1+3.0/8.0*kk*kk*aa*aa));	
					//calcul de l amplitude aa pour obtenir une hauteur crete a creux de Houle.hauteur
				  	//printf("kk  = %lf m\n",kk);		
					do
						{
						ff=aa*aa*aa+8.0/3.0/kk/kk*aa-8.0*(Houle.hauteur/2.0)/3.0/kk/kk;
						ffprim=aa*aa*3+8.0/3.0/kk/kk;
						dh=-ff/ffprim;
						aa=aa+dh;
				  		//printf("ff  = %lf m\n",ff);		
						}
					while (fabs(ff)>0.0001);
				  	//printf("ff  = %lf m\n",fabs(ff));		
				  	printf("For a crest to trough of %lf m,\nuse a wave height of     %lf m\n",Houle.hauteur,2*aa);	
				  	//exit(0);	
					}
			  	/*hauteur de houle par defaut a chaque noeud*/
			  	for (zi = 1 ; zi<= NOMBRE_NOEUDS; zi++) mh[zi] = 0.0;
			  	Houle.k     = 2.0 * PI / Houle.lambda;
			  	Houle.omega = 2.0 * PI / Houle.periode;
				printf("Houle.k  = %lf m\n",Houle.k);		
				printf("Houle.omega  = %lf m\n",Houle.omega);	
				}
			if (strcmp(chaine,"cable_tension_constant") == 0)
				{
				itmp = fscanf(fic, "%d", &i);
				itmp = fscanf(fic, "%lf", &TypeElement[i].tension_constant);
				TypeElement[i].constant_tension = 1;
				printf("cable_tension_constant, cable %d constant tension %lf N\n",i,TypeElement[i].tension_constant);
				}
			if (strcmp(chaine,"rope_X") == 0)
				{
				itmp = fscanf(fic,"%d",&zi);
				itmp = fscanf(fic,"%d",&zj);
				itmp = fscanf(fic,"%lf",&dist);
				printf("There are %d ropes like rope %d spaced of %lf created from rope %d (included)\n",zi,zj,dist,zj);
				for (pa=1;pa<=zi-1;pa++)
					{
					if (Structure.orientation == 1)
						{
						noeud[element[pa+zj].extremite[1]].z = noeud[element[pa+zj-1].extremite[1]].z + dist;
						noeud[element[pa+zj].extremite[1]].x = noeud[element[pa+zj-1].extremite[1]].x;
						noeud[element[pa+zj].extremite[1]].y = noeud[element[pa+zj-1].extremite[1]].y;
						noeud[element[pa+zj].extremite[2]].z = noeud[element[pa+zj-1].extremite[2]].z + dist;
						noeud[element[pa+zj].extremite[2]].x = noeud[element[pa+zj-1].extremite[2]].x;
						noeud[element[pa+zj].extremite[2]].y = noeud[element[pa+zj-1].extremite[2]].y;
						}
					if (Structure.orientation == 2)
						{
						noeud[element[pa+zj].extremite[1]].y = noeud[element[pa+zj-1].extremite[1]].y + dist;
						noeud[element[pa+zj].extremite[1]].z = noeud[element[pa+zj-1].extremite[1]].z;
						noeud[element[pa+zj].extremite[1]].x = noeud[element[pa+zj-1].extremite[1]].x;
						noeud[element[pa+zj].extremite[2]].y = noeud[element[pa+zj-1].extremite[2]].y + dist;
						noeud[element[pa+zj].extremite[2]].z = noeud[element[pa+zj-1].extremite[2]].z;
						noeud[element[pa+zj].extremite[2]].x = noeud[element[pa+zj-1].extremite[2]].x;
						}
					if (Structure.orientation == 3)
						{
						noeud[element[pa+zj].extremite[1]].x = noeud[element[pa+zj-1].extremite[1]].x + dist;
						noeud[element[pa+zj].extremite[1]].y = noeud[element[pa+zj-1].extremite[1]].y;
						noeud[element[pa+zj].extremite[1]].z = noeud[element[pa+zj-1].extremite[1]].z;
						noeud[element[pa+zj].extremite[2]].x = noeud[element[pa+zj-1].extremite[2]].x + dist;
						noeud[element[pa+zj].extremite[2]].y = noeud[element[pa+zj-1].extremite[2]].y;
						noeud[element[pa+zj].extremite[2]].z = noeud[element[pa+zj-1].extremite[2]].z;
						}
			    		TypeElement[pa+zj].raideur_traction 	= TypeElement[zj].raideur_traction;
			    		TypeElement[pa+zj].raideur_compression 	= TypeElement[zj].raideur_compression;
			    		TypeElement[pa+zj].lgrepos 			= TypeElement[zj].lgrepos;
			    		TypeElement[pa+zj].rhoelement 		= TypeElement[zj].rhoelement;
			    		TypeElement[pa+zj].diametrehydro 		= TypeElement[zj].diametrehydro;
			    		TypeElement[pa+zj].cdnormal 		= TypeElement[zj].cdnormal;
			    		TypeElement[pa+zj].ftangent 		= TypeElement[zj].ftangent;
			    		TypeElement[pa+zj].nb_barre 		= TypeElement[zj].nb_barre;
			    		TypeElement[pa+zj].type_noeud 		= TypeElement[zj].type_noeud;
					}
				}
/* debut modifdp du 4 mars 2010*/
			if (strcmp(chaine,"rope_Y") == 0)
				{
				itmp = fscanf(fic,"%d",&zi);
				itmp = fscanf(fic,"%d",&zj);
				itmp = fscanf(fic,"%lf",&dist);
				printf("There are %d ropes like rope %d spaced of %lf created from rope %d (included)\n",zi,zj,dist,zj);
				for (pa=1;pa<=zi-1;pa++)
					{
					if (Structure.orientation == 1)
						{
						noeud[element[pa+zj].extremite[1]].z = noeud[element[pa+zj-1].extremite[1]].z;
						noeud[element[pa+zj].extremite[1]].x = noeud[element[pa+zj-1].extremite[1]].x + dist;
						noeud[element[pa+zj].extremite[1]].y = noeud[element[pa+zj-1].extremite[1]].y;
						noeud[element[pa+zj].extremite[2]].z = noeud[element[pa+zj-1].extremite[2]].z;
						noeud[element[pa+zj].extremite[2]].x = noeud[element[pa+zj-1].extremite[2]].x + dist;
						noeud[element[pa+zj].extremite[2]].y = noeud[element[pa+zj-1].extremite[2]].y;
						}
					if (Structure.orientation == 2)
						{
						noeud[element[pa+zj].extremite[1]].y = noeud[element[pa+zj-1].extremite[1]].y;
						noeud[element[pa+zj].extremite[1]].z = noeud[element[pa+zj-1].extremite[1]].z + dist;
						noeud[element[pa+zj].extremite[1]].x = noeud[element[pa+zj-1].extremite[1]].x;
						noeud[element[pa+zj].extremite[2]].y = noeud[element[pa+zj-1].extremite[2]].y;
						noeud[element[pa+zj].extremite[2]].z = noeud[element[pa+zj-1].extremite[2]].z + dist;
						noeud[element[pa+zj].extremite[2]].x = noeud[element[pa+zj-1].extremite[2]].x;
						}
					if (Structure.orientation == 3)
						{
						noeud[element[pa+zj].extremite[1]].x = noeud[element[pa+zj-1].extremite[1]].x;
						noeud[element[pa+zj].extremite[1]].y = noeud[element[pa+zj-1].extremite[1]].y + dist;
						noeud[element[pa+zj].extremite[1]].z = noeud[element[pa+zj-1].extremite[1]].z;
						noeud[element[pa+zj].extremite[2]].x = noeud[element[pa+zj-1].extremite[2]].x;
						noeud[element[pa+zj].extremite[2]].y = noeud[element[pa+zj-1].extremite[2]].y + dist;
						noeud[element[pa+zj].extremite[2]].z = noeud[element[pa+zj-1].extremite[2]].z;
						}
			    		TypeElement[pa+zj].raideur_traction 	= TypeElement[zj].raideur_traction;
			    		TypeElement[pa+zj].raideur_compression 	= TypeElement[zj].raideur_compression;
			    		TypeElement[pa+zj].lgrepos 			= TypeElement[zj].lgrepos;
			    		TypeElement[pa+zj].rhoelement 		= TypeElement[zj].rhoelement;
			    		TypeElement[pa+zj].diametrehydro 		= TypeElement[zj].diametrehydro;
			    		TypeElement[pa+zj].cdnormal 		= TypeElement[zj].cdnormal;
			    		TypeElement[pa+zj].ftangent 		= TypeElement[zj].ftangent;
			    		TypeElement[pa+zj].nb_barre 		= TypeElement[zj].nb_barre;
			    		TypeElement[pa+zj].type_noeud 		= TypeElement[zj].type_noeud;
					}
				}
			if (strcmp(chaine,"rope_Z") == 0)
				{
				itmp = fscanf(fic,"%d",&zi);
				itmp = fscanf(fic,"%d",&zj);
				itmp = fscanf(fic,"%lf",&dist);
				printf("There are %d ropes like rope %d spaced of %lf created from rope %d (included)\n",zi,zj,dist,zj);
				for (pa=1;pa<=zi-1;pa++)
					{
					if (Structure.orientation == 1)
						{
						noeud[element[pa+zj].extremite[1]].z = noeud[element[pa+zj-1].extremite[1]].z;
						noeud[element[pa+zj].extremite[1]].x = noeud[element[pa+zj-1].extremite[1]].x;
						noeud[element[pa+zj].extremite[1]].y = noeud[element[pa+zj-1].extremite[1]].y + dist;
						noeud[element[pa+zj].extremite[2]].z = noeud[element[pa+zj-1].extremite[2]].z;
						noeud[element[pa+zj].extremite[2]].x = noeud[element[pa+zj-1].extremite[2]].x;
						noeud[element[pa+zj].extremite[2]].y = noeud[element[pa+zj-1].extremite[2]].y + dist;
						}
					if (Structure.orientation == 2)
						{
						noeud[element[pa+zj].extremite[1]].y = noeud[element[pa+zj-1].extremite[1]].y;
						noeud[element[pa+zj].extremite[1]].z = noeud[element[pa+zj-1].extremite[1]].z;
						noeud[element[pa+zj].extremite[1]].x = noeud[element[pa+zj-1].extremite[1]].x + dist;
						noeud[element[pa+zj].extremite[2]].y = noeud[element[pa+zj-1].extremite[2]].y;
						noeud[element[pa+zj].extremite[2]].z = noeud[element[pa+zj-1].extremite[2]].z;
						noeud[element[pa+zj].extremite[2]].x = noeud[element[pa+zj-1].extremite[2]].x + dist;
						}
					if (Structure.orientation == 3)
						{
						noeud[element[pa+zj].extremite[1]].x = noeud[element[pa+zj-1].extremite[1]].x;
						noeud[element[pa+zj].extremite[1]].y = noeud[element[pa+zj-1].extremite[1]].y;
						noeud[element[pa+zj].extremite[1]].z = noeud[element[pa+zj-1].extremite[1]].z + dist;
						noeud[element[pa+zj].extremite[2]].x = noeud[element[pa+zj-1].extremite[2]].x;
						noeud[element[pa+zj].extremite[2]].y = noeud[element[pa+zj-1].extremite[2]].y;
						noeud[element[pa+zj].extremite[2]].z = noeud[element[pa+zj-1].extremite[2]].z + dist;
						}
			    		TypeElement[pa+zj].raideur_traction 	= TypeElement[zj].raideur_traction;
			    		TypeElement[pa+zj].raideur_compression 	= TypeElement[zj].raideur_compression;
			    		TypeElement[pa+zj].lgrepos	 		= TypeElement[zj].lgrepos;
			    		TypeElement[pa+zj].rhoelement 		= TypeElement[zj].rhoelement;
			    		TypeElement[pa+zj].diametrehydro 		= TypeElement[zj].diametrehydro;
			    		TypeElement[pa+zj].cdnormal 		= TypeElement[zj].cdnormal;
			    		TypeElement[pa+zj].ftangent 		= TypeElement[zj].ftangent;
			    		TypeElement[pa+zj].nb_barre 		= TypeElement[zj].nb_barre;
			    		TypeElement[pa+zj].type_noeud 		= TypeElement[zj].type_noeud;
					}
				}
			if (strcmp(chaine,"catch_gravity") == 0)
				{
				itmp = fscanf(fic,"%lf",&Prise.catch_gravity);
				printf("The density of the catch is %lf kg/m³\n",Prise.catch_gravity);
				}
			if (strcmp(chaine,"sphere_element") == 0)
				{
				/*printf("add sphere floats  \n");*/
				itmp = fscanf(fic,"%d",&E_numero);
				itmp = fscanf(fic,"%lf",&S_Nb);
				itmp = fscanf(fic,"%lf",&S_Diam);
				itmp = fscanf(fic,"%lf",&S_Float);
				
				Structure.nb_sphere_element++;
				
				if (Structure.nb_sphere_element == 1)
					{
					Sphere_element.element =	(int *)    Malloc_int(1 + Structure.nb_sphere_element);
					Sphere_element.nb =		(int *)    Malloc_int(1 + Structure.nb_sphere_element);
					Sphere_element.diameter =	(double *)    Malloc_double(1 + Structure.nb_sphere_element);
					Sphere_element.floatability =	(double *)    Malloc_double(1 + Structure.nb_sphere_element);
					}
				else
					{
					Sphere_element.element  =	(int *) Realloc_int(Sphere_element.element ,1 + Structure.nb_sphere_element);
					Sphere_element.nb  =		(int *) Realloc_int(Sphere_element.nb ,1 + Structure.nb_sphere_element);
					Sphere_element.diameter =	(double *) Realloc_double(Sphere_element.diameter,1 + Structure.nb_sphere_element);
					Sphere_element.floatability =	(double *) Realloc_double(Sphere_element.floatability,1 + Structure.nb_sphere_element);
					}
					
				Sphere_element.element[Structure.nb_sphere_element] = E_numero;
				Sphere_element.nb[Structure.nb_sphere_element] = (int) S_Nb;
				Sphere_element.diameter[Structure.nb_sphere_element] = S_Diam;
				Sphere_element.floatability[Structure.nb_sphere_element] = S_Float;
				/*
				printf("Sphere_element.nb[Structure.nb_sphere_element] %d\n",Sphere_element.nb[Structure.nb_sphere_element]);
				exit(0);
				*/
				}			
			if (strcmp(chaine,"sphere_element2") == 0)
				{
				/*printf("add sphere floats  \n");*/
				itmp = fscanf(fic,"%d",&E_numero);
				itmp = fscanf(fic,"%lf",&S_Nb);
				itmp = fscanf(fic,"%lf",&S_Diam);
				itmp = fscanf(fic,"%lf",&S_Float);
				itmp = fscanf(fic,"%lf",&L_Float);
				
				Structure.nb_sphere_element++;
				
				if (Structure.nb_sphere_element == 1)
					{
					Sphere_element.element =	(int *)    Malloc_int(1 + Structure.nb_sphere_element);
					Sphere_element.nb =		(int *)    Malloc_int(1 + Structure.nb_sphere_element);
					Sphere_element.diameter =	(double *)    Malloc_double(1 + Structure.nb_sphere_element);
					Sphere_element.floatability =	(double *)    Malloc_double(1 + Structure.nb_sphere_element);
					}
				else
					{
					Sphere_element.element  =	(int *) Realloc_int(Sphere_element.element ,1 + Structure.nb_sphere_element);
					Sphere_element.nb  =		(int *) Realloc_int(Sphere_element.nb ,1 + Structure.nb_sphere_element);
					Sphere_element.diameter =	(double *) Realloc_double(Sphere_element.diameter,1 + Structure.nb_sphere_element);
					Sphere_element.floatability =	(double *) Realloc_double(Sphere_element.floatability,1 + Structure.nb_sphere_element);
					}
					
				Sphere_element.element[Structure.nb_sphere_element] = E_numero;
				Sphere_element.nb[Structure.nb_sphere_element] = (int) S_Nb;
				Sphere_element.diameter[Structure.nb_sphere_element] = S_Diam;
				Sphere_element.floatability[Structure.nb_sphere_element] = S_Float;
				/*
				printf("Sphere_element.nb[Structure.nb_sphere_element] %d\n",Sphere_element.nb[Structure.nb_sphere_element]);
				exit(0);
				*/
				}			
			if (strcmp(chaine,"neutral_angle") == 0)
				{
				printf("lecture de neutral_angle \n");
				/*lecture du numero (int) du panneau concerne entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&pa);
				/*lecture de la valeur de l'angle neutre (double) entre 2 caracteres blancs !!*/
				fscanf(fic,"%lf",&panneau[pa].neutral_angle);
				}
			if (strcmp(chaine,"EI_flexion") == 0)
				{
				printf("lecture de EI_flexion \n");
				/*lecture du numero (int) du panneau concerne entre 2 caracteres blancs !!*/
				fscanf(fic,"%d",&pa);
				/*lecture de la valeur de EI_flexion (double) entre 2 caracteres blancs !!*/
				fscanf(fic,"%lf",&panneau[pa].EI_flexion);
				}
			if (strcmp(chaine,"catch") == 0)
				{
				fscanf(fic,"%lf",&Prise.PR);	/*prise en m3*/
				fscanf(fic,"%lf",&Prise.PE);	/*perimetre du cul en m*/
				fscanf(fic,"%lf",&Prise.TA);	/*taille moyenne des poissons en m3*/
				fscanf(fic,"%lf",&Prise.RA);	/*mesh opening stiffness en N/m*/
				PE3 = pow(Prise.PE,3.0);
				Prise.volume = Prise.PR * (1.72*(pow(Prise.PR/PE3,-0.075)) + 0.046*(pow(Prise.TA/PE3,-0.034)) - 0.0772);
				if (WB < Prise.PR) WB = Prise.PR;
				printf("Catch characteristics : PR(m^3): %lf, PE(m): %lf, TA (m^3): %lf, RA (N/m): %lf, WB (m^3): %lf\n",Prise.PR,Prise.PE,Prise.TA,Prise.RA,Prise.volume);
				}
			if (strcmp(chaine,"balls") == 0)
				{
				printf("balls reading \n");
				fscanf(fic,"%d",&Ball.nb);
				printf("Ball.nb = %d \n",Ball.nb);
				fscanf(fic,"%lf",&tmp_d1);
				fscanf(fic,"%lf",&tmp_d2);
				fscanf(fic,"%lf",&tmp_d3);
				fscanf(fic,"%lf",&tmp_d4);
				fscanf(fic,"%lf",&tmp_d5);
				fscanf(fic,"%d",&tmp_i1);
				printf("Ball.radius = %lf \n",tmp_d1);
				}
			if (strcmp(chaine,"balls_2") == 0)
				{
				printf("balls reading \n");
				fscanf(fic,"%d",&Ball.nb);
				printf("Ball.nb = %d \n",Ball.nb);
				fscanf(fic,"%lf",&tmp_d1);
				fscanf(fic,"%lf",&tmp_d2);
				fscanf(fic,"%lf",&tmp_d3);
				fscanf(fic,"%lf",&tmp_d4);
				fscanf(fic,"%lf",&tmp_d5);
				fscanf(fic,"%d",&tmp_i1);
				fscanf(fic,"%lf",&tmp_d3);
				fscanf(fic,"%lf",&tmp_d4);
				fscanf(fic,"%lf",&tmp_d5);
				printf("Ball.radius = %lf \n",tmp_d1);
				}
			if (strcmp(chaine,"tarp") == 0)
				{
				/*lecture du numero (int) du panneau concerne !!*/
				fscanf(fic,"%d",&pa);
				panneau[pa].tarp = 1;
				printf("lecture de tarp, panneau : %d\n",pa);
				}

			/**********************************************************************************************************************/
			/**********************************************************************************************************************/

			if (strcmp(chaine,"add_cage") == 0)
				{

				/*reading of the center of rotation (xo,yo in m) */
				add_number_cage=add_number_cage+1;
				itmp = fscanf(fic,"%lf",&add_cage_diam);
				itmp = fscanf(fic,"%lf",&add_cage_xxo);
				itmp = fscanf(fic,"%lf",&add_cage_yyo);
				itmp = fscanf(fic,"%d",&add_cage_nsegment);
				itmp = fscanf(fic,"%lf",&add_cage_dist_ann);
				itmp = fscanf(fic,"%lf",&add_cage_haut_ann);
				itmp = fscanf(fic,"%lf",&add_hauteur_filet_elev);
				itmp = fscanf(fic,"%lf",&add_taille_maille_elev);
				itmp = fscanf(fic,"%lf",&diametre_pehd);
				itmp = fscanf(fic,"%lf",&epaisseur_pehd);
				itmp = fscanf(fic,"%lf",&rho_pehd);
				itmp = fscanf(fic,"%s",chainebis);


				if (strcmp(chainebis,"immersion") == 0)
					{
					immersion =1;
					}
				if (strcmp(chainebis,"floating") == 0)
					{
					immersion =0;
					}
				printf("cage of %lf diametre centre x %lf y %lf nombre de segment %d \n",add_cage_diam,add_cage_xxo,add_cage_yyo,add_cage_nsegment);


				/* définition des paramètres*/

				double hauteur_pieds = add_cage_haut_ann;
				double distance_anneaux = add_cage_dist_ann;

				double coeff_trainee_inter = 1.2;	/* coefficient de trainée des barres de la cage*/

				double pronf_niveau_bas = 0;		/* profondeur des barres du niveau bas (sous phobos)*/
				double pronf_niveau_haut = pronf_niveau_bas + add_cage_haut_ann;		/* profondeur des barres du niveau haut (sous phobos)*/

				
				/* 		ELEMENT 	*/



				for (zi=elem_inter;zi<=elem_inter+8*add_cage_nsegment-1;zi=zi+8)
					{
					int fl = floor((zi-elem_inter)/8);

					xxp11 = (float) add_cage_xxo - add_cage_diam/2*cos(2*PI*fl/add_cage_nsegment);
					yyp11 = (float) add_cage_yyo - add_cage_diam/2*sin(2*PI*fl/add_cage_nsegment);
					xxp12 = (float) add_cage_xxo - add_cage_diam/2*cos(2*PI*(fl+1)/add_cage_nsegment);
					yyp12 = (float) add_cage_yyo - add_cage_diam/2*sin(2*PI*(fl+1)/add_cage_nsegment);
					
					xxp21 = (float) add_cage_xxo - (add_cage_diam/2+distance_anneaux)*cos(2*PI*fl/add_cage_nsegment);
					yyp21 = (float) add_cage_yyo - (add_cage_diam/2+distance_anneaux)*sin(2*PI*fl/add_cage_nsegment);
					xxp22 = (float) add_cage_xxo - (add_cage_diam/2+distance_anneaux)*cos(2*PI*(fl+1)/add_cage_nsegment);
					yyp22 = (float) add_cage_yyo - (add_cage_diam/2+distance_anneaux)*sin(2*PI*(fl+1)/add_cage_nsegment);
					
					xxp31 = xxp12;
					yyp31 = yyp12;
					xxp32 = xxp22;
					yyp32 = yyp22;

					xxp41 = xxp11;
					yyp41 = yyp11;
					xxp42 = xxp12;
					yyp42 = yyp12;
					
					xxp51 = xxp12;
					yyp51 = yyp12;
					xxp52 = xxp12;
					yyp52 = yyp12;
					
					xxp61 = xxp42;
					yyp61 = yyp42;
					xxp62 = xxp22;
					yyp62 = yyp22;

					xxp71 = xxp21;
					yyp71 = yyp21;
					xxp72 = xxp12;
					yyp72 = yyp12;

					xxp81 = xxp12;
					yyp81 = yyp12;
					xxp82 = xxp41;
					yyp82 = yyp41;

					TypeElement[zi+0].x1 = xxp11;
					TypeElement[zi+0].y1 = yyp11;
					TypeElement[zi+0].z1 = pronf_niveau_bas;

					TypeElement[zi+0].x2 = xxp12;
					TypeElement[zi+0].y2 = yyp12;
					TypeElement[zi+0].z2 = pronf_niveau_bas;

					TypeElement[zi+1].x1 = xxp21;
					TypeElement[zi+1].y1 = yyp21;
					TypeElement[zi+1].z1 = pronf_niveau_bas;

					TypeElement[zi+1].x2 = xxp22;
					TypeElement[zi+1].y2 = yyp22;
					TypeElement[zi+1].z2 = pronf_niveau_bas;

					TypeElement[zi+2].x1 = xxp31;
					TypeElement[zi+2].y1 = yyp31;
					TypeElement[zi+2].z1 = pronf_niveau_bas;

					TypeElement[zi+2].x2 = xxp32;
					TypeElement[zi+2].y2 = yyp32;
					TypeElement[zi+2].z2 = pronf_niveau_bas;

					TypeElement[zi+3].x1 = xxp41;
					TypeElement[zi+3].y1 = yyp41;
					TypeElement[zi+3].z1 = pronf_niveau_haut;

					TypeElement[zi+3].x2 = xxp42;
					TypeElement[zi+3].y2 = yyp42;
					TypeElement[zi+3].z2 = pronf_niveau_haut;

					TypeElement[zi+4].x1 = xxp51;
					TypeElement[zi+4].y1 = yyp51;
					TypeElement[zi+4].z1 = pronf_niveau_haut;

					TypeElement[zi+4].x2 = xxp52;
					TypeElement[zi+4].y2 = yyp52;
					TypeElement[zi+4].z2 = pronf_niveau_bas;


					TypeElement[zi+5].x1 = xxp61;
					TypeElement[zi+5].y1 = yyp61;
					TypeElement[zi+5].z1 = pronf_niveau_haut;

					TypeElement[zi+5].x2 = xxp62;
					TypeElement[zi+5].y2 = yyp62;
					TypeElement[zi+5].z2 = pronf_niveau_bas;

					TypeElement[zi+6].x1 = xxp71;
					TypeElement[zi+6].y1 = yyp71;
					TypeElement[zi+6].z1 = pronf_niveau_bas;

					TypeElement[zi+6].x2 = xxp72;
					TypeElement[zi+6].y2 = yyp72;
					TypeElement[zi+6].z2 = pronf_niveau_bas;

					TypeElement[zi+7].x1 = xxp81;
					TypeElement[zi+7].y1 = yyp81;
					TypeElement[zi+7].z1 = pronf_niveau_bas;

					TypeElement[zi+7].x2 = xxp82;
					TypeElement[zi+7].y2 = yyp82;
					TypeElement[zi+7].z2 = pronf_niveau_haut;


					/* Calcul Coeff trainée + diametre + masse volumqiue pieds */


					/*TypeElement[zi+0].diametrehydro = diametre_pehd;	
					TypeElement[zi+1].diametrehydro = diametre_pehd;
					TypeElement[zi+2].diametrehydro = diametre_pehd;	
					TypeElement[zi+3].diametrehydro = diametre_pehd;				
					TypeElement[zi+4].diametrehydro = diametre_pehd;
					TypeElement[zi+5].diametrehydro = 0;	
					TypeElement[zi+6].diametrehydro = 0;
					TypeElement[zi+7].diametrehydro = 0;
				
				if (immersion ==0)
					{
					TypeElement[zi+0].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					TypeElement[zi+1].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					TypeElement[zi+2].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					TypeElement[zi+3].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					TypeElement[zi+4].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					}

				if (immersion ==1)
					{
					TypeElement[zi+0].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					TypeElement[zi+1].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					TypeElement[zi+2].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					TypeElement[zi+3].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					TypeElement[zi+4].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					}

					TypeElement[zi+0].cdnormal = coeff_trainee_inter;				
					TypeElement[zi+1].cdnormal = coeff_trainee_inter;
					TypeElement[zi+2].cdnormal = coeff_trainee_inter;
					TypeElement[zi+3].cdnormal = coeff_trainee_inter;
					TypeElement[zi+4].cdnormal = coeff_trainee_inter;*/

					double longueur_premiere_rangee=sqrt((TypeElement[zi+0].x1-TypeElement[zi+0].x2)*(TypeElement[zi+0].x1-TypeElement[zi+0].x2) + (TypeElement[zi+0].y1-TypeElement[zi+0].y2)*(TypeElement[zi+0].y1-TypeElement[zi+0].y2) + (TypeElement[zi+0].z1-TypeElement[zi+0].z2)*(TypeElement[zi+0].z1-TypeElement[zi+0].z2));
					double longueur_deuxieme_rangee=sqrt((TypeElement[zi+1].x1-TypeElement[zi+1].x2)*(TypeElement[zi+1].x1-TypeElement[zi+1].x2) + (TypeElement[zi+1].y1-TypeElement[zi+1].y2)*(TypeElement[zi+1].y1-TypeElement[zi+1].y2) + (TypeElement[zi+1].z1-TypeElement[zi+1].z2)*(TypeElement[zi+1].z1-TypeElement[zi+1].z2));
					double longueur_rangee_haute=sqrt((TypeElement[zi+3].x1-TypeElement[zi+3].x2)*(TypeElement[zi+3].x1-TypeElement[zi+3].x2) + (TypeElement[zi+3].y1-TypeElement[zi+3].y2)*(TypeElement[zi+3].y1-TypeElement[zi+3].y2) + (TypeElement[zi+3].z1-TypeElement[zi+3].z2)*(TypeElement[zi+3].z1-TypeElement[zi+3].z2));


					double volume_imerge1;
					double masse1;
					double trainee_totale1;
					double volume_imerge2;
					double masse2;
					double trainee_totale2;

				
					TypeElement[zi+4].raideur_compression = 5000000;
					TypeElement[zi+4].raideur_traction = 5000000;


					if (immersion ==0)
						{
						volume_imerge1 =(PI*diametre_pehd*diametre_pehd/4*add_cage_nsegment)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux);
						masse1 = PI/4*add_cage_nsegment*rho_pehd*(diametre_pehd*diametre_pehd -(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd))*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
					 	trainee_totale1 = diametre_pehd*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux) * add_cage_nsegment;

						TypeElement[zi+4].diametrehydro=sqrt(volume_imerge1/(PI*hauteur_pieds*add_cage_nsegment/4));
						TypeElement[zi+4].rhoelement=masse1/(hauteur_pieds*PI*TypeElement[zi+4].diametrehydro*TypeElement[zi+4].diametrehydro*add_cage_nsegment/4);

						double trainee_inter = TypeElement[zi+4].diametrehydro*hauteur_pieds*add_cage_nsegment;

						TypeElement[zi+4].cdnormal=coeff_trainee_inter*trainee_totale1/trainee_inter;
						}

					if (immersion ==1)
						{

						volume_imerge2 =(PI*diametre_pehd*diametre_pehd/4*add_cage_nsegment)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
						masse2 = PI/4*add_cage_nsegment*rho_pehd*(diametre_pehd*diametre_pehd -(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd))*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute)+PI/4*add_cage_nsegment*RHO*(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
						trainee_totale2 = diametre_pehd*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute) * add_cage_nsegment;
	
						TypeElement[zi+4].diametrehydro=sqrt(volume_imerge2/(PI*hauteur_pieds*add_cage_nsegment/4));
						TypeElement[zi+4].rhoelement=masse2/(hauteur_pieds*PI*TypeElement[zi+4].diametrehydro*TypeElement[zi+4].diametrehydro*add_cage_nsegment/4);

						double trainee_inter = TypeElement[zi+4].diametrehydro*hauteur_pieds*add_cage_nsegment;

						TypeElement[zi+4].cdnormal=coeff_trainee_inter*trainee_totale2/trainee_inter;
						}


					TypeElement[zi+6].flag_dessin = 0;
					TypeElement[zi+7].flag_dessin = 0;

					TypeElement[zi+6].raideur_traction=100000000;
					TypeElement[zi+6].raideur_compression=100000000;
					}

				/*calcul longueur repos*/

				nb_tot_elem += 8*add_cage_nsegment;

				for (zi=nb_ele_depart;zi<=nb_tot_elem;zi++)
					{
					TypeElement[zi].lgrepos=sqrt((TypeElement[zi].x1-TypeElement[zi].x2)*(TypeElement[zi].x1-TypeElement[zi].x2) + (TypeElement[zi].y1-TypeElement[zi].y2)*(TypeElement[zi].y1-TypeElement[zi].y2) + (TypeElement[zi].z1-TypeElement[zi].z2)*(TypeElement[zi].z1-TypeElement[zi].z2));
					}

				elem_inter += 8*add_cage_nsegment;
				nb_ele_depart += 8*add_cage_nsegment;
				nb_elem_cage += 8*add_cage_nsegment;

				}


			/**********************************************************************************************************************/
			/**********************************************************************************************************************/

			if (strcmp(chaine,"add_chapeau") == 0)
				{

				/*reading of the center of rotation (xo,yo in m) */
				add_number_cage=add_number_cage+1;
				itmp = fscanf(fic,"%lf",&add_cage_diam);
				itmp = fscanf(fic,"%lf",&add_cage_xxo);
				itmp = fscanf(fic,"%lf",&add_cage_yyo);
				itmp = fscanf(fic,"%d",&add_cage_nsegment);
				itmp = fscanf(fic,"%lf",&add_cage_dist_ann);
				itmp = fscanf(fic,"%lf",&add_cage_haut_ann);
				itmp = fscanf(fic,"%lf",&add_hauteur_filet_elev);
				itmp = fscanf(fic,"%lf",&add_taille_maille_elev);
				itmp = fscanf(fic,"%lf",&diametre_pehd);
				itmp = fscanf(fic,"%lf",&epaisseur_pehd);
				itmp = fscanf(fic,"%lf",&rho_pehd);
				itmp = fscanf(fic,"%s",chainebis);


				if (strcmp(chainebis,"immersion") == 0)
					{
					immersion =1;
					}
				if (strcmp(chainebis,"floating") == 0)
					{
					immersion =0;
					}
				printf("cage of %lf diametre centre x %lf y %lf nombre de segment %d \n",add_cage_diam,add_cage_xxo,add_cage_yyo,add_cage_nsegment);


				/* définition des paramètres*/

				double hauteur_pieds = add_cage_haut_ann;
				double distance_anneaux = add_cage_dist_ann;

				double coeff_trainee_inter = 1.2;	/* coefficient de trainée des barres de la cage*/

				double pronf_niveau_bas = 0;		/* profondeur des barres du niveau bas (sous phobos)*/
				double pronf_niveau_haut = pronf_niveau_bas + add_cage_haut_ann;		/* profondeur des barres du niveau haut (sous phobos)*/
				

				if (immersion == 0)
				{
					panneau[pan_inter_fond+1].flag_dessin = 0;
				}


				pan_inter_fond += add_cage_nsegment+2;



				/* 		ELEMENT 	*/



				for (zi=elem_inter;zi<=elem_inter+8*add_cage_nsegment-1;zi=zi+8)
					{
					int fl = floor((zi-elem_inter)/8);

					xxp11 = (float) add_cage_xxo - add_cage_diam/2*cos(2*PI*fl/add_cage_nsegment);
					yyp11 = (float) add_cage_yyo - add_cage_diam/2*sin(2*PI*fl/add_cage_nsegment);
					xxp12 = (float) add_cage_xxo - add_cage_diam/2*cos(2*PI*(fl+1)/add_cage_nsegment);
					yyp12 = (float) add_cage_yyo - add_cage_diam/2*sin(2*PI*(fl+1)/add_cage_nsegment);
					
					xxp21 = (float) add_cage_xxo - (add_cage_diam/2+distance_anneaux)*cos(2*PI*fl/add_cage_nsegment);
					yyp21 = (float) add_cage_yyo - (add_cage_diam/2+distance_anneaux)*sin(2*PI*fl/add_cage_nsegment);
					xxp22 = (float) add_cage_xxo - (add_cage_diam/2+distance_anneaux)*cos(2*PI*(fl+1)/add_cage_nsegment);
					yyp22 = (float) add_cage_yyo - (add_cage_diam/2+distance_anneaux)*sin(2*PI*(fl+1)/add_cage_nsegment);
					
					xxp31 = xxp12;
					yyp31 = yyp12;
					xxp32 = xxp22;
					yyp32 = yyp22;

					xxp41 = xxp11;
					yyp41 = yyp11;
					xxp42 = xxp12;
					yyp42 = yyp12;
					
					xxp51 = xxp12;
					yyp51 = yyp12;
					xxp52 = xxp12;
					yyp52 = yyp12;
					
					xxp61 = xxp42;
					yyp61 = yyp42;
					xxp62 = xxp22;
					yyp62 = yyp22;

					xxp71 = xxp21;
					yyp71 = yyp21;
					xxp72 = xxp12;
					yyp72 = yyp12;

					xxp81 = xxp12;
					yyp81 = yyp12;
					xxp82 = xxp41;
					yyp82 = yyp41;

					TypeElement[zi+0].x1 = xxp11;
					TypeElement[zi+0].y1 = yyp11;
					TypeElement[zi+0].z1 = pronf_niveau_bas;

					TypeElement[zi+0].x2 = xxp12;
					TypeElement[zi+0].y2 = yyp12;
					TypeElement[zi+0].z2 = pronf_niveau_bas;

					TypeElement[zi+1].x1 = xxp21;
					TypeElement[zi+1].y1 = yyp21;
					TypeElement[zi+1].z1 = pronf_niveau_bas;

					TypeElement[zi+1].x2 = xxp22;
					TypeElement[zi+1].y2 = yyp22;
					TypeElement[zi+1].z2 = pronf_niveau_bas;

					TypeElement[zi+2].x1 = xxp31;
					TypeElement[zi+2].y1 = yyp31;
					TypeElement[zi+2].z1 = pronf_niveau_bas;

					TypeElement[zi+2].x2 = xxp32;
					TypeElement[zi+2].y2 = yyp32;
					TypeElement[zi+2].z2 = pronf_niveau_bas;

					TypeElement[zi+3].x1 = xxp41;
					TypeElement[zi+3].y1 = yyp41;
					TypeElement[zi+3].z1 = pronf_niveau_haut;

					TypeElement[zi+3].x2 = xxp42;
					TypeElement[zi+3].y2 = yyp42;
					TypeElement[zi+3].z2 = pronf_niveau_haut;

					TypeElement[zi+4].x1 = xxp51;
					TypeElement[zi+4].y1 = yyp51;
					TypeElement[zi+4].z1 = pronf_niveau_haut;

					TypeElement[zi+4].x2 = xxp52;
					TypeElement[zi+4].y2 = yyp52;
					TypeElement[zi+4].z2 = pronf_niveau_bas;


					TypeElement[zi+5].x1 = xxp61;
					TypeElement[zi+5].y1 = yyp61;
					TypeElement[zi+5].z1 = pronf_niveau_haut;

					TypeElement[zi+5].x2 = xxp62;
					TypeElement[zi+5].y2 = yyp62;
					TypeElement[zi+5].z2 = pronf_niveau_bas;

					TypeElement[zi+6].x1 = xxp71;
					TypeElement[zi+6].y1 = yyp71;
					TypeElement[zi+6].z1 = pronf_niveau_bas;

					TypeElement[zi+6].x2 = xxp72;
					TypeElement[zi+6].y2 = yyp72;
					TypeElement[zi+6].z2 = pronf_niveau_bas;

					TypeElement[zi+7].x1 = xxp81;
					TypeElement[zi+7].y1 = yyp81;
					TypeElement[zi+7].z1 = pronf_niveau_bas;

					TypeElement[zi+7].x2 = xxp82;
					TypeElement[zi+7].y2 = yyp82;
					TypeElement[zi+7].z2 = pronf_niveau_haut;


					/* Calcul Coeff trainée + diametre + masse volumique pieds */

					/*if (immersion ==0)
						{
						TypeElement[zi+0].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
						TypeElement[zi+1].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
						TypeElement[zi+2].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
						TypeElement[zi+3].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
						TypeElement[zi+4].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
						}*/

					if (immersion ==1)
						{
						TypeElement[zi+0].diametrehydro = diametre_pehd;
						TypeElement[zi+0].raideur_compression = 5000000;
						TypeElement[zi+0].raideur_traction = 5000000;	
						TypeElement[zi+1].diametrehydro = diametre_pehd;
						TypeElement[zi+1].raideur_compression = 5000000;
						TypeElement[zi+1].raideur_traction = 5000000;	
						TypeElement[zi+2].diametrehydro = diametre_pehd;
						TypeElement[zi+2].raideur_compression = 5000000;
						TypeElement[zi+2].raideur_traction = 5000000;		
						TypeElement[zi+3].diametrehydro = diametre_pehd;
						TypeElement[zi+3].raideur_compression = 5000000;
						TypeElement[zi+3].raideur_traction = 5000000;					
						TypeElement[zi+4].diametrehydro = diametre_pehd;
						TypeElement[zi+4].raideur_compression = 5000000;
						TypeElement[zi+4].raideur_traction = 5000000;	
						TypeElement[zi+5].diametrehydro = 0;	
						TypeElement[zi+6].diametrehydro = 0;
						TypeElement[zi+7].diametrehydro = 0;
				
						TypeElement[zi+0].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
						TypeElement[zi+1].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
						TypeElement[zi+2].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
						TypeElement[zi+3].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
						TypeElement[zi+4].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					
						TypeElement[zi+0].cdnormal = coeff_trainee_inter;				
						TypeElement[zi+1].cdnormal = coeff_trainee_inter;
						TypeElement[zi+2].cdnormal = coeff_trainee_inter;
						TypeElement[zi+3].cdnormal = coeff_trainee_inter;
						TypeElement[zi+4].cdnormal = coeff_trainee_inter;					
						}


					if (immersion ==0)
						{
						double longueur_premiere_rangee=sqrt((TypeElement[zi+0].x1-TypeElement[zi+0].x2)*(TypeElement[zi+0].x1-TypeElement[zi+0].x2) + (TypeElement[zi+0].y1-TypeElement[zi+0].y2)*(TypeElement[zi+0].y1-TypeElement[zi+0].y2) + (TypeElement[zi+0].z1-TypeElement[zi+0].z2)*(TypeElement[zi+0].z1-TypeElement[zi+0].z2));
						double longueur_deuxieme_rangee=sqrt((TypeElement[zi+1].x1-TypeElement[zi+1].x2)*(TypeElement[zi+1].x1-TypeElement[zi+1].x2) + (TypeElement[zi+1].y1-TypeElement[zi+1].y2)*(TypeElement[zi+1].y1-TypeElement[zi+1].y2) + (TypeElement[zi+1].z1-TypeElement[zi+1].z2)*(TypeElement[zi+1].z1-TypeElement[zi+1].z2));
						double longueur_rangee_haute=sqrt((TypeElement[zi+3].x1-TypeElement[zi+3].x2)*(TypeElement[zi+3].x1-TypeElement[zi+3].x2) + (TypeElement[zi+3].y1-TypeElement[zi+3].y2)*(TypeElement[zi+3].y1-TypeElement[zi+3].y2) + (TypeElement[zi+3].z1-TypeElement[zi+3].z2)*(TypeElement[zi+3].z1-TypeElement[zi+3].z2));


						double volume_imerge1;
						double masse1;
						double trainee_totale1;
						double volume_imerge2;
						double masse2;
						double trainee_totale2;

						volume_imerge1 =(PI*diametre_pehd*diametre_pehd/4*add_cage_nsegment)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux);
						masse1 = PI/4*add_cage_nsegment*rho_pehd*(diametre_pehd*diametre_pehd -(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd))*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
					 	trainee_totale1 = diametre_pehd*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux) * add_cage_nsegment;

						TypeElement[zi+4].diametrehydro=sqrt(volume_imerge1/(PI*hauteur_pieds*add_cage_nsegment/4));
						TypeElement[zi+4].rhoelement=masse1/(hauteur_pieds*PI*TypeElement[zi+4].diametrehydro*TypeElement[zi+4].diametrehydro*add_cage_nsegment/4);

						double trainee_inter = TypeElement[zi+4].diametrehydro*hauteur_pieds*add_cage_nsegment;

						TypeElement[zi+4].cdnormal=coeff_trainee_inter*trainee_totale1/trainee_inter;
						}


					/*if (immersion ==1)
						{
						volume_imerge2 =(PI*diametre_pehd*diametre_pehd/4*add_cage_nsegment)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
						masse2 = PI/4*add_cage_nsegment*rho_pehd*(diametre_pehd*diametre_pehd -(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd))*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute)+PI/4*add_cage_nsegment*RHO*(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
						trainee_totale2 = diametre_pehd*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute) * add_cage_nsegment;
	
						TypeElement[zi+4].diametrehydro=sqrt(volume_imerge2/(PI*hauteur_pieds*add_cage_nsegment/4));
						TypeElement[zi+4].rhoelement=masse2/(hauteur_pieds*PI*TypeElement[zi+4].diametrehydro*TypeElement[zi+4].diametrehydro*add_cage_nsegment/4);

						double trainee_inter = TypeElement[zi+4].diametrehydro*hauteur_pieds*add_cage_nsegment;

						TypeElement[zi+4].cdnormal=coeff_trainee_inter*trainee_totale2/trainee_inter;
						}*/

					TypeElement[zi+6].flag_dessin=0;
					TypeElement[zi+7].flag_dessin=0;

					TypeElement[zi+6].raideur_traction=100000000;
					TypeElement[zi+6].raideur_compression=100000000;
					}

				/*calcul longueur repos*/

				nb_tot_elem += 8*add_cage_nsegment;

				for (zi=nb_ele_depart;zi<=nb_tot_elem;zi++)
					{
					TypeElement[zi].lgrepos=sqrt((TypeElement[zi].x1-TypeElement[zi].x2)*(TypeElement[zi].x1-TypeElement[zi].x2) + (TypeElement[zi].y1-TypeElement[zi].y2)*(TypeElement[zi].y1-TypeElement[zi].y2) + (TypeElement[zi].z1-TypeElement[zi].z2)*(TypeElement[zi].z1-TypeElement[zi].z2));
					}

				elem_inter += 8*add_cage_nsegment;
				nb_ele_depart += 8*add_cage_nsegment;
				nb_elem_cage += 8*add_cage_nsegment;

				}

			/**********************************************************************************************************************/
			/**********************************************************************************************************************/
			/**********************************************************************************************************************/
			/**********************************************************************************************************************/
			if (strcmp(chaine,"add_filet_pred") == 0)
				{
				itmp = fscanf(fic,"%lf",&add_filet_pred_diam);
				itmp = fscanf(fic,"%lf",&add_diam_lest);				
				itmp = fscanf(fic,"%lf",&add_filet_pred_xxo);
				itmp = fscanf(fic,"%lf",&add_filet_pred_yyo);
				itmp = fscanf(fic,"%d",&add_filet_pred_nsegment);
				itmp = fscanf(fic,"%lf",&add_cage_dist_ann);
				itmp = fscanf(fic,"%lf",&add_hauteur_filet_pred);
				itmp = fscanf(fic,"%lf",&add_taille_maille_pred);
				itmp = fscanf(fic,"%lf",&diametre_pehd);
				itmp = fscanf(fic,"%lf",&epaisseur_pehd);
				itmp = fscanf(fic,"%lf",&rho_pehd);

				printf("nb_tot_elem = %d\n",nb_tot_elem);

				double pronf_niveau_bas = 0;		/* profondeur des barres du niveau bas (sous phobos)*/
				

				/* 		ELEMENT 	*/

				ele_inter_pred = nb_tot_elem +1;


				double longueur_contour_filet_pred;
				double volume_contour_pred;
				double masse_contour_pred;


				for (zi=ele_inter_pred;zi<=ele_inter_pred+4*add_filet_pred_nsegment-1;zi=zi+4)
					{
					int fl = floor((zi-ele_inter_pred)/4);

					xxp11 = (float) add_filet_pred_xxo - add_diam_lest/2*cos(2*PI*fl/add_filet_pred_nsegment);
					yyp11 = (float) add_filet_pred_yyo - add_diam_lest/2*sin(2*PI*fl/add_filet_pred_nsegment);
					xxp12 = (float) add_filet_pred_xxo - add_diam_lest/2*cos(2*PI*(fl+1)/add_filet_pred_nsegment);
					yyp12 = (float) add_filet_pred_yyo - add_diam_lest/2*sin(2*PI*(fl+1)/add_filet_pred_nsegment);
					
					xxp21 = xxp11;
					yyp21 = yyp11;
					xxp22 = (float) add_filet_pred_xxo - add_diam_lest/2*cos(2*PI*(fl+2)/add_filet_pred_nsegment);
					yyp22 = (float) add_filet_pred_yyo - add_diam_lest/2*sin(2*PI*(fl+2)/add_filet_pred_nsegment);
					
					xxp31 = xxp11;
					yyp31 = yyp11;
					xxp32 = add_filet_pred_xxo - add_filet_pred_diam/2*cos(2*PI*fl/add_filet_pred_nsegment);
					yyp32 = add_filet_pred_yyo - add_filet_pred_diam/2*sin(2*PI*fl/add_filet_pred_nsegment);

					xxp41 = xxp11;
					yyp41 = yyp11;
					xxp42 = (float) (add_filet_pred_xxo - ((add_diam_lest)/2-add_cage_dist_ann-(add_diam_lest/2-add_filet_pred_diam/2)) * cos(2 * PI*fl/add_filet_pred_nsegment));
					yyp42 = (float) (add_filet_pred_yyo - ((add_diam_lest)/2-add_cage_dist_ann-(add_diam_lest/2-add_filet_pred_diam/2)) * sin(2 * PI*fl/add_filet_pred_nsegment));


					TypeElement[zi+0].x1 = xxp11;
					TypeElement[zi+0].y1 = yyp11;
					TypeElement[zi+0].z1 = - add_hauteur_filet_pred + pronf_niveau_bas;

					TypeElement[zi+0].x2 = xxp12;
					TypeElement[zi+0].y2 = yyp12;
					TypeElement[zi+0].z2 = - add_hauteur_filet_pred + pronf_niveau_bas;

					/* calcul masse volumique */
					longueur_contour_filet_pred=sqrt((TypeElement[zi+0].x1-TypeElement[zi+0].x2)*(TypeElement[zi+0].x1-TypeElement[zi+0].x2) + (TypeElement[zi+0].y1-TypeElement[zi+0].y2)*(TypeElement[zi+0].y1-TypeElement[zi+0].y2) + (TypeElement[zi+0].z1-TypeElement[zi+0].z2)*(TypeElement[zi+0].z1-TypeElement[zi+0].z2));
					volume_contour_pred = (PI*diametre_pehd*diametre_pehd/4*add_filet_pred_nsegment)*longueur_contour_filet_pred;
					
					/*masse avec chaine de 20 kg par metre de lest*/
					masse_contour_pred = PI/4*add_filet_pred_nsegment*rho_pehd*(diametre_pehd*diametre_pehd -(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd))*longueur_contour_filet_pred +PI/4*add_filet_pred_nsegment*RHO*(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd)*longueur_contour_filet_pred + 20*longueur_contour_filet_pred*add_filet_pred_nsegment ;


					TypeElement[zi+0].rhoelement=masse_contour_pred/volume_contour_pred;
					TypeElement[zi+0].diametrehydro = diametre_pehd;
					TypeElement[zi+0].raideur_compression = 5000000;
					TypeElement[zi+0].raideur_traction = 5000000;

					TypeElement[zi+1].x1 = xxp21;
					TypeElement[zi+1].y1 = yyp21;
					TypeElement[zi+1].z1 = - add_hauteur_filet_pred + pronf_niveau_bas;

					TypeElement[zi+1].x2 = xxp22;
					TypeElement[zi+1].y2 = yyp22;
					TypeElement[zi+1].z2 = - add_hauteur_filet_pred + pronf_niveau_bas;

					TypeElement[zi+2].x1 = xxp31;
					TypeElement[zi+2].y1 = yyp31;
					TypeElement[zi+2].z1 = - add_hauteur_filet_pred + pronf_niveau_bas;

					TypeElement[zi+2].x2 = xxp32;
					TypeElement[zi+2].y2 = yyp32;
					TypeElement[zi+2].z2 = pronf_niveau_bas;

					TypeElement[zi+2].raideur_compression = 10;
					TypeElement[zi+2].raideur_traction = 3923000;
					TypeElement[zi+2].rhoelement=955;
					TypeElement[zi+2].diametrehydro=0.044;

					TypeElement[zi+3].x1=xxp41;
					TypeElement[zi+3].y1=yyp41;
					TypeElement[zi+3].x2=xxp42;
					TypeElement[zi+3].y2=yyp42;
					TypeElement[zi+3].z1 = - add_hauteur_filet_pred + pronf_niveau_bas;
					TypeElement[zi+3].z2 = - add_hauteur_filet_elev + pronf_niveau_bas;

					TypeElement[zi+3].raideur_compression = 10;
					TypeElement[zi+3].raideur_traction = 3923000;
					TypeElement[zi+3].rhoelement=955;
					TypeElement[zi+3].diametrehydro=0.044;

					}


				for (zi=ele_inter_pred;zi<=ele_inter_pred+4*add_filet_pred_nsegment;zi++)
					{
					TypeElement[zi].lgrepos=sqrt((TypeElement[zi].x1-TypeElement[zi].x2)*(TypeElement[zi].x1-TypeElement[zi].x2) + (TypeElement[zi].y1-TypeElement[zi].y2)*(TypeElement[zi].y1-TypeElement[zi].y2) + (TypeElement[zi].z1-TypeElement[zi].z2)*(TypeElement[zi].z1-TypeElement[zi].z2));
					}

				for (zi=ele_inter_pred;zi<=ele_inter_pred+4*add_filet_pred_nsegment;zi=zi+4)
					{
					TypeElement[zi+3].lgrepos=0.95*sqrt((TypeElement[zi].x1-TypeElement[zi].x2)*(TypeElement[zi].x1-TypeElement[zi].x2) + (TypeElement[zi].y1-TypeElement[zi].y2)*(TypeElement[zi].y1-TypeElement[zi].y2) + (TypeElement[zi].z1-TypeElement[zi].z2)*(TypeElement[zi].z1-TypeElement[zi].z2));
					}

				nb_tot_elem += 4*add_filet_pred_nsegment;
				nb_elem_cage += 4*add_filet_pred_nsegment;

			}


			/**********************************************************************************************************************/
			/********************************************MODIF ARNAUD 29/10/09 ******************************/
				if (strcmp(chaine,"ligne_tot") == 0)
				{
					char test;
					double noeud_coord_x;
					double noeud_coord_y;
					double noeud_coord_z;
					int noeud_type_type;
					double lglg;

					long position_init;

					position_init = ftell(fic);

					itmp = fscanf(fic,"%lf %lf %lf %d", &noeud_coord_x, &noeud_coord_y, &noeud_coord_z, &noeud_type_type);


					int iii=1;

					itmp = fscanf(fic,"%c",&test);
					fseek(fic, -1, SEEK_CUR);

					while (test!='\n')
					{
						itmp = fscanf(fic, "%lf %lf %lf %lf %d", &lglg, &noeud_coord_x, &noeud_coord_y, &noeud_coord_z, &noeud_type_type);
						itmp = fscanf(fic,"%c",&test);
						fseek(fic, -1, SEEK_CUR);
						iii=iii+1;
					}

	
					coord_noeud_x = (double *) realloc(coord_noeud_x, (iii) * sizeof(double));

					coord_noeud_y = (double *) realloc(coord_noeud_y, (iii) * sizeof(double));

					coord_noeud_z = (double *) realloc(coord_noeud_z, (iii) * sizeof(double));

					type_type_noeud = (int *) realloc(type_type_noeud, (iii) * sizeof(int));

					lg_lg = (double *) realloc(lg_lg, (iii-1) * sizeof(double));



					fseek(fic, position_init, SEEK_SET);

					itmp = fscanf(fic,"%lf %lf %lf %d", &noeud_coord_x, &noeud_coord_y, &noeud_coord_z, &noeud_type_type);

					coord_noeud_x[0]=noeud_coord_x;
					coord_noeud_y[0]=noeud_coord_y;
					coord_noeud_z[0]=noeud_coord_z;
					type_type_noeud[0]=noeud_type_type;

					int jjj;
					int kkk;

					for (jjj=1;jjj<=(iii-1);jjj++)
					{
						itmp = fscanf (fic, "%lf", &lglg);
						itmp = fscanf (fic, "%lf", &noeud_coord_x);
						itmp = fscanf (fic, "%lf", &noeud_coord_y);
						itmp = fscanf (fic, "%lf", &noeud_coord_z);
						itmp = fscanf (fic, "%d", &noeud_type_type);
						lg_lg[jjj-1]=lglg;
						coord_noeud_x[jjj]=noeud_coord_x;
						coord_noeud_y[jjj]=noeud_coord_y;						
						coord_noeud_z[jjj]=noeud_coord_z;
						type_type_noeud[jjj]=noeud_type_type;
					}

					int elem_amarrage=nb_tot_elem+1;
				
					for (jjj=elem_amarrage;jjj<=elem_amarrage+iii-2;jjj++)
					{
						TypeElement[jjj].x1=coord_noeud_x[jjj-elem_amarrage];
						TypeElement[jjj].x2=coord_noeud_x[jjj-elem_amarrage+1];
						TypeElement[jjj].y1=coord_noeud_y[jjj-elem_amarrage];
						TypeElement[jjj].y2=coord_noeud_y[jjj-elem_amarrage+1];

						kkk=0;
						
						while(coord_noeud_x[jjj-elem_amarrage-kkk-1]==coord_noeud_x[jjj-elem_amarrage] && coord_noeud_y[jjj-elem_amarrage-kkk-1]==coord_noeud_y[jjj-elem_amarrage] && (jjj-elem_amarrage-kkk) > 0)
						{
							kkk=kkk+1;
						}

						if (coord_noeud_x[jjj-elem_amarrage]==coord_noeud_x[jjj-elem_amarrage+1] && coord_noeud_y[jjj-elem_amarrage]==coord_noeud_y[jjj-elem_amarrage+1] && jjj-elem_amarrage-1 > 0)
						{
							deb = TypeElement[jjj].extremite[1];
							fin = TypeElement[jjj].extremite[2];

							TypeElement[jjj].z1=coord_noeud_z[jjj-elem_amarrage];
							TypeElement[jjj].z2=coord_noeud_z[jjj-elem_amarrage+1];
							
							Noeud[deb].type=type_type_noeud[jjj-elem_amarrage];
							Noeud[fin].type=type_type_noeud[jjj-elem_amarrage+1];						
						}
						else
						{

							deb = TypeElement[jjj].extremite[1];
							fin = TypeElement[jjj].extremite[2];

							TypeElement[jjj].z1=coord_noeud_z[jjj-elem_amarrage-kkk];
							TypeElement[jjj].z2=coord_noeud_z[jjj-elem_amarrage+1];

							Noeud[deb].type=type_type_noeud[jjj-elem_amarrage-kkk];
							Noeud[fin].type=type_type_noeud[jjj-elem_amarrage+1];
						}
						TypeElement[jjj].lgrepos=lg_lg[jjj-elem_amarrage];
					}
					/***************************************MODIF ARNAUD****************************************************/

					nb_tot_elem += iii-1;
				}

				/**********************************************************************************************************************/
				/**********************************************************************************************************************/
				/***************************************MODIF ARNAUD****************************************************/

				/**********************************************************************************************************************/
				/********************************************MODIF ARNAUD 27/11/09 ******************************/
				if (strcmp(chaine,"ligne_ordre") == 0)
				{
					char test;
					double noeud_coord_x;
					double noeud_coord_y;
					double noeud_coord_z;
					int noeud_type_type;
					double lglg;

					long position_init;

					position_init = ftell(fic);
					itmp = fscanf(fic,"%c",&test);
					fseek(fic, -1, SEEK_CUR);

					int iii=0;

					while (test!='\n')
					{
					itmp = fscanf(fic,"%lf", &noeud_coord_x);
					itmp = fscanf(fic,"%c",&test);
					fseek(fic, -1, SEEK_CUR);
					iii=iii+1;
					}

					iii=iii+1;
					iii=iii/5;
	
					coord_noeud_x = (double *) realloc(coord_noeud_x, (iii) * sizeof(double));

					coord_noeud_y = (double *) realloc(coord_noeud_y, (iii) * sizeof(double));

					coord_noeud_z = (double *) realloc(coord_noeud_z, (iii) * sizeof(double));

					type_type_noeud = (int *) realloc(type_type_noeud, (iii) * sizeof(int));

					lg_lg = (double *) realloc(lg_lg, (iii-1) * sizeof(double));



					fseek(fic, position_init, SEEK_SET);

					int jjj;
					int kkk;

					for (jjj=1;jjj<=iii;jjj++)
					{
						itmp = fscanf (fic, "%lf", &noeud_coord_x);
						coord_noeud_x[jjj-1]=noeud_coord_x;
					}

					for (jjj=1;jjj<=iii;jjj++)
					{
						itmp = fscanf (fic, "%lf", &noeud_coord_y);
						coord_noeud_y[jjj-1]=noeud_coord_y;
					}

					for (jjj=1;jjj<=iii;jjj++)
					{
						itmp = fscanf (fic, "%lf", &noeud_coord_z);
						coord_noeud_z[jjj-1]=noeud_coord_z;
					}

					for (jjj=1;jjj<=iii;jjj++)
					{
						itmp = fscanf (fic, "%d", &noeud_type_type);
						type_type_noeud[jjj-1]=noeud_type_type;
					}

					for (jjj=1;jjj<=iii-1;jjj++)
					{
						itmp = fscanf (fic, "%lf", &lglg);
						lg_lg[jjj-1]=lglg;
					}

					int elem_amarrage=nb_tot_elem+1;

				
					for (jjj=elem_amarrage;jjj<=elem_amarrage+iii-2;jjj++)
					{
						TypeElement[jjj].x1=coord_noeud_x[jjj-elem_amarrage];
						TypeElement[jjj].x2=coord_noeud_x[jjj-elem_amarrage+1];
						TypeElement[jjj].y1=coord_noeud_y[jjj-elem_amarrage];
						TypeElement[jjj].y2=coord_noeud_y[jjj-elem_amarrage+1];

						kkk=0;
						
						while(coord_noeud_x[jjj-elem_amarrage-kkk-1]==coord_noeud_x[jjj-elem_amarrage] && coord_noeud_y[jjj-elem_amarrage-kkk-1]==coord_noeud_y[jjj-elem_amarrage] && (jjj-elem_amarrage-kkk) > 0)
						{
							kkk=kkk+1;
						}

						if (coord_noeud_x[jjj-elem_amarrage]==coord_noeud_x[jjj-elem_amarrage+1] && coord_noeud_y[jjj-elem_amarrage]==coord_noeud_y[jjj-elem_amarrage+1] && jjj-elem_amarrage-1 > 0)
						{
							deb = TypeElement[jjj].extremite[1];
							fin = TypeElement[jjj].extremite[2];

							TypeElement[jjj].z1=coord_noeud_z[jjj-elem_amarrage];
							TypeElement[jjj].z2=coord_noeud_z[jjj-elem_amarrage+1];
							
							Noeud[deb].type=type_type_noeud[jjj-elem_amarrage];
							Noeud[fin].type=type_type_noeud[jjj-elem_amarrage+1];						
						}
						else
						{

							deb = TypeElement[jjj].extremite[1];
							fin = TypeElement[jjj].extremite[2];

							TypeElement[jjj].z1=coord_noeud_z[jjj-elem_amarrage-kkk];
							TypeElement[jjj].z2=coord_noeud_z[jjj-elem_amarrage+1];

							Noeud[deb].type=type_type_noeud[jjj-elem_amarrage-kkk];
							Noeud[fin].type=type_type_noeud[jjj-elem_amarrage+1];
						}
						TypeElement[jjj].lgrepos=lg_lg[jjj-elem_amarrage];
					}
					/***************************************MODIF ARNAUD****************************************************/

					nb_tot_elem += iii-1;
				}


				/**********************************************************************************************************************/
				/**********************************************************************************************************************/
				/***************************************MODIF ARNAUD****************************************************/



				/***************************************MODIF ARNAUD - 08/10/09 *********************************/

				if (strcmp(chaine,"accroche") == 0)
				{
					itmp = fscanf(fic,"%lf",&add_filet_pred_diam);
					itmp = fscanf(fic,"%lf",&add_filet_pred_xxo);
					itmp = fscanf(fic,"%lf",&add_filet_pred_yyo);
					itmp = fscanf(fic,"%d",&add_filet_pred_nsegment);

					int type_accroche=0;
					int iii=0;
					int jjj=0;
					
					int elem_accroche;

					double pronf_niveau_bas=0;
					double xxo;
					double yyo;

					for (iii=1;iii<=4;iii++)
					{
						itmp = fscanf(fic,"%d",&type_accroche);
						
						elem_accroche = nb_tot_elem+1;
					
						if (type_accroche==1)
						{							
							itmp = fscanf(fic,"%f %f %f %f %f %d %d", &xxx, &yyy, &zzz, &pourc_lg_masse1, &z_masse1, &type_masse1, &pan_choisi1);

							TypeElement[elem_accroche].x1=xxx;
							TypeElement[elem_accroche].x2=xxx-(xxx-(add_filet_pred_xxo-add_filet_pred_diam/2*cos(2*PI*pan_choisi1/add_filet_pred_nsegment)))*pourc_lg_masse1;
							TypeElement[elem_accroche].y1=yyy;
							TypeElement[elem_accroche].y2=yyy-(yyy-(add_filet_pred_yyo+add_filet_pred_diam/2*sin(2*PI*pan_choisi1/add_filet_pred_nsegment)))*pourc_lg_masse1;
							TypeElement[elem_accroche].z1=zzz;
							TypeElement[elem_accroche].z2=z_masse1;

							TypeElement[elem_accroche+1].x1=TypeElement[elem_accroche].x2;
							TypeElement[elem_accroche+1].x2=TypeElement[elem_accroche].x2;
							TypeElement[elem_accroche+1].y1=TypeElement[elem_accroche].y2;
							TypeElement[elem_accroche+1].y2=TypeElement[elem_accroche].y2;
							TypeElement[elem_accroche+1].z1=z_masse1;
							TypeElement[elem_accroche+1].z2=z_masse1-1;
							fin=TypeElement[elem_accroche+1].extremite[2];
							Noeud[fin].type=type_masse1;

							TypeElement[elem_accroche+2].x1=TypeElement[elem_accroche].x2;
							TypeElement[elem_accroche+2].x2= add_filet_pred_xxo-add_filet_pred_diam/2*cos(2*PI*pan_choisi1/add_filet_pred_nsegment);
							TypeElement[elem_accroche+2].y1=TypeElement[elem_accroche].y2;
							TypeElement[elem_accroche+2].y2= add_filet_pred_yyo+add_filet_pred_diam/2*sin(2*PI*pan_choisi1/add_filet_pred_nsegment);
							TypeElement[elem_accroche+2].z1=z_masse1;
							TypeElement[elem_accroche+2].z2=pronf_niveau_bas;
							

							for (jjj=elem_accroche;jjj<=elem_accroche+2;jjj++)
							{
								TypeElement[jjj].lgrepos=sqrt((TypeElement[jjj].x1-TypeElement[jjj].x2)*(TypeElement[jjj].x1-TypeElement[jjj].x2) + (TypeElement[jjj].y1-TypeElement[jjj].y2)*(TypeElement[jjj].y1-TypeElement[jjj].y2) + (TypeElement[jjj].z1-TypeElement[jjj].z2)*(TypeElement[jjj].z1-TypeElement[jjj].z2));
							}
							nb_tot_elem += 3;	
						}
						
						else if (type_accroche==2)
						{
							itmp = fscanf(fic,"%f %f %f %f %f %d %d %f %f %d %d", &xxx, &yyy, &zzz, &pourc_lg_masse1, &z_masse1, &type_masse1, &pan_choisi1, &pourc_lg_masse2, &z_masse2, &type_masse2, &pan_choisi2);

							TypeElement[elem_accroche].x1=xxx;
							TypeElement[elem_accroche].x2=xxx-(xxx-(add_filet_pred_xxo-add_filet_pred_diam/2*cos(2*PI*pan_choisi1/add_filet_pred_nsegment)))*pourc_lg_masse1;
							TypeElement[elem_accroche].y1=yyy;
							TypeElement[elem_accroche].y2=yyy-(yyy-(add_filet_pred_yyo+add_filet_pred_diam/2*sin(2*PI*pan_choisi1/add_filet_pred_nsegment)))*pourc_lg_masse1;
							TypeElement[elem_accroche].z1=zzz;
							TypeElement[elem_accroche].z2=z_masse1;

							TypeElement[elem_accroche+1].x1=TypeElement[elem_accroche].x2;
							TypeElement[elem_accroche+1].x2=TypeElement[elem_accroche].x2;
							TypeElement[elem_accroche+1].y1=TypeElement[elem_accroche].y2;
							TypeElement[elem_accroche+1].y2=TypeElement[elem_accroche].y2;
							TypeElement[elem_accroche+1].z1=z_masse1;
							TypeElement[elem_accroche+1].z2=z_masse1-1;
							fin=TypeElement[elem_accroche+1].extremite[2];
							Noeud[fin].type=type_masse1;

							TypeElement[elem_accroche+2].x1=TypeElement[elem_accroche].x2;
							TypeElement[elem_accroche+2].x2= add_filet_pred_xxo-add_filet_pred_diam/2*cos(2*PI*pan_choisi1/add_filet_pred_nsegment);
							TypeElement[elem_accroche+2].y1=TypeElement[elem_accroche].y2;
							TypeElement[elem_accroche+2].y2= add_filet_pred_yyo+add_filet_pred_diam/2*sin(2*PI*pan_choisi1/add_filet_pred_nsegment);
							TypeElement[elem_accroche+2].z1=z_masse1;
							TypeElement[elem_accroche+2].z2=pronf_niveau_bas;


							TypeElement[elem_accroche+3].x1=xxx;
							TypeElement[elem_accroche+3].x2=xxx-(xxx-(add_filet_pred_xxo-add_filet_pred_diam/2*cos(2*PI*pan_choisi2/add_filet_pred_nsegment)))*pourc_lg_masse2;
							TypeElement[elem_accroche+3].y1=yyy;
							TypeElement[elem_accroche+3].y2=yyy-(yyy-(add_filet_pred_yyo+add_filet_pred_diam/2*sin(2*PI*pan_choisi2/add_filet_pred_nsegment)))*pourc_lg_masse2;
							TypeElement[elem_accroche+3].z1=zzz;
							TypeElement[elem_accroche+3].z2=z_masse2;

							TypeElement[elem_accroche+4].x1=TypeElement[elem_accroche+3].x2;
							TypeElement[elem_accroche+4].x2=TypeElement[elem_accroche+3].x2;
							TypeElement[elem_accroche+4].y1=TypeElement[elem_accroche+3].y2;
							TypeElement[elem_accroche+4].y2=TypeElement[elem_accroche+3].y2;
							TypeElement[elem_accroche+4].z1=z_masse2;
							TypeElement[elem_accroche+4].z2=z_masse2-1;
							fin=TypeElement[elem_accroche+4].extremite[2];
							Noeud[fin].type=type_masse2;

							TypeElement[elem_accroche+5].x1=TypeElement[elem_accroche+3].x2;
							TypeElement[elem_accroche+5].x2= add_filet_pred_xxo-add_filet_pred_diam/2*cos(2*PI*pan_choisi2/add_filet_pred_nsegment);
							TypeElement[elem_accroche+5].y1=TypeElement[elem_accroche+3].y2;
							TypeElement[elem_accroche+5].y2= add_filet_pred_yyo+add_filet_pred_diam/2*sin(2*PI*pan_choisi2/add_filet_pred_nsegment);
							TypeElement[elem_accroche+5].z1=z_masse2;
							TypeElement[elem_accroche+5].z2=pronf_niveau_bas;
							

							for (jjj=elem_accroche;jjj<=elem_accroche+5;jjj++)
							{
								TypeElement[jjj].lgrepos=sqrt((TypeElement[jjj].x1-TypeElement[jjj].x2)*(TypeElement[jjj].x1-TypeElement[jjj].x2) + (TypeElement[jjj].y1-TypeElement[jjj].y2)*(TypeElement[jjj].y1-TypeElement[jjj].y2) + (TypeElement[jjj].z1-TypeElement[jjj].z2)*(TypeElement[jjj].z1-TypeElement[jjj].z2));
							}
							nb_tot_elem += 6;
						}
								
		
						else if (type_accroche==3)
						{
							itmp = fscanf(fic,"%f %f %f %f %f %d %f %f %d %d", &xxx, &yyy, &zzz, &pourc_lg_masse1, &z_masse1, &type_masse1, &pourc_lg_pate, &z_pate, &pan_choisi1, &pan_choisi2);


							xxo=(add_filet_pred_xxo-xxx);
							yyo=(add_filet_pred_yyo-yyy);

							TypeElement[elem_accroche].x1=xxx;
							TypeElement[elem_accroche].x2=xxx+xxo*(1-add_filet_pred_diam/(2*sqrt(xxo*xxo+yyo*yyo)))*pourc_lg_masse1;
							TypeElement[elem_accroche].y1=yyy;
							TypeElement[elem_accroche].y2=yyy+yyo*(1-add_filet_pred_diam/(2*sqrt(xxo*xxo+yyo*yyo)))*pourc_lg_masse1;
							TypeElement[elem_accroche].z1=zzz;
							TypeElement[elem_accroche].z2=z_masse1;

							TypeElement[elem_accroche+1].x1=TypeElement[elem_accroche].x2;
							TypeElement[elem_accroche+1].x2=TypeElement[elem_accroche].x2;
							TypeElement[elem_accroche+1].y1=TypeElement[elem_accroche].y2;
							TypeElement[elem_accroche+1].y2=TypeElement[elem_accroche].y2;
							TypeElement[elem_accroche+1].z1=z_masse1;
							TypeElement[elem_accroche+1].z2=z_masse1-1;
							fin=TypeElement[elem_accroche+1].extremite[2];
							Noeud[fin].type=type_masse1;


							TypeElement[elem_accroche+2].x1=TypeElement[elem_accroche].x2;
							TypeElement[elem_accroche+2].x2=xxx+xxo*(1-add_filet_pred_diam/(2*sqrt(xxo*xxo+yyo*yyo)))*pourc_lg_pate;
							TypeElement[elem_accroche+2].y1=TypeElement[elem_accroche].y2;
							TypeElement[elem_accroche+2].y2=yyy+yyo*(1-add_filet_pred_diam/(2*sqrt(xxo*xxo+yyo*yyo)))*pourc_lg_pate;
							TypeElement[elem_accroche+2].z1=z_masse1;
							TypeElement[elem_accroche+2].z2=z_pate;


							TypeElement[elem_accroche+3].x1=TypeElement[elem_accroche+2].x2;
							TypeElement[elem_accroche+3].x2= add_filet_pred_xxo-add_filet_pred_diam/2*cos(2*PI*pan_choisi1/add_filet_pred_nsegment);
							TypeElement[elem_accroche+3].y1=TypeElement[elem_accroche+2].y2;
							TypeElement[elem_accroche+3].y2= add_filet_pred_yyo+add_filet_pred_diam/2*sin(2*PI*pan_choisi1/add_filet_pred_nsegment);
							TypeElement[elem_accroche+3].z1=z_pate;
							TypeElement[elem_accroche+3].z2=pronf_niveau_bas;


							TypeElement[elem_accroche+4].x1=TypeElement[elem_accroche+2].x2;
							TypeElement[elem_accroche+4].x2= add_filet_pred_xxo-add_filet_pred_diam/2*cos(2*PI*pan_choisi2/add_filet_pred_nsegment);
							TypeElement[elem_accroche+4].y1=TypeElement[elem_accroche+2].y2;
							TypeElement[elem_accroche+4].y2= add_filet_pred_yyo+add_filet_pred_diam/2*sin(2*PI*pan_choisi2/add_filet_pred_nsegment);
							TypeElement[elem_accroche+4].z1=z_pate;
							TypeElement[elem_accroche+4].z2=pronf_niveau_bas;
							

							for (jjj=elem_accroche;jjj<=elem_accroche+4;jjj++)
							{
								TypeElement[jjj].lgrepos=sqrt((TypeElement[jjj].x1-TypeElement[jjj].x2)*(TypeElement[jjj].x1-TypeElement[jjj].x2) + (TypeElement[jjj].y1-TypeElement[jjj].y2)*(TypeElement[jjj].y1-TypeElement[jjj].y2) + (TypeElement[jjj].z1-TypeElement[jjj].z2)*(TypeElement[jjj].z1-TypeElement[jjj].z2));
							}
							nb_tot_elem += 5;
						}
					}
				}



			/******************************************************MODIF****************************************************************/
			/***************************************MODIF ARNAUD - 23/11/09 *********************************/

			if (strcmp(chaine,"materiau_elem") == 0)
			{
				itmp = fscanf(fic,"%d",&num_elem_choisi);
				itmp = fscanf(fic,"%lf",&raideur_traction_choisie);
				itmp = fscanf(fic,"%lf",&raideur_compression_choisie);
				itmp = fscanf(fic,"%lf",&masse_volumique_choisie);
				itmp = fscanf(fic,"%lf",&diam_hydro_choisi);
				itmp = fscanf(fic,"%lf",&coeff_trainee_normal_choisi);
				itmp = fscanf(fic,"%lf",&coeff_trainee_tangent_choisi);

				modif_materiau_elem(num_elem_choisi, raideur_traction_choisie, raideur_compression_choisie, masse_volumique_choisie, diam_hydro_choisi, coeff_trainee_normal_choisi, coeff_trainee_tangent_choisi);
			}


			/*******************************************MODIF***************************************************************************/


			/***************************************MODIF ARNAUD - 06/01/10 *********************************/


			int nb_barre_choisi;
			int tp_noeud;

			if (strcmp(chaine,"carac_barre_noeud") == 0)
			{
				itmp = fscanf(fic,"%d",&tp_noeud);
				itmp = fscanf(fic,"%d",&nb_barre_choisi);
				itmp = fscanf(fic,"%lf",&raideur_traction_choisie);
				itmp = fscanf(fic,"%lf",&raideur_compression_choisie);
				itmp = fscanf(fic,"%lf",&masse_volumique_choisie);
				itmp = fscanf(fic,"%lf",&diam_hydro_choisi);
				itmp = fscanf(fic,"%lf",&coeff_trainee_normal_choisi);
				itmp = fscanf(fic,"%lf",&coeff_trainee_tangent_choisi);

				for (i=1;i<=NOMBRE_ELEMENTS;i++)
				{
					deb=Element[i].extremite[1];
					fin=Element[i].extremite[2];

					if (Noeud[deb].type == tp_noeud || Noeud[fin].type == tp_noeud)
					{
						modif_materiau_elem(Element[i].type, raideur_traction_choisie, raideur_compression_choisie, masse_volumique_choisie, diam_hydro_choisi, coeff_trainee_normal_choisi, coeff_trainee_tangent_choisi);
					}
				}		

			}



			/******************************************************MODIF****************************************************************/




			}
		}




	fclose(fic);
	
  	for (i=1;i<=NOMBRE_NOEUDS;i++)
  		{
    		Noeud[i].mx   = TypeNoeud[Noeud[i].type].mx;   /* Masse du noeud i */
    		Noeud[i].my   = TypeNoeud[Noeud[i].type].my;
    		Noeud[i].mz   = TypeNoeud[Noeud[i].type].mz;
    		Noeud[i].majx = TypeNoeud[Noeud[i].type].majx; /* Masse ajoutee du noeud i : n'intervient qu'en dynamique*/
    		Noeud[i].majy = TypeNoeud[Noeud[i].type].majy;
    		Noeud[i].majz = TypeNoeud[Noeud[i].type].majz;
    		Noeud[i].sx   = TypeNoeud[Noeud[i].type].sx;   /* Longueur selon x du noeud i */
    		Noeud[i].sy   = TypeNoeud[Noeud[i].type].sy;
    		Noeud[i].sz   = TypeNoeud[Noeud[i].type].sz;
    		Noeud[i].cdx  = TypeNoeud[Noeud[i].type].cdx;  /* Coefficient de trainee selon x du noeud i */
    		Noeud[i].cdy  = TypeNoeud[Noeud[i].type].cdy;
    		Noeud[i].cdz  = TypeNoeud[Noeud[i].type].cdz;
    		Noeud[i].fx   = TypeNoeud[Noeud[i].type].fx;   /* Effort exterieur selon x du noeud i */
    		Noeud[i].fy   = TypeNoeud[Noeud[i].type].fy;
    		Noeud[i].fz   = TypeNoeud[Noeud[i].type].fz;
    		Noeud[i].fixx = TypeNoeud[Noeud[i].type].fixx; /* Deplacement selon x du noeud i : Fixe ou Libre */
    		Noeud[i].fixy = TypeNoeud[Noeud[i].type].fixy;
    		Noeud[i].fixz = TypeNoeud[Noeud[i].type].fixz;
    		Noeud[i].limx = TypeNoeud[Noeud[i].type].limx; /* Limite du deplacement selon x du noeud i  */
    		Noeud[i].limy = TypeNoeud[Noeud[i].type].limy;
    		Noeud[i].limz = TypeNoeud[Noeud[i].type].limz;
    		Noeud[i].fmx  = TypeNoeud[Noeud[i].type].fmx;  /*Sens de la Limite du deplacement selon x du noeud i */
    		Noeud[i].fmy  = TypeNoeud[Noeud[i].type].fmy;
    		Noeud[i].fmz  = TypeNoeud[Noeud[i].type].fmz;
    		Noeud[i].symx = TypeNoeud[Noeud[i].type].symx; /* =1 si Le noeud i appartient au plan de symetrie YOZ, 0 sinon*/
    		Noeud[i].symy = TypeNoeud[Noeud[i].type].symy; /* =1 si Le noeud i appartient au plan de symetrie XOZ, 0 sinon*/
    		Noeud[i].symz = TypeNoeud[Noeud[i].type].symz; /* =1 si Le noeud i appartient au plan de symetrie XOY, 0 sinon*/
  		}

  	for (i=1;i<=NOMBRE_ELEMENTS;i++)
  		{ 
    		Element[i].raideur_traction    = TypeElement[Element[i].type].raideur_traction;
    		/*Element[i].lgrepos             = TypeElement[Element[i].type].lgrepos;*/
    		Element[i].diametremeca        = TypeElement[Element[i].type].diametremeca;
    		Element[i].raideur_compression = TypeElement[Element[i].type].raideur_compression;
    		Element[i].rhoelement          = TypeElement[Element[i].type].rhoelement;
    		Element[i].diametrehydro       = TypeElement[Element[i].type].diametrehydro;
    		Element[i].cdnormal            = TypeElement[Element[i].type].cdnormal;
    		Element[i].ftangent            = TypeElement[Element[i].type].ftangent;
  		}

  	for (i=1;i<=NOMBRE_SURFACES;i++)
  		{ 
    		Surface[i].raideur_traction    = panneau[Surface[i].type].raideur_traction;
    		Surface[i].lgrepos             = panneau[Surface[i].type].longueur_repos;
    		Surface[i].diametremeca        = panneau[Surface[i].type].diametremeca;
    		Surface[i].raideur_compression = panneau[Surface[i].type].raideur_compression;
    		Surface[i].raideur_ouverture   = panneau[Surface[i].type].raideur_ouverture;
    		Surface[i].rhosurface          = panneau[Surface[i].type].rho;
    		Surface[i].diametrehydro       = panneau[Surface[i].type].diam_hydro;
    		Surface[i].largeurnoeud        = panneau[Surface[i].type].largeurnoeud;
    		Surface[i].cdnormal            = panneau[Surface[i].type].cdnormal;
    		Surface[i].ftangent            = panneau[Surface[i].type].ftangent;
    		Surface[i].tarp		       = panneau[Surface[i].type].tarp;
  		}
  
  	for (i=1;i<=NOMBRE_SURF_HEXA;i++)
  		{ 
    		Surf_Hexa[i].raideur_traction_l    = TypeSurfHexa[Surf_Hexa[i].type].raideur_traction_l;
    		Surf_Hexa[i].raideur_traction_m    = TypeSurfHexa[Surf_Hexa[i].type].raideur_traction_m;
    		Surf_Hexa[i].raideur_traction_n    = TypeSurfHexa[Surf_Hexa[i].type].raideur_traction_n;
    		Surf_Hexa[i].lo_repos            = TypeSurfHexa[Surf_Hexa[i].type].lo_repos;
    		Surf_Hexa[i].mo_repos            = TypeSurfHexa[Surf_Hexa[i].type].mo_repos;
    		Surf_Hexa[i].no_repos            = TypeSurfHexa[Surf_Hexa[i].type].no_repos;
    		Surf_Hexa[i].diametremeca        = TypeSurfHexa[Surf_Hexa[i].type].diametremeca;
    		Surf_Hexa[i].raideur_compression_l = TypeSurfHexa[Surf_Hexa[i].type].raideur_compression_l;
    		Surf_Hexa[i].raideur_compression_m = TypeSurfHexa[Surf_Hexa[i].type].raideur_compression_m;
    		Surf_Hexa[i].raideur_compression_n = TypeSurfHexa[Surf_Hexa[i].type].raideur_compression_n;
    		Surf_Hexa[i].rhosurface          = TypeSurfHexa[Surf_Hexa[i].type].rhosurface;
    		Surf_Hexa[i].diam_hydro_l       = TypeSurfHexa[Surf_Hexa[i].type].diam_hydro_l;
    		Surf_Hexa[i].diam_hydro_m       = TypeSurfHexa[Surf_Hexa[i].type].diam_hydro_m;
    		Surf_Hexa[i].diam_hydro_n       = TypeSurfHexa[Surf_Hexa[i].type].diam_hydro_n;
    		Surf_Hexa[i].cdnormal            = TypeSurfHexa[Surf_Hexa[i].type].cdnormal;
    		Surf_Hexa[i].ftangent            = TypeSurfHexa[Surf_Hexa[i].type].ftangent;
  		}
	/*exit(0);*/
	
	/*strcpy(tonom,nomfichier);
	strcat(tonom,".des");
	f3 = fopen(tonom,"w");*/






	strcpy(tonom,nomfichier);
	strcat(tonom,".des");
	f3 = fopen(tonom,"w");
	/*f3 = fopen("dessin.txt","w");*/
   	if (f3 == NULL) 
  		{ 
  		printf("* creer_fichier_des * impossible d ouvrir le fichier %s\n",tonom);
  	  	exit(0);
  		}
	//for (pa=1;pa<=NbTypesurf;pa++)		fprintf(f3,"pa %3d :  %3d\n",pa,panneau[pa].flag_dessin);	fprintf(f3,"\n");
	for (pa=1;pa<=NbTypesurf;pa++)		fprintf(f3,"pa %3d :  %3d\n",pa,panneau[pa].flag_dessin);	fprintf(f3,"\n");
	for (pa=1;pa<=NbTypesurfHexa;pa++)	fprintf(f3,"he %3d : 1\n",pa);	fprintf(f3,"\n");
	for (pa=1;pa<=NbTypeelem;pa++)		fprintf(f3,"el %3d :  %3d\n",pa,TypeElement[pa].flag_dessin);	fprintf(f3,"\n");
	for (pa=1;pa<=NOMBRE_COULISSES;pa++)	fprintf(f3,"co %3d : 1\n",pa);	fprintf(f3,"\n");
	for (pa=1;pa<=NOMBRE_WINCHS;pa++)	fprintf(f3,"wi %3d : 1\n",pa);	fprintf(f3,"\n");
	for (pa=1;pa<=NOMBRE_ELEMENTS;pa++)	fprintf(f3,"ba %3d : 10\n",pa);	fprintf(f3,"\n");
	for (pa=1;pa<=NOMBRE_NOEUDS;pa++)	fprintf(f3,"pt %3d : 9\n",pa);	fprintf(f3,"\n");
	fclose(f3);
	}

void lecture_des()
	{
	/*chargement du fichier dessin.txt, qui contient les ordres de dessin des elements
	si 1 on dessine si 0 on ne dessine pas*/
	
	printf("debut lecture_des \n");/**/
	char c,tonom[100];
	int pa;
	FILE *fic;

	strcpy(tonom,fname1);
 	strcat(tonom,".des");
	fic = fopen(tonom,"r");
	/*fic = fopen("dessin.txt","r");*/
  	if (fic == NULL) 
  		{
    		printf(" \n");
    		printf("Le fichier %s n existe pas ?\n",tonom);
    		exit(0);/**/
  		} 

	printf("debut lecture_des Structure.symetry %d\n",Structure.symetry);/**/
	printf("debut lecture_des NbTypesurf %d\n",NbTypesurf);/**/
	printf("debut lecture_des NbTypesurfHexa %d\n",NbTypesurfHexa);/**/
	printf("debut lecture_des NbTypeelem %d\n",NbTypeelem);/**/
	printf("debut lecture_des NOMBRE_COULISSES %d\n",NOMBRE_COULISSES);/**/
	printf("debut lecture_des NOMBRE_WINCHS %d\n",NOMBRE_WINCHS);/**/
	printf("debut lecture_des NOMBRE_ELEMENTS %d\n",NOMBRE_ELEMENTS);/**/
	printf("debut lecture_des NOMBRE_NOEUDS %d\n",NOMBRE_NOEUDS);/**/
    	for (pa=1;pa<=NbTypesurf;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
  		fscanf(fic,"%d\n",&panneau[pa].flag_dessin);
    		}
    	for (pa=1;pa<=NbTypesurfHexa;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		fscanf(fic,"%d\n",&TypeSurfHexa[pa].flag_dessin);
    		}
    	for (pa=1;pa<=NbTypeelem;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		fscanf(fic,"%d\n",&TypeElement[pa].flag_dessin);
		}
    	for (pa=1;pa<=NOMBRE_COULISSES;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		fscanf(fic,"%d\n",&Coulisse[pa].flag_dessin);
    		}
    	for (pa=1;pa<=NOMBRE_WINCHS;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		fscanf(fic,"%d\n",&Winch[pa].flag_dessin);
    		}
	if (Structure.symetry == 0)
		{
		for (pa=1;pa<=NOMBRE_ELEMENTS;pa++)
			{
	    		do  c=fgetc(fic); while (c !=':'); 
	    		fscanf(fic,"%d\n",&Element[pa].flag_dessin);
			}
		}
	if (Structure.symetry == 2)
		{
		for (pa=1;pa<=NOMBRE_ELEMENTS/2;pa++)
			{
	    		do  c=fgetc(fic); while (c !=':'); 
	    		fscanf(fic,"%d\n",&Element[pa].flag_dessin);
	    		Element[pa+NOMBRE_ELEMENTS/2].flag_dessin = Element[pa].flag_dessin;
			}
		}
	if (Structure.symetry == 0)
		{
	    	for (pa=1;pa<=NOMBRE_NOEUDS;pa++)
	    		{
	    		do  c=fgetc(fic); while (c !=':'); 
	    		fscanf(fic,"%d\n",&Noeud[pa].flag_dessin);
			}
		}
	if (Structure.symetry == 2)
		{
	    	for (pa=1;pa<=NOMBRE_NOEUDS/2;pa++)
	    		{
	    		do  c=fgetc(fic); while (c !=':'); 
	    		fscanf(fic,"%d\n",&Noeud[pa].flag_dessin);
			}
		}
	fclose(fic);
	}

int lecture_chaine(FILE *fic, char *chain)
	{
	/*
	lecture d une chaine de caracteres compris entre ' ' '\n' '\t' ou EOF
	renvoie la longueur de la chaine 
	*/
	int zj;
	char c,t1[256];	

	chain[0] = '\0';
	c=fgetc(fic);
	if (c == EOF) 
		{
		/*printf("chain1 = %s\n",chain);*/
		return 0;
		}
	zj = 0;
	chain[zj] = c;
  	
	while ((c != EOF) && (c != ' ') && (c != '\n') && (c != '\t'))   
		{
		c=fgetc(fic);
		zj++;
		chain[zj] = c;
		}
		
		
	/*printf("zj = %d\n",zj);*/
	if ((c != EOF) && (zj == 0))
		{
		zj++;
		chain[zj] = ' ';
		/*printf("zjj = %d\n",zj);*/
		}
	else
		{
		/*printf("zjk = %d\n",zj);*/
		}
										
	chain[zj] = '\0';
	return zj;
	}
	
	
int lecture_commentaire(FILE *fic, char *chain)
	{
	/*
	lecture d une chaine de caracteres compris entre '"'
	renvoie la longueur de la chaine 
	*/
	int zj;
	char c,t1[256];	

	do  
		{
		c=fgetc(fic); 
		if (c == EOF) 
			{
			return 0;
			}
		}
	while (c !='"');
	
	/*lecture du premier caractere apres le premier "*/
	c=fgetc(fic); 
	/*printf("c = %c\n",c);*/
	zj = 0;
	chain[zj] = c;
	do  
		{
		c=fgetc(fic); 
		if (c == EOF) 
			{
			return 0;
			}
		/*printf("c = %c\n",c);*/
		zj++;
		chain[zj] = c;
		}
	while (c !='"');
	chain[zj] = ' '; /*un blanc au lieu de "*/
	/*printf("c = %c\n",c);
	printf("chain2 = %s\n",chain);
	printf("zj = %d\n",zj);*/
	
	while (zj < 50)
		{
		zj++;
		chain[zj] = ' ';
		/*printf("chain2 = %s\n",chain);*/
		}
	chain[50-2] = ':';
	chain[50] = '\0';
	return zj;
	}
	
	
