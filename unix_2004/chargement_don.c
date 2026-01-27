#define PRINCIPAL 0
#include "4c19.h"
#include <time.h>
#include "nr.h"




void modif_materiau_elem(int num_elem_choisi, double raideur_traction_choisie, double raideur_compression_choisie, double masse_volumique_choisie, double diam_hydro_choisi, double coeff_trainee_normal_choisi, double coeff_trainee_tangent_choisi)
	{
	TypeElement[num_elem_choisi].raideur_traction=raideur_traction_choisie;
	TypeElement[num_elem_choisi].raideur_compression=raideur_compression_choisie;
	TypeElement[num_elem_choisi].rhoelement=masse_volumique_choisie;
	TypeElement[num_elem_choisi].diametrehydro=diam_hydro_choisi;
	TypeElement[num_elem_choisi].cdnormal=coeff_trainee_normal_choisi;
	TypeElement[num_elem_choisi].ftangent=coeff_trainee_tangent_choisi;
	}


void charger(char *nomfichier)
	{
	/*chargement du fichier *.don, le nom generique est stocke dans fname1*/
	char c,t1[256],tonom[200],temp_char,*buffer,temp1_char;
	char chaine[] = "                                               ";
	char chainebis[] = "                                               ";
	char comment[] = "                                               ";
	int i,j,zi,zj,zk,pa,no,temp_int,temp2_int,temp3_int,type_maillage,NOMBRE_ORDRE_OBJET,symm,tmp_i1,type_ref,noeud_ref,temp1_int;
	double WB,PE3,PE4,VI,tmp_d1,tmp_d2,tmp_d3,tmp_d4,tmp_d5,tmp_d6,tmp_d7,tmp_d8,dist;
	
	double xx11,xx12,xx21,xx22,xx31,xx32,xx41,xx42,xx51,xx52,xx61,xx62,xx71,xx72,xx81,xx82;
	double yy11,yy12,yy21,yy22,yy31,yy32,yy41,yy42,yy51,yy52,yy61,yy62,yy71,yy72,yy81,yy82;

	double xxp11,xxp12,xxp21,xxp22,xxp31,xxp32,xxp41,xxp42,xxp51,xxp52,xxp61,xxp62,xxp71,xxp72,xxp81,xxp82;
	double yyp11,yyp12,yyp21,yyp22,yyp31,yyp32,yyp41,yyp42,yyp51,yyp52,yyp61,yyp62,yyp71,yyp72,yyp81,yyp82;

	int temp_num,temp_num2,itmp;
	int add_number_cage=0;
	double add_cage_diam;
	double add_cage_xxo;
	double add_cage_yyo;
	int add_cage_nsegment;
	double add_cage_dist_ann;
	double add_cage_haut_ann;

	double add_filet_pred_diam;
	double add_diam_lest;
	double add_filet_pred_xxo;
	double add_filet_pred_yyo;
	int add_filet_pred_nsegment;
	double add_hauteur_filet_elev;
	double add_taille_maille_elev;
	double add_hauteur_filet_pred;
	double add_taille_maille_pred;

	int nb_elem_cage=0;

	double diametre_pehd;
	double epaisseur_pehd;
	double rho_pehd;

	int E_numero;
	double S_Nb,S_Diam,S_Float,L_Float,S_Vol_Unit,S_Mass_Unit,S_Cd,S_Surf_Unit,S_Max_Float;
	double E_Length,E_Density,E_Diam,E_Cdn,E_Vol,E_Mass,E_Surf;
	double F_Length,F_Density,F_Diam,F_Cdn,F_Vol,F_Mass,F_Surf;
	double norm;


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

	int nb_barre_choisi;

	int pan11, pan22;
	

/************************************MODIF ARNAUD *******************/
	long idum;
	int node_type;
	double actual_foil_surface, model_foil_surface,model_mass_in_air,model_mass_in_water,foil_cd,foil_cl,foil_cz;
	double ref_length_model,ref_volume_model,ratio_mass_in_air_volume,ref_length_actual,ref_volume_actual;
	double actual_mass_in_air,model_density,actual_volume,Fd,Fl;
	
	
	float temp_double;
	FILE *fic,*f3;
	double *xmat,*cmat;
  	int n_ligne,p_colonne;
  	strcpy(tonom,nomfichier);
        j=strlen(tonom);
        while ((tonom[j])!='.' && j>0) j--;
        if (tonom[j]=='.') tonom[j]=0;
        
        
  	strcat(tonom,".don");

	fic = fopen(tonom,"r");

  	if (fic == NULL) 
  		{
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom," don't exist ?");
    		exit(0);
  		} 
  
    	printf("%s %s\n","fichier ",tonom);/**/

	find_link = 0;

	Structure.nb_winch = 0;
	Structure.version = 1;
	lecture_chaine(fic,chaine);		
	i = strlen(chaine);
	/*printf("chaine = %s  ",chaine);
	printf("longueur chaine = %d\n",i);*/
	
	if (strcmp(chaine,"version_2") == 0)
		{
		Structure.version = 2;
		}
	/*printf("Structure.version = %d\n",Structure.version);*/

	/*orientation du dessin****************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	itmp = fscanf(fic,"%d\n",&temp_int);
	/*printf("temp_int  %4d doit etre = a 1 2 ou 3  \n",temp_int );*/
	if ( (temp_int != 1) && (temp_int != 2) && (temp_int != 3))
		{
		printf(" temp_int %4d doit etre = a 1 2 ou 3  \n",temp_int );
		exit(0);
		}
	
	/*panneaux*****************************************************/
	
    	do  c=fgetc(fic); while (c !=':'); 
    	itmp = fscanf(fic,"%d\n",&Structure.NbTypesurf );
	printf("lecture %d panneaux\n",Structure.NbTypesurf); /**/
    	
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
	    	do  c=fgetc(fic); while (c !=':'); 
	    	do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&temp_int);
		buffer = fgets(t1,256,fic);
		/*printf("t1  : %s\n",t1);*/ 
		for (no=1;no<=temp_int;no++)
			{
			itmp = fscanf(fic,"%d",&temp2_int);
			itmp = fscanf(fic,"%f %f %f",&temp_double,&temp_double,&temp_double);
			itmp = fscanf(fic,"%f %f",&temp_double,&temp_double);
			itmp = fscanf(fic,"%d",&temp2_int);
			itmp = fscanf(fic,"%d",&temp2_int);
			}
		
		//buffer = fgets(t1,256,fic); 
		//buffer = fgets(t1,256,fic); 
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&panneau[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&panneau[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&panneau[pa].raideur_ouverture);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&panneau[pa].longueur_repos);
   		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&panneau[pa].rho);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&panneau[pa].diam_hydro);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&panneau[pa].largeurnoeud);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&panneau[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&panneau[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&temp_double);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&temp_int);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&temp_int);
		panneau[pa].neutral_angle = 0.0;
		panneau[pa].EI_flexion = 0.0;
		panneau[pa].tarp = 0;
		panneau[pa].current_reduction = 1.0;
		//printf("panneau[%d].longueur_repos %lf\n",pa,panneau[pa].longueur_repos);
		}
		
	/*panneaux hexagonaux*******************************************/
	
    	do  c=fgetc(fic); while (c !=':'); 
    	itmp = fscanf(fic,"%d\n",&Structure.NbTypesurf_hexa );
	/*printf("lecture %d panneaux hexagonaux\n",Structure.NbTypesurf_hexa); */
    	
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{
	    	do  c=fgetc(fic); while (c !=':'); 
	    	do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&temp_int);
		buffer = fgets(t1,256,fic);
		/*printf("t1  : %s\n",t1);*/ 
		for (no=1;no<=temp_int;no++)
			{
			itmp = fscanf(fic,"%d",&temp2_int);
			itmp = fscanf(fic,"%f %f %f",&temp_double,&temp_double,&temp_double);
			itmp = fscanf(fic,"%f %f",&temp_double,&temp_double);
			itmp = fscanf(fic,"%d",&temp2_int);
			itmp = fscanf(fic,"%d",&temp2_int);
			}
		
		buffer = fgets(t1,256,fic); 
		buffer = fgets(t1,256,fic); 
    		do  c=fgetc(fic); while (c !=':');
    		itmp = fscanf(fic,"%lf%lf%lf\n",&TypeSurfHexa[pa].raideur_traction_l,&TypeSurfHexa[pa].raideur_traction_m,&TypeSurfHexa[pa].raideur_traction_n);
    		do  c=fgetc(fic); while (c !=':'); 
     		itmp = fscanf(fic,"%lf%lf%lf\n",&TypeSurfHexa[pa].raideur_compression_l,&TypeSurfHexa[pa].raideur_compression_m,&TypeSurfHexa[pa].raideur_compression_n);
    		do  c=fgetc(fic); while (c !=':'); 
    		itmp = fscanf(fic,"%lf%lf%lf\n",&TypeSurfHexa[pa].lo_repos,&TypeSurfHexa[pa].mo_repos,&TypeSurfHexa[pa].no_repos);
    		do  c=fgetc(fic); while (c !=':'); 
     		itmp = fscanf(fic,"%lf%lf%lf\n",&TypeSurfHexa[pa].diam_hydro_l,&TypeSurfHexa[pa].diam_hydro_m,&TypeSurfHexa[pa].diam_hydro_n);
   		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%lf\n",&TypeSurfHexa[pa].rhosurface);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%lf\n",&TypeSurfHexa[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%lf\n",&TypeSurfHexa[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&temp_double);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&temp_int);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&type_maillage);
    		
		TypeSurfHexa[pa].tarp = 0;
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
    	itmp = fscanf(fic,"%d\n",&Structure.NbTypeelem);
	printf("lecture %d elements filaires\n",Structure.NbTypeelem); /**/
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); 
    		do  c=fgetc(fic); while (c !=':'); 
		for (no=1;no<=2;no++)
			{	
			/* printf("ok %d  \n",no);*/	
			if (no ==1)
				{
				itmp = fscanf(fic,"%d %lf %lf %lf %d",&temp_num,&TypeElement[pa].x1,&TypeElement[pa].y1,&TypeElement[pa].z1,&temp_num);
				printf(" %lf %lf %lf \n",TypeElement[pa].x1,TypeElement[pa].y1,TypeElement[pa].z1);/**/
				}
			else if (no ==2)
				{
				itmp = fscanf(fic,"%d %lf %lf %lf %d",&temp_num2,&TypeElement[pa].x2,&TypeElement[pa].y2,&TypeElement[pa].z2,&temp_num2);
				/*printf(" %lf %lf %lf \n",TypeElement[pa].x2,TypeElement[pa].y2,TypeElement[pa].z2);*/
				}
			}

    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&TypeElement[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&TypeElement[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&TypeElement[pa].lgrepos);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&TypeElement[pa].rhoelement);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&TypeElement[pa].diametrehydro);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&TypeElement[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&TypeElement[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&TypeElement[pa].nb_barre);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&temp_int);
    		TypeElement[pa].type = pa;
    		TypeElement[pa].EI_flexion = 0.0;
		/*printf("element %d cdnormal %lf\n",pa,TypeElement[pa].cdnormal);*/
		TypeElement[pa].slider = 0;		//default value this element is not part of a slider
		TypeElement[pa].nb_cable_contact = 0;	//default value this element is not part of a possible contact with an another cable
		}

	/*******************************************************************************************************************************/
	/*******************************************************************************************************************************/



	/*coulisses*****************************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	itmp = fscanf(fic,"%d\n",&pa);
	printf("lecture %d coulisses\n",pa);
	NOMBRE_COULISSES = pa;
	if (pa != NOMBRE_COULISSES)
		{
		//printf(" nb de coulisses != entre fichiers don et mdh %d et %d  \n ",pa,NOMBRE_COULISSES );
		//exit(0);
		}
    	
	/*printf("lecture %d coulisses\n",NOMBRE_COULISSES); */
	for (pa=1;pa<=NOMBRE_COULISSES;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); 
    		do  c=fgetc(fic); while (c !=':'); 
		for (no=1;no<=2;no++)
			{
			itmp = fscanf(fic,"%d",&temp_int);
			itmp = fscanf(fic,"%f %f%f",&temp_double,&temp_double,&temp_double);
			itmp = fscanf(fic,"%d",&temp_int);
			}
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Coulisse[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Coulisse[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Coulisse[pa].lgrepos);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Coulisse[pa].rhocoulisse);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Coulisse[pa].diametrehydro);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Coulisse[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Coulisse[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&temp_int);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&temp_int);

		/*
		printf("coulisse  %5d \n",pa);
		printf("raideur traction  %lf \n",Coulisse[pa].raideur_traction);
		printf("raideur traction  %lf \n",Coulisse[pa].raideur_compression);
		printf("raideur traction  %lf \n",Coulisse[pa].lgrepos);
		printf("raideur traction  %lf \n",Coulisse[pa].rhocoulisse);
		printf("raideur traction  %lf \n",Coulisse[pa].diametrehydro);
		printf("raideur traction  %lf \n",Coulisse[pa].cdnormal);
		printf("raideur traction  %lf \n",Coulisse[pa].ftangent);
		exit(0);
		*/
		}

if (Structure.version == 2)
	{
	/*winchs*****************************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	itmp = fscanf(fic,"%d\n",&Structure.nb_winch);
	/*printf("Structure.nb_winch  = %8d\n", Structure.nb_winch); */
	for (pa=1;pa<=Structure.nb_winch;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); 
    		do  c=fgetc(fic); while (c !=':'); 
		for (no=1;no<=2;no++)
			{
			itmp = fscanf(fic,"%d",&temp_int);
			itmp = fscanf(fic,"%f %f %f",&temp_double,&temp_double,&temp_double);
			itmp = fscanf(fic,"%d",&temp_int);
			}
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Winch[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Winch[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Winch[pa].longueur_repos);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Winch[pa].rho);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Winch[pa].diam_hydro);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Winch[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Winch[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&Winch[pa].adjust_force);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Winch[pa].nb_barre);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Winch[pa].type_noeud);
		/*printf("length of winch %d = %lf m \n",pa,Winch[pa].longueur_repos);*/
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
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&temp_int); 
	/*printf("Structure.nb_liaison  = %8d\n", temp_int);*/
	for (pa=1;pa<=temp_int;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d",&temp2_int);
		for (i=1;i<=temp2_int;i++)
			{
			do  c=fgetc(fic); while (c ==' '); temp_char = fgetc(fic);
    			do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d",&temp3_int);
    			do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d",&temp3_int);
			}
		}
		




	/*ordre de maillage***************************************************/
	
	NOMBRE_ORDRE_OBJET = Structure.NbTypesurf + Structure.NbTypeelem + NOMBRE_WINCHS + NOMBRE_COULISSES + Structure.NbTypesurf_hexa;
	/*printf("NOMBRE_ORDRE_OBJET = %8d\n", NOMBRE_ORDRE_OBJET);*/
	do  
		{
		c=fgetc(fic); 
		/*printf("%c",c);*/
		}
	while (c !=':'); 
	/*printf("\n");*/
		
		
	for (i=1;i<=NOMBRE_ORDRE_OBJET;i++)
		{ 
		do c=fgetc(fic); while ((c ==' ') || (c =='\n')); temp_char = c;
				
		if((temp_char!= 'a') && (temp_char!= 'p') && (temp_char != 'h') && (temp_char != 'e') && (temp_char !='c') && (temp_char !='w'))
			{
			printf("warning : the type of the object %d is unknown.",i);
    			printf("type = %c\n",temp_char);/**/
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
			
			
	    		do  c=fgetc(fic); while (c !=':');     itmp = fscanf(fic,"%d",&temp_int);
	    		//printf("type = %c indice = %d\n",temp_char,temp_int);/**/
			if (temp_char == 'p')
				{
				if((temp_int<1) || (temp_int>Structure.NbTypesurf))
					{
					printf("warning :the indice %d of the object %d is incompatible\n",temp_int,i);
					exit(0);
					}
				}
			if (temp_char == 'h')
				{
				if((temp_int<1) || (temp_int>Structure.NbTypesurf_hexa))
					{
					printf("warning: the indice %d of the object %d is incompatible\n",temp_int,i);
					exit(0);
					}
				}
			if (temp_char == 'e')
				{
				if((temp_int<1) || (temp_int>Structure.NbTypeelem))
					{
					printf("warning: the indice %d of the object %d is incompatible\n",temp_int,i);
					exit(0);
					}
				}
			if (temp_char == 'c')
				{
				if((temp_int<1) || (temp_int>NOMBRE_COULISSES))
					{
					printf("warning: the indice %d of the object %d is incompatible\n",temp_int,i);
					exit(0);
					}
				}
			if (temp_char == 'w')
				{
				if((temp_int<1) || (temp_int>NOMBRE_WINCHS))
					{
					printf("warning: the indice %d of the object %d is incompatible\n",temp_int,i);
					exit(0);
					}
				}
			/////////////////////////////////////////////////////
			}
 	        }
	
		
		
		
	/*Types de Noeuds*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Structure.NbTypeNoeud); 
	printf("Structure.NbTypeNoeud = %4d\n",Structure.NbTypeNoeud );/**/
	for (pa=1;pa<=Structure.NbTypeNoeud;pa++)
		{
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].mx,&TypeNoeud[pa].my,&TypeNoeud[pa].mz);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].majx,&TypeNoeud[pa].majy,&TypeNoeud[pa].majz);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].lonx,&TypeNoeud[pa].lony,&TypeNoeud[pa].lonz);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].cdx,&TypeNoeud[pa].cdy,&TypeNoeud[pa].cdz);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].fextx,&TypeNoeud[pa].fexty,&TypeNoeud[pa].fextz);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d %d%d",&TypeNoeud[pa].fixx,&TypeNoeud[pa].fixy,&TypeNoeud[pa].fixz);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf %lf%lf",&TypeNoeud[pa].limx,&TypeNoeud[pa].limy,&TypeNoeud[pa].limz);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d %d%d",&TypeNoeud[pa].senx,&TypeNoeud[pa].seny,&TypeNoeud[pa].senz);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d %d%d",&TypeNoeud[pa].symx,&TypeNoeud[pa].symy,&TypeNoeud[pa].symz);
		}

	/*ENVIRONNEMENT NUMERIQUE*****************************************************/
		do  c=fgetc(fic);  while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Structure.diviseur);
		//printf("Structure.diviseur %lf \n",Structure.diviseur);
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Seuilconvergence); 
		if (Seuilconvergence <= 0.0) {printf("Seuilconvergence must be > 0.0 and not = %15.5lf \n",Seuilconvergence); exit(0);}
		printf("Convergence threshold (N) 		%lf \n",Seuilconvergence);
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Deplacement); 
		if (Deplacement <= 0.0) {printf("Deplacement must be > 0.0 and not = %15.5lf \n",Deplacement); exit(0);}
		printf("Maximal allowed displacement (m) 	%lf \n",Deplacement);
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%10d\n",&Nbmaxiterations); 
		if (Nbmaxiterations <= 0) {printf("Nbmaxiterations must be > 0 and not = %15d \n",Nbmaxiterations); exit(0);}
		printf("Maximal number of ierations 		%d \n",Nbmaxiterations);
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Pascalcul); 
		if (Pascalcul <= 0.0) {printf("Pascalcul must be > 0.0 and not = %15.5lf \n",Pascalcul); exit(0);}
		printf("Dynamic time step (s) 			%lf \n",Pascalcul);
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Passtockage); 
		if (Passtockage <= 0.0) {printf("Record time step must be > 0.0 and not = %15.5lf \n",Passtockage); exit(0);}
		printf("Dynamic recording time step (s) 	%lf \n",Passtockage);
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Debutstockage); 
		printf("Begining of recording (s) 		%lf \n",Debutstockage);
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Finstockage); 
		printf("End of recording (s) 			%lf \n",Finstockage);
	
	/*ENVIRONNEMENT METEOROLOGIQUE ET OCEANIQUE***********************************/
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Courant.direction); 
		printf("Current direction (deg.)		%lf \n",Courant.direction);
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Courant.vitesse); 
		printf("Current speed (m/s) 			%lf \n",Courant.vitesse);
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Houle.periode); 
		printf("Wave period (s) 			%lf \n",Houle.periode);
		if (Houle.periode <= 0.0) {printf("Wave period must be > 0.0 and not = %15.5lf \n",Houle.periode); exit(0);}
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Houle.hauteur); 
		printf("Wave height (m) 			%lf \n",Houle.hauteur);
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Houle.direction); 
		printf("Wave direction (deg.) 			%lf \n",Houle.direction);
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Houle.depth);
		if (Houle.depth <= 0.0) {printf("Houle.depth must be > 0.0 and not = %15.5lf \n",Houle.depth); exit(0);}
		 
	/*DESCRIPTION DE LA PRISE*****************************************************/
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Prise.volume);
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Prise.seuil);
		if (Prise.seuil <= 0.0) {printf("Accuracy on the catch volume must be > 0.0 and not = %15.5lf \n",Prise.seuil); exit(0);}
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Prise.cd);
		Prise.PR = 0.0; /*utilise pour verifier si la prise est initialiser par le volume de poisson PR ou par le volume */
		
	/*ENVIRONNEMENT DU FOND MARIN*************************************************/
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Bottom.coef_frottement);
		do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%lf\n",&Bottom.raideur);

		
	/*sortie texte*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.nb_distance); 
	/*printf("Sortie_texte.nb_distance  = %8d\n",Sortie_texte.nb_distance );*/
	if (Sortie_texte.nb_distance != 0)
		{
       		/**********************************************/
	       	Sortie_texte.noeud1_distance = (int *) malloc((1 + Sortie_texte.nb_distance) * sizeof(int));
       		if (Sortie_texte.noeud1_distance    == NULL)
        	       	{
        	       	printf("Sortie_texte.noeud1_distance  1 = NULL  \n" );
        	       	exit(0);
        	       	}
       		/**********************************************/
       		Sortie_texte.noeud2_distance = (int *) malloc((1 + Sortie_texte.nb_distance) * sizeof(int));
       		if (Sortie_texte.noeud2_distance    == NULL)
        	       {
        	       printf("Sortie_texte.noeud2_distance  1 = NULL  \n" );
        	       exit(0);
        	       }
       		/**********************************************/
	       Sortie_texte.decimale_distance = (int *) malloc((1 + Sortie_texte.nb_distance) * sizeof(int));
	       if (Sortie_texte.decimale_distance    == NULL)
        	       {
        	       printf("Sortie_texte.decimale_distance  1 = NULL  \n" );
        	       exit(0);
        	       }
	       /**********************************************/
	       Sortie_texte.comment_distance = (COMMENTAIRE *) malloc((1 + Sortie_texte.nb_distance) * sizeof(COMMENTAIRE));
	       if (Sortie_texte.comment_distance    == NULL)
        	       {
        	       printf("Sortie_texte.comment_distance  1 = NULL  \n" );
        	       exit(0);
        	       }
	       /**********************************************/
		for (pa=1;pa<=Sortie_texte.nb_distance;pa++)
			{
	    		do  c=fgetc(fic); while (c !=':');
	    		do  c=fgetc(fic); while (c !=':');
    		
			c=fgetc(fic); 
			while ((c =='#') || (c ==' '))
				{
				c=fgetc(fic); 
				}
			for (i=1;i<=155;i++)
				{
				/*Sortie_texte.comment_distance[pa][i] = ' ';*/
				Sortie_texte.comment_distance[pa].texte[i] = ' ';
				}
			i = 0;
			while ((c !='#') && (i<155))
				{
				i++;
				/*Sortie_texte.comment_distance[pa][i] = c;*/
				Sortie_texte.comment_distance[pa].texte[i] = c;
				c=fgetc(fic);
				}
			i++;
			/*Sortie_texte.comment_distance[pa][i] = ':';*/
			Sortie_texte.comment_distance[pa].texte[i] = ':';
			do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%d\n",&Sortie_texte.noeud1_distance[pa]);
			do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%d\n",&Sortie_texte.noeud2_distance[pa]);
			do  c=fgetc(fic); while (c !=':');	itmp = fscanf(fic,"%d\n",&Sortie_texte.decimale_distance[pa]);
			}
		}
	/*sortie texte effort*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.nb_effort);
	if (Sortie_texte.nb_effort != 0)
		{
       	/**********************************************/
       	Sortie_texte.noeud_effort = (int *) malloc((1 + Sortie_texte.nb_effort) * sizeof(int));
       	if (Sortie_texte.noeud_effort    == NULL)
               	{
               	printf("Sortie_texte.noeud_effort  1 = NULL  \n" );
               	exit(0);
               	}
       	/**********************************************/
       	Sortie_texte.axe_effort = (int *) malloc((1 + Sortie_texte.nb_effort) * sizeof(int));
       	if (Sortie_texte.axe_effort    == NULL)
               {
               printf("Sortie_texte.axe_effort  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.decimale_effort = (int *) malloc((1 + Sortie_texte.nb_effort) * sizeof(int));
       if (Sortie_texte.decimale_effort    == NULL)
               {
               printf("Sortie_texte.decimale_effort  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.comment_effort = (COMMENTAIRE *) malloc((1 + Sortie_texte.nb_effort) * sizeof(COMMENTAIRE));
       /*Sortie_texte.comment_effort = (char *) malloc((1 + Sortie_texte.nb_effort) * 156 * sizeof(char));*/
       if (Sortie_texte.comment_effort    == NULL)
               {
               printf("Sortie_texte.comment_effort  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
	for (pa=1;pa<=Sortie_texte.nb_effort;pa++)
		{
    		do  c=fgetc(fic); while (c !=':');
    		do  c=fgetc(fic); while (c !=':');
    		
		c=fgetc(fic); 
		while ((c =='#') || (c ==' '))
			{
			c=fgetc(fic); 
			}
		for (i=1;i<=155;i++)
			{
			Sortie_texte.comment_effort[pa].texte[i] = ' ';
			}
		i = 0;
		while ((c !='#') && (i<155))
			{
			i++;
			Sortie_texte.comment_effort[pa].texte[i] = c;
			c=fgetc(fic);
			}
		i++;
		Sortie_texte.comment_effort[pa].texte[i] = ':';
		 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.noeud_effort[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.axe_effort[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.decimale_effort[pa]);
		
		/*printf("noeud = %d ",Sortie_texte.noeud_effort[pa]);
		printf("axe = %d ",Sortie_texte.axe_effort[pa]);
		printf("decimale_effort = %d\n",Sortie_texte.decimale_effort[pa]);*/
		}
		}

	/*sortie texte tension*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.nb_tension_element); 
	/*printf("Sortie_texte.nb_tension_element  = %8d\n",Sortie_texte.nb_tension_element );*/
	if (Sortie_texte.nb_tension_element != 0)
		{
       	/**********************************************/
       	Sortie_texte.element_tension = (int *) malloc((1 + Sortie_texte.nb_tension_element) * sizeof(int));
       	if (Sortie_texte.element_tension    == NULL)
               	{
               	printf("Sortie_texte.element_tension  1 = NULL  \n" );
               	exit(0);
               	}
       	/**********************************************/
       	Sortie_texte.element_extremite = (int *) malloc((1 + Sortie_texte.nb_tension_element) * sizeof(int));
       	if (Sortie_texte.element_extremite    == NULL)
               {
               printf("Sortie_texte.element_extremite  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.decimale_tension_element = (int *) malloc((1 + Sortie_texte.nb_tension_element) * sizeof(int));
       if (Sortie_texte.decimale_tension_element    == NULL)
               {
               printf("Sortie_texte.decimale_tension_element  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.comment_tension_element = (COMMENTAIRE *) malloc((1 + Sortie_texte.nb_tension_element) * sizeof(COMMENTAIRE));
       /*Sortie_texte.comment_tension_element = (char *) malloc((1 + Sortie_texte.nb_tension_element) * 156 * sizeof(char));*/
       if (Sortie_texte.comment_tension_element    == NULL)
               {
               printf("Sortie_texte.comment_tension_element  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
	for (pa=1;pa<=Sortie_texte.nb_tension_element;pa++)
		{
    		do  c=fgetc(fic); while (c !=':');
    		do  c=fgetc(fic); while (c !=':');
    		
		c=fgetc(fic); 
		while ((c =='#') || (c ==' '))
			{
			c=fgetc(fic); 
			}
		for (i=1;i<=155;i++)
			{
			Sortie_texte.comment_tension_element[pa].texte[i] = ' ';
			}
		i = 0;
		while ((c !='#') && (i<155))
			{
			i++;
			Sortie_texte.comment_tension_element[pa].texte[i] = c;
			c=fgetc(fic);
			}
		i++;
		Sortie_texte.comment_tension_element[pa].texte[i] = ':';
		 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.element_tension[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.element_extremite[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.decimale_tension_element[pa]);
		
		/*printf("element_tension = %d ",Sortie_texte.element_tension[pa]);
		printf("element_extremite = %d ",Sortie_texte.element_extremite[pa]);
		printf("decimale_tension_element = %d\n",Sortie_texte.decimale_tension_element[pa]);*/
		}
		}

	/*sortie texte tension coulisse*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.nb_tension_coulisse); 
	/*printf("Sortie_texte.nb_tension_coulisse  = %8d\n",Sortie_texte.nb_tension_coulisse	);*/
       	/**********************************************/
       	if (Sortie_texte.nb_tension_coulisse != 0)
       		{
       	Sortie_texte.coulisse_tension = (int *) malloc((1 + Sortie_texte.nb_tension_coulisse) * sizeof(int));
       	if (Sortie_texte.coulisse_tension    == NULL)
               	{
               	printf("Sortie_texte.coulisse_tension  1 = NULL  \n" );
               	exit(0);
               	}
       	/**********************************************/
       	Sortie_texte.coulisse_extremite = (int *) malloc((1 + Sortie_texte.nb_tension_coulisse) * sizeof(int));
       	if (Sortie_texte.coulisse_extremite    == NULL)
               {
               printf("Sortie_texte.coulisse_extremite  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.decimale_tension_coulisse = (int *) malloc((1 + Sortie_texte.nb_tension_coulisse) * sizeof(int));
       if (Sortie_texte.decimale_tension_coulisse    == NULL)
               {
               printf("Sortie_texte.decimale_tension_coulisse  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.comment_tension_coulisse = (COMMENTAIRE *) malloc((1 + Sortie_texte.nb_tension_coulisse) * sizeof(COMMENTAIRE));
       /*Sortie_texte.comment_tension_coulisse = (char *) malloc((1 + Sortie_texte.nb_tension_coulisse) * 156 * sizeof(char));*/
       if (Sortie_texte.comment_tension_coulisse    == NULL)
               {
               printf("Sortie_texte.comment_tension_coulisse  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
	for (pa=1;pa<=Sortie_texte.nb_tension_coulisse;pa++)
		{
    		do  c=fgetc(fic); while (c !=':');
    		do  c=fgetc(fic); while (c !=':');
    		
		c=fgetc(fic); 
		while ((c =='#') || (c ==' '))
			{
			c=fgetc(fic); 
			}
		for (i=1;i<=155;i++)
			{
			Sortie_texte.comment_tension_coulisse[pa].texte[i] = ' ';
			}
		i = 0;
		while ((c !='#') && (i<155))
			{
			i++;
			Sortie_texte.comment_tension_coulisse[pa].texte[i] = c;
			c=fgetc(fic);
			}
		i++;
		Sortie_texte.comment_tension_coulisse[pa].texte[i] = ':';
		 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.coulisse_tension[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.coulisse_extremite[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.decimale_tension_coulisse[pa]);
		
		/*printf("coulisse_tension = %d\n",Sortie_texte.coulisse_tension[pa]);
		printf("coulisse_extremite = %d\n",Sortie_texte.coulisse_extremite[pa]);
		printf("decimale_tension_coulisse = %d\n",Sortie_texte.decimale_tension_coulisse[pa]);*/
		}
		}

	/*sortie texte position*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.nb_position); 
	/*printf("Sortie_texte.nb_position  = %8d\n",Sortie_texte.nb_position );*/
	if (Sortie_texte.nb_position != 0)
		{
       	/**********************************************/
       	Sortie_texte.noeud_position = (int *) malloc((1 + Sortie_texte.nb_position) * sizeof(int));
       	if (Sortie_texte.noeud_position    == NULL)
               	{
               	printf("Sortie_texte.noeud_position  1 = NULL  \n" );
               	exit(0);
               	}
       	/**********************************************/
       	Sortie_texte.axe_position = (int *) malloc((1 + Sortie_texte.nb_position) * sizeof(int));
       	if (Sortie_texte.axe_position    == NULL)
               {
               printf("Sortie_texte.axe_position  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.decimale_position = (int *) malloc((1 + Sortie_texte.nb_position) * sizeof(int));
       if (Sortie_texte.decimale_position    == NULL)
               {
               printf("Sortie_texte.decimale_position  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.comment_position = (COMMENTAIRE *) malloc((1 + Sortie_texte.nb_position) * sizeof(COMMENTAIRE));
       /*Sortie_texte.comment_position = (char *) malloc((1 + Sortie_texte.nb_position) * 156 * sizeof(char));*/
       if (Sortie_texte.comment_position    == NULL)
               {
               printf("Sortie_texte.comment_position  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
	for (pa=1;pa<=Sortie_texte.nb_position;pa++)
		{
    		do  c=fgetc(fic); while (c !=':');
    		do  c=fgetc(fic); while (c !=':');
    		
		c=fgetc(fic); 
		while ((c =='#') || (c ==' '))
			{
			c=fgetc(fic); 
			}
		for (i=1;i<=155;i++)
			{
			Sortie_texte.comment_position[pa].texte[i] = ' ';
			}
		i = 0;
		while ((c !='#') && (i<155))
			{
			i++;
			Sortie_texte.comment_position[pa].texte[i] = c;
			c=fgetc(fic);
			}
		i++;
		Sortie_texte.comment_position[pa].texte[i] = ':';
		 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.noeud_position[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.axe_position[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.decimale_position[pa]);
		
		/*printf("noeud_position = %d ",Sortie_texte.noeud_position[pa]);
		printf("axe_position = %d ",Sortie_texte.axe_position[pa]);
		printf("decimale_position = %d\n",Sortie_texte.decimale_position[pa]);*/
		
		}
		}

	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.effort_structure); 
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.diametre_prise); 
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.epaisseur_prise); 
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.volume_capture); 
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.surface_filtree); 
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.vitesse_courant);
	
	/*
	printf("effort_structure = %d \n",Sortie_texte.effort_structure);
	printf("diametre_prise   = %d \n",Sortie_texte.diametre_prise);
	printf("epaisseur_prise  = %d \n",Sortie_texte.epaisseur_prise);
	printf("volume_capture   = %d \n",Sortie_texte.volume_capture);
	printf("surface_filtree  = %d \n",Sortie_texte.surface_filtree);
	printf("vitesse_courant  = %d \n",Sortie_texte.vitesse_courant);
	*/
	
	
	/**************************************************************/
	/*structure longueur de cable en utilisant les fonctions d allocation
	de alloc.c au depart nb_longueur_cable  est mis = 0
	nb_longueur_cable = le nombre de longueur de cables que l on veux afficher*/
	Sortie_texte.nb_longueur_cable =	0;
	
	/*structure energie de panneau en utilisant les fonctions d allocation
	de alloc.c au depart nb_longueur_cable  est mis = 0
	nb_longueur_cable = le nombre de longueur de cables que l on veux afficher*/
	Sortie_texte.nb_energie_elong_diamond =	0;
	
	/*structure energie de panneau en utilisant les fonctions d allocation
	de alloc.c au depart nb_longueur_cable  est mis = 0
	nb_longueur_cable = le nombre de longueur de cables que l on veux afficher*/
	Sortie_texte.nb_energie_fold_diamond =	0;
	
	/*structure energie de panneau en utilisant les fonctions d allocation
	de alloc.c au depart nb_longueur_cable  est mis = 0
	nb_longueur_cable = le nombre de longueur de cables que l on veux afficher*/
	Sortie_texte.nb_energie_open_diamond =	0;
				
	Sortie_texte.inner_surface = 0;
	Sortie_texte.inner_surface_triangulation = 0;
	Sortie_texte.meridian = 0;
	Opening_angle.nb_panel = 0;
	Opening_angle_stripe.nb_stripe = 0;
	Opening_angle_stripe.nb_panel = 0;
	Prise.panels[1] = 0;
	Prise.panels[2] = 0;
	Spheric_limit.radius = -1.0;
	Prise.dir_mesh_front = 0;
	Prise.catch_gravity = 0.0;
	Structure.nb_tarp_diamond = 0;
	Structure.nb_tarp_hexa = 0;
	Structure.nb_catch2_length = 0;
	Structure.nb_catch2_surface = 0;
	Structure.nb_catch2_volume = 0;
	Structure.nb_catch2_weight = 0;
	Structure.nb_value = 0;		/*nb of linear value*/
	Courant.nb_courant = 0;
	Courant.nb_angle_speed_cd = 0;
	Structure.nb_recouvrement_x = 0;	/*nb of recouvrement_x between elements*/
	Structure.nb_cage_volume = 0;	
	Structure.nb_vector_tension_bar = 0;
	Auto_convergence = 0;
	Vent.vitesse = 0.0;
	Vent.direction = 0.0;
	
	chaine[1] = '\0';
	
	/*printf("chaine = %s\n",chaine);
	i = strlen(chaine);
	printf("longueur chaine = %d\n",i);
	i = lecture_chaine(fic,chaine);*/
	int elem_inter =1;
	int nb_ele_depart=1;
	int nb_tot_elem=0;

	int ele_inter_pred =0;

	int elem_no1;
	int elem_no2;
	for (zi=1;zi<=Structure.NbTypeelem;zi++)	
		{
		TypeElement[zi].noeud_trainee = 1;	//volume des barres reporté dans des cubes centrés sur les 2 extremités de la barre				
		}


	int immersion =0;
	Prise.catch_dynamic = -1.0;	/*if <0 there is no dynamic of the catch*/
	Bottom.moving = 0;		/*if 0 the bottom is not moving if 1 the bottom move at the water speed*/
	RHO = 1025.0;                   	/*default value of the water density*/
	RHO_AIR = 1.208;                 	/* air density*/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		panneau[pa].largeurnoeud = 0.0;	/*the default value of the knot diameter of the netting is 0.0 m*/	
		}
	Plan_cutting.nb_plan = 0;
	Structure.hydro_forces = 0;			/*the default value = 0, otherwise it is 1 and if 1 the file *.hyd is created which contazins the nodes positions along x y z and the hydrodynamic forces on these ponts along x y and z*/
	Structure.drag_forces_type = 1;			/*the default value = 1, in this case the fhydrodynamic forces on netting is calculated with morison form=ulation,
							otherwise it is 2 in this case it is zhan formulation, or 3 where it is the drop pressure*/
	Structure.cut_plan_symmetry = 0;			/*the default value = 0, in this case there is no calculation of the intersection of triangular elements of diamond netting with symmetry plan,
							if 1 there is calculation of the intersection of triangular elements of diamond netting with symmetry plan X,
							if 2 there is calculation of the intersection of triangular elements of diamond netting with symmetry plan Y,
							if 3 there is calculation of the intersection of triangular elements of diamond netting with symmetry plan Z,
							*/
	Structure.nb_hauling_cable = 0;			/*the default value = 0, in this case there is no hauling cable used in dynamic (dyna2)*/
	Structure.nb_hauling_cable2 = 0;			/*the default value = 0, in this case there is no hauling cable used in dynamic (dyna2) of type 2*/
	for (zi=1;zi<=Structure.NbTypeelem;zi++)
		{
		TypeElement[zi].haul_speed = 0.0;
		TypeElement[zi].haul_extremity = 0;
		TypeElement[zi].haul_limit = 1.0;
		TypeElement[zi].haul_time = 0.0;
		TypeElement[zi].haul_beg_times = 0.0;
		TypeElement[zi].haul_end_times = 0.0;
		TypeElement[zi].haul_beg_speed = 0.0;
		TypeElement[zi].haul_end_speed = 0.0;
		TypeElement[zi].haul_energy = 0.0;
		TypeElement[zi].nb_times = 0;
		TypeElement[zi].times  = (double *) Malloc_double(1 + TypeElement[zi].nb_times);
		TypeElement[zi].haul_v = (double *) Malloc_double(1 + TypeElement[zi].nb_times);
		TypeElement[zi].haul_d = (double *) Malloc_double(1 + TypeElement[zi].nb_times);
		TypeElement[zi].haul_ext = (int *) Malloc_int(1 + TypeElement[zi].nb_times);

		TypeElement[zi].link_flexion = (int *) Malloc_int(3);		/*in case of 2 bar are connected */
		for (i = 0; i < 3; i++) TypeElement[zi].link_flexion[i] = 0;
		TypeElement[zi].nb_link_flexion2 = 0;
		TypeElement[zi].link_flexion2 = (int *) Malloc_int(1 + TypeElement[zi].nb_link_flexion2);
		TypeElement[zi].angle_link_flexion2 = (double *) Malloc_double(1 + TypeElement[zi].nb_link_flexion2);
		TypeElement[zi].constant_tension = 0;		//no cable with constant tension
		TypeElement[zi].nb_cable_contact = 0;	

		}
	Structure.nb_speed_type_node = 0;			/*the default value = 0, in this case there is no speed type node used in dynamic (dyna2)*/
	for (zi=1;zi<=Structure.NbTypeNoeud;zi++)
		{
		TypeNoeud[zi].beg_times 	= 0.0;
		TypeNoeud[zi].end_times 	= 0.0;
		TypeNoeud[zi].nb_times 		= 0;
		TypeNoeud[zi].times   		= (double *) Malloc_double(1 + TypeNoeud[zi].nb_times);
		TypeNoeud[zi].speedx  		= (double *) Malloc_double(1 + TypeNoeud[zi].nb_times);
		TypeNoeud[zi].speedy  		= (double *) Malloc_double(1 + TypeNoeud[zi].nb_times);
		TypeNoeud[zi].speedz  		= (double *) Malloc_double(1 + TypeNoeud[zi].nb_times);
		TypeNoeud[zi].speedm  		= (double *) Malloc_double(1 + TypeNoeud[zi].nb_times);
		TypeNoeud[zi].speedo  		= (double *) Malloc_double(1 + TypeNoeud[zi].nb_times);
		TypeNoeud[zi].speedd  		= (double *) Malloc_double(1 + TypeNoeud[zi].nb_times);
		TypeNoeud[zi].nb_times_fext 	= 0;
		TypeNoeud[zi].times_fext   	= (double *) Malloc_double(1 + TypeNoeud[zi].nb_times_fext);
		}
	Structure.nb_ratio_drag_panel = 0;			/*the default value = 0, in this case there is no speed type node used in dynamic (dyna2)*/
	Structure.times_drag_panel	= (double *) Malloc_double(1 + Structure.nb_ratio_drag_panel);
	Structure.ratio_drag_panel	= (double *) Malloc_double(1 + Structure.nb_ratio_drag_panel);

	Structure.type_solver = 1; 		/*the default value = 1, in this case the solver is gauss*/
	Grid_drag.pas = 0; 			/*the default value = 0, in this case there is no calculation of drag grid*/
	Foot_print.nb = 0;
	Structure.eigenvalues = 0;
	Structure.convergence_parameters = 0;	//default value, the convergence parameters are those of ~/hexa/unix_2004/param.txt
	Structure.delta_h1 = 0;			//default value no calculation of total height
	Structure.curvature = 0;
	Structure.hauling_cable4_tension = 0;	//default value no record of hauling tensions in *.hwt file
	Structure.nb_ballast = 0;
	Structure.nb_deck = 0;
	Prise.angle_tensions = 0;
	Prise.angle_twines = 0.0;
	Prise.tension_u = 0.0;
	Prise.tension_v = 0.0;	
	Structure.boat_no = 0;			//default value, there is no node which refers to the boat and there is no record of the power delivered by the boat	
	Structure.ballast_altitude = 0;	//default value, in this case there is no record of the altitude (m) in the ballast in sta file
	Structure.total_mass = 0.0;		//
	Structure.netting_volume_calculation = 0;		//volume inside nettings. If 0 the calculation is not done
	Sortie_texte.bar_tension = 0;	
	Sortie_texte.diamond_tension = 0;	
	Structure.speed_type_node = 0;		//default value. if 1, there is coordates for which the speed could be defined in *.fos file			
	Structure.nb_slider = 0;
	Structure.wave_model = 1;		//default value, the wave model used is Airy finite depth. The alternatives are 2: Stokes 2d order finite depth and 3: Stokes 3d order infinite depth
	Structure.stiffness_matrix = 0;	//default value, the stiffness matrix is not recorded in *.sti file
	Structure.nrj = 0;			//if 1 the energy par time step is recorded in *.nrj
	Structure.haul = 0;			//if 1 the bars length par time step is recorded in *.haul
	Structure.nb_cable_contact = 0;
	Structure.openfoam = 0;		//default value: openfoam will not be used
	Structure.pressure_file = 0;		//default value: pressure file is not created
	Structure.paraview = 0;		//default value: paraview files (*.vtk) are not created
	Structure.exit_size_diamond_panel = 0;		//default value: min max mean std_dev of exit size per diamond panel are not calculated
	Structure.mean_XYZ_desequilibrium = 0;		//default is 0. 1: display at each iteration mean desequilibrium along X, Y and Z (N)
	
	while (lecture_chaine(fic,chaine) != 0)
		{
		
		/*i = strlen(chaine);*/
		//printf("chaine %s  \n",chaine);/**/
		/*printf("longueur chaine = %d\n",i);*/
		
		
		
	
		if (strcmp(chaine,"output") == 0)
			{
			/*printf("lecture d output  ");/**/
			i = lecture_chaine(fic,chaine);
			//printf("output %s  \n",chaine);/**/
			if (strcmp(chaine,"mean_XYZ_desequilibrium") == 0)
				{
				printf("mean_XYZ_desequilibrium\n");
			 	Structure.mean_XYZ_desequilibrium = 1;
				}
			if (strcmp(chaine,"exit_size_diamond_panel") == 0)
				{
				printf("min max mean and std dev of exit_size are calculated per diamond panel\n");
			 	Structure.exit_size_diamond_panel = 1;
				}
			if (strcmp(chaine,"paraview") == 0)
				{
				printf("paraview files are created\n");
			 	Structure.paraview = 1;
				}
			if (strcmp(chaine,"pressure_file") == 0)
				{
				printf("pressure_file\n");
			 	Structure.pressure_file = 1;
				}
			if (strcmp(chaine,"haul") == 0)
				{
				Structure.haul = 1;	//if 1 the bars length per time step is recorded in *.haul
				printf("There is record of the bars length per time step in *.haul\n");
				}
			if (strcmp(chaine,"nrj") == 0)
				{
				Structure.nrj = 1;	//if 1 the energy par time step is recorded in *.nrj
				printf("There is record of the nrj per time step in *.nrj\n");
				}
			if (strcmp(chaine,"stiffness_matrix") == 0)
				{
				Structure.stiffness_matrix = 1;	//if 1 the stiffness matrix is recorded in *.sti
				printf("There is record of the stiffness matrix in *.sti\n");
				}
			if (strcmp(chaine,"netting_volume") == 0)
				{
				Structure.netting_volume_calculation = 1;	//if 1 the calculation is done
				itmp = fscanf(fic,"%lf",&Structure.front_netting_volume);	//position of the front plane normal to X axis
				printf("There is record of the volume inside nettings in sta file and in vol file for dynamic calculation\n");
				}
			if (strcmp(chaine,"gravity_floatability") == 0)
				{
				Structure.total_mass 			= -1.0;
				Structure.x_g = 0.0;	Structure.y_g = 0.0;	Structure.z_g = 0.0;
				Structure.total_volume_floatability 	=  0.0;
				Structure.x_p = 0.0;	Structure.y_p = 0.0;	Structure.z_p = 0.0;
				printf("There is record of the total mass, its position, the total floatabilty and its position in sta file\n");
				}
			if (strcmp(chaine,"ballast_altitude") == 0)
				{
				Structure.ballast_altitude = 1;
				printf("There is record a record of the ballasts altitude in sta file\n");
				}
			if (strcmp(chaine,"boat_no") == 0)
				{
				itmp = fscanf(fic,"%d",&Structure.boat_no);	/*node number which refers to rthe boat*/
				printf("There is record of power delivered by the boat in *.nrj file.\n");
				}
			if (strcmp(chaine,"prise_angle_tensions") == 0)
				{
				Prise.angle_tensions = 1;
				printf("There is record of angle (deg) between tiwnes and tension (N) in twines at the catch front\n");
				}
			if (strcmp(chaine,"hauling_cable4_tension") == 0)
				{
				Structure.hauling_cable4_tension = 1;
				printf("There is record of hauling tensions if any in *.hwt file.\n");
				}
			if (strcmp(chaine,"Delta_h") == 0)
				{
				Structure.delta_h1 = 1;
				printf("There is calculation of the total height of the structure.\n");
				}
			if (strcmp(chaine,"Delta_h_v") == 0)
				{
				Structure.Delta_h_v = 1;
				itmp = fscanf(fic,"%d",&Structure.Delta_h1);	/*first  node of the first  distance*/
				itmp = fscanf(fic,"%d",&Structure.Delta_h2);	/*second node of the first  distance*/
				itmp = fscanf(fic,"%d",&Structure.Delta_h3);	/*first  node of the second distance*/
				itmp = fscanf(fic,"%d",&Structure.Delta_h4);	/*second node of the second distance*/
				printf("There is calculation of the width and height of the structure between %d %d %d %d\n",Structure.Delta_h1,Structure.Delta_h2,Structure.Delta_h3,Structure.Delta_h4);
				}
			if (strcmp(chaine,"Curvature") == 0)
				{
				Structure.curvature = 1;
				printf("There is calculation of the curvature of elements.\n");
				}
			if (strcmp(chaine,"Energy_bottom_step") == 0)
				{
				itmp = fscanf(fic,"%lf",&Energy_bottom.step);
				printf("There is calculation of enrgy spent in bottom in dynamic. The calculation is done by squarre of %lf m side.\n",Energy_bottom.step);
				}
			if (strcmp(chaine,"eigenvalues") == 0)
				{
				itmp = fscanf(fic,"%d",&Structure.eigenvalues);
				if (Structure.eigenvalues <= 0)
					{
					printf("There is no calculation of eigenvalues\n");
					}
				if (Structure.eigenvalues > 1)
					{
					printf("There are calculation of %d eigenvalues\n",Structure.eigenvalues);
					}
				}
			if (strcmp(chaine,"foot_print") == 0)
				{
				printf("foot_print\n");
				Foot_print.nb = -1;
				}
			if (strcmp(chaine,"grid_drag") == 0)
				{
				itmp = fscanf(fic,"%lf",&Grid_drag.pas);	/*step along y and z axis in m*/
				printf("drag grid with a step of %lf m along y and z axis\n",Grid_drag.pas);
				Sortie_texte.panel_drag = 1;
				Sortie_texte.cable_drag = 1;
				}
			if (strcmp(chaine,"grid_drag_door") == 0)
				{
				if (Grid_drag.pas == 0) Grid_drag.pas = 1.0;	//in case the stap has not been defined
				Sortie_texte.panel_drag = 1;
				Sortie_texte.cable_drag = 1;
				itmp = fscanf(fic,"%d",&Grid_drag.nb_triangle);	/*number of triangles*/
				Grid_drag.vertex =		(int *) Malloc_int(1 + 3*Grid_drag.nb_triangle);
				for (zi = 1; zi<= 3*Grid_drag.nb_triangle; zi++)
					{
					itmp = fscanf(fic,"%d",&Grid_drag.vertex[zi]);	/*vertex of triangles*/
					}
				itmp = fscanf(fic,"%d",&Grid_drag.nb_type_point);	/*number of node types*/
				Grid_drag.type_point =		(int *) Malloc_int(1 + Grid_drag.nb_type_point);
				for (zi = 1; zi<= Grid_drag.nb_type_point; zi++)
					{
					itmp = fscanf(fic,"%d",&Grid_drag.type_point[zi]);	/*type of nodes*/
					}
				printf("%4d  triangles in the door\n",Grid_drag.nb_triangle);
				for (zi = 1; zi<= Grid_drag.nb_triangle; zi++)
					{
					printf("triangle %4d  nb_triangle %4d vertex %4d %4d %4d\n",zi,Grid_drag.nb_triangle,Grid_drag.vertex[3*zi-2],Grid_drag.vertex[3*zi-1],Grid_drag.vertex[3*zi-0]);
					}
				printf("%4d  node types in the door\n types:",Grid_drag.nb_type_point);
				for (zi = 1; zi<= Grid_drag.nb_type_point; zi++)
					{
					printf("  %4d",Grid_drag.type_point[zi]);
					}
				printf("\n");
				}
			if (strcmp(chaine,"cut_plan_symmetry") == 0)
				{
				itmp = fscanf(fic,"%d",&Structure.cut_plan_symmetry);	/*of the symmetry plan on which the intersection is calculated*/
				if (Structure.cut_plan_symmetry == 0) printf("intersection of triangular element of diamond netting with symmetry plan is not calculated\n");
				if (Structure.cut_plan_symmetry == 1) printf("intersection of triangular element of diamond netting with symmetry plan X is calculated\n");
				if (Structure.cut_plan_symmetry == 2) printf("intersection of triangular element of diamond netting with symmetry plan Y is calculated\n");
				if (Structure.cut_plan_symmetry == 3) printf("intersection of triangular element of diamond netting with symmetry plan Z is calculated\n");
				}
			if (strcmp(chaine,"hydro_forces") == 0)
				{
				Structure.hydro_forces = 1;
				printf("Structure.hydro_forces = %d\n",Structure.hydro_forces);
				}


			if (strcmp(chaine,"plan_cutting") == 0)
				{
				itmp = fscanf(fic,"%lf",&Plan_cutting.X0);	/*reading of the node position*/
				itmp = fscanf(fic,"%lf",&Plan_cutting.Y0);	/*reading of the node position*/
				itmp = fscanf(fic,"%lf",&Plan_cutting.Z0);	/*reading of the node position*/
				itmp = fscanf(fic,"%lf",&Plan_cutting.Xv);	/*reading of the plan normal*/
				itmp = fscanf(fic,"%lf",&Plan_cutting.Yv);	/*reading of the node position*/
				itmp = fscanf(fic,"%lf",&Plan_cutting.Zv);	/*reading of the node position*/
				Plan_cutting.nb_plan = 1;
				printf("output Plan_cutting node position %lf %lf %lf plan normal %lf %lf %lf\n",Plan_cutting.X0,Plan_cutting.Y0,Plan_cutting.Z0,Plan_cutting.Xv,Plan_cutting.Yv,Plan_cutting.Zv);
				}
			/* debut modifdp du 12 mars 2010*/
			if (strcmp(chaine,"vector_tension_bar") == 0)
				{
				Structure.nb_vector_tension_bar++;
				if (Structure.nb_vector_tension_bar == 1)
					{
					Vector_tension_bar.bar =		(int *) Malloc_int(1 + Structure.nb_vector_tension_bar);
      				 	}
      				 else
      				 	{
					Vector_tension_bar.bar =	(int *) Realloc_int(Vector_tension_bar.bar,1 + Structure.nb_vector_tension_bar);
      				 	}
				itmp = fscanf(fic,"%d",&Vector_tension_bar.bar[Structure.nb_vector_tension_bar]);	/*reading of number the bar element*/
				printf("output Vector_tension_bar %d\n",Vector_tension_bar.bar[Structure.nb_vector_tension_bar]);
				}
			/* fin modifdp du 12 mars 2010*/
			if (strcmp(chaine,"recouvrement_x_limit") == 0)
				{
				Structure.nb_recouvrement_x++;
				printf("lecture recouvrement_x_limit Structure.nb_recouvrement = %d\n",Structure.nb_recouvrement_x);
				if (Structure.nb_recouvrement_x == 1)
					{
       				 	/**********************************************/
       					Recouvrement_x.element1 = (int *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(int));
       					if (Recouvrement_x.element1    == NULL)
						{
						printf("Recouvrement_x.element1  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
       					Recouvrement_x.element2 = (int *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(int));
       					if (Recouvrement_x.element2    == NULL)
						{
						printf("Recouvrement_x.element2  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
      					Recouvrement_x.min = (double *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(double));
       					if (Recouvrement_x.min    == NULL)
						{
						printf("Recouvrement_x.min  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
     					Recouvrement_x.max = (double *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(double));
       					if (Recouvrement_x.max    == NULL)
						{
						printf("Recouvrement_x.max  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
     					Recouvrement_x.mean = (double *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(double));
       					if (Recouvrement_x.mean    == NULL)
						{
						printf("Recouvrement_x.mean  1 = NULL  \n" );
						exit(0);
						}
       				 	/**********************************************/
       					Recouvrement_x.flag_limit = (int *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(int));
       					if (Recouvrement_x.flag_limit    == NULL)
						{
						printf("Recouvrement_x.flag_limit  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
     					Recouvrement_x.limit = (double *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(double));
       					if (Recouvrement_x.limit    == NULL)
						{
						printf("Recouvrement_x.limit  1 = NULL  \n" );
						exit(0);
						}
       				 	/**********************************************/
 					}
				else
					{
					Recouvrement_x.element1 = 	(int *) Realloc_int(Recouvrement_x.element1,1 + Structure.nb_recouvrement_x);
					Recouvrement_x.element2 = 	(int *) Realloc_int(Recouvrement_x.element2,1 + Structure.nb_recouvrement_x);
					Recouvrement_x.min = 		(double *) Realloc_double(Recouvrement_x.min,1 + Structure.nb_recouvrement_x);
					Recouvrement_x.max = 		(double *) Realloc_double(Recouvrement_x.max,1 + Structure.nb_recouvrement_x);
					Recouvrement_x.mean = 		(double *) Realloc_double(Recouvrement_x.mean,1 + Structure.nb_recouvrement_x);
					Recouvrement_x.flag_limit = 	(int *) Realloc_int(Recouvrement_x.flag_limit,1 + Structure.nb_recouvrement_x);
					Recouvrement_x.limit = 		(double *) Realloc_double(Recouvrement_x.limit,1 + Structure.nb_recouvrement_x);
					}
				itmp = fscanf(fic,"%d",&Recouvrement_x.element1[Structure.nb_recouvrement_x]);	/*reading of the first element*/
				itmp = fscanf(fic,"%d",&Recouvrement_x.element2[Structure.nb_recouvrement_x]);	/*reading of the first element*/
				Recouvrement_x.min[Structure.nb_recouvrement_x] = 0.0;
				Recouvrement_x.max[Structure.nb_recouvrement_x] = 0.0;
				Recouvrement_x.mean[Structure.nb_recouvrement_x] = 0.0;
				Recouvrement_x.flag_limit[Structure.nb_recouvrement_x] = 1;
				itmp = fscanf(fic,"%lf",&Recouvrement_x.limit[Structure.nb_recouvrement_x]);	/*reading of the first element*/
				/*for (zi = 1; zi<=Structure.nb_recouvrement_x ; zi++)
					{
					printf("nb_recouvrement_x %d:",zi);
					printf("element1 %d  ",Recouvrement_x.element1[zi]);
					printf("element2 %d  ",Recouvrement_x.element2[zi]);
					printf("limit %lf\n",Recouvrement_x.limit[zi]);
					}*/
				}






			if (strcmp(chaine,"recouvrement_x") == 0)
				{
				printf("lecture recouvrement_x \n");
				Structure.nb_recouvrement_x++;
				if (Structure.nb_recouvrement_x == 1)
					{
       				 	/**********************************************/
       					Recouvrement_x.element1 = (int *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(int));
       					if (Recouvrement_x.element1    == NULL)
						{
						printf("Recouvrement_x.element1  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
       					Recouvrement_x.element2 = (int *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(int));
       					if (Recouvrement_x.element2    == NULL)
						{
						printf("Recouvrement_x.element2  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
      					Recouvrement_x.min = (double *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(double));
       					if (Recouvrement_x.min    == NULL)
						{
						printf("Recouvrement_x.min  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
     					Recouvrement_x.max = (double *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(double));
       					if (Recouvrement_x.max    == NULL)
						{
						printf("Recouvrement_x.max  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
     					Recouvrement_x.mean = (double *) malloc((1 + Structure.nb_recouvrement_x) * sizeof(double));
       					if (Recouvrement_x.mean    == NULL)
						{
						printf("Recouvrement_x.mean  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
					}
				else
					{
					Recouvrement_x.element1 = 	(int *) Realloc_int(Recouvrement_x.element1,1 + Structure.nb_recouvrement_x);
					Recouvrement_x.element2 = 	(int *) Realloc_int(Recouvrement_x.element2,1 + Structure.nb_recouvrement_x);
					Recouvrement_x.min = 		(double *) Realloc_double(Recouvrement_x.min,1 + Structure.nb_recouvrement_x);
					Recouvrement_x.max = 		(double *) Realloc_double(Recouvrement_x.max,1 + Structure.nb_recouvrement_x);
					Recouvrement_x.mean = 		(double *) Realloc_double(Recouvrement_x.mean,1 + Structure.nb_recouvrement_x);
					}
				itmp = fscanf(fic,"%d",&Recouvrement_x.element1[Structure.nb_recouvrement_x]);	/*reading of the first element*/
				itmp = fscanf(fic,"%d",&Recouvrement_x.element2[Structure.nb_recouvrement_x]);	/*reading of the first element*/
				Recouvrement_x.min[Structure.nb_recouvrement_x] = 0.0;
				Recouvrement_x.max[Structure.nb_recouvrement_x] = 0.0;
				Recouvrement_x.mean[Structure.nb_recouvrement_x] = 0.0;
				for (zi = 1; zi<=Structure.nb_recouvrement_x ; zi++)
					{
					printf("nb_recouvrement_x %d:",zi);
					printf("element1 %d  ",Recouvrement_x.element1[zi]);
					printf("element2 %d\n",Recouvrement_x.element2[zi]);
					/*
					*/
					}
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
			if (strcmp(chaine,"homothety") == 0)
				{
				itmp = fscanf(fic,"%lf",&tmp_d1);
				printf("homothety at %lf\n",tmp_d1);
				}
			if (strcmp(chaine,"black_drawing") == 0)
				{
				printf("black_drawing\n");
				}
			if (strcmp(chaine,"panel_drag") == 0)
				{
				Sortie_texte.panel_drag = 1;
				printf("display of panel_drag %d\n",Sortie_texte.panel_drag);
				}
			if (strcmp(chaine,"triangle_drag") == 0)
				{
				Sortie_texte.triangle_drag = 1;
				printf("display of triangle_drag %d\n",Sortie_texte.triangle_drag);
				}
			if (strcmp(chaine,"cable_drag") == 0)
				{
				Sortie_texte.cable_drag = 1;
				printf("display of cable_drag %d\n",Sortie_texte.cable_drag);
				}
			if (strcmp(chaine,"bottom_drag") == 0)
				{
				Sortie_texte.bottom_drag = 1;
				printf("display of bottom_drag %d\n",Sortie_texte.bottom_drag);
				}
			if (strcmp(chaine,"catch_drag") == 0)
				{
				Sortie_texte.catch_drag = 1;
				printf("display of catch_drag %d\n",Sortie_texte.catch_drag);
				}
			if (strcmp(chaine,"element_drag") == 0)
				{
				Sortie_texte.element_drag = 1;
				printf("display of element_drag %d\n",Sortie_texte.element_drag);
				}
			if (strcmp(chaine,"surface_drag") == 0)
				{
				Sortie_texte.surface_drag = 1;
				printf("display of surface_drag %d\n",Sortie_texte.surface_drag);
				}
			if (strcmp(chaine,"node_drag") == 0)
				{
				Sortie_texte.node_drag = 1;
				printf("display of node_drag %d \n",Sortie_texte.node_drag);
				}
			if (strcmp(chaine,"bar_tension") == 0)
				{
				Sortie_texte.bar_tension = 1;
				printf("display of bar_tension in dynamics %d\n",Sortie_texte.bar_tension);
				}
			if (strcmp(chaine,"diamond_tension") == 0)
				{
				Sortie_texte.diamond_tension = 1;
				printf("display of diamond_tension in dynamics %d\n",Sortie_texte.diamond_tension);
				}
			if (strcmp(chaine,"catch_diameter") == 0)
				{
				Sortie_texte.diametre_prise = 1;
				printf("lecture de catch_diameter %d\n",Sortie_texte.diametre_prise);
				}
			if (strcmp(chaine,"catch_volume") == 0)
				{
				Sortie_texte.volume_capture = 1;
				printf("lecture de catch_volume %d\n",Sortie_texte.volume_capture);
				}
			if (strcmp(chaine,"cable_length") == 0)
				{
				printf("lecture de cable_length ");
				Sortie_texte.nb_longueur_cable++;
				if (Sortie_texte.nb_longueur_cable == 1)
					{
     				 	/**********************************************/
       					Sortie_texte.element_longueur_cable = (int *) malloc((1 + Sortie_texte.nb_longueur_cable) * sizeof(int));
       					if (Sortie_texte.element_longueur_cable    == NULL)
            				   {
              				 printf("Sortie_texte.element_longueur_cable  1 = NULL  \n" );
              				 exit(0);
              				 }
      				 	/**********************************************/
       					Sortie_texte.decimale_longueur_cable = (int *) malloc((1 + Sortie_texte.nb_longueur_cable) * sizeof(int));
       					if (Sortie_texte.decimale_longueur_cable    == NULL)
            				   {
             				  printf("Sortie_texte.decimale_longueur_cable  1 = NULL  \n" );
             				  exit(0);
             				  }
       				 	/**********************************************/
       					Sortie_texte.valeur_longueur_cable = (double *) malloc((1 + Sortie_texte.nb_longueur_cable) * sizeof(double));
       					if (Sortie_texte.valeur_longueur_cable    == NULL)
            				   {
             				  printf("Sortie_texte.valeur_longueur_cable  1 = NULL  \n" );
             				  exit(0);
             				  }
      				 	/**********************************************/
					Sortie_texte.comment_longueur_cable =	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_longueur_cable);
					}
				else
					{
					Sortie_texte.element_longueur_cable =	(int *) Realloc_int(Sortie_texte.element_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
					Sortie_texte.decimale_longueur_cable = 	(int *) Realloc_int(Sortie_texte.decimale_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
					Sortie_texte.valeur_longueur_cable = 	(double *) Realloc_double(Sortie_texte.valeur_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
					Sortie_texte.comment_longueur_cable =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
					}
				i = lecture_commentaire(fic,comment);
				if (i == 0) printf("erreur dans l enonce de la longueur de cable\n");
 
				/*lecture du commentaire entre "*/
				for (zi=0;zi<=strlen(comment);zi++)
					Sortie_texte.comment_longueur_cable[Sortie_texte.nb_longueur_cable].texte[zi] = comment[zi];
				/*lecture du numero (int) de l element entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&Sortie_texte.element_longueur_cable[Sortie_texte.nb_longueur_cable]);
				/*lecture du nb (int) de decimale pour l affichage entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&Sortie_texte.decimale_longueur_cable[Sortie_texte.nb_longueur_cable]);
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
				if (Sortie_texte.nb_energie_elong_diamond == 1)
					{
					/*Sortie_texte.panneau_energie_elong =	(int *) Malloc_int(1 + Sortie_texte.nb_energie_elong_diamond);*/
					/**********************************************/
					Sortie_texte.panneau_energie_elong = (int *) malloc((1 + Sortie_texte.nb_energie_elong_diamond) * sizeof(int));
					if (Sortie_texte.panneau_energie_elong    == NULL)
						{
						printf("Sortie_texte.panneau_energie_elong  1 = NULL  \n" );
						exit(0);
						}
					/**********************************************/
					/*Sortie_texte.decimale_energie_elong = 	(int *) Malloc_int(1 + Sortie_texte.nb_energie_elong_diamond);*/
					/**********************************************/
					Sortie_texte.decimale_energie_elong = (int *) malloc((1 + Sortie_texte.nb_energie_elong_diamond) * sizeof(int));
					if (Sortie_texte.decimale_energie_elong     == NULL)
						{
						printf("Sortie_texte.decimale_energie_elong   1 = NULL  \n" );
						exit(0);
						}
					/**********************************************/
					Sortie_texte.comment_energie_elong_diamond =	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_energie_elong_diamond);
					}
				else
					{
					Sortie_texte.panneau_energie_elong =	(int *) Realloc_int(Sortie_texte.panneau_energie_elong,1 + Sortie_texte.nb_energie_elong_diamond);
					Sortie_texte.decimale_energie_elong = 	(int *) Realloc_int(Sortie_texte.decimale_energie_elong,1 + Sortie_texte.nb_energie_elong_diamond);
					Sortie_texte.comment_energie_elong_diamond =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_energie_elong_diamond,1 + Sortie_texte.nb_energie_elong_diamond);
					}
				i = lecture_commentaire(fic,comment);
				if (i == 0) printf("erreur dans l enonce de l ernegie d elongation filet losange\n");
 
				/*lecture du commentaire entre "*/
				for (zi=0;zi<=strlen(comment);zi++)
					Sortie_texte.comment_energie_elong_diamond[Sortie_texte.nb_energie_elong_diamond].texte[zi] = comment[zi];
				/*lecture du numero (int) du panneau entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&Sortie_texte.panneau_energie_elong[Sortie_texte.nb_energie_elong_diamond]);
				/*lecture du nb (int) de decimale pour l affichage entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&Sortie_texte.decimale_energie_elong[Sortie_texte.nb_energie_elong_diamond]);
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
				if (Sortie_texte.nb_energie_fold_diamond == 1)
					{
					/**********************************************/
					Sortie_texte.panneau_energie_fold= (int *) malloc((1 + Sortie_texte.nb_energie_fold_diamond) * sizeof(int));
					if (Sortie_texte.panneau_energie_fold    == NULL)
						{
						printf("Sortie_texte.panneau_energie_fold  1 = NULL  \n" );
						exit(0);
						}
					/**********************************************/
					Sortie_texte.decimale_energie_fold= (int *) malloc((1 + Sortie_texte.nb_energie_fold_diamond) * sizeof(int));
					if (Sortie_texte.decimale_energie_fold    == NULL)
						{
						printf("Sortie_texte.decimale_energie_fold  1 = NULL  \n" );
						exit(0);
						}
					/**********************************************/
					Sortie_texte.comment_energie_fold_diamond =	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_energie_fold_diamond);
					}
				else
					{
					Sortie_texte.panneau_energie_fold =	(int *) Realloc_int(Sortie_texte.panneau_energie_fold,1 + Sortie_texte.nb_energie_fold_diamond);
					Sortie_texte.decimale_energie_fold = 	(int *) Realloc_int(Sortie_texte.decimale_energie_fold,1 + Sortie_texte.nb_energie_fold_diamond);
					Sortie_texte.comment_energie_fold_diamond =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_energie_fold_diamond,1 + Sortie_texte.nb_energie_fold_diamond);
					}
				i = lecture_commentaire(fic,comment);
				if (i == 0) printf("erreur dans l enonce de l ernegie d foldation filet losange\n");
 
				/*lecture du commentaire entre "*/
				for (zi=0;zi<=strlen(comment);zi++)
					Sortie_texte.comment_energie_fold_diamond[Sortie_texte.nb_energie_fold_diamond].texte[zi] = comment[zi];
				/*lecture du numero (int) du panneau entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&Sortie_texte.panneau_energie_fold[Sortie_texte.nb_energie_fold_diamond]);
				/*lecture du nb (int) de decimale pour l affichage entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&Sortie_texte.decimale_energie_fold[Sortie_texte.nb_energie_fold_diamond]);
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
				if (Sortie_texte.nb_energie_open_diamond == 1)
					{
					/**********************************************/
					Sortie_texte.panneau_energie_open= (int *) malloc((1 + Sortie_texte.nb_energie_open_diamond) * sizeof(int));
					if (Sortie_texte.panneau_energie_open    == NULL)
						{
						printf("Sortie_texte.panneau_energie_open  1 = NULL  \n" );
						exit(0);
						}
					/**********************************************/
					Sortie_texte.decimale_energie_open= (int *) malloc((1 + Sortie_texte.nb_energie_open_diamond) * sizeof(int));
					if (Sortie_texte.decimale_energie_open    == NULL)
						{
						printf("Sortie_texte.decimale_energie_open  1 = NULL  \n" );
						exit(0);
						}
					/**********************************************/
					Sortie_texte.comment_energie_open_diamond =	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_energie_open_diamond);
					}
				else
					{
					Sortie_texte.panneau_energie_open =	(int *) Realloc_int(Sortie_texte.panneau_energie_open,1 + Sortie_texte.nb_energie_open_diamond);
					Sortie_texte.decimale_energie_open = 	(int *) Realloc_int(Sortie_texte.decimale_energie_open,1 + Sortie_texte.nb_energie_open_diamond);
					Sortie_texte.comment_energie_open_diamond =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_energie_open_diamond,1 + Sortie_texte.nb_energie_open_diamond);
					}
				i = lecture_commentaire(fic,comment);
				if (i == 0) printf("erreur dans l enonce de l ernegie d openation filet losange\n");
 
				/*lecture du commentaire entre "*/
				for (zi=0;zi<=strlen(comment);zi++)
					Sortie_texte.comment_energie_open_diamond[Sortie_texte.nb_energie_open_diamond].texte[zi] = comment[zi];
				/*lecture du numero (int) du panneau entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&Sortie_texte.panneau_energie_open[Sortie_texte.nb_energie_open_diamond]);
				/*lecture du nb (int) de decimale pour l affichage entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&Sortie_texte.decimale_energie_open[Sortie_texte.nb_energie_open_diamond]);
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
				itmp = fscanf(fic,"%d",&Sortie_texte.panneau_energie_contact[Sortie_texte.nb_energie_contact_diamond]);
				/*lecture du nb (int) de decimale pour l affichage entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&Sortie_texte.decimale_energie_contact[Sortie_texte.nb_energie_contact_diamond]);
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
				itmp = fscanf(fic,"%d",&temp_int);
				printf("no_visible_surface nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					itmp = fscanf(fic,"%d",&temp2_int);
					/*panneau[temp2_int].flag_dessin = 0;*/					
					}
				}
			if (strcmp(chaine,"no_visible_surface_hexa") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				printf("no_visible_surface_hexa nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					itmp = fscanf(fic,"%d",&temp2_int);
					/*pan_hexa[temp2_int].flag_dessin = 0;*/					
					}
				}
			if (strcmp(chaine,"no_visible_element") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				printf("no_visible_element nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					itmp = fscanf(fic,"%d",&temp2_int);
					/*element[temp2_int].flag_dessin = 0;*/					
					}
				}
			if (strcmp(chaine,"no_visible_element_window") == 0)
				{
				itmp = fscanf(fic,"%lf",&tmp_d1);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				printf("no_visible_element_window:  \n");
				/*for (pa=1;pa<=chalut.nb_element;pa++)
					{
					for (no=1;no<=2;no++)
						{
						if ((noeud[element[pa].extremite[no]].x > txmin) && (noeud[element[pa].extremite[no]].x < txmax))
							{
							if ((noeud[element[pa].extremite[no]].y > tymin) && (noeud[element[pa].extremite[no]].y < tymax))
								{
								if ((noeud[element[pa].extremite[no]].z > tzmin) && (noeud[element[pa].extremite[no]].z < tzmax))
									{
									element[pa].flag_dessin = 0;				
									}
								}
							}
						}
					}*/
				}
			if (strcmp(chaine,"no_visible_coulisse") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				printf("no_visible_coulisse nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					itmp = fscanf(fic,"%d",&temp2_int);
					/*coulisse[temp2_int].flag_dessin = 0;/**/					
					}
				}
			if (strcmp(chaine,"no_visible_winch") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				printf("no_visible_winch nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					itmp = fscanf(fic,"%d",&temp2_int);
					/*winch[temp2_int].flag_dessin = 0;/**/					
					}
				}
	  		if (strcmp(chaine,"orientation_netting") == 0)
	    			{
				itmp = fscanf(fic,"%d",&Orientation_netting.nb_panel);
				printf("opening nb_panel %d \n",Orientation_netting.nb_panel);
  				/*Orientation_netting.panel =	(int *) Malloc_int(1 + Orientation_netting.nb_panel);*/
				/**********************************************/
				Orientation_netting.panel= (int *) malloc((1 + Orientation_netting.nb_panel) * sizeof(int));
				if (Orientation_netting.panel    == NULL)
					{
					printf("Orientation_netting.panel  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				printf("opening panel : ");
	      			for (pa=1;pa<=Orientation_netting.nb_panel;pa++)
					{
		  			itmp = fscanf(fic,"%d",&Orientation_netting.panel[pa]);
		  			printf(" %d ",Orientation_netting.panel[pa]);
					}
				printf(" \n");
				itmp = fscanf(fic,"%lf",&Orientation_netting.pas);
				printf("opening pas %lf \n",Orientation_netting.pas);
				Orientation_netting.nb_tab = (int) 90.0 / Orientation_netting.pas;
	      			printf("calculation of the opening angle by panel\n");
	      		
       				/*allocation de la matrice tab_mesh*/
				n_ligne 	= Orientation_netting.nb_panel + 1;
       				p_colonne 	= Orientation_netting.nb_tab + 1;
       
       				xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
				Orientation_netting.tab_mesh = (double **) malloc (n_ligne * sizeof(double *));	if (Orientation_netting.tab_mesh	 == NULL){printf("Orientation_netting.tab_mesh	= NULL \n" );exit(0);}
  				cmat = xmat;
  				for (zk=0;zk<n_ligne;zk++)
  					{
  					Orientation_netting.tab_mesh[zk] = cmat;
  					cmat += p_colonne;
					}
				
       				/*allocation de la matrice tab_netting*/
				n_ligne 	= Orientation_netting.nb_panel + 1;
       				p_colonne 	= Orientation_netting.nb_tab + 1;
       
       				xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
				Orientation_netting.tab_netting = (double **) malloc (n_ligne * sizeof(double *));	if (Orientation_netting.tab_netting	 == NULL){printf("Orientation_netting.tab_netting	= NULL \n" );exit(0);}
  				cmat = xmat;
  				for (zk=0;zk<n_ligne;zk++)
  					{
  					Orientation_netting.tab_netting[zk] = cmat;
  					cmat += p_colonne;
					}
				
       				/*allocation de la matrice tab_netting*/
				n_ligne 	= Orientation_netting.nb_panel + 1;
       				p_colonne 	= Orientation_netting.nb_tab + 1;
       
       				xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
				Orientation_netting.tab_drag = (double **) malloc (n_ligne * sizeof(double *));	if (Orientation_netting.tab_drag	 == NULL){printf("Orientation_netting.tab_drag	= NULL \n" );exit(0);}
  				cmat = xmat;
  				for (zk=0;zk<n_ligne;zk++)
  					{
  					Orientation_netting.tab_drag[zk] = cmat;
  					cmat += p_colonne;
					}
				
	 		   	}
	  		if (strcmp(chaine,"opening_angle") == 0)
	    			{
				itmp = fscanf(fic,"%d",&Opening_angle.nb_panel);
				printf("opening nb_panel %d \n",Opening_angle.nb_panel);
  				/*Opening_angle.panel =	(int *) Malloc_int(1 + Opening_angle.nb_panel);*/
				/**********************************************/
				Opening_angle.panel= (int *) malloc((1 + Opening_angle.nb_panel) * sizeof(int));
				if (Opening_angle.panel    == NULL)
					{
					printf("Opening_angle.panel  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				printf("opening panel : ");
	      			for (pa=1;pa<=Opening_angle.nb_panel;pa++)
					{
		  			itmp = fscanf(fic,"%d",&Opening_angle.panel[pa]);
		  			printf(" %d ",Opening_angle.panel[pa]);
					}
				printf(" \n");
				itmp = fscanf(fic,"%lf",&Opening_angle.pas);
				printf("opening pas %lf \n",Opening_angle.pas);
				Opening_angle.nb_tab = (int) 90.0 / Opening_angle.pas;
	      			printf("calculation of the opening angle by panel\n");
	      		
       				/*allocation de la matrice tab*/
				n_ligne 	= Opening_angle.nb_panel + 1;
       				p_colonne 	= Opening_angle.nb_tab + 1;
       
       				xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
				Opening_angle.tab = (double **) malloc (n_ligne * sizeof(double *));	if (Opening_angle.tab	 == NULL){printf("Opening_angle.tab	= NULL \n" );exit(0);}
  				cmat = xmat;
  				for (zk=0;zk<n_ligne;zk++)
  					{
  					Opening_angle.tab[zk] = cmat;
  					cmat += p_colonne;
					}
				
				/*Opening_angle.tab =        (double *) Malloc_double(1 + Opening_angle.nb_tab);*/
	 		   	}
	  		if (strcmp(chaine,"opening_mesh") == 0)
	    			{
				itmp = fscanf(fic,"%d",&Opening_mesh.nb_panel);
				printf("opening nb_panel %d \n",Opening_mesh.nb_panel);
  				/*Opening_mesh.panel =	(int *) Malloc_int(1 + Opening_mesh.nb_panel);*/
				/**********************************************/
				Opening_mesh.panel= (int *) malloc((1 + Opening_mesh.nb_panel) * sizeof(int));
				if (Opening_mesh.panel    == NULL)
					{
					printf("Opening_mesh.panel  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				printf("opening panel : ");
	      			for (pa=1;pa<=Opening_mesh.nb_panel;pa++)
					{
		  			itmp = fscanf(fic,"%d",&Opening_mesh.panel[pa]);
		  			printf(" %d ",Opening_mesh.panel[pa]);
					}
				printf(" \n");
				itmp = fscanf(fic,"%lf",&Opening_mesh.pas);
				printf("opening pas %lf \n",Opening_mesh.pas);
				/*Opening_mesh.nb_tab = (int) 90.0 / Opening_mesh.pas;*/
	      			printf("calculation of the opening mesh surface by panel\n");
	      		
       				/*allocation de la matrice tab*/
				/*n_ligne 	= Opening_mesh.nb_panel + 1;
       				p_colonne 	= Opening_mesh.nb_tab + 1;
       
       				xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
				Opening_mesh.tab = (double **) malloc (n_ligne * sizeof(double *));	if (Opening_mesh.tab	 == NULL){printf("Opening_mesh.tab	= NULL \n" );exit(0);}
  				cmat = xmat;
  				for (zk=0;zk<n_ligne;zk++)
  					{
  					Opening_mesh.tab[zk] = cmat;
  					cmat += p_colonne;
					}*/
				
				/*Opening_mesh.tab =        (double *) Malloc_double(1 + Opening_mesh.nb_tab);*/
	 		   	}
	  		if (strcmp(chaine,"opening_angle_stripe") == 0)
	    			{
				itmp = fscanf(fic,"%d",&Opening_angle_stripe.nb_panel);
				printf("opening nb_panel %d \n",Opening_angle_stripe.nb_panel);
  				/*Opening_angle_stripe.panel =	(int *) Malloc_int(1 + Opening_angle_stripe.nb_panel);*/
				/**********************************************/
				Opening_angle_stripe.panel= (int *) malloc((1 + Opening_angle_stripe.nb_panel) * sizeof(int));
				if (Opening_angle_stripe.panel    == NULL)
					{
					printf("Opening_angle_stripe.panel  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				printf("opening panel : ");
	      			for (pa=1;pa<=Opening_angle_stripe.nb_panel;pa++)
					{
		  			itmp = fscanf(fic,"%d",&Opening_angle_stripe.panel[pa]);
		  			printf(" %d ",Opening_angle_stripe.panel[pa]);
					}
				printf(" \n");
				itmp = fscanf(fic,"%lf",&Opening_angle_stripe.pas);
				printf("opening stripe pas (deg.) %lf \n",Opening_angle_stripe.pas);
				Opening_angle_stripe.nb_tab = (int) 90.0 / Opening_angle_stripe.pas;
				itmp = fscanf(fic,"%lf",&Opening_angle_stripe.stripe_step);
				printf("opening stripe step (m) %lf \n",Opening_angle_stripe.stripe_step);
	      			printf("calculation of the opening angle by stripe\n");
	      		
       				/*allocation de la matrice tab*/
				/*n_ligne 	= Opening_angle_stripe.nb_panel + 1;
       				p_colonne 	= Opening_angle_stripe.nb_tab + 1;
       
       				xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
				Opening_angle_stripe.tab = (double **) malloc (n_ligne * sizeof(double *));	if (Opening_angle_stripe.tab	 == NULL){printf("Opening_angle_stripe.tab	= NULL \n" );exit(0);}
  				cmat = xmat;
  				for (zk=0;zk<n_ligne;zk++)
  					{
  					Opening_angle_stripe.tab[zk] = cmat;
  					cmat += p_colonne;
					}*/
				
				/*Opening_angle_stripe.tab =        (double *) Malloc_double(1 + Opening_angle_stripe.nb_tab);*/
	 		   	}
			if (strcmp(chaine,"meridian") == 0)
				{
				printf("calculation of the meridian\n");
				Sortie_texte.meridian = 1;
				/*reading of the nb of panels (int) used by the meridian : between 2 spaces !!*/
				itmp = fscanf(fic,"%d",&Prise.nb_panel_meridian);
				printf("Prise.nb_panel_meridian %d \n",Prise.nb_panel_meridian);
				/*Prise.panel_meridian =	(int *) Malloc_int(1 + Prise.nb_panel_meridian);*/
				/**********************************************/
				Prise.panel_meridian= (int *) malloc((1 + Prise.nb_panel_meridian) * sizeof(int));
				if (Prise.panel_meridian    == NULL)
					{
					printf("Prise.panel_meridian  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				for (pa=1;pa<=Prise.nb_panel_meridian;pa++)
					{
					itmp = fscanf(fic,"%d",&Prise.panel_meridian[pa]);
					printf("meridian panel %d \n",Prise.panel_meridian[pa]);
					}
				}
			if (strcmp(chaine,"meridian_X") == 0)
				{
				if (Sortie_texte.meridian == 0)
					{
					printf("calculation of the meridian : nodes of symmetry / X\n");
					Sortie_texte.meridian_X = 1;
					}
				else
					{
					printf("WARNING! this calculation of the meridian : nodes of symmetry / X will not be done\n");
					printf("because a previous one will be done\n");
					}
				}
			if (strcmp(chaine,"meridian_Y") == 0)
				{
				if ((Sortie_texte.meridian == 0) && (Sortie_texte.meridian_X == 0))
					{
					printf("calculation of the meridian : nodes of symmetry / Y\n");
					Sortie_texte.meridian_Y = 1;
					}
				else
					{
					printf("WARNING! this calculation of the meridian : nodes of symmetry / Y will not be done\n");
					printf("because a previous one will be done\n");
					}
				}
			if (strcmp(chaine,"meridian_Z") == 0)
				{
				if ((Sortie_texte.meridian == 0) && (Sortie_texte.meridian_X == 0) && (Sortie_texte.meridian_Y == 0))
					{
					printf("calculation of the meridian : nodes of symmetry / Z\n");
					Sortie_texte.meridian_Z = 1;
					}
				else
					{
					printf("WARNING! this calculation of the meridian : nodes of symmetry / Z will not be done\n");
					printf("because a previous one will be done\n");
					}
				}
			if (strcmp(chaine,"curvilinear_codend_length") == 0)
				{
				printf("calculation of the curvilinear_codend_length\n");
				Sortie_texte.curvilinear_codend_length = 1;
				/*reading of the nb of panels (int) used by the meridian : between 2 spaces !!*/
				itmp = fscanf(fic,"%d",&Prise.nb_panel_curvilinear);
				printf("Prise.nb_panel_curvilinear %d \n",Prise.nb_panel_curvilinear);
				/*Prise.panel_curvilinear =	(int *) Malloc_int(1 + Prise.nb_panel_curvilinear);*/
				/**********************************************/
				Prise.panel_curvilinear= (int *) malloc((1 +Prise.nb_panel_curvilinear ) * sizeof(int));
				if (Prise.panel_curvilinear    == NULL)
					{
					printf("Prise.panel_curvilinear  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				for (pa=1;pa<=Prise.nb_panel_curvilinear;pa++)
					{
					itmp = fscanf(fic,"%d",&Prise.panel_curvilinear[pa]);
					printf("curvilinear panel %d \n",Prise.panel_curvilinear[pa]);
					}
				}
			if (strcmp(chaine,"panels") == 0)
				{
				itmp = fscanf(fic,"%d",&Prise.panels[1]);
				itmp = fscanf(fic,"%d",&Prise.panels[2]);
				printf("calculation of the limit between panels %d %d\n",Prise.panels[1],Prise.panels[2]);
				}
			if (strcmp(chaine,"nb_mesh_front") == 0)
				{
				itmp = fscanf(fic,"%d",&Prise.dir_mesh_front);
				printf("calculation of the front in nb of mesh along the dir %d (1:U, 2:V)\n",Prise.dir_mesh_front);
				}
			}

		if (strcmp(chaine,"input") == 0)
			{
			/*printf("lecture d input  ");*/
			//printf("%s  \n",chaine);/**/
			i = lecture_chaine(fic,chaine);
			//printf("%s  \n",chaine);/**/
			if (strcmp(chaine,"netting2ropes") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				itmp = fscanf(fic,"%d",&panneau[temp_int].netting_2_ropes_period);
				itmp = fscanf(fic,"%lf",&panneau[temp_int].netting_2_ropes_gap_U);
				itmp = fscanf(fic,"%lf",&panneau[temp_int].netting_2_ropes_gap_V);
				itmp = fscanf(fic,"%lf",&panneau[temp_int].netting_2_ropes_accuracy);
				itmp = fscanf(fic,"%d",&panneau[temp_int].netting_2_ropes_bar_nb);
				panneau[temp_int].type_maillage = 4;
				printf("netting2ropes panel %d\n",temp_int);
				printf("type_maillage %d\n",panneau[temp_int].type_maillage);
				printf("netting_2_ropes_period %d	",panneau[temp_int].netting_2_ropes_period);
				printf("netting_2_ropes_gap_U %lf	",panneau[temp_int].netting_2_ropes_gap_U);
				printf("netting_2_ropes_gap_V %lf\n",panneau[temp_int].netting_2_ropes_gap_V);
				printf("netting_2_ropes_accuracy %lf meshe\n",panneau[temp_int].netting_2_ropes_accuracy);
				printf("netting_2_ropes_bar_nb %d\n",panneau[temp_int].netting_2_ropes_bar_nb);
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
				TypeNoeud[node_type].fextx = Fd*cos(PI/180*Courant.direction) - Fl*sin(PI/180*Courant.direction);
				TypeNoeud[node_type].fexty = Fd*sin(PI/180*Courant.direction) + Fl*cos(PI/180*Courant.direction);
				TypeNoeud[node_type].fextz = 0.5*RHO*foil_cz*actual_foil_surface*Courant.vitesse*Courant.vitesse;
				printf("TypeNoeud[%d].fextxyz (N)	%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].fextx,TypeNoeud[node_type].fexty,TypeNoeud[node_type].fextz);	
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
				TypeNoeud[node_type].lonx = pow(actual_volume,1.0/3.0);	TypeNoeud[node_type].lony = pow(actual_volume,1.0/3.0);	TypeNoeud[node_type].lonz = pow(actual_volume,1.0/3.0);
				TypeNoeud[node_type].cdx = 0.0;				TypeNoeud[node_type].cdy = 0.0;				TypeNoeud[node_type].cdz = 0.0;
				Fd = 0.5*RHO*foil_cd*actual_foil_surface*Courant.vitesse*Courant.vitesse;
				Fl = 0.5*RHO*foil_cl*actual_foil_surface*Courant.vitesse*Courant.vitesse;
				TypeNoeud[node_type].fextx = Fd*cos(PI/180*Courant.direction) - Fl*sin(PI/180*Courant.direction);
				TypeNoeud[node_type].fexty = Fd*sin(PI/180*Courant.direction) + Fl*cos(PI/180*Courant.direction);
				TypeNoeud[node_type].fextz = 0.5*RHO*foil_cz*actual_foil_surface*Courant.vitesse*Courant.vitesse;
				printf("TypeNoeud[%d].mxyz (N)		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].mx,TypeNoeud[node_type].my,TypeNoeud[node_type].mz);	
				printf("TypeNoeud[%d].majxyz (N)		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].majx,TypeNoeud[node_type].majy,TypeNoeud[node_type].majz);	
				printf("TypeNoeud[%d].lonxyz (m)		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].lonx,TypeNoeud[node_type].lony,TypeNoeud[node_type].lonz);	
				printf("TypeNoeud[%d].cdxyz		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].cdx,TypeNoeud[node_type].cdy,TypeNoeud[node_type].cdz);	
				printf("TypeNoeud[%d].fextxyz (N)	%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].fextx,TypeNoeud[node_type].fexty,TypeNoeud[node_type].fextz);	
				printf("Fd (N)				%lf 	Fl (N)		%lf\n",Fd,Fl);	
				}
			if (strcmp(chaine,"openfoam") == 0)
				{
				itmp = fscanf(fic, "%s", Structure.pathOFc);
			 	Structure.openfoam = 1;
				printf("openfoam path %s\n",Structure.pathOFc);
				}
			if (strcmp(chaine,"cable_contact") == 0)
				{
				Structure.nb_cable_contact++;
				itmp = fscanf(fic, "%d", &zi);
				itmp = fscanf(fic, "%d", &zj);
				if (zi < zj)
					{
					if (TypeElement[zi].nb_cable_contact == 0)
						{
						TypeElement[zi].nb_cable_contact++;	
						TypeElement[zi].cable_contact = (int *) Malloc_int(1);	
						TypeElement[zi].cable_contact[TypeElement[zi].nb_cable_contact] = zj;
						}
					else
						{
						TypeElement[zi].nb_cable_contact++;	
						TypeElement[zi].cable_contact = Realloc_int (TypeElement[zi].cable_contact,TypeElement[zi].nb_cable_contact);
						TypeElement[zi].cable_contact[TypeElement[zi].nb_cable_contact] = zj;
						}
					}
				if (zi > zj)
					{
					if (TypeElement[zj].nb_cable_contact == 0)
						{
						TypeElement[zj].nb_cable_contact++;	
						TypeElement[zj].cable_contact = (int *) Malloc_int(1);	
						TypeElement[zj].cable_contact[TypeElement[zi].nb_cable_contact] = zi;
						}						
					else
						{
						TypeElement[zj].nb_cable_contact++;	
						TypeElement[zj].cable_contact = Realloc_int (TypeElement[zj].cable_contact,TypeElement[zj].nb_cable_contact);
						TypeElement[zj].cable_contact[TypeElement[zj].nb_cable_contact] = zi;
						}
					}
				printf("Cables %d and %d could be in contact no %d\n",zi,zj,Structure.nb_cable_contact);
				}
			if (strcmp(chaine,"wave_model") == 0)
				{
				itmp = fscanf(fic, "%d", &Structure.wave_model);
				if (Structure.wave_model == 1) printf("The wave model is Airy intermediate depth\n");
				if (Structure.wave_model == 2) printf("The wave model is Stokes 2d order intermediate or infinite depth\n");
				if (Structure.wave_model == 3) printf("The wave model is Stokes 3d order infinite depth\n");
				}
			if (strcmp(chaine,"slider") == 0)
				{
				Structure.nb_slider++;
		    		//printf("Structure.nb_slider %d *****************\n",Structure.nb_slider);
				no = Structure.nb_slider;
				itmp = fscanf(fic,"%d",&Slider[no].nb_bar);
				printf("Slider %d has %d elements :",no,Slider[no].nb_bar);
				Slider[no].barre =	(int *)    Malloc_int(1 + Slider[no].nb_bar);
		    		//printf("*****************\n");
				for (zi=1;zi<=Slider[no].nb_bar;zi++)
					{
					itmp = fscanf(fic,"%d",&Slider[no].barre[zi]);
					TypeElement[Slider[no].barre[zi]].slider = no;	//this element is part of a slider
		    			//printf("********nb_slider %d barre %d slider %d *********\n",no,Slider[no].barre[zi],TypeElement[Slider[no].barre[zi]].slider);
					printf(" %d",Slider[no].barre[zi]);
					}
		    		printf("\n");
		    		
				Slider[no].diametremeca = TypeElement[Slider[no].barre[1]].diametremeca;
				Slider[no].raideur_traction = TypeElement[Slider[no].barre[1]].raideur_traction;
				Slider[no].raideur_compression = TypeElement[Slider[no].barre[1]].raideur_compression;
				Slider[no].lgrepos = TypeElement[Slider[no].barre[1]].lgrepos;
				Slider[no].diametrehydro = TypeElement[Slider[no].barre[1]].diametrehydro;
				Slider[no].rhoelement = TypeElement[Slider[no].barre[1]].rhoelement;
				Slider[no].cdnormal = TypeElement[Slider[no].barre[1]].cdnormal;
				Slider[no].ftangent = TypeElement[Slider[no].barre[1]].ftangent;

		    		//printf("el1 %d \n",Slider[no].barre[1]);
		    		//printf("Slider[no].raideur_compression %lf \n",Slider[no].raideur_compression);
		    		//printf("Slider[no].raideur_traction %lf \n",Slider[no].raideur_traction);
		    		//printf("Slider[no].raideur_effective %lf \n",Slider[no].raideur_effective);
		    		//printf("Slider[no].lgrepos %lf \n",Slider[no].lgrepos);
		    		//printf("Slider[no].wt %lf \n",Slider[no].wt);
				//exit(0);
				}
			if (strcmp(chaine,"ballast_dynamic2") == 0)
				{
				printf("lecture  ballast_dynamic2  \n");
				itmp = fscanf(fic, "%d", &zi);		//ballast numero
				printf("ballast %d ",zi);
				itmp = fscanf(fic,"%d",&Ballast[zi].nb_times);
				printf("nb_times %d \n",Ballast[zi].nb_times);
				Ballast[zi].times 		= (double *) Malloc_double(1 + Ballast[zi].nb_times);
				Ballast[zi].volume_table 	= (double *) Malloc_double(1 + Ballast[zi].nb_times);
				for (zk = 1; zk<= Ballast[zi].nb_times; zk++)
					{
					itmp = fscanf(fic,"%lf",&Ballast[zi].times[zk]);
					//printf("zk %d times %7.3lf s \n",zk,Ballast[zi].times[zk]);
					}
				for (zk = 1; zk<= Ballast[zi].nb_times; zk++)
					{
					itmp = fscanf(fic,"%lf",&Ballast[zi].volume_table[zk]);
					printf("zk %d volu %7.3lf m³\n",zk,Ballast[zi].volume_table[zk]);
					tmp_d1 = 0.0;
					for (zj = 1; zj<= Ballast[zi].nb_cables; zj++)
						{
						temp_int = Ballast[zi].cable[zj];
						tmp_d1 = tmp_d1 + Ballast[zi].cable_volume[zj];
						}
					printf("volume max %7.3lf m³ \n",tmp_d1);
					printf("%7.3lf m³\n",Ballast[zi].volume_table[zk]);
					if (Ballast[zi].volume_table[zk] > tmp_d1) Ballast[zi].volume_table[zk] = tmp_d1;
					printf("%7.3lf m³\n",Ballast[zi].volume_table[zk]);
					if (Ballast[zi].volume_table[zk] <      0.0) Ballast[zi].volume_table[zk] =      0.0;
					}
				printf("volume max %7.3lf m³ \n",tmp_d1);
				for (zk = 1; zk<= Ballast[zi].nb_times; zk++)
					{
					printf("%7.3lf s ",Ballast[zi].times[zk]);
					printf("%7.3lf m³\n",Ballast[zi].volume_table[zk]);
					}
				//exit(0);
				}						
			if (strcmp(chaine,"ballast2") == 0)
				{
				printf("lecture  ballast2  ");
				Structure.nb_ballast = Structure.nb_ballast + 1;
				tmp_d1 = 0.0;	//volume of the cables in the ballast
				if (Structure.nb_ballast > 5)
					{
					printf("ATTENTION the nb of ballasts is limited to 5  \n");
					exit(0);
					}
				itmp = fscanf(fic,"%d",&Ballast[Structure.nb_ballast].nb_cables);
				if (Ballast[Structure.nb_ballast].nb_cables > Structure.NbTypeelem)
					{
					printf("There are too many cables in the ballast %d it must be < the number of cables in the struture which is %d\n",Structure.nb_ballast,Structure.NbTypeelem);
					exit(0);
					}
				Ballast[Structure.nb_ballast].cable 		= (   int *) Malloc_int   (1 + Ballast[Structure.nb_ballast].nb_cables);
				Ballast[Structure.nb_ballast].cable_volume 	= (double *) Malloc_double(1 + Ballast[Structure.nb_ballast].nb_cables);
				for (zk = 1; zk<= Ballast[Structure.nb_ballast].nb_cables; zk++)
					{
					itmp = fscanf(fic,"%d",&Ballast[Structure.nb_ballast].cable[zk]);
					temp_int = Ballast[Structure.nb_ballast].cable[zk];
					if (temp_int <= 0)
						{
						printf("ATTENTION the cable %d of the ballast %d must be > 0\n",temp_int,Structure.nb_ballast);
						exit(0);
						}
					if (temp_int > Structure.NbTypeelem)
						{
						printf("ATTENTION the cable %d of the ballast %d must be <= the total number of cables in the structure which is %d\n",temp_int,Structure.nb_ballast,Structure.NbTypeelem);
						exit(0);
						}
					}
				for (zk = 1; zk<= Ballast[Structure.nb_ballast].nb_cables; zk++)
					{
					itmp = fscanf(fic,"%lf",&Ballast[Structure.nb_ballast].cable_volume[zk]);
					if (Ballast[Structure.nb_ballast].cable_volume[zk] < 0.0)
						{
						printf("WARNING in ballast %d: the maximal volume of cables %d is negative\n",Structure.nb_ballast,zk);
						}
					temp_int = Ballast[Structure.nb_ballast].cable[zk];
					tmp_d2 = TypeElement[temp_int].lgrepos * PI * TypeElement[temp_int].diametrehydro * TypeElement[temp_int].diametrehydro / 4.0;
					if (Ballast[Structure.nb_ballast].cable_volume[zk] > tmp_d2)
						{
						printf("WARNING in ballast %d: the maximal volume (%lf) of cables %d is larger the volume of cable %lf m³, are you sure ?\n",Structure.nb_ballast,Ballast[Structure.nb_ballast].cable_volume[zk],zk,tmp_d2);
						}
					tmp_d1 = tmp_d1 + Ballast[Structure.nb_ballast].cable_volume[zk];
					}
				itmp = fscanf(fic,"%lf",&Ballast[Structure.nb_ballast].volume);	
				if (Ballast[Structure.nb_ballast].volume > tmp_d1)
					{
					Ballast[Structure.nb_ballast].volume = tmp_d1;
					printf("For the ballast %d the volume is reduced to the volume of cables %lf m^3 \n",Structure.nb_ballast,tmp_d1);
					}
				printf("Ballast %d volume %lf m^3 for cables volume of %lf m^3 in cables :  ",Structure.nb_ballast,Ballast[Structure.nb_ballast].volume,tmp_d1);
				for (zk = 1; zk<= Ballast[Structure.nb_ballast].nb_cables; zk++)
					{
					printf("%d ",Ballast[Structure.nb_ballast].cable[zk]);
					}
				printf("\n");
				//exit(0);
				}						
			if (strcmp(chaine,"deck") == 0)
				{
				printf("lecture deck ");
				Structure.nb_deck = Structure.nb_deck + 1;
				if (Structure.nb_deck > 60)
					{
					printf("ATTENTION the nb of decks is limited to 60\n");
					exit(0);
					}
				itmp = fscanf(fic,"%d",&Deck[Structure.nb_deck].master_node);
				itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].x1);	itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].y1);	itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].z1);
				itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].x2);	itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].y2);	itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].z2);
				itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].x3);	itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].y3);	itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].z3);
				itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].thickness);
				itmp = fscanf(fic,"%lf",&Deck[Structure.nb_deck].stiffness);	
				printf(" %d ",Structure.nb_deck);

				printf("master %4d ",Deck[Structure.nb_deck].master_node);
				printf("vertex1 %6.2lf m ",Deck[Structure.nb_deck].x1);	printf(" %6.2lf m ",Deck[Structure.nb_deck].y1);	printf(" %6.2lf m ",Deck[Structure.nb_deck].z1);
				printf("vertex2 %6.2lf m ",Deck[Structure.nb_deck].x2);	printf(" %6.2lf m ",Deck[Structure.nb_deck].y2);	printf(" %6.2lf m ",Deck[Structure.nb_deck].z2);
				printf("vertex3 %6.2lf m ",Deck[Structure.nb_deck].x3);	printf(" %6.2lf m ",Deck[Structure.nb_deck].y3);	printf(" %6.2lf m ",Deck[Structure.nb_deck].z3);
				printf("thikness %lf m ",Deck[Structure.nb_deck].thickness);
				printf("stiffness %lf N/m\n",Deck[Structure.nb_deck].stiffness);

				}						
			if (strcmp(chaine,"tab_drag_filt") == 0)
				{
				printf("lecture  tab_drag_filt  ");
				itmp = fscanf(fic, "%d", &zi);
				itmp = fscanf(fic, "%d", &TypeElement[zi].nb_tab_drag_lift);		
				printf("tabulated element %d nb %d\n",zi,TypeElement[zi].nb_tab_drag_lift);
			 	/**********************************************/
				TypeElement[zi].angle_tab_drag_lift = (double *) malloc((1 + TypeElement[zi].nb_tab_drag_lift) * sizeof(double));
				if (TypeElement[zi].angle_tab_drag_lift    == NULL)
					{
					printf("TypeElement[zi].angle_tab_drag_lift  1 = NULL  \n" );
					exit(0);
					}
			 	/**********************************************/
				TypeElement[zi].drag_tab_drag_lift = (double *) malloc((1 + TypeElement[zi].nb_tab_drag_lift) * sizeof(double));
				if (TypeElement[zi].angle_tab_drag_lift    == NULL)
					{
					printf("TypeElement[zi].drag_tab_drag_lift  1 = NULL  \n" );
					exit(0);
					}
			 	/**********************************************/
				TypeElement[zi].lift_tab_drag_lift = (double *) malloc((1 + TypeElement[zi].nb_tab_drag_lift) * sizeof(double));
				if (TypeElement[zi].angle_tab_drag_lift    == NULL)
					{
					printf("TypeElement[zi].lift_tab_drag_lift  1 = NULL  \n" );
					exit(0);
					}
			 	/**********************************************/
				for (zk = 1; zk<= TypeElement[zi].nb_tab_drag_lift; zk++)
					{
					itmp = fscanf(fic,"%lf",&TypeElement[zi].angle_tab_drag_lift[zk]);	/*reading angle*/
					}
				for (zk = 1; zk<= TypeElement[zi].nb_tab_drag_lift; zk++)
					{
					itmp = fscanf(fic,"%lf",&TypeElement[zi].drag_tab_drag_lift[zk]);	/*reading angle*/
					}
				for (zk = 1; zk<= TypeElement[zi].nb_tab_drag_lift; zk++)
					{
					itmp = fscanf(fic,"%lf",&TypeElement[zi].lift_tab_drag_lift[zk]);	/*reading angle*/
					}
				printf("  theta      CD      CL\n");
				for (zk = 1; zk<= TypeElement[zi].nb_tab_drag_lift; zk++)
					{
					printf("%7.1lf  %6.2lf  %6.2lf\n",TypeElement[zi].angle_tab_drag_lift[zk],TypeElement[zi].drag_tab_drag_lift[zk],TypeElement[zi].lift_tab_drag_lift[zk]);
					}
				}						
			if (strcmp(chaine,"circular_speed_node") == 0)
				{
				itmp = fscanf(fic, "%d", &zi);
				Noeud[zi].circular_speed = 1;
				itmp = fscanf(fic, "%lf", &Noeud[zi].circular_normal[1]);
				itmp = fscanf(fic, "%lf", &Noeud[zi].circular_normal[2]);
				itmp = fscanf(fic, "%lf", &Noeud[zi].circular_normal[3]);
				//verification vect norm
				norm = sqrt(produit_scal(Noeud[zi].circular_normal,Noeud[zi].circular_normal));
				Noeud[zi].circular_normal[1] = Noeud[zi].circular_normal[1]/norm;
				Noeud[zi].circular_normal[2] = Noeud[zi].circular_normal[2]/norm;
				Noeud[zi].circular_normal[3] = Noeud[zi].circular_normal[3]/norm;
				itmp = fscanf(fic, "%lf", &Noeud[zi].circular_center[1]);
				itmp = fscanf(fic, "%lf", &Noeud[zi].circular_center[2]);
				itmp = fscanf(fic, "%lf", &Noeud[zi].circular_center[3]);
				itmp = fscanf(fic, "%lf", &Noeud[zi].circular_rev_speed);
				printf("circular_speed_node, node %d normal vect %lf %lf %lf center  %lf %lf %lf rev speed %lf tr/s\n",zi,Noeud[zi].circular_normal[1],Noeud[zi].circular_normal[2],Noeud[zi].circular_normal[3],Noeud[zi].circular_center[1],Noeud[zi].circular_center[2],Noeud[zi].circular_center[3],Noeud[zi].circular_rev_speed);	
				}
			if (strcmp(chaine,"cable_tension_constant") == 0)
				{
				itmp = fscanf(fic, "%d", &i);
				itmp = fscanf(fic, "%lf", &TypeElement[i].tension_constant);
				TypeElement[i].constant_tension = 1;
				printf("cable_tension_constant, cable %d constant tension %lf N\n",i,TypeElement[i].tension_constant);
				}
			if (strcmp(chaine,"convergence_parameters") == 0)
				{
				printf("convergence_parameters  ");
				Structure.convergence_parameters = 1;
			  	itmp = fscanf(fic,"%lf",&Relaxation); 		/* terme de relaxation du mouvement. En general =1 donc ne chamge rien!*/
			  	itmp = fscanf(fic,"%d",&Periodeimpression);	/*  periode d'affichage a l'ecran de certains renseignements */
			  	itmp = fscanf(fic,"%lf",&Numtemps ); 		/* Numtemps : le terme qui l'on ajoute a la diagonale de la matrice de raideur*/
				printf("convergence_parameters %lf %d %lf\n",Relaxation,Periodeimpression,Numtemps);
			  	strcpy(tonom,nomfichier);
				j=strlen(tonom);
				while ((tonom[j])!='.' && j>0) j--;
				if (tonom[j]=='.') tonom[j]=0;
			  	strcat(tonom,".par");
			  	f3 = fopen(tonom,"w");
			  	/*writting of convergence parameters in *.par*/
			    	fprintf(f3,"  %3.0lf\n",Relaxation);
			    	fprintf(f3,"  %3d\n",Periodeimpression);
			    	fprintf(f3,"  %9.0lf\n",Numtemps);
				fclose(f3);
				}
			if (strcmp(chaine,"angle_speed_cd") == 0)
				{
				printf("lecture  angle_speed_cd  ");
				Courant.nb_angle_speed_cd++;
				if (Courant.nb_angle_speed_cd == 1)
					{
       				 	/**********************************************/
       					Courant.angle_speed_cd_alpha = (double *) malloc((1 + Courant.nb_angle_speed_cd) * sizeof(double));
       					if (Courant.angle_speed_cd_alpha    == NULL)
						{
						printf("Courant.angle_speed_cd_alpha  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
       					Courant.angle_speed_cd_beta = (double *) malloc((1 + Courant.nb_angle_speed_cd) * sizeof(double));
       					if (Courant.angle_speed_cd_beta    == NULL)
						{
						printf("Courant.angle_speed_cd_beta  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
       					Courant.angle_speed_cd_speed = (double *) malloc((1 + Courant.nb_angle_speed_cd) * sizeof(double));
       					if (Courant.angle_speed_cd_speed    == NULL)
						{
						printf("Courant.angle_speed_cd_speed  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
       					Courant.angle_speed_cd_cd = (double *) malloc((1 + Courant.nb_angle_speed_cd) * sizeof(double));
       					if (Courant.angle_speed_cd_cd    == NULL)
						{
						printf("Courant.angle_speed_cd_cd  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
					}
				else
					{
					Courant.angle_speed_cd_alpha = 	(double *) Realloc_double(Courant.angle_speed_cd_alpha,1 + Courant.nb_angle_speed_cd);
					Courant.angle_speed_cd_beta = 	(double *) Realloc_double(Courant.angle_speed_cd_beta,1 + Courant.nb_angle_speed_cd);
					Courant.angle_speed_cd_speed = 	(double *) Realloc_double(Courant.angle_speed_cd_speed,1 + Courant.nb_angle_speed_cd);
					Courant.angle_speed_cd_cd = 	(double *) Realloc_double(Courant.angle_speed_cd_cd,1 + Courant.nb_angle_speed_cd);
					}
				itmp = fscanf(fic,"%lf",&Courant.angle_speed_cd_alpha[Courant.nb_angle_speed_cd]);	/*reading of the first angle*/
				itmp = fscanf(fic,"%lf",&Courant.angle_speed_cd_beta[Courant.nb_angle_speed_cd]);	/*reading of the second angle*/
				itmp = fscanf(fic,"%lf",&Courant.angle_speed_cd_speed[Courant.nb_angle_speed_cd]);	/*reading of the speed*/
				itmp = fscanf(fic,"%lf",&Courant.angle_speed_cd_cd[Courant.nb_angle_speed_cd]);		/*reading of the cd*/
				printf("from alpha %5.1lf deg. to beta %5.1lf deg. speed %8.2lf m/s and cd %5.2lf\n",Courant.angle_speed_cd_alpha[Courant.nb_angle_speed_cd],Courant.angle_speed_cd_beta[Courant.nb_angle_speed_cd],Courant.angle_speed_cd_speed[Courant.nb_angle_speed_cd],Courant.angle_speed_cd_cd[Courant.nb_angle_speed_cd]);
				}
			if (strcmp(chaine,"water_speed_depth") == 0)
				{
				printf("lecture  water_speed_depth  ");
				Courant.nb_courant++;
				if (Courant.nb_courant == 1)
					{
       				 	/**********************************************/
       					Courant.depth1 = (double *) malloc((1 + Courant.nb_courant) * sizeof(double));
       					if (Courant.depth1    == NULL)
						{
						printf("Courant.depth1  1 = NULL  \n" );
						exit(0);
						}
      				 	/**********************************************/
       					Courant.depth2 = (double *) malloc((1 + Courant.nb_courant) * sizeof(double));
       					if (Courant.depth2    == NULL)
						{
						printf("Courant.depth2  1 = NULL  \n" );
						exit(0);
						}
       				 	/**********************************************/
       					Courant.courant1 = (double *) malloc((1 + Courant.nb_courant) * sizeof(double));
       					if (Courant.courant1    == NULL)
						{
						printf("Courant.courant1  1 = NULL  \n" );
						exit(0);
						}
       				 	/**********************************************/
       					Courant.courant2 = (double *) malloc((1 + Courant.nb_courant) * sizeof(double));
       					if (Courant.courant2    == NULL)
						{
						printf("Courant.courant2  1 = NULL  \n" );
						exit(0);
						}
       				 	/**********************************************/
       					Courant.direction1 = (double *) malloc((1 + Courant.nb_courant) * sizeof(double));
       					if (Courant.direction1    == NULL)
						{
						printf("Courant.direction1  1 = NULL  \n" );
						exit(0);
						}
       				 	/**********************************************/
       					Courant.direction2 = (double *) malloc((1 + Courant.nb_courant) * sizeof(double));
       					if (Courant.direction2    == NULL)
						{
						printf("Courant.direction2  1 = NULL  \n" );
						exit(0);
						}
       				 	/**********************************************/
					}
				else
					{
					Courant.depth1 = 	(double *) Realloc_double(Courant.depth1,1 + Courant.nb_courant);
					Courant.depth2 = 	(double *) Realloc_double(Courant.depth2,1 + Courant.nb_courant);
					Courant.courant1 = 	(double *) Realloc_double(Courant.courant1,1 + Courant.nb_courant);
					Courant.courant2 = 	(double *) Realloc_double(Courant.courant2,1 + Courant.nb_courant);
					Courant.direction1 = 	(double *) Realloc_double(Courant.direction1,1 + Courant.nb_courant);
					Courant.direction2 = 	(double *) Realloc_double(Courant.direction2,1 + Courant.nb_courant);
					}
				itmp = fscanf(fic,"%lf",&Courant.depth1[Courant.nb_courant]);	/*reading of the first depth*/
				itmp = fscanf(fic,"%lf",&Courant.courant1[Courant.nb_courant]);	/*reading of the first depth*/
				itmp = fscanf(fic,"%lf",&Courant.direction1[Courant.nb_courant]);	/*reading of the first depth*/
				itmp = fscanf(fic,"%lf",&Courant.depth2[Courant.nb_courant]);	/*reading of the first depth*/
				itmp = fscanf(fic,"%lf",&Courant.courant2[Courant.nb_courant]);	/*reading of the first depth*/
				itmp = fscanf(fic,"%lf",&Courant.direction2[Courant.nb_courant]);	/*reading of the first depth*/
				if (Courant.depth1[Courant.nb_courant] == Courant.depth2[Courant.nb_courant])
					{
					printf("value nb %d:",Courant.nb_courant);
					printf("value %lf at depth %lf m and value %lf at depth %lf m\n",Courant.courant1[Courant.nb_courant],Courant.depth1[Courant.nb_courant],Courant.courant2[Courant.nb_courant],Courant.depth2[Courant.nb_courant]);
					printf("ERROR: the two depths (%lf m) can't be equal\n",Courant.depth1[Courant.nb_courant]);
					exit(0);
					}
				for (zi = 1; zi<=Courant.nb_courant ; zi++)
					{
					printf("Courant nb %d:\n",zi);
					printf("Courant %5.3lf m/s direction %5.0lf deg. at depth %8.2lf m and \n",Courant.courant1[zi],Courant.direction1[zi],Courant.depth1[zi]);
					printf("courant %5.3lf m/s direction %5.0lf deg. at depth %8.2lf m\n",Courant.courant2[zi],Courant.direction2[zi],Courant.depth2[zi]);
					/*
					*/
					}
				}
			if (strcmp(chaine,"type_solver") == 0)
				{
				//input type_solver : 1 for gauss, 2 for pardiso 
				itmp = fscanf(fic,"%d",&Structure.type_solver);			
				if (Structure.type_solver == 1) printf("The solver is gauss\n");
				if (Structure.type_solver == 2) printf("The solver is pardiso\n");
				if (Structure.type_solver < 1) 
					{
					printf("type_solver must be > 0 and < 3\n");
					exit(0);
					}
				if (Structure.type_solver > 2) 
					{
					printf("type_solver must be > 0 and < 3\n");
					exit(0);
					}
				}
			if (strcmp(chaine,"link_flexion_elem") == 0)
			{
				itmp = fscanf(fic, "%d", &i);
				itmp = fscanf(fic, "%d", &j);
				find_link = 1;
				printf ("link_flexion_elem with i = %d and j = %d\n", i, j);

				if (TypeElement[i].link_flexion[1] == 0) 
				{
					TypeElement[i].link_flexion[1] = j;
				}
				else if (TypeElement[i].link_flexion[2] == 0)
				{
					TypeElement[i].link_flexion[2] = j;
				}
				else
				{
					printf("les deux cases de TypeElement[%d].link_flexion sont deja remplies\n", i);
				}

				if (TypeElement[j].link_flexion[1] == 0 ) 
				{
					TypeElement[j].link_flexion[1] = i;
				}
				else if (TypeElement[j].link_flexion[2] == 0)
				{
					TypeElement[j].link_flexion[2] = i;
				}
				else
				{
					printf("les deux cases de TypeElement[%d].link_flexion sont deja remplies\n", i);
				}
			}
			if (strcmp(chaine,"link_flexion_elem2") == 0)
			{
				itmp = fscanf(fic, "%d", &i);
				itmp = fscanf(fic, "%d", &j);
				TypeElement[i].nb_link_flexion2++;
				TypeElement[j].nb_link_flexion2++;

				TypeElement[i].link_flexion2 = (int *) Realloc_int(TypeElement[i].link_flexion2   ,1 + TypeElement[i].nb_link_flexion2);	
				TypeElement[i].angle_link_flexion2 = (double *) Realloc_double(TypeElement[i].angle_link_flexion2   ,1 + TypeElement[i].nb_link_flexion2);	
				TypeElement[j].link_flexion2 = (int *) Realloc_int(TypeElement[j].link_flexion2   ,1 + TypeElement[j].nb_link_flexion2);	
				TypeElement[j].angle_link_flexion2 = (double *) Realloc_double(TypeElement[j].angle_link_flexion2   ,1 + TypeElement[j].nb_link_flexion2);	
				TypeElement[i].link_flexion2[TypeElement[i].nb_link_flexion2] = j;
				TypeElement[j].link_flexion2[TypeElement[j].nb_link_flexion2] = i;
				itmp = fscanf(fic,"%lf",&tmp_d1);
				TypeElement[i].angle_link_flexion2[TypeElement[i].nb_link_flexion2] = 180.0-tmp_d1;
				TypeElement[j].angle_link_flexion2[TypeElement[j].nb_link_flexion2] = 180.0-tmp_d1;

				//printf ("link_flexion_elem2 between cables %4d and %4d at angle %lf\n", TypeElement[i].link_flexion2[TypeElement[i].nb_link_flexion2], TypeElement[j].link_flexion2[TypeElement[j].nb_link_flexion2], TypeElement[i].angle_link_flexion2[TypeElement[i].nb_link_flexion2]);
			}
			if (strcmp(chaine,"speed_type_node") == 0)
				{
				Structure.speed_type_node = 1;				
				//input speed_type_node node_type begining_times end_times beginning_vx end_vx beginning_vy end_vy beginning_vz end_vz 
				Structure.nb_speed_type_node = Structure.nb_speed_type_node + 1;
				itmp = fscanf(fic,"%d",&i);		/*node type*/				
				itmp = fscanf(fic,"%lf",&TypeNoeud[i].beg_times);
				itmp = fscanf(fic,"%lf",&TypeNoeud[i].end_times);
				itmp = fscanf(fic,"%lf",&TypeNoeud[i].beg_vx);
				itmp = fscanf(fic,"%lf",&TypeNoeud[i].end_vx);
				itmp = fscanf(fic,"%lf",&TypeNoeud[i].beg_vy);
				itmp = fscanf(fic,"%lf",&TypeNoeud[i].end_vy);
				itmp = fscanf(fic,"%lf",&TypeNoeud[i].beg_vz);
				itmp = fscanf(fic,"%lf",&TypeNoeud[i].end_vz);

				printf("The type node %d has a speed of %lf %lf %lf m/s at %lf s\n",i,TypeNoeud[i].beg_vx,TypeNoeud[i].beg_vy,TypeNoeud[i].beg_vz,TypeNoeud[i].beg_times);
				printf("The type node %d has a speed of %lf %lf %lf m/s at %lf s\n",i,TypeNoeud[i].end_vx,TypeNoeud[i].end_vy,TypeNoeud[i].end_vz,TypeNoeud[i].end_times);
				}
			if (strcmp(chaine,"speed_type_node2") == 0)
				{
				Structure.speed_type_node = 2;				
				//input speed_type_node node_type begining_times end_times beginning_vx end_vx beginning_vy end_vy beginning_vz end_vz 
				itmp = fscanf(fic,"%d",&i);		/*node type*/				
				itmp = fscanf(fic,"%d",&TypeNoeud[i].nb_times);
				TypeNoeud[i].times   = (double *) Realloc_double(TypeNoeud[i].times    ,1 + TypeNoeud[i].nb_times);				
				TypeNoeud[i].speedx  = (double *) Realloc_double(TypeNoeud[i].speedx   ,1 + TypeNoeud[i].nb_times);				
				TypeNoeud[i].speedy  = (double *) Realloc_double(TypeNoeud[i].speedy   ,1 + TypeNoeud[i].nb_times);				
				TypeNoeud[i].speedz  = (double *) Realloc_double(TypeNoeud[i].speedz   ,1 + TypeNoeud[i].nb_times);				
				for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeNoeud[i].times[pa]);
				for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeNoeud[i].speedx[pa]);
				for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeNoeud[i].speedy[pa]);
				for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeNoeud[i].speedz[pa]);
				printf("the times table of the node type %d :\n",i);
				printf("times :  ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].times[pa]);	printf("  s\n");
				printf("speedx : ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].speedx[pa]);	printf("  m/s\n");
				printf("speedy : ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].speedy[pa]);	printf("  m/s\n");
				printf("speedz : ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].speedz[pa]);	printf("  m/s\n");
				}
			if (strcmp(chaine,"speed_type_node3") == 0)
				{
				Structure.speed_type_node = 3;				
				//input speed_type_node node_type begining_times end_times beginning_vx end_vx beginning_vy end_vy beginning_vz end_vz 
				itmp = fscanf(fic,"%d",&i);		/*node type*/				
				itmp = fscanf(fic,"%d",&TypeNoeud[i].nb_times);
				TypeNoeud[i].times   = (double *) Realloc_double(TypeNoeud[i].times    ,1 + TypeNoeud[i].nb_times);				
				TypeNoeud[i].speedm  = (double *) Realloc_double(TypeNoeud[i].speedm   ,1 + TypeNoeud[i].nb_times);				
				TypeNoeud[i].speedo  = (double *) Realloc_double(TypeNoeud[i].speedo   ,1 + TypeNoeud[i].nb_times);				
				TypeNoeud[i].speedd  = (double *) Realloc_double(TypeNoeud[i].speedd   ,1 + TypeNoeud[i].nb_times);				
				TypeNoeud[i].speedx  = (double *) Realloc_double(TypeNoeud[i].speedx   ,1 + TypeNoeud[i].nb_times);				
				TypeNoeud[i].speedy  = (double *) Realloc_double(TypeNoeud[i].speedy   ,1 + TypeNoeud[i].nb_times);				
				TypeNoeud[i].speedz  = (double *) Realloc_double(TypeNoeud[i].speedz   ,1 + TypeNoeud[i].nb_times);				
				for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeNoeud[i].times[pa]);
				for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeNoeud[i].speedm[pa]);
				for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeNoeud[i].speedo[pa]);
				for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeNoeud[i].speedd[pa]);
				for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)
					{
					tmp_d1=(double) gasdev(&idum)*TypeNoeud[i].speedd[pa]+TypeNoeud[i].speedm[pa];
					TypeNoeud[i].speedx[pa] = tmp_d1 * cos(TypeNoeud[i].speedo[pa]*PI/180);
					TypeNoeud[i].speedy[pa] = tmp_d1 * sin(TypeNoeud[i].speedo[pa]*PI/180);
					TypeNoeud[i].speedz[pa] = 0.0;
					}
				printf("the times table of the node type %d :\n",i);
				printf("times :  ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].times[pa]);	printf("  s\n");
				printf("speedm : ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].speedm[pa]);	printf("  m/s\n");
				printf("speedo : ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].speedo[pa]);	printf("  m/s\n");
				printf("speedd : ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].speedd[pa]);	printf("  m/s\n");
				printf("speedx : ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].speedx[pa]);	printf("  m/s\n");
				printf("speedy : ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].speedy[pa]);	printf("  m/s\n");
				printf("speedz : ");	for (pa=1;pa<=TypeNoeud[i].nb_times;pa++)	printf("     %8.2lf",TypeNoeud[i].speedz[pa]);	printf("  m/s\n");
				}
			if (strcmp(chaine,"speed_type_node4") == 0)
				{
				//input nb of node coordinates where the speed is given in the file  *.fos
				// nb_of coordinates numero_coordinate speed_along
				Structure.speed_type_node = 4;				
				strcpy(tonom,nomfichier);
				j=strlen(tonom);
				while ((tonom[j])!='.' && j>0) j--;
				if (tonom[j]=='.') tonom[j]=0;
			  	strcat(tonom,".fos");
				printf("At each time step the file %s is read. This file give the speed of coordinates\n",tonom);
			  	f3 = fopen(tonom,"r");
			  	if (f3 == NULL) 
			  		{
			    		printf(" \n");
			    		printf("%s %s %s \n","file ",tonom," don't exist ?");
			    		exit(0);
			  		} 
				itmp = fscanf(f3,"%d",&temp_int);
				printf("nb of coordinates %d\n",temp_int);
				for (pa=1;pa<=temp_int;pa++)	
					{	
					itmp = fscanf(f3,"%d",&temp2_int);
					itmp = fscanf(f3,"%lf",&tmp_d2);
					printf("coordinate %d has a speed of %lf m/s\n",temp2_int,tmp_d2);
					}
				fclose(f3);			
				}
			if (strcmp(chaine,"ratio_drag_panel") == 0)
				{
				//input nb_ratio_drag_panel begining_times end_times beginning_ratio_drag_panel end_ratio_drag_panel
				itmp = fscanf(fic,"%d",&Structure.nb_ratio_drag_panel);
				Structure.times_drag_panel   = (double *) Realloc_double(Structure.times_drag_panel    ,1 + Structure.nb_ratio_drag_panel);				
				Structure.ratio_drag_panel   = (double *) Realloc_double(Structure.ratio_drag_panel    ,1 + Structure.nb_ratio_drag_panel);				
				for (pa=1;pa<=Structure.nb_ratio_drag_panel;pa++)	{	itmp = fscanf(fic,"%lf",&Structure.times_drag_panel[pa]);	}
				for (pa=1;pa<=Structure.nb_ratio_drag_panel;pa++)	{	itmp = fscanf(fic,"%lf",&Structure.ratio_drag_panel[pa]);	}
				printf("the times table of the ratio_drag_panel. nb_ratio_drag_panel = %d :\n",Structure.nb_ratio_drag_panel);
				printf("times :  ");	for (pa=1;pa<=Structure.nb_ratio_drag_panel;pa++)	printf("     %8.2lf",Structure.times_drag_panel[pa]);	printf("  s\n");
				printf("ratio : ");	for (pa=1;pa<=Structure.nb_ratio_drag_panel;pa++)	printf("     %8.2lf",Structure.ratio_drag_panel[pa]);	printf("   \n");
				}
			if (strcmp(chaine,"hauling_cable") == 0)
				{
				Structure.nb_hauling_cable = Structure.nb_hauling_cable + 1;
				itmp = fscanf(fic,"%d",&i);		/*cable*/				
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_speed);
				itmp = fscanf(fic,"%d",&TypeElement[i].haul_extremity);
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_limit);
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_time);
				printf("The cable %d is reduced at %lf m/s by its extremity %d. Its minimal length is %lf m. It begins to reduce at %lf s.\n",i,TypeElement[i].haul_speed,TypeElement[i].haul_extremity,TypeElement[i].haul_limit,TypeElement[i].haul_time);
				}
			if (strcmp(chaine,"hauling_cable2") == 0)
				{
				Structure.nb_hauling_cable2 = Structure.nb_hauling_cable2 + 1;
				itmp = fscanf(fic,"%d",&i);		/*cable*/				
				itmp = fscanf(fic,"%d",&TypeElement[i].haul_extremity);
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_beg_times);
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_end_times);
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_beg_speed);
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_end_speed);
				printf("The cable %d is reduced by its extremity %d\n",i,TypeElement[i].haul_extremity);
				printf("Beginning times %lf s, end times %lf s, begining speed %lf m/s, end speed %lf m/s\n",TypeElement[i].haul_beg_times,TypeElement[i].haul_end_times,TypeElement[i].haul_beg_speed,TypeElement[i].haul_end_speed);
				}
			if (strcmp(chaine,"hauling_cable3") == 0)
				{
				itmp = fscanf(fic,"%d",&i);		/*cable*/				
				itmp = fscanf(fic,"%d",&TypeElement[i].haul_extremity);
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_mini);
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_maxi);
				itmp = fscanf(fic,"%d",&TypeElement[i].nb_times);
				TypeElement[i].times  = (double *) Realloc_double(TypeElement[i].times   ,1 + TypeElement[i].nb_times);				
				TypeElement[i].haul_v = (double *) Realloc_double(TypeElement[i].haul_v  ,1 + TypeElement[i].nb_times);				
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					itmp = fscanf(fic,"%lf",&TypeElement[i].times[pa]);
					}
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					itmp = fscanf(fic,"%lf",&TypeElement[i].haul_v[pa]);
					}
				printf("The cable %d is reduced by its extremity %d\n",i,TypeElement[i].haul_extremity);
				printf("the times table is :\n");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8.2lf",TypeElement[i].times[pa]);
					}
					printf("  s\n");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8.2lf",TypeElement[i].haul_v[pa]);
					}
					printf("  m/s\n");
				}
			if (strcmp(chaine,"hauling_cable4") == 0)
				{
				itmp = fscanf(fic,"%d",&i);		/*cable*/				
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_mini);
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_maxi);
				itmp = fscanf(fic,"%d",&TypeElement[i].nb_times);
				TypeElement[i].times  = (double *) Realloc_double(TypeElement[i].times   ,1 + TypeElement[i].nb_times);				
				TypeElement[i].haul_v = (double *) Realloc_double(TypeElement[i].haul_v  ,1 + TypeElement[i].nb_times);				
				TypeElement[i].haul_ext = (int *) Realloc_int(TypeElement[i].haul_ext  ,1 + TypeElement[i].nb_times);				
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					itmp = fscanf(fic,"%lf",&TypeElement[i].times[pa]);	// Recupere tous les temps
					}
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					itmp = fscanf(fic,"%lf",&TypeElement[i].haul_v[pa]);	// Recupere les vitesses a chaque pas de temps
					}
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					itmp = fscanf(fic,"%d",&TypeElement[i].haul_ext[pa]);	// Recupere les extremites utilisees a chaque pas de temps
					}
				printf("The cable %d is reduced\n",i);
				printf("the times table is : ");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8.2lf",TypeElement[i].times[pa]);
					}
					printf("  s\n");
				printf("the hauling speed :  ");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8.2lf",TypeElement[i].haul_v[pa]);
					}
					printf("  m/s\n");
				printf("the extremity     :  ");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8d",TypeElement[i].haul_ext[pa]);
					}
					printf("\n");
				}
			if (strcmp(chaine,"hauling_cable6") == 0)
				{
				itmp = fscanf(fic,"%d",&i);		/*cable*/				
				itmp = fscanf(fic,"%lf",&tmp_d1);	TypeElement[i].haul_mini = tmp_d1 / TypeElement[i].nb_barre;
				itmp = fscanf(fic,"%lf",&tmp_d1);	TypeElement[i].haul_maxi = tmp_d1 / TypeElement[i].nb_barre;
				itmp = fscanf(fic,"%d",&TypeElement[i].nb_times);
				TypeElement[i].times  = (double *) Realloc_double(TypeElement[i].times   ,1 + TypeElement[i].nb_times);				
				TypeElement[i].haul_v = (double *) Realloc_double(TypeElement[i].haul_v  ,1 + TypeElement[i].nb_times);				
				TypeElement[i].haul_ext = (int *) Realloc_int(TypeElement[i].haul_ext  ,1 + TypeElement[i].nb_times);				
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					itmp = fscanf(fic,"%lf",&TypeElement[i].times[pa]);	// Recupere tous les temps
					}
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					itmp = fscanf(fic,"%lf",&TypeElement[i].haul_v[pa]);	// Recupere les vitesses a chaque pas de temps
					}
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					itmp = fscanf(fic,"%d",&TypeElement[i].haul_ext[pa]);	// Recupere les extremites utilisees a chaque pas de temps
					}
				printf("The cable %d is reduced\n",i);
				printf("the times table is : ");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8.2lf",TypeElement[i].times[pa]);
					}
					printf("  s\n");
				printf("the hauling speed :  ");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8.2lf",TypeElement[i].haul_v[pa]);
					}
					printf("  m/s\n");
				printf("the extremity     :  ");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8d",TypeElement[i].haul_ext[pa]);
					}
					printf("\n");
				}
			if (strcmp(chaine,"hauling_cable5") == 0)
				{
				itmp = fscanf(fic,"%d",&i);		/*cable*/				
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_mini);
				itmp = fscanf(fic,"%lf",&TypeElement[i].haul_maxi);
				itmp = fscanf(fic,"%d",&TypeElement[i].nb_times);
				TypeElement[i].times  = (double *) Realloc_double(TypeElement[i].times   ,1 + TypeElement[i].nb_times);				
				TypeElement[i].haul_v = (double *) Realloc_double(TypeElement[i].haul_v  ,1 + TypeElement[i].nb_times);				
				TypeElement[i].haul_d = (double *) Realloc_double(TypeElement[i].haul_d  ,1 + TypeElement[i].nb_times);				
				TypeElement[i].haul_ext = (int *) Realloc_int(TypeElement[i].haul_ext  ,1 + TypeElement[i].nb_times);				
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeElement[i].times[pa]);	// Recupere tous les temps
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeElement[i].haul_v[pa]);	// Recupere la moyenne des vitesses a chaque pas de temps
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)	itmp = fscanf(fic,"%lf",&TypeElement[i].haul_d[pa]);	// Recupere l'ecart type des vitesses a chaque pas de temps
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)	itmp = fscanf(fic,"%d",&TypeElement[i].haul_ext[pa]);	// Recupere les extremites utilisees a chaque pas de temps
				/*from the mean speed haul_v[pa] and the standard deviation haul_d[pa] a speed is calculated and put in haul_v[pa]*/
				idum = (long) -time(NULL);
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)	
					{
					tmp_d1=(double) gasdev(&idum)*TypeElement[i].haul_d[pa]+TypeElement[i].haul_v[pa];
					TypeElement[i].haul_v[pa]=tmp_d1;
					}


				printf("The cable %d is reduced\n",i);
				printf("the times table is : ");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8.2lf",TypeElement[i].times[pa]);
					}
					printf("  s\n");
				printf("the hauling speed :  ");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8.2lf",TypeElement[i].haul_v[pa]);
					}
					printf("  m/s\n");
				printf("the hauling sd speed :  ");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8.2lf",TypeElement[i].haul_d[pa]);
					}
					printf("  m/s\n");
				printf("the extremity     :  ");
				for (pa=1;pa<=TypeElement[i].nb_times;pa++)
					{
					printf("     %8d",TypeElement[i].haul_ext[pa]);
					}
					printf("\n");
				}
			if (strcmp(chaine,"catch_gravity") == 0)
				{
				itmp = fscanf(fic,"%lf",&Prise.catch_gravity);
				printf("The density of the catch is %lf kg/m³\n",Prise.catch_gravity);
				}
			if (strcmp(chaine,"spheric_knot") == 0)
				{
				itmp = fscanf(fic,"%d",&i);
				itmp = fscanf(fic,"%f",&panneau[i].largeurnoeud);
				printf("The knot diameter of the panel %d is now %lf m\n",i,panneau[i].largeurnoeud);
				}
			if (strcmp(chaine,"drag_forces_type") == 0)
				{
				itmp = fscanf(fic,"%d",&Structure.drag_forces_type);
				if (Structure.drag_forces_type == 1)	printf("The hydrodynamic forces on diamond netting is calculated using Morison formulations\n");
				if (Structure.drag_forces_type == 2)	printf("The hydrodynamic forces on diamond netting is calculated using Zhan formulations\n");
				if (Structure.drag_forces_type == 3)	printf("The hydrodynamic forces on diamond netting is calculated using drop pressure formulations\n");
				if (Structure.drag_forces_type == 4)	printf("The hydrodynamic forces on diamond netting is calculated using Aarnes formulations\n");
				}
			if (strcmp(chaine,"water_density") == 0)
				{
				itmp = fscanf(fic,"%lf",&RHO);
				printf("The density of water is now %lf kg/m³\n",RHO);
				}/**/
			if (strcmp(chaine,"rope_X") == 0)
				{
				itmp = fscanf(fic,"%d",&i);
				itmp = fscanf(fic,"%d",&j);
				itmp = fscanf(fic,"%lf",&dist);
				printf("There are %d ropes like rope %d spaced of %lf created from rope %d (included)\n",i,j,dist,j);
				for (pa=1;pa<=i-1;pa++)
					{
			    		TypeElement[pa+j].raideur_traction 	= TypeElement[j].raideur_traction;
			    		TypeElement[pa+j].raideur_compression 	= TypeElement[j].raideur_compression;
			    		TypeElement[pa+j].lgrepos 		= TypeElement[j].lgrepos;
			    		TypeElement[pa+j].rhoelement 		= TypeElement[j].rhoelement;
			    		TypeElement[pa+j].diametrehydro 	= TypeElement[j].diametrehydro;
			    		TypeElement[pa+j].cdnormal 		= TypeElement[j].cdnormal;
			    		TypeElement[pa+j].ftangent 		= TypeElement[j].ftangent;
					}
				}
			if (strcmp(chaine,"sphere_element") == 0)
				{
				/*printf("add sphere floats  \n");*/
				itmp = fscanf(fic,"%d",&E_numero);
				itmp = fscanf(fic,"%lf",&S_Nb);
				itmp = fscanf(fic,"%lf",&S_Diam);
				itmp = fscanf(fic,"%lf",&S_Float);
				
				S_Vol_Unit = 4.0 / 3.0 * PI * S_Diam * S_Diam * S_Diam / 8.0;
				S_Mass_Unit = S_Vol_Unit * RHO - S_Float / G;
				S_Cd = 0.6;				/*usual cd value for sphere*/
				S_Surf_Unit = PI * S_Diam * S_Diam / 4.0;
				S_Max_Float = S_Vol_Unit * RHO * G;
				
				printf("Add on cable %d, %lg spheres diam %lgm floattability %lgN (floattability limit %lgN)",E_numero,S_Nb,S_Diam,S_Float,S_Max_Float);/**/
				
				if (S_Float > S_Max_Float)
					{
					printf("WARNING! The floattability (%lf N) of spheres is too large they must be limited to %lf N\n",S_Float,S_Max_Float);/**/
					exit(0);
 					}
				
				
				E_Length = TypeElement[E_numero].lgrepos;
				E_Density = TypeElement[E_numero].rhoelement;
				E_Diam = TypeElement[E_numero].diametrehydro;
				E_Cdn = TypeElement[E_numero].cdnormal;
				E_Vol = E_Length * PI * E_Diam * E_Diam / 4.0;
				E_Mass = E_Vol * E_Density;
				E_Surf = E_Length * E_Diam;
				
				F_Vol = E_Vol + S_Nb * S_Vol_Unit;
				F_Mass =  E_Mass + S_Nb * S_Mass_Unit;
				F_Length = E_Length;
				F_Diam = sqrt(4.0 * F_Vol / E_Length / PI);
				F_Density = F_Mass / F_Vol;
				F_Surf = F_Length * F_Diam;
				F_Cdn = (S_Nb*S_Surf_Unit*S_Cd + E_Surf*E_Cdn) / F_Surf;
				
				printf("has density %lgkg/m3 diam %lgm cd %lg ",TypeElement[E_numero].rhoelement,TypeElement[E_numero].diametrehydro,TypeElement[E_numero].cdnormal);/**/
    				TypeElement[E_numero].lgrepos = F_Length;
    				TypeElement[E_numero].rhoelement = F_Density;
    				TypeElement[E_numero].diametrehydro = F_Diam;
    				TypeElement[E_numero].cdnormal = F_Cdn;
				printf("has now density %lgkg/m3 diam %lgm cd %lg\n",TypeElement[E_numero].rhoelement,TypeElement[E_numero].diametrehydro,TypeElement[E_numero].cdnormal);/**/
				}
			if (strcmp(chaine,"sphere_element2") == 0)
				{
				/*printf("add sphere floats  \n");*/
				itmp = fscanf(fic,"%d",&E_numero);
				itmp = fscanf(fic,"%lf",&S_Nb);
				itmp = fscanf(fic,"%lf",&S_Diam);
				itmp = fscanf(fic,"%lf",&S_Float);
				itmp = fscanf(fic,"%lf",&L_Float);
				S_Vol_Unit = 4.0 / 3.0 * PI * S_Diam * S_Diam * S_Diam / 8.0;
				S_Mass_Unit = S_Vol_Unit * RHO - S_Float / G;
				S_Cd = 0.6;				/*usual cd value for sphere*/
				S_Surf_Unit = PI * S_Diam * S_Diam / 4.0;
				S_Max_Float = S_Vol_Unit * RHO * G;
				printf("Add on cable %d, %lg spheres diam %lgm floattability %lgN (floattability limit %lgN)",E_numero,S_Nb,S_Diam,S_Float,S_Max_Float);/**/
				
				if (S_Float > S_Max_Float)
					{
					printf("WARNING! The floattability (%lf N) of spheres is too large they must be limited to %lf N\n",S_Float,S_Max_Float);/**/
					exit(0);
 					}
				
				
				E_Length = L_Float;
				E_Density = TypeElement[E_numero].rhoelement;
				E_Diam = TypeElement[E_numero].diametrehydro;
				E_Cdn = TypeElement[E_numero].cdnormal;
				E_Vol = E_Length * PI * E_Diam * E_Diam / 4.0;
				E_Mass = E_Vol * E_Density;
				E_Surf = E_Length * E_Diam;
				
				F_Vol = E_Vol + S_Nb * S_Vol_Unit;
				F_Mass =  E_Mass + S_Nb * S_Mass_Unit;
				F_Length = E_Length;
				F_Diam = sqrt(4.0 * F_Vol / E_Length / PI);
				F_Density = F_Mass / F_Vol;
				F_Surf = F_Length * F_Diam;
				F_Cdn = (S_Nb*S_Surf_Unit*S_Cd + E_Surf*E_Cdn) / F_Surf;
				
				printf("has density %lgkg/m3 diam %lgm cd %lg ",TypeElement[E_numero].rhoelement,TypeElement[E_numero].diametrehydro,TypeElement[E_numero].cdnormal);/**/
    				//TypeElement[E_numero].lgrepos = F_Length;
    				TypeElement[E_numero].rhoelement = F_Density;
    				TypeElement[E_numero].diametrehydro = F_Diam;
    				TypeElement[E_numero].cdnormal = F_Cdn;
				printf("has now density %lgkg/m3 diam %lgm cd %lg\n",TypeElement[E_numero].rhoelement,TypeElement[E_numero].diametrehydro,TypeElement[E_numero].cdnormal);/**/
				}
			if (strcmp(chaine,"wind") == 0)
				{
				itmp = fscanf(fic,"%lf",&Vent.vitesse);
				itmp = fscanf(fic,"%lf",&Vent.direction);
				printf("wind at %lf m/s in %lf deg relatively to X axe\n",Vent.vitesse,Vent.direction);
				}
			if (strcmp(chaine,"current_reduction") == 0)
				{
				printf("lecture de current_reduction \n");
				/*lecture du numero (int) du panneau concerne entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&pa);
				/*lecture de la valeur de current_reduction (double) entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%lf",&panneau[pa].current_reduction);
				printf("current_reduction at pannel %d is %lf\n",pa,panneau[pa].current_reduction);
				}
			if (strcmp(chaine,"moving_bottom") == 0)
				{
				/*the bottom is moving at the water speed*/
				Bottom.moving = 1;
				printf("Bottom is moving at %lf\n",Courant.vitesse);
				}
			if (strcmp(chaine,"catch_dynamic") == 0)
				{
				/*reading of volume entering in the strcuture per second*/
				itmp = fscanf(fic,"%lf",&Prise.catch_dynamic);
				printf("reading of catch_dynamic %lf m^3/s\n",Prise.catch_dynamic);
				}
			if (strcmp(chaine,"neutral_angle") == 0)
				{
				printf("lecture de neutral_angle \n");
				/*lecture du numero (int) du panneau concerne entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&pa);
				/*lecture de la valeur de l'angle neutre (double) entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%lf",&panneau[pa].neutral_angle);
				}
			if (strcmp(chaine,"EI_flexion") == 0)
				{
				printf("lecture de EI_flexion \n");
				/*lecture du numero (int) du panneau concerne entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&pa);
				/*lecture de la valeur de EI_flexion (double) entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%lf",&panneau[pa].EI_flexion);
				}
			if (strcmp(chaine,"EI_flexion_cable") == 0)
				{
				/*lecture du numero (int) du cable concerne entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&pa);
				/*lecture de la valeur de EI_flexion_cable (double) entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%lf",&TypeElement[pa].EI_flexion);
				//printf("EI_flexion_cable of cable %d is %lf\n",pa,TypeElement[pa].EI_flexion);
				}
			if (strcmp(chaine,"tarp") == 0)
				{
				/*lecture du numero (int) du panneau concerne !!*/
				itmp = fscanf(fic,"%d",&pa);
				panneau[pa].tarp = 1;
				printf("lecture de tarp diamond, panneau : %d\n",pa);
				Structure.nb_tarp_diamond += 1;
				}
			if (strcmp(chaine,"tarp_hexa") == 0)
				{
				/*lecture du numero (int) du panneau concerne !!*/
				itmp = fscanf(fic,"%d",&pa);
				TypeSurfHexa[pa].tarp = 1;
				printf("lecture de tarp hexa, panneau : %d\n",pa);
				Structure.nb_tarp_hexa += 1;
				}
			if (strcmp(chaine,"catch") == 0)
				{
				itmp = fscanf(fic,"%lf",&Prise.PR);	/*prise en m3*/
				itmp = fscanf(fic,"%lf",&Prise.PE);	/*perimetre du cul en m*/
				itmp = fscanf(fic,"%lf",&Prise.TA);	/*taille moyenne des poissons en m3*/
				itmp = fscanf(fic,"%lf",&Prise.EI);	/*mesh opening stiffness en Nm^2*/
				PE3 = pow(Prise.PE,3.0);
				PE4 = pow(Prise.PE,4.0);
				VI = 0.5 * RHO * Courant.vitesse*Courant.vitesse;
				if (Prise.EI == 0.0)
					{
					//PA mostly
					Prise.volume = Prise.PR * (1.72*(pow(Prise.PR/PE3,-0.075)) 
					                        + 0.046*(pow(Prise.TA/PE3,-0.034)) - 0.0772);
					}
				else
					{
					//PE mostly Prise.EI around 0.001
					Prise.volume = Prise.PR * (   1.785   *(pow(Prise.PR/PE3    ,-0.0548  )) 
							    	   - 1.652E+10*(pow(Prise.TA/PE3    ,1.919    )) 
							    	    + 4.406E-3*(pow(Prise.EI/PE4/VI ,-0.172   )) - 0.015709);
					}
				if (WB < Prise.PR) 	WB = Prise.PR;
				if (WB < 0.0) 		WB = 0.0;
				printf("Catch characteristics : PR(m^3): %lf, PE(m): %lf, TA (m^3): %lf, EI (N.m^2): %lf, WB (m^3): %lf\n",Prise.PR,Prise.PE,Prise.TA,Prise.EI,Prise.volume);
				}
			if (strcmp(chaine,"catch2_volume") == 0)
				{
				Structure.nb_catch2_volume = Structure.nb_catch2_volume + 1;
				if (Structure.nb_catch2_volume > 5)
					{
					printf("ATTENTION the nb of Catch2_volume is limited to 5  \n");
					exit(0);
					}
				itmp = fscanf(fic,"%lf",&Catch2_volume[Structure.nb_catch2_volume].volume);		/*prise en m3*/
				itmp = fscanf(fic,"%d",&Catch2_volume[Structure.nb_catch2_volume].nb_panel_catch2);	/*panel nb*/
				/*Catch2_volume[Structure.nb_catch2_volume].panel_catch2 = (int *) Malloc_int(1 + Catch2_volume[Structure.nb_catch2_volume].nb_panel_catch2);*/
				/**********************************************/
				Catch2_volume[Structure.nb_catch2_volume].panel_catch2= (int *) malloc((1 + Catch2_volume[Structure.nb_catch2_volume].nb_panel_catch2) * sizeof(int));
				if (Catch2_volume[Structure.nb_catch2_volume].panel_catch2    == NULL)
					{
					printf("Catch2_volume[Structure.nb_catch2_volume].panel_catch2  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				for (pa=1;pa<=Catch2_volume[Structure.nb_catch2_volume].nb_panel_catch2;pa++)
					{
					itmp = fscanf(fic,"%d",&Catch2_volume[Structure.nb_catch2_volume].panel_catch2[pa]);	/*panel nb*/
					if ((Catch2_volume[Structure.nb_catch2_volume].panel_catch2[pa]>Structure.NbTypesurf) || (Catch2_volume[Structure.nb_catch2_volume].panel_catch2[pa]<1))
						{
						printf("the nb %d Catch2_volume panels must be between 1 and %d  (included) \n",Structure.nb_catch2_volume,Structure.NbTypesurf);
						exit(0);
						}
					}
				printf("Catch2_volume Structure.nb_catch2_volume = %d  ",Structure.nb_catch2_volume);
				printf("Volume %lf  ",Catch2_volume[Structure.nb_catch2_volume].volume);
				printf("nb panels %d  ",Catch2_volume[Structure.nb_catch2_volume].nb_panel_catch2);
				printf("panels :");
				for (pa=1;pa<=Catch2_volume[Structure.nb_catch2_volume].nb_panel_catch2;pa++)
					{
					printf(" %d",Catch2_volume[Structure.nb_catch2_volume].panel_catch2[pa]);
					}
				printf("\n");
				}



			if (strcmp(chaine,"balls") == 0)
				{
				printf("balls reading \n");
				itmp = fscanf(fic,"%d",&Ball.nb);
				printf("Ball.nb = %d \n",Ball.nb);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				itmp = fscanf(fic,"%lf",&tmp_d2);
				itmp = fscanf(fic,"%lf",&tmp_d3);
				itmp = fscanf(fic,"%lf",&tmp_d4);
				itmp = fscanf(fic,"%lf",&tmp_d5);
				itmp = fscanf(fic,"%d",&tmp_i1);
				}
			if (strcmp(chaine,"balls_2") == 0)
				{
				printf("balls_2 reading \n");
				itmp = fscanf(fic,"%d",&Ball.nb);
				printf("Ball.nb = %d \n",Ball.nb);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				itmp = fscanf(fic,"%lf",&tmp_d2);
				itmp = fscanf(fic,"%lf",&tmp_d3);
				itmp = fscanf(fic,"%lf",&tmp_d4);
				itmp = fscanf(fic,"%lf",&tmp_d5);
				itmp = fscanf(fic,"%d",&tmp_i1);
				itmp = fscanf(fic,"%lf",&tmp_d6);
				itmp = fscanf(fic,"%lf",&tmp_d7);
				itmp = fscanf(fic,"%lf",&tmp_d8);
				}
			if (strcmp(chaine,"spheric_limit") == 0)
				{
				printf("spheric limit \n");
				itmp = fscanf(fic,"%lf",&Spheric_limit.x);
				itmp = fscanf(fic,"%lf",&Spheric_limit.y);
				itmp = fscanf(fic,"%lf",&Spheric_limit.z);
				itmp = fscanf(fic,"%lf",&Spheric_limit.radius);
				itmp = fscanf(fic,"%lf",&Spheric_limit.kc);
				itmp = fscanf(fic,"%lf",&Spheric_limit.kt);
				printf("sphere centre %lf %lf %lf radius %lf stiffnesses %lf %lf \n",Spheric_limit.x,Spheric_limit.y,Spheric_limit.z,Spheric_limit.radius,Spheric_limit.kc,Spheric_limit.kt);
				}
			if (strcmp(chaine,"Auto_convergence") == 0)
				{
				printf("Auto_convergence \n");
				Auto_convergence = 1;
				}
			if (strcmp(chaine,"elem_noeud") == 0)
				{
				itmp = fscanf(fic,"%d",&elem_no1);
				itmp = fscanf(fic,"%d",&elem_no2);

				for (zi=elem_no1;zi<=elem_no2;zi++)	
					{
					TypeElement[zi].noeud_trainee = 0;	//volume des barres reporté sur toute la longueur des barres
					}
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

				if (strcmp(chaine,"ligne_tot") == 0)
				{
				}

				if (strcmp(chaine,"ligne_ordre") == 0)
				{
				}
				
				if (strcmp(chaine,"accroche") == 0)
				{
				}
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
			if (strcmp(chaine,"nb_barre") == 0)
			{
				itmp = fscanf(fic,"%d",&num_elem_choisi);
				itmp = fscanf(fic,"%d",&nb_barre_choisi);

				TypeElement[num_elem_choisi].nb_barre=nb_barre_choisi;
			}

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

				for (i=1;i<=Structure.NbTypeelem;i++)
				{
					deb=TypeElement[i].extremite[1];
					fin=TypeElement[i].extremite[2];

					if (Noeud[deb].type == tp_noeud || Noeud[fin].type == tp_noeud)
					{
						TypeElement[i].nb_barre=nb_barre_choisi;
						modif_materiau_elem(i, raideur_traction_choisie, raideur_compression_choisie, masse_volumique_choisie, diam_hydro_choisi, coeff_trainee_normal_choisi, coeff_trainee_tangent_choisi);
					}
				}		

			}


			if (strcmp(chaine,"cage_volume") == 0)
				{
				Structure.nb_cage_volume = Structure.nb_cage_volume + 1;
				if (Structure.nb_cage_volume > 20)
					{
					printf("ATTENTION le nombre de volume de cages calculables est limité à 20 \n");
					exit(0);
					}
				itmp = fscanf(fic,"%d",&pan11);
				itmp = fscanf(fic,"%d",&pan22);
				Cage_volume[Structure.nb_cage_volume].nb_panel_catch2 = pan22 - pan11 + 1;	/*panel nb*/
				Volume_cage[Structure.nb_cage_volume].nb_panel_catch2 = pan22 - pan11 + 1;	/*panel nb*/
				/*Cage_volume[Structure.nb_cage_volume].panel_catch2 = (int *) Malloc_int(1 + Cage_volume[Structure.nb_cage_volume].nb_panel_catch2);*/
				/**********************************************/
				Cage_volume[Structure.nb_cage_volume].panel_catch2= (int *) malloc((1 + Cage_volume[Structure.nb_cage_volume].nb_panel_catch2) * sizeof(int));
				if (Cage_volume[Structure.nb_cage_volume].panel_catch2    == NULL)
					{
					printf("Cage_volume[Structure.nb_cage_volume].panel_catch2  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				/**********************************************/
				Volume_cage[Structure.nb_cage_volume].panel_catch2= (int *) malloc((1 + Volume_cage[Structure.nb_cage_volume].nb_panel_catch2) * sizeof(int));
				if (Volume_cage[Structure.nb_cage_volume].panel_catch2    == NULL)
					{
					printf("Cage_volume[Structure.nb_cage_volume].panel_catch2  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				for (pa=1;pa<=Cage_volume[Structure.nb_cage_volume].nb_panel_catch2;pa++)
					{
					Cage_volume[Structure.nb_cage_volume].panel_catch2[pa]=pan11+pa-1;	/*panel nb*/
					Volume_cage[Structure.nb_cage_volume].panel_catch2[pa]=pan11+pa-1;	/*panel nb*/
					if ((Cage_volume[Structure.nb_cage_volume].panel_catch2[pa]>Structure.NbTypesurf) || (Cage_volume[Structure.nb_cage_volume].panel_catch2[pa]<1))
						{
						printf("the nb %d Cage_volume panels must be between 1 and %d (included) \n",Structure.nb_cage_volume,Structure.NbTypesurf);
						exit(0);
						}
					if ((Volume_cage[Structure.nb_cage_volume].panel_catch2[pa]>Structure.NbTypesurf) || (Volume_cage[Structure.nb_cage_volume].panel_catch2[pa]<1))
						{
						printf("the nb %d Volume_cage panels must be between 1 and %d (included) \n",Structure.nb_cage_volume,Structure.NbTypesurf);
						exit(0);
						}
					}
				}



			/**********************************************************************************************************************/
			/**********************************************************************************************************************/
			}
		/*
		printf("on est ici bbbbbbbb chaine = %s comment = %s\n",chaine,comment);
		*/
		}
	/*
	printf("on est ici cccccccc chaine = %s comment = %s\n",chaine,comment);
	*/
	
	/**************************************************************/


	fclose(fic);

	/*free xmat, */
	/*
	pourquoi ca ne marche pas ??????
	if (xmat						!= NULL)        free(xmat);
	*/
	}

int lecture_display_dyna(FILE *fic, char *chain)
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
  	
	while (c != EOF)    
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
	
	
