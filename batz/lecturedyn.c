#include "batz.h"

/*lecture du fichier de resultat dynamique si il existe*/

int lecturedyn(char *nomfichier)
	{
  	char tonom[100];
  	int elem,pa,nbtemps_bis,no;
	int zi,fin,deb;
	double an,epsilon,dist,elongation,vect_1[4],vect_2[4];
	int test;

	epsilon=1.0e-006;       

	
	test=(Houle.direction>90.0 && Houle.direction<270.0) || (Houle.direction<-90.0 && Houle.direction>-270.0);


  	strcpy(tonom,nomfichier);

  	strcat(tonom,".dyn");
  	f1 = fopen(tonom,"r");
  	if (f1 == NULL) 
  		{
    		printf(" \n");
    		printf("%s %s %s \n","fichier ",tonom," n existe pas ");
    		/*fclose(f1);*/
    		return 0;
  		} 
  	else
  		{
    		printf(" \n");
    		printf("%s %s %s \n","fichier ",tonom," existe ");
    		nbtemps = (int) ((Finstockage-Debutstockage) / Passtockage);
    		printf("%d \n",nbtemps);
		temps = (float *) Malloc_float(1 + nbtemps);
    		for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    			{
			Noeud[elem].dx = 	(double *) Malloc_double(1 + nbtemps);
			Noeud[elem].dy = 	(double *) Malloc_double(1 + nbtemps);
			Noeud[elem].dz = 	(double *) Malloc_double(1 + nbtemps);
			Noeud[elem].hz = 	(double *) Malloc_double(1 + nbtemps); /*immersion*/
			Noeud[elem].ex = 	(double *) Malloc_double(1 + nbtemps); /*idem apres rotation*/
			Noeud[elem].ey = 	(double *) Malloc_double(1 + nbtemps);
			Noeud[elem].ez = 	(double *) Malloc_double(1 + nbtemps);
			Noeud[elem].gx = 	(double *) Malloc_double(1 + nbtemps); /*immersion*/
			Noeud[elem].gy = 	(double *) Malloc_double(1 + nbtemps); /*immersion*/
			Noeud[elem].gz = 	(double *) Malloc_double(1 + nbtemps); /*immersion*/
    			}
    		for (elem=1;elem<=NOMBRE_ELEMENTS;elem++)
    			{
			Element[elem].dtension = 	(double *) Malloc_double(1 + nbtemps);
			Element[elem].dlgtendue = 	(double *) Malloc_double(1 + nbtemps);
 			Element[elem].dnrj = 		(double *) Malloc_double(1 + nbtemps);
  			}
  
    		/* lecture des nouvelles coordonnees des noeuds du maillage. */
		printf("nbtemps = %8d \n",nbtemps);
		nbtemps_bis = nbtemps;
    		for (pa=1;pa<=nbtemps;pa++)
    			{
    			/*printf("%d \n",pa);*/
     			fscanf(f1,"%f ",&temps[pa]);
			if ((temps[pa] < temps[pa-1]) && (pa > 1)) nbtemps_bis = pa - 1;
			//printf("nbtemps_bis %8d temps[%4d] %f\n",nbtemps_bis,pa,temps[pa]);
    			for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    				{
      				fscanf(f1,"%lf %lf %lf",&Noeud[elem].dx[pa],&Noeud[elem].dy[pa],&Noeud[elem].dz[pa]);
    				}
    			}
		printf("fin lecture :..........................nbtemps_bis %8d temps[%4d] %f\n",nbtemps_bis,nbtemps_bis,temps[nbtemps_bis]);
		Finstockage = temps[nbtemps_bis];
    		fclose(f1);
		nbtemps = nbtemps_bis;
		//Houle.lambda = G / 2.0 / PI * Houle.periode * Houle.periode;

    		for (pa=1;pa<=nbtemps;pa++)
    			{

			/*rampe from temps[pa]=0 to temps[pa]=period*/
			if (temps[pa] < Houle.periode)  	Houle.hh1 = Houle.hauteur * temps[pa]/Houle.periode; 
			else 					Houle.hh1 = Houle.hauteur;
			/*printf("Houle.hh1 = %8.3f ",Houle.hh1);
			printf("Houle.periode = %8.3f ",Houle.periode);
			printf("Houle.lambda = %8.3f \n",Houle.lambda);*/
	
    			for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    				{
      				Noeud[elem].ex[pa] = Noeud[elem].dx[pa];
      				Noeud[elem].ey[pa] = Noeud[elem].dy[pa];
      				Noeud[elem].ez[pa] = Noeud[elem].dz[pa];

				vect_1[1] = Noeud[elem].dx[pa];		vect_1[2] = Noeud[elem].dy[pa];		vect_1[3] = 0.0;	/*point vector*/
				vect_2[1] = cos(Houle.direction *PI/180);	vect_2[2] = sin(Houle.direction *PI/180);	vect_2[3] = 0.0; 	/*wave direction vector*/
				dist =  produit_scal_double(vect_1, vect_2);		/*distance between origin and the point along wave direction*/

				Noeud[elem].hz[pa] =  Noeud[elem].dz[pa] - Houle.hh1/2.0  * cos(2.0*PI*(temps[pa]/Houle.periode - dist/Houle.lambda));
				/*Noeud[elem].hz[pa] =  Noeud[elem].dz[pa];
				
				if (elem == 2)
					{
					printf("temps[pa] = %8.3f ",temps[pa]);
					printf("ex = %8.3f ",Noeud[elem].ex[pa]);
					printf("ey = %8.3f ",Noeud[elem].ey[pa]);
					printf("ez = %8.3f ",Noeud[elem].ez[pa]);
					printf("dist = %8.3f ",dist);
					printf("Noeud[elem].hz[pa] = %8.3f \n",Noeud[elem].hz[pa]);
					}*/
      				
      				Noeud[elem].gx[pa] = Noeud[elem].dx[pa];
      				Noeud[elem].gy[pa] = Noeud[elem].dy[pa];
      				Noeud[elem].gz[pa] = Noeud[elem].hz[pa];
    				}
    			for (elem=1;elem<=NOMBRE_ELEMENTS;elem++)
    				{
      				/*longueur tendue*/
				deb = Element[elem].extremite[1];
				fin = Element[elem].extremite[2];
      				Element[elem].dlgtendue[pa] = sqrt((Noeud[fin].dx[pa]-Noeud[deb].dx[pa])*(Noeud[fin].dx[pa]-Noeud[deb].dx[pa]) 
							         + (Noeud[fin].dy[pa]-Noeud[deb].dy[pa])*(Noeud[fin].dy[pa]-Noeud[deb].dy[pa]) 
								 + (Noeud[fin].dz[pa]-Noeud[deb].dz[pa])*(Noeud[fin].dz[pa]-Noeud[deb].dz[pa]));
      				elongation = (Element[elem].dlgtendue[pa]-Element[elem].lgrepos) / Element[elem].lgrepos ;
      				if (elongation >= 0.0) Element[elem].dtension[pa] = elongation * Element[elem].raideur_traction;
      				if (elongation <  0.0) Element[elem].dtension[pa] = elongation * Element[elem].raideur_compression;
    				Element[elem].dnrj[pa] = Element[elem].dtension[pa] * (Element[elem].dlgtendue[pa] - Element[elem].lgrepos)/2.0;

				if (elem ==35)
					{
					if(pa==2)
						{
						printf("[fin].dx[%d] %lf,[fin].dy[%d] %lf,[fin].dz[%d] %lf \n",pa,Noeud[fin].dx[pa],pa,Noeud[fin].dy[pa],pa,Noeud[fin].dz[pa]);
						printf("[deb].dx[%d] %lf,[deb].dy[%d] %lf,[deb].dz[%d] %lf \n",pa,Noeud[deb].dx[pa],pa,Noeud[deb].dy[pa],pa,Noeud[deb].dz[pa]);
						printf("lgrepos %lf,lgtendue[%d] %lf , tension[%d] %lf\n",Element[35].lgrepos,pa,Element[35].dlgtendue[pa],pa,Element[35].dtension[pa]);	
						}	
					}
				}



    			}
    		return 1;
  		}



	}	


