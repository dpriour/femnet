#include "batz.h"

/* Lecture du fichier .mdg */

int lectureDo3(char *nomfichier)
{
  char *pr;
  char t1[256],tonom[100];
  char 	chaine[] = "                                               ";
  int 	tmp,i,j,k,n_ligne,p_colonne,tmp_winch,tmp_i1,tmp_i2,tmp_i3,tmp_i4,tmp_i5;
  double	tmp_d1,tmp_d2,u2,u3,v2,v3;
  /*FILE *f1;*/

  strcpy(tonom,nomfichier);

  strcat(tonom,".mdg");

  printf(" \n");
  printf("%s %s \n","fichier ",tonom);

  f1 = fopen(tonom,"r");
  if (f1 == NULL) 
  {
    printf(" \n");
    printf("%s %s %s \n","fichier ",tonom," n existe pas ?");
    exit(0);
  } 
  
	Structure.version = 1;
	lecture_chaine(f1,chaine);		
	i = strlen(chaine);
	printf("chaine = %s  ",chaine);
	printf("longueur chaine = %d\n",i);/**/
	
	if (strcmp(chaine,"version_2") == 0)
		{
		Structure.version = 2;
		}
  fgets(t1,256,f1);  /* t1 contient la premiere ligne du fichier .mdh*/
  fgets(t1,256,f1);  /* t1 contient la seconde ligne du fichier .mdh*/
  fgets(t1,256,f1);  /* t1 contient la troisieme ligne du fichier .mdh*/
  fgets(t1,256,f1);  /* t1 contient la quatrieme ligne du fichier .mdh*/


  /* noeuds *************************************************************/
  fscanf(f1,"%d\n",&NOMBRE_NOEUDS); 
  if (3*NOMBRE_NOEUDS > DIM1)
  {
    printf("%s %d \n","Attention : DIM1 dans filwin.h est trop petit, l augmenter jusqu a",3*NOMBRE_NOEUDS+1);
    exit(0);
  }

  i = NOMBRE_NOEUDS;
  printf("%s %d %s \n","lecture ",i," noeuds");

  fgets(t1,256,f1); 
  for (i=1;i<=NOMBRE_NOEUDS;i++)
  {
	fscanf(f1,"%d %lf %lf %lf %d %d ",&tmp,&Noeud[i].inix,&Noeud[i].iniy,&Noeud[i].iniz,&Noeud[i].new_numero,&Noeud[i].type);
    	fgets(t1,256,f1); 
    	//printf("%lf %lf %lf \n",Noeud[i].inix,Noeud[i].iniy,Noeud[i].iniz);/**/
  }
  /*Noeud[i].x, Noeud[i].y,Noeud[i].z sont les coordonnees cartesiennes des noeuds */
  /* Noeud[i].type est le numero de reference du noeud i. */

  /* éléments *************************************************/
  do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  fscanf(f1,"%d",&NOMBRE_ELEMENTS);
  Structure.nombreElements = NOMBRE_ELEMENTS;
  if (NOMBRE_ELEMENTS > DIM2)
  {
    printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",NOMBRE_ELEMENTS+1);
    exit(0);
  }
	
  i = NOMBRE_ELEMENTS;
  printf("%s %d %s \n","lecture ",i," elements");

  do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  /* Element[i].extremite[1] et Element[i].extremite[2] sont les numeros du noeud i, extremites des bouts. */
  /* Element[i].type est le numero de type( ie de reference) du noeud i. */
  /* Element[i].pro[1] et Element[i].pro[2] sont les positions des extremites de l element par rapport aux extremites du bout qui le contient*/
  for (i=1;i<=NOMBRE_ELEMENTS;i++)
  	{ 
    	fscanf(f1,"%d %d %d %lf %lf %d",&tmp,&Element[i].extremite[1],&Element[i].extremite[2],&Element[i].pro[1],&Element[i].pro[2],&Element[i].type);
    	/*fscanf(f1,"%lf %lf %d  %lf",&Element[i].pro[1],&Element[i].pro[2],&Element[i].type,&Element[i].lgrepos);*/
	/*fscanf(f1,"%lf %lf %d",&Element[i].pro[1],&Element[i].pro[2],&Element[i].type);*/
    	fgets(t1,256,f1); 
    	
  	printf("%4d ",tmp);
  	printf("%4d ",Element[i].extremite[1]);
  	printf("%4d ",Element[i].extremite[2]);
  	printf("%6.2lf ",Element[i].pro[1]);
  	printf("%6.2lf ",Element[i].pro[2]);
  	printf("%4d\n",Element[i].type);
 	}

  	/* coulisses ***********************************************************/
  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	fscanf(f1,"%d",&NOMBRE_COULISSES);
  	if (NOMBRE_COULISSES > DIM2)
  		{
    		printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",NOMBRE_COULISSES+1);
    		exit(0);
  		}
  	i = NOMBRE_COULISSES;
  	printf("%s %d %s \n","lecture ",i," coulisses");

  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	/* Coulisse[i].extremite[1] et Coulisse[i].extremite[2] sont les numeros du noeud i, extremites des coulisses. */
  	for (i=1;i<=NOMBRE_COULISSES;i++)
  		{ 
    		fscanf(f1,"%d %d %d %d ",&tmp,&Coulisse[i].extremite[1],&Coulisse[i].extremite[2],&Coulisse[i].nb_noeud);
       		/*ici il y a +3 pour avoir suffisament de place pour mettre les extremites pour serie.c*/
		Coulisse[i].noeud = 	(int *) Malloc_int(3 + Coulisse[i].nb_noeud);
		Coulisse[i].longueur = 	(double *) Malloc_double(Coulisse[i].nb_noeud);
  		for (j=1;j<=Coulisse[i].nb_noeud;j++)
  			{ 
    			fscanf(f1,"%d  ",&Coulisse[i].noeud[j]);
    			}
 		}


  	for (i=1;i<=NOMBRE_COULISSES;i++)
  		{ 
  		printf("coulisse %d   nb noeud %d \n",i,Coulisse[i].nb_noeud);
  		for (j=1;j<=Coulisse[i].nb_noeud;j++)
  			{ 
  			printf(" %d ",Coulisse[i].noeud[j]);
    			}
  		printf(" \n");
 		}


  /* surfaces ***************************************************/
  do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  fscanf(f1,"%d",&NOMBRE_SURFACES);
  if (NOMBRE_SURFACES > DIM2)
  {
    printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",NOMBRE_SURFACES+1);
    exit(0);
  }
	
  i = NOMBRE_SURFACES;
  printf("%s %d %s \n","lecture ",i," surfaces");

  do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  /* Surface[i].extremite[1], Surface[i].extremite[2], Surface[i].extremite[3] sont les trois numeros des noeuds formant le ieme triangle*/
  /* Surface[i].lon[1], Surface[i].lon[2] sont les coordonnes filaires du 1er sommet du triangle i*/
  /* Surface[i].lon[3], Surface[i].lon[4] sont les coordonnes filaires du 2nd sommet du triangle i*/
  /* Surface[i].lon[5], Surface[i].lon[6] sont les coordonnes filaires du 3ieme sommet du triangle i*/
  /* Surface[i].type est le numero du type du triangle, appele surface, i */
  for (i=1;i<=NOMBRE_SURFACES;i++)
  { 
    fscanf(f1,"%d %d %d %d %lf %lf %lf %lf %lf %lf %d",
       &tmp,&Surface[i].extremite[1],&Surface[i].extremite[2],&Surface[i].extremite[3],
       &Surface[i].lon[1],&Surface[i].lon[2],&Surface[i].lon[3],&Surface[i].lon[4],&Surface[i].lon[5],&Surface[i].lon[6],&Surface[i].type);
       u2 = Surface[i].lon[3] - Surface[i].lon[1];
       u3 = Surface[i].lon[5] - Surface[i].lon[1];
       v2 = Surface[i].lon[4] - Surface[i].lon[2];
       v3 = Surface[i].lon[6] - Surface[i].lon[2];
       Surface[i].nb_cote_u_ou_v = fabs(u2*v3 - u3*v2) / 2.0 ;
    do  pr=fgets(t1,256,f1);
    while (pr == NULL || *pr =='\n');
  }
  /* surfaces hexagonales ******************************************/
  do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  fscanf(f1,"%d",&NOMBRE_SURF_HEXA);
  if (NOMBRE_SURF_HEXA > DIM2)
  {
    printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",NOMBRE_SURF_HEXA+1);
    exit(0);
  }
	
  i = NOMBRE_SURF_HEXA;
  printf("%s %d %s \n","lecture ",i," surfaces hexagonales");

  do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  /* Surf_Hexa[i].extremite[1], Surf_Hexa[i].extremite[2], Surf_Hexa[i].extremite[3] sont les trois numeros des noeuds formant le ieme triangle*/
  /* Surf_Hexa[i].lon[1], Surf_Hexa[i].lon[2] sont les coordonnes filaires du 1er sommet du triangle i*/
  /* Surf_Hexa[i].lon[3], Surf_Hexa[i].lon[4] sont les coordonnes filaires du 2nd sommet du triangle i*/
  /* Surf_Hexa[i].lon[5], Surf_Hexa[i].lon[6] sont les coordonnes filaires du 3ieme sommet du triangle i*/
  /* Surf_Hexa[i].type est le numero du type du triangle, appele Surf_Hexa, i */
  for (i=1;i<=NOMBRE_SURF_HEXA;i++)
  { 
    fscanf(f1,"%d %d %d %d %lf %lf %lf %lf %lf %lf %d",
       &tmp,&Surf_Hexa[i].extremite[1],&Surf_Hexa[i].extremite[2],&Surf_Hexa[i].extremite[3],
       &Surf_Hexa[i].lon[1],&Surf_Hexa[i].lon[2],&Surf_Hexa[i].lon[3],&Surf_Hexa[i].lon[4],&Surf_Hexa[i].lon[5],&Surf_Hexa[i].lon[6],&Surf_Hexa[i].type);
       u2 = Surf_Hexa[i].lon[3] - Surf_Hexa[i].lon[1];
       u3 = Surf_Hexa[i].lon[5] - Surf_Hexa[i].lon[1];
       v2 = Surf_Hexa[i].lon[4] - Surf_Hexa[i].lon[2];
       v3 = Surf_Hexa[i].lon[6] - Surf_Hexa[i].lon[2];
       Surf_Hexa[i].nb_cote_l_m_ou_n = fabs(u2*v3 - u3*v2) / 2.0 ;
    do  pr=fgets(t1,256,f1);
    while (pr == NULL || *pr =='\n');
  }

  	/* winch ***********************************************************/
  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	fscanf(f1,"%d",&tmp_winch);
  	printf("%s %d %s \n","lecture ",tmp_winch," winch bars");

  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
	NOMBRE_WINCHS = 0;
	tmp_i5 = 0;		/*first winch*/

	for (i=1;i<=tmp_winch;i++)
  		{ 
    		fscanf(f1,"%d %d %d %lf %lf %d",&tmp_i1,&tmp_i2,&tmp_i3,&tmp_d1,&tmp_d2,&tmp_i4);	fgets(t1,256,f1); 
		printf("tmp_i1 %3d tmp_i2 %3d tmp_i3 %3d tmp_d1 %7.3lf tmp_d2 %7.3lf tmp_i4 %3d tmp_i5 %3d\n",tmp_i1,tmp_i2,tmp_i3,tmp_d1,tmp_d2,tmp_i4,tmp_i5);
		/*
		*/
		
		if (tmp_i4 != tmp_i5)
			{
			/*new winch*/
			tmp_i5 = tmp_i4;
			Winch[tmp_i4].nb_barre = 1;
			Winch[tmp_i4].noeud = (int    *) Malloc_int   (3 + Winch[tmp_i4].nb_barre);
			Winch[tmp_i4].prop  = (double *) Malloc_double(3 + Winch[tmp_i4].nb_barre);
			Winch[tmp_i4].noeud[Winch[tmp_i4].nb_barre    ] = tmp_i2;
			Winch[tmp_i4].noeud[Winch[tmp_i4].nb_barre + 1] = tmp_i3;
			Winch[tmp_i4].prop [Winch[tmp_i4].nb_barre    ] = tmp_d1;
			Winch[tmp_i4].prop [Winch[tmp_i4].nb_barre + 1] = tmp_d2;
			Winch[tmp_i4].extremite[1] = tmp_i2;
			Winch[tmp_i4].extremite[2] = tmp_i3;
			NOMBRE_WINCHS = NOMBRE_WINCHS + 1;
			}
		else
			{
			Winch[tmp_i4].nb_barre = Winch[tmp_i4].nb_barre + 1;
			Winch[tmp_i4].noeud = Realloc_int   (Winch[tmp_i4].noeud,3 + Winch[tmp_i4].nb_barre);
			Winch[tmp_i4].prop  = Realloc_double(Winch[tmp_i4].prop ,3 + Winch[tmp_i4].nb_barre);
			Winch[tmp_i4].noeud[Winch[tmp_i4].nb_barre    ] = tmp_i2;
			Winch[tmp_i4].noeud[Winch[tmp_i4].nb_barre + 1] = tmp_i3;
			Winch[tmp_i4].prop [Winch[tmp_i4].nb_barre    ] = tmp_d1;
			Winch[tmp_i4].prop [Winch[tmp_i4].nb_barre + 1] = tmp_d2;
			Winch[tmp_i4].extremite[2] = tmp_i3;
			}
		}

	if (Ball.nb != 0)
		{
		/* balls ***********************************************************/
  		do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  		fscanf(f1,"%d",&Ball.nb);
		Ball.noeud =		(int *) Malloc_int(1 + Ball.nb);
		Ball.type = 		(int *) Malloc_int(1 + Ball.nb);
		Ball.birth_time = 	(double *) Malloc_double(1 + Ball.nb);
		Ball.stiffness = 	(double *) Malloc_double(1 + Ball.nb);
		Ball.radius = 		(double *) Malloc_double(1 + Ball.nb);
		Ball.x =                (double *) Malloc_double(1 + Ball.nb);
		Ball.y =                (double *) Malloc_double(1 + Ball.nb);
		Ball.z =                (double *) Malloc_double(1 + Ball.nb);
	
  		i = Ball.nb;
  		printf("%s %d %s \n","lecture ",i," balls");

  		do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  		for (i=1;i<=Ball.nb;i++)
  			{ 
    			/*1   89 0.0000000 100.0000000 0.1300000     2 */
    			fscanf(f1,"%d %d %lf %lf %lf %d %lf %lf %lf",&tmp,&Ball.noeud[i],&Ball.birth_time[i],&Ball.stiffness[i],&Ball.radius[i],&Ball.type[i],&tmp_d1,&tmp_d1,&tmp_d1);
    			fgets(t1,256,f1); 
			printf("Ball.noeud[%d] = %d \n",i,Ball.noeud[i]);
			}
 		}

	fclose(f1);
  	return 0;
	}	


