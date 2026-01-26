#include "batz.h"

void Rotation_X(Widget ww, float val, void *junk)
	{
  	angle_x = val;

	char text[4];
	sprintf(text,"%3.0f",angle_x);  

  	SetStringEntry(w[12], text);


  	/*printf("Val de l angle X = %8.0f \n",angle_x);*/
	rotation();
  	tri();
  	dessiner();
	}



void Rotation_Y(Widget ww, float val, void *junk)
	{
  	angle_y = val;
  	/*printf("Val de l angle Y = %8.0f \n",angle_y);*/
	
	char text[4];
	sprintf(text,"%3.0f",angle_y);  

  	SetStringEntry(w[13], text);

	rotation();
  	tri();
  	dessiner();
	}

void Entry_Rotation_X(Widget ww, char *string, void *junk)
	{
	/*prend la chaine de caractere dans MakeStringEntry la transforme en float
	et fait une rotation de cette valeur*/
	
  	float val;
 	void *me;
 
  	/*printf("entry = %s\n",string);*/
  	val = atof(string);

  	/*printf("val = %f\n",val);*/
	Rotation_X(ww, val, me);




	}
	
void Entry_Rotation_Y(Widget ww, char *string, void *junk)
	{
	/*prend la chaine de caractere dans MakeStringEntry la transforme en float
	et fait une rotation de cette valeur*/
	
  	float val;
 	void *me;
 	
  	/*printf("entry = %s\n",string);*/
  	val = atof(string);
  	/*printf("val = %f\n",val);*/
	Rotation_Y(ww, val, me);
	}
	
void rotation()
	{

	int no,pa,zi,nb_teta,premier,condition,flag;
	double vect[7];
	
	
	/*min et max sans zoom
  	vect[1] = Noeud[1].inix;	vect[2] = Noeud[1].iniy;	vect[3] = Noeud[1].iniz;
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  	cinx = vect[1];			ciny = vect[2];			cinz = vect[3];
   	caxx = vect[1];			caxy = vect[2];			caxz = vect[3];*/
 	
	/*rotation des noeuds*/
	premier = 0;
	for (pa=1;pa<=NOMBRE_SURFACES;pa++)
		{ 
		if (panneau[Surface[pa].type].flag_dessin != 0)
			{
			for (zi=1;zi<=3;zi++)
				{ 
				no = Surface[pa].extremite[zi];
  				vect[1] = Noeud[no].inix;	vect[2] = Noeud[no].iniy;	vect[3] = Noeud[no].iniz;
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  				Noeud[no].x = vect[1];		Noeud[no].y = vect[2];		Noeud[no].z = vect[3];
  				if (premier == 0)
  					{
  					premier = 1;
  					cinx = vect[1];	ciny = vect[2];	cinz = vect[3];
   					caxx = vect[1];	caxy = vect[2];	caxz = vect[3];
					}
				if((REEL) Noeud[no].x < cinx) cinx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].x > caxx) caxx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].y < ciny) ciny = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].y > caxy) caxy = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].z < cinz) cinz = (REEL) Noeud[no].z;
				if((REEL) Noeud[no].z > caxz) caxz = (REEL) Noeud[no].z;
				}
			}
		}
	for (pa=1;pa<=NOMBRE_SURF_HEXA;pa++)
		{ 
		if (TypeSurfHexa[Surf_Hexa[pa].type].flag_dessin != 0)
			{
			for (zi=1;zi<=3;zi++)
				{ 
				no = Surf_Hexa[pa].extremite[zi];
  				vect[1] = Noeud[no].inix;	vect[2] = Noeud[no].iniy;	vect[3] = Noeud[no].iniz;
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  				Noeud[no].x = vect[1];		Noeud[no].y = vect[2];		Noeud[no].z = vect[3];
  				if (premier == 0)
  					{
  					premier = 1;
  					cinx = vect[1];	ciny = vect[2];	cinz = vect[3];
   					caxx = vect[1];	caxy = vect[2];	caxz = vect[3];
					}
				if((REEL) Noeud[no].x < cinx) cinx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].x > caxx) caxx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].y < ciny) ciny = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].y > caxy) caxy = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].z < cinz) cinz = (REEL) Noeud[no].z;
				if((REEL) Noeud[no].z > caxz) caxz = (REEL) Noeud[no].z;
				}
			}
		}
	/*for (pa=1;pa<=NOMBRE_ELEMENTS;pa++)
		{
  		printf("pa %d type %d\n",pa,Element[pa].type);
		}*/
	for (pa=1;pa<=NOMBRE_ELEMENTS;pa++)
		{ 
		condition = 0;	//not draw
		if(Element[pa].type > 0)
			{
			//the bar belongs to a cable
			if ((TypeElement[Element[pa].type].flag_dessin != 0) && (Element[pa].flag_dessin != 0))
				{	
				condition = 1;	//draw
				flag = Element[pa].flag_dessin;
				}
			}
		else
			{
			//the bar belongs to a panel
			if (panneau[-Element[pa].type].flag_dessin != 0)
				{	
				condition = 1;	//draw
				flag = panneau[-Element[pa].type].flag_dessin;
				}
			}
		if ((condition == 1) && (flag != 0))
			{
			for (zi=1;zi<=2;zi++)
				{ 
				no = Element[pa].extremite[zi];
  				vect[1] = Noeud[no].inix;	vect[2] = Noeud[no].iniy;	vect[3] = Noeud[no].iniz;
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  				Noeud[no].x = vect[1];		Noeud[no].y = vect[2];		Noeud[no].z = vect[3];

  				if (premier == 0)
  					{
  					premier = 1;
  					cinx = vect[1];	ciny = vect[2];	cinz = vect[3];
   					caxx = vect[1];	caxy = vect[2];	caxz = vect[3];
					}
				if((REEL) Noeud[no].x < cinx) cinx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].x > caxx) caxx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].y < ciny) ciny = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].y > caxy) caxy = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].z < cinz) cinz = (REEL) Noeud[no].z;
				if((REEL) Noeud[no].z > caxz) caxz = (REEL) Noeud[no].z;
				}
			}
		}
	for (pa=1;pa<=NOMBRE_WINCHS;pa++)
		{ 
		if (Winch[pa].flag_dessin != 0)
			{
			for (zi=1;zi<=Winch[pa].nb_barre+1;zi++)
				{ 
				no = Winch[pa].noeud[zi  ];
  				vect[1] = Noeud[no].inix;	vect[2] = Noeud[no].iniy;	vect[3] = Noeud[no].iniz;
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  				Noeud[no].x = vect[1];		Noeud[no].y = vect[2];		Noeud[no].z = vect[3];

  				if (premier == 0)
  					{
  					premier = 1;
  					cinx = vect[1];	ciny = vect[2];	cinz = vect[3];
   					caxx = vect[1];	caxy = vect[2];	caxz = vect[3];
					}
				if((REEL) Noeud[no].x < cinx) cinx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].x > caxx) caxx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].y < ciny) ciny = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].y > caxy) caxy = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].z < cinz) cinz = (REEL) Noeud[no].z;
				if((REEL) Noeud[no].z > caxz) caxz = (REEL) Noeud[no].z;
				}
			}
		}
	for (pa=1;pa<=NOMBRE_COULISSES;pa++)
		{ 
		if (Coulisse[pa].flag_dessin != 0)
			{
			for (zi=1;zi<=2;zi++)
				{ 
				no = Coulisse[pa].extremite[zi];
  				vect[1] = Noeud[no].inix;	vect[2] = Noeud[no].iniy;	vect[3] = Noeud[no].iniz;
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  				Noeud[no].x = vect[1];		Noeud[no].y = vect[2];		Noeud[no].z = vect[3];

  				if (premier == 0)
  					{
  					premier = 1;
  					cinx = vect[1];	ciny = vect[2];	cinz = vect[3];
   					caxx = vect[1];	caxy = vect[2];	caxz = vect[3];
					}
				if((REEL) Noeud[no].x < cinx) cinx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].x > caxx) caxx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].y < ciny) ciny = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].y > caxy) caxy = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].z < cinz) cinz = (REEL) Noeud[no].z;
				if((REEL) Noeud[no].z > caxz) caxz = (REEL) Noeud[no].z;
				}
	  		for (zi=1;zi<=Coulisse[pa].nb_noeud;zi++)
	  			{ 
				no = Coulisse[pa].noeud[zi];
  				vect[1] = Noeud[no].inix;	vect[2] = Noeud[no].iniy;	vect[3] = Noeud[no].iniz;
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  				Noeud[no].x = vect[1];		Noeud[no].y = vect[2];		Noeud[no].z = vect[3];

  				if (premier == 0)
  					{
  					premier = 1;
  					cinx = vect[1];	ciny = vect[2];	cinz = vect[3];
   					caxx = vect[1];	caxy = vect[2];	caxz = vect[3];
					}
				if((REEL) Noeud[no].x < cinx) cinx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].x > caxx) caxx = (REEL) Noeud[no].x;
				if((REEL) Noeud[no].y < ciny) ciny = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].y > caxy) caxy = (REEL) Noeud[no].y;
				if((REEL) Noeud[no].z < cinz) cinz = (REEL) Noeud[no].z;
				if((REEL) Noeud[no].z > caxz) caxz = (REEL) Noeud[no].z;
	    			}
			}
		}
	/*premier = 0;
	for (no=1;no<=NOMBRE_NOEUDS;no++)
		{ 
  		vect[1] = Noeud[no].inix;	vect[2] = Noeud[no].iniy;	vect[3] = Noeud[no].iniz;
		base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  		Noeud[no].x = vect[1];		Noeud[no].y = vect[2];		Noeud[no].z = vect[3];
  	
  		if (premier == 0)
  			{
  			premier = 1;
  			cinx = vect[1];	ciny = vect[2];	cinz = vect[3];
   			caxx = vect[1];	caxy = vect[2];	caxz = vect[3];
			}
		if((REEL) Noeud[no].x < cinx) cinx = (REEL) Noeud[no].x;
		if((REEL) Noeud[no].x > caxx) caxx = (REEL) Noeud[no].x;
		if((REEL) Noeud[no].y < ciny) ciny = (REEL) Noeud[no].y;
		if((REEL) Noeud[no].y > caxy) caxy = (REEL) Noeud[no].y;
		if((REEL) Noeud[no].z < cinz) cinz = (REEL) Noeud[no].z;
		if((REEL) Noeud[no].z > caxz) caxz = (REEL) Noeud[no].z;
		}*/
		
	/*rotation des noeuds en dynamique*/
  	printf("debut rotation %d noeuds\n",NOMBRE_NOEUDS);/**/
	if (nbtemps > 1)
		{
		for (pa=1;pa<=nbtemps;pa++)
			{ 
  			/*printf("temps %d / temps total %d\n",pa,nbtemps);*/
			for (no=1;no<=NOMBRE_NOEUDS;no++)
				{
  				vect[1] = Noeud[no].dx[pa];	vect[2] = Noeud[no].dy[pa];	vect[3] = Noeud[no].dz[pa];
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  				Noeud[no].ex[pa] = vect[1];	Noeud[no].ey[pa] = vect[2];	Noeud[no].ez[pa] = vect[3];

  				if (premier == 0)
  					{
  					premier = 1;
  					cinx = vect[1];	ciny = vect[2];	cinz = vect[3];
   					caxx = vect[1];	caxy = vect[2];	caxz = vect[3];
					}
				if(vect[1] < cinx) cinx = vect[1];	if(vect[1] > caxx) caxx = vect[1];
				if(vect[2] < ciny) ciny = vect[2];	if(vect[2] > caxy) caxy = vect[2];
				if(vect[3] < cinz) cinz = vect[3];	if(vect[3] > caxz) caxz = vect[3];

  				vect[1] = Noeud[no].dx[pa];	vect[2] = Noeud[no].dy[pa];	vect[3] = Noeud[no].hz[pa]; /*wave*/
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  				Noeud[no].gx[pa] = vect[1];	Noeud[no].gy[pa] = vect[2];	Noeud[no].gz[pa] = vect[3];
				}
			}
		}
  	printf("fin rotation noeuds\n");/**/
		
  	printf("debut rotation SL: %d points\n",Houle.nb_point);/**/

	/*rotation de la surface libre en dynamique bis*/
	if (nbtemps > 1)
		{
		for (pa=1;pa<=nbtemps;pa++)
			{ 
			for (no=1;no<=Houle.nb_point;no++)
				{
  				vect[1] = Houle.X[no][pa];	vect[2] = Houle.Y[no][pa];	vect[3] = Houle.Z[no][pa];
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  				Houle.U[no][pa] = vect[1];	Houle.V[no][pa] = vect[2];	Houle.W[no][pa] = vect[3];
				}
			}
		}
	/*
	*/
  	printf("fin rotation SL\n");/**/
		
	/*rotation of eigenvectors*/
	if (Structure.eigenvalues > 0)
  		{
		for (pa=1;pa<=NOMBRE_NOEUDS;pa++)
			{
			for (no=1;no<=Structure.eigenvalues;no++)
				{
				//printf("pa %4d no %4d \n",pa,no);
 				//vect[1] = (double) v_jacobi_result[3*pa-2][no];	vect[2] = (double) v_jacobi_result[3*pa-1][no];	vect[3] = (double) v_jacobi_result[3*pa-0][no];
				//base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  				//v_jacobi_rotati[3*pa-2][no] = (float) vect[1];	v_jacobi_rotati[3*pa-1][no] = (float) vect[2];	v_jacobi_rotati[3*pa-0][no] = (float) vect[3];
 				}
			}
  		}
	  		
	/*mise a l echelle*/
	if (((caxx - cinx)*RESOLUTION_Y_FEN)>((caxy - ciny)*RESOLUTION_X_FEN))
		{
		caxy = ciny + (caxx - cinx) * RESOLUTION_Y_FEN / RESOLUTION_X_FEN;
		}
	else
		{
		caxx = cinx + (caxy - ciny) * RESOLUTION_X_FEN / RESOLUTION_Y_FEN;
		}
	/*min et max avec zoom*/
	binx = cinx - marge * (caxx - cinx);
	biny = ciny - marge * (caxy - ciny);
	baxx = caxx + marge * (caxx - cinx);
	baxy = caxy + marge * (caxy - ciny);
  	/*printf("binx et baxx = %f %f        ",binx,baxx);	printf("biny et baxy = %f %f\n",biny,baxy);*/
  	/*printf("minx et maxx = %f %f        ",minx,maxx);	printf("miny et maxy = %f %f\n",miny,maxy);*/
		
	/*repere*/
  	vect[1] = cinx;  		vect[2] = ciny;  		vect[3] = cinz;			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	repere[1][1] = vect[1];  repere[2][1] = vect[2];  repere[3][1] = vect[3];
  	vect[1] = cinx+ecartmax/5.0;  	vect[2] = ciny;  		vect[3] = cinz;			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	repere[1][2] = vect[1];  repere[2][2] = vect[2];  repere[3][2] = vect[3];
  	vect[1] = cinx;  		vect[2] = ciny+ecartmax/5.0;  	vect[3] = cinz;			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	repere[1][3] = vect[1];  repere[2][3] = vect[2];  repere[3][3] = vect[3];
  	vect[1] = cinx;  		vect[2] = ciny;  		vect[3] = cinz+ecartmax/5.0;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	repere[1][4] = vect[1];  repere[2][4] = vect[2];  repere[3][4] = vect[3];
		
	/*repere*/
  	vect[1] = 0.0;  		vect[2] = 0.0;  		vect[3] = 0.0;			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	repere[1][1] = vect[1];  repere[2][1] = vect[2];  repere[3][1] = vect[3];
  	vect[1] = 0.0+ecartmax/5.0;  	vect[2] = 0.0;  		vect[3] = 0.0;			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	repere[1][2] = vect[1];  repere[2][2] = vect[2];  repere[3][2] = vect[3];
  	vect[1] = 0.0;  		vect[2] = 0.0+ecartmax/5.0;  	vect[3] = 0.0;			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	repere[1][3] = vect[1];  repere[2][3] = vect[2];  repere[3][3] = vect[3];
  	vect[1] = 0.0;  		vect[2] = 0.0;  		vect[3] = 0.0+ecartmax/5.0;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	repere[1][4] = vect[1];  repere[2][4] = vect[2];  repere[3][4] = vect[3];
		
	/*surface libre*/
  	vect[1] = minx;  		vect[2] = miny;  		vect[3] = 0.0;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_libre[1][1] = vect[1];  surface_libre[2][1] = vect[2];  surface_libre[3][1] = vect[3];
  	vect[1] = minx;  		vect[2] = maxy;  		vect[3] = 0.0;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_libre[1][2] = vect[1];  surface_libre[2][2] = vect[2];  surface_libre[3][2] = vect[3];
  	vect[1] = maxx;  		vect[2] = maxy;  		vect[3] = 0.0;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_libre[1][3] = vect[1];  surface_libre[2][3] = vect[2];  surface_libre[3][3] = vect[3];
  	vect[1] = maxx;  		vect[2] = miny;  		vect[3] = 0.0;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_libre[1][4] = vect[1];  surface_libre[2][4] = vect[2];  surface_libre[3][4] = vect[3];
		
	/*surface du fond*/
  	vect[1] = minx;  		vect[2] = miny;  		vect[3] = -Houle.depth;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_fond[1][1] = vect[1];  surface_fond[2][1] = vect[2];  surface_fond[3][1] = vect[3];
  	vect[1] = minx;  		vect[2] = maxy;  		vect[3] = -Houle.depth;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_fond[1][2] = vect[1];  surface_fond[2][2] = vect[2];  surface_fond[3][2] = vect[3];
  	vect[1] = maxx;  		vect[2] = maxy;  		vect[3] = -Houle.depth;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_fond[1][3] = vect[1];  surface_fond[2][3] = vect[2];  surface_fond[3][3] = vect[3];
  	vect[1] = maxx;  		vect[2] = miny;  		vect[3] = -Houle.depth;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_fond[1][4] = vect[1];  surface_fond[2][4] = vect[2];  surface_fond[3][4] = vect[3];
		
	/*surface ballast*/
  	vect[1] = minx;  		vect[2] = miny;  		vect[3] = Ballast[1].altitude;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_ballast[1][1] = vect[1];  surface_ballast[2][1] = vect[2];  surface_ballast[3][1] = vect[3];
  	vect[1] = minx;  		vect[2] = maxy;  		vect[3] = Ballast[1].altitude;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_ballast[1][2] = vect[1];  surface_ballast[2][2] = vect[2];  surface_ballast[3][2] = vect[3];
  	vect[1] = maxx;  		vect[2] = maxy;  		vect[3] = Ballast[1].altitude;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_ballast[1][3] = vect[1];  surface_ballast[2][3] = vect[2];  surface_ballast[3][3] = vect[3];
  	vect[1] = maxx;  		vect[2] = miny;  		vect[3] = Ballast[1].altitude;	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_ballast[1][4] = vect[1];  surface_ballast[2][4] = vect[2];  surface_ballast[3][4] = vect[3];
		
	/*surface du front*/
  	vect[1] = surface_front[1][1];  	vect[2] = surface_front[2][1];  	vect[3] = surface_front[3][1];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_front_dessine[1][1] = vect[1];  surface_front_dessine[2][1] = vect[2];  surface_front_dessine[3][1] = vect[3];
  	vect[1] = surface_front[1][2];  	vect[2] = surface_front[2][2];  	vect[3] = surface_front[3][2];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_front_dessine[1][2] = vect[1];  surface_front_dessine[2][2] = vect[2];  surface_front_dessine[3][2] = vect[3];
  	vect[1] = surface_front[1][3];  	vect[2] = surface_front[2][3];  	vect[3] = surface_front[3][3];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_front_dessine[1][3] = vect[1];  surface_front_dessine[2][3] = vect[2];  surface_front_dessine[3][3] = vect[3];
  	vect[1] = surface_front[1][4];  	vect[2] = surface_front[2][4];  	vect[3] = surface_front[3][4];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	surface_front_dessine[1][4] = vect[1];  surface_front_dessine[2][4] = vect[2];  surface_front_dessine[3][4] = vect[3];
		
	/*volume of value*/
  	vect[1] = volume_value[1][1];  	vect[2] = volume_value[2][1];  	vect[3] = volume_value[3][1];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	volume_value_dessine[1][1] = vect[1];  volume_value_dessine[2][1] = vect[2];  volume_value_dessine[3][1] = vect[3];
  	vect[1] = volume_value[1][2];  	vect[2] = volume_value[2][2];  	vect[3] = volume_value[3][2];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	volume_value_dessine[1][2] = vect[1];  volume_value_dessine[2][2] = vect[2];  volume_value_dessine[3][2] = vect[3];
  	vect[1] = volume_value[1][3];  	vect[2] = volume_value[2][3];  	vect[3] = volume_value[3][3];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	volume_value_dessine[1][3] = vect[1];  volume_value_dessine[2][3] = vect[2];  volume_value_dessine[3][3] = vect[3];
  	vect[1] = volume_value[1][4];  	vect[2] = volume_value[2][4];  	vect[3] = volume_value[3][4];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	volume_value_dessine[1][4] = vect[1];  volume_value_dessine[2][4] = vect[2];  volume_value_dessine[3][4] = vect[3];
  	vect[1] = volume_value[1][5];  	vect[2] = volume_value[2][5];  	vect[3] = volume_value[3][5];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	volume_value_dessine[1][5] = vect[1];  volume_value_dessine[2][5] = vect[2];  volume_value_dessine[3][5] = vect[3];
  	vect[1] = volume_value[1][6];  	vect[2] = volume_value[2][6];  	vect[3] = volume_value[3][6];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	volume_value_dessine[1][6] = vect[1];  volume_value_dessine[2][6] = vect[2];  volume_value_dessine[3][6] = vect[3];
  	vect[1] = volume_value[1][7];  	vect[2] = volume_value[2][7];  	vect[3] = volume_value[3][7];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	volume_value_dessine[1][7] = vect[1];  volume_value_dessine[2][7] = vect[2];  volume_value_dessine[3][7] = vect[3];
  	vect[1] = volume_value[1][8];  	vect[2] = volume_value[2][8];  	vect[3] = volume_value[3][8];	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);  	volume_value_dessine[1][8] = vect[1];  volume_value_dessine[2][8] = vect[2];  volume_value_dessine[3][8] = vect[3];
		
	/*surface interne de la prise*/
	nb_teta = 20;
  	for (zi = 0; zi<= nb_teta; zi++)
  		{
  		vect[1] = surface_inner[1][zi];  	vect[2] = surface_inner[2][zi];  	vect[3] = surface_inner[3][zi];
		base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  		surface_inner_dessine[1][zi] = vect[1];  surface_inner_dessine[2][zi] = vect[2];  surface_inner_dessine[3][zi] = vect[3];
  		}

	/*surface triangularisee interne de la prise*/
  	/*printf("Prise.nb_noeuds = %d\n",Prise.nb_noeuds);*/
  	for (zi = 1; zi<= Prise.nb_noeuds; zi++)
  		{
  		vect[1] = Prise.xx_ini[zi];  	vect[2] = Prise.yy_ini[zi];  	vect[3] = Prise.zz_ini[zi];
		base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
  		Prise.xx[zi] = vect[1];  Prise.yy[zi] = vect[2]; Prise.zz[zi]  = vect[3];
  		/**/
  		}

	/*profondeur de coupe********************************************
	profondeur_coupe = 1.0;	*/
    	profondeur_coupe_float = cinz + profondeur_coupe * (caxz-cinz);
	}
	
void rotation_fils()
	{
	int no,pa,mode_u,mode_v;
	double vect[7];
	
	if (Structure.graphic == 1)
		{
		mode_u = GetMenuItemChecked(w[11]); /*fils u dessines*/
		mode_v = GetMenuItemChecked(w[29]); /*fils v dessines*/
		}
	/*
	if ((mode_u == 1) || (mode_v == 1) || (Structure.graphic == 2)) 
		{
		for (no=1;no<=NOMBRE_SURFACES;no++)
			{ 
			for (pa=1;pa<=Surface[no].nb_ufils;pa++)
				{ 
  				vect[1] = (double)Surface[no].g1_ux[pa];	vect[4] = (double)Surface[no].g2_ux[pa];
  				vect[2] = (double)Surface[no].g1_uy[pa];	vect[5] = (double)Surface[no].g2_uy[pa];
  				vect[3] = (double)Surface[no].g1_uz[pa];	vect[6] = (double)Surface[no].g2_uz[pa];
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,6,vect);
  				Surface[no].f1_ux[pa] = (REEL) vect[1];	Surface[no].f2_ux[pa] = (REEL) vect[4];
  				Surface[no].f1_uy[pa] = (REEL) vect[2];	Surface[no].f2_uy[pa] = (REEL) vect[5];
				}
			for (pa=1;pa<=Surface[no].nb_vfils;pa++)
				{ 
  				vect[1] = (double)Surface[no].g1_vx[pa];	vect[4] = (double)Surface[no].g2_vx[pa];
  				vect[2] = (double)Surface[no].g1_vy[pa];	vect[5] = (double)Surface[no].g2_vy[pa];
  				vect[3] = (double)Surface[no].g1_vz[pa];	vect[6] = (double)Surface[no].g2_vz[pa];
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,6,vect);
  				Surface[no].f1_vx[pa] = (REEL) vect[1];	Surface[no].f2_vx[pa] = (REEL) vect[4];
  				Surface[no].f1_vy[pa] = (REEL) vect[2];	Surface[no].f2_vy[pa] = (REEL) vect[5];
				}
			}
		for (no=1;no<=NOMBRE_SURF_HEXA;no++)
			{ 
			for (pa=1;pa<=Surf_Hexa[no].nb_Ufils;pa++)
				{ 
  				vect[1] = (double)Surf_Hexa[no].g1_Ux[pa];	vect[4] = (double)Surf_Hexa[no].g2_Ux[pa];
  				vect[2] = (double)Surf_Hexa[no].g1_Uy[pa];	vect[5] = (double)Surf_Hexa[no].g2_Uy[pa];
  				vect[3] = (double)Surf_Hexa[no].g1_Uz[pa];	vect[6] = (double)Surf_Hexa[no].g2_Uz[pa];
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,6,vect);
  				Surf_Hexa[no].f1_Ux[pa] = (REEL) vect[1];	Surf_Hexa[no].f2_Ux[pa] = (REEL) vect[4];
  				Surf_Hexa[no].f1_Uy[pa] = (REEL) vect[2];	Surf_Hexa[no].f2_Uy[pa] = (REEL) vect[5];
				}
			for (pa=1;pa<=Surf_Hexa[no].nb_Vfils;pa++)
				{ 
  				vect[1] = (double)Surf_Hexa[no].g1_Vx[pa];	vect[4] = (double)Surf_Hexa[no].g2_Vx[pa];
  				vect[2] = (double)Surf_Hexa[no].g1_Vy[pa];	vect[5] = (double)Surf_Hexa[no].g2_Vy[pa];
  				vect[3] = (double)Surf_Hexa[no].g1_Vz[pa];	vect[6] = (double)Surf_Hexa[no].g2_Vz[pa];
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,6,vect);
  				Surf_Hexa[no].f1_Vx[pa] = (REEL) vect[1];	Surf_Hexa[no].f2_Vx[pa] = (REEL) vect[4];
  				Surf_Hexa[no].f1_Vy[pa] = (REEL) vect[2];	Surf_Hexa[no].f2_Vy[pa] = (REEL) vect[5];
				}
			}
		}
	*/
	}
	
