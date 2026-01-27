#define PRINCIPAL 0
#include "phobos.h"

void charger_phobos()
	{
	/*chargement du fichier *.don, le nom generique est stocke dans fname1*/
	if (Structure.graphic == 1)
		{		
		strcpy(newfic , (char *) GetFile("../data_2001"));
		}
	if ((Structure.graphic == 2) || (Structure.graphic == 3))
		{
  		strcpy(newfic,Structure.nomfichier1);
		}
	//printf("Fichier selectionne: 			%s\n" , newfic);
	charger(newfic);
	}

void modif_materiau_elem(int num_elem_choisi, double raideur_traction_choisie, double raideur_compression_choisie, double masse_volumique_choisie, double diam_hydro_choisi, double coeff_trainee_normal_choisi, double coeff_trainee_tangent_choisi)
{
	element[num_elem_choisi].raideur_traction=raideur_traction_choisie;
	element[num_elem_choisi].raideur_compression=raideur_compression_choisie;
	element[num_elem_choisi].rhoelement=masse_volumique_choisie;
	element[num_elem_choisi].diametrehydro=diam_hydro_choisi;
	element[num_elem_choisi].cdnormal=coeff_trainee_normal_choisi;
	element[num_elem_choisi].ftangent=coeff_trainee_tangent_choisi;
}

	
void charger(char *nomfichier)
	{
	/*chargement du fichier *.don, le nom generique est stocke dans fname1*/
	char c,t1[256],*buffer;
	char chaine[] = "                                               ";
	char chainebis[] = "                                               ";
	char comment[] = "                                               ";
	char tonom[200];
	int i,j,jj,pa,pb,no,type_ref,noeud_ref,zi,tmp_i1,temp_int,temp2_int,p1,p2,p3,p0,itmp;
	FILE *fic,*f3;
	double dist,speed_ball,p1u,p2u,p3u,p0u,p1v,p2v,p3v,p0v,p1x,p2x,p3x,p0x,p1y,p2y,p3y,p0y,p1z,p2z,p3z,p0z;
	double surface,norme,alpha,beta,U2X,U2Y,U2Z,V2X,V2Y,V2Z;
	double WB,PE3,tmp_d1,tmp_d2,tmp_d3,tmp_d4,tmp_d5,tmp_d6,tmp_d7,tmp_d8,time,xxp,yyp,zzp,xxo,yyo,zzo,xx1,yy1,zz1,teta;
	double xxp1,xxp2,xxp3,xxp4,yyp1,yyp2,yyp3,yyp4,v1[4],v2[4];

	double xxp11,xxp12,xxp21,xxp22,xxp31,xxp32,xxp41,xxp42,xxp51,xxp52,xxp61,xxp62,xxp71,xxp72,xxp81,xxp82;
	double yyp11,yyp12,yyp21,yyp22,yyp31,yyp32,yyp41,yyp42,yyp51,yyp52,yyp61,yyp62,yyp71,yyp72,yyp81,yyp82;

	double nnu,nnv;

	double diametre_pehd;
	double epaisseur_pehd;
	double rho_pehd,homot_ratio;
	
	int E_numero;
	double S_Nb,S_Diam,S_Float,L_Float,S_Vol_Unit,S_Mass_Unit,S_Cd,S_Surf_Unit,S_Max_Float;
	double E_Length,E_Density,E_Diam,E_Cdn,E_Vol,E_Mass,E_Surf;
	double F_Length,F_Density,F_Diam,F_Cdn,F_Vol,F_Mass,F_Surf;
	
	double txmin,txmax,tymin,tymax,tzmin,tzmax;

/* debut modifdp du 4 mars 2010*/
	int pa1,no1,pa2,no2,first,node_type,number;
	double pr1,pr2,step,dist_c;
/* fin modifdp du 4 mars 2010*/


/********************************** MODIF ARNAUD 07/10/09 **************************/

	double* coord_noeud_x = NULL;
	double* coord_noeud_y = NULL;
	double* coord_noeud_z = NULL;
	int* type_type_noeud = NULL;
	double* lg_lg = NULL;
	
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
	double actual_foil_surface, model_foil_surface,model_mass_in_air,model_mass_in_water,foil_cd,foil_cl,foil_cz;
	double ref_length_model,ref_volume_model,ratio_mass_in_air_volume,ref_length_actual,ref_volume_actual;
	double actual_mass_in_air,model_density,actual_volume,Fd,Fl;
	char temp1_char,temp2_char;
	int temp1_int;
	
/************************************MODIF ARNAUD *******************/

  	/*strcpy(tonom,nomfichier);
        j=strlen(tonom);
        while ((tonom[j])!='.' && j>0) j--;
        if (tonom[j]=='.') tonom[j]=0; 
  	strcat(tonom,".don");
	fic = fopen(tonom,"r");

	if(newfic[0])
		{
		printf("Fichier selectionne: 			%s\n" , newfic);
		Flag_Fichier_charge = 1;
		}
	else
		{
		printf("fichier non trouve\n");
		return;
		}
        strcpy(fname1,newfic);*/
	//printf("Fichier selectionne: 			%s\n" , nomfichier);
	Flag_Fichier_charge = 1;
        strcpy(fname1,nomfichier);
	//printf("Fichier selectionne: 			%s\n" , fname1);
        j=strlen(fname1);
	//printf("length: 			%d\n" , j);
        while ((fname1[j])!='.' && j>0) j--;
        if (fname1[j]=='.') fname1[j]=0;

	//printf("Fichier selectionne: 			%s\n" , fname1);
	//printf("fname1 = 				%s \n",fname1);

	/* Lecture du fichier selectionne */	
	strcpy(newfic,fname1);
	strcat(newfic,".don");
	//printf("newfic = 				%s \n",newfic);
	fic = fopen(newfic,"r");

	Structure.nb_winch = 0;
	Structure.version = 1;
	lecture_chaine(fic,chaine);		

	i = strlen(chaine);
	//printf("chaine = %s  ",chaine);
	//printf("longueur chaine = %d\n",i);/**/
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
    	itmp = fscanf(fic,"%d\n",&Structure.orientation);
	if ( (Structure.orientation != 1) && (Structure.orientation != 2) && (Structure.orientation != 3))
		{
		printf(" Structure.orientation %4d doit etre = a 1 2 ou 3  \n",Structure.orientation );
		exit(0);
		}
		
	/*panneaux*****************************************************/
	do  c=fgetc(fic); while (c !=':'); 
    	itmp = fscanf(fic,"%d\n",&Structure.NbTypesurf);
	if ( Structure.NbTypesurf >= NBMAXPANNEAU)
		{
		printf(" NBMAXPANNEAU trop petit %4d < %4d \n",NBMAXPANNEAU,Structure.NbTypesurf );
		exit(0);
		}
    	printf("Structure.NbTypesurf  		= %8d\n", Structure.NbTypesurf);
	Structure.nb_total = 0;
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
	    	do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&temp_int);
		if (temp_int != pa) 	printf("WARNING le panneau %d a noté noté %d  \n",pa,temp_int);

	    	do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&panneau[pa].nb_noeud_contour);
		/**********************************************/
  		panneau[pa].noeud_contour = (int *) malloc((1 + panneau[pa].nb_noeud_contour) * sizeof(int));
		if (panneau[pa].noeud_contour    == NULL)
			{
			printf(" panneau[pa].noeud_contour 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		panneau[pa].suivant_contour = (int *) malloc((1 + panneau[pa].nb_noeud_contour) * sizeof(int));
		if (panneau[pa].suivant_contour    == NULL)
			{
			printf(" panneau[pa].suivant_contour 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		panneau[pa].type_suivant_contour = (int *) malloc((1 + panneau[pa].nb_noeud_contour) * sizeof(int));
		if (panneau[pa].type_suivant_contour    == NULL)
			{
			printf(" panneau[pa].type_suivant_contour 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		//printf("nb_noeud_contour %8d ", panneau[pa].nb_noeud_contour);
		buffer = fgets(t1,256,fic);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{
			Structure.nb_total++;
			if (Structure.nb_total >= NBMAXNOEUD)
				{
				printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
				exit(0);
				}
			itmp = fscanf(fic,"%d",&panneau[pa].noeud_contour[no]);
			panneau[pa].noeud_contour[no] = Structure.nb_total;
			panneau[pa].suivant_contour[no] = 0;
			if (Structure.orientation == 1)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[panneau[pa].noeud_contour[no]].z,
						     &noeud[panneau[pa].noeud_contour[no]].x,
						     &noeud[panneau[pa].noeud_contour[no]].y);
				}
			if (Structure.orientation == 2)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[panneau[pa].noeud_contour[no]].y,
						     &noeud[panneau[pa].noeud_contour[no]].z,
						     &noeud[panneau[pa].noeud_contour[no]].x);
				}
			if (Structure.orientation == 3)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[panneau[pa].noeud_contour[no]].x,
						     &noeud[panneau[pa].noeud_contour[no]].y,
						     &noeud[panneau[pa].noeud_contour[no]].z);
				}
			itmp = fscanf(fic,"%lf %lf",&noeud[panneau[pa].noeud_contour[no]].U,
					   &noeud[panneau[pa].noeud_contour[no]].V);
			noeud[panneau[pa].noeud_contour[no]].u =  noeud[panneau[pa].noeud_contour[no]].U + noeud[panneau[pa].noeud_contour[no]].V; 
			noeud[panneau[pa].noeud_contour[no]].v = -noeud[panneau[pa].noeud_contour[no]].U + noeud[panneau[pa].noeud_contour[no]].V; 
			itmp = fscanf(fic,"%d",&noeud[panneau[pa].noeud_contour[no]].type);
			itmp = fscanf(fic,"%d",&panneau[pa].type_suivant_contour[no]);
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
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&panneau[pa].pas_maillage);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&panneau[pa].type_noeud);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&panneau[pa].type_maillage);
    		
		//printf("t1  : %s\n",t1); 
		//printf("raideur_traction %9.2f ",panneau[pa].raideur_traction );
		//printf("cdnormal %9.2f ",panneau[pa].cdnormal );
		//printf("ftangent %9.2f ",panneau[pa].ftangent );
		//printf("type_noeud %9d ",panneau[pa].type_noeud );
		//printf("pas_maillage %9.2f\n",panneau[pa].pas_maillage );/**/
		}
		
	/*panneaux hexagonaux*******************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	itmp = fscanf(fic,"%d\n",&Structure.NbTypesurf_hexa);
	if ( Structure.NbTypesurf_hexa >= NBMAXPANHEXA)
		{
		printf(" NBMAXPANHEXA trop petit %4d < %4d \n",NBMAXPANHEXA,Structure.NbTypesurf_hexa );
		exit(0);
		}
    	printf("Structure.NbTypesurf_hexa  	= %8d\n", Structure.NbTypesurf_hexa);
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{
	    	do  c=fgetc(fic); while (c !=':'); 
	    	do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&pan_hexa[pa].nb_noeud_contour);
		/**********************************************/
  		pan_hexa[pa].noeud_contour = (int *) malloc((1 + pan_hexa[pa].nb_noeud_contour) * sizeof(int));
		if (pan_hexa[pa].noeud_contour    == NULL)
			{
			printf(" pan_hexa[pa].noeud_contour 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		pan_hexa[pa].suivant_contour = (int *) malloc((1 + pan_hexa[pa].nb_noeud_contour) * sizeof(int));
		if (pan_hexa[pa].suivant_contour    == NULL)
			{
			printf(" pan_hexa[pa].suivant_contour 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		pan_hexa[pa].type_suivant_contour = (int *) malloc((1 + pan_hexa[pa].nb_noeud_contour) * sizeof(int));
		if (pan_hexa[pa].type_suivant_contour    == NULL)
			{
			printf(" pan_hexa[pa].type_suivant_contour 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		//printf("nb_noeud_contour  = %8d\n", pan_hexa[pa].nb_noeud_contour);
		buffer = fgets(t1,256,fic);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{
			Structure.nb_total++;
			if (Structure.nb_total >= NBMAXNOEUD)
				{
				printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
				exit(0);
				}
			itmp = fscanf(fic,"%d",&pan_hexa[pa].noeud_contour[no]);
			pan_hexa[pa].noeud_contour[no] = Structure.nb_total;
			pan_hexa[pa].suivant_contour[no] = 0;
			if (Structure.orientation == 1)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[pan_hexa[pa].noeud_contour[no]].z,
						     &noeud[pan_hexa[pa].noeud_contour[no]].x,
						     &noeud[pan_hexa[pa].noeud_contour[no]].y);
				}
			if (Structure.orientation == 2)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[pan_hexa[pa].noeud_contour[no]].y,
						     &noeud[pan_hexa[pa].noeud_contour[no]].z,
						     &noeud[pan_hexa[pa].noeud_contour[no]].x);
				}
			if (Structure.orientation == 3)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[pan_hexa[pa].noeud_contour[no]].x,
						     &noeud[pan_hexa[pa].noeud_contour[no]].y,
						     &noeud[pan_hexa[pa].noeud_contour[no]].z);
				}
			itmp = fscanf(fic,"%lf %lf",&noeud[pan_hexa[pa].noeud_contour[no]].U,
					   &noeud[pan_hexa[pa].noeud_contour[no]].V);
			noeud[pan_hexa[pa].noeud_contour[no]].u =  noeud[pan_hexa[pa].noeud_contour[no]].U	+
			noeud[pan_hexa[pa].noeud_contour[no]].V; 
			noeud[pan_hexa[pa].noeud_contour[no]].v = -noeud[pan_hexa[pa].noeud_contour[no]].U	+
			noeud[pan_hexa[pa].noeud_contour[no]].V; 
			itmp = fscanf(fic,"%d",&noeud[pan_hexa[pa].noeud_contour[no]].type);
			itmp = fscanf(fic,"%d",&pan_hexa[pa].type_suivant_contour[no]);
			}
		buffer = fgets(t1,256,fic); 
		buffer = fgets(t1,256,fic); 
    		do  c=fgetc(fic); while (c !=':');
    		itmp = fscanf(fic,"%f%f%f\n",&pan_hexa[pa].raideur_traction_l,&pan_hexa[pa].raideur_traction_m,&pan_hexa[pa].raideur_traction_n);
    		do  c=fgetc(fic); while (c !=':'); 
     		itmp = fscanf(fic,"%f%f%f\n",&pan_hexa[pa].raideur_compression_l,&pan_hexa[pa].raideur_compression_m,&pan_hexa[pa].raideur_compression_n);
    		do  c=fgetc(fic); while (c !=':'); 
    		itmp = fscanf(fic,"%f%f%f\n",&pan_hexa[pa].lo_repos,&pan_hexa[pa].mo_repos,&pan_hexa[pa].no_repos);
    		do  c=fgetc(fic); while (c !=':'); 
     		itmp = fscanf(fic,"%f%f%f\n",&pan_hexa[pa].diam_hydro_l,&pan_hexa[pa].diam_hydro_m,&pan_hexa[pa].diam_hydro_n);
  		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&pan_hexa[pa].rho);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&pan_hexa[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&pan_hexa[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%f\n",&pan_hexa[pa].pas_maillage);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&pan_hexa[pa].type_noeud);
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&pan_hexa[pa].type_maillage);
    		
		/*printf("t1  : %s\n",t1); 
		printf("x 	: %9.2f\n",noeud[pan_hexa[pa].noeud_contour[no]].x);
		printf("raideur_traction 	: %9.2f\n",pan_hexa[pa].raideur_traction_l );
		printf("cdnormal 		: %9.2f\n",pan_hexa[pa].cdnormal );
		printf("ftangent 		: %9.2f\n",pan_hexa[pa].ftangent );
		printf("type_noeud 		: %9d\n",pan_hexa[pa].type_noeud );
		printf("pas_maillage 		: %9.2f\n",pan_hexa[pa].pas_maillage );*/
		}
		
	/*elements*****************************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	itmp = fscanf(fic,"%d\n",&Structure.NbTypeelem);
	if (Structure.NbTypeelem >= NBMAXELEMENT)
		{
		printf(" NBMAXELEMENT trop petit %4d < %4d \n",NBMAXELEMENT,Structure.NbTypeelem );
		exit(0);
		}
	printf("Structure.NbTypeelem  		= %8d\n", Structure.NbTypeelem); 
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{
	    	do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d\n",&temp_int);
		if (temp_int != pa) 	printf("WARNING l'élement %d a noté noté %d  \n",pa,temp_int);

    		do  c=fgetc(fic); while (c !=':'); 
		for (no=1;no<=2;no++)
			{
			Structure.nb_total++;
			if (Structure.nb_total >= NBMAXNOEUD)
				{
				printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
				exit(0);
				}
			itmp = fscanf(fic,"%d",&element[pa].extremite[no]);
			element[pa].extremite[no] = Structure.nb_total;
			if (Structure.orientation == 1)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[element[pa].extremite[no]].z,
						     &noeud[element[pa].extremite[no]].x,
						     &noeud[element[pa].extremite[no]].y);
				}
			if (Structure.orientation == 2)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[element[pa].extremite[no]].y,
						     &noeud[element[pa].extremite[no]].z,
						     &noeud[element[pa].extremite[no]].x);
				}
			if (Structure.orientation == 3)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[element[pa].extremite[no]].x,
						     &noeud[element[pa].extremite[no]].y,
						     &noeud[element[pa].extremite[no]].z);
				}
			itmp = fscanf(fic,"%d",&noeud[element[pa].extremite[no]].type);
			}
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&element[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&element[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&element[pa].lgrepos);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&element[pa].rhoelement);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&element[pa].diametrehydro);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&element[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&element[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&element[pa].nb_barre);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&element[pa].type_noeud);
		/*printf("longueur_repos = %8.3f  ",element[pa].lgrepos);
		printf("nb barre = %8d  \n",element[pa].nb_barre);*/
		/**********************************************/
  		element[pa].noeud = (int *) malloc((1 + element[pa].nb_barre) * sizeof(int));
		if (element[pa].noeud    == NULL)
			{
			printf(" element[pa].noeud 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		element[pa].barre = (int *) malloc((1 + element[pa].nb_barre) * sizeof(int));
		if (element[pa].barre    == NULL)
			{
			printf(" element[pa].barre 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		element[pa].prop = (double *) malloc((1 + element[pa].nb_barre) * sizeof(double));
		if (element[pa].prop    == NULL)
			{
			printf(" element[pa].prop 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		element[pa].slider = 0;	//default value this element is not part of a slider
    		}

	/*coulisses*****************************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	itmp = fscanf(fic,"%d\n",&Structure.nombreCoulisses);
	if (Structure.nombreCoulisses >= NBMAXELEMENT)
		{
		printf(" NBMAXELEMENT trop petit %4d < %4d \n",NBMAXELEMENT,Structure.nombreCoulisses );
		exit(0);
		}
	printf("Structure.nombreCoulisses  	= %8d\n", Structure.nombreCoulisses); 
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); 
    		do  c=fgetc(fic); while (c !=':'); 
		for (no=1;no<=2;no++)
			{
			Structure.nb_total++;
			if (Structure.nb_total >= NBMAXNOEUD)
				{
				printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
				exit(0);
				}
			itmp = fscanf(fic,"%d",&coulisse[pa].extremite[no]);
			coulisse[pa].extremite[no] = Structure.nb_total;
			if (Structure.orientation == 1)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[coulisse[pa].extremite[no]].z,
						     &noeud[coulisse[pa].extremite[no]].x,
						     &noeud[coulisse[pa].extremite[no]].y);
				}
			if (Structure.orientation == 2)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[coulisse[pa].extremite[no]].y,
						     &noeud[coulisse[pa].extremite[no]].z,
						     &noeud[coulisse[pa].extremite[no]].x);
				}
			if (Structure.orientation == 3)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[coulisse[pa].extremite[no]].x,
						     &noeud[coulisse[pa].extremite[no]].y,
						     &noeud[coulisse[pa].extremite[no]].z);
				}
			itmp = fscanf(fic,"%d",&noeud[coulisse[pa].extremite[no]].type);
			}
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&coulisse[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&coulisse[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&coulisse[pa].lgrepos);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&coulisse[pa].rhocoulisse);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&coulisse[pa].diametrehydro);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&coulisse[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&coulisse[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&coulisse[pa].nb_noeud);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&coulisse[pa].type_noeud);
		printf("longueur_repos = %8.2f  \n",coulisse[pa].lgrepos);

		/**********************************************/
  		coulisse[pa].noeud = (int *) malloc((1 + coulisse[pa].nb_noeud) * sizeof(int));
		if (coulisse[pa].noeud    == NULL)
			{
			printf(" coulisse[pa].noeud 1 = NULL  \n" );
			exit(0);
			}

		/**********************************************/
    		}

if (Structure.version >= 2)
	{
	/*winchs*****************************************************/
    	do  c=fgetc(fic); while (c !=':'); 
    	itmp = fscanf(fic,"%d\n",&Structure.nb_winch);
	if (Structure.nb_winch >= NBMAXELEMENT)
		{
		printf(" NBMAXELEMENT trop petit %4d < %4d \n",NBMAXELEMENT,Structure.nb_winch );
		exit(0);
		}
	printf("Structure.nb_winch  = %8d\n", Structure.nb_winch); 
	for (pa=1;pa<=Structure.nb_winch;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); 
    		do  c=fgetc(fic); while (c !=':'); 
		for (no=1;no<=2;no++)
			{
			Structure.nb_total++;
			if (Structure.nb_total >= NBMAXNOEUD)
				{
				printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
				exit(0);
				}
			itmp = fscanf(fic,"%d",&winch[pa].extremite[no]);
			winch[pa].extremite[no] = Structure.nb_total;
			if (Structure.orientation == 1)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[winch[pa].extremite[no]].z,
						     &noeud[winch[pa].extremite[no]].x,
						     &noeud[winch[pa].extremite[no]].y);
				}
			if (Structure.orientation == 2)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[winch[pa].extremite[no]].y,
						     &noeud[winch[pa].extremite[no]].z,
						     &noeud[winch[pa].extremite[no]].x);
				}
			if (Structure.orientation == 3)
				{
				itmp = fscanf(fic,"%lf %lf%lf",&noeud[winch[pa].extremite[no]].x,
						     &noeud[winch[pa].extremite[no]].y,
						     &noeud[winch[pa].extremite[no]].z);
				}
			itmp = fscanf(fic,"%d",&noeud[winch[pa].extremite[no]].type);
			}
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&winch[pa].raideur_traction);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&winch[pa].raideur_compression);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&winch[pa].longueur_repos);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&winch[pa].rho);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&winch[pa].diam_hydro);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&winch[pa].cdnormal);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&winch[pa].ftangent);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%lf\n",&winch[pa].adjust_force);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&winch[pa].nb_barre);
    		do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&winch[pa].type_noeud);
		printf("longueur_repos = %8.3f  \n",winch[pa].longueur_repos);
		/**********************************************/
  		winch[pa].noeud = (int *) malloc((1 + winch[pa].nb_barre) * sizeof(int));
		if (winch[pa].noeud    == NULL)
			{
			printf(" winch[pa].noeud 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		winch[pa].barre = (int *) malloc((1 + winch[pa].nb_barre) * sizeof(int));
		if (winch[pa].barre    == NULL)
			{
			printf(" winch[pa].barre 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
    		}
    	}

	/*liaisons*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Structure.nb_liaison); 
	printf("Structure.nb_liaison  		= %8d\n", Structure.nb_liaison);
	if ( Structure.nb_liaison >= NBMAXLIAISON)
		{
		printf(" NBMAXLIAISON trop petit %4d < %4d \n",NBMAXLIAISON,Structure.nb_liaison );
		exit(0);
		}
	for (pa=1;pa<=Structure.nb_liaison;pa++)
		{
    		do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d",&Lien[pa].nb_liaison);
		//printf("Lien[%d].nb_liaison  = %8d\n",pa,Lien[pa].nb_liaison);
		/**********************************************/
  		Lien[pa].structure = (int *) malloc((1 + Lien[pa].nb_liaison) * sizeof(int));
		if (Lien[pa].structure    == NULL)
			{
			printf("Lien[pa].structure  1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		Lien[pa].extremite = (int *) malloc((1 + Lien[pa].nb_liaison) * sizeof(int));
		if (Lien[pa].extremite    == NULL)
			{
			printf("Lien[pa].extremite  1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		Lien[pa].noeud = (int *) malloc((1 + Lien[pa].nb_liaison) * sizeof(int));
		if (Lien[pa].noeud    == NULL)
			{
			printf("Lien[pa].noeud  1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		Lien[pa].type = (char *) malloc((1 + Lien[pa].nb_liaison) * sizeof(char));
		if (Lien[pa].type    == NULL)
			{
			printf("Lien[pa].type  1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		for (i=1;i<=Lien[pa].nb_liaison;i++)
			{
			do  
				{
				c=fgetc(fic); 
				/*printf("'%c'",c);*/
				}
			while (c ==' '); 
			if ((c =='p') || (c =='h') || (c =='e') || (c =='c') || (c =='w')) Lien[pa].type[i] = c;
			else Lien[pa].type[i] = fgetc(fic);
			if((Lien[pa].type[i] != 'p') && (Lien[pa].type[i] != 'h') && (Lien[pa].type[i] != 'e') && (Lien[pa].type[i] !='c') && (Lien[pa].type[i] !='w'))
				{
				printf("warning : la structure %d de la liaison %d est inconnue\n",i,pa);
				}
    			do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d",&Lien[pa].structure[i]);
			if (Lien[pa].type[i] == 'p')
				{
				if((Lien[pa].structure[i]<1) || (Lien[pa].structure[i]>Structure.NbTypesurf))
					{
					printf("warning : le panneau %d de la liaison %d est invalide\n",Lien[pa].structure[i],pa);
					exit(0);
					}
				}
			if (Lien[pa].type[i] == 'h')
				{
				if((Lien[pa].structure[i]<1) || (Lien[pa].structure[i]>Structure.NbTypesurf_hexa))
					{
					printf("warning : le panneau hexa %d de la liaison %d est invalide\n",Lien[pa].structure[i],pa);
					exit(0);
					}
				}
			if (Lien[pa].type[i] == 'e')
				{
				if((Lien[pa].structure[i]<1) || (Lien[pa].structure[i]>Structure.NbTypeelem))
					{
					printf("warning : l element %d de la liaison %d est invalide\n",Lien[pa].structure[i],pa);
					exit(0);
					}
				}
			if (Lien[pa].type[i] == 'c')
				{
				if((Lien[pa].structure[i]<1) || (Lien[pa].structure[i]>Structure.nombreCoulisses))
					{
					printf("warning : la coulisse %d de la liaison %d est invalide\n",Lien[pa].structure[i],pa);
					exit(0);
					}
				}
			if (Lien[pa].type[i] == 'c')
				{
				if((Lien[pa].structure[i]<1) || (Lien[pa].structure[i]>Structure.nb_winch))
					{
					printf("warning : the winch %d of the link %d is not valid\n",Lien[pa].structure[i],pa);
					exit(0);
					}
				}
    			do  c=fgetc(fic); while (c !=':'); itmp = fscanf(fic,"%d",&Lien[pa].extremite[i]);
			if (Lien[pa].type[i] == 'p')
				{
				if((Lien[pa].extremite[i]<1) || (Lien[pa].extremite[i]>panneau[Lien[pa].structure[i]].nb_noeud_contour))
					{
					printf("warning : l extremite du panneau %d de la liaison %d est invalide\n",Lien[pa].structure[i],pa);
					exit(0);
					}
				}
			if (Lien[pa].type[i] == 'h')
				{
				if((Lien[pa].extremite[i]<1) || (Lien[pa].extremite[i]>pan_hexa[Lien[pa].structure[i]].nb_noeud_contour))
					{
					printf("warning : l extremite du panneau hexa %d de la liaison %d est invalide\n",Lien[pa].structure[i],pa);
					exit(0);
					}
				}
			if (Lien[pa].type[i] == 'e')
				{
				if((Lien[pa].extremite[i]<1) || (Lien[pa].extremite[i]>2))
					{
					printf("warning : l extremite de l element %d de la liaison %d est invalide\n",Lien[pa].structure[i],pa);
					exit(0);
					}
				}
			if (Lien[pa].type[i] == 'c')
				{
				if((Lien[pa].extremite[i]<1) || (Lien[pa].extremite[i]>2))
					{
					printf("warning : l extremite de la coulisse %d de la liaison %d est invalide\n",Lien[pa].structure[i],pa);
					exit(0);
					}
				}
			if (Lien[pa].type[i] == 'w')
				{
				if((Lien[pa].extremite[i]<1) || (Lien[pa].extremite[i]>2))
					{
					printf("warning : the extremity of the winch %d of the link %d is not valid\n",Lien[pa].structure[i],pa);
					exit(0);
					}
				}
			/*printf("type = %c ",Lien[pa].type[i]);
			printf("structure = %d ",Lien[pa].structure[i]);
			printf("extremite = %d ",Lien[pa].extremite[i]);*/
			if (i == 1)
				{
				if (Lien[pa].type[i] == 'p')
					{
					noeud_ref = panneau[Lien[pa].structure[i]].noeud_contour[Lien[pa].extremite[i]];
					type_ref = noeud[noeud_ref].type;
					}
				if (Lien[pa].type[i] == 'h')
					{
					noeud_ref = pan_hexa[Lien[pa].structure[i]].noeud_contour[Lien[pa].extremite[i]];
					type_ref = noeud[noeud_ref].type;
					}
				if (Lien[pa].type[i] == 'e')
					{
					noeud_ref = element[Lien[pa].structure[i]].extremite[Lien[pa].extremite[i]];
					type_ref = noeud[noeud_ref].type;
					}
				if (Lien[pa].type[i] == 'c')
					{
					noeud_ref = coulisse[Lien[pa].structure[i]].extremite[Lien[pa].extremite[i]];
					type_ref = noeud[noeud_ref].type;
					}
				if (Lien[pa].type[i] == 'w')
					{
					noeud_ref = winch[Lien[pa].structure[i]].extremite[Lien[pa].extremite[i]];
					type_ref = noeud[noeud_ref].type;
					}
				}
			if (i > 1)
				{
				if (Lien[pa].type[i] == 'p')
					{
					noeud_ref = panneau[Lien[pa].structure[i]].noeud_contour[Lien[pa].extremite[i]];
					if (type_ref != noeud[noeud_ref].type)
						{
						printf("warning : la liaison %4d ne lie pas des noeuds de meme type\n",pa);
						}
					}
				if (Lien[pa].type[i] == 'h')
					{
					noeud_ref = pan_hexa[Lien[pa].structure[i]].noeud_contour[Lien[pa].extremite[i]];
					if (type_ref != noeud[noeud_ref].type)
						{
						printf("warning : la liaison %4d ne lie pas des noeuds de meme type\n",pa);
						}
					}
				if (Lien[pa].type[i] == 'e')
					{
					noeud_ref = element[Lien[pa].structure[i]].extremite[Lien[pa].extremite[i]];
					if (type_ref != noeud[noeud_ref].type)
						{
						printf("warning : la liaison %4d ne lie pas des noeuds de meme type\n",pa);
						}
					}
				if (Lien[pa].type[i] == 'c')
					{
					noeud_ref = coulisse[Lien[pa].structure[i]].extremite[Lien[pa].extremite[i]];
					if (type_ref != noeud[noeud_ref].type)
						{
						printf("warning : la liaison %4d ne lie pas des noeuds de meme type\n",pa);
						}
					}
				if (Lien[pa].type[i] == 'w')
					{
					noeud_ref = winch[Lien[pa].structure[i]].extremite[Lien[pa].extremite[i]];
					if (type_ref != noeud[noeud_ref].type)
						{
						printf("warning : the link %4d dont link nodes of the same type\n",pa);
						}
					}
				}
			}
		}
		
	/*ordre de maillage***************************************************/
	
	Structure.nb_ordre_objet = Structure.NbTypesurf + Structure.NbTypeelem + Structure.nombreCoulisses + Structure.NbTypesurf_hexa + Structure.nb_winch;
	printf("Structure.nb_ordre_objet  	= %8d\n", Structure.nb_ordre_objet);
		
	/**********************************************/
  	ordre.type = (char *) malloc((1 + Structure.nb_ordre_objet) * sizeof(char));
	if (ordre.type	 == NULL)
	     	{
	       	printf("ordre.type  1 = NULL  \n" );
	       	exit(0);
	       	}
	/**********************************************/
  	ordre.indice = (int *) malloc((1 + Structure.nb_ordre_objet) * sizeof(int));
	if (ordre.indice    == NULL)
		{
		printf("ordre.indice  1 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	do  
		{
		c=fgetc(fic); 
		//printf("%c",c);/**/
		}
	while (c !=':'); 
	//printf("\n");
		
		
	for (i=1;i<=Structure.nb_ordre_objet;i++)
		{ 
		do 
			{
			c=fgetc(fic); 
			//printf("%c",c);
			}
		while ((c ==' ') || (c =='\r') || (c =='\n') || (c =='\t')); ordre.type[i] = c;
				
		if((ordre.type[i] != 'a') && (ordre.type[i] != 'b') && (ordre.type[i] != 'p') && (ordre.type[i] != 'h') && (ordre.type[i] != 'e') && (ordre.type[i] !='c') && (ordre.type[i] !='w'))
			{
			printf("warning : le type de l'objet %d est inconnu = *%c*\n",i,c);
			}



		if ((c =='a') || (c =='b'))
			{

			if (c =='a')
				{
				printf("Meshing begins by elements, followed by diamond mesh panels, hexagonal mesh panels, sliders and winches\n");
				jj = 0;
				printf("Meshing order:\n");
				for (j=1;j<=Structure.NbTypeelem;j++)		{ jj++;	ordre.type[jj] = 'e';	ordre.indice[jj] = j;	printf("el: %d ",j);}
				printf("\n");
				for (j=1;j<=Structure.NbTypesurf;j++)		{ jj++;	ordre.type[jj] = 'p';	ordre.indice[jj] = j;	printf("pa: %d ",j);	}
				printf("\n");
				for (j=1;j<=Structure.NbTypesurf_hexa;j++)	{ jj++;	ordre.type[jj] = 'h';	ordre.indice[jj] = j;	printf("he: %d ",j);	}
				printf("\n");
				for (j=1;j<=Structure.nombreCoulisses;j++)	{ jj++;	ordre.type[jj] = 'c';	ordre.indice[jj] = j;	printf("co: %d ",j);	}
				printf("\n");
				for (j=1;j<=Structure.nb_winch;j++)		{ jj++;	ordre.type[jj] = 'w';	ordre.indice[jj] = j;	printf("wi: %d ",j);	}
				printf("\n");
				break;
				//exit(0);
				}
			if (c =='b')
				{
				printf("Meshing begins by diamond mesh panels, followed by hexagonal mesh panels, elements, sliders and winches\n");
				jj = 0;
				printf("Meshing order:\n");
				for (j=1;j<=Structure.NbTypesurf;j++)		{ jj++;	ordre.type[jj] = 'p';	ordre.indice[jj] = j;	printf("pa: %d ",j);}
				printf("\n");
				for (j=1;j<=Structure.NbTypesurf_hexa;j++)	{ jj++;	ordre.type[jj] = 'h';	ordre.indice[jj] = j;	printf("he: %d ",j);}
				printf("\n");
				for (j=1;j<=Structure.NbTypeelem;j++)		{ jj++;	ordre.type[jj] = 'e';	ordre.indice[jj] = j;	printf("el: %d ",j);}
				printf("\n");
				for (j=1;j<=Structure.nombreCoulisses;j++)	{ jj++;	ordre.type[jj] = 'c';	ordre.indice[jj] = j;	printf("co: %d ",j);}
				printf("\n");
				for (j=1;j<=Structure.nb_winch;j++)		{ jj++;	ordre.type[jj] = 'w';	ordre.indice[jj] = j;	printf("wi: %d ",j);}
				printf("\n");
				break;
				//exit(0);
				}

			}



		else
			{
			/////////////////////////////////////////////////////////////////////////////////////
	    		do  
	    			{
	    			c=fgetc(fic); 
				//printf("%c",c);
	    			}
	    		while (c !=':');     itmp = fscanf(fic,"%d",&ordre.indice[i]);
	    		//printf("type = %c indice =%d\n",ordre.type[i],ordre.indice[i]);/**/
			if (ordre.type[i] == 'p')
				{
				if((ordre.indice[i]<1) || (ordre.indice[i]>Structure.NbTypesurf))
					{
					printf("error :l'indice %d de l'objet %d est incompatible\n",ordre.indice[i],i);
					exit(0);
					}
				for (j=1;j<i;j++)
					{
					/*verification that this element is not in the list yet*/
					if ((ordre.type[j] == ordre.type[i]) && (ordre.indice[j] == ordre.indice[i]))
						{
						printf("error : the panel %d is twice in the list of meshing order\n",ordre.indice[i]);
						exit(0);
						}
					}			
				}
			if (ordre.type[i] == 'h')
				{
				if((ordre.indice[i]<1) || (ordre.indice[i]>Structure.NbTypesurf_hexa))
					{
					printf("warning :l'indice %d de l'objet %d est incompatible\n",ordre.indice[i],i);
					exit(0);
					}
				for (j=1;j<i;j++)
					{
					/*verification that this element is not in the list yet*/
					if ((ordre.type[j] == ordre.type[i]) && (ordre.indice[j] == ordre.indice[i]))
						{
						printf("error : the hexa panel %d is twice in the list of meshing order\n",ordre.indice[i]);
						exit(0);
						}
					}			
				}
			if (ordre.type[i] == 'e')
				{
				if((ordre.indice[i]<1) || (ordre.indice[i]>Structure.NbTypeelem))
					{
					printf("warning :l'indice %d de l'objet %d est incompatible\n",ordre.indice[i],i);
					exit(0);
					}
				for (j=1;j<i;j++)
					{
					/*verification that this element is not in the list yet*/
					if ((ordre.type[j] == ordre.type[i]) && (ordre.indice[j] == ordre.indice[i]))
						{
						printf("error : the element %d is twice in the list of meshing order\n",ordre.indice[i]);
						exit(0);
						}
					}			
				}
			if (ordre.type[i] == 'c')
				{
				if((ordre.indice[i]<1) || (ordre.indice[i]>Structure.nombreCoulisses))
					{
					printf("warning :l'indice %d de l'objet %d est incompatible\n",ordre.indice[i],i);
					exit(0);
					}
				for (j=1;j<i;j++)
					{
					/*verification that this element is not in the list yet*/
					if ((ordre.type[j] == ordre.type[i]) && (ordre.indice[j] == ordre.indice[i]))
						{
						printf("error : the sliding rope %d is twice in the list of meshing order\n",ordre.indice[i]);
						exit(0);
						}
					}			
				}
			if (ordre.type[i] == 'w')
				{
				if((ordre.indice[i]<1) || (ordre.indice[i]>Structure.nb_winch))
					{
					printf("warning :l'indice %d de l'objet %d est incompatible\n",ordre.indice[i],i);
					exit(0);
					}
				for (j=1;j<i;j++)
					{
					/*verification that this element is not in the list yet*/
					if ((ordre.type[j] == ordre.type[i]) && (ordre.indice[j] == ordre.indice[i]))
						{
						printf("error : the winch %d is twice in the list of meshing order\n",ordre.indice[i]);
						exit(0);
						}
					}			
				}
			//////////////////////////////////////////////////////////////////////
			}
 	        }
	/*Types de Noeuds*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Structure.NbTypeNoeud); 
	printf("Structure.NbTypeNoeud 		=     %4d\n",Structure.NbTypeNoeud );
	if ( Structure.NbTypeNoeud >= NBMAXTYPENOEUD)
		{
		printf(" NBMAXTYPENOEUD trop petit %4d < %4d \n",NBMAXTYPENOEUD,Structure.NbTypeNoeud );
		exit(0);
		}
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
		/*printf("sym %d %d %d\n",TypeNoeud[pa].symx,TypeNoeud[pa].symy,TypeNoeud[pa].symz);*/
		}
	/*ENVIRONNEMENT NUMERIQUE*****************************************************/
		do  c=fgetc(fic);  while (c !=':');	
		itmp = fscanf(fic,"%f\n",&Numerique.Diviseur); 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%f\n",&Numerique.Seuilconvergence); 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%f\n",&Numerique.Deplacement); 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%10d\n",&Numerique.Nbmaxiterations); 
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%f\n",&Numerique.Pascalcul); 
		printf("Numerique.Pascalcul %f\n",Numerique.Pascalcul);
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%f\n",&Numerique.Passtockage); 
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%f\n",&Numerique.Debutstockage); 
		do  c=fgetc(fic); while (c !=':');	
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%f\n",&Numerique.Finstockage); 
		printf("Numerique.Finstockage %f\n",Numerique.Finstockage);
		
	/*ENVIRONNEMENT METEOROLOGIQUE ET OCEANIQUE***********************************/
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Courant.direction); 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Courant.vitesse); 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Houle.periode); 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Houle.hauteur); 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Houle.direction); 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%f\n",&Houle.Depth1);
		 
	/*DESCRIPTION DE LA PRISE*****************************************************/
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Prise.volume);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Prise.seuil);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Prise.cd);
		
	/*ENVIRONNEMENT DU FOND MARIN*************************************************/
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Bottom.coef_frottement);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%lf\n",&Bottom.raideur);
		printf("Bottom.raideur %f\n",Bottom.raideur);

	/*sortie texte distance*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.nb_distance); 
	printf("Sortie_texte.nb_distance  = %8d\n",Sortie_texte.nb_distance );
       /**********************************************/
       Sortie_texte.type_structure1_distance = (char *) malloc((1 + Sortie_texte.nb_distance) * sizeof(char));
       if (Sortie_texte.type_structure1_distance    == NULL)
               {
               printf("Sortie_texte.type_structure1_distance  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.numero_structure1_distance = (int *) malloc((1 + Sortie_texte.nb_distance) * sizeof(int));
       if (Sortie_texte.numero_structure1_distance    == NULL)
               {
               printf("Sortie_texte.numero_structure1_distance  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.noeud1_distance = (int *) malloc((1 + Sortie_texte.nb_distance) * sizeof(int));
       if (Sortie_texte.noeud1_distance    == NULL)
               {
               printf("Sortie_texte.noeud1_distance  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.type_structure2_distance = (char *) malloc((1 + Sortie_texte.nb_distance) * sizeof(char));
       if (Sortie_texte.type_structure2_distance    == NULL)
               {
               printf("Sortie_texte.type_structure2_distance  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.numero_structure2_distance = (int *) malloc((1 + Sortie_texte.nb_distance) * sizeof(int));
       if (Sortie_texte.numero_structure2_distance    == NULL)
               {
               printf("Sortie_texte.numero_structure2_distance  1 = NULL  \n" );
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
       Sortie_texte.valeur_distance = (double *) malloc((1 + Sortie_texte.nb_distance) * sizeof(double));
       if (Sortie_texte.valeur_distance    == NULL)
               {
               printf("Sortie_texte.valeur_distance  1 = NULL  \n" );
               exit(0);
               }
       /**********************************************/
       Sortie_texte.comment_distance = (COMMENTAIRE *) malloc((1 + Sortie_texte.nb_distance) * sizeof(COMMENTAIRE));
       /*Sortie_texte.comment_distance = (char *) malloc((1 + Sortie_texte.nb_distance) * 156 * sizeof(char));*/
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
			Sortie_texte.comment_distance[pa].texte[i] = ' ';
			}
		i = 0;
		while ((c !='#') && (i<155))
			{
			i++;
			Sortie_texte.comment_distance[pa].texte[i] = c;
			c=fgetc(fic);
			}
		 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.noeud1_distance[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.noeud2_distance[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.decimale_distance[pa]);
		
		printf("noeud1 = %d ",Sortie_texte.noeud1_distance[pa]);
		printf("noeud2 = %d ",Sortie_texte.noeud2_distance[pa]);
		printf("decimale_distance = %d\n",Sortie_texte.decimale_distance[pa]);
		}



	/*sortie texte effort*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.nb_effort); 
	printf("Sortie_texte.nb_effort  = %8d\n",Sortie_texte.nb_effort );
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
       Sortie_texte.valeur_effort = (double *) malloc((1 + Sortie_texte.nb_effort) * sizeof(double));
       if (Sortie_texte.valeur_effort    == NULL)
               {
               printf("Sortie_texte.valeur_effort  1 = NULL  \n" );
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
		 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.noeud_effort[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.axe_effort[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.decimale_effort[pa]);
		
		printf("noeud = %d ",Sortie_texte.noeud_effort[pa]);
		printf("axe = %d ",Sortie_texte.axe_effort[pa]);
		printf("decimale_effort = %d\n",Sortie_texte.decimale_effort[pa]);
		}

	/*sortie texte tension*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.nb_tension_element); 
	printf("Sortie_texte.nb_tension_element  = %8d\n",Sortie_texte.nb_tension_element );
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
       Sortie_texte.valeur_tension = (double *) malloc((1 + Sortie_texte.nb_tension_element) * sizeof(double));
       if (Sortie_texte.valeur_tension    == NULL)
               {
               printf("Sortie_texte.valeur_tension  1 = NULL  \n" );
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
		 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.element_tension[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.element_extremite[pa]);
		if ((Sortie_texte.element_extremite[pa] < 1) || (Sortie_texte.element_extremite[pa] > 2))
			{
			printf("ATTENTION l extremite de la tension no  %d doit etre 1 ou 2",pa);
			printf(" et non  %d \n",Sortie_texte.element_extremite[pa]);
			Sortie_texte.element_extremite[pa] = 1;
			}
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.decimale_tension_element[pa]);
		
		printf("element_tension = %d ",Sortie_texte.element_tension[pa]);
		printf("element_extremite = %d ",Sortie_texte.element_extremite[pa]);
		printf("decimale_tension_element = %d\n",Sortie_texte.decimale_tension_element[pa]);
		}


	/*sortie texte tension_coulisse*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.nb_tension_coulisse); 
	printf("Sortie_texte.nb_tension_coulisse  = %8d\n",Sortie_texte.nb_tension_coulisse );
       /**********************************************/
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
       Sortie_texte.valeur_tension_coulisse = (double *) malloc((1 + Sortie_texte.nb_tension_coulisse) * sizeof(double));
       if (Sortie_texte.valeur_tension_coulisse    == NULL)
               {
               printf("Sortie_texte.valeur_tension_coulisse  1 = NULL  \n" );
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
		 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.coulisse_tension[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.coulisse_extremite[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.decimale_tension_coulisse[pa]);
		
		printf("coulisse_tension = %d ",Sortie_texte.coulisse_tension[pa]);
		printf("coulisse_extremite = %d ",Sortie_texte.coulisse_extremite[pa]);
		printf("decimale_tension_coulisse = %d\n",Sortie_texte.decimale_tension_coulisse[pa]);
		}


	/*sortie texte position*****************************************************/
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.nb_position); 
	printf("Sortie_texte.nb_position  = %8d\n",Sortie_texte.nb_position );
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
       Sortie_texte.valeur_position = (double *) malloc((1 + Sortie_texte.nb_position) * sizeof(double));
       if (Sortie_texte.valeur_position    == NULL)
               {
               printf("Sortie_texte.valeur_position  1 = NULL  \n" );
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
		 
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.noeud_position[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.axe_position[pa]);
		do  c=fgetc(fic); while (c !=':');	
		itmp = fscanf(fic,"%d\n",&Sortie_texte.decimale_position[pa]);
		
		printf("noeud_position = %d ",Sortie_texte.noeud_position[pa]);
		printf("axe_position = %d ",Sortie_texte.axe_position[pa]);
		printf("decimale_position = %d\n",Sortie_texte.decimale_position[pa]);
		}
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.effort_structure); 
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.diametre_prise); 
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.epaisseur_prise); 
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.volume_capture); 
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.surface_filtree); 
	do  c=fgetc(fic); while (c !=':');itmp = fscanf(fic,"%d\n",&Sortie_texte.vitesse_courant); 

	/**************************************************************/
	/*structure longueur de cable en utilisant les fonctions d allocation
	de alloc.c au depart nb_longueur_cable  est mis = 0
	nb_longueur_cable = le nombre de longueur de cables que l on veux afficher*/
	Sortie_texte.nb_longueur_cable =	0;
	Sortie_texte.valeur_longueur_cable =	(double *) Malloc_double(1 + Sortie_texte.nb_longueur_cable);
	Sortie_texte.element_longueur_cable =	(int *) Malloc_int(1 + Sortie_texte.nb_longueur_cable);
	Sortie_texte.decimale_longueur_cable = 	(int *) Malloc_int(1 + Sortie_texte.nb_longueur_cable);
	Sortie_texte.comment_longueur_cable =	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_longueur_cable);
	
	/*structure energie de panneau en utilisant les fonctions d allocation
	de alloc.c au depart nb_longueur_cable  est mis = 0
	nb_longueur_cable = le nombre de longueur de cables que l on veux afficher*/
	Sortie_texte.nb_energie_elong_diamond =	0;
	Sortie_texte.panneau_energie_elong =	(int *) Malloc_int(1 + Sortie_texte.nb_energie_elong_diamond);
	Sortie_texte.decimale_energie_elong = 	(int *) Malloc_int(1 + Sortie_texte.nb_energie_elong_diamond);
	Sortie_texte.comment_energie_elong_diamond =	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_energie_elong_diamond);
	
	/*structure energie de panneau en utilisant les fonctions d allocation
	de alloc.c au depart nb_longueur_cable  est mis = 0
	nb_longueur_cable = le nombre de longueur de cables que l on veux afficher*/
	Sortie_texte.nb_energie_fold_diamond =	0;
	Sortie_texte.panneau_energie_fold =	(int *) Malloc_int(1 + Sortie_texte.nb_energie_fold_diamond);
	Sortie_texte.decimale_energie_fold = 	(int *) Malloc_int(1 + Sortie_texte.nb_energie_fold_diamond);
	Sortie_texte.comment_energie_fold_diamond =	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_energie_fold_diamond);
	
	/*structure energie de panneau en utilisant les fonctions d allocation
	de alloc.c au depart nb_longueur_cable  est mis = 0
	nb_longueur_cable = le nombre de longueur de cables que l on veux afficher*/
	Sortie_texte.nb_energie_open_diamond =	0;
	Sortie_texte.panneau_energie_open =	(int *) Malloc_int(1 + Sortie_texte.nb_energie_open_diamond);
	Sortie_texte.decimale_energie_open = 	(int *) Malloc_int(1 + Sortie_texte.nb_energie_open_diamond);
	Sortie_texte.comment_energie_open_diamond =	(struct commentaire *) Malloc_commentaire(1 + Sortie_texte.nb_energie_open_diamond);
	
	/*structure inversion_triangles en utilisant les fonctions d allocation
	de alloc.c au depart nb_inversion_triangles  est mis = 0*/
	inversion_triangles.nb_inversion_triangles =	0;	
	inversion_triangles.premier =	(int *) Malloc_int(1 + inversion_triangles.nb_inversion_triangles);
	inversion_triangles.second  =	(int *) Malloc_int(1 + inversion_triangles.nb_inversion_triangles);
				
	/*structure de changement de type de noeud  est mis = 0*/
	type_noeud_XYZ_SUPINF.code = 0;

	chaine[1] = '\0';



	Structure.add_number_cage	= 0;
	int pan_inter_fond =1;
	int pan_inter = 2;
	int elem_inter = 1;

	int nb_ele_depart=1;
	int nb_tot_elem=0;
	int nb_elem_cage=0;

	int nb_tot_pan_elev =0;
	int pan_inter_pred_fond=0 ;
	int pan_inter_pred=0;

	int ele_inter_pred =0;


	int immersion ;


	/*printf("chaine = %s\n",chaine);
	i = strlen(chaine);
	printf("longueur chaine = %d\n",i);
	i = lecture_chaine(fic,chaine);*/
	Structure.link_distance = 0.0;
	
	for (pa=1;pa<=Structure.NbTypesurf;pa++)	panneau[pa].pas_U = 0.0;
	for (pa=1;pa<=Structure.NbTypesurf;pa++)	panneau[pa].pas_V = 0.0;
	for (pa=1;pa<=Structure.NbTypesurf;pa++)	panneau[pa].seam = 0.0;
	for (pa=1;pa<=Structure.NbTypesurf;pa++)	panneau[pa].flag_dessin = 2;
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)	pan_hexa[pa].flag_dessin = 3;
	for (pa=1;pa<=Structure.NbTypeelem;pa++)	element[pa].flag_dessin = 3;				

	for (pa=1;pa<=Structure.nombreCoulisses;pa++)	coulisse[pa].flag_dessin = 1;
	for (pa=1;pa<=Structure.nb_winch;pa++)	winch[pa].flag_dessin = 1;
	Sortie_texte.panel_drag = 0;
	Structure.link_distance = -1.0; /*if -1 that means that there is no automatic linking if >= 0 that means that there is automatic linking. It is necessary because it must be done at the end (after add_cage add_filet_pred)*/
/* debut modifdp du 4 mars 2010*/
	Structure.nb_connect_panel_node = 0;
	Structure.nb_sphere_element = 0;
/* fin modifdp du 4 mars 2010*/
	/*plan.do_it = 0;*/
	initialisation_min_max();
	plan.nb_indication = 0;
	plan.nb_trait_UV_symmetry = 0;
	plan.nb_trait_UV = 0;
	plan.nb_cable_length = 0;
	plan.nb_cable_diameter = 0;
	plan.nb_cable = 0;
	plan.nb_cut = 0;
	plan.nb_widths = 0;
	plan.nb_width = 0;
	plan.nb_height = 0;
	plan.nb_line = 0;
	Structure.nb_type_noeud_XYZ_SUPINF = 0;	//if 0 there is no modification of nodes type due to their opsition
	RHO = 1025.0;                   	/*kg/m^3, default value of the water density*/
	RHO_AIR = 1.208;                 	/*kg/m^3,  air density*/
	Structure.total1 = 0;	
	Structure.total2 = 0;	
	for (pa=1;pa<=Structure.nb_liaison;pa++) Lien[pa].angle_link_flexion2 = 0.0;
	for (pa=1;pa<=Structure.NbTypeelem;pa++) TypeElement[pa].nb_link_flexion2 = 0;
	Structure.nb_slider = 0;	
	Structure.nb_add_node_panel = 0;	//default value: no added numeric node in diamond panel
	Courant.nb_courant = 0;
	
	while (lecture_chaine(fic,chaine) != 0)
		{
		
		i = strlen(chaine);
		/*printf("chaine = %s  ",chaine);
		printf("longueur chaine = %d\n",i);*/

		if (strcmp(chaine,"output") == 0)
			{
			/*printf("lecture d output  ");*/
			i = lecture_chaine(fic,chaine);
			if (strcmp(chaine,"plan_indication_XY") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.nb_indication);	/*direction of the symmetry plan*/
				printf("plan.nb_indication %d\n",plan.nb_indication);
				plan.X1 =		(float *)    Malloc_float(1 + plan.nb_indication);
				plan.Y1 =		(float *)    Malloc_float(1 + plan.nb_indication);
				plan.indication = 	(float *)    Malloc_float(1 + plan.nb_indication); 
				for (pa=1;pa<=plan.nb_indication;pa++)
					{
					itmp = fscanf(fic,"%f",&plan.X1[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.Y1[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.indication[pa]);	/*panel*/
					printf("X1 %f Y1 %f indication %f\n",plan.X1[pa],plan.Y1[pa],plan.indication[pa]);
					}
				}
			if (strcmp(chaine,"trait_UV_panel_symmetry") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.nb_trait_UV_symmetry);	/*direction of the symmetry plan*/
				printf("nb_trait_UV_symmetry %d\n",plan.nb_trait_UV_symmetry);
				plan.panels =	(int *)    Malloc_int(1 + plan.nb_trait_UV_symmetry);
				plan.R1 =	(float *)    Malloc_float(1 + plan.nb_trait_UV_symmetry);
				plan.S1 =	(float *)    Malloc_float(1 + plan.nb_trait_UV_symmetry);
				plan.R2 =	(float *)    Malloc_float(1 + plan.nb_trait_UV_symmetry);
				plan.S2 =	(float *)    Malloc_float(1 + plan.nb_trait_UV_symmetry);
				plan.symmetryt =	(float *)    Malloc_float(1 + plan.nb_trait_UV_symmetry);
				for (pa=1;pa<=plan.nb_trait_UV_symmetry;pa++)
					{
					itmp = fscanf(fic,"%d",&plan.panels[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.R1[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.S1[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.R2[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.S2[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.symmetryt[pa]);	/*panel*/

					printf("panels %d  ",plan.panels[pa]);
					printf("R1 %f S1 %f R2 %f S2 %f symmetryt %f\n",plan.R1[pa],plan.S1[pa],plan.R2[pa],plan.S2[pa],plan.symmetryt[pa]);
					}
				}
			if (strcmp(chaine,"trait_UV_panel") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.nb_trait_UV);	/*direction of the symmetry plan*/
				printf("nb_trait_UV %d\n",plan.nb_trait_UV);
				plan.panelt =	(int *)    Malloc_int(1 + plan.nb_trait_UV);
				plan.U1 =	(float *)    Malloc_float(1 + plan.nb_trait_UV);
				plan.V1 =	(float *)    Malloc_float(1 + plan.nb_trait_UV);
				plan.U2 =	(float *)    Malloc_float(1 + plan.nb_trait_UV);
				plan.V2 =	(float *)    Malloc_float(1 + plan.nb_trait_UV);
				for (pa=1;pa<=plan.nb_trait_UV;pa++)
					{
					itmp = fscanf(fic,"%d",&plan.panelt[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.U1[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.V1[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.U2[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.V2[pa]);	/*panel*/

					printf("panelt %d  ",plan.panelt[pa]);
					printf("U1 %f V1 %f U2 %f V2 %f\n",plan.U1[pa],plan.V1[pa],plan.U2[pa],plan.V2[pa]);
					}
				}
			if (strcmp(chaine,"plan_cable_length") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.nb_cable_length);	/*direction of the symmetry plan*/
				printf("nb_cable_length %d\n",plan.nb_cable_length);
				plan.cablel =	(int *)    Malloc_int(1 + plan.nb_cable_length);
				plan.cable_length =	(float *)    Malloc_float(1 + plan.nb_cable_length);
				printf("cables:  ");
				for (pa=1;pa<=plan.nb_cable_length;pa++)
					{
					itmp = fscanf(fic,"%d",&plan.cablel[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.cable_length[pa]);	/*panel*/
					printf(" %d",plan.cablel[pa]);
					}
				printf("\n");
				}
			if (strcmp(chaine,"plan_cable_diameter") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.nb_cable_diameter);	/*direction of the symmetry plan*/
				printf("nb_cable_diameter %d\n",plan.nb_cable_diameter);
				plan.cabled =	(int *)    Malloc_int(1 + plan.nb_cable_diameter);
				plan.cable_diameter =	(float *)    Malloc_float(1 + plan.nb_cable_diameter);
				printf("cables:  ");
				for (pa=1;pa<=plan.nb_cable_diameter;pa++)
					{
					itmp = fscanf(fic,"%d",&plan.cabled[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.cable_diameter[pa]);	/*panel*/
					printf(" %d",plan.cabled[pa]);
					}
				printf("\n");
				}
			if (strcmp(chaine,"plan_cable") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.nb_cable);	/*direction of the symmetry plan*/
				printf("nb_cable %d\n",plan.nb_cable);
				plan.cable =	(int *)    Malloc_int(1 + plan.nb_cable);
				printf("cables:  ");
				for (pa=1;pa<=plan.nb_cable;pa++)
					{
					itmp = fscanf(fic,"%d",&plan.cable[pa]);	/*panel*/
					printf(" %d",plan.cable[pa]);
					}
				printf("\n");
				}
			if (strcmp(chaine,"panel_cutting") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.nb_cut);	/*direction of the symmetry plan*/
				printf("nb_cut %d\n",plan.nb_cut);
				plan.panelc =	(int *)    Malloc_int(1 + plan.nb_cut);
				plan.corner5 =	(int *)    Malloc_int(1 + plan.nb_cut);
				for (pa=1;pa<=plan.nb_cut;pa++)
					{
					itmp = fscanf(fic,"%d",&plan.panelc[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.corner5[pa]);	/*panel*/
					printf("panel %d   ",plan.panelc[pa]);
					printf("corner %d\n",plan.corner5[pa]);
					}
				}
			if (strcmp(chaine,"width_symmetry_plan") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.direction);	/*direction of the symmetry plan*/
				itmp = fscanf(fic,"%d",&plan.nb_widths);	/*direction of the symmetry plan*/
				printf("line_width %d\n",plan.nb_widths);
				plan.panelws =	(int *)    Malloc_int(1 + plan.nb_widths);
				plan.corner3s =	(int *)    Malloc_int(1 + plan.nb_widths);
				plan.corner4s =	(int *)    Malloc_int(1 + plan.nb_widths);
				plan.directionws =	(int *)    Malloc_int(1 + plan.nb_widths);
				plan.positionws =	(float *)    Malloc_float(1 + plan.nb_widths);
				for (pa=1;pa<=plan.nb_widths;pa++)
					{
					itmp = fscanf(fic,"%d",&plan.panelws[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.corner3s[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.corner4s[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.directionws[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.positionws[pa]);	/*panel*/

					printf("panel %d   ",plan.panelws[pa]);
					printf("corners %d %d   ",plan.corner3s[pa],plan.corner4s[pa]);
					printf("directionw %d   ",plan.directionws[pa]);
					printf("positionw %f\n",plan.positionws[pa]);
					}
				}
			if (strcmp(chaine,"width_plan") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.direction);	/*direction of the symmetry plan*/
				itmp = fscanf(fic,"%d",&plan.nb_width);	/*direction of the symmetry plan*/
				printf("line_width %d\n",plan.nb_width);
				plan.panelw =	(int *)    Malloc_int(1 + plan.nb_width);
				plan.corner3 =	(int *)    Malloc_int(1 + plan.nb_width);
				plan.corner4 =	(int *)    Malloc_int(1 + plan.nb_width);
				plan.directionw =	(int *)    Malloc_int(1 + plan.nb_width);
				plan.positionw =	(float *)    Malloc_float(1 + plan.nb_width);
				for (pa=1;pa<=plan.nb_width;pa++)
					{
					itmp = fscanf(fic,"%d",&plan.panelw[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.corner3[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.corner4[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.directionw[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.positionw[pa]);	/*panel*/

					printf("panel %d   ",plan.panelw[pa]);
					printf("corners %d %d   ",plan.corner3[pa],plan.corner4[pa]);
					printf("directionw %d   ",plan.directionw[pa]);
					printf("positionw %f\n",plan.positionw[pa]);
					}
				}
			if (strcmp(chaine,"minmax_plan") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%f",&plan.minx);	/*minx of the plan*/
				itmp = fscanf(fic,"%f",&plan.maxx);	/*minx of the plan*/
				itmp = fscanf(fic,"%f",&plan.miny);	/*minx of the plan*/
				itmp = fscanf(fic,"%f",&plan.maxy);	/*minx of the plan*/
				printf("minmax plan %f %f %f %f\n",plan.minx,plan.maxx,plan.miny,plan.maxy);
				minx = plan.minx;
				maxx = plan.maxx;
				miny = plan.miny;
				maxy = plan.maxy;
				if ((maxx - minx) > (maxy - miny) && (maxx - minx) > (maxz - minz) ) ecartmax = maxx - minx;
				if ((maxy - miny) > (maxz - minz) && (maxy - miny) > (maxx - minx) ) ecartmax = maxy - miny;
				if ((maxz - minz) > (maxx - minx) && (maxz - minz) > (maxy - miny) ) ecartmax = maxz - minz;
				binx = minx - 0.05 * (maxx - minx);
				biny = miny - 0.05 * (maxy - miny);
				baxx = maxx + 0.05 * (maxx - minx);
				baxy = maxy + 0.05 * (maxy - miny);
				bcartmax = ecartmax;
				}
			if (strcmp(chaine,"height_plan") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.direction);	/*direction of the symmetry plan*/
				itmp = fscanf(fic,"%d",&plan.nb_height);	/*direction of the symmetry plan*/
				printf("line_height %d\n",plan.nb_height);
				plan.panelh =	(int *)    Malloc_int(1 + plan.nb_height);
				plan.corner1 =	(int *)    Malloc_int(1 + plan.nb_height);
				plan.corner2 =	(int *)    Malloc_int(1 + plan.nb_height);
				plan.directionh =	(int *)    Malloc_int(1 + plan.nb_height);
				plan.position =	(float *)    Malloc_float(1 + plan.nb_height);
				for (pa=1;pa<=plan.nb_height;pa++)
					{
					itmp = fscanf(fic,"%d",&plan.panelh[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.corner1[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.corner2[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.directionh[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.position[pa]);	/*panel*/

					printf("panel %d   ",plan.panelh[pa]);
					printf("corners %d %d   ",plan.corner1[pa],plan.corner2[pa]);
					printf("directionh %d   ",plan.directionh[pa]);
					printf("position %f\n",plan.position[pa]);
					}
				}
			if (strcmp(chaine,"line_plan") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.direction);	/*direction of the symmetry plan*/
				itmp = fscanf(fic,"%d",&plan.nb_line);	/*direction of the symmetry plan*/
				printf("line_plan %d\n",plan.nb_line);
				plan.panel =	(int *)    Malloc_int(1 + plan.nb_line);
				plan.corner =	(int *)    Malloc_int(1 + plan.nb_line);
				plan.limit =	(float *)    Malloc_float(1 + plan.nb_line);
				for (pa=1;pa<=plan.nb_line;pa++)
					{
					itmp = fscanf(fic,"%d",&plan.panel[pa]);	/*panel*/
					itmp = fscanf(fic,"%d",&plan.corner[pa]);	/*panel*/
					itmp = fscanf(fic,"%f",&plan.limit[pa]);	/*panel*/

					printf("panel %d   ",plan.panel[pa]);
					printf("corner %d   ",plan.corner[pa]);
					printf("limit %f\n",plan.limit[pa]);
					}
				}
			if (strcmp(chaine,"symmetry_plan") == 0)
				{
				plan.do_it = 1;
				itmp = fscanf(fic,"%d",&plan.direction);	/*direction of the symmetry plan*/
				printf("symmetry_plan direction %d\n",plan.direction);
				for (pa=1;pa<=Structure.NbTypesurf;pa++)
					{
					itmp = fscanf(fic,"%f",&panneau[pa].symmetry_plan);	/*position of the symmetry plan*/
					}
				}
			if (strcmp(chaine,"rotation_panel_U") == 0)
				{
				itmp = fscanf(fic,"%d",&pa);	/*panel turned*/
				itmp = fscanf(fic,"%d",&p1);	/*side turned such as aligned on U twines*/
				printf("rotation_panel_U panel %d side %d\n",pa,p1);
				
				if (p1 != panneau[pa].nb_noeud_contour) p2 = p1+1;
				if (p1 == panneau[pa].nb_noeud_contour) p2 = 1;
				
				v1[1] = noeud[panneau[pa].noeud_contour[p2]].U - noeud[panneau[pa].noeud_contour[p1]].U;
				v1[2] = noeud[panneau[pa].noeud_contour[p2]].V - noeud[panneau[pa].noeud_contour[p1]].V;
				v1[3] = 0.0;
								
				dist = sqrt(produit_scal(v1, v1));
				
				if (dist <= 0.0)
					{
					printf("The side %d of panel %d has a length = %lf. It must be > 0.0\n",p1,pa,dist);
					}
				
				v2[1] = 1.0;
				v2[2] = 0.0;
				v2[3] = 0.0;
				
				alpha = acos(produit_scal(v1, v2) / dist);
				printf("alpha %lf dist %lf\n",alpha,dist);
				
				for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
					{
					if (no != p1)
						{
						v1[1] = noeud[panneau[pa].noeud_contour[no]].U - noeud[panneau[pa].noeud_contour[p1]].U;
						v1[2] = noeud[panneau[pa].noeud_contour[no]].V - noeud[panneau[pa].noeud_contour[p1]].V;
						v1[3] = 0.0;
						base1(alpha,3,0.0,3,3,v1);
						noeud[panneau[pa].noeud_contour[no]].U = v1[1] + noeud[panneau[pa].noeud_contour[p1]].U;
						noeud[panneau[pa].noeud_contour[no]].V = v1[2] + noeud[panneau[pa].noeud_contour[p1]].V;
						}
					}
				
/* debut modifdp du 4 mars 2010*/
				printf("Panel : %d\n",pa);
				printf("Nombre de points du contour : %d\n",panneau[pa].nb_noeud_contour);
				printf("points du contour dans l ordre du contour no x y z U V no_type no_type_suivant :\n");
				for (p0=1;p0<=panneau[pa].nb_noeud_contour;p0++)
					{
					if (Structure.orientation == 1)
						{
						}
					if (Structure.orientation == 2)
						{
						printf("%d %9.2lf %9.2lf %9.2lf ",p0,noeud[panneau[pa].noeud_contour[p0]].y,noeud[panneau[pa].noeud_contour[p0]].z,noeud[panneau[pa].noeud_contour[p0]].x);/**/
						printf("%9.2lf %9.2lf ",noeud[panneau[pa].noeud_contour[p0]].U,noeud[panneau[pa].noeud_contour[p0]].V);/**/
						printf("%d %d\n",noeud[panneau[pa].noeud_contour[p0]].type,panneau[pa].type_suivant_contour[p0]);/**/
						}
					if (Structure.orientation == 3)
						{
						}
					}				
				printf("\n");
				printf("Raideur traction (N) 		: %12.0lf\n",panneau[pa].raideur_traction);
				printf("Raideur compression (N) 	: %12.0lf\n",panneau[pa].raideur_compression);
				printf("Raideur ouverture (N.m/rad) 	: %12.0lf\n",panneau[pa].raideur_ouverture);
				printf("Maille au repos (m) 		: %12.3lf\n",panneau[pa].longueur_repos);
				printf("Masse volumique (kg/m3) 	: %12.0lf\n",panneau[pa].rho);
				printf("Diametre hydrodynamique (m) 	: %12.4lf\n",panneau[pa].diam_hydro);
				printf("largeur noeud 			: %12.3lf\n",panneau[pa].largeurnoeud);
				printf("Cd normal 			: %12.2lf\n",panneau[pa].cdnormal);
				printf("Cd tangentiel 			: %12.2lf\n",panneau[pa].ftangent);
				printf("Pas du maillage (m) 		: %12.2lf\n",panneau[pa].pas_maillage);
				printf("type des noeuds interieurs 	: %12d\n",panneau[pa].type_noeud);
				printf("type de maillage 		: %12d\n\n",panneau[pa].type_maillage);
/* fin modifdp du 4 mars 2010*/
				exit(0);
				}
			if (strcmp(chaine,"homothety") == 0)
				{
				itmp = fscanf(fic,"%lf",&homot_ratio);
				printf("homothety at %lf\n",homot_ratio);
				printf("Structure.graphic %d\n",Structure.graphic);
				if (Structure.graphic == 2)
					{
  					strcpy(tonom,nomfichier);
					strcat(tonom,"_H");
					//printf("Fichier selectionne: 			%s\n" , tonom);
					homot_file(nomfichier, tonom, homot_ratio);
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
			if (strcmp(chaine,"panel_drag") == 0)
				{
				Sortie_texte.panel_drag = 1;
				printf("lecture de panel_drag %d\n",Sortie_texte.panel_drag);
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
				Sortie_texte.valeur_longueur_cable =	(double *) Realloc_double(Sortie_texte.valeur_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
				Sortie_texte.element_longueur_cable =	(int *) Realloc_int(Sortie_texte.element_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
				Sortie_texte.decimale_longueur_cable = 	(int *) Realloc_int(Sortie_texte.decimale_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
				Sortie_texte.comment_longueur_cable =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_longueur_cable,1 + Sortie_texte.nb_longueur_cable);
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
				Sortie_texte.panneau_energie_elong =	(int *) Realloc_int(Sortie_texte.panneau_energie_elong,1 + Sortie_texte.nb_energie_elong_diamond);
				Sortie_texte.decimale_energie_elong = 	(int *) Realloc_int(Sortie_texte.decimale_energie_elong,1 + Sortie_texte.nb_energie_elong_diamond);
				Sortie_texte.comment_energie_elong_diamond =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_energie_elong_diamond,1 + Sortie_texte.nb_energie_elong_diamond);
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
				Sortie_texte.panneau_energie_fold =	(int *) Realloc_int(Sortie_texte.panneau_energie_fold,1 + Sortie_texte.nb_energie_fold_diamond);
				Sortie_texte.decimale_energie_fold = 	(int *) Realloc_int(Sortie_texte.decimale_energie_fold,1 + Sortie_texte.nb_energie_fold_diamond);
				Sortie_texte.comment_energie_fold_diamond =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_energie_fold_diamond,1 + Sortie_texte.nb_energie_fold_diamond);
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
				Sortie_texte.panneau_energie_open =	(int *) Realloc_int(Sortie_texte.panneau_energie_open,1 + Sortie_texte.nb_energie_open_diamond);
				Sortie_texte.decimale_energie_open = 	(int *) Realloc_int(Sortie_texte.decimale_energie_open,1 + Sortie_texte.nb_energie_open_diamond);
				Sortie_texte.comment_energie_open_diamond =	(struct commentaire *) Realloc_commentaire(Sortie_texte.comment_energie_open_diamond,1 + Sortie_texte.nb_energie_open_diamond);
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
					panneau[temp2_int].flag_dessin = 0;/**/					
					}
				}
			if (strcmp(chaine,"no_visible_surface_hexa") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				printf("no_visible_surface_hexa nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					itmp = fscanf(fic,"%d",&temp2_int);
					pan_hexa[temp2_int].flag_dessin = 0;/**/					
					}
				}
			if (strcmp(chaine,"no_visible_element") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				printf("no_visible_element nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					itmp = fscanf(fic,"%d",&temp2_int);
					element[temp2_int].flag_dessin = 0;/**/					
					}
				}
			if (strcmp(chaine,"no_visible_element_window") == 0)
				{			
/* debut modifdp du 6 mars 2010*/				
				if (Structure.orientation == 1)
					{
					itmp = fscanf(fic,"%lf %lf",&tzmin,&tzmax);
					itmp = fscanf(fic,"%lf %lf",&txmin,&txmax);
					itmp = fscanf(fic,"%lf %lf",&tymin,&tymax);
					}
				if (Structure.orientation == 2)
					{
					itmp = fscanf(fic,"%lf %lf",&tymin,&tymax);
					itmp = fscanf(fic,"%lf %lf",&tzmin,&tzmax);
					itmp = fscanf(fic,"%lf %lf",&txmin,&txmax);
					}
				if (Structure.orientation == 3)
					{
					itmp = fscanf(fic,"%lf %lf",&txmin,&txmax);
					itmp = fscanf(fic,"%lf %lf",&tymin,&tymax);
					itmp = fscanf(fic,"%lf %lf",&tzmin,&tzmax);
					}
				/*itmp = fscanf(fic,"%lf",&txmin);
				itmp = fscanf(fic,"%lf",&txmax);
				itmp = fscanf(fic,"%lf",&tymin);
				itmp = fscanf(fic,"%lf",&tymax);
				itmp = fscanf(fic,"%lf",&tzmin);
				itmp = fscanf(fic,"%lf",&tzmax);*/
				printf("no_visible_element_window: %lf %lf %lf %lf %lf %lf \n",txmin,txmax,tymin,tymax,tzmin,tzmax);
				/*for (pa=1;pa<=Structure.NbTypeelem;pa++)
					{
					printf("[%d].xyz12: %lf %lf %lf %lf %lf %lf \n",pa,noeud[element[pa].extremite[1]].x,noeud[element[pa].extremite[1]].y,noeud[element[pa].extremite[1]].z,noeud[element[pa].extremite[2]].x,noeud[element[pa].extremite[2]].y,noeud[element[pa].extremite[2]].z);
					}*/
				for (pa=1;pa<=Structure.NbTypeelem;pa++)
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
									printf("element[%d].flag_dessin = %d  ",pa,element[pa].flag_dessin);
									printf("[%d].xyz12: %lf %lf %lf %lf %lf %lf \n",pa,noeud[element[pa].extremite[1]].x,noeud[element[pa].extremite[1]].y,noeud[element[pa].extremite[1]].z,noeud[element[pa].extremite[2]].x,noeud[element[pa].extremite[2]].y,noeud[element[pa].extremite[2]].z);
									}
								}
							}
						}
					}
/* fin modifdp du 6 mars 2010*/				
				}
			if (strcmp(chaine,"no_visible_coulisse") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				printf("no_visible_coulisse nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					itmp = fscanf(fic,"%d",&temp2_int);
					coulisse[temp2_int].flag_dessin = 0;/**/					
					}
				}
			if (strcmp(chaine,"no_visible_winch") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				printf("no_visible_winch nb: %d \n",temp_int);
				for (zi=1;zi<=temp_int;zi++)
					{
					itmp = fscanf(fic,"%d",&temp2_int);
					winch[temp2_int].flag_dessin = 0;/**/					
					}
				}
	  		if (strcmp(chaine,"opening_angle") == 0)
	    			{
				itmp = fscanf(fic,"%d",&Opening_angle.nb_panel);
				printf("opening nb_panel %d \n",Opening_angle.nb_panel);
				Opening_angle.panel =         	(int *)    Malloc_int(1 + Opening_angle.nb_panel);
	      			for (pa=1;pa<=Opening_angle.nb_panel;pa++)
					{
		  			itmp = fscanf(fic,"%d",&Opening_angle.panel[pa]);
		  			printf(" %d ",Opening_angle.panel[pa]);
					}

				itmp = fscanf(fic,"%lf",&Opening_angle.pas);
				printf("opening pas %lf \n",Opening_angle.pas);
				Opening_angle.nb_tab = (int) 90.0 / Opening_angle.pas;
	      			printf("calculation of the opening angle by panel\n");
				printf("opening nb tab %d \n",Opening_angle.nb_tab);
	 		   	}
	  		if (strcmp(chaine,"opening_mesh") == 0)
	    			{
				itmp = fscanf(fic,"%d",&Opening_mesh.nb_panel);
				printf("opening nb_panel %d \n",Opening_mesh.nb_panel);
				Opening_mesh.panel =         	(int *)    Malloc_int(1 + Opening_mesh.nb_panel);
	      			for (pa=1;pa<=Opening_mesh.nb_panel;pa++)
					{
		  			itmp = fscanf(fic,"%d",&Opening_mesh.panel[pa]);
		  			printf(" %d ",Opening_mesh.panel[pa]);
					}
				printf(" \n");
				itmp = fscanf(fic,"%lf",&Opening_mesh.pas);
				printf("opening pas %lf \n",Opening_mesh.pas);
	 		   	}
	  		if (strcmp(chaine,"opening_angle_stripe") == 0)
	    			{
				itmp = fscanf(fic,"%d",&Opening_angle_stripe.nb_panel);
				printf("opening nb_panel %d \n",Opening_angle_stripe.nb_panel);
				Opening_angle_stripe.panel =         	(int *)    Malloc_int(1 + Opening_angle_stripe.nb_panel);
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
	 		   	}
			if (strcmp(chaine,"meridian") == 0)
				{
				printf("calculation of the meridian\n");
				Sortie_texte.meridian = 1;
				}
			if (strcmp(chaine,"meridian_X") == 0)
				{
				printf("calculation of the meridian_X\n");
				Sortie_texte.meridian_X = 1;
				}
			if (strcmp(chaine,"meridian_Y") == 0)
				{
				printf("calculation of the meridian_Y\n");
				Sortie_texte.meridian_Y = 1;
				}
			if (strcmp(chaine,"meridian_Z") == 0)
				{
				printf("calculation of the meridian_Z\n");
				Sortie_texte.meridian_Z = 1;
				}
			if (strcmp(chaine,"curvilinear_codend_length") == 0)
				{
				printf("calculation of the curvilinear_codend_length\n");
				Sortie_texte.curvilinear_codend_length = 1;
				}
			if (strcmp(chaine,"panels") == 0)
				{
				printf("calculation of the limit between panels\n");
				itmp = fscanf(fic,"%d",&Prise.panels[1]);
				itmp = fscanf(fic,"%d",&Prise.panels[2]);
				}
			if (strcmp(chaine,"nb_mesh_front") == 0)
				{
				printf("calculation of the nb_mesh_front\n");
				itmp = fscanf(fic,"%d",&Prise.dir_mesh_front);
				}
			if (strcmp(chaine,"color_element") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				itmp = fscanf(fic,"%d",&temp2_int);
				element[temp_int].flag_dessin = temp2_int;
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
				itmp = fscanf(fic,"%d",&temp_int);
				itmp = fscanf(fic,"%d",&temp2_int);
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
			} /*end of output*/
			
		if (strcmp(chaine,"input") == 0)
			{
			//printf("lecture d input  ");/**/
			i = lecture_chaine(fic,chaine);
			/*printf("chaine = %s  ",chaine);
			printf("longueur chaine = %d\n",i);*/
			
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
				printf("netting_2_ropes_accuracy %lf\n",panneau[temp_int].netting_2_ropes_accuracy);
				printf("netting_2_ropes_bar_nb %d\n",panneau[temp_int].netting_2_ropes_bar_nb);
				//modification of the order of meshing in order to put this panel in first position
				
				for (pa=1;pa<=Structure.nb_ordre_objet;pa++)
					{ 
			    		//printf("uype = %c indice =%d\n",ordre.type[pa],ordre.indice[pa]);/**/
			    		}

				temp1_int = temp_int;
				pa = 0;
				do
					{
					pa++;
					if (ordre.type[pa] == 'p')
						{
						temp2_int = ordre.indice[pa];
						//printf("temp2_int %d  ",temp2_int);
						ordre.indice[pa] = temp1_int;
						//printf("indice %d  ",ordre.indice[pa]);
						temp1_int = temp2_int;
						//printf("temp1_int %d  \n",temp1_int);
						}
					}
				while (temp2_int != temp_int);

				/*
				temp1_char = 'p';
				temp1_int = temp_int;
				pa = 0;
				do
					{
					pa++;
					temp2_char = ordre.type[pa];
					temp2_int = ordre.indice[pa];
					ordre.type[pa] = temp1_char;
					ordre.indice[pa] = temp1_int;
					temp1_char = temp2_char;
					temp1_int = temp2_int;
					}
				while ((temp2_char != 'p') || (temp2_int != temp_int));
				*/
				for (pa=1;pa<=Structure.nb_ordre_objet;pa++)
					{ 
			    		//printf("%c: %d	",ordre.type[pa],ordre.indice[pa]);/**/
			    		}
				//printf("\n");
			    	//exit(0);
			
				
				//exit(0);
				}
			if (strcmp(chaine,"foil2") == 0)
				{
				itmp = fscanf(fic, "%d", &node_type);
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
				printf("TypeNoeud[%d].mxyz (N)		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].mx,TypeNoeud[node_type].my,TypeNoeud[node_type].mz);	
				printf("TypeNoeud[%d].majxyz (N)		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].majx,TypeNoeud[node_type].majy,TypeNoeud[node_type].majz);	
				printf("TypeNoeud[%d].lonxyz (m)		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].lonx,TypeNoeud[node_type].lony,TypeNoeud[node_type].lonz);	
				printf("TypeNoeud[%d].cdxyz		%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].cdx,TypeNoeud[node_type].cdy,TypeNoeud[node_type].cdz);	
				printf("TypeNoeud[%d].fextxyz (N)	%lf	%lf	%lf\n",node_type,TypeNoeud[node_type].fextx,TypeNoeud[node_type].fexty,TypeNoeud[node_type].fextz);	
				printf("Fd (N)				%lf 	Fl (N)		%lf\n",Fd,Fl);	
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
			if (strcmp(chaine,"openfoam") == 0)
				{
				printf("open_foam\n");
				}
			if (strcmp(chaine,"add_node_panel") == 0)
				{
				Structure.nb_add_node_panel++;
				number = Structure.nb_add_node_panel;
				if (number == 1)
					{
					Add_node_panel.panel =	(int *)    Malloc_int(1 + number);
					Add_node_panel.U =	(double *) Malloc_double(1 + number);
					Add_node_panel.V =	(double *) Malloc_double(1 + number);
					Add_node_panel.type =	(int *)    Malloc_int(1 + number);
					}
				else
					{
					Add_node_panel.panel =	(int *)    Realloc_int(Add_node_panel.panel, 1 + number);
					Add_node_panel.U =	(double *) Realloc_double(Add_node_panel.U,  1 + number);
					Add_node_panel.V =	(double *) Realloc_double(Add_node_panel.V,  1 + number);
					Add_node_panel.type =	(int *)    Realloc_int(Add_node_panel.type,  1 + number);
					}
				itmp = fscanf(fic,"%d",&Add_node_panel.panel[number]);
				itmp = fscanf(fic,"%lf",&Add_node_panel.U[number]);
				itmp = fscanf(fic,"%lf",&Add_node_panel.V[number]);
				itmp = fscanf(fic,"%d",&Add_node_panel.type[number]);
				printf("add node %d in panel %d coordinates %lf %lf with type %d\n",number,Add_node_panel.panel[number],Add_node_panel.U[number],Add_node_panel.V[number],Add_node_panel.type[number]);
				}
			if (strcmp(chaine,"slider") == 0)
				{
				Structure.nb_slider++;
				itmp = fscanf(fic,"%d",&Slider[Structure.nb_slider].nb_bar);
				printf("Slider %d has %d elements :",Structure.nb_slider,Slider[Structure.nb_slider].nb_bar);
				Slider[Structure.nb_slider].barre =	(int *)    Malloc_int(1 + Slider[Structure.nb_slider].nb_bar);
				for (zi=1;zi<=Slider[Structure.nb_slider].nb_bar;zi++)
					{
					itmp = fscanf(fic,"%d",&Slider[Structure.nb_slider].barre[zi]);
					element[Slider[Structure.nb_slider].barre[zi]].slider = Structure.nb_slider;	//this element is part of a slider
					//element[Slider[Structure.nb_slider].barre[zi]].flag_dessin = 0;
					printf(" %d",Slider[Structure.nb_slider].barre[zi]);
					}
				printf("\n");
				}
			if (strcmp(chaine,"2globals_to_1global") == 0)
			//input 2globals_to_1global 1514 173
				{
				itmp = fscanf(fic,"%d",&Structure.total1);
				itmp = fscanf(fic,"%d",&Structure.total2);
				printf("The total node %d and %d are linked\n",Structure.total1,Structure.total2);
				}
			if (strcmp(chaine,"Diamond_panel_2_bar_element") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				panneau[temp_int].type_maillage	= 3;		
				printf("Discretisation of panel %d in bar elements\n",temp_int);
				}
			if (strcmp(chaine,"Meshing_UV") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				itmp = fscanf(fic,"%f",&panneau[temp_int].pas_U);
				itmp = fscanf(fic,"%f",&panneau[temp_int].pas_V);
				printf("Meshing of panel %d of %f meshes along U meshes and %f meshes along V meshes\n",temp_int,panneau[temp_int].pas_U,panneau[temp_int].pas_V);
				}
			if (strcmp(chaine,"Meshing_uv") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				itmp = fscanf(fic,"%f",&panneau[temp_int].pas_u);
				itmp = fscanf(fic,"%f",&panneau[temp_int].pas_v);
				printf("Meshing of panel %d of %f twines along u twines and %f twines along v twines\n",temp_int,panneau[temp_int].pas_u,panneau[temp_int].pas_v);
				}
/* debut modifdp du 4 mars 2010*/
			if (strcmp(chaine,"connect_panel_node") == 0)
				{
				Structure.nb_connect_panel_node++;
				if (Structure.nb_connect_panel_node == 1)
					{
					Connect_panel_node.panel =	(int *)    Malloc_int(1 + Structure.nb_connect_panel_node);
					Connect_panel_node.node =	(int *)    Malloc_int(1 + Structure.nb_connect_panel_node);
					Connect_panel_node.panel1 =	(int *)    Malloc_int(1 + Structure.nb_connect_panel_node);
					Connect_panel_node.node1 =	(int *)    Malloc_int(1 + Structure.nb_connect_panel_node);
					Connect_panel_node.pro1 =	(double *)    Malloc_double(1 + Structure.nb_connect_panel_node);
					Connect_panel_node.panel2 =	(int *)    Malloc_int(1 + Structure.nb_connect_panel_node);
					Connect_panel_node.node2 =	(int *)    Malloc_int(1 + Structure.nb_connect_panel_node);
					Connect_panel_node.pro2 =	(double *)    Malloc_double(1 + Structure.nb_connect_panel_node);
					}
				else
					{
					Connect_panel_node.panel =	(int *) Realloc_int(Connect_panel_node.panel ,1 + Structure.nb_connect_panel_node);
					Connect_panel_node.node =	(int *) Realloc_int(Connect_panel_node.node ,1 + Structure.nb_connect_panel_node);
					Connect_panel_node.panel1 =	(int *) Realloc_int(Connect_panel_node.panel1 ,1 + Structure.nb_connect_panel_node);
					Connect_panel_node.node1 =	(int *) Realloc_int(Connect_panel_node.node1 ,1 + Structure.nb_connect_panel_node);
					Connect_panel_node.pro1 =	(double *) Realloc_double(Connect_panel_node.pro1 ,1 + Structure.nb_connect_panel_node);
					Connect_panel_node.panel2 =	(int *) Realloc_int(Connect_panel_node.panel2 ,1 + Structure.nb_connect_panel_node);
					Connect_panel_node.node2 =	(int *) Realloc_int(Connect_panel_node.node2 ,1 + Structure.nb_connect_panel_node);
					Connect_panel_node.pro2 =	(double *) Realloc_double(Connect_panel_node.pro2 ,1 + Structure.nb_connect_panel_node);
					}
				itmp = fscanf(fic,"%d",&Connect_panel_node.panel[Structure.nb_connect_panel_node]);
				itmp = fscanf(fic,"%d",&Connect_panel_node.node[Structure.nb_connect_panel_node]);
				itmp = fscanf(fic,"%d",&Connect_panel_node.panel1[Structure.nb_connect_panel_node]);
				itmp = fscanf(fic,"%d",&Connect_panel_node.node1[Structure.nb_connect_panel_node]);
				itmp = fscanf(fic,"%lf",&Connect_panel_node.pro1[Structure.nb_connect_panel_node]);
				itmp = fscanf(fic,"%d",&Connect_panel_node.panel2[Structure.nb_connect_panel_node]);
				itmp = fscanf(fic,"%d",&Connect_panel_node.node2[Structure.nb_connect_panel_node]);
				itmp = fscanf(fic,"%lf",&Connect_panel_node.pro2[Structure.nb_connect_panel_node]);
				//printf("nb_connect_panel_node %d  ",Structure.nb_connect_panel_node);
				//printf("panel %d  \n",Connect_panel_node.panel[Structure.nb_connect_panel_node]);
				//printf("node %d  ",Connect_panel_node.node[Structure.nb_connect_panel_node]);
				//printf("panel1 %d  ",Connect_panel_node.panel1[Structure.nb_connect_panel_node]);
				//printf("node1 %d  ",Connect_panel_node.node1[Structure.nb_connect_panel_node]);
				//printf("pro1 %lf  ",Connect_panel_node.pro1[Structure.nb_connect_panel_node]);
				//printf("panel2 %d  ",Connect_panel_node.panel2[Structure.nb_connect_panel_node]);
				//printf("node2 %d  ",Connect_panel_node.node2[Structure.nb_connect_panel_node]);
				//printf("pro2 %lf\n",Connect_panel_node.pro2[Structure.nb_connect_panel_node]);
				
				pa = 	Connect_panel_node.panel[Structure.nb_connect_panel_node];
				no = 	Connect_panel_node.node[Structure.nb_connect_panel_node];
				pa1 = 	Connect_panel_node.panel1[Structure.nb_connect_panel_node];
				no1 =	Connect_panel_node.node1[Structure.nb_connect_panel_node];
				pr1 =	Connect_panel_node.pro1[Structure.nb_connect_panel_node];
				pa2 =	Connect_panel_node.panel2[Structure.nb_connect_panel_node];
				no2 =	Connect_panel_node.node2[Structure.nb_connect_panel_node];
				pr2 =	Connect_panel_node.pro2[Structure.nb_connect_panel_node];
				
				noeud[panneau[pa].noeud_contour[no]].x = noeud[panneau[pa1].noeud_contour[no1]].x * pr1 + noeud[panneau[pa2].noeud_contour[no2]].x * pr2;
				noeud[panneau[pa].noeud_contour[no]].y = noeud[panneau[pa1].noeud_contour[no1]].y * pr1 + noeud[panneau[pa2].noeud_contour[no2]].y * pr2;
				noeud[panneau[pa].noeud_contour[no]].z = noeud[panneau[pa1].noeud_contour[no1]].z * pr1 + noeud[panneau[pa2].noeud_contour[no2]].z * pr2;
				noeud[panneau[pa].noeud_contour[no]].U = noeud[panneau[pa1].noeud_contour[no1]].U * pr1 + noeud[panneau[pa2].noeud_contour[no2]].U * pr2;
				noeud[panneau[pa].noeud_contour[no]].V = noeud[panneau[pa1].noeud_contour[no1]].V * pr1 + noeud[panneau[pa2].noeud_contour[no2]].V * pr2;
				if ((Connect_panel_node.panel[Structure.nb_connect_panel_node-1] != Connect_panel_node.panel[Structure.nb_connect_panel_node]) && (Structure.nb_connect_panel_node > 1))
					{
					printf("panel %d  \n",Connect_panel_node.panel[Structure.nb_connect_panel_node]);
					}
				if (Structure.nb_connect_panel_node == 1)
					{
					printf("panel %d  \n",Connect_panel_node.panel[Structure.nb_connect_panel_node]);
					}
				printf("%d",Connect_panel_node.node[Structure.nb_connect_panel_node]);
				if (Structure.orientation == 1)
					{
					printf(" %lf", noeud[panneau[pa].noeud_contour[no]].z);
					printf(" %lf", noeud[panneau[pa].noeud_contour[no]].x);
					printf(" %lf", noeud[panneau[pa].noeud_contour[no]].y);
					}
				if (Structure.orientation == 2)
					{
					printf(" %lf", noeud[panneau[pa].noeud_contour[no]].y);
					printf(" %lf", noeud[panneau[pa].noeud_contour[no]].z);
					printf(" %lf", noeud[panneau[pa].noeud_contour[no]].x);
					}
				if (Structure.orientation == 3)
					{
					printf(" %lf", noeud[panneau[pa].noeud_contour[no]].x);
					printf(" %lf", noeud[panneau[pa].noeud_contour[no]].y);
					printf(" %lf", noeud[panneau[pa].noeud_contour[no]].z);
					}
				printf(" %lf", noeud[panneau[pa].noeud_contour[no]].u);
				printf(" %lf", noeud[panneau[pa].noeud_contour[no]].V);
				printf(" %d",  noeud[panneau[pa].noeud_contour[no]].type);
				printf(" %d\n",panneau[pa].type_suivant_contour[no]);	
				
				
				
				
				
				
				
				
				
				
				
				
				
				
							
				}
			if (strcmp(chaine,"type_node_X") == 0)
				{
				itmp = fscanf(fic,"%d",&first);
				itmp = fscanf(fic,"%lf",&step);
				itmp = fscanf(fic,"%d",&number);
				itmp = fscanf(fic,"%lf",&dist);
				itmp = fscanf(fic,"%d",&node_type);
				for (zi=1;zi<=number;zi++)
					{
					if (Structure.orientation == 1)
						{
						xx1 = noeud[first].x;		
						yy1 = noeud[first].y;		
						zz1 = noeud[first].z + (zi-1) * step;
						}
					if (Structure.orientation == 2)
						{
						xx1 = noeud[first].x;		
						yy1 = noeud[first].y + (zi-1) * step;		
						zz1 = noeud[first].z;
						}
					if (Structure.orientation == 3)
						{
						xx1 = noeud[first].x + (zi-1) * step;		
						yy1 = noeud[first].y;		
						zz1 = noeud[first].z;
						}
					printf("There are a modification of node type at %lf %lf %lf\n",noeud[first].x,noeud[first].y,noeud[first].z);
					printf("There are a modification of node type at %lf %lf %lf\n",xx1,yy1,zz1);
					for (pa=1;pa<=Structure.NbTypesurf;pa++)
						{
						for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
							{
							dist_c = sqrt((noeud[panneau[pa].noeud_contour[no]].x-xx1)*(noeud[panneau[pa].noeud_contour[no]].x-xx1)
								+(noeud[panneau[pa].noeud_contour[no]].y-yy1)*(noeud[panneau[pa].noeud_contour[no]].y-yy1)
								+(noeud[panneau[pa].noeud_contour[no]].z-zz1)*(noeud[panneau[pa].noeud_contour[no]].z-zz1));
							if (dist_c < dist)
								{
								noeud[panneau[pa].noeud_contour[no]].type = node_type;
								}
							}
						}
					for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
						{
						for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
							{
							dist_c = sqrt((noeud[pan_hexa[pa].noeud_contour[no]].x-xx1)*(noeud[pan_hexa[pa].noeud_contour[no]].x-xx1)
								+(noeud[pan_hexa[pa].noeud_contour[no]].y-yy1)*(noeud[pan_hexa[pa].noeud_contour[no]].y-yy1)
								+(noeud[pan_hexa[pa].noeud_contour[no]].z-zz1)*(noeud[pan_hexa[pa].noeud_contour[no]].z-zz1));
							if (dist_c < dist)
								{
								noeud[pan_hexa[pa].noeud_contour[no]].type = node_type;
								}
							}
						}
					for (pa=1;pa<=Structure.NbTypeelem;pa++)
						{
						for (no=1;no<=2;no++)
							{
							dist_c = sqrt((noeud[element[pa].extremite[no]].x-xx1)*(noeud[element[pa].extremite[no]].x-xx1)
								+(noeud[element[pa].extremite[no]].y-yy1)*(noeud[element[pa].extremite[no]].y-yy1)
								+(noeud[element[pa].extremite[no]].z-zz1)*(noeud[element[pa].extremite[no]].z-zz1));
							printf("element pa %d no %d dist_c %lf pos %lf %lf %lf\n",pa,no,dist_c,noeud[element[pa].extremite[no]].x,noeud[element[pa].extremite[no]].y,noeud[element[pa].extremite[no]].z);
							if (dist_c < dist)
								{
								noeud[element[pa].extremite[no]].type = node_type;
								}
							}
						}
					}
				}
/* fin modifdp du 4 mars 2010*/
			if (strcmp(chaine,"rope_X") == 0)
				{
				itmp = fscanf(fic,"%d",&i);
				itmp = fscanf(fic,"%d",&j);
				itmp = fscanf(fic,"%lf",&dist);
				printf("There are %d ropes like rope %d spaced of %lf created from rope %d (included)\n\n",i,j,dist,j);
				pa = 0;
				if (Structure.orientation == 1)
					{
					printf("El: %d ",pa+j);
					printf("D: 1 ");
					printf("%lf ",noeud[element[pa+j].extremite[1]].z);
					printf("%lf ",noeud[element[pa+j].extremite[1]].x);
					printf("%lf ",noeud[element[pa+j].extremite[1]].y);
					printf("%d ",noeud[element[pa+j].extremite[1]].type);
					printf(" 2 ");
					printf("%lf ",noeud[element[pa+j].extremite[2]].z);
					printf("%lf ",noeud[element[pa+j].extremite[2]].x);
					printf("%lf ",noeud[element[pa+j].extremite[2]].y);
					printf("%d ",noeud[element[pa+j].extremite[2]].type);
					}
				if (Structure.orientation == 2)
					{
					printf("El: %d ",pa+j);
					printf("D: 1 ");
					printf("%lf ",noeud[element[pa+j].extremite[1]].y);
					printf("%lf ",noeud[element[pa+j].extremite[1]].z);
					printf("%lf ",noeud[element[pa+j].extremite[1]].x);
					printf("%d ",noeud[element[pa+j].extremite[1]].type);
					printf(" 2 ");
					printf("%lf ",noeud[element[pa+j].extremite[2]].y);
					printf("%lf ",noeud[element[pa+j].extremite[2]].z);
					printf("%lf ",noeud[element[pa+j].extremite[2]].x);
					printf("%d ",noeud[element[pa+j].extremite[2]].type);
					}
				if (Structure.orientation == 3)
					{
					printf("El: %d ",pa+j);
					printf("D: 1 ");
					printf("%lf ",noeud[element[pa+j].extremite[1]].x);
					printf("%lf ",noeud[element[pa+j].extremite[1]].y);
					printf("%lf ",noeud[element[pa+j].extremite[1]].z);
					printf("%d ",noeud[element[pa+j].extremite[1]].type);
					printf(" 2 ");
					printf("%lf ",noeud[element[pa+j].extremite[2]].x);
					printf("%lf ",noeud[element[pa+j].extremite[2]].y);
					printf("%lf ",noeud[element[pa+j].extremite[2]].z);
					printf("%d ",noeud[element[pa+j].extremite[2]].type);
					}
				printf("Kt: %lf ",element[pa+j].raideur_traction);
				printf("Kc: %lf ",element[pa+j].raideur_compression);
				printf("L: %lf ",element[pa+j].lgrepos);
				printf("M: %lf ",element[pa+j].rhoelement);
				printf("D: %lf ",element[pa+j].diametrehydro);
				printf("Cd: %lf ",element[pa+j].cdnormal);
				printf("f: %lf ",element[pa+j].ftangent);
				printf("n: %d ",element[pa+j].nb_barre);
				printf("t: %d\n",element[pa+j].type_noeud);
				for (pa=1;pa<=i-1;pa++)
					{
					if (Structure.orientation == 1)
						{
						noeud[element[pa+j].extremite[1]].z = noeud[element[pa+j-1].extremite[1]].z + dist;
						noeud[element[pa+j].extremite[1]].x = noeud[element[pa+j-1].extremite[1]].x;
						noeud[element[pa+j].extremite[1]].y = noeud[element[pa+j-1].extremite[1]].y;
						noeud[element[pa+j].extremite[2]].z = noeud[element[pa+j-1].extremite[2]].z + dist;
						noeud[element[pa+j].extremite[2]].x = noeud[element[pa+j-1].extremite[2]].x;
						noeud[element[pa+j].extremite[2]].y = noeud[element[pa+j-1].extremite[2]].y;
						printf("El: %d ",pa+j);
						printf("D: 1 ");
						printf("%lf ",noeud[element[pa+j].extremite[1]].z);
						printf("%lf ",noeud[element[pa+j].extremite[1]].x);
						printf("%lf ",noeud[element[pa+j].extremite[1]].y);
						printf("%d ",noeud[element[pa+j].extremite[1]].type);
						printf(" 2 ");
						printf("%lf ",noeud[element[pa+j].extremite[2]].z);
						printf("%lf ",noeud[element[pa+j].extremite[2]].x);
						printf("%lf ",noeud[element[pa+j].extremite[2]].y);
						printf("%d ",noeud[element[pa+j].extremite[2]].type);
						}
					if (Structure.orientation == 2)
						{
						noeud[element[pa+j].extremite[1]].y = noeud[element[pa+j-1].extremite[1]].y + dist;
						noeud[element[pa+j].extremite[1]].z = noeud[element[pa+j-1].extremite[1]].z;
						noeud[element[pa+j].extremite[1]].x = noeud[element[pa+j-1].extremite[1]].x;
						noeud[element[pa+j].extremite[2]].y = noeud[element[pa+j-1].extremite[2]].y + dist;
						noeud[element[pa+j].extremite[2]].z = noeud[element[pa+j-1].extremite[2]].z;
						noeud[element[pa+j].extremite[2]].x = noeud[element[pa+j-1].extremite[2]].x;
						printf("El: %d ",pa+j);
						printf("D: 1 ");
						printf("%lf ",noeud[element[pa+j].extremite[1]].y);
						printf("%lf ",noeud[element[pa+j].extremite[1]].z);
						printf("%lf ",noeud[element[pa+j].extremite[1]].x);
						printf("%d ",noeud[element[pa+j].extremite[1]].type);
						printf(" 2 ");
						printf("%lf ",noeud[element[pa+j].extremite[2]].y);
						printf("%lf ",noeud[element[pa+j].extremite[2]].z);
						printf("%lf ",noeud[element[pa+j].extremite[2]].x);
						printf("%d ",noeud[element[pa+j].extremite[2]].type);
						}
					if (Structure.orientation == 3)
						{
						noeud[element[pa+j].extremite[1]].x = noeud[element[pa+j-1].extremite[1]].x + dist;
						noeud[element[pa+j].extremite[1]].y = noeud[element[pa+j-1].extremite[1]].y;
						noeud[element[pa+j].extremite[1]].z = noeud[element[pa+j-1].extremite[1]].z;
						noeud[element[pa+j].extremite[2]].x = noeud[element[pa+j-1].extremite[2]].x + dist;
						noeud[element[pa+j].extremite[2]].y = noeud[element[pa+j-1].extremite[2]].y;
						noeud[element[pa+j].extremite[2]].z = noeud[element[pa+j-1].extremite[2]].z;
						printf("El: %d ",pa+j);
						printf("D: 1 ");
						printf("%lf ",noeud[element[pa+j].extremite[1]].x);
						printf("%lf ",noeud[element[pa+j].extremite[1]].y);
						printf("%lf ",noeud[element[pa+j].extremite[1]].z);
						printf("%d ",noeud[element[pa+j].extremite[1]].type);
						printf(" 2 ");
						printf("%lf ",noeud[element[pa+j].extremite[2]].x);
						printf("%lf ",noeud[element[pa+j].extremite[2]].y);
						printf("%lf ",noeud[element[pa+j].extremite[2]].z);
						printf("%d ",noeud[element[pa+j].extremite[2]].type);
						}
			    		element[pa+j].raideur_traction 	= element[j].raideur_traction;
			    		element[pa+j].raideur_compression 	= element[j].raideur_compression;
			    		element[pa+j].lgrepos 			= element[j].lgrepos;
			    		element[pa+j].rhoelement 		= element[j].rhoelement;
			    		element[pa+j].diametrehydro 		= element[j].diametrehydro;
			    		element[pa+j].cdnormal 		= element[j].cdnormal;
			    		element[pa+j].ftangent 		= element[j].ftangent;
			    		element[pa+j].nb_barre 		= element[j].nb_barre;
			    		element[pa+j].type_noeud 		= element[j].type_noeud;
					printf("Kt: %lf ",element[pa+j].raideur_traction);
					printf("Kc: %lf ",element[pa+j].raideur_compression);
					printf("L: %lf ",element[pa+j].lgrepos);
					printf("M: %lf ",element[pa+j].rhoelement);
					printf("D: %lf ",element[pa+j].diametrehydro);
					printf("Cd: %lf ",element[pa+j].cdnormal);
					printf("f: %lf ",element[pa+j].ftangent);
					printf("n: %d ",element[pa+j].nb_barre);
					printf("t: %d\n",element[pa+j].type_noeud);
			    		
					}
				printf("\n");
				}
/* debut modifdp du 4 mars 2010*/
			if (strcmp(chaine,"rope_Y") == 0)
				{
				itmp = fscanf(fic,"%d",&i);
				itmp = fscanf(fic,"%d",&j);
				itmp = fscanf(fic,"%lf",&dist);
				printf("There are %d ropes like rope %d spaced of %lf created from rope %d (included)\n",i,j,dist,j);
				for (pa=1;pa<=i-1;pa++)
					{
					if (Structure.orientation == 1)
						{
						noeud[element[pa+j].extremite[1]].z = noeud[element[pa+j-1].extremite[1]].z;
						noeud[element[pa+j].extremite[1]].x = noeud[element[pa+j-1].extremite[1]].x + dist;
						noeud[element[pa+j].extremite[1]].y = noeud[element[pa+j-1].extremite[1]].y;
						noeud[element[pa+j].extremite[2]].z = noeud[element[pa+j-1].extremite[2]].z;
						noeud[element[pa+j].extremite[2]].x = noeud[element[pa+j-1].extremite[2]].x + dist;
						noeud[element[pa+j].extremite[2]].y = noeud[element[pa+j-1].extremite[2]].y;
						}
					if (Structure.orientation == 2)
						{
						noeud[element[pa+j].extremite[1]].y = noeud[element[pa+j-1].extremite[1]].y;
						noeud[element[pa+j].extremite[1]].z = noeud[element[pa+j-1].extremite[1]].z + dist;
						noeud[element[pa+j].extremite[1]].x = noeud[element[pa+j-1].extremite[1]].x;
						noeud[element[pa+j].extremite[2]].y = noeud[element[pa+j-1].extremite[2]].y;
						noeud[element[pa+j].extremite[2]].z = noeud[element[pa+j-1].extremite[2]].z + dist;
						noeud[element[pa+j].extremite[2]].x = noeud[element[pa+j-1].extremite[2]].x;
						}
					if (Structure.orientation == 3)
						{
						noeud[element[pa+j].extremite[1]].x = noeud[element[pa+j-1].extremite[1]].x;
						noeud[element[pa+j].extremite[1]].y = noeud[element[pa+j-1].extremite[1]].y + dist;
						noeud[element[pa+j].extremite[1]].z = noeud[element[pa+j-1].extremite[1]].z;
						noeud[element[pa+j].extremite[2]].x = noeud[element[pa+j-1].extremite[2]].x;
						noeud[element[pa+j].extremite[2]].y = noeud[element[pa+j-1].extremite[2]].y + dist;
						noeud[element[pa+j].extremite[2]].z = noeud[element[pa+j-1].extremite[2]].z;
						}
			    		element[pa+j].raideur_traction 		= element[j].raideur_traction;
			    		element[pa+j].raideur_compression 	= element[j].raideur_compression;
			    		element[pa+j].lgrepos 			= element[j].lgrepos;
			    		element[pa+j].rhoelement 		= element[j].rhoelement;
			    		element[pa+j].diametrehydro 		= element[j].diametrehydro;
			    		element[pa+j].cdnormal 			= element[j].cdnormal;
			    		element[pa+j].ftangent 			= element[j].ftangent;
			    		element[pa+j].nb_barre 			= element[j].nb_barre;
			    		element[pa+j].type_noeud 		= element[j].type_noeud;
					}
				}
			if (strcmp(chaine,"rope_Z") == 0)
				{
				itmp = fscanf(fic,"%d",&i);
				itmp = fscanf(fic,"%d",&j);
				itmp = fscanf(fic,"%lf",&dist);
				printf("There are %d ropes like rope %d spaced of %lf created from rope %d (included)\n",i,j,dist,j);
				for (pa=1;pa<=i-1;pa++)
					{
					if (Structure.orientation == 1)
						{
						noeud[element[pa+j].extremite[1]].z = noeud[element[pa+j-1].extremite[1]].z;
						noeud[element[pa+j].extremite[1]].x = noeud[element[pa+j-1].extremite[1]].x;
						noeud[element[pa+j].extremite[1]].y = noeud[element[pa+j-1].extremite[1]].y + dist;
						noeud[element[pa+j].extremite[2]].z = noeud[element[pa+j-1].extremite[2]].z;
						noeud[element[pa+j].extremite[2]].x = noeud[element[pa+j-1].extremite[2]].x;
						noeud[element[pa+j].extremite[2]].y = noeud[element[pa+j-1].extremite[2]].y + dist;
						}
					if (Structure.orientation == 2)
						{
						noeud[element[pa+j].extremite[1]].y = noeud[element[pa+j-1].extremite[1]].y;
						noeud[element[pa+j].extremite[1]].z = noeud[element[pa+j-1].extremite[1]].z;
						noeud[element[pa+j].extremite[1]].x = noeud[element[pa+j-1].extremite[1]].x + dist;
						noeud[element[pa+j].extremite[2]].y = noeud[element[pa+j-1].extremite[2]].y;
						noeud[element[pa+j].extremite[2]].z = noeud[element[pa+j-1].extremite[2]].z;
						noeud[element[pa+j].extremite[2]].x = noeud[element[pa+j-1].extremite[2]].x + dist;
						}
					if (Structure.orientation == 3)
						{
						noeud[element[pa+j].extremite[1]].x = noeud[element[pa+j-1].extremite[1]].x;
						noeud[element[pa+j].extremite[1]].y = noeud[element[pa+j-1].extremite[1]].y;
						noeud[element[pa+j].extremite[1]].z = noeud[element[pa+j-1].extremite[1]].z + dist;
						noeud[element[pa+j].extremite[2]].x = noeud[element[pa+j-1].extremite[2]].x;
						noeud[element[pa+j].extremite[2]].y = noeud[element[pa+j-1].extremite[2]].y;
						noeud[element[pa+j].extremite[2]].z = noeud[element[pa+j-1].extremite[2]].z + dist;
						}
			    		element[pa+j].raideur_traction 		= element[j].raideur_traction;
			    		element[pa+j].raideur_compression 	= element[j].raideur_compression;
			    		element[pa+j].lgrepos	 		= element[j].lgrepos;
			    		element[pa+j].rhoelement 			= element[j].rhoelement;
			    		element[pa+j].diametrehydro 		= element[j].diametrehydro;
			    		element[pa+j].cdnormal 			= element[j].cdnormal;
			    		element[pa+j].ftangent 			= element[j].ftangent;
			    		element[pa+j].nb_barre 			= element[j].nb_barre;
			    		element[pa+j].type_noeud 		= element[j].type_noeud;
					}
				}
/* fin modifdp du 4 mars 2010*/
			if (strcmp(chaine,"diamond_seam_element") == 0)
				{
				itmp = fscanf(fic,"%d",&temp_int);
				itmp = fscanf(fic,"%lf",&panneau[temp_int].seam);
				printf("add %lf seam meshes to the panel %d of diamond netting\n",panneau[temp_int].seam,temp_int);
				}
			if (strcmp(chaine,"sphere_element") == 0)
				{
				/*printf("add sphere floats  \n");*/
				itmp = fscanf(fic,"%d",&E_numero);
				itmp = fscanf(fic,"%lf",&S_Nb);
				itmp = fscanf(fic,"%lf",&S_Diam);
				itmp = fscanf(fic,"%lf",&S_Float);
				/* debut modifdp du 4 mars 2010*/
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
				Sphere_element.nb[Structure.nb_sphere_element] = S_Nb;
				Sphere_element.diameter[Structure.nb_sphere_element] = S_Diam;
				Sphere_element.floatability[Structure.nb_sphere_element] = S_Float;
				/* fin modifdp du 4 mars 2010*/
				printf("Add on element %d, %lg spheres diam %lgm floattability %lgN ",E_numero,S_Nb,S_Diam,S_Float);/**/
				S_Vol_Unit = 4.0 / 3.0 * PI * S_Diam * S_Diam * S_Diam / 8.0;
				S_Mass_Unit = S_Vol_Unit * RHO - S_Float / G;
				S_Cd = 0.6;				/*usual cd value for sphere*/
				S_Surf_Unit = PI * S_Diam * S_Diam / 4.0;
				S_Max_Float = S_Vol_Unit * RHO * G;
				//printf("RH, %lf G %lf S_Vol_Uni %lf\n",RHO,G,S_Vol_Unit);/**/
				
				if (S_Float > S_Max_Float)
					{
					printf("WARNING! The floattability (%lf N) of spheres is too large they must be limited to %lf N\n",S_Float,S_Max_Float);/**/
					exit(0);
 					}
				
				E_Length = element[E_numero].lgrepos;
				E_Density = element[E_numero].rhoelement;
				E_Diam = element[E_numero].diametrehydro;
				E_Cdn = element[E_numero].cdnormal;
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
				
				printf("has density %lgkg/m3 diam %lgm cd %lg ",element[E_numero].rhoelement,element[E_numero].diametrehydro,element[E_numero].cdnormal);/**/
    				element[E_numero].lgrepos = F_Length;
    				element[E_numero].rhoelement = F_Density;
    				element[E_numero].diametrehydro = F_Diam;
    				element[E_numero].cdnormal = F_Cdn;
				printf("has now density %lgkg/m3 diam %lgm cd %lg\n",element[E_numero].rhoelement,element[E_numero].diametrehydro,element[E_numero].cdnormal);/**/
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
				Sphere_element.nb[Structure.nb_sphere_element] = S_Nb;
				Sphere_element.diameter[Structure.nb_sphere_element] = S_Diam;
				Sphere_element.floatability[Structure.nb_sphere_element] = S_Float;
				printf("Add on element %d, %lg spheres diam %lgm floattability %lgN ",E_numero,S_Nb,S_Diam,S_Float);/**/
				S_Vol_Unit = 4.0 / 3.0 * PI * S_Diam * S_Diam * S_Diam / 8.0;
				S_Mass_Unit = S_Vol_Unit * RHO - S_Float / G;
				S_Cd = 0.6;				/*usual cd value for sphere*/
				S_Surf_Unit = PI * S_Diam * S_Diam / 4.0;
				S_Max_Float = S_Vol_Unit * RHO * G;
				//printf("RH, %lf G %lf S_Vol_Uni %lf\n",RHO,G,S_Vol_Unit);/**/
				
				if (S_Float > S_Max_Float)
					{
					printf("WARNING! The floattability (%lf N) of spheres is too large they must be limited to %lf N\n",S_Float,S_Max_Float);/**/
					exit(0);
 					}
				
				E_Length = L_Float;
				E_Density = element[E_numero].rhoelement;
				E_Diam = element[E_numero].diametrehydro;
				E_Cdn = element[E_numero].cdnormal;
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
				
				printf("has density %lgkg/m3 diam %lgm cd %lg ",element[E_numero].rhoelement,element[E_numero].diametrehydro,element[E_numero].cdnormal);/**/
    				//element[E_numero].lgrepos = F_Length;
    				element[E_numero].rhoelement = F_Density;
    				element[E_numero].diametrehydro = F_Diam;
    				element[E_numero].cdnormal = F_Cdn;
				printf("has now density %lgkg/m3 diam %lgm cd %lg\n",element[E_numero].rhoelement,element[E_numero].diametrehydro,element[E_numero].cdnormal);/**/
				}
			if (strcmp(chaine,"uniform_meshing") == 0)
				{
				printf("uniform_meshing  \n");
				for (pa=1;pa<=Structure.NbTypesurf;pa++)
					{
					/*find the first 3 points not aligned, called the reference points: p1 p2 p3 */
					p1 = 1;
					p2 = 2;
					p3 = 2;
					p1u = noeud[panneau[pa].noeud_contour[p1]].U;	p1v = noeud[panneau[pa].noeud_contour[p1]].V;
					p1x = noeud[panneau[pa].noeud_contour[p1]].x;						
					p1y = noeud[panneau[pa].noeud_contour[p1]].y;						
					p1z = noeud[panneau[pa].noeud_contour[p1]].z;	
					p2u = noeud[panneau[pa].noeud_contour[p2]].U;	p2v = noeud[panneau[pa].noeud_contour[p2]].V;
					p2x = noeud[panneau[pa].noeud_contour[p2]].x;						
					p2y = noeud[panneau[pa].noeud_contour[p2]].y;						
					p2z = noeud[panneau[pa].noeud_contour[p2]].z;	
					do
						{
						p3++;
						p3u = noeud[panneau[pa].noeud_contour[p3]].U;	p3v = noeud[panneau[pa].noeud_contour[p3]].V;
						p3x = noeud[panneau[pa].noeud_contour[p3]].x;						
						p3y = noeud[panneau[pa].noeud_contour[p3]].y;						
						p3z = noeud[panneau[pa].noeud_contour[p3]].z;	
						surface = fabs((p2u-p1u)*(p3v-p1v) - (p2v-p1v)*(p3u-p1u)); /*surfec of the triangle p1 p2 p3 in nb of meshes*/
						}
					while (surface == 0.0);
					printf("panel %d surface %lf p3 = %d  \n",pa,surface,p3);/**/
					/*for each points 0 (not in the 3 reference points: 1 2 3) calculate alpha and beta such as 10 = alpha 12 + beta 13*/
					for (p0=1;p0<=panneau[pa].nb_noeud_contour;p0++)
						{
						if ((p0!=p1) && (p0!=p2) && (p0!=p3))
							{
							p0u = noeud[panneau[pa].noeud_contour[p0]].U;	p0v = noeud[panneau[pa].noeud_contour[p0]].V;
							alpha = (-(p3u - p1u)*(p0v - p1v)+(p0u - p1u)*(p3v - p1v))/(-(p2v - p1v)*(p3u - p1u)+(p2u - p1u)*(p3v - p1v));
							beta =  (-(p2v - p1v)*(p0u - p1u)+(p2u - p1u)*(p0v - p1v))/(-(p2v - p1v)*(p3u - p1u)+(p2u - p1u)*(p3v - p1v));
							/*for each points (not in the 3 reference points) calculate the cartesians coordinates*/
							noeud[panneau[pa].noeud_contour[p0]].x = p1x + alpha * (p2x - p1x) + beta * (p3x - p1x);
							noeud[panneau[pa].noeud_contour[p0]].y = p1y + alpha * (p2y - p1y) + beta * (p3y - p1y);
							noeud[panneau[pa].noeud_contour[p0]].z = p1z + alpha * (p2z - p1z) + beta * (p3z - p1z);
							printf("   p0 %d alpha %lf beta %lf  \n",p0,alpha,beta);/**/
							}
						}				
					}
				}
			if (strcmp(chaine,"uniform_meshing2") == 0)
				{
				printf("uniform_meshing2  \n");
				itmp = fscanf(fic,"%d",&pa); /*panel involved*/
				itmp = fscanf(fic,"%d",&p1); /*point involved*/
				itmp = fscanf(fic,"%d",&p2); /*point involved*/
				itmp = fscanf(fic,"%d",&p3); /*point involved*/
				/*find the first 3 points not aligned, called the reference points: p1 p2 p3 */
				p1u = noeud[panneau[pa].noeud_contour[p1]].U;	p1v = noeud[panneau[pa].noeud_contour[p1]].V;
				p1x = noeud[panneau[pa].noeud_contour[p1]].x;						
				p1y = noeud[panneau[pa].noeud_contour[p1]].y;						
				p1z = noeud[panneau[pa].noeud_contour[p1]].z;	
				p2u = noeud[panneau[pa].noeud_contour[p2]].U;	p2v = noeud[panneau[pa].noeud_contour[p2]].V;
				p2x = noeud[panneau[pa].noeud_contour[p2]].x;						
				p2y = noeud[panneau[pa].noeud_contour[p2]].y;						
				p2z = noeud[panneau[pa].noeud_contour[p2]].z;	
				p3u = noeud[panneau[pa].noeud_contour[p3]].U;	p3v = noeud[panneau[pa].noeud_contour[p3]].V;
				p3x = noeud[panneau[pa].noeud_contour[p3]].x;						
				p3y = noeud[panneau[pa].noeud_contour[p3]].y;						
				p3z = noeud[panneau[pa].noeud_contour[p3]].z;	
				/*for each points 0 (not in the 3 reference points: 1 2 3) calculate alpha and beta such as 10 = alpha 12 + beta 13*/
				for (p0=1;p0<=panneau[pa].nb_noeud_contour;p0++)
					{
					if ((p0!=p1) && (p0!=p2) && (p0!=p3))
						{
						p0u = noeud[panneau[pa].noeud_contour[p0]].U;	p0v = noeud[panneau[pa].noeud_contour[p0]].V;
						alpha = (-(p3u - p1u)*(p0v - p1v)+(p0u - p1u)*(p3v - p1v))/(-(p2v - p1v)*(p3u - p1u)+(p2u - p1u)*(p3v - p1v));
						beta =  (-(p2v - p1v)*(p0u - p1u)+(p2u - p1u)*(p0v - p1v))/(-(p2v - p1v)*(p3u - p1u)+(p2u - p1u)*(p3v - p1v));
						/*for each points (not in the 3 reference points) calculate the cartesians coordinates*/
						noeud[panneau[pa].noeud_contour[p0]].x = p1x + alpha * (p2x - p1x) + beta * (p3x - p1x);
						noeud[panneau[pa].noeud_contour[p0]].y = p1y + alpha * (p2y - p1y) + beta * (p3y - p1y);
						noeud[panneau[pa].noeud_contour[p0]].z = p1z + alpha * (p2z - p1z) + beta * (p3z - p1z);
						printf("   p0 %d alpha %lf beta %lf  \n",p0,alpha,beta);/**/
						}
					}				
				}
			if (strcmp(chaine,"uniform_meshing3") == 0)
				{
/* debut modifdp du 4 mars 2010*/
				/*printf("uniform_meshing3  \n");*/
/* fin modifdp du 4 mars 2010*/
				itmp = fscanf(fic,"%d",&pa); /*panel involved*/
				itmp = fscanf(fic,"%d",&p1); /*no involved*/
				itmp = fscanf(fic,"%lf",&U2X); /*U size in m*/
				itmp = fscanf(fic,"%lf",&U2Y); /*U size in m*/
				itmp = fscanf(fic,"%lf",&U2Z); /*U size in m*/
				itmp = fscanf(fic,"%lf",&V2X); /*U size in m*/
				itmp = fscanf(fic,"%lf",&V2Y); /*U size in m*/
				itmp = fscanf(fic,"%lf",&V2Z); /*U size in m*/
/* debut modifdp du 4 mars 2010*/
				/*printf("pa %d p1 %d U2X %lf U2Y %lf  U2Z %lf  V2X %lf V2Y %lf U2Y %lf  \n",pa,p1,U2X,U2Y,U2Z,V2X,V2Y,V2Z);*/
/* fin modifdp du 4 mars 2010*/
				p1u = noeud[panneau[pa].noeud_contour[p1]].U;	p1v = noeud[panneau[pa].noeud_contour[p1]].V;
				p1x = noeud[panneau[pa].noeud_contour[p1]].x;	
				p1y = noeud[panneau[pa].noeud_contour[p1]].y;	
				p1z = noeud[panneau[pa].noeud_contour[p1]].z;	
				for (p0=1;p0<=panneau[pa].nb_noeud_contour;p0++)
					{
					if (p0!=p1)
						{
						p0u = noeud[panneau[pa].noeud_contour[p0]].U;	p0v = noeud[panneau[pa].noeud_contour[p0]].V;
						if (Structure.orientation == 1)
							{
							noeud[panneau[pa].noeud_contour[p0]].z = p1z + U2X * (p0u-p1u) + V2X * (p0v-p1v);
							noeud[panneau[pa].noeud_contour[p0]].x = p1x + U2Y * (p0u-p1u) + V2Y * (p0v-p1v);
							noeud[panneau[pa].noeud_contour[p0]].y = p1y + U2Z * (p0u-p1u) + V2Z * (p0v-p1v);
							}
						if (Structure.orientation == 2)
							{
							noeud[panneau[pa].noeud_contour[p0]].y = p1y + U2X * (p0u-p1u) + V2X * (p0v-p1v);
							noeud[panneau[pa].noeud_contour[p0]].z = p1z + U2Y * (p0u-p1u) + V2Y * (p0v-p1v);
							noeud[panneau[pa].noeud_contour[p0]].x = p1x + U2Z * (p0u-p1u) + V2Z * (p0v-p1v);
							}
						if (Structure.orientation == 3)
							{
							noeud[panneau[pa].noeud_contour[p0]].x = p1x + U2X * (p0u-p1u) + V2X * (p0v-p1v);
							noeud[panneau[pa].noeud_contour[p0]].y = p1y + U2Y * (p0u-p1u) + V2Y * (p0v-p1v);
							noeud[panneau[pa].noeud_contour[p0]].z = p1z + U2Z * (p0u-p1u) + V2Z * (p0v-p1v);
							}
						}
					}				
/* debut modifdp du 4 mars 2010*/
				printf("Panel : %d\n",pa);
				printf("Nombre de points du contour : %d\n",panneau[pa].nb_noeud_contour);
				printf("points du contour dans l ordre du contour no x y z U V no_type no_type_suivant :\n");
				for (p0=1;p0<=panneau[pa].nb_noeud_contour;p0++)
					{
					if (Structure.orientation == 1)
						{
						}
					if (Structure.orientation == 2)
						{
						printf("%d %9.2lf %9.2lf %9.2lf ",p0,noeud[panneau[pa].noeud_contour[p0]].y,noeud[panneau[pa].noeud_contour[p0]].z,noeud[panneau[pa].noeud_contour[p0]].x);/**/
						printf("%9.2lf %9.2lf ",noeud[panneau[pa].noeud_contour[p0]].U,noeud[panneau[pa].noeud_contour[p0]].V);/**/
						printf("%d %d\n",noeud[panneau[pa].noeud_contour[p0]].type,panneau[pa].type_suivant_contour[p0]);/**/
						}
					if (Structure.orientation == 3)
						{
						}
					}				
				printf("\n");
				printf("Raideur traction (N) 		: %12.0lf\n",panneau[pa].raideur_traction);
				printf("Raideur compression (N) 	: %12.0lf\n",panneau[pa].raideur_compression);
				printf("Raideur ouverture (N.m/rad) 	: %12.0lf\n",panneau[pa].raideur_ouverture);
				printf("Maille au repos (m) 		: %12.3lf\n",panneau[pa].longueur_repos);
				printf("Masse volumique (kg/m3) 	: %12.0lf\n",panneau[pa].rho);
				printf("Diametre hydrodynamique (m) 	: %12.4lf\n",panneau[pa].diam_hydro);
				printf("largeur noeud 			: %12.3lf\n",panneau[pa].largeurnoeud);
				printf("Cd normal 			: %12.2lf\n",panneau[pa].cdnormal);
				printf("Cd tangentiel 			: %12.2lf\n",panneau[pa].ftangent);
				printf("Pas du maillage (m) 		: %12.2lf\n",panneau[pa].pas_maillage);
				printf("type des noeuds interieurs 	: %12d\n",panneau[pa].type_noeud);
				printf("type de maillage 		: %12d\n\n",panneau[pa].type_maillage);
				/* fin modifdp du 4 mars 2010*/
				}
				
			if (strcmp(chaine,"add_x_pan") == 0)
				{
				/*reading of the distance added for some panels*/
				itmp = fscanf(fic,"%lf",&Structure.add_x_pa);
				itmp = fscanf(fic,"%d",&Structure.add_x_pa_no1);
				itmp = fscanf(fic,"%d",&Structure.add_x_pa_no2);
				printf("added distance along x = %lf  ",Structure.add_x_pa);
				printf("for panels from %d to %d\n",Structure.add_x_pa_no1,Structure.add_x_pa_no2);
				if ((Structure.add_x_pa_no1 < 1) || (Structure.add_x_pa_no2 > Structure.NbTypesurf))	printf("panels must be between 1 and %d\n",Structure.NbTypesurf);
				if (Structure.add_x_pa_no1 > Structure.add_x_pa_no2)	printf("no panel 1 must be >= no panel 2\n");
				for (zi=Structure.add_x_pa_no1;zi<=Structure.add_x_pa_no2;zi++)	for (no=1;no<=panneau[zi].nb_noeud_contour;no++)	noeud[panneau[zi].noeud_contour[no]].x  += (float) Structure.add_x_pa;
				initialisation_min_max();
				}
			if (strcmp(chaine,"add_y_pan") == 0)
				{
				/*reading of the distance added for some panels*/
				itmp = fscanf(fic,"%lf",&Structure.add_y_pa);
				itmp = fscanf(fic,"%d",&Structure.add_y_pa_no1);
				itmp = fscanf(fic,"%d",&Structure.add_y_pa_no2);
				printf("added distance along y = %lf  ",Structure.add_y_pa);
				printf("for panels from %d to %d\n",Structure.add_y_pa_no1,Structure.add_y_pa_no2);
				if ((Structure.add_y_pa_no1 < 1) || (Structure.add_y_pa_no2 > Structure.NbTypesurf))	printf("panels must be between 1 and %d\n",Structure.NbTypesurf);
				if (Structure.add_y_pa_no1 > Structure.add_y_pa_no2)	printf("no panel 1 must be >= no panel 2\n");
				for (zi=Structure.add_y_pa_no1;zi<=Structure.add_y_pa_no2;zi++)	for (no=1;no<=panneau[zi].nb_noeud_contour;no++)	noeud[panneau[zi].noeud_contour[no]].y  += (float) Structure.add_y_pa;
				initialisation_min_max();
				}
			if (strcmp(chaine,"add_z_pan") == 0)
				{
				/*reading of the distance added for some panels*/
				itmp = fscanf(fic,"%lf",&Structure.add_z_pa);
				itmp = fscanf(fic,"%d",&Structure.add_z_pa_no1);
				itmp = fscanf(fic,"%d",&Structure.add_z_pa_no2);
				printf("added distance along z = %lf  ",Structure.add_z_pa);
				printf("for panels from %d to %d\n",Structure.add_z_pa_no1,Structure.add_z_pa_no2);
				if ((Structure.add_z_pa_no1 < 1) || (Structure.add_z_pa_no2 > Structure.NbTypesurf))	printf("panels must be between 1 and %d\n",Structure.NbTypesurf);
				if (Structure.add_z_pa_no1 > Structure.add_z_pa_no2)	printf("no panel 1 must be >= no panel 2\n");
				for (zi=Structure.add_z_pa_no1;zi<=Structure.add_z_pa_no2;zi++)	for (no=1;no<=panneau[zi].nb_noeud_contour;no++)	noeud[panneau[zi].noeud_contour[no]].z  += (float) Structure.add_z_pa;
				initialisation_min_max();
				}
			if (strcmp(chaine,"add_x_ele") == 0)
				{
				/*reading of the distance added for some panels*/
				itmp = fscanf(fic,"%lf",&Structure.add_x_el);
				itmp = fscanf(fic,"%d",&Structure.add_x_el_no1);
				itmp = fscanf(fic,"%d",&Structure.add_x_el_no2);
				printf("added distance along x = %lf  ",Structure.add_x_el);
				printf("for elements from %d to %d\n",Structure.add_x_el_no1,Structure.add_x_el_no2);
				if ((Structure.add_x_el_no1 < 1) || (Structure.add_x_el_no2 > Structure.NbTypeelem))	printf("elements must be between 1 and %d\n",Structure.NbTypeelem);
				if (Structure.add_x_el_no1 > Structure.add_x_el_no2)	printf("no element 1 must be >= no element 2\n");
				for (zi=Structure.add_x_el_no1;zi<=Structure.add_x_el_no2;zi++)	for (no=1;no<=2;no++)	noeud[element[zi].extremite[no]].x  += (float) Structure.add_x_el;
				initialisation_min_max();
				}
			if (strcmp(chaine,"add_y_ele") == 0)
				{
				/*reading of the distance added for some panels*/
				itmp = fscanf(fic,"%lf",&Structure.add_y_el);
				itmp = fscanf(fic,"%d",&Structure.add_y_el_no1);
				itmp = fscanf(fic,"%d",&Structure.add_y_el_no2);
				printf("added distance along y = %lf  ",Structure.add_y_el);
				printf("for elements from %d to %d\n",Structure.add_y_el_no1,Structure.add_y_el_no2);
				if ((Structure.add_y_el_no1 < 1) || (Structure.add_y_el_no2 > Structure.NbTypeelem))	printf("elements must be between 1 and %d\n",Structure.NbTypeelem);
				if (Structure.add_y_el_no1 > Structure.add_y_el_no2)	printf("no element 1 must be >= no element 2\n");
				for (zi=Structure.add_y_el_no1;zi<=Structure.add_y_el_no2;zi++)	for (no=1;no<=2;no++)	noeud[element[zi].extremite[no]].y  += (float) Structure.add_y_el;
				initialisation_min_max();
				}
			if (strcmp(chaine,"add_z_ele") == 0)
				{
				/*reading of the distance added for some panels*/
				itmp = fscanf(fic,"%lf",&Structure.add_z_el);
				itmp = fscanf(fic,"%d",&Structure.add_z_el_no1);
				itmp = fscanf(fic,"%d",&Structure.add_z_el_no2);
				printf("added distance along z = %lf  ",Structure.add_z_el);
				printf("for elements from %d to %d\n",Structure.add_z_el_no1,Structure.add_z_el_no2);
				if ((Structure.add_z_el_no1 < 1) || (Structure.add_z_el_no2 > Structure.NbTypeelem))	printf("elements must be between 1 and %d\n",Structure.NbTypeelem);
				if (Structure.add_z_el_no1 > Structure.add_z_el_no2)	printf("no element 1 must be >= no element 2\n");
				for (zi=Structure.add_z_el_no1;zi<=Structure.add_z_el_no2;zi++)	for (no=1;no<=2;no++)	noeud[element[zi].extremite[no]].z  += (float) Structure.add_z_el;
				initialisation_min_max();
				}
			if (strcmp(chaine,"rot_x_ele") == 0)
				{
				/*reading of the center of rotation (yo,zo in m) and the angle (teta in rad)*/
				itmp = fscanf(fic,"%lf",&Structure.rot_el_yyo);
				itmp = fscanf(fic,"%lf",&Structure.rot_el_zzo);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				Structure.rot_el_teta = PI / tmp_d1;
				/*reading the nb among them the elements are rotated */
				itmp = fscanf(fic,"%d",&Structure.rot_el_no1);
				itmp = fscanf(fic,"%d",&Structure.rot_el_no2);
				printf("rotation of %lf rad around y %lf z %lf ",Structure.rot_el_teta,Structure.rot_el_yyo,Structure.rot_el_zzo);
				printf("for elements from %d to %d\n",Structure.rot_el_no1,Structure.rot_el_no2);
				if ((Structure.rot_el_no1 < 1) || (Structure.rot_el_no2 > Structure.NbTypeelem))	printf("elements must be between 1 and %d\n",Structure.NbTypeelem);
				if (Structure.rot_el_no1 > Structure.rot_el_no2)	printf("no element 1 must be >= no element 2\n");
				for (zi=Structure.rot_el_no1;zi<=Structure.rot_el_no2;zi++)	
					{
					for (no=1;no<=2;no++)	
						{
						yy1 = (double) noeud[element[zi].extremite[no]].y;
						zz1 = (double) noeud[element[zi].extremite[no]].z;
						yyp = Structure.rot_el_yyo + (yy1-Structure.rot_el_yyo) * cos(Structure.rot_el_teta) - (zz1-Structure.rot_el_zzo) * sin(Structure.rot_el_teta);
						zzp = Structure.rot_el_zzo + (yy1-Structure.rot_el_yyo) * sin(Structure.rot_el_teta) + (zz1-Structure.rot_el_zzo) * cos(Structure.rot_el_teta);
						noeud[element[zi].extremite[no]].y = (float) yyp;
						noeud[element[zi].extremite[no]].z = (float) zzp;
						}
					}
				initialisation_min_max();
				}
			if (strcmp(chaine,"rot_y_ele") == 0)
				{
				/*reading of the center of rotation (zo,xo in m) and the angle (teta in rad)*/
				itmp = fscanf(fic,"%lf",&Structure.rot_el_zzo);
				itmp = fscanf(fic,"%lf",&Structure.rot_el_xxo);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				Structure.rot_el_teta = PI / tmp_d1;
				/*reading the nb among them the elements are rotated */
				itmp = fscanf(fic,"%d",&Structure.rot_el_no1);
				itmp = fscanf(fic,"%d",&Structure.rot_el_no2);
				printf("rotation of %lf rad around z %lf x %lf ",Structure.rot_el_teta,Structure.rot_el_zzo,Structure.rot_el_xxo);
				printf("for elements from %d to %d\n",Structure.rot_el_no1,Structure.rot_el_no2);
				if ((Structure.rot_el_no1 < 1) || (Structure.rot_el_no2 > Structure.NbTypeelem))	printf("elements must be between 1 and %d\n",Structure.NbTypeelem);
				if (Structure.rot_el_no1 > Structure.rot_el_no2)	printf("no element 1 must be >= no element 2\n");
				for (zi=Structure.rot_el_no1;zi<=Structure.rot_el_no2;zi++)	
					{
					for (no=1;no<=2;no++)	
						{
						zz1 = (double) noeud[element[zi].extremite[no]].z;
						xx1 = (double) noeud[element[zi].extremite[no]].x;
						zzp = Structure.rot_el_zzo + (zz1-Structure.rot_el_zzo) * cos(Structure.rot_el_teta) - (xx1-Structure.rot_el_xxo) * sin(Structure.rot_el_teta);
						xxp = Structure.rot_el_xxo + (zz1-Structure.rot_el_zzo) * sin(Structure.rot_el_teta) + (xx1-Structure.rot_el_xxo) * cos(Structure.rot_el_teta);
						noeud[element[zi].extremite[no]].z = (float) zzp;
						noeud[element[zi].extremite[no]].x = (float) xxp;
						}
					}
				initialisation_min_max();
				}
			if (strcmp(chaine,"rot_z_ele") == 0)
				{
				/*reading of the center of rotation (xo,yo in m) and the angle (teta in rad)*/
				itmp = fscanf(fic,"%lf",&Structure.rot_el_xxo);
				itmp = fscanf(fic,"%lf",&Structure.rot_el_yyo);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				Structure.rot_el_teta = PI / tmp_d1;
				/*reading the nb among them the elements are rotated */
				itmp = fscanf(fic,"%d",&Structure.rot_el_no1);
				itmp = fscanf(fic,"%d",&Structure.rot_el_no2);
				printf("rotation of %lf rad around x %lf y %lf ",Structure.rot_el_teta,Structure.rot_el_xxo,Structure.rot_el_yyo);
				printf("for elements from %d to %d\n",Structure.rot_el_no1,Structure.rot_el_no2);
				if ((Structure.rot_el_no1 < 1) || (Structure.rot_el_no2 > Structure.NbTypeelem))	printf("elements must be between 1 and %d\n",Structure.NbTypeelem);
				if (Structure.rot_el_no1 > Structure.rot_el_no2)	printf("no element 1 must be >= no element 2\n");
				for (zi=Structure.rot_el_no1;zi<=Structure.rot_el_no2;zi++)	
					{
					for (no=1;no<=2;no++)	
						{
						xx1 = (double) noeud[element[zi].extremite[no]].x;
						yy1 = (double) noeud[element[zi].extremite[no]].y;
						xxp = Structure.rot_el_xxo + (xx1-Structure.rot_el_xxo) * cos(Structure.rot_el_teta) - (yy1-Structure.rot_el_yyo) * sin(Structure.rot_el_teta);
						yyp = Structure.rot_el_yyo + (xx1-Structure.rot_el_xxo) * sin(Structure.rot_el_teta) + (yy1-Structure.rot_el_yyo) * cos(Structure.rot_el_teta);
						noeud[element[zi].extremite[no]].x = (float) xxp;
						noeud[element[zi].extremite[no]].y = (float) yyp;
						}
					}
				initialisation_min_max();
				}
			if (strcmp(chaine,"rot_x_pan") == 0)
				{
				/*reading of the center of rotation (yo,zo in m) and the angle (teta in rad)*/
				itmp = fscanf(fic,"%lf",&Structure.rot_pa_yyo);
				itmp = fscanf(fic,"%lf",&Structure.rot_pa_zzo);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				Structure.rot_pa_teta = PI / tmp_d1;
				/*reading the nb among them the panels are rotated */
				itmp = fscanf(fic,"%d",&Structure.rot_pa_no1);
				itmp = fscanf(fic,"%d",&Structure.rot_pa_no2);
				printf("rotation of %lf rad around y %lf z %lf ",Structure.rot_pa_teta,Structure.rot_pa_yyo,Structure.rot_pa_zzo);
				printf("for panels from %d to %d\n",Structure.rot_pa_no1,Structure.rot_pa_no2);
				if ((Structure.rot_pa_no1 < 1) || (Structure.rot_pa_no2 > Structure.NbTypesurf))	printf("panels must be between 1 and %d\n",Structure.NbTypesurf);
				if (Structure.rot_pa_no1 > Structure.rot_pa_no2)	printf("no panneau 1 must be >= no panneau 2\n");
				for (zi=Structure.rot_pa_no1;zi<=Structure.rot_pa_no2;zi++)	
					{
					for (no=1;no<=panneau[zi].nb_noeud_contour;no++)	
						{
						yy1 = (double) noeud[panneau[zi].noeud_contour[no]].y;
						zz1 = (double) noeud[panneau[zi].noeud_contour[no]].z;
						yyp = Structure.rot_pa_yyo + (yy1-Structure.rot_pa_yyo) * cos(Structure.rot_pa_teta) - (zz1-Structure.rot_pa_zzo) * sin(Structure.rot_pa_teta);
						zzp = Structure.rot_pa_zzo + (yy1-Structure.rot_pa_yyo) * sin(Structure.rot_pa_teta) + (zz1-Structure.rot_pa_zzo) * cos(Structure.rot_pa_teta);
						noeud[panneau[zi].noeud_contour[no]].y = (float) yyp;
						noeud[panneau[zi].noeud_contour[no]].z = (float) zzp;
						}
					}
				initialisation_min_max();
				}
			if (strcmp(chaine,"rot_y_pan") == 0)
				{
				/*reading of the center of rotation (zo,xo in m) and the angle (teta in rad)*/
				itmp = fscanf(fic,"%lf",&Structure.rot_pa_zzo);
				itmp = fscanf(fic,"%lf",&Structure.rot_pa_xxo);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				Structure.rot_pa_teta = PI / tmp_d1;
				/*reading the nb among them the panels are rotated */
				itmp = fscanf(fic,"%d",&Structure.rot_pa_no1);
				itmp = fscanf(fic,"%d",&Structure.rot_pa_no2);
				printf("rotation of %lf rad around z %lf x %lf ",Structure.rot_pa_teta,Structure.rot_pa_zzo,Structure.rot_pa_xxo);
				printf("for panels from %d to %d\n",Structure.rot_pa_no1,Structure.rot_pa_no2);
				if ((Structure.rot_pa_no1 < 1) || (Structure.rot_pa_no2 > Structure.NbTypesurf))	printf("panels must be between 1 and %d\n",Structure.NbTypesurf);
				if (Structure.rot_pa_no1 > Structure.rot_pa_no2)	printf("no panneau 1 must be >= no panneau 2\n");
				for (zi=Structure.rot_pa_no1;zi<=Structure.rot_pa_no2;zi++)	
					{
					for (no=1;no<=panneau[zi].nb_noeud_contour;no++)	
						{
						zz1 = (double) noeud[panneau[zi].noeud_contour[no]].z;
						xx1 = (double) noeud[panneau[zi].noeud_contour[no]].x;
						zzp = Structure.rot_pa_zzo + (zz1-Structure.rot_pa_zzo) * cos(Structure.rot_pa_teta) - (xx1-Structure.rot_pa_xxo) * sin(Structure.rot_pa_teta);
						xxp = Structure.rot_pa_xxo + (zz1-Structure.rot_pa_zzo) * sin(Structure.rot_pa_teta) + (xx1-Structure.rot_pa_xxo) * cos(Structure.rot_pa_teta);
						noeud[panneau[zi].noeud_contour[no]].z = (float) zzp;
						noeud[panneau[zi].noeud_contour[no]].x = (float) xxp;
						}
					}
				initialisation_min_max();
				}
			if (strcmp(chaine,"rot_z_pan") == 0)
				{
				/*reading of the center of rotation (xo,yo in m) and the angle (teta in rad)*/
				itmp = fscanf(fic,"%lf",&Structure.rot_pa_xxo);
				itmp = fscanf(fic,"%lf",&Structure.rot_pa_yyo);
				itmp = fscanf(fic,"%lf",&tmp_d1);
				Structure.rot_pa_teta = PI / tmp_d1;
				/*reading the nb among them the panels are rotated */
				itmp = fscanf(fic,"%d",&Structure.rot_pa_no1);
				itmp = fscanf(fic,"%d",&Structure.rot_pa_no2);
				printf("rotation of %lf rad around x %lf y %lf ",Structure.rot_pa_teta,Structure.rot_pa_xxo,Structure.rot_pa_yyo);
				printf("for panels from %d to %d\n",Structure.rot_pa_no1,Structure.rot_pa_no2);
				if ((Structure.rot_pa_no1 < 1) || (Structure.rot_pa_no2 > Structure.NbTypesurf))	printf("panels must be between 1 and %d\n",Structure.NbTypesurf);
				if (Structure.rot_pa_no1 > Structure.rot_pa_no2)	printf("no panneau 1 must be >= no panneau 2\n");
				for (zi=Structure.rot_pa_no1;zi<=Structure.rot_pa_no2;zi++)	
					{
					for (no=1;no<=panneau[zi].nb_noeud_contour;no++)	
						{
						xx1 = (double) noeud[panneau[zi].noeud_contour[no]].x;
						yy1 = (double) noeud[panneau[zi].noeud_contour[no]].y;
						xxp = Structure.rot_pa_xxo + (xx1-Structure.rot_pa_xxo) * cos(Structure.rot_pa_teta) - (yy1-Structure.rot_pa_yyo) * sin(Structure.rot_pa_teta);
						yyp = Structure.rot_pa_yyo + (xx1-Structure.rot_pa_xxo) * sin(Structure.rot_pa_teta) + (yy1-Structure.rot_pa_yyo) * cos(Structure.rot_pa_teta);
						noeud[panneau[zi].noeud_contour[no]].x = (float) xxp;
						noeud[panneau[zi].noeud_contour[no]].y = (float) yyp;
						}
					}
				initialisation_min_max();
				}


/**********************************************************************************************************************/
/**********************************************************************************************************************/

			if (strcmp(chaine,"add_cage") == 0)
				{

				/*reading of the center of rotation (xo,yo in m) */
				Structure.add_number_cage=Structure.add_number_cage+1;
				itmp = fscanf(fic,"%lf",&Structure.add_cage_diam);
				itmp = fscanf(fic,"%lf",&Structure.add_cage_xxo);
				itmp = fscanf(fic,"%lf",&Structure.add_cage_yyo);
				itmp = fscanf(fic,"%d",&Structure.add_cage_nsegment);
				itmp = fscanf(fic,"%lf",&Structure.add_cage_dist_ann);
				itmp = fscanf(fic,"%lf",&Structure.add_cage_haut_ann);
				itmp = fscanf(fic,"%lf",&Structure.add_hauteur_filet_elev);
				itmp = fscanf(fic,"%lf",&Structure.add_taille_maille_elev);
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
				printf("cage of %lf diametre centre x %lf y %lf nombre de segment %d \n",Structure.add_cage_diam,Structure.add_cage_xxo,Structure.add_cage_yyo,Structure.add_cage_nsegment);


				/* définition des paramètres*/

				double hauteur_pieds = Structure.add_cage_haut_ann;
				double distance_anneaux = Structure.add_cage_dist_ann;

				double coeff_trainee_inter = 1.2;	/* coefficient de trainée des barres de la cage*/

				double pronf_niveau_bas = 0;		/* profondeur des barres du niveau bas (sous phobos)*/
				double pronf_niveau_haut = pronf_niveau_bas + Structure.add_cage_haut_ann;		/* profondeur des barres du niveau haut (sous phobos)*/


				/*			PANNEAU			*/

				nb_tot_pan_elev += (Structure.add_cage_nsegment +1);

				double nb_maille_diametre = Structure.add_cage_diam/(Structure.add_taille_maille_elev*sqrt(2));

				/* PANNEAU FOND*/
					
				panneau[pan_inter_fond].longueur_repos = Structure.add_taille_maille_elev;


				/*	printf("%lf %lf \n%",noeud[panneau[pan_inter_fond].noeud_contour[1]].U,noeud[panneau[pan_inter_fond].noeud_contour[1]].V);*/
							
				for (no=1;no<=Structure.add_cage_nsegment;no++)
					{

					xxp = Structure.add_cage_xxo - Structure.add_cage_diam/2*cos(2*PI*(no-1)/Structure.add_cage_nsegment);
					yyp = Structure.add_cage_yyo - Structure.add_cage_diam/2*sin(2*PI*(no-1)/Structure.add_cage_nsegment);

					noeud[panneau[pan_inter_fond].noeud_contour[no]].x = xxp;
					noeud[panneau[pan_inter_fond].noeud_contour[no]].y = yyp;
					noeud[panneau[pan_inter_fond].noeud_contour[no]].z = - Structure.add_hauteur_filet_elev + pronf_niveau_bas;
					}

				/*calcul minx maxx miny maxy*/

				double minx = Structure.add_cage_xxo;
				double maxx = Structure.add_cage_xxo;

				for (no=1;no<=panneau[pan_inter_fond].nb_noeud_contour;no++)
					{
					if (noeud[panneau[pan_inter_fond].noeud_contour[no]].x < minx) minx =noeud[panneau[pan_inter_fond].noeud_contour[no]].x;
					if (noeud[panneau[pan_inter_fond].noeud_contour[no]].x > maxx) maxx =noeud[panneau[pan_inter_fond].noeud_contour[no]].x;
					}

				double ecartx = maxx - minx;
				double ratio = nb_maille_diametre/ ecartx;
											

				/*calcul vecteur*/
	
				for (no=1;no<=panneau[pan_inter_fond].nb_noeud_contour;no++)
					{
					noeud[panneau[pan_inter_fond].noeud_contour[no]].U =(noeud[panneau[pan_inter_fond].noeud_contour[no]].x - Structure.add_cage_xxo)*ratio ;
					noeud[panneau[pan_inter_fond].noeud_contour[no]].V =(noeud[panneau[pan_inter_fond].noeud_contour[no]].y - Structure.add_cage_yyo)*ratio ;

					noeud[panneau[pan_inter_fond].noeud_contour[no]].u =  noeud[panneau[pan_inter_fond].noeud_contour[no]].U + noeud[panneau[pan_inter_fond].noeud_contour[no]].V; 
					noeud[panneau[pan_inter_fond].noeud_contour[no]].v = -noeud[panneau[pan_inter_fond].noeud_contour[no]].U + noeud[panneau[pan_inter_fond].noeud_contour[no]].V; 
					}


				/* PANNEAUX LATERAUX */

				for (zi=pan_inter;zi<=pan_inter + Structure.add_cage_nsegment-1;zi++)	
					{

					/*noeud 1*/
					xxp1 = (float) Structure.add_cage_xxo - Structure.add_cage_diam/2*cos(2*PI*(zi-pan_inter)/Structure.add_cage_nsegment);
					yyp1 = (float) Structure.add_cage_yyo - Structure.add_cage_diam/2*sin(2*PI*(zi-pan_inter)/Structure.add_cage_nsegment);
					/*noeud 3*/
					xxp3 = (float) Structure.add_cage_xxo - Structure.add_cage_diam/2*cos(2*PI*(zi-pan_inter+1)/Structure.add_cage_nsegment);
					yyp3 = (float) Structure.add_cage_yyo - Structure.add_cage_diam/2*sin(2*PI*(zi-pan_inter+1)/Structure.add_cage_nsegment);
					
					noeud[panneau[zi].noeud_contour[1]].x = xxp1;
					noeud[panneau[zi].noeud_contour[1]].y = yyp1;
					noeud[panneau[zi].noeud_contour[1]].z = - Structure.add_hauteur_filet_elev + pronf_niveau_bas;

					noeud[panneau[zi].noeud_contour[2]].x = xxp1;
					noeud[panneau[zi].noeud_contour[2]].y = yyp1;
					noeud[panneau[zi].noeud_contour[2]].z = pronf_niveau_bas;

					noeud[panneau[zi].noeud_contour[3]].x = xxp3;
					noeud[panneau[zi].noeud_contour[3]].y = yyp3;
					noeud[panneau[zi].noeud_contour[3]].z = pronf_niveau_bas;

					noeud[panneau[zi].noeud_contour[4]].x = xxp3;
					noeud[panneau[zi].noeud_contour[4]].y = yyp3;
					noeud[panneau[zi].noeud_contour[4]].z = - Structure.add_hauteur_filet_elev + pronf_niveau_bas;

					panneau[zi].longueur_repos = Structure.add_taille_maille_elev;

					noeud[panneau[zi].noeud_contour[1]].U = 0;
					noeud[panneau[zi].noeud_contour[1]].V = 0;
					noeud[panneau[zi].noeud_contour[2]].U = 0;
					noeud[panneau[zi].noeud_contour[2]].V = -floor((Structure.add_hauteur_filet_elev) / (Structure.add_taille_maille_elev * sqrt(2)));
					noeud[panneau[zi].noeud_contour[3]].U = floor(Structure.add_cage_diam * PI/Structure.add_cage_nsegment / (Structure.add_taille_maille_elev * sqrt(2)));
					noeud[panneau[zi].noeud_contour[3]].V = -floor((Structure.add_hauteur_filet_elev) / (Structure.add_taille_maille_elev * sqrt(2)));
					noeud[panneau[zi].noeud_contour[4]].U = floor(Structure.add_cage_diam * PI/Structure.add_cage_nsegment / (Structure.add_taille_maille_elev * sqrt(2)));
					noeud[panneau[zi].noeud_contour[4]].V = 0;

					for (no=1;no<=4;no++)
						{
						noeud[panneau[zi].noeud_contour[no]].u =  noeud[panneau[zi].noeud_contour[no]].U + noeud[panneau[zi].noeud_contour[no]].V; 
						noeud[panneau[zi].noeud_contour[no]].v = -noeud[panneau[zi].noeud_contour[no]].U + noeud[panneau[zi].noeud_contour[no]].V; 
						}
					/*	printf("%lf %lf \n%lf %lf \n %lf %lf \n%lf %lf\n",noeud[panneau[zi].noeud_contour[1]].U,noeud[panneau[zi].noeud_contour[1]].V,noeud[panneau[zi].noeud_contour[2]].U,noeud[panneau[zi].noeud_contour[2]].V,noeud[panneau[zi].noeud_contour[3]].U,noeud[panneau[zi].noeud_contour[3]].V,noeud[panneau[zi].noeud_contour[4]].U,noeud[panneau[zi].noeud_contour[4]].V);*/					

					}

				pan_inter_fond += Structure.add_cage_nsegment+1;
				pan_inter += Structure.add_cage_nsegment+1;




				/* 		ELEMENT 	*/



				for (zi=elem_inter;zi<=elem_inter+8*Structure.add_cage_nsegment-1;zi=zi+8)
					{
					int fl = floor((zi-elem_inter)/8);

					xxp11 = (float) Structure.add_cage_xxo - Structure.add_cage_diam/2*cos(2*PI*fl/Structure.add_cage_nsegment);
					yyp11 = (float) Structure.add_cage_yyo - Structure.add_cage_diam/2*sin(2*PI*fl/Structure.add_cage_nsegment);
					xxp12 = (float) Structure.add_cage_xxo - Structure.add_cage_diam/2*cos(2*PI*(fl+1)/Structure.add_cage_nsegment);
					yyp12 = (float) Structure.add_cage_yyo - Structure.add_cage_diam/2*sin(2*PI*(fl+1)/Structure.add_cage_nsegment);
					
					xxp21 = (float) Structure.add_cage_xxo - (Structure.add_cage_diam/2+distance_anneaux)*cos(2*PI*fl/Structure.add_cage_nsegment);
					yyp21 = (float) Structure.add_cage_yyo - (Structure.add_cage_diam/2+distance_anneaux)*sin(2*PI*fl/Structure.add_cage_nsegment);
					xxp22 = (float) Structure.add_cage_xxo - (Structure.add_cage_diam/2+distance_anneaux)*cos(2*PI*(fl+1)/Structure.add_cage_nsegment);
					yyp22 = (float) Structure.add_cage_yyo - (Structure.add_cage_diam/2+distance_anneaux)*sin(2*PI*(fl+1)/Structure.add_cage_nsegment);
					
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

					noeud[element[zi+0].extremite[1]].x = xxp11;
					noeud[element[zi+0].extremite[1]].y = yyp11;
					noeud[element[zi+0].extremite[1]].z = pronf_niveau_bas;

					noeud[element[zi+0].extremite[2]].x = xxp12;
					noeud[element[zi+0].extremite[2]].y = yyp12;
					noeud[element[zi+0].extremite[2]].z = pronf_niveau_bas;

					noeud[element[zi+1].extremite[1]].x = xxp21;
					noeud[element[zi+1].extremite[1]].y = yyp21;
					noeud[element[zi+1].extremite[1]].z = pronf_niveau_bas;

					noeud[element[zi+1].extremite[2]].x = xxp22;
					noeud[element[zi+1].extremite[2]].y = yyp22;
					noeud[element[zi+1].extremite[2]].z = pronf_niveau_bas;

					noeud[element[zi+2].extremite[1]].x = xxp31;
					noeud[element[zi+2].extremite[1]].y = yyp31;
					noeud[element[zi+2].extremite[1]].z = pronf_niveau_bas;

					noeud[element[zi+2].extremite[2]].x = xxp32;
					noeud[element[zi+2].extremite[2]].y = yyp32;
					noeud[element[zi+2].extremite[2]].z = pronf_niveau_bas;

					noeud[element[zi+3].extremite[1]].x = xxp41;
					noeud[element[zi+3].extremite[1]].y = yyp41;
					noeud[element[zi+3].extremite[1]].z = pronf_niveau_haut;

					noeud[element[zi+3].extremite[2]].x = xxp42;
					noeud[element[zi+3].extremite[2]].y = yyp42;
					noeud[element[zi+3].extremite[2]].z = pronf_niveau_haut;

					noeud[element[zi+4].extremite[1]].x = xxp51;
					noeud[element[zi+4].extremite[1]].y = yyp51;
					noeud[element[zi+4].extremite[1]].z = pronf_niveau_haut;

					noeud[element[zi+4].extremite[2]].x = xxp52;
					noeud[element[zi+4].extremite[2]].y = yyp52;
					noeud[element[zi+4].extremite[2]].z = pronf_niveau_bas;


					noeud[element[zi+5].extremite[1]].x = xxp61;
					noeud[element[zi+5].extremite[1]].y = yyp61;
					noeud[element[zi+5].extremite[1]].z = pronf_niveau_haut;

					noeud[element[zi+5].extremite[2]].x = xxp62;
					noeud[element[zi+5].extremite[2]].y = yyp62;
					noeud[element[zi+5].extremite[2]].z = pronf_niveau_bas;

					noeud[element[zi+6].extremite[1]].x = xxp71;
					noeud[element[zi+6].extremite[1]].y = yyp71;
					noeud[element[zi+6].extremite[1]].z = pronf_niveau_bas;

					noeud[element[zi+6].extremite[2]].x = xxp72;
					noeud[element[zi+6].extremite[2]].y = yyp72;
					noeud[element[zi+6].extremite[2]].z = pronf_niveau_bas;

					noeud[element[zi+7].extremite[1]].x = xxp81;
					noeud[element[zi+7].extremite[1]].y = yyp81;
					noeud[element[zi+7].extremite[1]].z = pronf_niveau_bas;

					noeud[element[zi+7].extremite[2]].x = xxp82;
					noeud[element[zi+7].extremite[2]].y = yyp82;
					noeud[element[zi+7].extremite[2]].z = pronf_niveau_haut;


					/* Calcul Coeff trainée + diametre + masse volumqiue pieds */


					element[zi+0].diametrehydro = diametre_pehd;	
					element[zi+1].diametrehydro = diametre_pehd;
					element[zi+2].diametrehydro = diametre_pehd;	
					element[zi+3].diametrehydro = diametre_pehd;				
					element[zi+4].diametrehydro = diametre_pehd;
					element[zi+5].diametrehydro = 0;	
					element[zi+6].diametrehydro = 0;
					element[zi+7].diametrehydro = 0;
				
				/*if (immersion ==0)
					{
					element[zi+0].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					element[zi+1].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					element[zi+2].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					element[zi+3].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					element[zi+4].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					}

				if (immersion ==1)
					{
					element[zi+0].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					element[zi+1].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					element[zi+2].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					element[zi+3].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					element[zi+4].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
					}

					element[zi+0].cdnormal = coeff_trainee_inter;				
					element[zi+1].cdnormal = coeff_trainee_inter;
					element[zi+2].cdnormal = coeff_trainee_inter;
					element[zi+3].cdnormal = coeff_trainee_inter;
					element[zi+4].cdnormal = coeff_trainee_inter;*/


					double longueur_premiere_rangee=sqrt((noeud[element[zi+0].extremite[1]].x-noeud[element[zi+0].extremite[2]].x)*(noeud[element[zi+0].extremite[1]].x-noeud[element[zi+0].extremite[2]].x) + (noeud[element[zi+0].extremite[1]].y-noeud[element[zi+0].extremite[2]].y)*(noeud[element[zi+0].extremite[1]].y-noeud[element[zi+0].extremite[2]].y) + (noeud[element[zi+0].extremite[1]].z-noeud[element[zi+0].extremite[2]].z)*(noeud[element[zi+0].extremite[1]].z-noeud[element[zi+0].extremite[2]].z));
					double longueur_deuxieme_rangee=sqrt((noeud[element[zi+1].extremite[1]].x-noeud[element[zi+1].extremite[2]].x)*(noeud[element[zi+1].extremite[1]].x-noeud[element[zi+1].extremite[2]].x) + (noeud[element[zi+1].extremite[1]].y-noeud[element[zi+1].extremite[2]].y)*(noeud[element[zi+1].extremite[1]].y-noeud[element[zi+1].extremite[2]].y) + (noeud[element[zi+1].extremite[1]].z-noeud[element[zi+1].extremite[2]].z)*(noeud[element[zi+1].extremite[1]].z-noeud[element[zi+1].extremite[2]].z));
					double longueur_rangee_haute=sqrt((noeud[element[zi+3].extremite[1]].x-noeud[element[zi+3].extremite[2]].x)*(noeud[element[zi+3].extremite[1]].x-noeud[element[zi+3].extremite[2]].x) + (noeud[element[zi+3].extremite[1]].y-noeud[element[zi+3].extremite[2]].y)*(noeud[element[zi+3].extremite[1]].y-noeud[element[zi+3].extremite[2]].y) + (noeud[element[zi+3].extremite[1]].z-noeud[element[zi+3].extremite[2]].z)*(noeud[element[zi+3].extremite[1]].z-noeud[element[zi+3].extremite[2]].z));


					double volume_imerge1;
					double masse1;
					double trainee_totale1;
					double volume_imerge2;
					double masse2;
					double trainee_totale2;

					element[zi+4].raideur_compression = 5000000;
					element[zi+4].raideur_traction = 5000000;


					if (immersion ==0)
						{
						volume_imerge1 =(PI*diametre_pehd*diametre_pehd/4*Structure.add_cage_nsegment)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux);
						masse1 = PI/4*Structure.add_cage_nsegment*rho_pehd*(diametre_pehd*diametre_pehd -(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd))*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
					 	trainee_totale1 = diametre_pehd*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux) * Structure.add_cage_nsegment;

						element[zi+4].diametrehydro=sqrt(volume_imerge1/(PI*hauteur_pieds*Structure.add_cage_nsegment/4));
						element[zi+4].rhoelement=masse1/(hauteur_pieds*PI*element[zi+4].diametrehydro*element[zi+4].diametrehydro*Structure.add_cage_nsegment/4);

						double trainee_inter = element[zi+4].diametrehydro*hauteur_pieds*Structure.add_cage_nsegment;

						element[zi+4].cdnormal=coeff_trainee_inter*trainee_totale1/trainee_inter;
						}

					if (immersion ==1)
						{

						volume_imerge2 =(PI*diametre_pehd*diametre_pehd/4*Structure.add_cage_nsegment)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
						masse2 = PI/4*Structure.add_cage_nsegment*rho_pehd*(diametre_pehd*diametre_pehd -(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd))*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute)+PI/4*Structure.add_cage_nsegment*RHO*(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
						trainee_totale2 = diametre_pehd*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute) * Structure.add_cage_nsegment;
	
						element[zi+4].diametrehydro=sqrt(volume_imerge2/(PI*hauteur_pieds*Structure.add_cage_nsegment/4));
						element[zi+4].rhoelement=masse2/(hauteur_pieds*PI*element[zi+4].diametrehydro*element[zi+4].diametrehydro*Structure.add_cage_nsegment/4);

						double trainee_inter = element[zi+4].diametrehydro*hauteur_pieds*Structure.add_cage_nsegment;

						element[zi+4].cdnormal=coeff_trainee_inter*trainee_totale2/trainee_inter;
						}


					element[zi+6].raideur_traction=100000000;
					element[zi+6].raideur_compression=100000000;
					}

				/*calcul longueur repos*/

				nb_tot_elem += 8*Structure.add_cage_nsegment;

				for (zi=nb_ele_depart;zi<=nb_tot_elem;zi++)
					{
					element[zi].lgrepos=sqrt((noeud[element[zi].extremite[1]].x-noeud[element[zi].extremite[2]].x)*(noeud[element[zi].extremite[1]].x-noeud[element[zi].extremite[2]].x) + (noeud[element[zi].extremite[1]].y-noeud[element[zi].extremite[2]].y)*(noeud[element[zi].extremite[1]].y-noeud[element[zi].extremite[2]].y) + (noeud[element[zi].extremite[1]].z-noeud[element[zi].extremite[2]].z)*(noeud[element[zi].extremite[1]].z-noeud[element[zi].extremite[2]].z));
					}

				elem_inter += 8*Structure.add_cage_nsegment;
				nb_ele_depart += 8*Structure.add_cage_nsegment;
				nb_elem_cage += 8*Structure.add_cage_nsegment;

				}



/**********************************************************************************************************************/
/**********************************************************************************************************************/

			if (strcmp(chaine,"add_chapeau") == 0)
				{

				/*reading of the center of rotation (xo,yo in m) */
				Structure.add_number_cage=Structure.add_number_cage+1;
				itmp = fscanf(fic,"%lf",&Structure.add_cage_diam);
				itmp = fscanf(fic,"%lf",&Structure.add_cage_xxo);
				itmp = fscanf(fic,"%lf",&Structure.add_cage_yyo);
				itmp = fscanf(fic,"%d",&Structure.add_cage_nsegment);
				itmp = fscanf(fic,"%lf",&Structure.add_cage_dist_ann);
				itmp = fscanf(fic,"%lf",&Structure.add_cage_haut_ann);
				itmp = fscanf(fic,"%lf",&Structure.add_hauteur_filet_elev);
				itmp = fscanf(fic,"%lf",&Structure.add_taille_maille_elev);
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
				printf("cage of %lf diametre centre x %lf y %lf nombre de segment %d \n",Structure.add_cage_diam,Structure.add_cage_xxo,Structure.add_cage_yyo,Structure.add_cage_nsegment);


				/* définition des paramètres*/

				double hauteur_pieds = Structure.add_cage_haut_ann;
				double distance_anneaux = Structure.add_cage_dist_ann;

				double coeff_trainee_inter = 1.2;	/* coefficient de trainée des barres de la cage*/

				double pronf_niveau_bas = 0;		/* profondeur des barres du niveau bas (sous phobos)*/
				double pronf_niveau_haut = pronf_niveau_bas + Structure.add_cage_haut_ann;		/* profondeur des barres du niveau haut (sous phobos)*/


				/*			PANNEAU			*/

				nb_tot_pan_elev += (Structure.add_cage_nsegment + 2);

				pan_inter = pan_inter+1;

				double nb_maille_diametre = Structure.add_cage_diam/(Structure.add_taille_maille_elev*sqrt(2));

				/* PANNEAU FOND ET HAUT*/
					
				panneau[pan_inter_fond].longueur_repos = Structure.add_taille_maille_elev;
				panneau[pan_inter_fond+1].longueur_repos = Structure.add_taille_maille_elev;


				/*	printf("%lf %lf \n%",noeud[panneau[pan_inter_fond].noeud_contour[1]].U,noeud[panneau[pan_inter_fond].noeud_contour[1]].V);*/
							
				for (no=1;no<=Structure.add_cage_nsegment;no++)
					{

					xxp = Structure.add_cage_xxo - Structure.add_cage_diam/2*cos(2*PI*(no-1)/Structure.add_cage_nsegment);
					yyp = Structure.add_cage_yyo - Structure.add_cage_diam/2*sin(2*PI*(no-1)/Structure.add_cage_nsegment);

					noeud[panneau[pan_inter_fond].noeud_contour[no]].x = xxp;
					noeud[panneau[pan_inter_fond].noeud_contour[no]].y = yyp;
					noeud[panneau[pan_inter_fond].noeud_contour[no]].z = - Structure.add_hauteur_filet_elev + pronf_niveau_bas;

					noeud[panneau[pan_inter_fond+1].noeud_contour[no]].x = xxp;
					noeud[panneau[pan_inter_fond+1].noeud_contour[no]].y = yyp;
					noeud[panneau[pan_inter_fond+1].noeud_contour[no]].z = pronf_niveau_bas;
					}

				/*calcul minx maxx miny maxy*/

				double minx = Structure.add_cage_xxo;
				double maxx = Structure.add_cage_xxo;

				for (no=1;no<=panneau[pan_inter_fond].nb_noeud_contour;no++)
					{
					if (noeud[panneau[pan_inter_fond].noeud_contour[no]].x < minx) minx =noeud[panneau[pan_inter_fond].noeud_contour[no]].x;
					if (noeud[panneau[pan_inter_fond].noeud_contour[no]].x > maxx) maxx =noeud[panneau[pan_inter_fond].noeud_contour[no]].x;
					}

				double ecartx = maxx - minx;
				double ratio = nb_maille_diametre/ ecartx;
											

				/*calcul vecteur*/
	
				for (no=1;no<=panneau[pan_inter_fond].nb_noeud_contour;no++)
					{
					noeud[panneau[pan_inter_fond].noeud_contour[no]].U =(noeud[panneau[pan_inter_fond].noeud_contour[no]].x - Structure.add_cage_xxo)*ratio ;
					noeud[panneau[pan_inter_fond].noeud_contour[no]].V =(noeud[panneau[pan_inter_fond].noeud_contour[no]].y - Structure.add_cage_yyo)*ratio ;

					noeud[panneau[pan_inter_fond].noeud_contour[no]].u =  noeud[panneau[pan_inter_fond].noeud_contour[no]].U + noeud[panneau[pan_inter_fond].noeud_contour[no]].V; 
					noeud[panneau[pan_inter_fond].noeud_contour[no]].v = -noeud[panneau[pan_inter_fond].noeud_contour[no]].U + noeud[panneau[pan_inter_fond].noeud_contour[no]].V; 
					}

				for (no=1;no<=panneau[pan_inter_fond+1].nb_noeud_contour;no++)
					{
					noeud[panneau[pan_inter_fond+1].noeud_contour[no]].U =(noeud[panneau[pan_inter_fond+1].noeud_contour[no]].x - Structure.add_cage_xxo)*ratio ;
					noeud[panneau[pan_inter_fond+1].noeud_contour[no]].V = -(noeud[panneau[pan_inter_fond+1].noeud_contour[no]].y - Structure.add_cage_yyo)*ratio ;

					noeud[panneau[pan_inter_fond+1].noeud_contour[no]].u =  noeud[panneau[pan_inter_fond+1].noeud_contour[no]].U + noeud[panneau[pan_inter_fond+1].noeud_contour[no]].V; 
					noeud[panneau[pan_inter_fond+1].noeud_contour[no]].v = -noeud[panneau[pan_inter_fond+1].noeud_contour[no]].U + noeud[panneau[pan_inter_fond+1].noeud_contour[no]].V; 
					}




				/* PANNEAUX LATERAUX */

				for (zi=pan_inter;zi<=pan_inter + Structure.add_cage_nsegment-1;zi++)	
					{

					/*noeud 1*/
					xxp1 = (float) Structure.add_cage_xxo - Structure.add_cage_diam/2*cos(2*PI*(zi-pan_inter)/Structure.add_cage_nsegment);
					yyp1 = (float) Structure.add_cage_yyo - Structure.add_cage_diam/2*sin(2*PI*(zi-pan_inter)/Structure.add_cage_nsegment);
					/*noeud 3*/
					xxp3 = (float) Structure.add_cage_xxo - Structure.add_cage_diam/2*cos(2*PI*(zi-pan_inter+1)/Structure.add_cage_nsegment);
					yyp3 = (float) Structure.add_cage_yyo - Structure.add_cage_diam/2*sin(2*PI*(zi-pan_inter+1)/Structure.add_cage_nsegment);
					
					noeud[panneau[zi].noeud_contour[1]].x = xxp1;
					noeud[panneau[zi].noeud_contour[1]].y = yyp1;
					noeud[panneau[zi].noeud_contour[1]].z = - Structure.add_hauteur_filet_elev + pronf_niveau_bas;

					noeud[panneau[zi].noeud_contour[2]].x = xxp1;
					noeud[panneau[zi].noeud_contour[2]].y = yyp1;
					noeud[panneau[zi].noeud_contour[2]].z = pronf_niveau_bas;

					noeud[panneau[zi].noeud_contour[3]].x = xxp3;
					noeud[panneau[zi].noeud_contour[3]].y = yyp3;
					noeud[panneau[zi].noeud_contour[3]].z = pronf_niveau_bas;

					noeud[panneau[zi].noeud_contour[4]].x = xxp3;
					noeud[panneau[zi].noeud_contour[4]].y = yyp3;
					noeud[panneau[zi].noeud_contour[4]].z = - Structure.add_hauteur_filet_elev + pronf_niveau_bas;

					panneau[zi].longueur_repos = Structure.add_taille_maille_elev;

					noeud[panneau[zi].noeud_contour[1]].U = 0;
					noeud[panneau[zi].noeud_contour[1]].V = 0;
					noeud[panneau[zi].noeud_contour[2]].U = 0;
					noeud[panneau[zi].noeud_contour[2]].V = -floor((Structure.add_hauteur_filet_elev) / (Structure.add_taille_maille_elev * sqrt(2)));
					noeud[panneau[zi].noeud_contour[3]].U = floor(Structure.add_cage_diam * PI/Structure.add_cage_nsegment / (Structure.add_taille_maille_elev * sqrt(2)));
					noeud[panneau[zi].noeud_contour[3]].V = -floor((Structure.add_hauteur_filet_elev) / (Structure.add_taille_maille_elev * sqrt(2)));
					noeud[panneau[zi].noeud_contour[4]].U = floor(Structure.add_cage_diam * PI/Structure.add_cage_nsegment / (Structure.add_taille_maille_elev * sqrt(2)));
					noeud[panneau[zi].noeud_contour[4]].V = 0;

					for (no=1;no<=4;no++)
						{
						noeud[panneau[zi].noeud_contour[no]].u =  noeud[panneau[zi].noeud_contour[no]].U + noeud[panneau[zi].noeud_contour[no]].V; 
						noeud[panneau[zi].noeud_contour[no]].v = -noeud[panneau[zi].noeud_contour[no]].U + noeud[panneau[zi].noeud_contour[no]].V; 
						}
					/*	printf("%lf %lf \n%lf %lf \n %lf %lf \n%lf %lf\n",noeud[panneau[zi].noeud_contour[1]].U,noeud[panneau[zi].noeud_contour[1]].V,noeud[panneau[zi].noeud_contour[2]].U,noeud[panneau[zi].noeud_contour[2]].V,noeud[panneau[zi].noeud_contour[3]].U,noeud[panneau[zi].noeud_contour[3]].V,noeud[panneau[zi].noeud_contour[4]].U,noeud[panneau[zi].noeud_contour[4]].V);*/					

					}


				if (immersion == 0)
				{
					panneau[pan_inter_fond+1].flag_dessin = 0;
				}

				pan_inter_fond += Structure.add_cage_nsegment+2;
				pan_inter += Structure.add_cage_nsegment+1;




				/* 		ELEMENT 	*/



				for (zi=elem_inter;zi<=elem_inter+8*Structure.add_cage_nsegment-1;zi=zi+8)
					{
					int fl = floor((zi-elem_inter)/8);

					xxp11 = (float) Structure.add_cage_xxo - Structure.add_cage_diam/2*cos(2*PI*fl/Structure.add_cage_nsegment);
					yyp11 = (float) Structure.add_cage_yyo - Structure.add_cage_diam/2*sin(2*PI*fl/Structure.add_cage_nsegment);
					xxp12 = (float) Structure.add_cage_xxo - Structure.add_cage_diam/2*cos(2*PI*(fl+1)/Structure.add_cage_nsegment);
					yyp12 = (float) Structure.add_cage_yyo - Structure.add_cage_diam/2*sin(2*PI*(fl+1)/Structure.add_cage_nsegment);
					
					xxp21 = (float) Structure.add_cage_xxo - (Structure.add_cage_diam/2+distance_anneaux)*cos(2*PI*fl/Structure.add_cage_nsegment);
					yyp21 = (float) Structure.add_cage_yyo - (Structure.add_cage_diam/2+distance_anneaux)*sin(2*PI*fl/Structure.add_cage_nsegment);
					xxp22 = (float) Structure.add_cage_xxo - (Structure.add_cage_diam/2+distance_anneaux)*cos(2*PI*(fl+1)/Structure.add_cage_nsegment);
					yyp22 = (float) Structure.add_cage_yyo - (Structure.add_cage_diam/2+distance_anneaux)*sin(2*PI*(fl+1)/Structure.add_cage_nsegment);
					
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

					noeud[element[zi+0].extremite[1]].x = xxp11;
					noeud[element[zi+0].extremite[1]].y = yyp11;
					noeud[element[zi+0].extremite[1]].z = pronf_niveau_bas;

					noeud[element[zi+0].extremite[2]].x = xxp12;
					noeud[element[zi+0].extremite[2]].y = yyp12;
					noeud[element[zi+0].extremite[2]].z = pronf_niveau_bas;

					noeud[element[zi+1].extremite[1]].x = xxp21;
					noeud[element[zi+1].extremite[1]].y = yyp21;
					noeud[element[zi+1].extremite[1]].z = pronf_niveau_bas;

					noeud[element[zi+1].extremite[2]].x = xxp22;
					noeud[element[zi+1].extremite[2]].y = yyp22;
					noeud[element[zi+1].extremite[2]].z = pronf_niveau_bas;

					noeud[element[zi+2].extremite[1]].x = xxp31;
					noeud[element[zi+2].extremite[1]].y = yyp31;
					noeud[element[zi+2].extremite[1]].z = pronf_niveau_bas;

					noeud[element[zi+2].extremite[2]].x = xxp32;
					noeud[element[zi+2].extremite[2]].y = yyp32;
					noeud[element[zi+2].extremite[2]].z = pronf_niveau_bas;

					noeud[element[zi+3].extremite[1]].x = xxp41;
					noeud[element[zi+3].extremite[1]].y = yyp41;
					noeud[element[zi+3].extremite[1]].z = pronf_niveau_haut;

					noeud[element[zi+3].extremite[2]].x = xxp42;
					noeud[element[zi+3].extremite[2]].y = yyp42;
					noeud[element[zi+3].extremite[2]].z = pronf_niveau_haut;

					noeud[element[zi+4].extremite[1]].x = xxp51;
					noeud[element[zi+4].extremite[1]].y = yyp51;
					noeud[element[zi+4].extremite[1]].z = pronf_niveau_haut;

					noeud[element[zi+4].extremite[2]].x = xxp52;
					noeud[element[zi+4].extremite[2]].y = yyp52;
					noeud[element[zi+4].extremite[2]].z = pronf_niveau_bas;


					noeud[element[zi+5].extremite[1]].x = xxp61;
					noeud[element[zi+5].extremite[1]].y = yyp61;
					noeud[element[zi+5].extremite[1]].z = pronf_niveau_haut;

					noeud[element[zi+5].extremite[2]].x = xxp62;
					noeud[element[zi+5].extremite[2]].y = yyp62;
					noeud[element[zi+5].extremite[2]].z = pronf_niveau_bas;

					noeud[element[zi+6].extremite[1]].x = xxp71;
					noeud[element[zi+6].extremite[1]].y = yyp71;
					noeud[element[zi+6].extremite[1]].z = pronf_niveau_bas;

					noeud[element[zi+6].extremite[2]].x = xxp72;
					noeud[element[zi+6].extremite[2]].y = yyp72;
					noeud[element[zi+6].extremite[2]].z = pronf_niveau_bas;

					noeud[element[zi+7].extremite[1]].x = xxp81;
					noeud[element[zi+7].extremite[1]].y = yyp81;
					noeud[element[zi+7].extremite[1]].z = pronf_niveau_bas;

					noeud[element[zi+7].extremite[2]].x = xxp82;
					noeud[element[zi+7].extremite[2]].y = yyp82;
					noeud[element[zi+7].extremite[2]].z = pronf_niveau_haut;


					/* Calcul Coeff trainée + diametre + masse volumique pieds */



				
				/*if (immersion ==0)
					{
					element[zi+0].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					element[zi+1].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					element[zi+2].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					element[zi+3].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					element[zi+4].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4);
					}*/

					if (immersion ==1)
						{
						element[zi+0].diametrehydro = diametre_pehd;
						element[zi+0].raideur_compression = 5000000;
						element[zi+0].raideur_traction = 5000000;
	
						element[zi+1].diametrehydro = diametre_pehd;
						element[zi+1].raideur_compression = 5000000;
						element[zi+1].raideur_traction = 5000000;

						element[zi+2].diametrehydro = diametre_pehd;
						element[zi+2].raideur_compression = 5000000;
						element[zi+2].raideur_traction = 5000000;
		
						element[zi+3].diametrehydro = diametre_pehd;
						element[zi+3].raideur_compression = 5000000;
						element[zi+3].raideur_traction = 5000000;
				
						element[zi+4].diametrehydro = diametre_pehd;
						element[zi+4].raideur_compression = 5000000;
						element[zi+4].raideur_traction = 5000000;

						element[zi+5].diametrehydro = 0;	
						element[zi+6].diametrehydro = 0;
						element[zi+7].diametrehydro = 0;

						element[zi+0].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
						element[zi+1].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
						element[zi+2].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
						element[zi+3].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);
						element[zi+4].rhoelement=rho_pehd*(diametre_pehd*diametre_pehd/4-(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd))/(diametre_pehd*diametre_pehd/4)+RHO*(diametre_pehd/2-epaisseur_pehd)*(diametre_pehd/2-epaisseur_pehd)/(diametre_pehd*diametre_pehd/4);

						element[zi+0].cdnormal = coeff_trainee_inter;				
						element[zi+1].cdnormal = coeff_trainee_inter;
						element[zi+2].cdnormal = coeff_trainee_inter;
						element[zi+3].cdnormal = coeff_trainee_inter;
						element[zi+4].cdnormal = coeff_trainee_inter;
						}


					if (immersion ==0)
						{
						double longueur_premiere_rangee=sqrt((noeud[element[zi+0].extremite[1]].x-noeud[element[zi+0].extremite[2]].x)*(noeud[element[zi+0].extremite[1]].x-noeud[element[zi+0].extremite[2]].x) + (noeud[element[zi+0].extremite[1]].y-noeud[element[zi+0].extremite[2]].y)*(noeud[element[zi+0].extremite[1]].y-noeud[element[zi+0].extremite[2]].y) + (noeud[element[zi+0].extremite[1]].z-noeud[element[zi+0].extremite[2]].z)*(noeud[element[zi+0].extremite[1]].z-noeud[element[zi+0].extremite[2]].z));
						double longueur_deuxieme_rangee=sqrt((noeud[element[zi+1].extremite[1]].x-noeud[element[zi+1].extremite[2]].x)*(noeud[element[zi+1].extremite[1]].x-noeud[element[zi+1].extremite[2]].x) + (noeud[element[zi+1].extremite[1]].y-noeud[element[zi+1].extremite[2]].y)*(noeud[element[zi+1].extremite[1]].y-noeud[element[zi+1].extremite[2]].y) + (noeud[element[zi+1].extremite[1]].z-noeud[element[zi+1].extremite[2]].z)*(noeud[element[zi+1].extremite[1]].z-noeud[element[zi+1].extremite[2]].z));
						double longueur_rangee_haute=sqrt((noeud[element[zi+3].extremite[1]].x-noeud[element[zi+3].extremite[2]].x)*(noeud[element[zi+3].extremite[1]].x-noeud[element[zi+3].extremite[2]].x) + (noeud[element[zi+3].extremite[1]].y-noeud[element[zi+3].extremite[2]].y)*(noeud[element[zi+3].extremite[1]].y-noeud[element[zi+3].extremite[2]].y) + (noeud[element[zi+3].extremite[1]].z-noeud[element[zi+3].extremite[2]].z)*(noeud[element[zi+3].extremite[1]].z-noeud[element[zi+3].extremite[2]].z));

	
						double volume_imerge1;
						double masse1;
						double trainee_totale1;
						double volume_imerge2;
						double masse2;
						double trainee_totale2;

						volume_imerge1 =(PI*diametre_pehd*diametre_pehd/4*Structure.add_cage_nsegment)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux);
						masse1 = PI/4*Structure.add_cage_nsegment*rho_pehd*(diametre_pehd*diametre_pehd -(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd))*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
					 	trainee_totale1 = diametre_pehd*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux) * Structure.add_cage_nsegment;

						element[zi+4].diametrehydro=sqrt(volume_imerge1/(PI*hauteur_pieds*Structure.add_cage_nsegment/4));
						element[zi+4].rhoelement=masse1/(hauteur_pieds*PI*element[zi+4].diametrehydro*element[zi+4].diametrehydro*Structure.add_cage_nsegment/4);

						double trainee_inter = element[zi+4].diametrehydro*hauteur_pieds*Structure.add_cage_nsegment;

						element[zi+4].cdnormal=coeff_trainee_inter*trainee_totale1/trainee_inter;
						}


					/*if (immersion ==1)
						{

						volume_imerge2 =(PI*diametre_pehd*diametre_pehd/4*Structure.add_cage_nsegment)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
						masse2 = PI/4*Structure.add_cage_nsegment*rho_pehd*(diametre_pehd*diametre_pehd -(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd))*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute)+PI/4*Structure.add_cage_nsegment*RHO*(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd)*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute);
						trainee_totale2 = diametre_pehd*(longueur_premiere_rangee + longueur_deuxieme_rangee+hauteur_pieds+distance_anneaux+longueur_rangee_haute) * Structure.add_cage_nsegment;
	
						element[zi+4].diametrehydro=sqrt(volume_imerge2/(PI*hauteur_pieds*Structure.add_cage_nsegment/4));
						element[zi+4].rhoelement=masse2/(hauteur_pieds*PI*element[zi+4].diametrehydro*element[zi+4].diametrehydro*Structure.add_cage_nsegment/4);

						double trainee_inter = element[zi+4].diametrehydro*hauteur_pieds*Structure.add_cage_nsegment;

						element[zi+4].cdnormal=coeff_trainee_inter*trainee_totale2/trainee_inter;
						}*/


					element[zi+6].flag_dessin=0;
					element[zi+7].flag_dessin=0;

					element[zi+6].raideur_traction=100000000;
					element[zi+6].raideur_compression=100000000;
					}

				/*calcul longueur repos*/

				nb_tot_elem += 8*Structure.add_cage_nsegment;

				for (zi=nb_ele_depart;zi<=nb_tot_elem;zi++)
					{
					element[zi].lgrepos=sqrt((noeud[element[zi].extremite[1]].x-noeud[element[zi].extremite[2]].x)*(noeud[element[zi].extremite[1]].x-noeud[element[zi].extremite[2]].x) + (noeud[element[zi].extremite[1]].y-noeud[element[zi].extremite[2]].y)*(noeud[element[zi].extremite[1]].y-noeud[element[zi].extremite[2]].y) + (noeud[element[zi].extremite[1]].z-noeud[element[zi].extremite[2]].z)*(noeud[element[zi].extremite[1]].z-noeud[element[zi].extremite[2]].z));
					}

				elem_inter += 8*Structure.add_cage_nsegment;
				nb_ele_depart += 8*Structure.add_cage_nsegment;
				nb_elem_cage += 8*Structure.add_cage_nsegment;

				}

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
			if (strcmp(chaine,"add_filet_pred") == 0)
				{
				itmp = fscanf(fic,"%lf",&Structure.add_filet_pred_diam);
				itmp = fscanf(fic,"%lf",&Structure.add_diam_lest);
				itmp = fscanf(fic,"%lf",&Structure.add_filet_pred_xxo);
				itmp = fscanf(fic,"%lf",&Structure.add_filet_pred_yyo);
				itmp = fscanf(fic,"%d",&Structure.add_filet_pred_nsegment);
				itmp = fscanf(fic,"%lf",&Structure.add_cage_dist_ann);
				itmp = fscanf(fic,"%lf",&Structure.add_hauteur_filet_pred);
				itmp = fscanf(fic,"%lf",&Structure.add_taille_maille_pred);
				itmp = fscanf(fic,"%lf",&diametre_pehd);
				itmp = fscanf(fic,"%lf",&epaisseur_pehd);
				itmp = fscanf(fic,"%lf",&rho_pehd);

				pan_inter_pred_fond = nb_tot_pan_elev+1;
				pan_inter_pred = pan_inter_pred_fond+1;
				printf("pan_inter_pred_fond = %d\n",pan_inter_pred_fond);

				double pronf_niveau_bas = 0;		/* profondeur des barres du niveau bas (sous phobos)*/
				

				/*			PANNEAU			*/

				nb_tot_pan_elev += (Structure.add_filet_pred_nsegment + 1);

				double nb_maille_diametre = Structure.add_diam_lest/(Structure.add_taille_maille_pred*sqrt(2));

				/* PANNEAU FOND*/
					
				panneau[pan_inter_pred_fond].longueur_repos = Structure.add_taille_maille_pred;


				/*	printf("%lf %lf \n%",noeud[panneau[pan_inter_pred_fond].noeud_contour[1]].U,noeud[panneau[pan_inter_pred_fond].noeud_contour[1]].V);*/
							
				for (no=1;no<=Structure.add_filet_pred_nsegment;no++)
					{

					xxp = Structure.add_filet_pred_xxo - (Structure.add_diam_lest)/2*cos(2*PI*(no-1)/Structure.add_filet_pred_nsegment);
					yyp = Structure.add_filet_pred_yyo - (Structure.add_diam_lest)/2*sin(2*PI*(no-1)/Structure.add_filet_pred_nsegment);

					noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].x = xxp;
					noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].y = yyp;
					noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].z = - Structure.add_hauteur_filet_pred + pronf_niveau_bas;
					}

				/*calcul minx maxx miny maxy*/

				double minx = Structure.add_filet_pred_xxo;
				double maxx = Structure.add_filet_pred_xxo;

				for (no=1;no<=panneau[pan_inter_pred_fond].nb_noeud_contour;no++)
					{
					if (noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].x < minx) minx =noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].x;
					if (noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].x > maxx) maxx =noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].x;
					}

				double ecartx = maxx - minx;
				double ratio = nb_maille_diametre/ ecartx;
											

				/*calcul vecteur*/
	
				for (no=1;no<=panneau[pan_inter_pred_fond].nb_noeud_contour;no++)
					{
					noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].U =(noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].x - Structure.add_cage_xxo)*ratio ;
					noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].V =(noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].y - Structure.add_cage_yyo)*ratio ;

					noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].u =  noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].U + noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].V; 
					noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].v = -noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].U + noeud[panneau[pan_inter_pred_fond].noeud_contour[no]].V; 
					}


				/* PANNEAUX LATERAUX */

				for (zi=pan_inter_pred;zi<=pan_inter_pred + Structure.add_filet_pred_nsegment-1;zi++)	
					{

					/*noeud 1*/
					xxp1 = (float) Structure.add_filet_pred_xxo - Structure.add_diam_lest/2*cos(2*PI*(zi-pan_inter_pred)/Structure.add_filet_pred_nsegment);
					yyp1 = (float) Structure.add_filet_pred_yyo - Structure.add_diam_lest/2*sin(2*PI*(zi-pan_inter_pred)/Structure.add_filet_pred_nsegment);

					/*noeud 2*/
					xxp2 = (float) Structure.add_filet_pred_xxo - Structure.add_filet_pred_diam/2*cos(2*PI*(zi-pan_inter_pred)/Structure.add_filet_pred_nsegment);
					yyp2 = (float) Structure.add_filet_pred_yyo - Structure.add_filet_pred_diam/2*sin(2*PI*(zi-pan_inter_pred)/Structure.add_filet_pred_nsegment);

					/*noeud 3*/
					xxp3 = (float) Structure.add_filet_pred_xxo - Structure.add_filet_pred_diam/2*cos(2*PI*(zi-pan_inter_pred+1)/Structure.add_filet_pred_nsegment);
					yyp3 = (float) Structure.add_filet_pred_yyo - Structure.add_filet_pred_diam/2*sin(2*PI*(zi-pan_inter_pred+1)/Structure.add_filet_pred_nsegment);

					/*noeud 4*/
					xxp4 = (float) Structure.add_filet_pred_xxo - Structure.add_diam_lest/2*cos(2*PI*(zi-pan_inter_pred+1)/Structure.add_filet_pred_nsegment);
					yyp4 = (float) Structure.add_filet_pred_yyo - Structure.add_diam_lest/2*sin(2*PI*(zi-pan_inter_pred+1)/Structure.add_filet_pred_nsegment);


					
					noeud[panneau[zi].noeud_contour[1]].x = xxp1;
					noeud[panneau[zi].noeud_contour[1]].y = yyp1;
					noeud[panneau[zi].noeud_contour[1]].z = - Structure.add_hauteur_filet_pred + pronf_niveau_bas;

					noeud[panneau[zi].noeud_contour[2]].x = xxp2;
					noeud[panneau[zi].noeud_contour[2]].y = yyp2;
					noeud[panneau[zi].noeud_contour[2]].z = pronf_niveau_bas;

					noeud[panneau[zi].noeud_contour[3]].x = xxp3;
					noeud[panneau[zi].noeud_contour[3]].y = yyp3;
					noeud[panneau[zi].noeud_contour[3]].z = pronf_niveau_bas;

					noeud[panneau[zi].noeud_contour[4]].x = xxp4;
					noeud[panneau[zi].noeud_contour[4]].y = yyp4;
					noeud[panneau[zi].noeud_contour[4]].z = - Structure.add_hauteur_filet_pred + pronf_niveau_bas;

					panneau[zi].longueur_repos = Structure.add_taille_maille_pred;

					noeud[panneau[zi].noeud_contour[1]].U = 0;
					noeud[panneau[zi].noeud_contour[1]].V = 0;
					noeud[panneau[zi].noeud_contour[2]].U = 0;
					noeud[panneau[zi].noeud_contour[2]].V = -ceil(sqrt(((Structure.add_hauteur_filet_pred) / (Structure.add_taille_maille_pred * sqrt(2)))*((Structure.add_hauteur_filet_pred) / (Structure.add_taille_maille_pred * sqrt(2)))+((Structure.add_diam_lest/2-Structure.add_filet_pred_diam/2)/(Structure.add_taille_maille_pred * sqrt(2)))*((Structure.add_diam_lest/2-Structure.add_filet_pred_diam/2)/(Structure.add_taille_maille_pred * sqrt(2)))));
					noeud[panneau[zi].noeud_contour[3]].U = ceil((Structure.add_filet_pred_diam*PI/Structure.add_filet_pred_nsegment) / (Structure.add_taille_maille_pred * sqrt(2)));
					noeud[panneau[zi].noeud_contour[3]].V = -ceil(sqrt(((Structure.add_hauteur_filet_pred) / (Structure.add_taille_maille_pred * sqrt(2)))*((Structure.add_hauteur_filet_pred) / (Structure.add_taille_maille_pred * sqrt(2)))+((Structure.add_diam_lest/2-Structure.add_filet_pred_diam/2)/(Structure.add_taille_maille_pred * sqrt(2)))*((Structure.add_diam_lest/2-Structure.add_filet_pred_diam/2)/(Structure.add_taille_maille_pred * sqrt(2)))));
					noeud[panneau[zi].noeud_contour[4]].U = ceil((Structure.add_diam_lest*PI/Structure.add_filet_pred_nsegment) / (Structure.add_taille_maille_pred * sqrt(2)));
					noeud[panneau[zi].noeud_contour[4]].V = 0;

					for (no=1;no<=4;no++)
						{
						noeud[panneau[zi].noeud_contour[no]].u =  noeud[panneau[zi].noeud_contour[no]].U + noeud[panneau[zi].noeud_contour[no]].V; 
						noeud[panneau[zi].noeud_contour[no]].v = -noeud[panneau[zi].noeud_contour[no]].U + noeud[panneau[zi].noeud_contour[no]].V; 
						}
					/*	printf("%lf %lf \n%lf %lf \n %lf %lf \n%lf %lf\n",noeud[panneau[zi].noeud_contour[1]].U,noeud[panneau[zi].noeud_contour[1]].V,noeud[panneau[zi].noeud_contour[2]].U,noeud[panneau[zi].noeud_contour[2]].V,noeud[panneau[zi].noeud_contour[3]].U,noeud[panneau[zi].noeud_contour[3]].V,noeud[panneau[zi].noeud_contour[4]].U,noeud[panneau[zi].noeud_contour[4]].V);*/					

					}

				pan_inter_pred_fond += Structure.add_filet_pred_nsegment+1;
				pan_inter_pred += Structure.add_filet_pred_nsegment+1;



				/* 		ELEMENT 	*/

				ele_inter_pred = nb_tot_elem +1;

				double longueur_contour_filet_pred;
				double volume_contour_pred;
				double masse_contour_pred;

				for (zi=ele_inter_pred;zi<=ele_inter_pred+4*Structure.add_filet_pred_nsegment-1;zi=zi+4)
					{
					int fl = floor((zi-ele_inter_pred)/4);

					xxp11 = (float) Structure.add_filet_pred_xxo - Structure.add_diam_lest/2*cos(2*PI*fl/Structure.add_filet_pred_nsegment);
					yyp11 = (float) Structure.add_filet_pred_yyo - Structure.add_diam_lest/2*sin(2*PI*fl/Structure.add_filet_pred_nsegment);
					xxp12 = (float) Structure.add_filet_pred_xxo - Structure.add_diam_lest/2*cos(2*PI*(fl+1)/Structure.add_filet_pred_nsegment);
					yyp12 = (float) Structure.add_filet_pred_yyo - Structure.add_diam_lest/2*sin(2*PI*(fl+1)/Structure.add_filet_pred_nsegment);
					
					xxp21 = xxp11;
					yyp21 = yyp11;
					xxp22 = (float) Structure.add_filet_pred_xxo - Structure.add_diam_lest/2*cos(2*PI*(fl+2)/Structure.add_filet_pred_nsegment);
					yyp22 = (float) Structure.add_filet_pred_yyo - Structure.add_diam_lest/2*sin(2*PI*(fl+2)/Structure.add_filet_pred_nsegment);
					
					xxp31 = xxp11;
					yyp31 = yyp11;
					xxp32 = Structure.add_filet_pred_xxo - Structure.add_filet_pred_diam/2*cos(2*PI*fl/Structure.add_filet_pred_nsegment);
					yyp32 = Structure.add_filet_pred_yyo - Structure.add_filet_pred_diam/2*sin(2*PI*fl/Structure.add_filet_pred_nsegment);
					
					xxp41 = xxp11;
					yyp41 = yyp11;
					xxp42 = (float) (Structure.add_filet_pred_xxo - ((Structure.add_diam_lest)/2-Structure.add_cage_dist_ann-(Structure.add_diam_lest/2-Structure.add_filet_pred_diam/2)) * cos(2 * PI*fl/Structure.add_filet_pred_nsegment));
					yyp42 = (float) (Structure.add_filet_pred_yyo - ((Structure.add_diam_lest)/2-Structure.add_cage_dist_ann-(Structure.add_diam_lest/2-Structure.add_filet_pred_diam/2)) * sin(2 * PI*fl/Structure.add_filet_pred_nsegment));


					noeud[element[zi+0].extremite[1]].x = xxp11;
					noeud[element[zi+0].extremite[1]].y = yyp11;
					noeud[element[zi+0].extremite[1]].z = - Structure.add_hauteur_filet_pred + pronf_niveau_bas;

					noeud[element[zi+0].extremite[2]].x = xxp12;
					noeud[element[zi+0].extremite[2]].y = yyp12;
					noeud[element[zi+0].extremite[2]].z = - Structure.add_hauteur_filet_pred + pronf_niveau_bas;

					/* calcul masse volumique */
					longueur_contour_filet_pred=sqrt((noeud[element[zi+0].extremite[1]].x-noeud[element[zi+0].extremite[2]].x)*(noeud[element[zi+0].extremite[1]].x-noeud[element[zi+0].extremite[2]].x) + (noeud[element[zi+0].extremite[1]].y-noeud[element[zi+0].extremite[2]].y)*(noeud[element[zi+0].extremite[1]].y-noeud[element[zi+0].extremite[2]].y) + (noeud[element[zi+0].extremite[1]].z-noeud[element[zi+0].extremite[2]].z)*(noeud[element[zi+0].extremite[1]].z-noeud[element[zi+0].extremite[2]].z));
					volume_contour_pred = (PI*diametre_pehd*diametre_pehd/4*Structure.add_filet_pred_nsegment)*longueur_contour_filet_pred;

					/*masse avec chaine de 20 kg par metre de lest*/
					masse_contour_pred = PI/4*Structure.add_filet_pred_nsegment*rho_pehd*(diametre_pehd*diametre_pehd -(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd))*longueur_contour_filet_pred +PI/4*Structure.add_filet_pred_nsegment*RHO*(diametre_pehd-2*epaisseur_pehd)*(diametre_pehd-2*epaisseur_pehd)*longueur_contour_filet_pred + 20*longueur_contour_filet_pred*Structure.add_filet_pred_nsegment ;


					element[zi+0].rhoelement=masse_contour_pred/volume_contour_pred;
					element[zi+0].diametrehydro = diametre_pehd;
					element[zi+0].raideur_compression = 5000000;
					element[zi+0].raideur_traction = 5000000;

					noeud[element[zi+1].extremite[1]].x = xxp21;
					noeud[element[zi+1].extremite[1]].y = yyp21;
					noeud[element[zi+1].extremite[1]].z = - Structure.add_hauteur_filet_pred + pronf_niveau_bas;

					noeud[element[zi+1].extremite[2]].x = xxp22;
					noeud[element[zi+1].extremite[2]].y = yyp22;
					noeud[element[zi+1].extremite[2]].z = - Structure.add_hauteur_filet_pred + pronf_niveau_bas;

					noeud[element[zi+2].extremite[1]].x = xxp31;
					noeud[element[zi+2].extremite[1]].y = yyp31;
					noeud[element[zi+2].extremite[1]].z = - Structure.add_hauteur_filet_pred + pronf_niveau_bas;

					noeud[element[zi+2].extremite[2]].x = xxp32;
					noeud[element[zi+2].extremite[2]].y = yyp32;
					noeud[element[zi+2].extremite[2]].z = pronf_niveau_bas;

					element[zi+2].raideur_compression = 10;
					element[zi+2].raideur_traction = 3923000;
					element[zi+2].rhoelement=955;
					element[zi+2].diametrehydro=0.044;
					element[zi+2].nb_barre=1;

					noeud[element[zi+3].extremite[1]].x=xxp41;
					noeud[element[zi+3].extremite[1]].y=yyp41;
					noeud[element[zi+3].extremite[2]].x=xxp42;
					noeud[element[zi+3].extremite[2]].y=yyp42;
					noeud[element[zi+3].extremite[1]].z = - Structure.add_hauteur_filet_pred + pronf_niveau_bas;
					noeud[element[zi+3].extremite[2]].z = - Structure.add_hauteur_filet_elev + pronf_niveau_bas;

					element[zi+3].raideur_compression = 10;
					element[zi+3].raideur_traction = 3923000;
					element[zi+3].rhoelement=955;
					element[zi+3].diametrehydro=0.044;

					}


				for (zi=ele_inter_pred;zi<=ele_inter_pred+4*Structure.add_filet_pred_nsegment;zi++)
					{
					element[zi].lgrepos=sqrt((noeud[element[zi].extremite[1]].x-noeud[element[zi].extremite[2]].x)*(noeud[element[zi].extremite[1]].x-noeud[element[zi].extremite[2]].x) + (noeud[element[zi].extremite[1]].y-noeud[element[zi].extremite[2]].y)*(noeud[element[zi].extremite[1]].y-noeud[element[zi].extremite[2]].y) + (noeud[element[zi].extremite[1]].z-noeud[element[zi].extremite[2]].z)*(noeud[element[zi].extremite[1]].z-noeud[element[zi].extremite[2]].z));
					}

				for (zi=ele_inter_pred;zi<=ele_inter_pred+4*Structure.add_filet_pred_nsegment;zi=zi+4)
					{
					element[zi+3].lgrepos=0.95*sqrt((noeud[element[zi].extremite[1]].x-noeud[element[zi].extremite[2]].x)*(noeud[element[zi].extremite[1]].x-noeud[element[zi].extremite[2]].x) + (noeud[element[zi].extremite[1]].y-noeud[element[zi].extremite[2]].y)*(noeud[element[zi].extremite[1]].y-noeud[element[zi].extremite[2]].y) + (noeud[element[zi].extremite[1]].z-noeud[element[zi].extremite[2]].z)*(noeud[element[zi].extremite[1]].z-noeud[element[zi].extremite[2]].z));
					}

				nb_tot_elem += 4*Structure.add_filet_pred_nsegment;
				nb_elem_cage += 4*Structure.add_filet_pred_nsegment;

			}


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/***************************************MODIF ARNAUD****************************************************/


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

					int kkk;
				
					for (jjj=elem_amarrage;jjj<=elem_amarrage+iii-2;jjj++)
					{
						noeud[element[jjj].extremite[1]].x=coord_noeud_x[jjj-elem_amarrage];
						noeud[element[jjj].extremite[2]].x=coord_noeud_x[jjj-elem_amarrage+1];
						noeud[element[jjj].extremite[1]].y=coord_noeud_y[jjj-elem_amarrage];
						noeud[element[jjj].extremite[2]].y=coord_noeud_y[jjj-elem_amarrage+1];

						kkk=0;
						
						while(coord_noeud_x[jjj-elem_amarrage-kkk-1]==coord_noeud_x[jjj-elem_amarrage] && coord_noeud_y[jjj-elem_amarrage-kkk-1]==coord_noeud_y[jjj-elem_amarrage] && (jjj-elem_amarrage-kkk) > 0)
						{
							kkk=kkk+1;
						}

						if (coord_noeud_x[jjj-elem_amarrage]==coord_noeud_x[jjj-elem_amarrage+1] && coord_noeud_y[jjj-elem_amarrage]==coord_noeud_y[jjj-elem_amarrage+1] && jjj-elem_amarrage-1 > 0)
						{
							noeud[element[jjj].extremite[1]].z=coord_noeud_z[jjj-elem_amarrage];
							noeud[element[jjj].extremite[2]].z=coord_noeud_z[jjj-elem_amarrage+1];
							
							noeud[element[jjj].extremite[1]].type=type_type_noeud[jjj-elem_amarrage];
							noeud[element[jjj].extremite[2]].type=type_type_noeud[jjj-elem_amarrage+1];						
						}
						else
						{
							noeud[element[jjj].extremite[1]].z=coord_noeud_z[jjj-elem_amarrage-kkk];
							noeud[element[jjj].extremite[2]].z=coord_noeud_z[jjj-elem_amarrage+1];

							noeud[element[jjj].extremite[1]].type=type_type_noeud[jjj-elem_amarrage-kkk];
							noeud[element[jjj].extremite[2]].type=type_type_noeud[jjj-elem_amarrage+1];
						}
						element[jjj].lgrepos=lg_lg[jjj-elem_amarrage];
						printf("El: %d ",jjj);
						printf("D: 1 ");
						printf("%lf %lf %lf ",noeud[element[jjj].extremite[1]].x,noeud[element[jjj].extremite[1]].y,noeud[element[jjj].extremite[1]].z);
						printf("%d ",noeud[element[jjj].extremite[1]].type);
						printf("2 ");
						printf("%lf %lf %lf ",noeud[element[jjj].extremite[2]].x,noeud[element[jjj].extremite[2]].y,noeud[element[jjj].extremite[2]].z);
						printf("%d ",noeud[element[jjj].extremite[2]].type);
						printf("Kt: %lf ",element[jjj].raideur_traction);
						printf("Kc: %lf ",element[jjj].raideur_compression);
						printf("L: %lf ",element[jjj].lgrepos);
						printf("M: %lf ",element[jjj].rhoelement);
						printf("D: %lf ",element[jjj].diametrehydro);
						printf("Cd: %lf ",element[jjj].cdnormal);
						printf("f: %lf ",element[jjj].ftangent);
						printf("n: %d ",element[jjj].nb_barre);
						printf("t: %d ",element[jjj].type_noeud);
						printf("\n");

					}

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

					


					int kkk;
				
					for (jjj=elem_amarrage;jjj<=elem_amarrage+iii-2;jjj++)
					{
						noeud[element[jjj].extremite[1]].x=coord_noeud_x[jjj-elem_amarrage];
						noeud[element[jjj].extremite[2]].x=coord_noeud_x[jjj-elem_amarrage+1];
						noeud[element[jjj].extremite[1]].y=coord_noeud_y[jjj-elem_amarrage];
						noeud[element[jjj].extremite[2]].y=coord_noeud_y[jjj-elem_amarrage+1];

						kkk=0;
						
						while(coord_noeud_x[jjj-elem_amarrage-kkk-1]==coord_noeud_x[jjj-elem_amarrage] && coord_noeud_y[jjj-elem_amarrage-kkk-1]==coord_noeud_y[jjj-elem_amarrage] && (jjj-elem_amarrage-kkk) > 0)
						{
							kkk=kkk+1;
						}

						if (coord_noeud_x[jjj-elem_amarrage]==coord_noeud_x[jjj-elem_amarrage+1] && coord_noeud_y[jjj-elem_amarrage]==coord_noeud_y[jjj-elem_amarrage+1] && jjj-elem_amarrage-1 > 0)
						{
							noeud[element[jjj].extremite[1]].z=coord_noeud_z[jjj-elem_amarrage];
							noeud[element[jjj].extremite[2]].z=coord_noeud_z[jjj-elem_amarrage+1];
							
							noeud[element[jjj].extremite[1]].type=type_type_noeud[jjj-elem_amarrage];
							noeud[element[jjj].extremite[2]].type=type_type_noeud[jjj-elem_amarrage+1];						
						}
						else
						{
							noeud[element[jjj].extremite[1]].z=coord_noeud_z[jjj-elem_amarrage-kkk];
							noeud[element[jjj].extremite[2]].z=coord_noeud_z[jjj-elem_amarrage+1];

							noeud[element[jjj].extremite[1]].type=type_type_noeud[jjj-elem_amarrage-kkk];
							noeud[element[jjj].extremite[2]].type=type_type_noeud[jjj-elem_amarrage+1];
						}
						element[jjj].lgrepos=lg_lg[jjj-elem_amarrage];
					}

					nb_tot_elem += iii-1;

				}


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/***************************************MODIF ARNAUD****************************************************/



/***************************************MODIF ARNAUD - 08/10/09 *********************************/

				if (strcmp(chaine,"accroche") == 0)
				{
					itmp = fscanf(fic,"%lf",&Structure.add_filet_pred_diam);
					itmp = fscanf(fic,"%lf",&Structure.add_filet_pred_xxo);
					itmp = fscanf(fic,"%lf",&Structure.add_filet_pred_yyo);
					itmp = fscanf(fic,"%d",&Structure.add_filet_pred_nsegment);

					int type_accroche=0;
					int iii=0;
					int jjj=0;
	
					int elem_accroche;

					double pronf_niveau_bas=0;
					

					for (iii=1;iii<=4;iii++)
					{
						itmp = fscanf(fic,"%d",&type_accroche);
						
						elem_accroche = nb_tot_elem+1;
					
						if (type_accroche==1)
						{							
							itmp=fscanf(fic,"%f %f %f %f %f %d %d", &xxx, &yyy, &zzz, &pourc_lg_masse1, &z_masse1, &type_masse1, &pan_choisi1);

							noeud[element[elem_accroche].extremite[1]].x=xxx;
							noeud[element[elem_accroche].extremite[2]].x=xxx-(xxx-(Structure.add_filet_pred_xxo-Structure.add_filet_pred_diam/2*cos(2*PI*pan_choisi1/Structure.add_filet_pred_nsegment)))*pourc_lg_masse1;
							noeud[element[elem_accroche].extremite[1]].y=yyy;
							noeud[element[elem_accroche].extremite[2]].y=yyy-(yyy-(Structure.add_filet_pred_yyo+Structure.add_filet_pred_diam/2*sin(2*PI*pan_choisi1/Structure.add_filet_pred_nsegment)))*pourc_lg_masse1;
							noeud[element[elem_accroche].extremite[1]].z=zzz;
							noeud[element[elem_accroche].extremite[2]].z=z_masse1;

							noeud[element[elem_accroche+1].extremite[1]].x=noeud[element[elem_accroche].extremite[2]].x;
							noeud[element[elem_accroche+1].extremite[2]].x=noeud[element[elem_accroche].extremite[2]].x;
							noeud[element[elem_accroche+1].extremite[1]].y=noeud[element[elem_accroche].extremite[2]].y;
							noeud[element[elem_accroche+1].extremite[2]].y=noeud[element[elem_accroche].extremite[2]].y;
							noeud[element[elem_accroche+1].extremite[1]].z=z_masse1;
							noeud[element[elem_accroche+1].extremite[2]].z=z_masse1-1;
							noeud[element[elem_accroche+1].extremite[2]].type=type_masse1;

							noeud[element[elem_accroche+2].extremite[1]].x=noeud[element[elem_accroche].extremite[2]].x;
							noeud[element[elem_accroche+2].extremite[2]].x= Structure.add_filet_pred_xxo-Structure.add_filet_pred_diam/2*cos(2*PI*pan_choisi1/Structure.add_filet_pred_nsegment);
							noeud[element[elem_accroche+2].extremite[1]].y=noeud[element[elem_accroche].extremite[2]].y;
							noeud[element[elem_accroche+2].extremite[2]].y= Structure.add_filet_pred_yyo+Structure.add_filet_pred_diam/2*sin(2*PI*pan_choisi1/Structure.add_filet_pred_nsegment);
							noeud[element[elem_accroche+2].extremite[1]].z=z_masse1;
							noeud[element[elem_accroche+2].extremite[2]].z=pronf_niveau_bas;
							

							for (jjj=elem_accroche;jjj<=elem_accroche+2;jjj++)
							{
								element[jjj].lgrepos=sqrt((noeud[element[jjj].extremite[1]].x-noeud[element[jjj].extremite[2]].x)*(noeud[element[jjj].extremite[1]].x-noeud[element[jjj].extremite[2]].x) + (noeud[element[jjj].extremite[1]].y-noeud[element[jjj].extremite[2]].y)*(noeud[element[jjj].extremite[1]].y-noeud[element[jjj].extremite[2]].y) + (noeud[element[jjj].extremite[1]].z-noeud[element[jjj].extremite[2]].z)*(noeud[element[jjj].extremite[1]].z-noeud[element[jjj].extremite[2]].z));
							}
							nb_tot_elem += 3;	
						}


						
						else if (type_accroche==2)
						{
							itmp = fscanf(fic,"%f %f %f %f %f %d %d %f %f %d %d", &xxx, &yyy, &zzz, &pourc_lg_masse1, &z_masse1, &type_masse1, &pan_choisi1, &pourc_lg_masse2, &z_masse2, &type_masse2, &pan_choisi2);

							noeud[element[elem_accroche].extremite[1]].x=xxx;
							noeud[element[elem_accroche].extremite[2]].x=xxx-(xxx-(Structure.add_filet_pred_xxo-Structure.add_filet_pred_diam/2*cos(2*PI*pan_choisi1/Structure.add_filet_pred_nsegment)))*pourc_lg_masse1;
							noeud[element[elem_accroche].extremite[1]].y=yyy;
							noeud[element[elem_accroche].extremite[2]].y=yyy-(yyy-(Structure.add_filet_pred_yyo+Structure.add_filet_pred_diam/2*sin(2*PI*pan_choisi1/Structure.add_filet_pred_nsegment)))*pourc_lg_masse1;
							noeud[element[elem_accroche].extremite[1]].z=zzz;
							noeud[element[elem_accroche].extremite[2]].z=z_masse1;

							noeud[element[elem_accroche+1].extremite[1]].x=noeud[element[elem_accroche].extremite[2]].x;
							noeud[element[elem_accroche+1].extremite[2]].x=noeud[element[elem_accroche].extremite[2]].x;
							noeud[element[elem_accroche+1].extremite[1]].y=noeud[element[elem_accroche].extremite[2]].y;
							noeud[element[elem_accroche+1].extremite[2]].y=noeud[element[elem_accroche].extremite[2]].y;
							noeud[element[elem_accroche+1].extremite[1]].z=z_masse1;
							noeud[element[elem_accroche+1].extremite[2]].z=z_masse1-1;
							noeud[element[elem_accroche+1].extremite[2]].type=type_masse1;

							noeud[element[elem_accroche+2].extremite[1]].x=noeud[element[elem_accroche].extremite[2]].x;
							noeud[element[elem_accroche+2].extremite[2]].x= Structure.add_filet_pred_xxo-Structure.add_filet_pred_diam/2*cos(2*PI*pan_choisi1/Structure.add_filet_pred_nsegment);
							noeud[element[elem_accroche+2].extremite[1]].y=noeud[element[elem_accroche].extremite[2]].y;
							noeud[element[elem_accroche+2].extremite[2]].y= Structure.add_filet_pred_yyo+Structure.add_filet_pred_diam/2*sin(2*PI*pan_choisi1/Structure.add_filet_pred_nsegment);
							noeud[element[elem_accroche+2].extremite[1]].z=z_masse1;
							noeud[element[elem_accroche+2].extremite[2]].z=pronf_niveau_bas;


							noeud[element[elem_accroche+3].extremite[1]].x=xxx;
							noeud[element[elem_accroche+3].extremite[2]].x=xxx-(xxx-(Structure.add_filet_pred_xxo-Structure.add_filet_pred_diam/2*cos(2*PI*pan_choisi2/Structure.add_filet_pred_nsegment)))*pourc_lg_masse2;
							noeud[element[elem_accroche+3].extremite[1]].y=yyy;
							noeud[element[elem_accroche+3].extremite[2]].y=yyy-(yyy-(Structure.add_filet_pred_yyo+Structure.add_filet_pred_diam/2*sin(2*PI*pan_choisi2/Structure.add_filet_pred_nsegment)))*pourc_lg_masse2;
							noeud[element[elem_accroche+3].extremite[1]].z=zzz;
							noeud[element[elem_accroche+3].extremite[2]].z=z_masse2;

							noeud[element[elem_accroche+4].extremite[1]].x=noeud[element[elem_accroche+3].extremite[2]].x;
							noeud[element[elem_accroche+4].extremite[2]].x=noeud[element[elem_accroche+3].extremite[2]].x;
							noeud[element[elem_accroche+4].extremite[1]].y=noeud[element[elem_accroche+3].extremite[2]].y;
							noeud[element[elem_accroche+4].extremite[2]].y=noeud[element[elem_accroche+3].extremite[2]].y;
							noeud[element[elem_accroche+4].extremite[1]].z=z_masse2;
							noeud[element[elem_accroche+4].extremite[2]].z=z_masse2-1;
							noeud[element[elem_accroche+4].extremite[2]].type=type_masse2;

							noeud[element[elem_accroche+5].extremite[1]].x=noeud[element[elem_accroche+3].extremite[2]].x;
							noeud[element[elem_accroche+5].extremite[2]].x= Structure.add_filet_pred_xxo-Structure.add_filet_pred_diam/2*cos(2*PI*pan_choisi2/Structure.add_filet_pred_nsegment);
							noeud[element[elem_accroche+5].extremite[1]].y=noeud[element[elem_accroche+3].extremite[2]].y;
							noeud[element[elem_accroche+5].extremite[2]].y= Structure.add_filet_pred_yyo+Structure.add_filet_pred_diam/2*sin(2*PI*pan_choisi2/Structure.add_filet_pred_nsegment);
							noeud[element[elem_accroche+5].extremite[1]].z=z_masse2;
							noeud[element[elem_accroche+5].extremite[2]].z=pronf_niveau_bas;
							

							for (jjj=elem_accroche;jjj<=elem_accroche+5;jjj++)
							{
								element[jjj].lgrepos=sqrt((noeud[element[jjj].extremite[1]].x-noeud[element[jjj].extremite[2]].x)*(noeud[element[jjj].extremite[1]].x-noeud[element[jjj].extremite[2]].x) + (noeud[element[jjj].extremite[1]].y-noeud[element[jjj].extremite[2]].y)*(noeud[element[jjj].extremite[1]].y-noeud[element[jjj].extremite[2]].y) + (noeud[element[jjj].extremite[1]].z-noeud[element[jjj].extremite[2]].z)*(noeud[element[jjj].extremite[1]].z-noeud[element[jjj].extremite[2]].z));
							}
							nb_tot_elem += 6;
						}
								
		
						else if (type_accroche==3)
						{
							itmp = fscanf(fic,"%f %f %f %f %f %d %f %f %d %d", &xxx, &yyy, &zzz, &pourc_lg_masse1, &z_masse1, &type_masse1, &pourc_lg_pate, &z_pate, &pan_choisi1, &pan_choisi2);

							xxo=(Structure.add_filet_pred_xxo-xxx);
							yyo=(Structure.add_filet_pred_yyo-yyy);

							noeud[element[elem_accroche].extremite[1]].x=xxx;
							noeud[element[elem_accroche].extremite[2]].x=xxx+xxo*(1-Structure.add_filet_pred_diam/(2*sqrt(xxo*xxo+yyo*yyo)))*pourc_lg_masse1;

							noeud[element[elem_accroche].extremite[1]].y=yyy;
							noeud[element[elem_accroche].extremite[2]].y=yyy+yyo*(1-Structure.add_filet_pred_diam/(2*sqrt(xxo*xxo+yyo*yyo)))*pourc_lg_masse1;
							noeud[element[elem_accroche].extremite[1]].z=zzz;
							noeud[element[elem_accroche].extremite[2]].z=z_masse1;

							noeud[element[elem_accroche+1].extremite[1]].x=noeud[element[elem_accroche].extremite[2]].x;
							noeud[element[elem_accroche+1].extremite[2]].x=noeud[element[elem_accroche].extremite[2]].x;
							noeud[element[elem_accroche+1].extremite[1]].y=noeud[element[elem_accroche].extremite[2]].y;
							noeud[element[elem_accroche+1].extremite[2]].y=noeud[element[elem_accroche].extremite[2]].y;
							noeud[element[elem_accroche+1].extremite[1]].z=z_masse1;
							noeud[element[elem_accroche+1].extremite[2]].z=z_masse1-1;
							noeud[element[elem_accroche+1].extremite[2]].type=type_masse1;


							noeud[element[elem_accroche+2].extremite[1]].x=noeud[element[elem_accroche].extremite[2]].x;
							noeud[element[elem_accroche+2].extremite[2]].x=xxx+xxo*(1-Structure.add_filet_pred_diam/(2*sqrt(xxo*xxo+yyo*yyo)))*pourc_lg_pate;

							noeud[element[elem_accroche+2].extremite[1]].y=noeud[element[elem_accroche].extremite[2]].y;
							noeud[element[elem_accroche+2].extremite[2]].y=yyy+yyo*(1-Structure.add_filet_pred_diam/(2*sqrt(xxo*xxo+yyo*yyo)))*pourc_lg_pate;
							noeud[element[elem_accroche+2].extremite[1]].z=z_masse1;
							noeud[element[elem_accroche+2].extremite[2]].z=z_pate;


							noeud[element[elem_accroche+3].extremite[1]].x=noeud[element[elem_accroche+2].extremite[2]].x;
							noeud[element[elem_accroche+3].extremite[2]].x= Structure.add_filet_pred_xxo-Structure.add_filet_pred_diam/2*cos(2*PI*pan_choisi1/Structure.add_filet_pred_nsegment);
							noeud[element[elem_accroche+3].extremite[1]].y=noeud[element[elem_accroche+2].extremite[2]].y;
							noeud[element[elem_accroche+3].extremite[2]].y= Structure.add_filet_pred_yyo+Structure.add_filet_pred_diam/2*sin(2*PI*pan_choisi1/Structure.add_filet_pred_nsegment);
							noeud[element[elem_accroche+3].extremite[1]].z=z_pate;
							noeud[element[elem_accroche+3].extremite[2]].z=pronf_niveau_bas;


							noeud[element[elem_accroche+4].extremite[1]].x=noeud[element[elem_accroche+2].extremite[2]].x;
							noeud[element[elem_accroche+4].extremite[2]].x= Structure.add_filet_pred_xxo-Structure.add_filet_pred_diam/2*cos(2*PI*pan_choisi2/Structure.add_filet_pred_nsegment);
							noeud[element[elem_accroche+4].extremite[1]].y=noeud[element[elem_accroche+2].extremite[2]].y;
							noeud[element[elem_accroche+4].extremite[2]].y= Structure.add_filet_pred_yyo+Structure.add_filet_pred_diam/2*sin(2*PI*pan_choisi2/Structure.add_filet_pred_nsegment);
							noeud[element[elem_accroche+4].extremite[1]].z=z_pate;
							noeud[element[elem_accroche+4].extremite[2]].z=pronf_niveau_bas;
							

							for (jjj=elem_accroche;jjj<=elem_accroche+4;jjj++)
							{
								element[jjj].lgrepos=sqrt((noeud[element[jjj].extremite[1]].x-noeud[element[jjj].extremite[2]].x)*(noeud[element[jjj].extremite[1]].x-noeud[element[jjj].extremite[2]].x) + (noeud[element[jjj].extremite[1]].y-noeud[element[jjj].extremite[2]].y)*(noeud[element[jjj].extremite[1]].y-noeud[element[jjj].extremite[2]].y) + (noeud[element[jjj].extremite[1]].z-noeud[element[jjj].extremite[2]].z)*(noeud[element[jjj].extremite[1]].z-noeud[element[jjj].extremite[2]].z));
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


/******************************************************MODIF****************************************************************/
/***************************************MODIF ARNAUD - 23/11/09 *********************************/

			if (strcmp(chaine,"nb_barre") == 0)
			{
				itmp = fscanf(fic,"%d",&num_elem_choisi);
				itmp = fscanf(fic,"%d",&nb_barre_choisi);

				element[num_elem_choisi].nb_barre=nb_barre_choisi;
			}


/******************************************************MODIF****************************************************************/

/***************************************MODIF ARNAUD - 06/01/10 *********************************/
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

				int iii;

				for (iii=1;iii<=Structure.NbTypeelem;iii++)
				{
					if (noeud[element[iii].extremite[1]].type == tp_noeud || noeud[element[iii].extremite[2]].type == tp_noeud)
					{
						element[iii].nb_barre=nb_barre_choisi;
						modif_materiau_elem(iii, raideur_traction_choisie, raideur_compression_choisie, masse_volumique_choisie, diam_hydro_choisi, coeff_trainee_normal_choisi, coeff_trainee_tangent_choisi);
					}
				}		

			}





/******************************************************MODIF****************************************************************/


			if (strcmp(chaine,"link") == 0)
				{
				/*reading of the distance used for the automatic linling*/
				itmp = fscanf(fic,"%lf",&Structure.link_distance);
				/*itmp = fscanf(fic,"%d",&Structure.version);*/
				printf("automatic link of the points, minimal distance = %lf\n",Structure.link_distance);
				/*printf("automatic link of the points, minimal distance = %d\n",Structure.version);*/
				/*automatic_linking();*/
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
				/*
				if (element[i].extremite[1] == element[j].extremite[1]) noeud_ref = element[i].extremite[1];
				if (element[i].extremite[1] == element[j].extremite[2]) noeud_ref = element[i].extremite[1];
				if (element[i].extremite[2] == element[j].extremite[1]) noeud_ref = element[i].extremite[2];
				if (element[i].extremite[2] == element[j].extremite[2]) noeud_ref = element[i].extremite[2];
				printf ("el1 %4d nos %4d %4d  \n",i,element[i].extremite[1],element[i].extremite[2]);
				printf ("el2 %4d nos %4d %4d  \n",j,element[j].extremite[1],element[j].extremite[2]);
				printf ("noeud %4d   \n",noeud_ref);
				exit(0);
				TypeNoeud[noeud_ref].angle_link_flexion2+= TypeElement[i].angle_link_flexion2[TypeElement[i].nb_link_flexion2];
				printf ("noeud %4d angle %lf  ",noeud_ref, TypeNoeud[noeud_ref].angle_link_flexion2);
				*/
				//printf ("link_flexion_elem2 between cables %4d and %4d at angle %lf\n", TypeElement[i].link_flexion2[TypeElement[i].nb_link_flexion2], TypeElement[j].link_flexion2[TypeElement[j].nb_link_flexion2], TypeElement[i].angle_link_flexion2[TypeElement[i].nb_link_flexion2]);
			}
			if (strcmp(chaine,"catch") == 0)
				{
				itmp = fscanf(fic,"%lf",&Prise.PR);	/*prise en m3*/
				itmp = fscanf(fic,"%lf",&Prise.PE);	/*perimetre du cul en m*/
				itmp = fscanf(fic,"%lf",&Prise.TA);	/*taille moyenne des poissons en m3*/
				itmp = fscanf(fic,"%lf",&Prise.RA);	/*mesh opening stiffness en N/m*/
				PE3 = pow(Prise.PE,3.0);
				Prise.volume = Prise.PR * (1.72*(pow(Prise.PR/PE3,-0.075)) + 0.046*(pow(Prise.TA/PE3,-0.034)) - 0.0772);
				if (WB < Prise.PR) WB = Prise.PR;
				printf("Catch characteristics : PR(m^3): %lf, PE(m): %lf, TA (m^3): %lf, RA (N/m): %lf, WB (m^3): %lf\n",Prise.PR,Prise.PE,Prise.TA,Prise.RA,Prise.volume);
				}
			if (strcmp(chaine,"inversion_triangles") == 0)
				{
				inversion_triangles.nb_inversion_triangles = inversion_triangles.nb_inversion_triangles + 1;
				inversion_triangles.premier = (int *) Realloc_int(inversion_triangles.premier,1 + inversion_triangles.nb_inversion_triangles);
				inversion_triangles.second  = (int *) Realloc_int(inversion_triangles.second ,1 + inversion_triangles.nb_inversion_triangles);
				/*lecture du numero (int) du premier triangle concerne entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&inversion_triangles.premier[inversion_triangles.nb_inversion_triangles]);
				/*lecture du numero (int) du second triangle concerne entre 2 caracteres blancs !!*/
				itmp = fscanf(fic,"%d",&inversion_triangles.second[inversion_triangles.nb_inversion_triangles]);
				printf("lecture de inversion_triangles entre %d et %d \n",inversion_triangles.premier[inversion_triangles.nb_inversion_triangles],inversion_triangles.second[inversion_triangles.nb_inversion_triangles]);
				}
			if (strcmp(chaine,"type_noeud_X_SUP") == 0)
				{
				//itmp = fscanf(fic,"%lf",&type_noeud_XYZ_SUPINF.limite);
				//itmp = fscanf(fic,"%d",&type_noeud_XYZ_SUPINF.type);
				//printf("Si x > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite,type_noeud_XYZ_SUPINF.type);
				}
			if (strcmp(chaine,"type_noeud_XYZ_SUPINF") == 0)
				{
				Structure.nb_type_noeud_XYZ_SUPINF = Structure.nb_type_noeud_XYZ_SUPINF + 1;
				number = Structure.nb_type_noeud_XYZ_SUPINF;
				
				if (number == 1)
					{
					type_noeud_XYZ_SUPINF.code =	(int *)    Malloc_int(1 + number);
					type_noeud_XYZ_SUPINF.type =	(int *)    Malloc_int(1 + number);
					type_noeud_XYZ_SUPINF.limite =	(double *)    Malloc_double(1 + number);
					type_noeud_XYZ_SUPINF.limite_basse1 =	(double *)    Malloc_double(1 + number);
					type_noeud_XYZ_SUPINF.limite_haute1 =	(double *)    Malloc_double(1 + number);
					type_noeud_XYZ_SUPINF.limite_basse2 =	(double *)    Malloc_double(1 + number);
					type_noeud_XYZ_SUPINF.limite_haute2 =	(double *)    Malloc_double(1 + number);
					type_noeud_XYZ_SUPINF.limite_basse3 =	(double *)    Malloc_double(1 + number);
					type_noeud_XYZ_SUPINF.limite_haute3 =	(double *)    Malloc_double(1 + number);
					}
				else
					{
					type_noeud_XYZ_SUPINF.code =	(int *) Realloc_int(type_noeud_XYZ_SUPINF.code ,1 + number);
					type_noeud_XYZ_SUPINF.type =	(int *) Realloc_int(type_noeud_XYZ_SUPINF.type ,1 + number);
					type_noeud_XYZ_SUPINF.limite =	(double *) Realloc_double(type_noeud_XYZ_SUPINF.limite ,1 + number);
					type_noeud_XYZ_SUPINF.limite_basse1 =	(double *) Realloc_double(type_noeud_XYZ_SUPINF.limite_basse1 ,1 + number);
					type_noeud_XYZ_SUPINF.limite_haute1 =	(double *) Realloc_double(type_noeud_XYZ_SUPINF.limite_haute1 ,1 + number);
					type_noeud_XYZ_SUPINF.limite_basse2 =	(double *) Realloc_double(type_noeud_XYZ_SUPINF.limite_basse2 ,1 + number);
					type_noeud_XYZ_SUPINF.limite_haute2 =	(double *) Realloc_double(type_noeud_XYZ_SUPINF.limite_haute2 ,1 + number);
					type_noeud_XYZ_SUPINF.limite_basse3 =	(double *) Realloc_double(type_noeud_XYZ_SUPINF.limite_basse3 ,1 + number);
					type_noeud_XYZ_SUPINF.limite_haute3 =	(double *) Realloc_double(type_noeud_XYZ_SUPINF.limite_haute3 ,1 + number);
					}
				itmp = fscanf(fic,"%d",&type_noeud_XYZ_SUPINF.code[number]);
				if (type_noeud_XYZ_SUPINF.code[number] <= 6)
					{
					itmp = fscanf(fic,"%lf",&type_noeud_XYZ_SUPINF.limite[number]);
					itmp = fscanf(fic,"%d",&type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 1) printf("Si x > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite[number],type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 2) printf("Si x < %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite[number],type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 3) printf("Si y > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite[number],type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 4) printf("Si y < %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite[number],type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 5) printf("Si z > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite[number],type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 6) printf("Si z < %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite[number],type_noeud_XYZ_SUPINF.type[number]);
					}
				if ((type_noeud_XYZ_SUPINF.code[number] >= 7) && (type_noeud_XYZ_SUPINF.code[number] <= 9))
					{
					printf("number %d \n",number);
					printf("type_noeud_XYZ_SUPINF.code[number] %d \n",type_noeud_XYZ_SUPINF.code[number]);
					itmp = fscanf(fic,"%lf",&tmp_d1);
					itmp = fscanf(fic,"%lf",&tmp_d2);
					if (tmp_d1 < tmp_d2)
						{
						type_noeud_XYZ_SUPINF.limite_basse1[number] = tmp_d1;
						type_noeud_XYZ_SUPINF.limite_haute1[number] = tmp_d2;
						}
					else
						{
						type_noeud_XYZ_SUPINF.limite_basse1[number] = tmp_d2;
						type_noeud_XYZ_SUPINF.limite_haute1[number] = tmp_d1;
						}
					itmp = fscanf(fic,"%d" ,&type_noeud_XYZ_SUPINF.type[number]);
					printf("type_noeud_XYZ_SUPINF.limite_basse1[number] %lf \n",type_noeud_XYZ_SUPINF.limite_basse1[number]);
					printf("type_noeud_XYZ_SUPINF.limite_haute1[number] %lf \n",type_noeud_XYZ_SUPINF.limite_haute1[number]);
					printf("type_noeud_XYZ_SUPINF.type[number] %d \n",type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 7) printf("Si %lf > x > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite_basse1[number],type_noeud_XYZ_SUPINF.limite_haute1[number],type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 8) printf("Si %lf > y > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite_basse1[number],type_noeud_XYZ_SUPINF.limite_haute1[number],type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 9) printf("Si %lf > z > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite_basse1[number],type_noeud_XYZ_SUPINF.limite_haute1[number],type_noeud_XYZ_SUPINF.type[number]);
					}
				if ((type_noeud_XYZ_SUPINF.code[number] >= 10) && (type_noeud_XYZ_SUPINF.code[number] <= 12))
					{
					printf("number %d \n",number);
					printf("type_noeud_XYZ_SUPINF.code[number] %d \n",type_noeud_XYZ_SUPINF.code[number]);
					itmp = fscanf(fic,"%lf",&tmp_d1);
					itmp = fscanf(fic,"%lf",&tmp_d2);
					if (tmp_d1 < tmp_d2)
						{
						type_noeud_XYZ_SUPINF.limite_basse1[number] = tmp_d1;
						type_noeud_XYZ_SUPINF.limite_haute1[number] = tmp_d2;
						}
					else
						{
						type_noeud_XYZ_SUPINF.limite_basse1[number] = tmp_d2;
						type_noeud_XYZ_SUPINF.limite_haute1[number] = tmp_d1;
						}
					itmp = fscanf(fic,"%lf",&tmp_d1);
					itmp = fscanf(fic,"%lf",&tmp_d2);
					if (tmp_d1 < tmp_d2)
						{
						type_noeud_XYZ_SUPINF.limite_basse2[number] = tmp_d1;
						type_noeud_XYZ_SUPINF.limite_haute2[number] = tmp_d2;
						}
					else
						{
						type_noeud_XYZ_SUPINF.limite_basse2[number] = tmp_d2;
						type_noeud_XYZ_SUPINF.limite_haute2[number] = tmp_d1;
						}
					itmp = fscanf(fic,"%d" ,&type_noeud_XYZ_SUPINF.type[number]);
					printf("type_noeud_XYZ_SUPINF.limite_basse1[number] %lf \n",type_noeud_XYZ_SUPINF.limite_basse1[number]);
					printf("type_noeud_XYZ_SUPINF.limite_haute1[number] %lf \n",type_noeud_XYZ_SUPINF.limite_haute1[number]);
					printf("type_noeud_XYZ_SUPINF.limite_basse2[number] %lf \n",type_noeud_XYZ_SUPINF.limite_basse2[number]);
					printf("type_noeud_XYZ_SUPINF.limite_haute2[number] %lf \n",type_noeud_XYZ_SUPINF.limite_haute2[number]);
					printf("type_noeud_XYZ_SUPINF.type[number] %d \n",type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 10) printf("Si %lf > x > %lf et si  %lf > y > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite_basse1[number],type_noeud_XYZ_SUPINF.limite_haute1[number],type_noeud_XYZ_SUPINF.limite_basse2[number],type_noeud_XYZ_SUPINF.limite_haute2[number],type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 11) printf("Si %lf > y > %lf et si  %lf > z > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite_basse1[number],type_noeud_XYZ_SUPINF.limite_haute1[number],type_noeud_XYZ_SUPINF.limite_basse2[number],type_noeud_XYZ_SUPINF.limite_haute2[number],type_noeud_XYZ_SUPINF.type[number]);
					if (type_noeud_XYZ_SUPINF.code[number] == 12) printf("Si %lf > z > %lf et si  %lf > x > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite_basse1[number],type_noeud_XYZ_SUPINF.limite_haute1[number],type_noeud_XYZ_SUPINF.limite_basse2[number],type_noeud_XYZ_SUPINF.limite_haute2[number],type_noeud_XYZ_SUPINF.type[number]);
					}
				if (type_noeud_XYZ_SUPINF.code[number] == 13)
					{
					printf("number %d \n",number);
					printf("type_noeud_XYZ_SUPINF.code[number] %d \n",type_noeud_XYZ_SUPINF.code[number]);
					itmp = fscanf(fic,"%lf",&tmp_d1);
					itmp = fscanf(fic,"%lf",&tmp_d2);
					printf("tmp_d %lf %lf \n",tmp_d1,tmp_d2);
					if (tmp_d1 < tmp_d2)
						{
						type_noeud_XYZ_SUPINF.limite_basse1[number] = tmp_d1;
						type_noeud_XYZ_SUPINF.limite_haute1[number] = tmp_d2;
						}
					else
						{
						type_noeud_XYZ_SUPINF.limite_basse1[number] = tmp_d2;
						type_noeud_XYZ_SUPINF.limite_haute1[number] = tmp_d1;
						}
					itmp = fscanf(fic,"%lf",&tmp_d1);
					itmp = fscanf(fic,"%lf",&tmp_d2);
					printf("tmp_d %lf %lf \n",tmp_d1,tmp_d2);
					if (tmp_d1 < tmp_d2)
						{
						type_noeud_XYZ_SUPINF.limite_basse2[number] = tmp_d1;
						type_noeud_XYZ_SUPINF.limite_haute2[number] = tmp_d2;
						}
					else
						{
						type_noeud_XYZ_SUPINF.limite_basse2[number] = tmp_d2;
						type_noeud_XYZ_SUPINF.limite_haute2[number] = tmp_d1;
						}
					itmp = fscanf(fic,"%lf",&tmp_d1);
					itmp = fscanf(fic,"%lf",&tmp_d2);
					printf("tmp_d %lf %lf \n",tmp_d1,tmp_d2);
					if (tmp_d1 < tmp_d2)
						{
						type_noeud_XYZ_SUPINF.limite_basse3[number] = tmp_d1;
						type_noeud_XYZ_SUPINF.limite_haute3[number] = tmp_d2;
						}
					else
						{
						type_noeud_XYZ_SUPINF.limite_basse3[number] = tmp_d2;
						type_noeud_XYZ_SUPINF.limite_haute3[number] = tmp_d1;
						}
					itmp = fscanf(fic,"%d" ,&type_noeud_XYZ_SUPINF.type[number]);
					printf("type_noeud_XYZ_SUPINF.limite_basse1[number] %lf \n",type_noeud_XYZ_SUPINF.limite_basse1[number]);
					printf("type_noeud_XYZ_SUPINF.limite_haute1[number] %lf \n",type_noeud_XYZ_SUPINF.limite_haute1[number]);
					printf("type_noeud_XYZ_SUPINF.limite_basse2[number] %lf \n",type_noeud_XYZ_SUPINF.limite_basse2[number]);
					printf("type_noeud_XYZ_SUPINF.limite_haute2[number] %lf \n",type_noeud_XYZ_SUPINF.limite_haute2[number]);
					printf("type_noeud_XYZ_SUPINF.limite_basse3[number] %lf \n",type_noeud_XYZ_SUPINF.limite_basse3[number]);
					printf("type_noeud_XYZ_SUPINF.limite_haute3[number] %lf \n",type_noeud_XYZ_SUPINF.limite_haute3[number]);
					printf("type_noeud_XYZ_SUPINF.type[number] %d \n",type_noeud_XYZ_SUPINF.type[number]);
					printf("Si %lf > x > %lf et si  %lf > y > %lf et si  %lf > z > %lf son type est %d \n",type_noeud_XYZ_SUPINF.limite_basse1[number],type_noeud_XYZ_SUPINF.limite_haute1[number],type_noeud_XYZ_SUPINF.limite_basse2[number],type_noeud_XYZ_SUPINF.limite_haute2[number],type_noeud_XYZ_SUPINF.limite_basse3[number],type_noeud_XYZ_SUPINF.limite_haute3[number],type_noeud_XYZ_SUPINF.type[number]);
					}
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
				printf("Ball.radius = %lf \n",tmp_d1);
				Ball.radius =        	(double *) Malloc_double(1 + Ball.nb);
				Ball.x =        	(double *) Malloc_double(1 + Ball.nb);
				Ball.y =        	(double *) Malloc_double(1 + Ball.nb);
				Ball.z =        	(double *) Malloc_double(1 + Ball.nb);
				Ball.birth_time =    	(double *) Malloc_double(1 + Ball.nb);
				Ball.noeud =         	(int *)    Malloc_int(1 + Ball.nb);
				Ball.stiffness =    	(double *) Malloc_double(1 + Ball.nb);
				Ball.type =         	(int *)    Malloc_int(1 + Ball.nb);
				Ball.ini_speed_x =    	(double *) Malloc_double(1 + Ball.nb);
				Ball.ini_speed_y =    	(double *) Malloc_double(1 + Ball.nb);
				Ball.ini_speed_z =    	(double *) Malloc_double(1 + Ball.nb);
				time = 0.0;
				for (pa=1;pa<=Ball.nb;pa++)
					{
					Ball.radius[pa] = tmp_d1;
					Ball.birth_time[pa] = time;
					speed_ball = fabs(Courant.vitesse);
					if (speed_ball == 0.0) speed_ball = 0.1;
					time = time + 4.0 * Ball.radius[pa] / speed_ball;
					Ball.stiffness[pa] = tmp_d5;
					Ball.type[pa] = tmp_i1;		
					Ball.ini_speed_x[pa] = 0.0;
					Ball.ini_speed_y[pa] = 0.0;
					Ball.ini_speed_z[pa] = 0.0;
					if (Structure.orientation == 1)
						{
						Ball.z[pa] = tmp_d2;
						Ball.x[pa] = tmp_d3;
						Ball.y[pa] = tmp_d4;
						}
					if (Structure.orientation == 2)
						{
						Ball.y[pa] = tmp_d2;
						Ball.z[pa] = tmp_d3;
						Ball.x[pa] = tmp_d4;
						}
					if (Structure.orientation == 3)
						{
						Ball.x[pa] = tmp_d2;
						Ball.y[pa] = tmp_d3;
						Ball.z[pa] = tmp_d4;
						}
					}
				}			
			if (strcmp(chaine,"balls_2") == 0)
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
				itmp = fscanf(fic,"%lf",&tmp_d6);
				itmp = fscanf(fic,"%lf",&tmp_d7);
				itmp = fscanf(fic,"%lf",&tmp_d8);
				printf("Ball.radius = %lf \n",tmp_d1);
				Ball.radius =        	(double *) Malloc_double(1 + Ball.nb);
				Ball.x =        	(double *) Malloc_double(1 + Ball.nb);
				Ball.y =        	(double *) Malloc_double(1 + Ball.nb);
				Ball.z =        	(double *) Malloc_double(1 + Ball.nb);
				Ball.birth_time =    	(double *) Malloc_double(1 + Ball.nb);
				Ball.noeud =         	(int *)    Malloc_int(1 + Ball.nb);
				Ball.stiffness =    	(double *) Malloc_double(1 + Ball.nb);
				Ball.type =         	(int *)    Malloc_int(1 + Ball.nb);
				Ball.ini_speed_x =    	(double *) Malloc_double(1 + Ball.nb);
				Ball.ini_speed_y =    	(double *) Malloc_double(1 + Ball.nb);
				Ball.ini_speed_z =    	(double *) Malloc_double(1 + Ball.nb);
				time = 0.0;
				for (pa=1;pa<=Ball.nb;pa++)
					{
					Ball.radius[pa] = tmp_d1;
					Ball.stiffness[pa] = tmp_d5;
					Ball.type[pa] = tmp_i1;		
					Ball.ini_speed_x[pa] = tmp_d6;
					Ball.ini_speed_y[pa] = tmp_d7;
					Ball.ini_speed_z[pa] = tmp_d8;
					Ball.birth_time[pa] = time;
					speed_ball = fabs((Ball.ini_speed_x[pa]*Ball.ini_speed_x[pa])+(Ball.ini_speed_y[pa]*Ball.ini_speed_y[pa])+(Ball.ini_speed_z[pa]*Ball.ini_speed_z[pa]));
					if (speed_ball == 0.0) speed_ball = 1.0;
					time = time + 4.0 * Ball.radius[pa] / speed_ball;
					if (Structure.orientation == 1)
						{
						Ball.z[pa] = tmp_d2;
						Ball.x[pa] = tmp_d3;
						Ball.y[pa] = tmp_d4;
						}
					if (Structure.orientation == 2)
						{
						Ball.y[pa] = tmp_d2;
						Ball.z[pa] = tmp_d3;
						Ball.x[pa] = tmp_d4;
						}
					if (Structure.orientation == 3)
						{
						Ball.x[pa] = tmp_d2;
						Ball.y[pa] = tmp_d3;
						Ball.z[pa] = tmp_d4;
						}
					}
				}
			}	/*end of input*/
			
		}	/*end of lecture chaine*/
	if ((Structure.version == 3) && (Ball.nb == 0))
		{
		printf("If Structure.version = %d Ball.nb must be > %d\n",Structure.version,Ball.nb);
		exit(0);
		}
	
	/**************************************************************/
	fclose(fic);
	



	initialisation_nb_fils();
	initialisation_ps();
	initialisation_lien();
	initialisation_seam();
	
	strcpy(tonom,fname1);
 	strcat(tonom,".des");
	f3 = fopen(tonom,"w");

	/* debut modifdp du 4 mars 2010*/
	/*f3 = fopen("dessin.txt","w");
  	if (f3 == NULL) 
  		{ 
  		printf("* creer_fichier_des * impossible d ouvrir le fichier dessin.txt\n");
  	  	exit(0);
  		}*/
	/*f3 = fopen("dessin.txt","w");*/
  	if (f3 == NULL) 
  		{ 
  		/*printf("* creer_fichier_des * impossible d ouvrir le fichier dessin.txt\n");*/
  		printf("creer_fichier_des: impossible d ouvrir le fichier %s\n",tonom);
  	  	exit(0);
  		}
	/* fin modifdp du 4 mars 2010*/


	for (pa=1;pa<=Structure.NbTypesurf;pa++)	fprintf(f3,"pa %3d : %d\n",pa,panneau[pa].flag_dessin);	fprintf(f3,"\n");
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)	fprintf(f3,"he %3d : 1\n",pa);	fprintf(f3,"\n");
	for (pa=1;pa<=Structure.NbTypeelem;pa++)	fprintf(f3,"el %3d : %d\n",pa,element[pa].flag_dessin);	fprintf(f3,"\n");
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)	fprintf(f3,"co %3d : 1\n",pa);	fprintf(f3,"\n");
	for (pa=1;pa<=Structure.nb_winch;pa++)	fprintf(f3,"wi %3d : 1\n",pa);	fprintf(f3,"\n");
	for (pa=1;pa<=Structure.nb_barre;pa++)	fprintf(f3,"ba %3d : 1\n",pa);	fprintf(f3,"\n"); //NOMBRE_ELEMENTS
	for (pa=1;pa<=Structure.nb_total;pa++)	fprintf(f3,"pt %3d : 1\n",pa); //NOMBRE_NOEUDS
	fclose(f3);

	if (Structure.link_distance >= 0.0)
		{
		printf("Automatic linking with distance = %lf\n",Structure.link_distance);
		automatic_linking();
		}
	
	for (pa=1;pa<=Structure.nb_liaison;pa++) Lien[pa].angle_link_flexion2 = 0.0;
	int el1,el2,strli,noli,nblink,trouve_el1,trouve_el2,trouve_no1,trouve_no2,extr1,extr2,strli1,strli2,noli1,noli2;
	for (el1=1;el1<=Structure.NbTypeelem;el1++)
		{
		if (TypeElement[el1].nb_link_flexion2 > 0)
			{
			for (nblink=1;nblink<=TypeElement[el1].nb_link_flexion2;nblink++)
				{
				el2 = TypeElement[el1].link_flexion2[nblink];
				//printf ("el1 %4d el2 %4d  \n",el1,el2);
				for (strli=1;strli<=Structure.nb_liaison;strli++)
					{
					trouve_el1 = 0;
					trouve_el2 = 0;
					for (noli=1;noli<=Lien[strli].nb_liaison;noli++)
						{
						if (Lien[strli].type[noli] == 'e')
							{
							if (Lien[strli].structure[noli] == el1)
								{
								trouve_el1 = 1;
								strli1 = strli;
								noli1 = noli;
								extr1 = Lien[strli].extremite[noli];
								trouve_no1 = element[el1].extremite[extr1];
								}
							}
						if (Lien[strli].type[noli] == 'e')
							{
							if (Lien[strli].structure[noli] == el2)
								{
								trouve_el2 = 1;
								strli2 = strli;
								noli2 = noli;
								extr2 = Lien[strli].extremite[noli];
								trouve_no2 = element[el2].extremite[extr2];
								}
							}
						}
					if ((trouve_el1 == 1) && (trouve_el2 == 1))
						{
						Lien[strli1].angle_link_flexion2+= (180.0 - TypeElement[el1].angle_link_flexion2[nblink])/2.0;
						//printf ("el1 %4d trouve_no1 %4d strli1 %4d ",el1,trouve_no1,strli1);
						//printf ("el2 %4d trouve_no2 %4d strli2 %4d angle %3.0lf\n",el2,trouve_no2,strli2,Lien[strli1].angle_link_flexion2);
						}
					}
				
				}
			}
		}	
	for (pa=1;pa<=Structure.nb_liaison;pa++)
		{
		//printf ("pa %4d angle %3.0lf\n",pa,Lien[pa].angle_link_flexion2);
		}
	
	
	initialisation_nb();
	/*initialisation_lien();*/
	if (Structure.graphic == 1)
		{
		SetMenuItemChecked(w[1],1);
		}
	}


void initialisation_nb()
	{
	/*initialisation des nb*********************************************/
	Structure.NbTypeNoeud 		= Structure.NbTypeNoeud;
	Structure.nb_barre 		= 0;
	Structure.nombreSurfaces 		= 0;
	Structure.nombreSurfHexa 		= 0;
	Structure.nb_lien	 		= Structure.nb_liaison;
	}
	
void initialisation_seam()
	{
	int pa,nn,no,np,p1,p2,p3;
	double nnU,nnV,npU,npV,U1,U2,U3,U4,V1,V2,V3,V4,Ln,Lp,Us,Vs;
	double Un,Uo,Up,Vn,Vo,Vp,UO,VO,deno,orientation,p0u,p0v,p0x,p0y,p0z,p1u,p1v,p1x,p1y,p1z,p2u,p2v,p2x,p2y,p2z,p3u,p3v,p3x,p3y,p3z;
	double surface,alpha,beta;
	
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{
			noeud_seam[panneau[pa].noeud_contour[no]].U = noeud[panneau[pa].noeud_contour[no]].U;
			noeud_seam[panneau[pa].noeud_contour[no]].V = noeud[panneau[pa].noeud_contour[no]].V;
			}
		}

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		if (panneau[pa].seam != 0.0)
			{
			orientation = 0.0;
			/*point no is treated, nn is the node before and np thye node after
			from segment nn no  another segment is created : 12
			from segment no np  another segment is created : 34
			the intersection of 12 & 34 is the seam node of no*/
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{
				if (no == 1)
					{
					nn = panneau[pa].nb_noeud_contour;
					np = no + 1;
					}
				if (no == panneau[pa].nb_noeud_contour)
					{
					nn = no - 1;
					np = 1;
					}
				if ((no != 1) && (no != panneau[pa].nb_noeud_contour))
					{
					nn = no - 1;
					np = no + 1;
					}
				Un = noeud[panneau[pa].noeud_contour[nn]].U;	Vn = noeud[panneau[pa].noeud_contour[nn]].V;
				Uo = noeud[panneau[pa].noeud_contour[no]].U;	Vo = noeud[panneau[pa].noeud_contour[no]].V;
				Up = noeud[panneau[pa].noeud_contour[np]].U;	Vp = noeud[panneau[pa].noeud_contour[np]].V;
				orientation += (Uo-Un)*(Vp-Vn) - (Up-Un)*(Vo-Vn);
				}
			/*orientation tells in which sense we turn around the polygon 
			and consequently on which side of segment the seam is created*/
			if (fabs(orientation) != 0.0)
				{
				orientation = orientation/fabs(orientation);
				}
			else
				{
				orientation = 1.0;
				}
		
			printf("orientation panel %d = %lf\n", pa,orientation); 		
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{
				if (no == 1)
					{
					nn = panneau[pa].nb_noeud_contour;
					np = no + 1;
					}
				if (no == panneau[pa].nb_noeud_contour)
					{
					nn = no - 1;
					np = 1;
					}
				if ((no != 1) && (no != panneau[pa].nb_noeud_contour))
					{
					nn = no - 1;
					np = no + 1;
					}
				Un = noeud[panneau[pa].noeud_contour[nn]].U;	Vn = noeud[panneau[pa].noeud_contour[nn]].V;
				Uo = noeud[panneau[pa].noeud_contour[no]].U;	Vo = noeud[panneau[pa].noeud_contour[no]].V;
				Up = noeud[panneau[pa].noeud_contour[np]].U;	Vp = noeud[panneau[pa].noeud_contour[np]].V;
				/*printf("Uo %lf Un %lf Vo %lf Vn %lf \n",Uo,Un,Vo,Vn);
				8 sectors are defined :
				between E  and NE : sector1 => the seam is under if orientation >0
				between NE and N  : sector2 => the seam is right if orientation >0
				between N  and NW : sector3 => the seam is right if orientation >0
				between NW and W  : sector4 => the seam is above if orientation >0
				between W  and SW : sector5 => the seam is above if orientation >0
				between SW and S  : sector6 => the seam is left if orientation >0
				between S  and SE : sector7 => the seam is left if orientation >0
				between SE and E  : sector8 => the seam is under if orientation >0
				*/
				/*first segment no*/
				if ((Uo>=Un)&&(Vo>=Vn)&&((Uo-Un)>=(Vo-Vn)))
					{
					printf("sector no 1 ");	
					U1 = Un;	V1 = Vn - orientation * panneau[pa].seam;
					U2 = Uo;	V2 = Vo - orientation * panneau[pa].seam;
					}
				if ((Uo>=Un)&&(Vo>=Vn)&&((Uo-Un)<=(Vo-Vn)))
					{
					printf("sector no 2 ");	
					U1 = Un + orientation * panneau[pa].seam;	V1 = Vn;
					U2 = Uo + orientation * panneau[pa].seam;	V2 = Vo;
					}
				if ((Uo<=Un)&&(Vo>=Vn)&&((Un-Uo)<=(Vo-Vn)))
					{
					printf("sector no 3 ");		
					U1 = Un + orientation * panneau[pa].seam;	V1 = Vn;
					U2 = Uo + orientation * panneau[pa].seam;	V2 = Vo;
					}
				if ((Uo<=Un)&&(Vo>=Vn)&&((Un-Uo)>=(Vo-Vn)))
					{
					printf("sector no 4 ");		
					U1 = Un;	V1 = Vn + orientation * panneau[pa].seam;
					U2 = Uo;	V2 = Vo + orientation * panneau[pa].seam;
					}
				if ((Uo<=Un)&&(Vo<=Vn)&&((Un-Uo)>=(Vn-Vo)))
					{
					printf("sector no 5 ");	
					U1 = Un;	V1 = Vn + orientation * panneau[pa].seam;
					U2 = Uo;	V2 = Vo + orientation * panneau[pa].seam;
					}
				if ((Uo<=Un)&&(Vo<=Vn)&&((Un-Uo)<=(Vn-Vo)))
					{
					printf("sector no 6 ");		
					U1 = Un - orientation * panneau[pa].seam;	V1 = Vn;
					U2 = Uo - orientation * panneau[pa].seam;	V2 = Vo;
					}
				if ((Uo>=Un)&&(Vo<=Vn)&&((Uo-Un)<=(Vn-Vo)))
					{
					printf("sector no 7 ");	
					U1 = Un - orientation * panneau[pa].seam;	V1 = Vn;
					U2 = Uo - orientation * panneau[pa].seam;	V2 = Vo;
					}
				if ((Uo>=Un)&&(Vo<=Vn)&&((Uo-Un)>=(Vn-Vo)))
					{
					printf("sector no 8 ");	
					U1 = Un;	V1 = Vn - orientation * panneau[pa].seam;
					U2 = Uo;	V2 = Vo - orientation * panneau[pa].seam;
					}

				/*second segment op*/
				if ((Up>=Uo)&&(Vp>=Vo)&&((Up-Uo)>=(Vp-Vo)))
					{
					printf("	sector op 1 \n");
					U3 = Uo;	V3 = Vo - orientation * panneau[pa].seam;
					U4 = Up;	V4 = Vp - orientation * panneau[pa].seam;
					}
				if ((Up>=Uo)&&(Vp>=Vo)&&((Up-Uo)<=(Vp-Vo)))
					{
					printf("	sector op 2 \n");	
					U3 = Uo + orientation * panneau[pa].seam;	V3 = Vo;
					U4 = Up + orientation * panneau[pa].seam;	V4 = Vp;
					}
				if ((Up<=Uo)&&(Vp>=Vo)&&((Uo-Up)<=(Vp-Vo)))
					{
					printf("	sector op 3 \n");	
					U3 = Uo + orientation * panneau[pa].seam;	V3 = Vo;
					U4 = Up + orientation * panneau[pa].seam;	V4 = Vp;
					}
				if ((Up<=Uo)&&(Vp>=Vo)&&((Uo-Up)>=(Vp-Vo)))
					{
					printf("	sector op 4 \n");	
					U3 = Uo;	V3 = Vo + orientation * panneau[pa].seam;
					U4 = Up;	V4 = Vp + orientation * panneau[pa].seam;
					}
				if ((Up<=Uo)&&(Vp<=Vo)&&((Uo-Up)>=(Vo-Vp)))
					{
					printf("	sector op 5 \n");	
					U3 = Uo;	V3 = Vo + orientation * panneau[pa].seam;
					U4 = Up;	V4 = Vp + orientation * panneau[pa].seam;
					}
				if ((Up<=Uo)&&(Vp<=Vo)&&((Uo-Up)<=(Vo-Vp)))
					{
					printf("	sector op 6 \n");	
					U3 = Uo - orientation * panneau[pa].seam;	V3 = Vo;
					U4 = Up - orientation * panneau[pa].seam;	V4 = Vp;
					}
				if ((Up>=Uo)&&(Vp<=Vo)&&((Up-Uo)<=(Vo-Vp)))
					{
					printf("	sector op 7 \n");				U3 = Uo - orientation * panneau[pa].seam;	V3 = Vo;
					U4 = Up - orientation * panneau[pa].seam;	V4 = Vp;
					}
				if ((Up>=Uo)&&(Vp<=Vo)&&((Up-Uo)>=(Vo-Vp)))
					{
					printf("	sector op 8 \n");
					U3 = Uo;	V3 = Vo - orientation * panneau[pa].seam;
					U4 = Up;	V4 = Vp - orientation * panneau[pa].seam;
					}
				seam_coordinates(pa, no, U1, U2, U3, U4, V1, V2, V3, V4);
				}
			}
		}
	}

void automatic_linking()
	{
	/*initialisation of links between points*********************************************/
	double xx1,xx2,yy1,yy2,zz1,zz2,distance;
	int pa1,no1,el1,pa2,no2,el2,trouve,li2,co2;
	
	initialisation_lien();
	printf("Structure.nb_liaison  = %8d\n", Structure.nb_liaison);
	/*find the links for the corners of the diamond mesh panels***********************************************************/
	for (pa1=1;pa1<=Structure.NbTypesurf;pa1++)
		{
		for (no1=1;no1<=panneau[pa1].nb_noeud_contour;no1++)
			{
			if (Structure.orientation == 1)
				{
				xx1 = noeud[panneau[pa1].noeud_contour[no1]].y;
				yy1 = noeud[panneau[pa1].noeud_contour[no1]].z;
				zz1 = noeud[panneau[pa1].noeud_contour[no1]].x;
				}
			if (Structure.orientation == 2)
				{
				xx1 = noeud[panneau[pa1].noeud_contour[no1]].z;
				yy1 = noeud[panneau[pa1].noeud_contour[no1]].x;
				zz1 = noeud[panneau[pa1].noeud_contour[no1]].y;
				}
			if (Structure.orientation == 3)
				{
				xx1 = noeud[panneau[pa1].noeud_contour[no1]].x;
				yy1 = noeud[panneau[pa1].noeud_contour[no1]].y;
				zz1 = noeud[panneau[pa1].noeud_contour[no1]].z;
				}
			trouve = 0;
			/*printf("pa1: %4d no1: %4d pos  %lf %lf %lf\n",pa1,no1,xx1,yy1,zz1);*/
			
			/*verify if the node is in a link*/
			for (li2=1;li2<=Structure.nb_liaison;li2++)
				{
				for (co2=1;co2<=Lien[li2].nb_liaison;co2++)
					{
					if ((Lien[li2].type[co2] == 'p') && (Lien[li2].structure[co2] == pa1) && (Lien[li2].extremite[co2] == no1))
						{
						/*this node is already in a link*/
						trouve = 1;
						}
					}
				}
			
			/*because the node is not in a link we verify if the node is near a link*/
			if (trouve == 0)
				{
				for (li2=1;li2<=Structure.nb_liaison;li2++)
					{
					for (co2=1;co2<=Lien[li2].nb_liaison;co2++)
						{
						if (Structure.orientation == 1)
							{
							xx2 = noeud[Lien[li2].noeud[co2]].y;
							yy2 = noeud[Lien[li2].noeud[co2]].z;
							zz2 = noeud[Lien[li2].noeud[co2]].x;
							}
						if (Structure.orientation == 2)
							{
							xx2 = noeud[Lien[li2].noeud[co2]].z;
							yy2 = noeud[Lien[li2].noeud[co2]].x;
							zz2 = noeud[Lien[li2].noeud[co2]].y;
							}
						if (Structure.orientation == 3)
							{
							xx2 = noeud[Lien[li2].noeud[co2]].x;
							yy2 = noeud[Lien[li2].noeud[co2]].y;
							zz2 = noeud[Lien[li2].noeud[co2]].z;
							}
						/*printf("pa1: %4d no1: %4d pos  %lf %lf %lf  ",pa1,no1,xx1,yy1,zz1);*/
						/*printf("li2: %4d co2: %4d pos  %lf %lf %lf\n",li2,co2,xx2,yy2,zz2);*/
						distance = sqrt((xx2-xx1)*(xx2-xx1) + (yy2-yy1)*(yy2-yy1) + (zz2-zz1)*(zz2-zz1));
						if ((distance <= Structure.link_distance) && (trouve == 0))
							{
							/*this node is near a link*/
							trouve = 1;
							//printf("1 Automatic linking pa1: %4d no1: %4d li2: %4d co2: %4d dist %lf pas  %lf %lf %lf %lf %lf %lf\n",pa1,no1,li2,co2,distance,xx1,xx2,yy1,yy2,zz1,zz2);/**/
							
							Lien[li2].nb_liaison = Lien[li2].nb_liaison + 1;
							/**********************************************/
  							Lien[li2].structure = (int *) realloc(Lien[li2].structure, (1 + Lien[li2].nb_liaison) * sizeof(int));
							if (Lien[li2].structure    == NULL)
								{
								printf("Lien[li2].structure  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[li2].extremite = (int *) realloc(Lien[li2].extremite, (1 + Lien[li2].nb_liaison) * sizeof(int));
							if (Lien[li2].extremite    == NULL)
								{
								printf("Lien[li2].extremite  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[li2].noeud = (int *) realloc(Lien[li2].noeud, (1 + Lien[li2].nb_liaison) * sizeof(int));
							if (Lien[li2].noeud    == NULL)
								{
								printf("Lien[li2].noeud  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[li2].type = (char *) realloc(Lien[li2].type, (1 + Lien[li2].nb_liaison) * sizeof(char));
							if (Lien[li2].type    == NULL)
								{
								printf("Lien[li2].type  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
							Lien[li2].type     [Lien[li2].nb_liaison] = 'p';
							Lien[li2].structure[Lien[li2].nb_liaison] = pa1;
							Lien[li2].extremite[Lien[li2].nb_liaison] = no1;
							Lien[li2].noeud    [Lien[li2].nb_liaison] = panneau[pa1].noeud_contour[no1];
							}
						}
					}
				}
			
			
			
			
			/*because the node is not in a link and not near a link we verify if the node is near another node
			of diamond mesh panel and we create a new link with 2 nodes*/
			if (trouve == 0)
				{
				for (pa2=1;pa2<=Structure.NbTypesurf;pa2++)
					{
					if (pa2 != pa1)
						{
						for (no2=1;no2<=panneau[pa2].nb_noeud_contour;no2++)
							{
							if (Structure.orientation == 1)
								{
								xx2 = noeud[panneau[pa2].noeud_contour[no2]].y;
								yy2 = noeud[panneau[pa2].noeud_contour[no2]].z;
								zz2 = noeud[panneau[pa2].noeud_contour[no2]].x;
								}
							if (Structure.orientation == 2)
								{
								xx2 = noeud[panneau[pa2].noeud_contour[no2]].z;
								yy2 = noeud[panneau[pa2].noeud_contour[no2]].x;
								zz2 = noeud[panneau[pa2].noeud_contour[no2]].y;
								}
							if (Structure.orientation == 3)
								{
								xx2 = noeud[panneau[pa2].noeud_contour[no2]].x;
								yy2 = noeud[panneau[pa2].noeud_contour[no2]].y;
								zz2 = noeud[panneau[pa2].noeud_contour[no2]].z;
								}
							distance = sqrt((xx2-xx1)*(xx2-xx1) + (yy2-yy1)*(yy2-yy1) + (zz2-zz1)*(zz2-zz1));
							//printf("2 Automatic linking pa1: %4d no1: %4d pa2: %4d no2: %4d  distance: %lf\n",pa1,no1,pa2,no2,distance);
							if ((distance <= Structure.link_distance) && (trouve == 0))
								{
								trouve = 1;
								Structure.nb_liaison  = Structure.nb_liaison + 1;
								//printf("3 Automatic linking pa1: %4d no1: %4d pa2: %4d no2: %4d  nb_link: %4d\n",pa1,no1,pa2,no2,Structure.nb_liaison);
								if ( Structure.nb_liaison >= NBMAXLIAISON)
									{
									printf(" NBMAXLIAISON trop petit %4d < %4d \n",NBMAXLIAISON,Structure.nb_liaison );
									exit(0);
									}
								Lien[Structure.nb_liaison].nb_liaison = 2;
								/**********************************************/
								Lien[Structure.nb_liaison].structure = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
								if (Lien[Structure.nb_liaison].structure    == NULL)
									{
									printf("Lien[Structure.nb_liaison].structure  1 = NULL  \n" );
									exit(0);
									}
								/**********************************************/
  								Lien[Structure.nb_liaison].extremite = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
								if (Lien[Structure.nb_liaison].extremite    == NULL)
									{
									printf("Lien[Structure.nb_liaison].extremite  1 = NULL  \n" );
									exit(0);
									}
								/**********************************************/
  								Lien[Structure.nb_liaison].noeud = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
								if (Lien[Structure.nb_liaison].noeud    == NULL)
									{
									printf("Lien[Structure.nb_liaison].noeud  1 = NULL  \n" );
									exit(0);
									}
								/**********************************************/
  								Lien[Structure.nb_liaison].type = (char *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(char));
								if (Lien[Structure.nb_liaison].type    == NULL)
									{
									printf("Lien[Structure.nb_liaison].type  1 = NULL  \n" );
									exit(0);
									}
								/**********************************************/
								Lien[Structure.nb_liaison].nb_liaison = 2;
								Lien[Structure.nb_liaison].type[1] = 'p';
								Lien[Structure.nb_liaison].structure[1] = pa1;
								Lien[Structure.nb_liaison].extremite[1] = no1;
								Lien[Structure.nb_liaison].noeud[1] = panneau[pa1].noeud_contour[no1];
								Lien[Structure.nb_liaison].type[2] = 'p';
								Lien[Structure.nb_liaison].structure[2] = pa2;
								Lien[Structure.nb_liaison].extremite[2] = no2;
								Lien[Structure.nb_liaison].noeud[2] = panneau[pa2].noeud_contour[no2];
								}
							}
						}
					}
				}

			/*because the node is not in a link and not near a link we verify if the node is near another node
			of element and we create a new link with 2 nodes*/
			if (trouve == 0)
				{
				for (pa2=1;pa2<=Structure.NbTypeelem;pa2++)
					{
					for (no2=1;no2<=2;no2++)
						{
						if (Structure.orientation == 1)
							{
							xx2 = noeud[element[pa2].extremite[no2]].y;
							yy2 = noeud[element[pa2].extremite[no2]].z;
							zz2 = noeud[element[pa2].extremite[no2]].x;
							}
						if (Structure.orientation == 2)
							{
							xx2 = noeud[element[pa2].extremite[no2]].z;
							yy2 = noeud[element[pa2].extremite[no2]].x;
							zz2 = noeud[element[pa2].extremite[no2]].y;
							}
						if (Structure.orientation == 3)
							{
							xx2 = noeud[element[pa2].extremite[no2]].x;
							yy2 = noeud[element[pa2].extremite[no2]].y;
							zz2 = noeud[element[pa2].extremite[no2]].z;
							}
						distance = sqrt((xx2-xx1)*(xx2-xx1) + (yy2-yy1)*(yy2-yy1) + (zz2-zz1)*(zz2-zz1));
						/*the next line is to avoid to link a node with it self*/
						if ((pa2==pa1) && (no2==no1)) distance = 2.0 * Structure.link_distance;
						if ((distance <= Structure.link_distance) && (trouve == 0))
							{
							trouve = 1;
							Structure.nb_liaison  = Structure.nb_liaison + 1;
							/*printf("4 Automatic linking pa1: %4d no1: %4d el2: %4d no2: %4d  nb_link: %4d\n",pa1,no1,pa2,no2,Structure.nb_liaison);*/
							if ( Structure.nb_liaison >= NBMAXLIAISON)
								{
								printf(" NBMAXLIAISON trop petit %4d < %4d \n",NBMAXLIAISON,Structure.nb_liaison );
								exit(0);
								}
							Lien[Structure.nb_liaison].nb_liaison = 2;
							/**********************************************/
  							Lien[Structure.nb_liaison].structure = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
							if (Lien[Structure.nb_liaison].structure    == NULL)
								{
								printf("Lien[Structure.nb_liaison].structure  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[Structure.nb_liaison].extremite = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
							if (Lien[Structure.nb_liaison].extremite    == NULL)
								{
								printf("Lien[Structure.nb_liaison].extremite  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[Structure.nb_liaison].noeud = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
							if (Lien[Structure.nb_liaison].noeud    == NULL)
								{
								printf("Lien[Structure.nb_liaison].noeud  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[Structure.nb_liaison].type = (char *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(char));
							if (Lien[Structure.nb_liaison].type    == NULL)
								{
								printf("Lien[Structure.nb_liaison].type  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
							Lien[Structure.nb_liaison].nb_liaison = 2;
							Lien[Structure.nb_liaison].type[1] = 'p';
							Lien[Structure.nb_liaison].structure[1] = pa1;
							Lien[Structure.nb_liaison].extremite[1] = no1;
							Lien[Structure.nb_liaison].noeud[1] = panneau[pa1].noeud_contour[no1];
							Lien[Structure.nb_liaison].type[2] = 'e';
							Lien[Structure.nb_liaison].structure[2] = pa2;
							Lien[Structure.nb_liaison].extremite[2] = no2;
							Lien[Structure.nb_liaison].noeud[2] = element[pa2].extremite[no2];
							}
						}
					}
				}
			}
		}
		

	/*find the links for the extremities of the elements***********************************************************/
	for (el1=1;el1<=Structure.NbTypeelem;el1++)
		{
		//printf("el1: %4d \n",el1);
		for (no1=1;no1<=2;no1++)
			{
			if (Structure.orientation == 1)
				{
				xx1 = noeud[element[el1].extremite[no1]].y;
				yy1 = noeud[element[el1].extremite[no1]].z;
				zz1 = noeud[element[el1].extremite[no1]].x;
				}
			if (Structure.orientation == 2)
				{
				xx1 = noeud[element[el1].extremite[no1]].z;
				yy1 = noeud[element[el1].extremite[no1]].x;
				zz1 = noeud[element[el1].extremite[no1]].y;
				}
			if (Structure.orientation == 3)
				{
				xx1 = noeud[element[el1].extremite[no1]].x;
				yy1 = noeud[element[el1].extremite[no1]].y;
				zz1 = noeud[element[el1].extremite[no1]].z;
				}
			trouve = 0;
			
			/*verify if the node is in a link*/
			for (li2=1;li2<=Structure.nb_liaison;li2++)
				{
				for (co2=1;co2<=Lien[li2].nb_liaison;co2++)
					{
					if ((Lien[li2].type[co2] == 'e') && (Lien[li2].structure[co2] == el1) && (Lien[li2].extremite[co2] == no1))
						{
						/*this node is already in a link : nothing to do*/
						trouve = 1;
						}
					}
				}
				
				
			/*because the node is not in a link we verify if the node is near a link*/
			if (trouve == 0)
				{
				for (li2=1;li2<=Structure.nb_liaison;li2++)
					{
					for (co2=1;co2<=Lien[li2].nb_liaison;co2++)
						{
						if (Structure.orientation == 1)
							{
							xx2 = noeud[Lien[li2].noeud[co2]].y;
							yy2 = noeud[Lien[li2].noeud[co2]].z;
							zz2 = noeud[Lien[li2].noeud[co2]].x;
							}
						if (Structure.orientation == 2)
							{
							xx2 = noeud[Lien[li2].noeud[co2]].z;
							yy2 = noeud[Lien[li2].noeud[co2]].x;
							zz2 = noeud[Lien[li2].noeud[co2]].y;
							}
						if (Structure.orientation == 3)
							{
							xx2 = noeud[Lien[li2].noeud[co2]].x;
							yy2 = noeud[Lien[li2].noeud[co2]].y;
							zz2 = noeud[Lien[li2].noeud[co2]].z;
							}
						distance = sqrt((xx2-xx1)*(xx2-xx1) + (yy2-yy1)*(yy2-yy1) + (zz2-zz1)*(zz2-zz1));
						if ((distance <= Structure.link_distance) && (trouve == 0))
							{
							/*this node is near a link*/
							trouve = 1;
							/*printf("5 Automatic linking el1: %4d no1: %4d li2: %4d co2: %4d\n",el1,no1,li2,co2);*/
							
							Lien[li2].nb_liaison = Lien[li2].nb_liaison + 1;
							/**********************************************/
							Lien[li2].structure = (int *) realloc(Lien[li2].structure, (1 + Lien[li2].nb_liaison) * sizeof(int));
							if (Lien[li2].structure    == NULL)
								{
								printf("Lien[li2].structure  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
							Lien[li2].extremite = (int *) realloc(Lien[li2].extremite, (1 + Lien[li2].nb_liaison) * sizeof(int));
							if (Lien[li2].extremite    == NULL)
								{
								printf("Lien[li2].extremite  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
							Lien[li2].noeud = (int *) realloc(Lien[li2].noeud, (1 + Lien[li2].nb_liaison) * sizeof(int));
							if (Lien[li2].noeud    == NULL)
								{
								printf("Lien[li2].noeud  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
							Lien[li2].type = (char *) realloc(Lien[li2].type, (1 + Lien[li2].nb_liaison) * sizeof(char));
							if (Lien[li2].type    == NULL)
								{
								printf("Lien[li2].type  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
							Lien[li2].type[Lien[li2].nb_liaison] = 'e';
							Lien[li2].structure[Lien[li2].nb_liaison] = el1;
							Lien[li2].extremite[Lien[li2].nb_liaison] = no1;
							Lien[li2].noeud[Lien[li2].nb_liaison] = element[el1].extremite[no1];
							}
						}
					}
				}
			
			/*because the node is not in a link and not near a link we verify if the node is near another node
			of element and we create a new link with 2 nodes*/
			if (trouve == 0)
				{
				for (pa2=1;pa2<=Structure.NbTypeelem;pa2++)
					{
					for (no2=1;no2<=2;no2++)
						{
						if (Structure.orientation == 1)
							{
							xx2 = noeud[element[pa2].extremite[no2]].y;
							yy2 = noeud[element[pa2].extremite[no2]].z;
							zz2 = noeud[element[pa2].extremite[no2]].x;
							}
						if (Structure.orientation == 2)
							{
							xx2 = noeud[element[pa2].extremite[no2]].z;
							yy2 = noeud[element[pa2].extremite[no2]].x;
							zz2 = noeud[element[pa2].extremite[no2]].y;
							}
						if (Structure.orientation == 3)
							{
							xx2 = noeud[element[pa2].extremite[no2]].x;
							yy2 = noeud[element[pa2].extremite[no2]].y;
							zz2 = noeud[element[pa2].extremite[no2]].z;
							}
						distance = sqrt((xx2-xx1)*(xx2-xx1) + (yy2-yy1)*(yy2-yy1) + (zz2-zz1)*(zz2-zz1));
						/*the next line is to avoid to link a node with it self*/
						if ((pa2==el1) && (no2==no1)) distance = 2.0 * Structure.link_distance;
						if ((distance <= Structure.link_distance) && (trouve == 0))
							{
							trouve = 1;
							Structure.nb_liaison  = Structure.nb_liaison + 1;
							/*printf("6 Automatic linking el1: %4d no1: %4d pa2: %4d no2: %4d  nb_link: %4d\n",el1,no1,pa2,no2,Structure.nb_liaison);*/
							if ( Structure.nb_liaison >= NBMAXLIAISON)
								{
								printf(" NBMAXLIAISON trop petit %4d < %4d \n",NBMAXLIAISON,Structure.nb_liaison );
								exit(0);
								}
							Lien[Structure.nb_liaison].nb_liaison = 2;
							/**********************************************/
  							Lien[Structure.nb_liaison].structure = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
							if (Lien[Structure.nb_liaison].structure    == NULL)
								{
								printf("Lien[Structure.nb_liaison].structure  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[Structure.nb_liaison].extremite = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
							if (Lien[Structure.nb_liaison].extremite    == NULL)
								{
								printf("Lien[Structure.nb_liaison].extremite  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[Structure.nb_liaison].noeud = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
							if (Lien[Structure.nb_liaison].noeud    == NULL)
								{
								printf("Lien[Structure.nb_liaison].noeud  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[Structure.nb_liaison].type = (char *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(char));
							if (Lien[Structure.nb_liaison].type    == NULL)
								{
								printf("Lien[Structure.nb_liaison].type  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
							Lien[Structure.nb_liaison].nb_liaison = 2;
							Lien[Structure.nb_liaison].type[1] = 'e';
							Lien[Structure.nb_liaison].structure[1] = el1;
							Lien[Structure.nb_liaison].extremite[1] = no1;
							Lien[Structure.nb_liaison].noeud[1] = element[el1].extremite[no1];
							Lien[Structure.nb_liaison].type[2] = 'e';
							Lien[Structure.nb_liaison].structure[2] = pa2;
							Lien[Structure.nb_liaison].extremite[2] = no2;
							Lien[Structure.nb_liaison].noeud[2] = element[pa2].extremite[no2];
							}
						}
					}
				}		
////////////////////////////////////////////////////////DEB COULISSSE///////////////////////////////////////////////////////////////////			
			/*because the node is not in a link and not near a link we verify if the node is near another extremity node
			of coulisse and we create a new link with 2 nodes*/
			if (trouve == 0)
				{
				for (pa2=1;pa2<=Structure.nombreCoulisses;pa2++)
					{
					for (no2=1;no2<=2;no2++)
						{
						if (Structure.orientation == 1)
							{
							xx2 = noeud[coulisse[pa2].extremite[no2]].y;
							yy2 = noeud[coulisse[pa2].extremite[no2]].z;
							zz2 = noeud[coulisse[pa2].extremite[no2]].x;
							}
						if (Structure.orientation == 2)
							{
							xx2 = noeud[coulisse[pa2].extremite[no2]].z;
							yy2 = noeud[coulisse[pa2].extremite[no2]].x;
							zz2 = noeud[coulisse[pa2].extremite[no2]].y;
							}
						if (Structure.orientation == 3)
							{
							xx2 = noeud[coulisse[pa2].extremite[no2]].x;
							yy2 = noeud[coulisse[pa2].extremite[no2]].y;
							zz2 = noeud[coulisse[pa2].extremite[no2]].z;
							}
						distance = sqrt((xx2-xx1)*(xx2-xx1) + (yy2-yy1)*(yy2-yy1) + (zz2-zz1)*(zz2-zz1));
printf("7 Automatic linking el1: %4d no1: %4d pa2: %4d no2: %4d  nb_link: %4d\n",el1,no1,pa2,no2,Structure.nb_liaison);
exit(0);
						if ((distance <= Structure.link_distance) && (trouve == 0))
							{
							trouve = 1;
							Structure.nb_liaison  = Structure.nb_liaison + 1;
							/*printf("8 Automatic linking el1: %4d no1: %4d pa2: %4d no2: %4d  nb_link: %4d\n",el1,no1,pa2,no2,Structure.nb_liaison);*/
							if ( Structure.nb_liaison >= NBMAXLIAISON)
								{
								printf(" NBMAXLIAISON trop petit %4d < %4d \n",NBMAXLIAISON,Structure.nb_liaison );
								exit(0);
								}
							Lien[Structure.nb_liaison].nb_liaison = 2;
							/**********************************************/
  							Lien[Structure.nb_liaison].structure = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
							if (Lien[Structure.nb_liaison].structure    == NULL)
								{
								printf("Lien[Structure.nb_liaison].structure  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[Structure.nb_liaison].extremite = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
							if (Lien[Structure.nb_liaison].extremite    == NULL)
								{
								printf("Lien[Structure.nb_liaison].extremite  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[Structure.nb_liaison].noeud = (int *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(int));
							if (Lien[Structure.nb_liaison].noeud    == NULL)
								{
								printf("Lien[Structure.nb_liaison].noeud  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
  							Lien[Structure.nb_liaison].type = (char *) malloc((1 + Lien[Structure.nb_liaison].nb_liaison) * sizeof(char));
							if (Lien[Structure.nb_liaison].type    == NULL)
								{
								printf("Lien[Structure.nb_liaison].type  1 = NULL  \n" );
								exit(0);
								}
							/**********************************************/
							Lien[Structure.nb_liaison].nb_liaison = 2;
							Lien[Structure.nb_liaison].type[1] = 'e';
							Lien[Structure.nb_liaison].structure[1] = el1;
							Lien[Structure.nb_liaison].extremite[1] = no1;
							Lien[Structure.nb_liaison].noeud[1] = element[el1].extremite[no1];
							Lien[Structure.nb_liaison].type[2] = 'c';
							Lien[Structure.nb_liaison].structure[2] = pa2;
							Lien[Structure.nb_liaison].extremite[2] = no2;
							Lien[Structure.nb_liaison].noeud[2] = coulisse[pa2].extremite[no2];
							}
						}
					}
				}		
////////////////////////////////////////////////////////FIN COULISSSE///////////////////////////////////////////////////////////////////			
			}
		}
	/* debut modifdp du 4 mars 2010*/
	printf("Number of links : %4d\n",Structure.nb_liaison);
	/* fin modifdp du 4 mars 2010*/
	for (pa1=1;pa1<=Structure.nb_liaison;pa1++)
		{
		/* debut modifdp du 22 mars 2010*/
		/*printf("link %4d nb_pt: %4d ",pa1,Lien[pa1].nb_liaison);*/
		printf("nb_pt: %4d ",Lien[pa1].nb_liaison);/**/
		/* fin modifdp du 22 mars 2010*/
		for (no1=1;no1<=Lien[pa1].nb_liaison;no1++)
			{
			//printf("str:%c %4d no:%4d  ",Lien[pa1].type[no1],Lien[pa1].structure[no1],Lien[pa1].extremite[no1]);
			if (Lien[pa1].type[no1] == 'p')
				{
				printf("pa: %4d nd:%4d ",Lien[pa1].structure[no1],Lien[pa1].extremite[no1]);
				}
			if (Lien[pa1].type[no1] == 'e')
				{
				printf("el: %4d nd:%4d ",Lien[pa1].structure[no1],Lien[pa1].extremite[no1]);
				}
			if (Lien[pa1].type[no1] == 'c')
				{
				printf("co: %4d nd:%4d ",Lien[pa1].structure[no1],Lien[pa1].extremite[no1]);
				}
			if (Lien[pa1].type[no1] == 'h')
				{
				printf("he: %4d nd:%4d ",Lien[pa1].structure[no1],Lien[pa1].extremite[no1]);
				}
			}
		printf("\n");
		}
	//exit(0);
	}
	
void initialisation_nb_fils()
	{
	/*initialisation des nb*********************************************/
	Structure.nb_fils 		= 0;
	/**********************************************/
  	h1x = (float *) malloc((1 + Structure.nb_fils) * sizeof(float));
	if (h1x    == NULL)
		{
		printf("h1x  = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	h2x = (float *) malloc((1 + Structure.nb_fils) * sizeof(float));
	if (h2x    == NULL)
		{
		printf("h2x  = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	h1y = (float *) malloc((1 + Structure.nb_fils) * sizeof(float));
	if (h1y    == NULL)
		{
		printf("h1y  = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	h2y = (float *) malloc((1 + Structure.nb_fils) * sizeof(float));
	if (h2y    == NULL)
		{
		printf("h2y  = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	/*initialisation des nb*********************************************/
	Structure.T90_nb_fils 		= 0;
	/**********************************************/
  	g1x = (float *) malloc((1 + Structure.T90_nb_fils) * sizeof(float));
	if (g1x    == NULL)
		{
		printf("g1x  = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	g2x = (float *) malloc((1 + Structure.T90_nb_fils) * sizeof(float));
	if (g2x    == NULL)
		{
		printf("g2x  = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	g1y = (float *) malloc((1 + Structure.T90_nb_fils) * sizeof(float));
	if (g1y    == NULL)
		{
		printf("g1y  = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	g2y = (float *) malloc((1 + Structure.T90_nb_fils) * sizeof(float));
	if (g2y    == NULL)
		{
		printf("g2y  = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	}
	
void initialisation_lien()
	{
	int pa,co,no_panneau,no_pan_hexa,no_extremite,no_element,no_coulisse;
	/*initialisation des liaisons 'lien' entre noeuds***********************************/
	for (pa=1;pa<=Structure.nb_liaison;pa++)
		{
		for (co=1;co<=Lien[pa].nb_liaison;co++)
			{
			if((Lien[pa].type[co] == 'p') || (Lien[pa].type[co] == 'P'))
				{
				no_panneau = Lien[pa].structure[co];
				no_extremite = Lien[pa].extremite[co];
				Lien[pa].noeud[co] = panneau[no_panneau].noeud_contour[no_extremite];
				}
			if((Lien[pa].type[co] == 'h') || (Lien[pa].type[co] == 'H'))
				{
				no_pan_hexa = Lien[pa].structure[co];
				no_extremite = Lien[pa].extremite[co];
				Lien[pa].noeud[co] = pan_hexa[no_pan_hexa].noeud_contour[no_extremite];
				}
			if((Lien[pa].type[co] == 'e') || (Lien[pa].type[co] == 'E'))
				{
				no_element = Lien[pa].structure[co];
				no_extremite = Lien[pa].extremite[co];
				Lien[pa].noeud[co] = element[no_element].extremite[no_extremite];
				}
			if((Lien[pa].type[co] == 'c') || (Lien[pa].type[co] == 'C'))
				{
				no_coulisse = Lien[pa].structure[co];
				no_extremite = Lien[pa].extremite[co];
				Lien[pa].noeud[co] = coulisse[no_coulisse].extremite[no_extremite];
				}
			}
		}
	}
	
	
void initialisation_min_max()
	{
	int no,pa;
	
	/*initialisation des min et des max*********************************************/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		if (panneau[pa].flag_dessin != 0)
			{
			minx = noeud[panneau[pa].noeud_contour[1]].x;	maxx = noeud[panneau[pa].noeud_contour[1]].x;
			miny = noeud[panneau[pa].noeud_contour[1]].y;	maxy = noeud[panneau[pa].noeud_contour[1]].y;
			minz = noeud[panneau[pa].noeud_contour[1]].z;	maxz = noeud[panneau[pa].noeud_contour[1]].z;
			}
		}
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{
		if (element[pa].flag_dessin != 0)
			{
			minx = noeud[element[pa].extremite[1]].x;	maxx = noeud[element[pa].extremite[1]].x;
			miny = noeud[element[pa].extremite[1]].y;	maxy = noeud[element[pa].extremite[1]].y;
			minz = noeud[element[pa].extremite[1]].z;	maxz = noeud[element[pa].extremite[1]].z;
			}
		}
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{
		if (coulisse[pa].flag_dessin != 0)
			{
			minx = noeud[coulisse[pa].extremite[1]].x;	maxx = noeud[coulisse[pa].extremite[1]].x;
			miny = noeud[coulisse[pa].extremite[1]].y;	maxy = noeud[coulisse[pa].extremite[1]].y;
			minz = noeud[coulisse[pa].extremite[1]].z;	maxz = noeud[coulisse[pa].extremite[1]].z;
			}
		}
	//printf("min max %f  %f %f  %f  %f  %f\n",minx,miny,minz,maxx,maxy,maxz);
 	/*minx = noeud[1].x;	maxx = noeud[1].x;
	miny = noeud[1].y;	maxy = noeud[1].y;
	minz = noeud[1].z;	maxz = noeud[1].z;
	for (no=1;no<=Structure.nb_total;no++)
		{
		if(noeud[no].x < minx) minx = noeud[no].x;
		if(noeud[no].x > maxx) maxx = noeud[no].x;
		if(noeud[no].y < miny) miny = noeud[no].y;
		if(noeud[no].y > maxy) maxy = noeud[no].y;
		if(noeud[no].z < minz) minz = noeud[no].z;
		if(noeud[no].z > maxz) maxz = noeud[no].z;
		}*/
	/*recherche des min et des max*********************************************/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		if (panneau[pa].flag_dessin != 0)
			{
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{
				if(noeud[panneau[pa].noeud_contour[no]].x < minx) minx = noeud[panneau[pa].noeud_contour[no]].x;
				if(noeud[panneau[pa].noeud_contour[no]].x > maxx) maxx = noeud[panneau[pa].noeud_contour[no]].x;
				if(noeud[panneau[pa].noeud_contour[no]].y < miny) miny = noeud[panneau[pa].noeud_contour[no]].y;
				if(noeud[panneau[pa].noeud_contour[no]].y > maxy) maxy = noeud[panneau[pa].noeud_contour[no]].y;
				if(noeud[panneau[pa].noeud_contour[no]].z < minz) minz = noeud[panneau[pa].noeud_contour[no]].z;
				if(noeud[panneau[pa].noeud_contour[no]].z > maxz) maxz = noeud[panneau[pa].noeud_contour[no]].z;
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{
		if (element[pa].flag_dessin != 0)
			{
			for (no=1;no<=2;no++)
				{
				if(noeud[element[pa].extremite[no]].x < minx) minx = noeud[element[pa].extremite[no]].x;
				if(noeud[element[pa].extremite[no]].x > maxx) maxx = noeud[element[pa].extremite[no]].x;
				if(noeud[element[pa].extremite[no]].y < miny) miny = noeud[element[pa].extremite[no]].y;
				if(noeud[element[pa].extremite[no]].y > maxy) maxy = noeud[element[pa].extremite[no]].y;
				if(noeud[element[pa].extremite[no]].z < minz) minz = noeud[element[pa].extremite[no]].z;
				if(noeud[element[pa].extremite[no]].z > maxz) maxz = noeud[element[pa].extremite[no]].z;
				}
			}
		}
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{
		if (coulisse[pa].flag_dessin != 0)
			{
			for (no=1;no<=2;no++)
				{
				if(noeud[coulisse[pa].extremite[no]].x < minx) minx = noeud[coulisse[pa].extremite[no]].x;
				if(noeud[coulisse[pa].extremite[no]].x > maxx) maxx = noeud[coulisse[pa].extremite[no]].x;
				if(noeud[coulisse[pa].extremite[no]].y < miny) miny = noeud[coulisse[pa].extremite[no]].y;
				if(noeud[coulisse[pa].extremite[no]].y > maxy) maxy = noeud[coulisse[pa].extremite[no]].y;
				if(noeud[coulisse[pa].extremite[no]].z < minz) minz = noeud[coulisse[pa].extremite[no]].z;
				if(noeud[coulisse[pa].extremite[no]].z > maxz) maxz = noeud[coulisse[pa].extremite[no]].z;
				}
			for (no=1;no<=coulisse[pa].nb_noeud ;no++)
				{
				if(noeud[coulisse[pa].noeud[no]].x < minx) minx = noeud[coulisse[pa].noeud[no]].x;
				if(noeud[coulisse[pa].noeud[no]].x > maxx) maxx = noeud[coulisse[pa].noeud[no]].x;
				if(noeud[coulisse[pa].noeud[no]].y < miny) miny = noeud[coulisse[pa].noeud[no]].y;
				if(noeud[coulisse[pa].noeud[no]].y > maxy) maxy = noeud[coulisse[pa].noeud[no]].y;
				if(noeud[coulisse[pa].noeud[no]].z < minx) minx = noeud[coulisse[pa].noeud[no]].z;
				if(noeud[coulisse[pa].noeud[no]].z > maxx) maxx = noeud[coulisse[pa].noeud[no]].z;
				}
















			}
		}

	/*precaution sur les min et des max*********************************************/
	if ((maxx == minx) && (maxy == miny) && (maxz == minz))
		{
		maxx = minx + 1.0;
		maxy = miny + 1.0;
		maxz = minz + 1.0;
		}	
	if ((maxx == minx) && (maxy == miny) && (maxz != minz))
		{
		maxx = minx + maxz - minz;
		maxy = miny + maxz - minz;
		}
	if ((maxx == minx) && (maxy != miny) && (maxz == minz))
		{
		maxx = minx + maxy - miny;
		maxz = minz + maxy - miny;
		}
	if ((maxx != minx) && (maxy == miny) && (maxz == minz))
		{
		maxy = miny + maxx - minx;
		maxz = minz + maxx - minx;
		}
	if ((maxx == minx) && (maxy != miny) && (maxz != minz))
		{
		maxx = minx + maxy - miny;
		}
	if ((maxx != minx) && (maxy == miny) && (maxz != minz))
		{
		maxy = miny + maxz - minz;
		}
	if ((maxx != minx) && (maxy != miny) && (maxz == minz))
		{
		maxz = minz + maxx - minx;
		}
		
		
	if ((maxx - minx) > (maxy - miny) && (maxx - minx) > (maxz - minz) ) ecartmax = maxx - minx;
	if ((maxy - miny) > (maxz - minz) && (maxy - miny) > (maxx - minx) ) ecartmax = maxy - miny;
	if ((maxz - minz) > (maxx - minx) && (maxz - minz) > (maxy - miny) ) ecartmax = maxz - minz;
	binx = minx - 0.05 * (maxx - minx);
	biny = miny - 0.05 * (maxy - miny);
	baxx = maxx + 0.05 * (maxx - minx);
	baxy = maxy + 0.05 * (maxy - miny);
	bcartmax = ecartmax;
	}
	
void creer_fichier_phobos()
	{
	/*cree un fichier *.mdg compatible avec le calcul MEF*/
	int i,j,mode;
	
	if (Structure.graphic == 1)
		{
		/*faire surface_de_fils si ce n est pas fait*/
		mode = GetMenuItemChecked(w[59]);
		if (mode == 0) nb_maille_total();
		}	
	if (Flag_Fichier_charge == 0)
		{
		printf(" selectionnez un fichier *.don :\n ");
		exit(0);
		}
	creer_fichier();
	}
		
void creer_fichier()
	{
	/*cree un fichier *.mdg compatible avec le calcul MEF*/
	char tonom[128];
	int i,j,mode;
  	FILE   *f2;
	
  	strcpy(tonom,fname1);
  	strcat(tonom,".mdg");
  	
  	f2 = fopen(tonom,"w");
	if (Structure.version == 1)    	fprintf(f2,"Fichier  %s.mdg\n",fname1);
	if (Structure.version == 2)    	fprintf(f2,"version_2  %s.mdg\n",fname1);
    	fprintf(f2,"IFREMER - Module Filiere - \n");
    	fprintf(f2,"DESCRIPTION DE LA STRUCTURE\n");
    	fprintf(f2,"Nombre de noeuds\n");
    	fprintf(f2,"%8d\n",Structure.nb_global);
    	fprintf(f2,"\n");
    	fprintf(f2,"Description des Noeuds\n");
  	for (i = 1 ; i<=Structure.nb_global  ; i++) 
  		{
    		fprintf(f2,"%5d",i);
		if (Structure.orientation == 1)
			{
    			fprintf(f2,"%12.6f ",noeud_global[i].z);
    			fprintf(f2,"%12.6f ",noeud_global[i].x);
    			fprintf(f2,"%12.6f ",noeud_global[i].y);
			}
		if (Structure.orientation == 2)
			{
    			fprintf(f2,"%12.6f ",noeud_global[i].y);
    			fprintf(f2,"%12.6f ",noeud_global[i].z);
    			fprintf(f2,"%12.6f ",noeud_global[i].x);
			}
		if (Structure.orientation == 3)
			{
    			fprintf(f2,"%12.6f ",noeud_global[i].x);
    			fprintf(f2,"%12.6f ",noeud_global[i].y);
    			fprintf(f2,"%12.6f ",noeud_global[i].z);
			}
    		fprintf(f2,"%5d",i);
    		fprintf(f2,"%5d ",noeud_global[i].type);
    		fprintf(f2,"%5d",noeud_global[i].type);
    		fprintf(f2,"\n");
  		}
    	fprintf(f2,"\n");
    	fprintf(f2,"Nombre d'elements\n");
    	fprintf(f2,"%5d\n",Structure.nb_barre);
    	fprintf(f2,"\n");
    	fprintf(f2,"Description des elements\n");
  	for (i = 1 ; i<=Structure.nb_barre  ; i++) 
  		{
    		fprintf(f2,"%5d",i);
    		fprintf(f2,"%5d ",total2global[barre[i].noeud[1]]);
    		fprintf(f2,"%5d ",total2global[barre[i].noeud[2]]);
    		fprintf(f2,"%8.7f ",barre[i].pro[1]);
    		fprintf(f2,"%8.7f ",barre[i].pro[2]);
    		fprintf(f2,"%5d ",barre[i].type);
    		/*fprintf(f2,"%6.5f ",barre[i].longueur_repos);*/
    		fprintf(f2,"\n");
  		}
  		
    	fprintf(f2,"\n");
    	fprintf(f2,"Nombre de coulisses\n");
    	fprintf(f2,"%5d\n",Structure.nombreCoulisses);
    	fprintf(f2,"\n");
    	fprintf(f2,"Description des coulisses\n");
  	for (i = 1 ; i<=Structure.nombreCoulisses  ; i++) 
  		{
    		fprintf(f2,"%5d",i);
    		fprintf(f2,"%5d ",total2global[coulisse[i].extremite[1]]);
    		fprintf(f2,"%5d ",total2global[coulisse[i].extremite[2]]);
     		fprintf(f2,"%5d ",coulisse[i].nb_noeud);
    		/*fprintf(f2,"%5d ",i);*/
    		fprintf(f2,"\n");
  		for (j = 1 ; j<=coulisse[i].nb_noeud  ; j++) 
  			{
    			fprintf(f2,"%5d ",total2global[coulisse[i].noeud[j]]);
      			if (16*(j/16) == j) fprintf(f2," \n");
  			}
      		if (16*((j-1)/16) != (j-1)) fprintf(f2," \n"); /*evite 2 \n consecutifs*/
    		fprintf(f2,"\n");
  		}
  		
    	fprintf(f2,"\n");
    	fprintf(f2,"Nombre de surfaces\n");
    	fprintf(f2,"%5d\n",Structure.nombreSurfaces);
    	fprintf(f2,"\n");
    	fprintf(f2,"Description des surfaces\n");
  	for (i = 1 ; i<=Structure.nombreSurfaces  ; i++) 
  		{
    		fprintf(f2,"%d ",i);
    		fprintf(f2,"%d ",total2global[surface[i].extremite[1]]);
    		fprintf(f2,"%d ",total2global[surface[i].extremite[2]]);
    		fprintf(f2,"%d ",total2global[surface[i].extremite[3]]);
    		fprintf(f2,"%f ",noeud[surface[i].extremite[1]].U); /*ATTENTION*/
    		fprintf(f2,"%f ",noeud[surface[i].extremite[1]].V); /*cf dessous*/
    		fprintf(f2,"%f ",noeud[surface[i].extremite[2]].U);
    		fprintf(f2,"%f ",noeud[surface[i].extremite[2]].V);
    		fprintf(f2,"%f ",noeud[surface[i].extremite[3]].U);
    		fprintf(f2,"%f ",noeud[surface[i].extremite[3]].V);
    		fprintf(f2,"%d ",surface[i].type);
    		fprintf(f2,"%d",surface[i].type);
    		fprintf(f2,"\n");
  		}
  	/*
  	attention a la facon dont U et V sont ecrit car precisionu depend de ca
  	dans chargement_mdgsta.c dans titus_2003
  	*/
    	fprintf(f2,"\n");
    	fprintf(f2,"Nombre de surfaces hexagonales\n");
    	fprintf(f2,"%5d\n",Structure.nombreSurfHexa);
    	fprintf(f2,"\n");
    	fprintf(f2,"Description des surfaces hexagonales\n");
  	for (i = 1 ; i<=Structure.nombreSurfHexa  ; i++) 
  		{
		/*
		printf("triangle %4d : ", i );
		printf("sommets %4d  %4d  %4d\n",total2global[surf_hexa[i].extremite[1]],total2global[surf_hexa[i].extremite[2]],total2global[surf_hexa[i].extremite[3]]);
		*/
    		fprintf(f2,"%5d",i);
    		fprintf(f2,"%5d",total2global[surf_hexa[i].extremite[1]]);
    		fprintf(f2,"%5d",total2global[surf_hexa[i].extremite[2]]);
    		fprintf(f2,"%5d",total2global[surf_hexa[i].extremite[3]]);
    		fprintf(f2,"%8.2f",noeud[surf_hexa[i].extremite[1]].U);
    		fprintf(f2,"%8.2f",noeud[surf_hexa[i].extremite[1]].V);
    		fprintf(f2,"%8.2f",noeud[surf_hexa[i].extremite[2]].U);
    		fprintf(f2,"%8.2f",noeud[surf_hexa[i].extremite[2]].V);
    		fprintf(f2,"%8.2f",noeud[surf_hexa[i].extremite[3]].U);
    		fprintf(f2,"%8.2f",noeud[surf_hexa[i].extremite[3]].V);
    		fprintf(f2,"%5d",surf_hexa[i].type);
    		fprintf(f2,"%5d",surf_hexa[i].type);
    		fprintf(f2,"\n");
  		}
    	fprintf(f2,"\n");

    	fprintf(f2,"\n");
    	fprintf(f2,"Bar winch number\n");
    	fprintf(f2,"%5d\n",Structure.nb_barre_winch);
    	fprintf(f2,"\n");
    	fprintf(f2,"Description of winch bars\n");
  	for (i = 1 ; i<=Structure.nb_barre_winch  ; i++) 
  		{
    		fprintf(f2,"%5d",i);
    		fprintf(f2,"%5d ",total2global[barre_winch[i].noeud[1]]);
    		fprintf(f2,"%5d ",total2global[barre_winch[i].noeud[2]]);
    		fprintf(f2,"%8.7f ",barre_winch[i].pro[1]);
    		fprintf(f2,"%8.7f ",barre_winch[i].pro[2]);
    		fprintf(f2,"%5d ",barre_winch[i].type);
    		/*fprintf(f2,"%6.5f ",barre_winch[i].longueur_repos);*/
    		fprintf(f2,"\n");
  		}
  		
   	fprintf(f2,"\n");
    	fprintf(f2,"Balls number\n");
    	fprintf(f2,"%5d\n",Ball.nb);
    	fprintf(f2,"\n");
    	fprintf(f2,"Description of balls\n");
	printf("Ball.nb %4d \n", Ball.nb);
  	for (i = 1 ; i<=Ball.nb  ; i++) /**/
  		{
    		fprintf(f2,"%5d",i);
    		fprintf(f2,"%5d ",total2global[Ball.noeud[i]]);
    		fprintf(f2,"%8.7f ",Ball.birth_time[i]);
    		fprintf(f2,"%8.7f ",Ball.stiffness[i]);
    		fprintf(f2,"%8.7f ",Ball.radius[i]);
    		fprintf(f2,"%5d ",Ball.type[i]);
    		fprintf(f2,"%8.7f ",Ball.ini_speed_x[i]);
    		fprintf(f2,"%8.7f ",Ball.ini_speed_y[i]);
    		fprintf(f2,"%8.7f ",Ball.ini_speed_z[i]);
    		fprintf(f2,"\n");
  		}
  		
    	fclose(f2);
    	
    	if (Ball.nb != 0)
    		{
		printf("the last ball is created at %f \n",Ball.birth_time[Ball.nb]);
		printf("the total stockage time %f \n",Numerique.Finstockage);
		}    	
    	
  	Flag_Fichier_cree_mdg = 1;
  	printf("The file %s is created\n",tonom);
	if (Structure.graphic == 1)
		{
		SetMenuItemChecked(w[22],1);
		}
	}
	
	
void Genere_ps()
	{
	flag_ps = TRUE;
	ClearDrawArea();
    	printf("fname1 = %s \n",fname1);
	mode_portrait = TRUE;
	Chk_ps_open();
	dessiner();
	Chk_ps_close();
	flag_ps = FALSE;
	}


void initialisation_ps()
	{
	flag_ps  = FALSE; 	/* sortie a l'ecran seulement */
	fic_ps = NULL; 		/* Fichier PostSript non ouvert */
	hauteur_police_ps = 6;
	largeur_police_ps = 2;
	hauteur_police_ps = 12;
	largeur_police_ps = 4;
	mode_portrait = FALSE;
	epaisseur_trait_ps = 0.1;
	flag_delta_carac = FALSE;
	flag_ortho_norm = TRUE;	/*sortie papier postscript a l echelle*/

	fic_ps=NULL;
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
	
void lecture_des()
	{
	/*chargement du fichier dessin.txt, qui contient les ordres de dessin des elements
	si 1 on dessne si 0 on ne dessine pas*/
	
/* debut modifdp du 4 mars 2010*/
	/*char c;
	int pa,itmp;
	FILE *fic;

	fic = fopen("dessin.txt","r");
  	if (fic == NULL) 
  		{
    		printf(" \n");
    		printf("fichier dessin.txt n existe pas ?\n");
    		exit(0);
  		}*/
    	
	char c,tonom[200];
	int pa,itmp;
	FILE *fic;

	strcpy(tonom,fname1);
 	strcat(tonom,".des");
	fic = fopen(tonom,"r");
	/*fic = fopen("dessin.txt","r");*/
  	if (fic == NULL) 
  		{
    		printf(" \n");
    		printf("a fichier %s n existe pas ?\n",tonom);
    		exit(0);
  		} 
/* fin modifdp du 4 mars 2010*/
    	for (pa=1;pa<=Structure.NbTypesurf;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		itmp = fscanf(fic,"%d\n",&panneau[pa].flag_dessin);
    		}
    	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		itmp = fscanf(fic,"%d\n",&pan_hexa[pa].flag_dessin);
    		}
    	for (pa=1;pa<=Structure.NbTypeelem;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		itmp = fscanf(fic,"%d\n",&element[pa].flag_dessin);
		}
    	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		itmp = fscanf(fic,"%d\n",&coulisse[pa].flag_dessin);
    		}
    	for (pa=1;pa<=Structure.nb_winch;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		itmp = fscanf(fic,"%d\n",&winch[pa].flag_dessin);
    		}

    	for (pa=1;pa<=Structure.nb_barre;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		itmp = fscanf(fic,"%d\n",&barre[pa].flag_dessin);
    		}
    	for (pa=1;pa<=Structure.nb_global;pa++)
    		{
    		do  c=fgetc(fic); while (c !=':'); 
    		itmp = fscanf(fic,"%d\n",&noeud[pa].flag_dessin);
		}
	fclose(fic);
	}


int seam_coordinates(int pa, int no, double U1, double U2, double U3, double U4, double V1, double V2, double V3, double V4)
	{
	int p1,p2,p3;
	double deno,UO,VO,surface,p1u,p2u,p3u,p1v,p2v,p3v,p1x,p2x,p3x,p1y,p2y,p3y,p1z,p2z,p3z,alpha,beta;
	double p0u,p0v;
	
	/*intersection 12 and 34*/
	deno = V4*U2-V4*U1-V3*U2+V3*U1+V2*U3-V2*U4-V1*U3+V1*U4;
	if (deno == 0)
		{
		UO = U2;
		VO = V2;
		}
	else
		{
		UO = (-U4*V3*U2+U4*V3*U1+U3*V4*U2+U4*V1*U2-U4*U1*V2-U3*V1*U2-U3*V4*U1+U3*U1*V2)/deno;
		VO = (-V4*U1*V2-V1*U3*V4+V2*U3*V4+V4*V1*U2+V3*U1*V2-V2*V3*U4-V3*V1*U2+V1*V3*U4)/deno;
		}
	noeud_seam[panneau[pa].noeud_contour[no]].U = UO;
	noeud_seam[panneau[pa].noeud_contour[no]].V = VO;
	/*find the first 3 points not aligned, called the reference points: p1 p2 p3 */

	p1 = 1; /*no - 1*/ 
	p2 = 2; /*no*/
	p3 = 2; /*no*/
	if (no == 1) p1 = panneau[pa].nb_noeud_contour; else  p1 = no-1;
	p2 = no;
	p3 = no;
	p1u = noeud[panneau[pa].noeud_contour[p1]].U;	p1v = noeud[panneau[pa].noeud_contour[p1]].V;
	p1x = noeud[panneau[pa].noeud_contour[p1]].x;						
	p1y = noeud[panneau[pa].noeud_contour[p1]].y;						
	p1z = noeud[panneau[pa].noeud_contour[p1]].z;	
	p2u = noeud[panneau[pa].noeud_contour[p2]].U;	p2v = noeud[panneau[pa].noeud_contour[p2]].V;
	p2x = noeud[panneau[pa].noeud_contour[p2]].x;						
	p2y = noeud[panneau[pa].noeud_contour[p2]].y;						
	p2z = noeud[panneau[pa].noeud_contour[p2]].z;	
	do
		{
		p3++;
		if (p3 > panneau[pa].nb_noeud_contour) p3 = 1;
		p3u = noeud[panneau[pa].noeud_contour[p3]].U;	p3v = noeud[panneau[pa].noeud_contour[p3]].V;
		p3x = noeud[panneau[pa].noeud_contour[p3]].x;						
		p3y = noeud[panneau[pa].noeud_contour[p3]].y;						
		p3z = noeud[panneau[pa].noeud_contour[p3]].z;	
		surface = fabs((p2u-p1u)*(p3v-p1v) - (p2v-p1v)*(p3u-p1u)); /*surfec of the triangle p1 p2 p3 in nb of meshes*/
		}
	while (surface == 0.0);
	printf("panel %d surface %lf p3 = %d  \n",pa,surface,p3);/**/
	/*for each points 0 (not in the 3 reference points: 1 2 3) calculate alpha and beta such as 10 = alpha 12 + beta 13*/
	p0u = UO;	p0v = VO;
	alpha = (-(p3u - p1u)*(p0v - p1v)+(p0u - p1u)*(p3v - p1v))/(-(p2v - p1v)*(p3u - p1u)+(p2u - p1u)*(p3v - p1v));
	beta =  (-(p2v - p1v)*(p0u - p1u)+(p2u - p1u)*(p0v - p1v))/(-(p2v - p1v)*(p3u - p1u)+(p2u - p1u)*(p3v - p1v));
	/*for each points (not in the 3 reference points) calculate the cartesians coordinates*/
	noeud_seam[panneau[pa].noeud_contour[no]].x = p1x + alpha * (p2x - p1x) + beta * (p3x - p1x);
	noeud_seam[panneau[pa].noeud_contour[no]].y = p1y + alpha * (p2y - p1y) + beta * (p3y - p1y);
	noeud_seam[panneau[pa].noeud_contour[no]].z = p1z + alpha * (p2z - p1z) + beta * (p3z - p1z);
	printf("   no %d alpha %lf beta %lf  \n",no,alpha,beta);/**/
	printf("x %lf %lf %lf seamx %lf %lf %lf\n",noeud[panneau[pa].noeud_contour[no]].x,noeud[panneau[pa].noeud_contour[no]].y,noeud[panneau[pa].noeud_contour[no]].z,noeud_seam[panneau[pa].noeud_contour[no]].x,noeud_seam[panneau[pa].noeud_contour[no]].y,noeud_seam[panneau[pa].noeud_contour[no]].z);/**/
	}
	
void homot_file(char *source_file, char *target_file, double homot_ratio)
	{
	/*modify the file source_file in target_file such as there is a homothety between the two files
	the homothety is defined by the ratio homot_ratio
	this function is very similar to modify_file_5 in nerzh directory*/
	
  	FILE	*fic_source,*fic_target;
	char 	source_file_temp[256],target_file_temp[256],c,t1[256],tonom_csh[128];
	char 	chaine[] = "                                               ";
	char 	*buffer;
	int 	i,j,mode,pa,no,zc,zi,paa,noo,temp_i,temp_j,tri,trouve,ni;
	int	n1l,n2l,n3l,n1g,n2g,n3g,step_vect,itmp;
	float 	temp_f,U_stepp,UU1,VV1,XX1,YY1,ZZ1,UU2,VV2,XX2,YY2,ZZ2,UU3,VV3,XX3,YY3,ZZ3,XXp,YYp,ZZp;
	float	alpha,beta,denom,um,vm;
	
	/*printf("%s 				%s\n","source_file ",source_file);

	/*code 0: no modification, it is just a copy*/  	
	
	strcpy(source_file_temp,source_file);
	strcat(source_file_temp,".don");
	fic_source = fopen(source_file_temp,"r");
	strcpy(target_file_temp,target_file);
	strcat(target_file_temp,".don");
	fic_target = fopen(target_file_temp,"w");
	lecture_chaine(fic_source,chaine);		
    	fprintf(fic_target,"%s ",chaine);
	i = strlen(chaine);
	if (strcmp(chaine,"version_2") == 0)	Structure.version = 2;
	if (strcmp(chaine,"version_3") == 0)	Structure.version = 3;

	/*orientation du dessin****************************************/
    	do
    		{
    		c=fgetc(fic_source);
    		fprintf(fic_target,"%c",c);
    		}
    	while (c !=':'); 
    	itmp = fscanf(fic_source,"%d\n",&Structure.orientation);
	if ( (Structure.orientation != 1) && (Structure.orientation != 2) && (Structure.orientation != 3))
		{
		printf(" Structure.orientation %4d doit etre = a 1 2 ou 3  \n",Structure.orientation );
		exit(0);
		}
    	fprintf(fic_target,"%d\n",Structure.orientation);
	/*panneaux*****************************************************/
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
    	itmp = fscanf(fic_source,"%d\n",&Structure.NbTypesurf);
    	fprintf(fic_target,"%d\n",Structure.NbTypesurf);
	
	step_vect = 0;
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
	    	itmp = fscanf(fic_source,"%d\n",&panneau[pa].nb_noeud_contour);
    		fprintf(fic_target,"%d\n",panneau[pa].nb_noeud_contour);
		buffer = fgets(t1,256,fic_source);
    		fprintf(fic_target,"%s ",t1);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{

			itmp = fscanf(fic_source,"%d",&temp_i);	fprintf(fic_target,"%d ",temp_i);
			itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f*homot_ratio);/*x coordinate*/			
			itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f*homot_ratio);/*y coordinate*/				
			itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f*homot_ratio);/*z coordinate*/				
			itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f*homot_ratio);/*U coordinate*/				
			itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f*homot_ratio);/*V coordinate*/				
			itmp = fscanf(fic_source,"%d",&temp_i);	fprintf(fic_target,"%d ",temp_i);
			itmp = fscanf(fic_source,"%d",&temp_i);	fprintf(fic_target,"%d \n",temp_i);
			}
		buffer = fgets(t1,256,fic_source);     		fprintf(fic_target,"%s ",t1);
		buffer = fgets(t1,256,fic_source);     		fprintf(fic_target,"%s ",t1);
		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%f\n",&panneau[pa].raideur_traction);	fprintf(fic_target,"%f\n",panneau[pa].raideur_traction);
   		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%f\n",&panneau[pa].raideur_compression);	fprintf(fic_target,"%f\n",panneau[pa].raideur_compression);
   		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%f\n",&panneau[pa].raideur_ouverture);	fprintf(fic_target,"%f\n",panneau[pa].raideur_ouverture);
 		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%f\n",&panneau[pa].longueur_repos);	fprintf(fic_target,"%f\n",panneau[pa].longueur_repos);
  		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%f\n",&panneau[pa].rho);	fprintf(fic_target,"%f\n",panneau[pa].rho);
    		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%f\n",&panneau[pa].diam_hydro);	fprintf(fic_target,"%f\n",panneau[pa].diam_hydro);
		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%f\n",&panneau[pa].largeurnoeud);	fprintf(fic_target,"%f\n",panneau[pa].largeurnoeud);
    		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%f\n",&panneau[pa].cdnormal);	fprintf(fic_target,"%f\n",panneau[pa].cdnormal);
    		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%f\n",&panneau[pa].ftangent);	fprintf(fic_target,"%f\n",panneau[pa].ftangent);
    		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%f\n",&panneau[pa].pas_maillage);	fprintf(fic_target,"%f\n",panneau[pa].pas_maillage);
    		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%d\n",&panneau[pa].type_noeud);	fprintf(fic_target,"%d\n",panneau[pa].type_noeud);
    		do  
			{
			c=fgetc(fic_source); 
    			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
    		itmp = fscanf(fic_source,"%d\n",&panneau[pa].type_maillage);	fprintf(fic_target,"%d\n",panneau[pa].type_maillage);
   		}
	fprintf(fic_target,"\n");
   		
	/*panneaux hexagonaux*******************************************/
	do  
		{
		c=fgetc(fic_source); 
		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 	
    	itmp = fscanf(fic_source,"%d\n",&Structure.NbTypesurf_hexa);	fprintf(fic_target,"%d\n",Structure.NbTypesurf_hexa);
    	if (Structure.NbTypesurf_hexa != 0)
    		{
		printf("nb of hexagonal panels must be equal to 0 not to %d \n",Structure.NbTypesurf_hexa);
		exit(0);
    		}
	fprintf(fic_target,"\n");
		
	/*elements*****************************************************/
	do  
		{
		c=fgetc(fic_source); 
		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 	

    	itmp = fscanf(fic_source,"%d\n",&Structure.NbTypeelem);	fprintf(fic_target,"%d\n",Structure.NbTypeelem);
	fprintf(fic_target,"\n");
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		fprintf(fic_target,"\n");
		for (no=1;no<=2;no++)
			{
			itmp = fscanf(fic_source,"%d",&temp_i);	fprintf(fic_target,"%d ",temp_i);
			itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f*homot_ratio);/*x coordinate*/
			itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f*homot_ratio);/*y coordinate*/
			itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f*homot_ratio);/*z coordinate*/
			itmp = fscanf(fic_source,"%d",&temp_i);	fprintf(fic_target,"%d\n",temp_i);
			}
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f);/*tension stiffness*/
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f);/*compression stiffness*/
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f*homot_ratio);/*unstretched length*/
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f);/*density*/
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f*homot_ratio);/*diameter*/
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f);/*cd*/
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target,"%f ",temp_f);/*f*/
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		itmp = fscanf(fic_source,"%d",&temp_i);	fprintf(fic_target,"%d ",temp_i);/*nb bars*/
		do  
			{
			c=fgetc(fic_source); 
			fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 	
		itmp = fscanf(fic_source,"%d",&temp_i);	fprintf(fic_target,"%d\n",temp_i);/*node type*/
		}
		
	/*coulisses *******************************************/
	do  
		{
		c=fgetc(fic_source); 
		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 	
    	itmp = fscanf(fic_source,"%d\n",&Structure.nombreCoulisses);	fprintf(fic_target,"%d\n",Structure.nombreCoulisses);
    	if (Structure.nombreCoulisses != 0)
    		{
		printf("nb of coulisse must be equal to 0 not to %d \n",Structure.nombreCoulisses);
		exit(0);
    		}
	fprintf(fic_target,"\n");
		

	/*liaisons*****************************************************/
	do  c=fgetc(fic_source); while (c !=':');itmp = fscanf(fic_source,"%d\n",&Structure.nb_liaison); 
	for (pa=1;pa<=Structure.nb_liaison;pa++)
		{
		/*printf("pa %d \n",pa);*/
    		do  c=fgetc(fic_source); while (c !=':'); itmp = fscanf(fic_source,"%d",&Lien[pa].nb_liaison);
		for (i=1;i<=Lien[pa].nb_liaison;i++)
			{
			/*printf("i %d \n",i);*/
			do  
				{
				c=fgetc(fic_source); 
				}
			while (c ==' '); 
    			do  c=fgetc(fic_source); while (c !=':'); itmp = fscanf(fic_source,"%d",&temp_i);
   			do  c=fgetc(fic_source); while (c !=':'); itmp = fscanf(fic_source,"%d",&temp_i);
   			}
		}
    	
    	fprintf(fic_target,"Nombre de liaison : %d\n",Structure.nb_liaison);
	for (pa=1;pa<=Structure.nb_liaison;pa++)
		{
    		fprintf(fic_target,"nb_pt : ");	fprintf(fic_target,"%4d ",Lien[pa].nb_liaison);
		for (ni=1;ni<=Lien[pa].nb_liaison;ni++)
			{
			if (Lien[pa].type[ni] == 'p')	fprintf(fic_target,"pa: ");
			if (Lien[pa].type[ni] == 'e')	fprintf(fic_target,"el: ");
			if (Lien[pa].type[ni] == 'c')	fprintf(fic_target,"co: ");
			if (Lien[pa].type[ni] == 'h')	fprintf(fic_target,"he: ");
			fprintf(fic_target,"%4d ",Lien[pa].structure[ni]);
    			fprintf(fic_target,"nd: ");	fprintf(fic_target,"%4d ",Lien[pa].extremite[ni]);
			/*
			Lien[pa].type[ni] = Lien[pa].type[ni];
    			Lien[pa].structure[ni] = Lien[pa].structure[ni];
    			*/
    			}
		fprintf(fic_target,"\n");
		}
	
	/*ordre de maillage***************************************************/	
	
	Structure.nb_ordre_objet = Structure.NbTypesurf + Structure.NbTypeelem + Structure.nombreCoulisses + Structure.NbTypesurf_hexa + Structure.nb_winch;
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	for (i=1;i<=Structure.nb_ordre_objet;i++)
		{ 
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
		itmp = fscanf(fic_source,"%d",&temp_i);	fprintf(fic_target," %4d ",temp_i);
		}
	fprintf(fic_target,"\n");
    	
    	/*types of nodes********************************************************/
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	itmp = fscanf(fic_source,"%d",&temp_i);	fprintf(fic_target," %4d ",temp_i);
	for (i=1;i<=temp_i;i++)
		{ 
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
		itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':');
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*homot_ratio*homot_ratio);/*masse*/
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*homot_ratio*homot_ratio);
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*homot_ratio*homot_ratio);
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':');
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*homot_ratio*homot_ratio);/*added masse*/
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*homot_ratio*homot_ratio);
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*homot_ratio*homot_ratio);
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':');
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*pow(homot_ratio,3.0/2.0));/*length*/
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*pow(homot_ratio,3.0/2.0));
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*pow(homot_ratio,3.0/2.0));
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':');
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f);/*cd*/
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f);
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f);
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':');
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*homot_ratio*homot_ratio);/*extern forces*/
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*homot_ratio*homot_ratio);
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f*homot_ratio*homot_ratio);
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
		itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);/*displacement*/
		itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
		itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':');
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f);/*limits*/
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f);
		itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f",temp_f);
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
		itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);/*senses of limits*/
		itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
		itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
		do  
			{
			c=fgetc(fic_source); 
	    		fprintf(fic_target,"%c",c);
			}
		while (c !=':'); 
		itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);/*symmetry*/
		itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
		itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
		}
	fprintf(fic_target,"\n");

	/*ENVIRONNEMENT NUMERIQUE*/
	do  	
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d\n",temp_j);
	
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f\n",&temp_f);	fprintf(fic_target," %f\n",temp_f);

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':');
	itmp = fscanf(fic_source,"%f\n",&temp_f);	fprintf(fic_target," %f\n",temp_f);
	
	/*sortie texte distance*****************************************************/
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
	
	if (Sortie_texte.nb_distance != 0)
		{
		for (pa=1;pa<=Sortie_texte.nb_distance;pa++)
			{
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
			}
		}

	
	/*sortie texte d effort*****************************************************/
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
	
	if (Sortie_texte.nb_effort != 0)
		{
		for (pa=1;pa<=Sortie_texte.nb_effort;pa++)
			{
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
			}
		}

	
	/*sortie texte tension_element*****************************************************/
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
	
	if (Sortie_texte.nb_tension_element != 0)
		{
		for (pa=1;pa<=Sortie_texte.nb_tension_element;pa++)
			{
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
			}
		}

	
	/*sortie texte tension_coulisse*****************************************************/
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
	
	if (Sortie_texte.nb_tension_coulisse != 0)
		{
		for (pa=1;pa<=Sortie_texte.nb_tension_coulisse;pa++)
			{
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
			}
		}

	
	/*sortie texte position*****************************************************/
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
	
	if (Sortie_texte.nb_position != 0)
		{
		for (pa=1;pa<=Sortie_texte.nb_position;pa++)
			{
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			do  
				{
				c=fgetc(fic_source); 
		    		fprintf(fic_target,"%c",c);
				}
			while (c !=':'); 
			itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
			}
		}

	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=':'); 
	itmp = fscanf(fic_source,"%d",&temp_j);	fprintf(fic_target," %4d",temp_j);
	
	
	/*input and output*/
	
	
    	do  
		{
		c=fgetc(fic_source); 
    		fprintf(fic_target,"%c",c);
		}
	while (c !=EOF); 
	/**/
	
    	fclose(fic_target);
    	fclose(fic_source);
    	
    	
	strcpy(source_file_temp,source_file);
	strcat(source_file_temp,".sta");
	
	if(source_file_temp[0])
		{
		/*source.sta file exists*/
		fic_source = fopen(source_file_temp,"r");
		strcpy(target_file_temp,target_file);
		strcat(target_file_temp,".sta");
		/*fic_target = fopen(target_file_temp,"w");*/
	
	
	
	    	/*fclose(fic_target);*/
    		fclose(fic_source);
		}
	else
		{
		/*source.sta file dont exist*/
		}
	}
	
void produit_vect(double xx1, double yy1, double zz1, double xx2, double yy2, double zz2, double *xx3, double *yy3, double *zz3)
	{
	*xx3 = yy1*zz2 - zz1*yy2;
	*yy3 = zz1*xx2 - xx1*zz2;
	*zz3 = xx1*yy2 - yy1*xx2;
	}


void produit_vect2(double vect_1[4], double vect_2[4], double *xx3, double *yy3, double *zz3)
	{
	*xx3 = vect_1[2]*vect_2[3] - vect_1[3]*vect_2[2];
	*yy3 = vect_1[3]*vect_2[1] - vect_1[1]*vect_2[3];
	*zz3 = vect_1[1]*vect_2[2] - vect_1[2]*vect_2[1];
	}


void produit_vect3(double vect_1[4], double vect_2[4], double *vect_3)
	{
	vect_3[1] = vect_1[2]*vect_2[3] - vect_1[3]*vect_2[2];
	vect_3[2] = vect_1[3]*vect_2[1] - vect_1[1]*vect_2[3];
	vect_3[3] = vect_1[1]*vect_2[2] - vect_1[2]*vect_2[1];
	}

void add_vect(double vect_1[4], double vect_2[4], double *vect_3)
	{
	vect_3[1] = vect_1[1] + vect_2[1];
	vect_3[2] = vect_1[2] + vect_2[2];
	vect_3[3] = vect_1[3] + vect_2[3];
	}

void add_vect_6(double vect_1[4], double vect_2[4], double *vect_3)
	{
	int zi;
   	for (zi = 1 ; zi<= 6; zi++) 
  		{
		vect_3[zi] = vect_1[zi] + vect_2[zi];
		}
	}

void add_vect_12(double vect_1[4], double vect_2[4], double *vect_3)
	{
	int zi;
   	for (zi = 1 ; zi<= 12; zi++) 
  		{
		vect_3[zi] = vect_1[zi] + vect_2[zi];
		}
	}

void produit_scal_vect(double scal, double vect_1[4], double *vect_2)
	{
	vect_2[1] = vect_1[1]*scal;
	vect_2[2] = vect_1[2]*scal;
	vect_2[3] = vect_1[3]*scal;
	}

void produit_scal_vect_12(double scal, double vect_1[13], double *vect_2)
	{
	int zi;
   	for (zi = 1 ; zi<= 12; zi++) 
  		{
		vect_2[zi] = vect_1[zi]*scal;
		}
	}

void produit_scal_vect_6(double scal, double vect_1[13], double *vect_2)
	{
	int zi;
   	for (zi = 1 ; zi<= 6; zi++) 
  		{
		vect_2[zi] = vect_1[zi]*scal;
		}
	}

double produit_scal(double vect_1[4], double vect_2[4])
	{
	double prod_scal;
	
	prod_scal = vect_1[1]*vect_2[1] + vect_1[2]*vect_2[2] + vect_1[3]*vect_2[3];
	return prod_scal;
	}
	
void base1(double angl1,int axeangl1,double angl2,int  axeangl2,int  nbcol,double *vect)

/* Changement de base du vecteur vect de dimension nbcol
  Rotation de angl1 autour de l'axe axeangl1 puis rotation de angl2  autour de l'axe axeangl2.
  Si axeangl = 1 : rotation autour de l axe des X
  Si axeangl = 2 : rotation autour de l axe des Y
  Si axeangl = 3 : rotation autour de l axe des Z*/

{
  int zi,zj,zk;
  double    Lamda[10][10], inter[10], rota[4][4], rotb[4][4], rotc[4][4];

  /*premiere matrice de rotation*/
  if (axeangl1 == 1)
  {
    rota[1][1] =   1.0;         rota[1][2] =   0.0;         rota[1][3] =   0.0;
    rota[2][1] =   0.0;         rota[2][2] =   cos(angl1);  rota[2][3] =   sin(angl1);
    rota[3][1] =   0.0;         rota[3][2] = - sin(angl1);  rota[3][3] =   cos(angl1);
  }
  if (axeangl1 == 2)
  {
    rota[1][1] =   cos(angl1);  rota[1][2] =   0.0;         rota[1][3] = - sin(angl1);
    rota[2][1] =   0.0;         rota[2][2] =   1.0;         rota[2][3] =   0.0;
    rota[3][1] =   sin(angl1);  rota[3][2] =   0.0;         rota[3][3] =   cos(angl1);
  }
  if (axeangl1 == 3)
  {
    rota[1][1] =   cos(angl1);  rota[1][2] =   sin(angl1);  rota[1][3] =   0.0;
    rota[2][1] = - sin(angl1);  rota[2][2] =   cos(angl1);  rota[2][3] =   0.0;
    rota[3][1] =   0.0;         rota[3][2] =   0.0;         rota[3][3] =   1.0;
  }
  
  /*seconde matrice de rotation*/
  if (axeangl2 == 1)
  {
    rotb[1][1] =   1.0;         rotb[1][2] =   0.0;         rotb[1][3] =   0.0;
    rotb[2][1] =   0.0;         rotb[2][2] =   cos(angl2);  rotb[2][3] =   sin(angl2);
    rotb[3][1] =   0.0;         rotb[3][2] = - sin(angl2);  rotb[3][3] =   cos(angl2);
  }
  if (axeangl2 == 2)
  {
    rotb[1][1] =   cos(angl2);  rotb[1][2] =   0.0;         rotb[1][3] = - sin(angl2);
    rotb[2][1] =   0.0;         rotb[2][2] =   1.0;         rotb[2][3] =   0.0;
    rotb[3][1] =   sin(angl2);  rotb[3][2] =   0.0;         rotb[3][3] =   cos(angl2);
  }
  if (axeangl2 == 3)
  {
    rotb[1][1] =   cos(angl2);  rotb[1][2] =   sin(angl2);  rotb[1][3] =   0.0;
    rotb[2][1] = - sin(angl2);  rotb[2][2] =   cos(angl2);  rotb[2][3] =   0.0;
    rotb[3][1] =   0.0;         rotb[3][2] =   0.0;         rotb[3][3] =   1.0;
  }
  
  /*mise a zero de la matrice rotation elementaire*/
  for (zi = 1 ; zi<= 3 ; zi++)
  {
    for (zj = 1 ; zj<= 3 ; zj++) 
    {
      rotc[zi][zj] = 0.0;
    }
  }

  /*matrice rotation elementaire*/
  for (zi = 1 ; zi<= 3 ; zi++)
  {
    for (zj = 1 ; zj<= 3 ; zj++) 
    {
      for (zk = 1 ; zk<= 3 ; zk++) 
      {
        rotc[zi][zj] += rotb[zk][zj] * rota[zi][zk];
      }
    }
  }

  /*mise a zero de la matrice rotation globale*/
  for (zi = 1 ; zi<= nbcol ; zi++)
  {
    for (zj = 1 ; zj<= nbcol ; zj++) 
    {
      Lamda[zi][zj] = 0.0;
    }
  }

  /*matrice rotation globale*/
  for (zi = 1 ; zi<= nbcol/3 ; zi++)
  {
    for (zj = 1 ; zj<= 3 ; zj++) 
    {
      for (zk = 1 ; zk<= 3 ; zk++) 
      {
        Lamda[zj+3*zi-3][zk+3*zi-3] = rotc[zj][zk];
      }
    }
  }

  /*copie du vecteur vect dans inter*/
  for (zi = 1 ; zi<= nbcol ; zi++)
  {
    inter[zi] = vect[zi];
  }

  /*mise a zero du vecteur vect */
  for (zi = 1 ; zi<= nbcol ; zi++)
  {
    vect[zi] = 0.0;
  }

  /*changement de base de vect*/
  for (zi = 1 ; zi<= nbcol ; zi++)
  {
    for (zj = 1 ; zj<= nbcol ; zj++) 
    {
       vect[zi] += inter[zj] * Lamda[zj][zi];
    }
  }

}

		
