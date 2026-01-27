#define PRINCIPAL 0
#include "4c19.h"

void meridian()
	{
  	/*
	calculation of the meridian
	*/
   
  	double minx,maxx,surfacefr,volumefr,somme,angle,volume_ellipse;
  	double aa,bb,cc,v1,ve,amax,amin,Ecart,*rk,AA,BB,CC,AA_y,AA_z,AA_R,BB_y,BB_z,BB_R,CC_y,CC_z,CC_R,delta_y,delta_z,delta_R;
  	int zh,zi,zj,elem,symm,za,zb,zc,zd,ze,zf,taille;
  	double Ecart_0,AA_0,BB_0,CC_0,AA_1,BB_1,CC_1,delta_x,aa_y,aa_z,aa_R,bb_y,bb_z,bb_R,cc_y,cc_z,cc_R;	
	double **mat,*xmat,*cmat,*ff,*uu,*YY_vect,*ZZ_vect;
  	int zk,zl,n_ligne,p_colonne,nb_YY_ZZ;
  	
	changement_variable_catch();
	if (Sortie_texte.meridian == 1) 			extrema_direction_courant_meridian(&minx,&maxx);
	if (Sortie_texte.curvilinear_codend_length == 1) 	extrema_direction_courant_curvilinear(&minx,&maxx);
	
	Prise.nb_point_meridian = 1000;
	printf("Prise.nb_point_meridian %d\n",Prise.nb_point_meridian);
	Prise.meridian_x =        (double *) Malloc_double(1 + Prise.nb_point_meridian);
	Prise.meridian_r =        (double *) Malloc_double(1 + Prise.nb_point_meridian);
	delta_x = (maxx - minx) / (Prise.nb_point_meridian - 1);		/*step along x axis*/
	/*printf("delta_x%lf\n",delta_x);*/
	for (zi=1;zi<=Prise.nb_point_meridian;zi++)
		{
		Prise.meridian_x[zi] = minx + (zi - 1) * delta_x;
		}
	if (ARTICLE_TRACTRIX_2007 == 1)
		{
		/*modification of the 11 first x values to coincide with the data of Barry*/
		Prise.meridian_x[1] = 0.0;
		Prise.meridian_x[2] = 0.403501;
		Prise.meridian_x[3] = 0.844094;
		Prise.meridian_x[4] = 1.303628;
		Prise.meridian_x[5] = 1.773173;
		Prise.meridian_x[6] = 2.248093;
		Prise.meridian_x[7] = 2.725923;
		Prise.meridian_x[8] = 3.205334;
		Prise.meridian_x[9] = 3.685607;
		Prise.meridian_x[10] = 4.166349;
		Prise.meridian_x[11] = maxx - 0.000001;
		}
	/*printf("x extrema of meridian: %lf %lf\n",minx,maxx);*/
	/*printf("x extrema of meridian: %lf %lf\n",Prise.meridian_x[1],Prise.meridian_x[Prise.nb_point_meridian]);*/
	
  	/*symmetry*/
	symm = recherche_symmetry();
	printf("symm: %d\n",symm);
  			
  	if (symm == 0)
  		{
  		/*aucune symmetrie*/
		printf("Attention meridian pas fait pour symm: %d\n",symm);
		exit(0);		
  		}
  	if (symm == 1)
  		{
  		/*symmetrie par rapport a l'axe x*/
		printf("Attention meridian pas fait pour symm: %d\n",symm);
		exit(0);
  		}
  	if (symm == 2)
  		{
  		/*symmetrie par rapport a l'axe y*/
		printf("Attention meridian pas fait pour symm: %d\n",symm);
		exit(0);
  		}
  	if (symm == 3)
  		{
  		/*symmetrie par rapport a l'axe z*/
		printf("Attention meridian pas fait pour symm: %d\n",symm);
		exit(0);
  		}
  	if (symm == 4)
  		{
  		/*symmetrie par rapport a y et z*/
  		/*recherche du centre du cercle*/
  		for (za = 1; za <= NOMBRE_NOEUDS; za++)
  			{
 			if ( Noeud[za].symy == 1 )	Prise.Oy = Noeud[za].y;
 			if ( Noeud[za].symz == 1 )	Prise.Oz = Noeud[za].z;
			}
		Prise.Ox = 0.0;
		Prise.diametre = 0.0;
		for (zi=1;zi<=Prise.nb_point_meridian;zi++)
			{
  			/*calcul du rayon du cercle*/
			Prise.nb_point = 0;
			if(Prise.meridian_x[zi] < minx) Prise.meridian_x[zi] = minx;
			if(Prise.meridian_x[zi] > maxx) Prise.meridian_x[zi] = maxx;
   			perimeter2(Prise.meridian_x[zi]);
  			somme = 0.0;
  			for (za = 1; za <= Prise.nb_point; za++)	
				{
				somme = somme + sqrt((Prise.perimeter_y[za]-Prise.Oy)*(Prise.perimeter_y[za]-Prise.Oy)+(Prise.perimeter_z[za]-Prise.Oz)*(Prise.perimeter_z[za]-Prise.Oz));
				}
  			if (Prise.nb_point == 0)
  				{
  				Prise.meridian_r[zi] = Prise.meridian_r[zi-1];
  				Prise.meridian_r[zi] = 0.0;
  				}
  			else
  				{
  				Prise.meridian_r[zi] = somme / Prise.nb_point;
  				}
  			if (Prise.diametre < 2.0 * Prise.meridian_r[zi]) Prise.diametre = 2.0 *  Prise.meridian_r[zi];
			}
  		}
  	if (symm == 5)
  		{
  		/*symmetrie par rapport a Z et X*/
		printf("Attention meridian pas fait pour symm: %d\n",symm);
		exit(0);
  		}
  	if (symm == 6)
  		{
  		/*symmetrie par rapport a X et Y*/
		printf("Attention meridian pas fait pour symm: %d\n",symm);
		exit(0);
  		}
  	if (symm == 7)
  		{
  		/*symmetrie par rapport a X Y et Z*/
		printf("Attention meridian pas fait pour symm: %d\n",symm);
		exit(0);
  		}		
	/*for (zi=1;zi<=Prise.nb_point_meridian;zi++)
		{
		printf("zi %d ",zi);
		printf("Prise.meridian_x[zi] & r %lf %lf\n",Prise.meridian_x[zi],Prise.meridian_r[zi]);
		}*/
	}

void curvilinear()
	{
  	/*
	calculation of the curvilinear length of the cod end
	it is done after meridian
	*/
	int zi;
	double total_length,occult_length,xx1,xx2,yy1,yy2,delta_length;
	
	/*for (zi=1;zi<=Prise.nb_point_meridian;zi++)
		{
		printf("zi %d ",zi);
		printf("Prise.meridian_x[zi] & r %lf %lf\n",Prise.meridian_x[zi],Prise.meridian_r[zi]);
		}*/
   
	total_length = 0.0;
	for (zi=1;zi<=Prise.nb_point_meridian - 1;zi++)
		{
		xx1 = Prise.meridian_x[zi];
		xx2 = Prise.meridian_x[zi+1];
		yy1 = Prise.meridian_r[zi];
		yy2 = Prise.meridian_r[zi+1];
		delta_length = sqrt((xx2-xx1)*(xx2-xx1) + (yy2-yy1)*(yy2-yy1));
		total_length = total_length + sqrt((xx2-xx1)*(xx2-xx1) + (yy2-yy1)*(yy2-yy1));
		
		/*printf("zi %d ",zi);
		printf("x %lf r %lf  ",Prise.meridian_x[zi],Prise.meridian_r[zi]);
		printf("total_length %lf delta_length %lf\n",total_length,delta_length);*/
		}
	occult_length = 0.0;
	for (zi=1;zi<=Prise.nb_point_meridian - 1;zi++)
		{
		xx1 = Prise.meridian_x[zi];
		xx2 = Prise.meridian_x[zi+1];
		yy1 = Prise.meridian_r[zi];
		yy2 = Prise.meridian_r[zi+1];
		if (xx1 > Prise.front)
			{
			/*ce segment est derriere le front*/
			delta_length = sqrt((xx2-xx1)*(xx2-xx1) + (yy2-yy1)*(yy2-yy1));
			occult_length = occult_length + delta_length;
			}
		if ((xx1 < Prise.front) && (xx2 > Prise.front))
			{
			/*le front coupe ce segment*/
			delta_length = sqrt((xx2-xx1)*(xx2-xx1) + (yy2-yy1)*(yy2-yy1));
			delta_length = delta_length * (xx2-Prise.front) / (xx2-xx1);
			occult_length = occult_length + delta_length;
			/*printf("zi %d ",zi);
			printf("x %lf r %lf  ",Prise.meridian_x[zi],Prise.meridian_r[zi]);
			printf("total_length %lf delta_length %lf\n",total_length,delta_length);*/
			}
		}
	printf("total_length %6.3lf occult_length %6.3lf ratio %6.3lf\n",total_length,occult_length,occult_length/total_length);
	}
	
void meridian_x()
	{
	int za;
	
	Prise.nb_point_meridian = 0;
	printf("Prise.nb_point_meridian %d\n",Prise.nb_point_meridian);
	Prise.meridian_y =        (double *) Malloc_double(1 + Prise.nb_point_meridian);
	Prise.meridian_z =        (double *) Malloc_double(1 + Prise.nb_point_meridian);
  	for (za = 1; za <= NOMBRE_NOEUDS; za++)
  		{
 		if ( Noeud[za].symx == 1 )
 			{
			Prise.nb_point_meridian = Prise.nb_point_meridian + 1;
                        Prise.meridian_y = (double *) Realloc_double(Prise.meridian_y,1 + Prise.nb_point_meridian);
                        Prise.meridian_z = (double *) Realloc_double(Prise.meridian_z,1 + Prise.nb_point_meridian);
                        Prise.meridian_y[Prise.nb_point_meridian] = Noeud[za].y;
 	                Prise.meridian_z[Prise.nb_point_meridian] = Noeud[za].z;
 			}
		}
	}
	
void meridian_y()
	{
	int za;

	Prise.nb_point_meridian = 0;
	printf("Prise.nb_point_meridian %d\n",Prise.nb_point_meridian);
	Prise.meridian_z =        (double *) Malloc_double(1 + Prise.nb_point_meridian);
	Prise.meridian_x =        (double *) Malloc_double(1 + Prise.nb_point_meridian);
  	for (za = 1; za <= NOMBRE_NOEUDS; za++)
  		{
 		if ( Noeud[za].symy == 1 )
 			{
			Prise.nb_point_meridian = Prise.nb_point_meridian + 1;
                        Prise.meridian_z = (double *) Realloc_double(Prise.meridian_z,1 + Prise.nb_point_meridian);
                        Prise.meridian_x = (double *) Realloc_double(Prise.meridian_x,1 + Prise.nb_point_meridian);
                        Prise.meridian_z[Prise.nb_point_meridian] = Noeud[za].z;
 	                Prise.meridian_x[Prise.nb_point_meridian] = Noeud[za].x;
 			}
		}
	}
	
void meridian_z()
	{
	int za;
	
	Prise.nb_point_meridian = 0;
	printf("Prise.nb_point_meridian %d\n",Prise.nb_point_meridian);
	Prise.meridian_x =        (double *) Malloc_double(1 + Prise.nb_point_meridian);
	Prise.meridian_y =        (double *) Malloc_double(1 + Prise.nb_point_meridian);
  	for (za = 1; za <= NOMBRE_NOEUDS; za++)
  		{
 		if ( Noeud[za].symz == 1 )
 			{
			Prise.nb_point_meridian = Prise.nb_point_meridian + 1;
                        Prise.meridian_x = (double *) Realloc_double(Prise.meridian_x,1 + Prise.nb_point_meridian);
                        Prise.meridian_y = (double *) Realloc_double(Prise.meridian_y,1 + Prise.nb_point_meridian);
                        Prise.meridian_x[Prise.nb_point_meridian] = Noeud[za].x;
 	                Prise.meridian_y[Prise.nb_point_meridian] = Noeud[za].y;
 			}
		}
	}
