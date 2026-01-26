#define PRINCIPAL 0
#include "4c19.h"

/*fonctions utilisées dans pliage_triangle2.C*/

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

void substract_vect(double vect_1[4], double vect_2[4], double *vect_3)
	{
	vect_3[1] = vect_1[1] - vect_2[1];
	vect_3[2] = vect_1[2] - vect_2[2];
	vect_3[3] = vect_1[3] - vect_2[3];
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

void add_scal_vect_1(double double_1, double vect_1[4], double *vect)
	{
	vect[1] = double_1*vect_1[1];
	vect[2] = double_1*vect_1[2];
	vect[3] = double_1*vect_1[3];
	}

void add_scal_vect_2(double double_1, double vect_1[4], double double_2, double vect_2[4], double *vect)
	{
	vect[1] = double_1*vect_1[1] + double_2*vect_2[1];
	vect[2] = double_1*vect_1[2] + double_2*vect_2[2];
	vect[3] = double_1*vect_1[3] + double_2*vect_2[3];
	}

void add_scal_vect_3(double double_1, double vect_1[4], double double_2, double vect_2[4], double double_3, double vect_3[4], double *vect)
	{
	vect[1] = double_1*vect_1[1] + double_2*vect_2[1] + double_3*vect_3[1];
	vect[2] = double_1*vect_1[2] + double_2*vect_2[2] + double_3*vect_3[2];
	vect[3] = double_1*vect_1[3] + double_2*vect_2[3] + double_3*vect_3[3];
	}

void add_scal_vect_4(double double_1, double vect_1[4], double double_2, double vect_2[4], double double_3, double vect_3[4], double double_4, double vect_4[4], double *vect)
	{
	vect[1] = double_1*vect_1[1] + double_2*vect_2[1] + double_3*vect_3[1] + double_4*vect_4[1];
	vect[2] = double_1*vect_1[2] + double_2*vect_2[2] + double_3*vect_3[2] + double_4*vect_4[2];
	vect[3] = double_1*vect_1[3] + double_2*vect_2[3] + double_3*vect_3[3] + double_4*vect_4[3];
	}

void add_scal_vect_5(double double_1, double vect_1[4], double double_2, double vect_2[4], double double_3, double vect_3[4], double double_4, double vect_4[4], double double_5, double vect_5[4], double *vect)
	{
	vect[1] = double_1*vect_1[1] + double_2*vect_2[1] + double_3*vect_3[1] + double_4*vect_4[1] + double_5*vect_5[1];
	vect[2] = double_1*vect_1[2] + double_2*vect_2[2] + double_3*vect_3[2] + double_4*vect_4[2] + double_5*vect_5[2];
	vect[3] = double_1*vect_1[3] + double_2*vect_2[3] + double_3*vect_3[3] + double_4*vect_4[3] + double_5*vect_5[3];
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
	
int trouver(int elem1, int sommet1, int *elem2, int *sommet2, double *U2, double *V2)
	{
	int trouve,elem3,zb,zc,zd,sommet3,sommet4;
	
	if (sommet1 == yc(elem1,1))  {	sommet3 = yc(elem1,4);  sommet4 = yc(elem1,7);	}
	if (sommet1 == yc(elem1,4))  {	sommet3 = yc(elem1,7);  sommet4 = yc(elem1,1);	}
	if (sommet1 == yc(elem1,7))  {	sommet3 = yc(elem1,1);  sommet4 = yc(elem1,4);	}
	
  	trouve = 0;			
  	elem3 = elem1;
  	while ((trouve == 0) && (elem3 <= NOMBRE_SURFACES))
  		{
  		/*recherche d un triangle voisin de elem1 par les sommets sommet3 et sommet4 et de meme type que elem1*/
  		/*printf("elem1 = %5d elem3 = %5d       \n",elem1,elem3);*/
  		elem3 = elem3 + 1;
  		if (Surface[elem3].type == Surface[elem1].type)
  			{
  			zb = yc(elem3,1);  zc = yc(elem3,4);  zd = yc(elem3,7);
  			/*printf("elem1 = %5d elem3 = %5d       ",elem1,elem3);
   			printf("sommet3 = %5d sommet4 = %5d        ",sommet3,sommet4);
   			printf("zb = %5d zc = %5d zd = %5d \n",zb,zc,zd);*/
  			if((zb == sommet3) && (zc == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zd; /*sommet 3 (zd) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[5] + Surface[*elem2].lon[6];
				*V2 = - Surface[*elem2].lon[5] + Surface[*elem2].lon[6];
   				/*printf("1 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			if((zc == sommet3) && (zb == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zd; /*sommet 3 (zd) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[5] + Surface[*elem2].lon[6];
				*V2 = - Surface[*elem2].lon[5] + Surface[*elem2].lon[6];
   				/*printf("2 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			if((zc == sommet3) && (zd == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zb; /*sommet 1 (zb) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[1] + Surface[*elem2].lon[2]; 
				*V2 = - Surface[*elem2].lon[1] + Surface[*elem2].lon[2]; 
   				/*printf("3 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			if((zd == sommet3) && (zc == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zb; /*sommet 1 (zb) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[1] + Surface[*elem2].lon[2]; 
				*V2 = - Surface[*elem2].lon[1] + Surface[*elem2].lon[2]; 
   				/*printf("4 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			if((zd == sommet3) && (zb == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zc; /*sommet 2 (zc) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[3] + Surface[*elem2].lon[4]; 
				*V2 = - Surface[*elem2].lon[3] + Surface[*elem2].lon[4]; 
   				/*printf("5 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			if((zb == sommet3) && (zd == sommet4))
  				{
  				trouve = 1;
  				*sommet2 = zc; /*sommet 2 (zc) non contigu du triangle 1*/
  				*elem2 = elem3;
				*U2 =   Surface[*elem2].lon[3] + Surface[*elem2].lon[4]; 
				*V2 = - Surface[*elem2].lon[3] + Surface[*elem2].lon[4]; 
   				/*printf("6 sommet2 = %5d ",*sommet2);printf("U2 = %lf ",*U2);printf("V2 = %lf \n",*V2);*/
  				}
  			}
  		}
	return trouve;	
	}
					
int trouver_sym(int elem1, int coord1)
	{
	/*renvoie l'axe de symmetrie porte par sommet3 et sommet4, sinon renvoie 0*/
	int trouve,elem3,zb,zc,zd,sommet3,sommet4;
	
	if (coord1 == yc(elem1,1))  {	sommet3 = (yc(elem1,4)+2)/3;  sommet4 = (yc(elem1,7)+2)/3;	}
	if (coord1 == yc(elem1,4))  {	sommet3 = (yc(elem1,7)+2)/3;  sommet4 = (yc(elem1,1)+2)/3;	}
	if (coord1 == yc(elem1,7))  {	sommet3 = (yc(elem1,1)+2)/3;  sommet4 = (yc(elem1,4)+2)/3;	}
	
  	trouve = 0;

	if ((Noeud[sommet3].symx == 1) && (Noeud[sommet4].symx == 1)) 		trouve = 1;
	if ((Noeud[sommet3].symy == 1) && (Noeud[sommet4].symy == 1)) 		trouve = 2;
	if ((Noeud[sommet3].symz == 1) && (Noeud[sommet4].symz == 1)) 		trouve = 3;
	
	return trouve;	
	}
					
void diff_nx_vector(double v_vect[5], double d_vect[3], double *d_nx_vect)
	{
	int zi;
	
	for   (zi = 0; zi<= 12; zi++) 	d_nx_vect[zi] = 0.0;
	
	d_nx_vect[ 1] = (v_vect[4]-v_vect[3]) / d_vect[1];
	d_nx_vect[ 7] = (v_vect[1]-v_vect[4]) / d_vect[1];
	d_nx_vect[10] = (v_vect[3]-v_vect[1]) / d_vect[1];
	}
						
void diff_ny_vector(double v_vect[5], double d_vect[3], double *d_ny_vect)
	{
	int zi;
	
	for   (zi = 0; zi<= 12; zi++) 	d_ny_vect[zi] = 0.0;
	
	d_ny_vect[ 2] = (v_vect[4]-v_vect[3]) / d_vect[1];
	d_ny_vect[ 8] = (v_vect[1]-v_vect[4]) / d_vect[1];
	d_ny_vect[11] = (v_vect[3]-v_vect[1]) / d_vect[1];
	}
						
void diff_nz_vector(double v_vect[5], double d_vect[3], double *d_nz_vect)
	{
	int zi;
	
	for   (zi = 0; zi<= 12; zi++) 	d_nz_vect[zi] = 0.0;
	
	d_nz_vect[ 3] = (v_vect[4]-v_vect[3]) / d_vect[1];
	d_nz_vect[ 9] = (v_vect[1]-v_vect[4]) / d_vect[1];
	d_nz_vect[12] = (v_vect[3]-v_vect[1]) / d_vect[1];
	}
						
						
						
void diff_mx_vector(double v_vect[5], double d_vect[3], double *d_mx_vect)
	{
	int zi;
	
	for   (zi = 0; zi<= 12; zi++) 	d_mx_vect[zi] = 0.0;
	
	d_mx_vect[ 4] = (v_vect[3]-v_vect[4]) / d_vect[2];
	d_mx_vect[ 7] = (v_vect[4]-v_vect[2]) / d_vect[2];
	d_mx_vect[10] = (v_vect[2]-v_vect[3]) / d_vect[2];
	}
						
	
void diff_my_vector(double v_vect[5], double d_vect[3], double *d_my_vect)
	{
	int zi;
	
	for   (zi = 0; zi<= 12; zi++) 	d_my_vect[zi] = 0.0;
	
	d_my_vect[ 5] = (v_vect[3]-v_vect[4]) / d_vect[2];
	d_my_vect[ 8] = (v_vect[4]-v_vect[2]) / d_vect[2];
	d_my_vect[11] = (v_vect[2]-v_vect[3]) / d_vect[2];
	}
						
void diff_mz_vector(double v_vect[5], double d_vect[3], double *d_mz_vect)
	{
	int zi;
	
	for   (zi = 0; zi<= 12; zi++) 	d_mz_vect[zi] = 0.0;
	
	d_mz_vect[ 6] = (v_vect[3]-v_vect[4]) / d_vect[2];
	d_mz_vect[ 9] = (v_vect[4]-v_vect[2]) / d_vect[2];
	d_mz_vect[12] = (v_vect[2]-v_vect[3]) / d_vect[2];
	}
						
						
	
void diff_ps_vector(double v_vect[5], double d_vect[3], double coord_vect[13], double *d_ps_vect)
	{
	d_ps_vect[ 1] = (v_vect[4]-v_vect[3])*((coord_vect[ 7]-coord_vect[ 4])*(v_vect[4]-v_vect[2])-(coord_vect[10]-coord_vect[ 4])*(v_vect[3]-v_vect[2]))/d_vect[1]/d_vect[2];
	d_ps_vect[ 4] = (v_vect[3]-v_vect[4])*((coord_vect[10]-coord_vect[ 1])*(v_vect[3]-v_vect[1])-(coord_vect[ 7]-coord_vect[ 1])*(v_vect[4]-v_vect[1]))/d_vect[1]/d_vect[2];
	d_ps_vect[ 7] = (v_vect[1]-v_vect[4])*((coord_vect[ 7]-coord_vect[ 4])*(v_vect[4]-v_vect[2])-(coord_vect[10]-coord_vect[ 4])*(v_vect[3]-v_vect[2]))/d_vect[1]/d_vect[2]  +  (v_vect[4]-v_vect[2])*((coord_vect[10]-coord_vect[ 1])*(v_vect[3]-v_vect[1])-(coord_vect[ 7]-coord_vect[ 1])*(v_vect[4]-v_vect[1]))/d_vect[1]/d_vect[2];
	d_ps_vect[10] = (v_vect[3]-v_vect[1])*((coord_vect[ 7]-coord_vect[ 4])*(v_vect[4]-v_vect[2])-(coord_vect[10]-coord_vect[ 4])*(v_vect[3]-v_vect[2]))/d_vect[1]/d_vect[2]  +  (v_vect[2]-v_vect[3])*((coord_vect[10]-coord_vect[ 1])*(v_vect[3]-v_vect[1])-(coord_vect[ 7]-coord_vect[ 1])*(v_vect[4]-v_vect[1]))/d_vect[1]/d_vect[2];

	d_ps_vect[ 2] = (v_vect[4]-v_vect[3])*((coord_vect[ 8]-coord_vect[ 5])*(v_vect[4]-v_vect[2])-(coord_vect[11]-coord_vect[ 5])*(v_vect[3]-v_vect[2]))/d_vect[1]/d_vect[2];
	d_ps_vect[ 5] = (v_vect[3]-v_vect[4])*((coord_vect[11]-coord_vect[ 2])*(v_vect[3]-v_vect[1])-(coord_vect[ 8]-coord_vect[ 2])*(v_vect[4]-v_vect[1]))/d_vect[1]/d_vect[2];
	d_ps_vect[ 8] = (v_vect[1]-v_vect[4])*((coord_vect[ 8]-coord_vect[ 5])*(v_vect[4]-v_vect[2])-(coord_vect[11]-coord_vect[ 5])*(v_vect[3]-v_vect[2]))/d_vect[1]/d_vect[2]  +  (v_vect[4]-v_vect[2])*((coord_vect[11]-coord_vect[ 2])*(v_vect[3]-v_vect[1])-(coord_vect[ 8]-coord_vect[ 2])*(v_vect[4]-v_vect[1]))/d_vect[1]/d_vect[2];
	d_ps_vect[11] = (v_vect[3]-v_vect[1])*((coord_vect[ 8]-coord_vect[ 5])*(v_vect[4]-v_vect[2])-(coord_vect[11]-coord_vect[ 5])*(v_vect[3]-v_vect[2]))/d_vect[1]/d_vect[2]  +  (v_vect[2]-v_vect[3])*((coord_vect[11]-coord_vect[ 2])*(v_vect[3]-v_vect[1])-(coord_vect[ 8]-coord_vect[ 2])*(v_vect[4]-v_vect[1]))/d_vect[1]/d_vect[2];

	d_ps_vect[ 3] = (v_vect[4]-v_vect[3])*((coord_vect[ 9]-coord_vect[ 6])*(v_vect[4]-v_vect[2])-(coord_vect[12]-coord_vect[ 6])*(v_vect[3]-v_vect[2]))/d_vect[1]/d_vect[2];
	d_ps_vect[ 6] = (v_vect[3]-v_vect[4])*((coord_vect[12]-coord_vect[ 3])*(v_vect[3]-v_vect[1])-(coord_vect[ 9]-coord_vect[ 3])*(v_vect[4]-v_vect[1]))/d_vect[1]/d_vect[2];
	d_ps_vect[ 9] = (v_vect[1]-v_vect[4])*((coord_vect[ 9]-coord_vect[ 6])*(v_vect[4]-v_vect[2])-(coord_vect[12]-coord_vect[ 6])*(v_vect[3]-v_vect[2]))/d_vect[1]/d_vect[2]  +  (v_vect[4]-v_vect[2])*((coord_vect[12]-coord_vect[ 3])*(v_vect[3]-v_vect[1])-(coord_vect[ 9]-coord_vect[ 3])*(v_vect[4]-v_vect[1]))/d_vect[1]/d_vect[2];
	d_ps_vect[12] = (v_vect[3]-v_vect[1])*((coord_vect[ 9]-coord_vect[ 6])*(v_vect[4]-v_vect[2])-(coord_vect[12]-coord_vect[ 6])*(v_vect[3]-v_vect[2]))/d_vect[1]/d_vect[2]  +  (v_vect[2]-v_vect[3])*((coord_vect[12]-coord_vect[ 3])*(v_vect[3]-v_vect[1])-(coord_vect[ 9]-coord_vect[ 3])*(v_vect[4]-v_vect[1]))/d_vect[1]/d_vect[2];
	}
	
void diff_nn_vector(double v_vect[5], double d_vect[3], double n_vect[4], double *d_nn_vect)
	{
	double nn,n2;
	
	n2 = produit_scal(n_vect, n_vect);
	nn = sqrt(n2);
	
	d_nn_vect[ 1] = n_vect[1] * (v_vect[4]-v_vect[3]) / d_vect[1] / nn;	
	d_nn_vect[ 2] = n_vect[2] * (v_vect[4]-v_vect[3]) / d_vect[1] / nn;	
	d_nn_vect[ 3] = n_vect[3] * (v_vect[4]-v_vect[3]) / d_vect[1] / nn;	
	d_nn_vect[ 4] = 0.0;	
	d_nn_vect[ 5] = 0.0;	
	d_nn_vect[ 6] = 0.0;	
	d_nn_vect[ 7] = n_vect[1] * (v_vect[1]-v_vect[4]) / d_vect[1] / nn;	
	d_nn_vect[ 8] = n_vect[2] * (v_vect[1]-v_vect[4]) / d_vect[1] / nn;	
	d_nn_vect[ 9] = n_vect[3] * (v_vect[1]-v_vect[4]) / d_vect[1] / nn;	
	d_nn_vect[10] = n_vect[1] * (v_vect[3]-v_vect[1]) / d_vect[1] / nn;
	d_nn_vect[11] = n_vect[2] * (v_vect[3]-v_vect[1]) / d_vect[1] / nn;
	d_nn_vect[12] = n_vect[3] * (v_vect[3]-v_vect[1]) / d_vect[1] / nn;
	}
						

void diff_mm_vector(double v_vect[5], double d_vect[3], double m_vect[4], double *d_mm_vect)
	{
	double mm,m2;
	
	m2 = produit_scal(m_vect, m_vect);
	mm = sqrt(m2);
	
	d_mm_vect[ 1] = 0.0;	
	d_mm_vect[ 2] = 0.0;	
	d_mm_vect[ 3] = 0.0;	
	d_mm_vect[ 4] = m_vect[1] * (v_vect[3]-v_vect[4]) / d_vect[2] / mm;	
	d_mm_vect[ 5] = m_vect[2] * (v_vect[3]-v_vect[4]) / d_vect[2] / mm;	
	d_mm_vect[ 6] = m_vect[3] * (v_vect[3]-v_vect[4]) / d_vect[2] / mm;	
	d_mm_vect[ 7] = m_vect[1] * (v_vect[4]-v_vect[2]) / d_vect[2] / mm;	
	d_mm_vect[ 8] = m_vect[2] * (v_vect[4]-v_vect[2]) / d_vect[2] / mm;	
	d_mm_vect[ 9] = m_vect[3] * (v_vect[4]-v_vect[2]) / d_vect[2] / mm;	
	d_mm_vect[10] = m_vect[1] * (v_vect[2]-v_vect[3]) / d_vect[2] / mm;
	d_mm_vect[11] = m_vect[2] * (v_vect[2]-v_vect[3]) / d_vect[2] / mm;						
	d_mm_vect[12] = m_vect[3] * (v_vect[2]-v_vect[3]) / d_vect[2] / mm;
	}
	
	
void diff_Alph_vector(double Alph, double seui, double v_vect[5], double d_vect[3], double n_vect[4], double m_vect[4], double *d_al_vect)
	{
	double ps,n2,m2,nn,mm,Beta;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);
	mm = sqrt(m2);
	
   	if ((fabs(Alph) > seui) && (fabs(PI-Alph) > seui))
		{
		d_al_vect[ 1] = (v_vect[4]-v_vect[3])*(ps*n_vect[1] - m_vect[1]*n2) / n2 / nn / mm / d_vect[1] / sin(Alph);
		d_al_vect[ 2] = (v_vect[4]-v_vect[3])*(ps*n_vect[2] - m_vect[2]*n2) / n2 / nn / mm / d_vect[1] / sin(Alph);
		d_al_vect[ 3] = (v_vect[4]-v_vect[3])*(ps*n_vect[3] - m_vect[3]*n2) / n2 / nn / mm / d_vect[1] / sin(Alph);
		d_al_vect[ 4] = 		       									     (v_vect[3]-v_vect[4])*(ps*m_vect[1] - n_vect[1]*m2) / m2 / mm / nn / d_vect[2] / sin(Alph);
		d_al_vect[ 5] = 		       									     (v_vect[3]-v_vect[4])*(ps*m_vect[2] - n_vect[2]*m2) / m2 / mm / nn / d_vect[2] / sin(Alph);
		d_al_vect[ 6] = 		       									     (v_vect[3]-v_vect[4])*(ps*m_vect[3] - n_vect[3]*m2) / m2 / mm / nn / d_vect[2] / sin(Alph);
		d_al_vect[ 7] = (v_vect[1]-v_vect[4])*(ps*n_vect[1] - m_vect[1]*n2) / n2 / nn / mm / d_vect[1] / sin(Alph) + (v_vect[4]-v_vect[2])*(ps*m_vect[1] - n_vect[1]*m2) / m2 / mm / nn / d_vect[2] / sin(Alph);
		d_al_vect[ 8] = (v_vect[1]-v_vect[4])*(ps*n_vect[2] - m_vect[2]*n2) / n2 / nn / mm / d_vect[1] / sin(Alph) + (v_vect[4]-v_vect[2])*(ps*m_vect[2] - n_vect[2]*m2) / m2 / mm / nn / d_vect[2] / sin(Alph);
		d_al_vect[ 9] = (v_vect[1]-v_vect[4])*(ps*n_vect[3] - m_vect[3]*n2) / n2 / nn / mm / d_vect[1] / sin(Alph) + (v_vect[4]-v_vect[2])*(ps*m_vect[3] - n_vect[3]*m2) / m2 / mm / nn / d_vect[2] / sin(Alph);
		d_al_vect[10] = (v_vect[3]-v_vect[1])*(ps*n_vect[1] - m_vect[1]*n2) / n2 / nn / mm / d_vect[1] / sin(Alph) + (v_vect[2]-v_vect[3])*(ps*m_vect[1] - n_vect[1]*m2) / m2 / mm / nn / d_vect[2] / sin(Alph);
		d_al_vect[11] = (v_vect[3]-v_vect[1])*(ps*n_vect[2] - m_vect[2]*n2) / n2 / nn / mm / d_vect[1] / sin(Alph) + (v_vect[2]-v_vect[3])*(ps*m_vect[2] - n_vect[2]*m2) / m2 / mm / nn / d_vect[2] / sin(Alph);
		d_al_vect[12] = (v_vect[3]-v_vect[1])*(ps*n_vect[3] - m_vect[3]*n2) / n2 / nn / mm / d_vect[1] / sin(Alph) + (v_vect[2]-v_vect[3])*(ps*m_vect[3] - n_vect[3]*m2) / m2 / mm / nn / d_vect[2] / sin(Alph);		
		}
	else
		{
		if (fabs(Alph) <= seui)
			{
			Beta = seui;
			d_al_vect[ 1] = (v_vect[4]-v_vect[3])*(ps*n_vect[1] - m_vect[1]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta);
			d_al_vect[ 2] = (v_vect[4]-v_vect[3])*(ps*n_vect[2] - m_vect[2]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta);
			d_al_vect[ 3] = (v_vect[4]-v_vect[3])*(ps*n_vect[3] - m_vect[3]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta);
			d_al_vect[ 4] = 		       									     (v_vect[3]-v_vect[4])*(ps*m_vect[1] - n_vect[1]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[ 5] = 		       									     (v_vect[3]-v_vect[4])*(ps*m_vect[2] - n_vect[2]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[ 6] = 		       									     (v_vect[3]-v_vect[4])*(ps*m_vect[3] - n_vect[3]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[ 7] = (v_vect[1]-v_vect[4])*(ps*n_vect[1] - m_vect[1]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[4]-v_vect[2])*(ps*m_vect[1] - n_vect[1]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[ 8] = (v_vect[1]-v_vect[4])*(ps*n_vect[2] - m_vect[2]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[4]-v_vect[2])*(ps*m_vect[2] - n_vect[2]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[ 9] = (v_vect[1]-v_vect[4])*(ps*n_vect[3] - m_vect[3]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[4]-v_vect[2])*(ps*m_vect[3] - n_vect[3]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[10] = (v_vect[3]-v_vect[1])*(ps*n_vect[1] - m_vect[1]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[2]-v_vect[3])*(ps*m_vect[1] - n_vect[1]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[11] = (v_vect[3]-v_vect[1])*(ps*n_vect[2] - m_vect[2]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[2]-v_vect[3])*(ps*m_vect[2] - n_vect[2]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[12] = (v_vect[3]-v_vect[1])*(ps*n_vect[3] - m_vect[3]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[2]-v_vect[3])*(ps*m_vect[3] - n_vect[3]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);			
			}
		else
			{
			Beta = PI - seui;
			d_al_vect[ 1] = (v_vect[4]-v_vect[3])*(ps*n_vect[1] - m_vect[1]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta);
			d_al_vect[ 2] = (v_vect[4]-v_vect[3])*(ps*n_vect[2] - m_vect[2]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta);
			d_al_vect[ 3] = (v_vect[4]-v_vect[3])*(ps*n_vect[3] - m_vect[3]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta);
			d_al_vect[ 4] = 		       									     (v_vect[3]-v_vect[4])*(ps*m_vect[1] - n_vect[1]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[ 5] = 		       									     (v_vect[3]-v_vect[4])*(ps*m_vect[2] - n_vect[2]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[ 6] = 		       									     (v_vect[3]-v_vect[4])*(ps*m_vect[3] - n_vect[3]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[ 7] = (v_vect[1]-v_vect[4])*(ps*n_vect[1] - m_vect[1]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[4]-v_vect[2])*(ps*m_vect[1] - n_vect[1]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[ 8] = (v_vect[1]-v_vect[4])*(ps*n_vect[2] - m_vect[2]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[4]-v_vect[2])*(ps*m_vect[2] - n_vect[2]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[ 9] = (v_vect[1]-v_vect[4])*(ps*n_vect[3] - m_vect[3]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[4]-v_vect[2])*(ps*m_vect[3] - n_vect[3]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[10] = (v_vect[3]-v_vect[1])*(ps*n_vect[1] - m_vect[1]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[2]-v_vect[3])*(ps*m_vect[1] - n_vect[1]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[11] = (v_vect[3]-v_vect[1])*(ps*n_vect[2] - m_vect[2]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[2]-v_vect[3])*(ps*m_vect[2] - n_vect[2]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);
			d_al_vect[12] = (v_vect[3]-v_vect[1])*(ps*n_vect[3] - m_vect[3]*n2) / n2 / nn / mm / d_vect[1] / sin(Beta) + (v_vect[2]-v_vect[3])*(ps*m_vect[3] - n_vect[3]*m2) / m2 / mm / nn / d_vect[2] / sin(Beta);		
			}
		}
	}

void diff_coef_vector(double hhh, double Alph, double seui, double nnn, double mmm, double v_vect[5], double d_al_vect[13], double d_nn_vect[13], double d_mm_vect[13], double *d_co_vect)
	{
	double Beta;
 	
   	if ((fabs(Alph) > seui) && (fabs(PI-Alph) > seui))
		{
		d_co_vect[ 1] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[ 1]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[ 1]+nnn*d_mm_vect[ 1])/nnn/mmm);
		d_co_vect[ 2] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[ 2]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[ 2]+nnn*d_mm_vect[ 2])/nnn/mmm);
		d_co_vect[ 3] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[ 3]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[ 3]+nnn*d_mm_vect[ 3])/nnn/mmm);
		d_co_vect[ 4] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[ 4]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[ 4]+nnn*d_mm_vect[ 4])/nnn/mmm);
		d_co_vect[ 5] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[ 5]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[ 5]+nnn*d_mm_vect[ 5])/nnn/mmm);
		d_co_vect[ 6] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[ 6]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[ 6]+nnn*d_mm_vect[ 6])/nnn/mmm);
		d_co_vect[ 7] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[ 7]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[ 7]+nnn*d_mm_vect[ 7])/nnn/mmm);
		d_co_vect[ 8] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[ 8]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[ 8]+nnn*d_mm_vect[ 8])/nnn/mmm);
		d_co_vect[ 9] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[ 9]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[ 9]+nnn*d_mm_vect[ 9])/nnn/mmm);
		d_co_vect[10] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[10]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[10]+nnn*d_mm_vect[10])/nnn/mmm);
		d_co_vect[11] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[11]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[11]+nnn*d_mm_vect[11])/nnn/mmm);
		d_co_vect[12] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Alph) / nnn / mmm * (d_al_vect[12]*(1.0-Alph/tan(Alph)) - Alph*(mmm*d_nn_vect[12]+nnn*d_mm_vect[12])/nnn/mmm);
		}
	else
		{
		if (fabs(Alph) <= seui)
			{
			Beta = seui;
			d_co_vect[ 1] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 1]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 1]+nnn*d_mm_vect[ 1])/nnn/mmm);
			d_co_vect[ 2] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 2]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 2]+nnn*d_mm_vect[ 2])/nnn/mmm);
			d_co_vect[ 3] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 3]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 3]+nnn*d_mm_vect[ 3])/nnn/mmm);
			d_co_vect[ 4] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 4]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 4]+nnn*d_mm_vect[ 4])/nnn/mmm);
			d_co_vect[ 5] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 5]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 5]+nnn*d_mm_vect[ 5])/nnn/mmm);
			d_co_vect[ 6] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 6]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 6]+nnn*d_mm_vect[ 6])/nnn/mmm);
			d_co_vect[ 7] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 7]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 7]+nnn*d_mm_vect[ 7])/nnn/mmm);
			d_co_vect[ 8] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 8]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 8]+nnn*d_mm_vect[ 8])/nnn/mmm);
			d_co_vect[ 9] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 9]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 9]+nnn*d_mm_vect[ 9])/nnn/mmm);
			d_co_vect[10] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[10]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[10]+nnn*d_mm_vect[10])/nnn/mmm);	
			d_co_vect[11] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[11]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[11]+nnn*d_mm_vect[11])/nnn/mmm);
			d_co_vect[12] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[12]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[12]+nnn*d_mm_vect[12])/nnn/mmm);
			}
		else
			{
			Beta = PI - seui;
			d_co_vect[ 1] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 1]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 1]+nnn*d_mm_vect[ 1])/nnn/mmm);
			d_co_vect[ 2] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 2]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 2]+nnn*d_mm_vect[ 2])/nnn/mmm);
			d_co_vect[ 3] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 3]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 3]+nnn*d_mm_vect[ 3])/nnn/mmm);
			d_co_vect[ 4] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 4]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 4]+nnn*d_mm_vect[ 4])/nnn/mmm);
			d_co_vect[ 5] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 5]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 5]+nnn*d_mm_vect[ 5])/nnn/mmm);
			d_co_vect[ 6] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 6]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 6]+nnn*d_mm_vect[ 6])/nnn/mmm);
			d_co_vect[ 7] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 7]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 7]+nnn*d_mm_vect[ 7])/nnn/mmm);
			d_co_vect[ 8] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 8]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 8]+nnn*d_mm_vect[ 8])/nnn/mmm);
			d_co_vect[ 9] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[ 9]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[ 9]+nnn*d_mm_vect[ 9])/nnn/mmm);
			d_co_vect[10] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[10]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[10]+nnn*d_mm_vect[10])/nnn/mmm);
			d_co_vect[11] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[11]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[11]+nnn*d_mm_vect[11])/nnn/mmm);	
			d_co_vect[12] = hhh * fabs(v_vect[3]-v_vect[4]) / sin(Beta) / nnn / mmm * (d_al_vect[12]*(1.0-Alph/tan(Beta)) - Beta*(mmm*d_nn_vect[12]+nnn*d_mm_vect[12])/nnn/mmm);
			}
		}
	}


void diff_fx1_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fx1_vect)
	{
	/*raideur de force_vector[ 1]*/
	/*df_x1 = dcoef * ( ( ps * nx - mx * n2 ) / n2 * (v3-v4) / d1 )  + coef *  ( (( (dps*nx +ps*dnx) - (dmx*n2 + mx*2*n*dn) )*n2 - ( ps * nx - mx * n2 )*2*nn*dn )/ n4 * (v3-v4) / d1 )*/
	
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fx1_vect[ 1] = d_co_vect[ 1] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 1]*n_vect[1] +ps*d_nx_vect[ 1]) - (d_mx_vect[ 1]*n2 + m_vect[1]*2*nn*d_nn_vect[ 1]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 1])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[ 2] = d_co_vect[ 2] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 2]*n_vect[1] +ps*d_nx_vect[ 2]) - (d_mx_vect[ 2]*n2 + m_vect[1]*2*nn*d_nn_vect[ 2]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 2])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[ 3] = d_co_vect[ 3] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 3]*n_vect[1] +ps*d_nx_vect[ 3]) - (d_mx_vect[ 3]*n2 + m_vect[1]*2*nn*d_nn_vect[ 3]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 3])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[ 4] = d_co_vect[ 4] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 4]*n_vect[1] +ps*d_nx_vect[ 4]) - (d_mx_vect[ 4]*n2 + m_vect[1]*2*nn*d_nn_vect[ 4]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 4])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[ 5] = d_co_vect[ 5] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 5]*n_vect[1] +ps*d_nx_vect[ 5]) - (d_mx_vect[ 5]*n2 + m_vect[1]*2*nn*d_nn_vect[ 5]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 5])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[ 6] = d_co_vect[ 6] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 6]*n_vect[1] +ps*d_nx_vect[ 6]) - (d_mx_vect[ 6]*n2 + m_vect[1]*2*nn*d_nn_vect[ 6]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 6])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[ 7] = d_co_vect[ 7] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 7]*n_vect[1] +ps*d_nx_vect[ 7]) - (d_mx_vect[ 7]*n2 + m_vect[1]*2*nn*d_nn_vect[ 7]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 7])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[ 8] = d_co_vect[ 8] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 8]*n_vect[1] +ps*d_nx_vect[ 8]) - (d_mx_vect[ 8]*n2 + m_vect[1]*2*nn*d_nn_vect[ 8]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 8])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[ 9] = d_co_vect[ 9] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 9]*n_vect[1] +ps*d_nx_vect[ 9]) - (d_mx_vect[ 9]*n2 + m_vect[1]*2*nn*d_nn_vect[ 9]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 9])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[10] = d_co_vect[10] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[10]*n_vect[1] +ps*d_nx_vect[10]) - (d_mx_vect[10]*n2 + m_vect[1]*2*nn*d_nn_vect[10]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[10])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[11] = d_co_vect[11] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[11]*n_vect[1] +ps*d_nx_vect[11]) - (d_mx_vect[11]*n2 + m_vect[1]*2*nn*d_nn_vect[11]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[11])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fx1_vect[12] = d_co_vect[12] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[12]*n_vect[1] +ps*d_nx_vect[12]) - (d_mx_vect[12]*n2 + m_vect[1]*2*nn*d_nn_vect[12]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[12])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	}

void diff_fy1_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fy1_vect)
	{
	/*raideur de force_vector[ 2]*/
	
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fy1_vect[ 1] = d_co_vect[ 1] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 1]*n_vect[2] +ps*d_ny_vect[ 1]) - (d_my_vect[ 1]*n2 + m_vect[2]*2*nn*d_nn_vect[ 1]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 1])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[ 2] = d_co_vect[ 2] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 2]*n_vect[2] +ps*d_ny_vect[ 2]) - (d_my_vect[ 2]*n2 + m_vect[2]*2*nn*d_nn_vect[ 2]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 2])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[ 3] = d_co_vect[ 3] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 3]*n_vect[2] +ps*d_ny_vect[ 3]) - (d_my_vect[ 3]*n2 + m_vect[2]*2*nn*d_nn_vect[ 3]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 3])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[ 4] = d_co_vect[ 4] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 4]*n_vect[2] +ps*d_ny_vect[ 4]) - (d_my_vect[ 4]*n2 + m_vect[2]*2*nn*d_nn_vect[ 4]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 4])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[ 5] = d_co_vect[ 5] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 5]*n_vect[2] +ps*d_ny_vect[ 5]) - (d_my_vect[ 5]*n2 + m_vect[2]*2*nn*d_nn_vect[ 5]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 5])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[ 6] = d_co_vect[ 6] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 6]*n_vect[2] +ps*d_ny_vect[ 6]) - (d_my_vect[ 6]*n2 + m_vect[2]*2*nn*d_nn_vect[ 6]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 6])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[ 7] = d_co_vect[ 7] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 7]*n_vect[2] +ps*d_ny_vect[ 7]) - (d_my_vect[ 7]*n2 + m_vect[2]*2*nn*d_nn_vect[ 7]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 7])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[ 8] = d_co_vect[ 8] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 8]*n_vect[2] +ps*d_ny_vect[ 8]) - (d_my_vect[ 8]*n2 + m_vect[2]*2*nn*d_nn_vect[ 8]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 8])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[ 9] = d_co_vect[ 9] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 9]*n_vect[2] +ps*d_ny_vect[ 9]) - (d_my_vect[ 9]*n2 + m_vect[2]*2*nn*d_nn_vect[ 9]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 9])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[10] = d_co_vect[10] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[10]*n_vect[2] +ps*d_ny_vect[10]) - (d_my_vect[10]*n2 + m_vect[2]*2*nn*d_nn_vect[10]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[10])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[11] = d_co_vect[11] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[11]*n_vect[2] +ps*d_ny_vect[11]) - (d_my_vect[11]*n2 + m_vect[2]*2*nn*d_nn_vect[11]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[11])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fy1_vect[12] = d_co_vect[12] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[12]*n_vect[2] +ps*d_ny_vect[12]) - (d_my_vect[12]*n2 + m_vect[2]*2*nn*d_nn_vect[12]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[12])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	}
		
void diff_fz1_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fz1_vect)
	{
	/*raideur de force_vector[ 3]*/
	
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fz1_vect[ 1] = d_co_vect[ 1] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 1]*n_vect[3] +ps*d_nz_vect[ 1]) - (d_mz_vect[ 1]*n2 + m_vect[3]*2*nn*d_nn_vect[ 1]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 1])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[ 2] = d_co_vect[ 2] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 2]*n_vect[3] +ps*d_nz_vect[ 2]) - (d_mz_vect[ 2]*n2 + m_vect[3]*2*nn*d_nn_vect[ 2]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 2])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[ 3] = d_co_vect[ 3] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 3]*n_vect[3] +ps*d_nz_vect[ 3]) - (d_mz_vect[ 3]*n2 + m_vect[3]*2*nn*d_nn_vect[ 3]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 3])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[ 4] = d_co_vect[ 4] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 4]*n_vect[3] +ps*d_nz_vect[ 4]) - (d_mz_vect[ 4]*n2 + m_vect[3]*2*nn*d_nn_vect[ 4]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 4])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[ 5] = d_co_vect[ 5] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 5]*n_vect[3] +ps*d_nz_vect[ 5]) - (d_mz_vect[ 5]*n2 + m_vect[3]*2*nn*d_nn_vect[ 5]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 5])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[ 6] = d_co_vect[ 6] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 6]*n_vect[3] +ps*d_nz_vect[ 6]) - (d_mz_vect[ 6]*n2 + m_vect[3]*2*nn*d_nn_vect[ 6]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 6])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[ 7] = d_co_vect[ 7] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 7]*n_vect[3] +ps*d_nz_vect[ 7]) - (d_mz_vect[ 7]*n2 + m_vect[3]*2*nn*d_nn_vect[ 7]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 7])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[ 8] = d_co_vect[ 8] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 8]*n_vect[3] +ps*d_nz_vect[ 8]) - (d_mz_vect[ 8]*n2 + m_vect[3]*2*nn*d_nn_vect[ 8]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 8])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[ 9] = d_co_vect[ 9] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 9]*n_vect[3] +ps*d_nz_vect[ 9]) - (d_mz_vect[ 9]*n2 + m_vect[3]*2*nn*d_nn_vect[ 9]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 9])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[10] = d_co_vect[10] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[10]*n_vect[3] +ps*d_nz_vect[10]) - (d_mz_vect[10]*n2 + m_vect[3]*2*nn*d_nn_vect[10]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[10])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[11] = d_co_vect[11] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[11]*n_vect[3] +ps*d_nz_vect[11]) - (d_mz_vect[11]*n2 + m_vect[3]*2*nn*d_nn_vect[11]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[11])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	d_fz1_vect[12] = d_co_vect[12] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[3]-v_vect[4]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[12]*n_vect[3] +ps*d_nz_vect[12]) - (d_mz_vect[12]*n2 + m_vect[3]*2*nn*d_nn_vect[12]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[12])/ n4 * (v_vect[3]-v_vect[4]) / d_vect[1] );
	}
	
void diff_fx2_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fx2_vect)
	{
	/*raideur de force_vector[ 4]*/
	
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fx2_vect[ 1] = d_co_vect[ 1] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 1]*m_vect[1] +ps*d_mx_vect[ 1]) - (d_nx_vect[ 1]*m2 + n_vect[1]*2*mm*d_mm_vect[ 1]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 1])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[ 2] = d_co_vect[ 2] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 2]*m_vect[1] +ps*d_mx_vect[ 2]) - (d_nx_vect[ 2]*m2 + n_vect[1]*2*mm*d_mm_vect[ 2]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 2])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[ 3] = d_co_vect[ 3] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 3]*m_vect[1] +ps*d_mx_vect[ 3]) - (d_nx_vect[ 3]*m2 + n_vect[1]*2*mm*d_mm_vect[ 3]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 3])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[ 4] = d_co_vect[ 4] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 4]*m_vect[1] +ps*d_mx_vect[ 4]) - (d_nx_vect[ 4]*m2 + n_vect[1]*2*mm*d_mm_vect[ 4]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 4])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[ 5] = d_co_vect[ 5] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 5]*m_vect[1] +ps*d_mx_vect[ 5]) - (d_nx_vect[ 5]*m2 + n_vect[1]*2*mm*d_mm_vect[ 5]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 5])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[ 6] = d_co_vect[ 6] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 6]*m_vect[1] +ps*d_mx_vect[ 6]) - (d_nx_vect[ 6]*m2 + n_vect[1]*2*mm*d_mm_vect[ 6]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 6])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[ 7] = d_co_vect[ 7] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 7]*m_vect[1] +ps*d_mx_vect[ 7]) - (d_nx_vect[ 7]*m2 + n_vect[1]*2*mm*d_mm_vect[ 7]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 7])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[ 8] = d_co_vect[ 8] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 8]*m_vect[1] +ps*d_mx_vect[ 8]) - (d_nx_vect[ 8]*m2 + n_vect[1]*2*mm*d_mm_vect[ 8]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 8])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[ 9] = d_co_vect[ 9] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 9]*m_vect[1] +ps*d_mx_vect[ 9]) - (d_nx_vect[ 9]*m2 + n_vect[1]*2*mm*d_mm_vect[ 9]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 9])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[10] = d_co_vect[10] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[10]*m_vect[1] +ps*d_mx_vect[10]) - (d_nx_vect[10]*m2 + n_vect[1]*2*mm*d_mm_vect[10]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[10])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[11] = d_co_vect[11] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[11]*m_vect[1] +ps*d_mx_vect[11]) - (d_nx_vect[11]*m2 + n_vect[1]*2*mm*d_mm_vect[11]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[11])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fx2_vect[12] = d_co_vect[12] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[12]*m_vect[1] +ps*d_mx_vect[12]) - (d_nx_vect[12]*m2 + n_vect[1]*2*mm*d_mm_vect[12]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[12])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	}
	
void diff_fy2_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fy2_vect)
	{
	/*raideur de force_vector[ 5]*/
	
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fy2_vect[ 1] = d_co_vect[ 1] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 1]*m_vect[2] +ps*d_my_vect[ 1]) - (d_ny_vect[ 1]*m2 + n_vect[2]*2*mm*d_mm_vect[ 1]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 1])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[ 2] = d_co_vect[ 2] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 2]*m_vect[2] +ps*d_my_vect[ 2]) - (d_ny_vect[ 2]*m2 + n_vect[2]*2*mm*d_mm_vect[ 2]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 2])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[ 3] = d_co_vect[ 3] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 3]*m_vect[2] +ps*d_my_vect[ 3]) - (d_ny_vect[ 3]*m2 + n_vect[2]*2*mm*d_mm_vect[ 3]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 3])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[ 4] = d_co_vect[ 4] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 4]*m_vect[2] +ps*d_my_vect[ 4]) - (d_ny_vect[ 4]*m2 + n_vect[2]*2*mm*d_mm_vect[ 4]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 4])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[ 5] = d_co_vect[ 5] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 5]*m_vect[2] +ps*d_my_vect[ 5]) - (d_ny_vect[ 5]*m2 + n_vect[2]*2*mm*d_mm_vect[ 5]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 5])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[ 6] = d_co_vect[ 6] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 6]*m_vect[2] +ps*d_my_vect[ 6]) - (d_ny_vect[ 6]*m2 + n_vect[2]*2*mm*d_mm_vect[ 6]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 6])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[ 7] = d_co_vect[ 7] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 7]*m_vect[2] +ps*d_my_vect[ 7]) - (d_ny_vect[ 7]*m2 + n_vect[2]*2*mm*d_mm_vect[ 7]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 7])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[ 8] = d_co_vect[ 8] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 8]*m_vect[2] +ps*d_my_vect[ 8]) - (d_ny_vect[ 8]*m2 + n_vect[2]*2*mm*d_mm_vect[ 8]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 8])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[ 9] = d_co_vect[ 9] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 9]*m_vect[2] +ps*d_my_vect[ 9]) - (d_ny_vect[ 9]*m2 + n_vect[2]*2*mm*d_mm_vect[ 9]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 9])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[10] = d_co_vect[10] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[10]*m_vect[2] +ps*d_my_vect[10]) - (d_ny_vect[10]*m2 + n_vect[2]*2*mm*d_mm_vect[10]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[10])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[11] = d_co_vect[11] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[11]*m_vect[2] +ps*d_my_vect[11]) - (d_ny_vect[11]*m2 + n_vect[2]*2*mm*d_mm_vect[11]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[11])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fy2_vect[12] = d_co_vect[12] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[12]*m_vect[2] +ps*d_my_vect[12]) - (d_ny_vect[12]*m2 + n_vect[2]*2*mm*d_mm_vect[12]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[12])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	}
	
void diff_fz2_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fz2_vect)
	{	
	/*raideur de force_vector[ 6]*/

	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fz2_vect[ 1] = d_co_vect[ 1] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 1]*m_vect[3] +ps*d_mz_vect[ 1]) - (d_nz_vect[ 1]*m2 + n_vect[3]*2*mm*d_mm_vect[ 1]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 1])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[ 2] = d_co_vect[ 2] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 2]*m_vect[3] +ps*d_mz_vect[ 2]) - (d_nz_vect[ 2]*m2 + n_vect[3]*2*mm*d_mm_vect[ 2]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 2])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[ 3] = d_co_vect[ 3] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 3]*m_vect[3] +ps*d_mz_vect[ 3]) - (d_nz_vect[ 3]*m2 + n_vect[3]*2*mm*d_mm_vect[ 3]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 3])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[ 4] = d_co_vect[ 4] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 4]*m_vect[3] +ps*d_mz_vect[ 4]) - (d_nz_vect[ 4]*m2 + n_vect[3]*2*mm*d_mm_vect[ 4]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 4])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[ 5] = d_co_vect[ 5] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 5]*m_vect[3] +ps*d_mz_vect[ 5]) - (d_nz_vect[ 5]*m2 + n_vect[3]*2*mm*d_mm_vect[ 5]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 5])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[ 6] = d_co_vect[ 6] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 6]*m_vect[3] +ps*d_mz_vect[ 6]) - (d_nz_vect[ 6]*m2 + n_vect[3]*2*mm*d_mm_vect[ 6]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 6])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[ 7] = d_co_vect[ 7] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 7]*m_vect[3] +ps*d_mz_vect[ 7]) - (d_nz_vect[ 7]*m2 + n_vect[3]*2*mm*d_mm_vect[ 7]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 7])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[ 8] = d_co_vect[ 8] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 8]*m_vect[3] +ps*d_mz_vect[ 8]) - (d_nz_vect[ 8]*m2 + n_vect[3]*2*mm*d_mm_vect[ 8]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 8])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[ 9] = d_co_vect[ 9] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 9]*m_vect[3] +ps*d_mz_vect[ 9]) - (d_nz_vect[ 9]*m2 + n_vect[3]*2*mm*d_mm_vect[ 9]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 9])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[10] = d_co_vect[10] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[10]*m_vect[3] +ps*d_mz_vect[10]) - (d_nz_vect[10]*m2 + n_vect[3]*2*mm*d_mm_vect[10]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[10])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[11] = d_co_vect[11] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[11]*m_vect[3] +ps*d_mz_vect[11]) - (d_nz_vect[11]*m2 + n_vect[3]*2*mm*d_mm_vect[11]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[11])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	d_fz2_vect[12] = d_co_vect[12] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[4]-v_vect[3]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[12]*m_vect[3] +ps*d_mz_vect[12]) - (d_nz_vect[12]*m2 + n_vect[3]*2*mm*d_mm_vect[12]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[12])/ m4 * (v_vect[4]-v_vect[3]) / d_vect[2] );
	}
	
void diff_fx3_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fx3_vect)
	{
	/*raideur de force_vector[ 7]*/
	
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fx3_vect[ 1] = d_co_vect[ 1] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 1]*n_vect[1] +ps*d_nx_vect[ 1]) - (d_mx_vect[ 1]*n2 + m_vect[1]*2*nn*d_nn_vect[ 1]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 1])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 1] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 1]*m_vect[1] +ps*d_mx_vect[ 1]) - (d_nx_vect[ 1]*m2 + n_vect[1]*2*mm*d_mm_vect[ 1]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 1])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[ 2] = d_co_vect[ 2] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 2]*n_vect[1] +ps*d_nx_vect[ 2]) - (d_mx_vect[ 2]*n2 + m_vect[1]*2*nn*d_nn_vect[ 2]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 2])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 2] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 2]*m_vect[1] +ps*d_mx_vect[ 2]) - (d_nx_vect[ 2]*m2 + n_vect[1]*2*mm*d_mm_vect[ 2]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 2])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[ 3] = d_co_vect[ 3] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 3]*n_vect[1] +ps*d_nx_vect[ 3]) - (d_mx_vect[ 3]*n2 + m_vect[1]*2*nn*d_nn_vect[ 3]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 3])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 3] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 3]*m_vect[1] +ps*d_mx_vect[ 3]) - (d_nx_vect[ 3]*m2 + n_vect[1]*2*mm*d_mm_vect[ 3]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 3])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[ 4] = d_co_vect[ 4] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 4]*n_vect[1] +ps*d_nx_vect[ 4]) - (d_mx_vect[ 4]*n2 + m_vect[1]*2*nn*d_nn_vect[ 4]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 4])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 4] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 4]*m_vect[1] +ps*d_mx_vect[ 4]) - (d_nx_vect[ 4]*m2 + n_vect[1]*2*mm*d_mm_vect[ 4]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 4])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[ 5] = d_co_vect[ 5] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 5]*n_vect[1] +ps*d_nx_vect[ 5]) - (d_mx_vect[ 5]*n2 + m_vect[1]*2*nn*d_nn_vect[ 5]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 5])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 5] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 5]*m_vect[1] +ps*d_mx_vect[ 5]) - (d_nx_vect[ 5]*m2 + n_vect[1]*2*mm*d_mm_vect[ 5]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 5])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[ 6] = d_co_vect[ 6] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 6]*n_vect[1] +ps*d_nx_vect[ 6]) - (d_mx_vect[ 6]*n2 + m_vect[1]*2*nn*d_nn_vect[ 6]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 6])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 6] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 6]*m_vect[1] +ps*d_mx_vect[ 6]) - (d_nx_vect[ 6]*m2 + n_vect[1]*2*mm*d_mm_vect[ 6]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 6])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[ 7] = d_co_vect[ 7] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 7]*n_vect[1] +ps*d_nx_vect[ 7]) - (d_mx_vect[ 7]*n2 + m_vect[1]*2*nn*d_nn_vect[ 7]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 7])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 7] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 7]*m_vect[1] +ps*d_mx_vect[ 7]) - (d_nx_vect[ 7]*m2 + n_vect[1]*2*mm*d_mm_vect[ 7]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 7])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[ 8] = d_co_vect[ 8] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 8]*n_vect[1] +ps*d_nx_vect[ 8]) - (d_mx_vect[ 8]*n2 + m_vect[1]*2*nn*d_nn_vect[ 8]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 8])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 8] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 8]*m_vect[1] +ps*d_mx_vect[ 8]) - (d_nx_vect[ 8]*m2 + n_vect[1]*2*mm*d_mm_vect[ 8]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 8])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[ 9] = d_co_vect[ 9] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 9]*n_vect[1] +ps*d_nx_vect[ 9]) - (d_mx_vect[ 9]*n2 + m_vect[1]*2*nn*d_nn_vect[ 9]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 9])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 9] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 9]*m_vect[1] +ps*d_mx_vect[ 9]) - (d_nx_vect[ 9]*m2 + n_vect[1]*2*mm*d_mm_vect[ 9]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 9])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[10] = d_co_vect[10] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[10]*n_vect[1] +ps*d_nx_vect[10]) - (d_mx_vect[10]*n2 + m_vect[1]*2*nn*d_nn_vect[10]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[10])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[10] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[10]*m_vect[1] +ps*d_mx_vect[10]) - (d_nx_vect[10]*m2 + n_vect[1]*2*mm*d_mm_vect[10]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[10])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[11] = d_co_vect[11] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[11]*n_vect[1] +ps*d_nx_vect[11]) - (d_mx_vect[11]*n2 + m_vect[1]*2*nn*d_nn_vect[11]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[11])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[11] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[11]*m_vect[1] +ps*d_mx_vect[11]) - (d_nx_vect[11]*m2 + n_vect[1]*2*mm*d_mm_vect[11]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[11])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fx3_vect[12] = d_co_vect[12] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[12]*n_vect[1] +ps*d_nx_vect[12]) - (d_mx_vect[12]*n2 + m_vect[1]*2*nn*d_nn_vect[12]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[12])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[12] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[12]*m_vect[1] +ps*d_mx_vect[12]) - (d_nx_vect[12]*m2 + n_vect[1]*2*mm*d_mm_vect[12]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[12])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	}
	
void diff_fy3_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fy3_vect)
	{
	/*raideur de force_vector[ 8]*/
	
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fy3_vect[ 1] = d_co_vect[ 1] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 1]*n_vect[2] +ps*d_ny_vect[ 1]) - (d_my_vect[ 1]*n2 + m_vect[2]*2*nn*d_nn_vect[ 1]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 1])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 1] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 1]*m_vect[2] +ps*d_my_vect[ 1]) - (d_ny_vect[ 1]*m2 + n_vect[2]*2*mm*d_mm_vect[ 1]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 1])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[ 2] = d_co_vect[ 2] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 2]*n_vect[2] +ps*d_ny_vect[ 2]) - (d_my_vect[ 2]*n2 + m_vect[2]*2*nn*d_nn_vect[ 2]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 2])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 2] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 2]*m_vect[2] +ps*d_my_vect[ 2]) - (d_ny_vect[ 2]*m2 + n_vect[2]*2*mm*d_mm_vect[ 2]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 2])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[ 3] = d_co_vect[ 3] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 3]*n_vect[2] +ps*d_ny_vect[ 3]) - (d_my_vect[ 3]*n2 + m_vect[2]*2*nn*d_nn_vect[ 3]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 3])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 3] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 3]*m_vect[2] +ps*d_my_vect[ 3]) - (d_ny_vect[ 3]*m2 + n_vect[2]*2*mm*d_mm_vect[ 3]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 3])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[ 4] = d_co_vect[ 4] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 4]*n_vect[2] +ps*d_ny_vect[ 4]) - (d_my_vect[ 4]*n2 + m_vect[2]*2*nn*d_nn_vect[ 4]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 4])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 4] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 4]*m_vect[2] +ps*d_my_vect[ 4]) - (d_ny_vect[ 4]*m2 + n_vect[2]*2*mm*d_mm_vect[ 4]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 4])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[ 5] = d_co_vect[ 5] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 5]*n_vect[2] +ps*d_ny_vect[ 5]) - (d_my_vect[ 5]*n2 + m_vect[2]*2*nn*d_nn_vect[ 5]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 5])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 5] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 5]*m_vect[2] +ps*d_my_vect[ 5]) - (d_ny_vect[ 5]*m2 + n_vect[2]*2*mm*d_mm_vect[ 5]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 5])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[ 6] = d_co_vect[ 6] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 6]*n_vect[2] +ps*d_ny_vect[ 6]) - (d_my_vect[ 6]*n2 + m_vect[2]*2*nn*d_nn_vect[ 6]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 6])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 6] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 6]*m_vect[2] +ps*d_my_vect[ 6]) - (d_ny_vect[ 6]*m2 + n_vect[2]*2*mm*d_mm_vect[ 6]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 6])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[ 7] = d_co_vect[ 7] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 7]*n_vect[2] +ps*d_ny_vect[ 7]) - (d_my_vect[ 7]*n2 + m_vect[2]*2*nn*d_nn_vect[ 7]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 7])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 7] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 7]*m_vect[2] +ps*d_my_vect[ 7]) - (d_ny_vect[ 7]*m2 + n_vect[2]*2*mm*d_mm_vect[ 7]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 7])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[ 8] = d_co_vect[ 8] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 8]*n_vect[2] +ps*d_ny_vect[ 8]) - (d_my_vect[ 8]*n2 + m_vect[2]*2*nn*d_nn_vect[ 8]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 8])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 8] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 8]*m_vect[2] +ps*d_my_vect[ 8]) - (d_ny_vect[ 8]*m2 + n_vect[2]*2*mm*d_mm_vect[ 8]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 8])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[ 9] = d_co_vect[ 9] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 9]*n_vect[2] +ps*d_ny_vect[ 9]) - (d_my_vect[ 9]*n2 + m_vect[2]*2*nn*d_nn_vect[ 9]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 9])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[ 9] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 9]*m_vect[2] +ps*d_my_vect[ 9]) - (d_ny_vect[ 9]*m2 + n_vect[2]*2*mm*d_mm_vect[ 9]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 9])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[10] = d_co_vect[10] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[10]*n_vect[2] +ps*d_ny_vect[10]) - (d_my_vect[10]*n2 + m_vect[2]*2*nn*d_nn_vect[10]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[10])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[10] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[10]*m_vect[2] +ps*d_my_vect[10]) - (d_ny_vect[10]*m2 + n_vect[2]*2*mm*d_mm_vect[10]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[10])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[11] = d_co_vect[11] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[11]*n_vect[2] +ps*d_ny_vect[11]) - (d_my_vect[11]*n2 + m_vect[2]*2*nn*d_nn_vect[11]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[11])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[11] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[11]*m_vect[2] +ps*d_my_vect[11]) - (d_ny_vect[11]*m2 + n_vect[2]*2*mm*d_mm_vect[11]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[11])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fy3_vect[12] = d_co_vect[12] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[12]*n_vect[2] +ps*d_ny_vect[12]) - (d_my_vect[12]*n2 + m_vect[2]*2*nn*d_nn_vect[12]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[12])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
               	       + d_co_vect[12] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[12]*m_vect[2] +ps*d_my_vect[12]) - (d_ny_vect[12]*m2 + n_vect[2]*2*mm*d_mm_vect[12]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[12])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	}
	
void diff_fz3_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fz3_vect)
	{
	/*raideur de force_vector[ 9]*/
	
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fz3_vect[ 1] = d_co_vect[ 1] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 1]*n_vect[3] +ps*d_nz_vect[ 1]) - (d_mz_vect[ 1]*n2 + m_vect[3]*2*nn*d_nn_vect[ 1]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 1])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[ 1] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 1]*m_vect[3] +ps*d_mz_vect[ 1]) - (d_nz_vect[ 1]*m2 + n_vect[3]*2*mm*d_mm_vect[ 1]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 1])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[ 2] = d_co_vect[ 2] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 2]*n_vect[3] +ps*d_nz_vect[ 2]) - (d_mz_vect[ 2]*n2 + m_vect[3]*2*nn*d_nn_vect[ 2]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 2])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[ 2] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 2]*m_vect[3] +ps*d_mz_vect[ 2]) - (d_nz_vect[ 2]*m2 + n_vect[3]*2*mm*d_mm_vect[ 2]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 2])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[ 3] = d_co_vect[ 3] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 3]*n_vect[3] +ps*d_nz_vect[ 3]) - (d_mz_vect[ 3]*n2 + m_vect[3]*2*nn*d_nn_vect[ 3]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 3])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[ 3] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 3]*m_vect[3] +ps*d_mz_vect[ 3]) - (d_nz_vect[ 3]*m2 + n_vect[3]*2*mm*d_mm_vect[ 3]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 3])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[ 4] = d_co_vect[ 4] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 4]*n_vect[3] +ps*d_nz_vect[ 4]) - (d_mz_vect[ 4]*n2 + m_vect[3]*2*nn*d_nn_vect[ 4]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 4])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[ 4] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 4]*m_vect[3] +ps*d_mz_vect[ 4]) - (d_nz_vect[ 4]*m2 + n_vect[3]*2*mm*d_mm_vect[ 4]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 4])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[ 5] = d_co_vect[ 5] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 5]*n_vect[3] +ps*d_nz_vect[ 5]) - (d_mz_vect[ 5]*n2 + m_vect[3]*2*nn*d_nn_vect[ 5]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 5])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[ 5] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 5]*m_vect[3] +ps*d_mz_vect[ 5]) - (d_nz_vect[ 5]*m2 + n_vect[3]*2*mm*d_mm_vect[ 5]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 5])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[ 6] = d_co_vect[ 6] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 6]*n_vect[3] +ps*d_nz_vect[ 6]) - (d_mz_vect[ 6]*n2 + m_vect[3]*2*nn*d_nn_vect[ 6]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 6])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[ 6] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 6]*m_vect[3] +ps*d_mz_vect[ 6]) - (d_nz_vect[ 6]*m2 + n_vect[3]*2*mm*d_mm_vect[ 6]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 6])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[ 7] = d_co_vect[ 7] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 7]*n_vect[3] +ps*d_nz_vect[ 7]) - (d_mz_vect[ 7]*n2 + m_vect[3]*2*nn*d_nn_vect[ 7]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 7])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[ 7] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 7]*m_vect[3] +ps*d_mz_vect[ 7]) - (d_nz_vect[ 7]*m2 + n_vect[3]*2*mm*d_mm_vect[ 7]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 7])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[ 8] = d_co_vect[ 8] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 8]*n_vect[3] +ps*d_nz_vect[ 8]) - (d_mz_vect[ 8]*n2 + m_vect[3]*2*nn*d_nn_vect[ 8]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 8])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[ 8] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 8]*m_vect[3] +ps*d_mz_vect[ 8]) - (d_nz_vect[ 8]*m2 + n_vect[3]*2*mm*d_mm_vect[ 8]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 8])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[ 9] = d_co_vect[ 9] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 9]*n_vect[3] +ps*d_nz_vect[ 9]) - (d_mz_vect[ 9]*n2 + m_vect[3]*2*nn*d_nn_vect[ 9]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 9])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[ 9] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 9]*m_vect[3] +ps*d_mz_vect[ 9]) - (d_nz_vect[ 9]*m2 + n_vect[3]*2*mm*d_mm_vect[ 9]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 9])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[10] = d_co_vect[10] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[10]*n_vect[3] +ps*d_nz_vect[10]) - (d_mz_vect[10]*n2 + m_vect[3]*2*nn*d_nn_vect[10]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[10])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[10] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[10]*m_vect[3] +ps*d_mz_vect[10]) - (d_nz_vect[10]*m2 + n_vect[3]*2*mm*d_mm_vect[10]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[10])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[11] = d_co_vect[11] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[11]*n_vect[3] +ps*d_nz_vect[11]) - (d_mz_vect[11]*n2 + m_vect[3]*2*nn*d_nn_vect[11]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[11])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[11] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[11]*m_vect[3] +ps*d_mz_vect[11]) - (d_nz_vect[11]*m2 + n_vect[3]*2*mm*d_mm_vect[11]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[11])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	d_fz3_vect[12] = d_co_vect[12] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[4]-v_vect[1]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[12]*n_vect[3] +ps*d_nz_vect[12]) - (d_mz_vect[12]*n2 + m_vect[3]*2*nn*d_nn_vect[12]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[12])/ n4 * (v_vect[4]-v_vect[1]) / d_vect[1] )
              	       + d_co_vect[12] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[2]-v_vect[4]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[12]*m_vect[3] +ps*d_mz_vect[12]) - (d_nz_vect[12]*m2 + n_vect[3]*2*mm*d_mm_vect[12]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[12])/ m4 * (v_vect[2]-v_vect[4]) / d_vect[2] );
	}
	
void diff_fx4_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fx4_vect)
	{
	/*raideur de force_vector[10]*/
	
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fx4_vect[ 1] = d_co_vect[ 1] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 1]*n_vect[1] +ps*d_nx_vect[ 1]) - (d_mx_vect[ 1]*n2 + m_vect[1]*2*nn*d_nn_vect[ 1]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 1])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[ 1] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 1]*m_vect[1] +ps*d_mx_vect[ 1]) - (d_nx_vect[ 1]*m2 + n_vect[1]*2*mm*d_mm_vect[ 1]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 1])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[ 2] = d_co_vect[ 2] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 2]*n_vect[1] +ps*d_nx_vect[ 2]) - (d_mx_vect[ 2]*n2 + m_vect[1]*2*nn*d_nn_vect[ 2]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 2])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[ 2] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 2]*m_vect[1] +ps*d_mx_vect[ 2]) - (d_nx_vect[ 2]*m2 + n_vect[1]*2*mm*d_mm_vect[ 2]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 2])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[ 3] = d_co_vect[ 3] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 3]*n_vect[1] +ps*d_nx_vect[ 3]) - (d_mx_vect[ 3]*n2 + m_vect[1]*2*nn*d_nn_vect[ 3]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 3])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[ 3] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 3]*m_vect[1] +ps*d_mx_vect[ 3]) - (d_nx_vect[ 3]*m2 + n_vect[1]*2*mm*d_mm_vect[ 3]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 3])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[ 4] = d_co_vect[ 4] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 4]*n_vect[1] +ps*d_nx_vect[ 4]) - (d_mx_vect[ 4]*n2 + m_vect[1]*2*nn*d_nn_vect[ 4]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 4])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[ 4] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 4]*m_vect[1] +ps*d_mx_vect[ 4]) - (d_nx_vect[ 4]*m2 + n_vect[1]*2*mm*d_mm_vect[ 4]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 4])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[ 5] = d_co_vect[ 5] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 5]*n_vect[1] +ps*d_nx_vect[ 5]) - (d_mx_vect[ 5]*n2 + m_vect[1]*2*nn*d_nn_vect[ 5]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 5])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[ 5] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 5]*m_vect[1] +ps*d_mx_vect[ 5]) - (d_nx_vect[ 5]*m2 + n_vect[1]*2*mm*d_mm_vect[ 5]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 5])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[ 6] = d_co_vect[ 6] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 6]*n_vect[1] +ps*d_nx_vect[ 6]) - (d_mx_vect[ 6]*n2 + m_vect[1]*2*nn*d_nn_vect[ 6]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 6])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[ 6] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 6]*m_vect[1] +ps*d_mx_vect[ 6]) - (d_nx_vect[ 6]*m2 + n_vect[1]*2*mm*d_mm_vect[ 6]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 6])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[ 7] = d_co_vect[ 7] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 7]*n_vect[1] +ps*d_nx_vect[ 7]) - (d_mx_vect[ 7]*n2 + m_vect[1]*2*nn*d_nn_vect[ 7]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 7])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[ 7] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 7]*m_vect[1] +ps*d_mx_vect[ 7]) - (d_nx_vect[ 7]*m2 + n_vect[1]*2*mm*d_mm_vect[ 7]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 7])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[ 8] = d_co_vect[ 8] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 8]*n_vect[1] +ps*d_nx_vect[ 8]) - (d_mx_vect[ 8]*n2 + m_vect[1]*2*nn*d_nn_vect[ 8]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 8])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[ 8] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 8]*m_vect[1] +ps*d_mx_vect[ 8]) - (d_nx_vect[ 8]*m2 + n_vect[1]*2*mm*d_mm_vect[ 8]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 8])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[ 9] = d_co_vect[ 9] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 9]*n_vect[1] +ps*d_nx_vect[ 9]) - (d_mx_vect[ 9]*n2 + m_vect[1]*2*nn*d_nn_vect[ 9]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[ 9])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[ 9] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 9]*m_vect[1] +ps*d_mx_vect[ 9]) - (d_nx_vect[ 9]*m2 + n_vect[1]*2*mm*d_mm_vect[ 9]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[ 9])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[10] = d_co_vect[10] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[10]*n_vect[1] +ps*d_nx_vect[10]) - (d_mx_vect[10]*n2 + m_vect[1]*2*nn*d_nn_vect[10]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[10])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[10] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[10]*m_vect[1] +ps*d_mx_vect[10]) - (d_nx_vect[10]*m2 + n_vect[1]*2*mm*d_mm_vect[10]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[10])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[11] = d_co_vect[11] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[11]*n_vect[1] +ps*d_nx_vect[11]) - (d_mx_vect[11]*n2 + m_vect[1]*2*nn*d_nn_vect[11]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[11])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[11] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[11]*m_vect[1] +ps*d_mx_vect[11]) - (d_nx_vect[11]*m2 + n_vect[1]*2*mm*d_mm_vect[11]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[11])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fx4_vect[12] = d_co_vect[12] * ( ( ps * n_vect[1] - m_vect[1] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[12]*n_vect[1] +ps*d_nx_vect[12]) - (d_mx_vect[12]*n2 + m_vect[1]*2*nn*d_nn_vect[12]) )*n2 - ( ps * n_vect[1] - m_vect[1] * n2 )*2*nn*d_nn_vect[12])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
          	       + d_co_vect[12] * ( ( ps * m_vect[1] - n_vect[1] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[12]*m_vect[1] +ps*d_mx_vect[12]) - (d_nx_vect[12]*m2 + n_vect[1]*2*mm*d_mm_vect[12]) )*m2 - ( ps * m_vect[1] - n_vect[1] * m2 )*2*mm*d_mm_vect[12])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	}
	
void diff_fy4_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fy4_vect)
	{
	/*raideur de force_vector[11]*/
	
	double UU,VV,Up,Vp;
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fy4_vect[ 1] = d_co_vect[ 1] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 1]*n_vect[2] +ps*d_ny_vect[ 1]) - (d_my_vect[ 1]*n2 + m_vect[2]*2*nn*d_nn_vect[ 1]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 1])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[ 1] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 1]*m_vect[2] +ps*d_my_vect[ 1]) - (d_ny_vect[ 1]*m2 + n_vect[2]*2*mm*d_mm_vect[ 1]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 1])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[ 2] = d_co_vect[ 2] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 2]*n_vect[2] +ps*d_ny_vect[ 2]) - (d_my_vect[ 2]*n2 + m_vect[2]*2*nn*d_nn_vect[ 2]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 2])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[ 2] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 2]*m_vect[2] +ps*d_my_vect[ 2]) - (d_ny_vect[ 2]*m2 + n_vect[2]*2*mm*d_mm_vect[ 2]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 2])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[ 3] = d_co_vect[ 3] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 3]*n_vect[2] +ps*d_ny_vect[ 3]) - (d_my_vect[ 3]*n2 + m_vect[2]*2*nn*d_nn_vect[ 3]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 3])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[ 3] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 3]*m_vect[2] +ps*d_my_vect[ 3]) - (d_ny_vect[ 3]*m2 + n_vect[2]*2*mm*d_mm_vect[ 3]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 3])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[ 4] = d_co_vect[ 4] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 4]*n_vect[2] +ps*d_ny_vect[ 4]) - (d_my_vect[ 4]*n2 + m_vect[2]*2*nn*d_nn_vect[ 4]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 4])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[ 4] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 4]*m_vect[2] +ps*d_my_vect[ 4]) - (d_ny_vect[ 4]*m2 + n_vect[2]*2*mm*d_mm_vect[ 4]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 4])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[ 5] = d_co_vect[ 5] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 5]*n_vect[2] +ps*d_ny_vect[ 5]) - (d_my_vect[ 5]*n2 + m_vect[2]*2*nn*d_nn_vect[ 5]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 5])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[ 5] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 5]*m_vect[2] +ps*d_my_vect[ 5]) - (d_ny_vect[ 5]*m2 + n_vect[2]*2*mm*d_mm_vect[ 5]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 5])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[ 6] = d_co_vect[ 6] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 6]*n_vect[2] +ps*d_ny_vect[ 6]) - (d_my_vect[ 6]*n2 + m_vect[2]*2*nn*d_nn_vect[ 6]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 6])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[ 6] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 6]*m_vect[2] +ps*d_my_vect[ 6]) - (d_ny_vect[ 6]*m2 + n_vect[2]*2*mm*d_mm_vect[ 6]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 6])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[ 7] = d_co_vect[ 7] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 7]*n_vect[2] +ps*d_ny_vect[ 7]) - (d_my_vect[ 7]*n2 + m_vect[2]*2*nn*d_nn_vect[ 7]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 7])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[ 7] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 7]*m_vect[2] +ps*d_my_vect[ 7]) - (d_ny_vect[ 7]*m2 + n_vect[2]*2*mm*d_mm_vect[ 7]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 7])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[ 8] = d_co_vect[ 8] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 8]*n_vect[2] +ps*d_ny_vect[ 8]) - (d_my_vect[ 8]*n2 + m_vect[2]*2*nn*d_nn_vect[ 8]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 8])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[ 8] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 8]*m_vect[2] +ps*d_my_vect[ 8]) - (d_ny_vect[ 8]*m2 + n_vect[2]*2*mm*d_mm_vect[ 8]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 8])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[ 9] = d_co_vect[ 9] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 9]*n_vect[2] +ps*d_ny_vect[ 9]) - (d_my_vect[ 9]*n2 + m_vect[2]*2*nn*d_nn_vect[ 9]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[ 9])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[ 9] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 9]*m_vect[2] +ps*d_my_vect[ 9]) - (d_ny_vect[ 9]*m2 + n_vect[2]*2*mm*d_mm_vect[ 9]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[ 9])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[10] = d_co_vect[10] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[10]*n_vect[2] +ps*d_ny_vect[10]) - (d_my_vect[10]*n2 + m_vect[2]*2*nn*d_nn_vect[10]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[10])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[10] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[10]*m_vect[2] +ps*d_my_vect[10]) - (d_ny_vect[10]*m2 + n_vect[2]*2*mm*d_mm_vect[10]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[10])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[11] = d_co_vect[11] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[11]*n_vect[2] +ps*d_ny_vect[11]) - (d_my_vect[11]*n2 + m_vect[2]*2*nn*d_nn_vect[11]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[11])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[11] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[11]*m_vect[2] +ps*d_my_vect[11]) - (d_ny_vect[11]*m2 + n_vect[2]*2*mm*d_mm_vect[11]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[11])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fy4_vect[12] = d_co_vect[12] * ( ( ps * n_vect[2] - m_vect[2] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[12]*n_vect[2] +ps*d_ny_vect[12]) - (d_my_vect[12]*n2 + m_vect[2]*2*nn*d_nn_vect[12]) )*n2 - ( ps * n_vect[2] - m_vect[2] * n2 )*2*nn*d_nn_vect[12])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
        	       + d_co_vect[12] * ( ( ps * m_vect[2] - n_vect[2] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[12]*m_vect[2] +ps*d_my_vect[12]) - (d_ny_vect[12]*m2 + n_vect[2]*2*mm*d_mm_vect[12]) )*m2 - ( ps * m_vect[2] - n_vect[2] * m2 )*2*mm*d_mm_vect[12])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	}
	
void diff_fz4_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fz4_vect)
	{
	/*raideur de force_vector[12]*/
	
	double ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	d_fz4_vect[ 1] = d_co_vect[ 1] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 1]*n_vect[3] +ps*d_nz_vect[ 1]) - (d_mz_vect[ 1]*n2 + m_vect[3]*2*nn*d_nn_vect[ 1]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 1])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[ 1] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 1]*m_vect[3] +ps*d_mz_vect[ 1]) - (d_nz_vect[ 1]*m2 + n_vect[3]*2*mm*d_mm_vect[ 1]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 1])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[ 2] = d_co_vect[ 2] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 2]*n_vect[3] +ps*d_nz_vect[ 2]) - (d_mz_vect[ 2]*n2 + m_vect[3]*2*nn*d_nn_vect[ 2]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 2])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[ 2] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 2]*m_vect[3] +ps*d_mz_vect[ 2]) - (d_nz_vect[ 2]*m2 + n_vect[3]*2*mm*d_mm_vect[ 2]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 2])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[ 3] = d_co_vect[ 3] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 3]*n_vect[3] +ps*d_nz_vect[ 3]) - (d_mz_vect[ 3]*n2 + m_vect[3]*2*nn*d_nn_vect[ 3]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 3])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[ 3] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 3]*m_vect[3] +ps*d_mz_vect[ 3]) - (d_nz_vect[ 3]*m2 + n_vect[3]*2*mm*d_mm_vect[ 3]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 3])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[ 4] = d_co_vect[ 4] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 4]*n_vect[3] +ps*d_nz_vect[ 4]) - (d_mz_vect[ 4]*n2 + m_vect[3]*2*nn*d_nn_vect[ 4]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 4])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[ 4] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 4]*m_vect[3] +ps*d_mz_vect[ 4]) - (d_nz_vect[ 4]*m2 + n_vect[3]*2*mm*d_mm_vect[ 4]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 4])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[ 5] = d_co_vect[ 5] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 5]*n_vect[3] +ps*d_nz_vect[ 5]) - (d_mz_vect[ 5]*n2 + m_vect[3]*2*nn*d_nn_vect[ 5]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 5])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[ 5] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 5]*m_vect[3] +ps*d_mz_vect[ 5]) - (d_nz_vect[ 5]*m2 + n_vect[3]*2*mm*d_mm_vect[ 5]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 5])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[ 6] = d_co_vect[ 6] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 6]*n_vect[3] +ps*d_nz_vect[ 6]) - (d_mz_vect[ 6]*n2 + m_vect[3]*2*nn*d_nn_vect[ 6]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 6])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[ 6] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 6]*m_vect[3] +ps*d_mz_vect[ 6]) - (d_nz_vect[ 6]*m2 + n_vect[3]*2*mm*d_mm_vect[ 6]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 6])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[ 7] = d_co_vect[ 7] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 7]*n_vect[3] +ps*d_nz_vect[ 7]) - (d_mz_vect[ 7]*n2 + m_vect[3]*2*nn*d_nn_vect[ 7]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 7])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[ 7] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 7]*m_vect[3] +ps*d_mz_vect[ 7]) - (d_nz_vect[ 7]*m2 + n_vect[3]*2*mm*d_mm_vect[ 7]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 7])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[ 8] = d_co_vect[ 8] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 8]*n_vect[3] +ps*d_nz_vect[ 8]) - (d_mz_vect[ 8]*n2 + m_vect[3]*2*nn*d_nn_vect[ 8]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 8])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[ 8] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 8]*m_vect[3] +ps*d_mz_vect[ 8]) - (d_nz_vect[ 8]*m2 + n_vect[3]*2*mm*d_mm_vect[ 8]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 8])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[ 9] = d_co_vect[ 9] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[ 9]*n_vect[3] +ps*d_nz_vect[ 9]) - (d_mz_vect[ 9]*n2 + m_vect[3]*2*nn*d_nn_vect[ 9]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[ 9])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[ 9] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[ 9]*m_vect[3] +ps*d_mz_vect[ 9]) - (d_nz_vect[ 9]*m2 + n_vect[3]*2*mm*d_mm_vect[ 9]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[ 9])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[10] = d_co_vect[10] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[10]*n_vect[3] +ps*d_nz_vect[10]) - (d_mz_vect[10]*n2 + m_vect[3]*2*nn*d_nn_vect[10]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[10])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[10] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[10]*m_vect[3] +ps*d_mz_vect[10]) - (d_nz_vect[10]*m2 + n_vect[3]*2*mm*d_mm_vect[10]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[10])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[11] = d_co_vect[11] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[11]*n_vect[3] +ps*d_nz_vect[11]) - (d_mz_vect[11]*n2 + m_vect[3]*2*nn*d_nn_vect[11]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[11])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[11] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[11]*m_vect[3] +ps*d_mz_vect[11]) - (d_nz_vect[11]*m2 + n_vect[3]*2*mm*d_mm_vect[11]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[11])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	d_fz4_vect[12] = d_co_vect[12] * ( ( ps * n_vect[3] - m_vect[3] * n2 ) / n2 * (v_vect[1]-v_vect[3]) / d_vect[1] )  + coe *  ( (( (d_ps_vect[12]*n_vect[3] +ps*d_nz_vect[12]) - (d_mz_vect[12]*n2 + m_vect[3]*2*nn*d_nn_vect[12]) )*n2 - ( ps * n_vect[3] - m_vect[3] * n2 )*2*nn*d_nn_vect[12])/ n4 * (v_vect[1]-v_vect[3]) / d_vect[1] )
               	       + d_co_vect[12] * ( ( ps * m_vect[3] - n_vect[3] * m2 ) / m2 * (v_vect[3]-v_vect[2]) / d_vect[2] )  + coe *  ( (( (d_ps_vect[12]*m_vect[3] +ps*d_mz_vect[12]) - (d_nz_vect[12]*m2 + n_vect[3]*2*mm*d_mm_vect[12]) )*m2 - ( ps * m_vect[3] - n_vect[3] * m2 )*2*mm*d_mm_vect[12])/ m4 * (v_vect[3]-v_vect[2]) / d_vect[2] );
	}
	
	
void diff_alphax1_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nx_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_ps_vect[13], double *d_alphax1_vect)
	{
	/*raideur de alpha_x1*/
	
	double UU,UP,VV,VP,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU = ps*n_vect[1] - m_vect[1]*n2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV = n2*nn*mm*d_vect[1]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV = n2*nn*mm*d_vect[1]*sin(0.00001);
			}
		else
			{
			VV = n2*nn*mm*d_vect[1]*sin(0.00001-PI);
			}
		}
	
	UP = d_ps_vect[ 1]*n_vect[1] + ps*d_nx_vect[ 1] - d_mx_vect[ 1]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 1];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 1]*mm*sin(alph) + n2*nn*d_mm_vect[ 1]*sin(alph) + n2*nn*mm*d_alpha[ 1]*cos(alph));
	d_alphax1_vect[ 1] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 2]*n_vect[1] + ps*d_nx_vect[ 2] - d_mx_vect[ 2]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 2];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 2]*mm*sin(alph) + n2*nn*d_mm_vect[ 2]*sin(alph) + n2*nn*mm*d_alpha[ 2]*cos(alph));
	d_alphax1_vect[ 2] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 3]*n_vect[1] + ps*d_nx_vect[ 3] - d_mx_vect[ 3]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 3];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 3]*mm*sin(alph) + n2*nn*d_mm_vect[ 3]*sin(alph) + n2*nn*mm*d_alpha[ 3]*cos(alph));
	d_alphax1_vect[ 3] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 4]*n_vect[1] + ps*d_nx_vect[ 4] - d_mx_vect[ 4]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 4];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 4]*mm*sin(alph) + n2*nn*d_mm_vect[ 4]*sin(alph) + n2*nn*mm*d_alpha[ 4]*cos(alph));
	d_alphax1_vect[ 4] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 5]*n_vect[1] + ps*d_nx_vect[ 5] - d_mx_vect[ 5]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 5];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 5]*mm*sin(alph) + n2*nn*d_mm_vect[ 5]*sin(alph) + n2*nn*mm*d_alpha[ 5]*cos(alph));
	d_alphax1_vect[ 5] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 6]*n_vect[1] + ps*d_nx_vect[ 6] - d_mx_vect[ 6]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 6];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 6]*mm*sin(alph) + n2*nn*d_mm_vect[ 6]*sin(alph) + n2*nn*mm*d_alpha[ 6]*cos(alph));
	d_alphax1_vect[ 6] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 7]*n_vect[1] + ps*d_nx_vect[ 7] - d_mx_vect[ 7]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 7];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 7]*mm*sin(alph) + n2*nn*d_mm_vect[ 7]*sin(alph) + n2*nn*mm*d_alpha[ 7]*cos(alph));
	d_alphax1_vect[ 7] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 8]*n_vect[1] + ps*d_nx_vect[ 8] - d_mx_vect[ 8]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 8];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 8]*mm*sin(alph) + n2*nn*d_mm_vect[ 8]*sin(alph) + n2*nn*mm*d_alpha[ 8]*cos(alph));
	d_alphax1_vect[ 8] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 9]*n_vect[1] + ps*d_nx_vect[ 9] - d_mx_vect[ 9]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 9];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 9]*mm*sin(alph) + n2*nn*d_mm_vect[ 9]*sin(alph) + n2*nn*mm*d_alpha[ 9]*cos(alph));
	d_alphax1_vect[ 9] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[10]*n_vect[1] + ps*d_nx_vect[10] - d_mx_vect[10]*n2 - m_vect[1]*2.0*nn*d_nn_vect[10];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[10]*mm*sin(alph) + n2*nn*d_mm_vect[10]*sin(alph) + n2*nn*mm*d_alpha[10]*cos(alph));
	d_alphax1_vect[10] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[11]*n_vect[1] + ps*d_nx_vect[11] - d_mx_vect[11]*n2 - m_vect[1]*2.0*nn*d_nn_vect[11];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[11]*mm*sin(alph) + n2*nn*d_mm_vect[11]*sin(alph) + n2*nn*mm*d_alpha[11]*cos(alph));
	d_alphax1_vect[11] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[12]*n_vect[1] + ps*d_nx_vect[12] - d_mx_vect[12]*n2 - m_vect[1]*2.0*nn*d_nn_vect[12];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[12]*mm*sin(alph) + n2*nn*d_mm_vect[12]*sin(alph) + n2*nn*mm*d_alpha[12]*cos(alph));
	d_alphax1_vect[12] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	}
	

void diff_alphay1_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_ny_vect[13], double d_mm_vect[13], double d_my_vect[13], double d_ps_vect[13], double *d_alphay1_vect)
	{
	/*raideur de alpha_y1*/
	
	double UU,UP,VV,VP,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU = ps*n_vect[2] - m_vect[2]*n2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV = n2*nn*mm*d_vect[1]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV = n2*nn*mm*d_vect[1]*sin(0.00001);
			}
		else
			{
			VV = n2*nn*mm*d_vect[1]*sin(0.00001-PI);
			}
		}

	UP = d_ps_vect[ 1]*n_vect[2] + ps*d_ny_vect[ 1] - d_my_vect[ 1]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 1];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 1]*mm*sin(alph) + n2*nn*d_mm_vect[ 1]*sin(alph) + n2*nn*mm*d_alpha[ 1]*cos(alph));
	d_alphay1_vect[ 1] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 2]*n_vect[2] + ps*d_ny_vect[ 2] - d_my_vect[ 2]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 2];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 2]*mm*sin(alph) + n2*nn*d_mm_vect[ 2]*sin(alph) + n2*nn*mm*d_alpha[ 2]*cos(alph));
	d_alphay1_vect[ 2] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 3]*n_vect[2] + ps*d_ny_vect[ 3] - d_my_vect[ 3]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 3];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 3]*mm*sin(alph) + n2*nn*d_mm_vect[ 3]*sin(alph) + n2*nn*mm*d_alpha[ 3]*cos(alph));
	d_alphay1_vect[ 3] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 4]*n_vect[2] + ps*d_ny_vect[ 4] - d_my_vect[ 4]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 4];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 4]*mm*sin(alph) + n2*nn*d_mm_vect[ 4]*sin(alph) + n2*nn*mm*d_alpha[ 4]*cos(alph));
	d_alphay1_vect[ 4] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 5]*n_vect[2] + ps*d_ny_vect[ 5] - d_my_vect[ 5]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 5];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 5]*mm*sin(alph) + n2*nn*d_mm_vect[ 5]*sin(alph) + n2*nn*mm*d_alpha[ 5]*cos(alph));
	d_alphay1_vect[ 5] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 6]*n_vect[2] + ps*d_ny_vect[ 6] - d_my_vect[ 6]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 6];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 6]*mm*sin(alph) + n2*nn*d_mm_vect[ 6]*sin(alph) + n2*nn*mm*d_alpha[ 6]*cos(alph));
	d_alphay1_vect[ 6] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 7]*n_vect[2] + ps*d_ny_vect[ 7] - d_my_vect[ 7]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 7];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 7]*mm*sin(alph) + n2*nn*d_mm_vect[ 7]*sin(alph) + n2*nn*mm*d_alpha[ 7]*cos(alph));
	d_alphay1_vect[ 7] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 8]*n_vect[2] + ps*d_ny_vect[ 8] - d_my_vect[ 8]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 8];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 8]*mm*sin(alph) + n2*nn*d_mm_vect[ 8]*sin(alph) + n2*nn*mm*d_alpha[ 8]*cos(alph));
	d_alphay1_vect[ 8] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 9]*n_vect[2] + ps*d_ny_vect[ 9] - d_my_vect[ 9]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 9];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 9]*mm*sin(alph) + n2*nn*d_mm_vect[ 9]*sin(alph) + n2*nn*mm*d_alpha[ 9]*cos(alph));
	d_alphay1_vect[ 9] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[10]*n_vect[2] + ps*d_ny_vect[10] - d_my_vect[10]*n2 - m_vect[2]*2.0*nn*d_nn_vect[10];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[10]*mm*sin(alph) + n2*nn*d_mm_vect[10]*sin(alph) + n2*nn*mm*d_alpha[10]*cos(alph));
	d_alphay1_vect[10] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[11]*n_vect[2] + ps*d_ny_vect[11] - d_my_vect[11]*n2 - m_vect[2]*2.0*nn*d_nn_vect[11];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[11]*mm*sin(alph) + n2*nn*d_mm_vect[11]*sin(alph) + n2*nn*mm*d_alpha[11]*cos(alph));
	d_alphay1_vect[11] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[12]*n_vect[2] + ps*d_ny_vect[12] - d_my_vect[12]*n2 - m_vect[2]*2.0*nn*d_nn_vect[12];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[12]*mm*sin(alph) + n2*nn*d_mm_vect[12]*sin(alph) + n2*nn*mm*d_alpha[12]*cos(alph));
	d_alphay1_vect[12] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	}
	

void diff_alphaz1_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mz_vect[13], double d_ps_vect[13], double *d_alphaz1_vect)
	{
	/*raideur de alpha_z1*/
	
	double UU,UP,VV,VP,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU = ps*n_vect[3] - m_vect[3]*n2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV = n2*nn*mm*d_vect[1]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV = n2*nn*mm*d_vect[1]*sin(0.00001);
			}
		else
			{
			VV = n2*nn*mm*d_vect[1]*sin(0.00001-PI);
			}
		}

	UP = d_ps_vect[ 1]*n_vect[3] + ps*d_nz_vect[ 1] - d_mz_vect[ 1]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 1];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 1]*mm*sin(alph) + n2*nn*d_mm_vect[ 1]*sin(alph) + n2*nn*mm*d_alpha[ 1]*cos(alph));
	d_alphaz1_vect[ 1] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 2]*n_vect[3] + ps*d_nz_vect[ 2] - d_mz_vect[ 2]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 2];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 2]*mm*sin(alph) + n2*nn*d_mm_vect[ 2]*sin(alph) + n2*nn*mm*d_alpha[ 2]*cos(alph));
	d_alphaz1_vect[ 2] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 3]*n_vect[3] + ps*d_nz_vect[ 3] - d_mz_vect[ 3]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 3];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 3]*mm*sin(alph) + n2*nn*d_mm_vect[ 3]*sin(alph) + n2*nn*mm*d_alpha[ 3]*cos(alph));
	d_alphaz1_vect[ 3] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 4]*n_vect[3] + ps*d_nz_vect[ 4] - d_mz_vect[ 4]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 4];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 4]*mm*sin(alph) + n2*nn*d_mm_vect[ 4]*sin(alph) + n2*nn*mm*d_alpha[ 4]*cos(alph));
	d_alphaz1_vect[ 4] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 5]*n_vect[3] + ps*d_nz_vect[ 5] - d_mz_vect[ 5]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 5];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 5]*mm*sin(alph) + n2*nn*d_mm_vect[ 5]*sin(alph) + n2*nn*mm*d_alpha[ 5]*cos(alph));
	d_alphaz1_vect[ 5] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 6]*n_vect[3] + ps*d_nz_vect[ 6] - d_mz_vect[ 6]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 6];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 6]*mm*sin(alph) + n2*nn*d_mm_vect[ 6]*sin(alph) + n2*nn*mm*d_alpha[ 6]*cos(alph));
	d_alphaz1_vect[ 6] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 7]*n_vect[3] + ps*d_nz_vect[ 7] - d_mz_vect[ 7]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 7];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 7]*mm*sin(alph) + n2*nn*d_mm_vect[ 7]*sin(alph) + n2*nn*mm*d_alpha[ 7]*cos(alph));
	d_alphaz1_vect[ 7] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 8]*n_vect[3] + ps*d_nz_vect[ 8] - d_mz_vect[ 8]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 8];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 8]*mm*sin(alph) + n2*nn*d_mm_vect[ 8]*sin(alph) + n2*nn*mm*d_alpha[ 8]*cos(alph));
	d_alphaz1_vect[ 8] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 9]*n_vect[3] + ps*d_nz_vect[ 9] - d_mz_vect[ 9]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 9];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[ 9]*mm*sin(alph) + n2*nn*d_mm_vect[ 9]*sin(alph) + n2*nn*mm*d_alpha[ 9]*cos(alph));
	d_alphaz1_vect[ 9] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[10]*n_vect[3] + ps*d_nz_vect[10] - d_mz_vect[10]*n2 - m_vect[3]*2.0*nn*d_nn_vect[10];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[10]*mm*sin(alph) + n2*nn*d_mm_vect[10]*sin(alph) + n2*nn*mm*d_alpha[10]*cos(alph));
	d_alphaz1_vect[10] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[11]*n_vect[3] + ps*d_nz_vect[11] - d_mz_vect[11]*n2 - m_vect[3]*2.0*nn*d_nn_vect[11];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[11]*mm*sin(alph) + n2*nn*d_mm_vect[11]*sin(alph) + n2*nn*mm*d_alpha[11]*cos(alph));
	d_alphaz1_vect[11] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[12]*n_vect[3] + ps*d_nz_vect[12] - d_mz_vect[12]*n2 - m_vect[3]*2.0*nn*d_nn_vect[12];
	VP = d_vect[1]*(3.0*n2*d_nn_vect[12]*mm*sin(alph) + n2*nn*d_mm_vect[12]*sin(alph) + n2*nn*mm*d_alpha[12]*cos(alph));
	d_alphaz1_vect[12] = (v_vect[4]-v_vect[3])*(UP*VV - UU*VP)/VV/VV;
	}
	
void diff_alphax2_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nx_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_ps_vect[13], double *d_alphax2_vect)
	{
	/*raideur de alpha_x1*/
	
	double UU,UP,VV,VP,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU = ps*m_vect[1] - n_vect[1]*m2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV = m2*mm*nn*d_vect[2]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV = m2*mm*nn*d_vect[2]*sin(0.00001);
			}
		else
			{
			VV = m2*mm*nn*d_vect[2]*sin(0.00001-PI);
			}
		}

	UP = d_ps_vect[ 1]*m_vect[1] + ps*d_mx_vect[ 1] - d_nx_vect[ 1]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 1];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 1]*nn*sin(alph) + m2*mm*d_nn_vect[ 1]*sin(alph) + m2*mm*nn*d_alpha[ 1]*cos(alph));
	d_alphax2_vect[ 1] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 2]*m_vect[1] + ps*d_mx_vect[ 2] - d_nx_vect[ 2]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 2];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 2]*nn*sin(alph) + m2*mm*d_nn_vect[ 2]*sin(alph) + m2*mm*nn*d_alpha[ 2]*cos(alph));
	d_alphax2_vect[ 2] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 3]*m_vect[1] + ps*d_mx_vect[ 3] - d_nx_vect[ 3]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 3];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 3]*nn*sin(alph) + m2*mm*d_nn_vect[ 3]*sin(alph) + m2*mm*nn*d_alpha[ 3]*cos(alph));
	d_alphax2_vect[ 3] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 4]*m_vect[1] + ps*d_mx_vect[ 4] - d_nx_vect[ 4]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 4];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 4]*nn*sin(alph) + m2*mm*d_nn_vect[ 4]*sin(alph) + m2*mm*nn*d_alpha[ 4]*cos(alph));
	d_alphax2_vect[ 4] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 5]*m_vect[1] + ps*d_mx_vect[ 5] - d_nx_vect[ 5]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 5];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 5]*nn*sin(alph) + m2*mm*d_nn_vect[ 5]*sin(alph) + m2*mm*nn*d_alpha[ 5]*cos(alph));
	d_alphax2_vect[ 5] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 6]*m_vect[1] + ps*d_mx_vect[ 6] - d_nx_vect[ 6]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 6];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 6]*nn*sin(alph) + m2*mm*d_nn_vect[ 6]*sin(alph) + m2*mm*nn*d_alpha[ 6]*cos(alph));
	d_alphax2_vect[ 6] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 7]*m_vect[1] + ps*d_mx_vect[ 7] - d_nx_vect[ 7]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 7];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 7]*nn*sin(alph) + m2*mm*d_nn_vect[ 7]*sin(alph) + m2*mm*nn*d_alpha[ 7]*cos(alph));
	d_alphax2_vect[ 7] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 8]*m_vect[1] + ps*d_mx_vect[ 8] - d_nx_vect[ 8]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 8];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 8]*nn*sin(alph) + m2*mm*d_nn_vect[ 8]*sin(alph) + m2*mm*nn*d_alpha[ 8]*cos(alph));
	d_alphax2_vect[ 8] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 9]*m_vect[1] + ps*d_mx_vect[ 9] - d_nx_vect[ 9]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 9];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 9]*nn*sin(alph) + m2*mm*d_nn_vect[ 9]*sin(alph) + m2*mm*nn*d_alpha[ 9]*cos(alph));
	d_alphax2_vect[ 9] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[10]*m_vect[1] + ps*d_mx_vect[10] - d_nx_vect[10]*m2 - n_vect[1]*2.0*mm*d_mm_vect[10];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[10]*nn*sin(alph) + m2*mm*d_nn_vect[10]*sin(alph) + m2*mm*nn*d_alpha[10]*cos(alph));
	d_alphax2_vect[10] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[11]*m_vect[1] + ps*d_mx_vect[11] - d_nx_vect[11]*m2 - n_vect[1]*2.0*mm*d_mm_vect[11];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[11]*nn*sin(alph) + m2*mm*d_nn_vect[11]*sin(alph) + m2*mm*nn*d_alpha[11]*cos(alph));
	d_alphax2_vect[11] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[12]*m_vect[1] + ps*d_mx_vect[12] - d_nx_vect[12]*m2 - n_vect[1]*2.0*mm*d_mm_vect[12];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[12]*nn*sin(alph) + m2*mm*d_nn_vect[12]*sin(alph) + m2*mm*nn*d_alpha[12]*cos(alph));
	d_alphax2_vect[12] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	}


void diff_alphay2_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_ny_vect[13], double d_mm_vect[13], double d_my_vect[13], double d_ps_vect[13], double *d_alphay2_vect)
	{
	/*raideur de alpha_x1*/
	
	double UU,UP,VV,VP,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU = ps*m_vect[2] - n_vect[2]*m2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV = m2*mm*nn*d_vect[2]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV = m2*mm*nn*d_vect[2]*sin(0.00001);
			}
		else
			{
			VV = m2*mm*nn*d_vect[2]*sin(0.00001-PI);
			}
		}

	UP = d_ps_vect[ 1]*m_vect[2] + ps*d_my_vect[ 1] - d_ny_vect[ 1]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 1];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 1]*nn*sin(alph) + m2*mm*d_nn_vect[ 1]*sin(alph) + m2*mm*nn*d_alpha[ 1]*cos(alph));
	d_alphay2_vect[ 1] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 2]*m_vect[2] + ps*d_my_vect[ 2] - d_ny_vect[ 2]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 2];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 2]*nn*sin(alph) + m2*mm*d_nn_vect[ 2]*sin(alph) + m2*mm*nn*d_alpha[ 2]*cos(alph));
	d_alphay2_vect[ 2] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 3]*m_vect[2] + ps*d_my_vect[ 3] - d_ny_vect[ 3]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 3];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 3]*nn*sin(alph) + m2*mm*d_nn_vect[ 3]*sin(alph) + m2*mm*nn*d_alpha[ 3]*cos(alph));
	d_alphay2_vect[ 3] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 4]*m_vect[2] + ps*d_my_vect[ 4] - d_ny_vect[ 4]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 4];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 4]*nn*sin(alph) + m2*mm*d_nn_vect[ 4]*sin(alph) + m2*mm*nn*d_alpha[ 4]*cos(alph));
	d_alphay2_vect[ 4] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 5]*m_vect[2] + ps*d_my_vect[ 5] - d_ny_vect[ 5]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 5];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 5]*nn*sin(alph) + m2*mm*d_nn_vect[ 5]*sin(alph) + m2*mm*nn*d_alpha[ 5]*cos(alph));
	d_alphay2_vect[ 5] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 6]*m_vect[2] + ps*d_my_vect[ 6] - d_ny_vect[ 6]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 6];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 6]*nn*sin(alph) + m2*mm*d_nn_vect[ 6]*sin(alph) + m2*mm*nn*d_alpha[ 6]*cos(alph));
	d_alphay2_vect[ 6] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 7]*m_vect[2] + ps*d_my_vect[ 7] - d_ny_vect[ 7]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 7];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 7]*nn*sin(alph) + m2*mm*d_nn_vect[ 7]*sin(alph) + m2*mm*nn*d_alpha[ 7]*cos(alph));
	d_alphay2_vect[ 7] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 8]*m_vect[2] + ps*d_my_vect[ 8] - d_ny_vect[ 8]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 8];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 8]*nn*sin(alph) + m2*mm*d_nn_vect[ 8]*sin(alph) + m2*mm*nn*d_alpha[ 8]*cos(alph));
	d_alphay2_vect[ 8] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 9]*m_vect[2] + ps*d_my_vect[ 9] - d_ny_vect[ 9]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 9];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 9]*nn*sin(alph) + m2*mm*d_nn_vect[ 9]*sin(alph) + m2*mm*nn*d_alpha[ 9]*cos(alph));
	d_alphay2_vect[ 9] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[10]*m_vect[2] + ps*d_my_vect[10] - d_ny_vect[10]*m2 - n_vect[2]*2.0*mm*d_mm_vect[10];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[10]*nn*sin(alph) + m2*mm*d_nn_vect[10]*sin(alph) + m2*mm*nn*d_alpha[10]*cos(alph));
	d_alphay2_vect[10] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[11]*m_vect[2] + ps*d_my_vect[11] - d_ny_vect[11]*m2 - n_vect[2]*2.0*mm*d_mm_vect[11];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[11]*nn*sin(alph) + m2*mm*d_nn_vect[11]*sin(alph) + m2*mm*nn*d_alpha[11]*cos(alph));
	d_alphay2_vect[11] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[12]*m_vect[2] + ps*d_my_vect[12] - d_ny_vect[12]*m2 - n_vect[2]*2.0*mm*d_mm_vect[12];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[12]*nn*sin(alph) + m2*mm*d_nn_vect[12]*sin(alph) + m2*mm*nn*d_alpha[12]*cos(alph));
	d_alphay2_vect[12] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	}

void diff_alphaz2_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mz_vect[13], double d_ps_vect[13], double *d_alphaz2_vect)
	{
	/*raideur de alpha_x1*/
	
	double UU,UP,VV,VP,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU = ps*m_vect[3] - n_vect[3]*m2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV = m2*mm*nn*d_vect[2]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV = m2*mm*nn*d_vect[2]*sin(0.00001);
			}
		else
			{
			VV = m2*mm*nn*d_vect[2]*sin(0.00001-PI);
			}
		}

	UP = d_ps_vect[ 1]*m_vect[3] + ps*d_mz_vect[ 1] - d_nz_vect[ 1]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 1];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 1]*nn*sin(alph) + m2*mm*d_nn_vect[ 1]*sin(alph) + m2*mm*nn*d_alpha[ 1]*cos(alph));
	d_alphaz2_vect[ 1] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 2]*m_vect[3] + ps*d_mz_vect[ 2] - d_nz_vect[ 2]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 2];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 2]*nn*sin(alph) + m2*mm*d_nn_vect[ 2]*sin(alph) + m2*mm*nn*d_alpha[ 2]*cos(alph));
	d_alphaz2_vect[ 2] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 3]*m_vect[3] + ps*d_mz_vect[ 3] - d_nz_vect[ 3]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 3];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 3]*nn*sin(alph) + m2*mm*d_nn_vect[ 3]*sin(alph) + m2*mm*nn*d_alpha[ 3]*cos(alph));
	d_alphaz2_vect[ 3] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 4]*m_vect[3] + ps*d_mz_vect[ 4] - d_nz_vect[ 4]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 4];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 4]*nn*sin(alph) + m2*mm*d_nn_vect[ 4]*sin(alph) + m2*mm*nn*d_alpha[ 4]*cos(alph));
	d_alphaz2_vect[ 4] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 5]*m_vect[3] + ps*d_mz_vect[ 5] - d_nz_vect[ 5]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 5];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 5]*nn*sin(alph) + m2*mm*d_nn_vect[ 5]*sin(alph) + m2*mm*nn*d_alpha[ 5]*cos(alph));
	d_alphaz2_vect[ 5] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 6]*m_vect[3] + ps*d_mz_vect[ 6] - d_nz_vect[ 6]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 6];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 6]*nn*sin(alph) + m2*mm*d_nn_vect[ 6]*sin(alph) + m2*mm*nn*d_alpha[ 6]*cos(alph));
	d_alphaz2_vect[ 6] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 7]*m_vect[3] + ps*d_mz_vect[ 7] - d_nz_vect[ 7]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 7];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 7]*nn*sin(alph) + m2*mm*d_nn_vect[ 7]*sin(alph) + m2*mm*nn*d_alpha[ 7]*cos(alph));
	d_alphaz2_vect[ 7] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 8]*m_vect[3] + ps*d_mz_vect[ 8] - d_nz_vect[ 8]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 8];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 8]*nn*sin(alph) + m2*mm*d_nn_vect[ 8]*sin(alph) + m2*mm*nn*d_alpha[ 8]*cos(alph));
	d_alphaz2_vect[ 8] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[ 9]*m_vect[3] + ps*d_mz_vect[ 9] - d_nz_vect[ 9]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 9];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[ 9]*nn*sin(alph) + m2*mm*d_nn_vect[ 9]*sin(alph) + m2*mm*nn*d_alpha[ 9]*cos(alph));
	d_alphaz2_vect[ 9] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[10]*m_vect[3] + ps*d_mz_vect[10] - d_nz_vect[10]*m2 - n_vect[3]*2.0*mm*d_mm_vect[10];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[10]*nn*sin(alph) + m2*mm*d_nn_vect[10]*sin(alph) + m2*mm*nn*d_alpha[10]*cos(alph));
	d_alphaz2_vect[10] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[11]*m_vect[3] + ps*d_mz_vect[11] - d_nz_vect[11]*m2 - n_vect[3]*2.0*mm*d_mm_vect[11];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[11]*nn*sin(alph) + m2*mm*d_nn_vect[11]*sin(alph) + m2*mm*nn*d_alpha[11]*cos(alph));
	d_alphaz2_vect[11] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	
	UP = d_ps_vect[12]*m_vect[3] + ps*d_mz_vect[12] - d_nz_vect[12]*m2 - n_vect[3]*2.0*mm*d_mm_vect[12];
	VP = d_vect[2]*(3.0*m2*d_mm_vect[12]*nn*sin(alph) + m2*mm*d_nn_vect[12]*sin(alph) + m2*mm*nn*d_alpha[12]*cos(alph));
	d_alphaz2_vect[12] = (v_vect[3]-v_vect[4])*(UP*VV - UU*VP)/VV/VV;
	}


void diff_alphax3_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nx_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_ps_vect[13], double *d_alphax3_vect)
	{
	/*raideur de alpha_x1*/
	
	double UU1,UP1,VV1,VP1,UU2,UP2,VV2,VP2,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU1 = ps*n_vect[1] - m_vect[1]*n2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV1 = n2*nn*mm*d_vect[1]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001);
			}
		else
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001-PI);
			}
		}
	UU2 = ps*m_vect[1] - n_vect[1]*m2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV2 = m2*mm*nn*d_vect[2]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001);
			}
		else
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001-PI);
			}
		}
	
	UP1 = d_ps_vect[ 1]*n_vect[1] + ps*d_nx_vect[ 1] - d_mx_vect[ 1]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 1];
	UP2 = d_ps_vect[ 1]*m_vect[1] + ps*d_mx_vect[ 1] - d_nx_vect[ 1]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 1];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 1]*mm*sin(alph) + n2*nn*d_mm_vect[ 1]*sin(alph) + n2*nn*mm*d_alpha[ 1]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 1]*nn*sin(alph) + m2*mm*d_nn_vect[ 1]*sin(alph) + m2*mm*nn*d_alpha[ 1]*cos(alph));
	d_alphax3_vect[ 1] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 2]*n_vect[1] + ps*d_nx_vect[ 2] - d_mx_vect[ 2]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 2];
	UP2 = d_ps_vect[ 2]*m_vect[1] + ps*d_mx_vect[ 2] - d_nx_vect[ 2]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 2];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 2]*mm*sin(alph) + n2*nn*d_mm_vect[ 2]*sin(alph) + n2*nn*mm*d_alpha[ 2]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 2]*nn*sin(alph) + m2*mm*d_nn_vect[ 2]*sin(alph) + m2*mm*nn*d_alpha[ 2]*cos(alph));
	d_alphax3_vect[ 2] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 3]*n_vect[1] + ps*d_nx_vect[ 3] - d_mx_vect[ 3]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 3];
	UP2 = d_ps_vect[ 3]*m_vect[1] + ps*d_mx_vect[ 3] - d_nx_vect[ 3]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 3];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 3]*mm*sin(alph) + n2*nn*d_mm_vect[ 3]*sin(alph) + n2*nn*mm*d_alpha[ 3]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 3]*nn*sin(alph) + m2*mm*d_nn_vect[ 3]*sin(alph) + m2*mm*nn*d_alpha[ 3]*cos(alph));
	d_alphax3_vect[ 3] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 4]*n_vect[1] + ps*d_nx_vect[ 4] - d_mx_vect[ 4]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 4];
	UP2 = d_ps_vect[ 4]*m_vect[1] + ps*d_mx_vect[ 4] - d_nx_vect[ 4]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 4];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 4]*mm*sin(alph) + n2*nn*d_mm_vect[ 4]*sin(alph) + n2*nn*mm*d_alpha[ 4]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 4]*nn*sin(alph) + m2*mm*d_nn_vect[ 4]*sin(alph) + m2*mm*nn*d_alpha[ 4]*cos(alph));
	d_alphax3_vect[ 4] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 5]*n_vect[1] + ps*d_nx_vect[ 5] - d_mx_vect[ 5]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 5];
	UP2 = d_ps_vect[ 5]*m_vect[1] + ps*d_mx_vect[ 5] - d_nx_vect[ 5]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 5];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 5]*mm*sin(alph) + n2*nn*d_mm_vect[ 5]*sin(alph) + n2*nn*mm*d_alpha[ 5]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 5]*nn*sin(alph) + m2*mm*d_nn_vect[ 5]*sin(alph) + m2*mm*nn*d_alpha[ 5]*cos(alph));
	d_alphax3_vect[ 5] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 6]*n_vect[1] + ps*d_nx_vect[ 6] - d_mx_vect[ 6]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 6];
	UP2 = d_ps_vect[ 6]*m_vect[1] + ps*d_mx_vect[ 6] - d_nx_vect[ 6]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 6];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 6]*mm*sin(alph) + n2*nn*d_mm_vect[ 6]*sin(alph) + n2*nn*mm*d_alpha[ 6]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 6]*nn*sin(alph) + m2*mm*d_nn_vect[ 6]*sin(alph) + m2*mm*nn*d_alpha[ 6]*cos(alph));
	d_alphax3_vect[ 6] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 7]*n_vect[1] + ps*d_nx_vect[ 7] - d_mx_vect[ 7]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 7];
	UP2 = d_ps_vect[ 7]*m_vect[1] + ps*d_mx_vect[ 7] - d_nx_vect[ 7]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 7];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 7]*mm*sin(alph) + n2*nn*d_mm_vect[ 7]*sin(alph) + n2*nn*mm*d_alpha[ 7]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 7]*nn*sin(alph) + m2*mm*d_nn_vect[ 7]*sin(alph) + m2*mm*nn*d_alpha[ 7]*cos(alph));
	d_alphax3_vect[ 7] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 8]*n_vect[1] + ps*d_nx_vect[ 8] - d_mx_vect[ 8]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 8];
	UP2 = d_ps_vect[ 8]*m_vect[1] + ps*d_mx_vect[ 8] - d_nx_vect[ 8]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 8];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 8]*mm*sin(alph) + n2*nn*d_mm_vect[ 8]*sin(alph) + n2*nn*mm*d_alpha[ 8]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 8]*nn*sin(alph) + m2*mm*d_nn_vect[ 8]*sin(alph) + m2*mm*nn*d_alpha[ 8]*cos(alph));
	d_alphax3_vect[ 8] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 9]*n_vect[1] + ps*d_nx_vect[ 9] - d_mx_vect[ 9]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 9];
	UP2 = d_ps_vect[ 9]*m_vect[1] + ps*d_mx_vect[ 9] - d_nx_vect[ 9]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 9];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 9]*mm*sin(alph) + n2*nn*d_mm_vect[ 9]*sin(alph) + n2*nn*mm*d_alpha[ 9]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 9]*nn*sin(alph) + m2*mm*d_nn_vect[ 9]*sin(alph) + m2*mm*nn*d_alpha[ 9]*cos(alph));
	d_alphax3_vect[ 9] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[10]*n_vect[1] + ps*d_nx_vect[10] - d_mx_vect[10]*n2 - m_vect[1]*2.0*nn*d_nn_vect[10];
	UP2 = d_ps_vect[10]*m_vect[1] + ps*d_mx_vect[10] - d_nx_vect[10]*m2 - n_vect[1]*2.0*mm*d_mm_vect[10];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[10]*mm*sin(alph) + n2*nn*d_mm_vect[10]*sin(alph) + n2*nn*mm*d_alpha[10]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[10]*nn*sin(alph) + m2*mm*d_nn_vect[10]*sin(alph) + m2*mm*nn*d_alpha[10]*cos(alph));
	d_alphax3_vect[10] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[11]*n_vect[1] + ps*d_nx_vect[11] - d_mx_vect[11]*n2 - m_vect[1]*2.0*nn*d_nn_vect[11];
	UP2 = d_ps_vect[11]*m_vect[1] + ps*d_mx_vect[11] - d_nx_vect[11]*m2 - n_vect[1]*2.0*mm*d_mm_vect[11];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[11]*mm*sin(alph) + n2*nn*d_mm_vect[11]*sin(alph) + n2*nn*mm*d_alpha[11]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[11]*nn*sin(alph) + m2*mm*d_nn_vect[11]*sin(alph) + m2*mm*nn*d_alpha[11]*cos(alph));
	d_alphax3_vect[11] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[12]*n_vect[1] + ps*d_nx_vect[12] - d_mx_vect[12]*n2 - m_vect[1]*2.0*nn*d_nn_vect[12];
	UP2 = d_ps_vect[12]*m_vect[1] + ps*d_mx_vect[12] - d_nx_vect[12]*m2 - n_vect[1]*2.0*mm*d_mm_vect[12];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[12]*mm*sin(alph) + n2*nn*d_mm_vect[12]*sin(alph) + n2*nn*mm*d_alpha[12]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[12]*nn*sin(alph) + m2*mm*d_nn_vect[12]*sin(alph) + m2*mm*nn*d_alpha[12]*cos(alph));
	d_alphax3_vect[12] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	}


void diff_alphay3_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_ny_vect[13], double d_mm_vect[13], double d_my_vect[13], double d_ps_vect[13], double *d_alphay3_vect)
	{
	/*raideur de alpha_x1*/
	
	double UU1,UP1,VV1,VP1,UU2,UP2,VV2,VP2,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU1 = ps*n_vect[2] - m_vect[2]*n2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV1 = n2*nn*mm*d_vect[1]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001);
			}
		else
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001-PI);
			}
		}
	UU2 = ps*m_vect[2] - n_vect[2]*m2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV2 = m2*mm*nn*d_vect[2]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001);
			}
		else
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001-PI);
			}
		}
	
	UP1 = d_ps_vect[ 1]*n_vect[2] + ps*d_ny_vect[ 1] - d_my_vect[ 1]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 1];
	UP2 = d_ps_vect[ 1]*m_vect[2] + ps*d_my_vect[ 1] - d_ny_vect[ 1]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 1];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 1]*mm*sin(alph) + n2*nn*d_mm_vect[ 1]*sin(alph) + n2*nn*mm*d_alpha[ 1]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 1]*nn*sin(alph) + m2*mm*d_nn_vect[ 1]*sin(alph) + m2*mm*nn*d_alpha[ 1]*cos(alph));
	d_alphay3_vect[ 1] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 2]*n_vect[2] + ps*d_ny_vect[ 2] - d_my_vect[ 2]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 2];
	UP2 = d_ps_vect[ 2]*m_vect[2] + ps*d_my_vect[ 2] - d_ny_vect[ 2]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 2];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 2]*mm*sin(alph) + n2*nn*d_mm_vect[ 2]*sin(alph) + n2*nn*mm*d_alpha[ 2]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 2]*nn*sin(alph) + m2*mm*d_nn_vect[ 2]*sin(alph) + m2*mm*nn*d_alpha[ 2]*cos(alph));
	d_alphay3_vect[ 2] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 3]*n_vect[2] + ps*d_ny_vect[ 3] - d_my_vect[ 3]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 3];
	UP2 = d_ps_vect[ 3]*m_vect[2] + ps*d_my_vect[ 3] - d_ny_vect[ 3]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 3];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 3]*mm*sin(alph) + n2*nn*d_mm_vect[ 3]*sin(alph) + n2*nn*mm*d_alpha[ 3]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 3]*nn*sin(alph) + m2*mm*d_nn_vect[ 3]*sin(alph) + m2*mm*nn*d_alpha[ 3]*cos(alph));
	d_alphay3_vect[ 3] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 4]*n_vect[2] + ps*d_ny_vect[ 4] - d_my_vect[ 4]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 4];
	UP2 = d_ps_vect[ 4]*m_vect[2] + ps*d_my_vect[ 4] - d_ny_vect[ 4]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 4];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 4]*mm*sin(alph) + n2*nn*d_mm_vect[ 4]*sin(alph) + n2*nn*mm*d_alpha[ 4]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 4]*nn*sin(alph) + m2*mm*d_nn_vect[ 4]*sin(alph) + m2*mm*nn*d_alpha[ 4]*cos(alph));
	d_alphay3_vect[ 4] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 5]*n_vect[2] + ps*d_ny_vect[ 5] - d_my_vect[ 5]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 5];
	UP2 = d_ps_vect[ 5]*m_vect[2] + ps*d_my_vect[ 5] - d_ny_vect[ 5]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 5];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 5]*mm*sin(alph) + n2*nn*d_mm_vect[ 5]*sin(alph) + n2*nn*mm*d_alpha[ 5]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 5]*nn*sin(alph) + m2*mm*d_nn_vect[ 5]*sin(alph) + m2*mm*nn*d_alpha[ 5]*cos(alph));
	d_alphay3_vect[ 5] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 6]*n_vect[2] + ps*d_ny_vect[ 6] - d_my_vect[ 6]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 6];
	UP2 = d_ps_vect[ 6]*m_vect[2] + ps*d_my_vect[ 6] - d_ny_vect[ 6]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 6];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 6]*mm*sin(alph) + n2*nn*d_mm_vect[ 6]*sin(alph) + n2*nn*mm*d_alpha[ 6]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 6]*nn*sin(alph) + m2*mm*d_nn_vect[ 6]*sin(alph) + m2*mm*nn*d_alpha[ 6]*cos(alph));
	d_alphay3_vect[ 6] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 7]*n_vect[2] + ps*d_ny_vect[ 7] - d_my_vect[ 7]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 7];
	UP2 = d_ps_vect[ 7]*m_vect[2] + ps*d_my_vect[ 7] - d_ny_vect[ 7]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 7];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 7]*mm*sin(alph) + n2*nn*d_mm_vect[ 7]*sin(alph) + n2*nn*mm*d_alpha[ 7]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 7]*nn*sin(alph) + m2*mm*d_nn_vect[ 7]*sin(alph) + m2*mm*nn*d_alpha[ 7]*cos(alph));
	d_alphay3_vect[ 7] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 8]*n_vect[2] + ps*d_ny_vect[ 8] - d_my_vect[ 8]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 8];
	UP2 = d_ps_vect[ 8]*m_vect[2] + ps*d_my_vect[ 8] - d_ny_vect[ 8]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 8];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 8]*mm*sin(alph) + n2*nn*d_mm_vect[ 8]*sin(alph) + n2*nn*mm*d_alpha[ 8]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 8]*nn*sin(alph) + m2*mm*d_nn_vect[ 8]*sin(alph) + m2*mm*nn*d_alpha[ 8]*cos(alph));
	d_alphay3_vect[ 8] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 9]*n_vect[2] + ps*d_ny_vect[ 9] - d_my_vect[ 9]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 9];
	UP2 = d_ps_vect[ 9]*m_vect[2] + ps*d_my_vect[ 9] - d_ny_vect[ 9]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 9];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 9]*mm*sin(alph) + n2*nn*d_mm_vect[ 9]*sin(alph) + n2*nn*mm*d_alpha[ 9]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 9]*nn*sin(alph) + m2*mm*d_nn_vect[ 9]*sin(alph) + m2*mm*nn*d_alpha[ 9]*cos(alph));
	d_alphay3_vect[ 9] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[10]*n_vect[2] + ps*d_ny_vect[10] - d_my_vect[10]*n2 - m_vect[2]*2.0*nn*d_nn_vect[10];
	UP2 = d_ps_vect[10]*m_vect[2] + ps*d_my_vect[10] - d_ny_vect[10]*m2 - n_vect[2]*2.0*mm*d_mm_vect[10];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[10]*mm*sin(alph) + n2*nn*d_mm_vect[10]*sin(alph) + n2*nn*mm*d_alpha[10]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[10]*nn*sin(alph) + m2*mm*d_nn_vect[10]*sin(alph) + m2*mm*nn*d_alpha[10]*cos(alph));
	d_alphay3_vect[10] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[11]*n_vect[2] + ps*d_ny_vect[11] - d_my_vect[11]*n2 - m_vect[2]*2.0*nn*d_nn_vect[11];
	UP2 = d_ps_vect[11]*m_vect[2] + ps*d_my_vect[11] - d_ny_vect[11]*m2 - n_vect[2]*2.0*mm*d_mm_vect[11];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[11]*mm*sin(alph) + n2*nn*d_mm_vect[11]*sin(alph) + n2*nn*mm*d_alpha[11]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[11]*nn*sin(alph) + m2*mm*d_nn_vect[11]*sin(alph) + m2*mm*nn*d_alpha[11]*cos(alph));
	d_alphay3_vect[11] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[12]*n_vect[2] + ps*d_ny_vect[12] - d_my_vect[12]*n2 - m_vect[2]*2.0*nn*d_nn_vect[12];
	UP2 = d_ps_vect[12]*m_vect[2] + ps*d_my_vect[12] - d_ny_vect[12]*m2 - n_vect[2]*2.0*mm*d_mm_vect[12];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[12]*mm*sin(alph) + n2*nn*d_mm_vect[12]*sin(alph) + n2*nn*mm*d_alpha[12]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[12]*nn*sin(alph) + m2*mm*d_nn_vect[12]*sin(alph) + m2*mm*nn*d_alpha[12]*cos(alph));
	d_alphay3_vect[12] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	}


void diff_alphaz3_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mz_vect[13], double d_ps_vect[13], double *d_alphaz3_vect)
	{
	/*raideur de alpha_x1*/
	
	double UU1,UP1,VV1,VP1,UU2,UP2,VV2,VP2,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU1 = ps*n_vect[3] - m_vect[3]*n2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV1 = n2*nn*mm*d_vect[1]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001);
			}
		else
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001-PI);
			}
		}
	UU2 = ps*m_vect[3] - n_vect[3]*m2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV2 = m2*mm*nn*d_vect[2]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001);
			}
		else
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001-PI);
			}
		}
	
	UP1 = d_ps_vect[ 1]*n_vect[3] + ps*d_nz_vect[ 1] - d_mz_vect[ 1]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 1];
	UP2 = d_ps_vect[ 1]*m_vect[3] + ps*d_mz_vect[ 1] - d_nz_vect[ 1]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 1];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 1]*mm*sin(alph) + n2*nn*d_mm_vect[ 1]*sin(alph) + n2*nn*mm*d_alpha[ 1]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 1]*nn*sin(alph) + m2*mm*d_nn_vect[ 1]*sin(alph) + m2*mm*nn*d_alpha[ 1]*cos(alph));
	d_alphaz3_vect[ 1] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 2]*n_vect[3] + ps*d_nz_vect[ 2] - d_mz_vect[ 2]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 2];
	UP2 = d_ps_vect[ 2]*m_vect[3] + ps*d_mz_vect[ 2] - d_nz_vect[ 2]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 2];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 2]*mm*sin(alph) + n2*nn*d_mm_vect[ 2]*sin(alph) + n2*nn*mm*d_alpha[ 2]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 2]*nn*sin(alph) + m2*mm*d_nn_vect[ 2]*sin(alph) + m2*mm*nn*d_alpha[ 2]*cos(alph));
	d_alphaz3_vect[ 2] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 3]*n_vect[3] + ps*d_nz_vect[ 3] - d_mz_vect[ 3]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 3];
	UP2 = d_ps_vect[ 3]*m_vect[3] + ps*d_mz_vect[ 3] - d_nz_vect[ 3]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 3];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 3]*mm*sin(alph) + n2*nn*d_mm_vect[ 3]*sin(alph) + n2*nn*mm*d_alpha[ 3]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 3]*nn*sin(alph) + m2*mm*d_nn_vect[ 3]*sin(alph) + m2*mm*nn*d_alpha[ 3]*cos(alph));
	d_alphaz3_vect[ 3] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 4]*n_vect[3] + ps*d_nz_vect[ 4] - d_mz_vect[ 4]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 4];
	UP2 = d_ps_vect[ 4]*m_vect[3] + ps*d_mz_vect[ 4] - d_nz_vect[ 4]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 4];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 4]*mm*sin(alph) + n2*nn*d_mm_vect[ 4]*sin(alph) + n2*nn*mm*d_alpha[ 4]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 4]*nn*sin(alph) + m2*mm*d_nn_vect[ 4]*sin(alph) + m2*mm*nn*d_alpha[ 4]*cos(alph));
	d_alphaz3_vect[ 4] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 5]*n_vect[3] + ps*d_nz_vect[ 5] - d_mz_vect[ 5]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 5];
	UP2 = d_ps_vect[ 5]*m_vect[3] + ps*d_mz_vect[ 5] - d_nz_vect[ 5]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 5];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 5]*mm*sin(alph) + n2*nn*d_mm_vect[ 5]*sin(alph) + n2*nn*mm*d_alpha[ 5]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 5]*nn*sin(alph) + m2*mm*d_nn_vect[ 5]*sin(alph) + m2*mm*nn*d_alpha[ 5]*cos(alph));
	d_alphaz3_vect[ 5] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 6]*n_vect[3] + ps*d_nz_vect[ 6] - d_mz_vect[ 6]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 6];
	UP2 = d_ps_vect[ 6]*m_vect[3] + ps*d_mz_vect[ 6] - d_nz_vect[ 6]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 6];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 6]*mm*sin(alph) + n2*nn*d_mm_vect[ 6]*sin(alph) + n2*nn*mm*d_alpha[ 6]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 6]*nn*sin(alph) + m2*mm*d_nn_vect[ 6]*sin(alph) + m2*mm*nn*d_alpha[ 6]*cos(alph));
	d_alphaz3_vect[ 6] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 7]*n_vect[3] + ps*d_nz_vect[ 7] - d_mz_vect[ 7]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 7];
	UP2 = d_ps_vect[ 7]*m_vect[3] + ps*d_mz_vect[ 7] - d_nz_vect[ 7]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 7];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 7]*mm*sin(alph) + n2*nn*d_mm_vect[ 7]*sin(alph) + n2*nn*mm*d_alpha[ 7]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 7]*nn*sin(alph) + m2*mm*d_nn_vect[ 7]*sin(alph) + m2*mm*nn*d_alpha[ 7]*cos(alph));
	d_alphaz3_vect[ 7] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 8]*n_vect[3] + ps*d_nz_vect[ 8] - d_mz_vect[ 8]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 8];
	UP2 = d_ps_vect[ 8]*m_vect[3] + ps*d_mz_vect[ 8] - d_nz_vect[ 8]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 8];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 8]*mm*sin(alph) + n2*nn*d_mm_vect[ 8]*sin(alph) + n2*nn*mm*d_alpha[ 8]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 8]*nn*sin(alph) + m2*mm*d_nn_vect[ 8]*sin(alph) + m2*mm*nn*d_alpha[ 8]*cos(alph));
	d_alphaz3_vect[ 8] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 9]*n_vect[3] + ps*d_nz_vect[ 9] - d_mz_vect[ 9]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 9];
	UP2 = d_ps_vect[ 9]*m_vect[3] + ps*d_mz_vect[ 9] - d_nz_vect[ 9]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 9];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 9]*mm*sin(alph) + n2*nn*d_mm_vect[ 9]*sin(alph) + n2*nn*mm*d_alpha[ 9]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 9]*nn*sin(alph) + m2*mm*d_nn_vect[ 9]*sin(alph) + m2*mm*nn*d_alpha[ 9]*cos(alph));
	d_alphaz3_vect[ 9] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[10]*n_vect[3] + ps*d_nz_vect[10] - d_mz_vect[10]*n2 - m_vect[3]*2.0*nn*d_nn_vect[10];
	UP2 = d_ps_vect[10]*m_vect[3] + ps*d_mz_vect[10] - d_nz_vect[10]*m2 - n_vect[3]*2.0*mm*d_mm_vect[10];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[10]*mm*sin(alph) + n2*nn*d_mm_vect[10]*sin(alph) + n2*nn*mm*d_alpha[10]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[10]*nn*sin(alph) + m2*mm*d_nn_vect[10]*sin(alph) + m2*mm*nn*d_alpha[10]*cos(alph));
	d_alphaz3_vect[10] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[11]*n_vect[3] + ps*d_nz_vect[11] - d_mz_vect[11]*n2 - m_vect[3]*2.0*nn*d_nn_vect[11];
	UP2 = d_ps_vect[11]*m_vect[3] + ps*d_mz_vect[11] - d_nz_vect[11]*m2 - n_vect[3]*2.0*mm*d_mm_vect[11];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[11]*mm*sin(alph) + n2*nn*d_mm_vect[11]*sin(alph) + n2*nn*mm*d_alpha[11]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[11]*nn*sin(alph) + m2*mm*d_nn_vect[11]*sin(alph) + m2*mm*nn*d_alpha[11]*cos(alph));
	d_alphaz3_vect[11] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[12]*n_vect[3] + ps*d_nz_vect[12] - d_mz_vect[12]*n2 - m_vect[3]*2.0*nn*d_nn_vect[12];
	UP2 = d_ps_vect[12]*m_vect[3] + ps*d_mz_vect[12] - d_nz_vect[12]*m2 - n_vect[3]*2.0*mm*d_mm_vect[12];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[12]*mm*sin(alph) + n2*nn*d_mm_vect[12]*sin(alph) + n2*nn*mm*d_alpha[12]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[12]*nn*sin(alph) + m2*mm*d_nn_vect[12]*sin(alph) + m2*mm*nn*d_alpha[12]*cos(alph));
	d_alphaz3_vect[12] = (v_vect[1]-v_vect[4])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[4]-v_vect[2])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	}

void diff_alphax4_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nx_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_ps_vect[13], double *d_alphax4_vect)
	{
	/*raideur de alpha_x1*/
	
	double UU1,UP1,VV1,VP1,UU2,UP2,VV2,VP2,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU1 = ps*n_vect[1] - m_vect[1]*n2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV1 = n2*nn*mm*d_vect[1]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001);
			}
		else
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001-PI);
			}
		}
	UU2 = ps*m_vect[1] - n_vect[1]*m2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV2 = m2*mm*nn*d_vect[2]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001);
			}
		else
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001-PI);
			}
		}
	
	UP1 = d_ps_vect[ 1]*n_vect[1] + ps*d_nx_vect[ 1] - d_mx_vect[ 1]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 1];
	UP2 = d_ps_vect[ 1]*m_vect[1] + ps*d_mx_vect[ 1] - d_nx_vect[ 1]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 1];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 1]*mm*sin(alph) + n2*nn*d_mm_vect[ 1]*sin(alph) + n2*nn*mm*d_alpha[ 1]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 1]*nn*sin(alph) + m2*mm*d_nn_vect[ 1]*sin(alph) + m2*mm*nn*d_alpha[ 1]*cos(alph));
	d_alphax4_vect[ 1] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 2]*n_vect[1] + ps*d_nx_vect[ 2] - d_mx_vect[ 2]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 2];
	UP2 = d_ps_vect[ 2]*m_vect[1] + ps*d_mx_vect[ 2] - d_nx_vect[ 2]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 2];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 2]*mm*sin(alph) + n2*nn*d_mm_vect[ 2]*sin(alph) + n2*nn*mm*d_alpha[ 2]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 2]*nn*sin(alph) + m2*mm*d_nn_vect[ 2]*sin(alph) + m2*mm*nn*d_alpha[ 2]*cos(alph));
	d_alphax4_vect[ 2] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 3]*n_vect[1] + ps*d_nx_vect[ 3] - d_mx_vect[ 3]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 3];
	UP2 = d_ps_vect[ 3]*m_vect[1] + ps*d_mx_vect[ 3] - d_nx_vect[ 3]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 3];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 3]*mm*sin(alph) + n2*nn*d_mm_vect[ 3]*sin(alph) + n2*nn*mm*d_alpha[ 3]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 3]*nn*sin(alph) + m2*mm*d_nn_vect[ 3]*sin(alph) + m2*mm*nn*d_alpha[ 3]*cos(alph));
	d_alphax4_vect[ 3] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 4]*n_vect[1] + ps*d_nx_vect[ 4] - d_mx_vect[ 4]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 4];
	UP2 = d_ps_vect[ 4]*m_vect[1] + ps*d_mx_vect[ 4] - d_nx_vect[ 4]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 4];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 4]*mm*sin(alph) + n2*nn*d_mm_vect[ 4]*sin(alph) + n2*nn*mm*d_alpha[ 4]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 4]*nn*sin(alph) + m2*mm*d_nn_vect[ 4]*sin(alph) + m2*mm*nn*d_alpha[ 4]*cos(alph));
	d_alphax4_vect[ 4] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 5]*n_vect[1] + ps*d_nx_vect[ 5] - d_mx_vect[ 5]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 5];
	UP2 = d_ps_vect[ 5]*m_vect[1] + ps*d_mx_vect[ 5] - d_nx_vect[ 5]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 5];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 5]*mm*sin(alph) + n2*nn*d_mm_vect[ 5]*sin(alph) + n2*nn*mm*d_alpha[ 5]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 5]*nn*sin(alph) + m2*mm*d_nn_vect[ 5]*sin(alph) + m2*mm*nn*d_alpha[ 5]*cos(alph));
	d_alphax4_vect[ 5] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 6]*n_vect[1] + ps*d_nx_vect[ 6] - d_mx_vect[ 6]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 6];
	UP2 = d_ps_vect[ 6]*m_vect[1] + ps*d_mx_vect[ 6] - d_nx_vect[ 6]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 6];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 6]*mm*sin(alph) + n2*nn*d_mm_vect[ 6]*sin(alph) + n2*nn*mm*d_alpha[ 6]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 6]*nn*sin(alph) + m2*mm*d_nn_vect[ 6]*sin(alph) + m2*mm*nn*d_alpha[ 6]*cos(alph));
	d_alphax4_vect[ 6] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 7]*n_vect[1] + ps*d_nx_vect[ 7] - d_mx_vect[ 7]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 7];
	UP2 = d_ps_vect[ 7]*m_vect[1] + ps*d_mx_vect[ 7] - d_nx_vect[ 7]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 7];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 7]*mm*sin(alph) + n2*nn*d_mm_vect[ 7]*sin(alph) + n2*nn*mm*d_alpha[ 7]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 7]*nn*sin(alph) + m2*mm*d_nn_vect[ 7]*sin(alph) + m2*mm*nn*d_alpha[ 7]*cos(alph));
	d_alphax4_vect[ 7] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 8]*n_vect[1] + ps*d_nx_vect[ 8] - d_mx_vect[ 8]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 8];
	UP2 = d_ps_vect[ 8]*m_vect[1] + ps*d_mx_vect[ 8] - d_nx_vect[ 8]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 8];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 8]*mm*sin(alph) + n2*nn*d_mm_vect[ 8]*sin(alph) + n2*nn*mm*d_alpha[ 8]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 8]*nn*sin(alph) + m2*mm*d_nn_vect[ 8]*sin(alph) + m2*mm*nn*d_alpha[ 8]*cos(alph));
	d_alphax4_vect[ 8] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 9]*n_vect[1] + ps*d_nx_vect[ 9] - d_mx_vect[ 9]*n2 - m_vect[1]*2.0*nn*d_nn_vect[ 9];
	UP2 = d_ps_vect[ 9]*m_vect[1] + ps*d_mx_vect[ 9] - d_nx_vect[ 9]*m2 - n_vect[1]*2.0*mm*d_mm_vect[ 9];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 9]*mm*sin(alph) + n2*nn*d_mm_vect[ 9]*sin(alph) + n2*nn*mm*d_alpha[ 9]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 9]*nn*sin(alph) + m2*mm*d_nn_vect[ 9]*sin(alph) + m2*mm*nn*d_alpha[ 9]*cos(alph));
	d_alphax4_vect[ 9] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[10]*n_vect[1] + ps*d_nx_vect[10] - d_mx_vect[10]*n2 - m_vect[1]*2.0*nn*d_nn_vect[10];
	UP2 = d_ps_vect[10]*m_vect[1] + ps*d_mx_vect[10] - d_nx_vect[10]*m2 - n_vect[1]*2.0*mm*d_mm_vect[10];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[10]*mm*sin(alph) + n2*nn*d_mm_vect[10]*sin(alph) + n2*nn*mm*d_alpha[10]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[10]*nn*sin(alph) + m2*mm*d_nn_vect[10]*sin(alph) + m2*mm*nn*d_alpha[10]*cos(alph));
	d_alphax4_vect[10] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[11]*n_vect[1] + ps*d_nx_vect[11] - d_mx_vect[11]*n2 - m_vect[1]*2.0*nn*d_nn_vect[11];
	UP2 = d_ps_vect[11]*m_vect[1] + ps*d_mx_vect[11] - d_nx_vect[11]*m2 - n_vect[1]*2.0*mm*d_mm_vect[11];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[11]*mm*sin(alph) + n2*nn*d_mm_vect[11]*sin(alph) + n2*nn*mm*d_alpha[11]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[11]*nn*sin(alph) + m2*mm*d_nn_vect[11]*sin(alph) + m2*mm*nn*d_alpha[11]*cos(alph));
	d_alphax4_vect[11] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[12]*n_vect[1] + ps*d_nx_vect[12] - d_mx_vect[12]*n2 - m_vect[1]*2.0*nn*d_nn_vect[12];
	UP2 = d_ps_vect[12]*m_vect[1] + ps*d_mx_vect[12] - d_nx_vect[12]*m2 - n_vect[1]*2.0*mm*d_mm_vect[12];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[12]*mm*sin(alph) + n2*nn*d_mm_vect[12]*sin(alph) + n2*nn*mm*d_alpha[12]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[12]*nn*sin(alph) + m2*mm*d_nn_vect[12]*sin(alph) + m2*mm*nn*d_alpha[12]*cos(alph));
	d_alphax4_vect[12] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	}


void diff_alphay4_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_ny_vect[13], double d_mm_vect[13], double d_my_vect[13], double d_ps_vect[13], double *d_alphay4_vect)
	{
	/*raideur de alpha_x1*/
	
	double UU1,UP1,VV1,VP1,UU2,UP2,VV2,VP2,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU1 = ps*n_vect[2] - m_vect[2]*n2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV1 = n2*nn*mm*d_vect[1]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001);
			}
		else
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001-PI);
			}
		}
	UU2 = ps*m_vect[2] - n_vect[2]*m2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV2 = m2*mm*nn*d_vect[2]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001);
			}
		else
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001-PI);
			}
		}
	
	UP1 = d_ps_vect[ 1]*n_vect[2] + ps*d_ny_vect[ 1] - d_my_vect[ 1]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 1];
	UP2 = d_ps_vect[ 1]*m_vect[2] + ps*d_my_vect[ 1] - d_ny_vect[ 1]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 1];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 1]*mm*sin(alph) + n2*nn*d_mm_vect[ 1]*sin(alph) + n2*nn*mm*d_alpha[ 1]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 1]*nn*sin(alph) + m2*mm*d_nn_vect[ 1]*sin(alph) + m2*mm*nn*d_alpha[ 1]*cos(alph));
	d_alphay4_vect[ 1] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 2]*n_vect[2] + ps*d_ny_vect[ 2] - d_my_vect[ 2]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 2];
	UP2 = d_ps_vect[ 2]*m_vect[2] + ps*d_my_vect[ 2] - d_ny_vect[ 2]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 2];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 2]*mm*sin(alph) + n2*nn*d_mm_vect[ 2]*sin(alph) + n2*nn*mm*d_alpha[ 2]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 2]*nn*sin(alph) + m2*mm*d_nn_vect[ 2]*sin(alph) + m2*mm*nn*d_alpha[ 2]*cos(alph));
	d_alphay4_vect[ 2] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 3]*n_vect[2] + ps*d_ny_vect[ 3] - d_my_vect[ 3]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 3];
	UP2 = d_ps_vect[ 3]*m_vect[2] + ps*d_my_vect[ 3] - d_ny_vect[ 3]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 3];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 3]*mm*sin(alph) + n2*nn*d_mm_vect[ 3]*sin(alph) + n2*nn*mm*d_alpha[ 3]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 3]*nn*sin(alph) + m2*mm*d_nn_vect[ 3]*sin(alph) + m2*mm*nn*d_alpha[ 3]*cos(alph));
	d_alphay4_vect[ 3] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 4]*n_vect[2] + ps*d_ny_vect[ 4] - d_my_vect[ 4]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 4];
	UP2 = d_ps_vect[ 4]*m_vect[2] + ps*d_my_vect[ 4] - d_ny_vect[ 4]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 4];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 4]*mm*sin(alph) + n2*nn*d_mm_vect[ 4]*sin(alph) + n2*nn*mm*d_alpha[ 4]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 4]*nn*sin(alph) + m2*mm*d_nn_vect[ 4]*sin(alph) + m2*mm*nn*d_alpha[ 4]*cos(alph));
	d_alphay4_vect[ 4] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 5]*n_vect[2] + ps*d_ny_vect[ 5] - d_my_vect[ 5]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 5];
	UP2 = d_ps_vect[ 5]*m_vect[2] + ps*d_my_vect[ 5] - d_ny_vect[ 5]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 5];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 5]*mm*sin(alph) + n2*nn*d_mm_vect[ 5]*sin(alph) + n2*nn*mm*d_alpha[ 5]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 5]*nn*sin(alph) + m2*mm*d_nn_vect[ 5]*sin(alph) + m2*mm*nn*d_alpha[ 5]*cos(alph));
	d_alphay4_vect[ 5] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 6]*n_vect[2] + ps*d_ny_vect[ 6] - d_my_vect[ 6]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 6];
	UP2 = d_ps_vect[ 6]*m_vect[2] + ps*d_my_vect[ 6] - d_ny_vect[ 6]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 6];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 6]*mm*sin(alph) + n2*nn*d_mm_vect[ 6]*sin(alph) + n2*nn*mm*d_alpha[ 6]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 6]*nn*sin(alph) + m2*mm*d_nn_vect[ 6]*sin(alph) + m2*mm*nn*d_alpha[ 6]*cos(alph));
	d_alphay4_vect[ 6] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 7]*n_vect[2] + ps*d_ny_vect[ 7] - d_my_vect[ 7]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 7];
	UP2 = d_ps_vect[ 7]*m_vect[2] + ps*d_my_vect[ 7] - d_ny_vect[ 7]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 7];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 7]*mm*sin(alph) + n2*nn*d_mm_vect[ 7]*sin(alph) + n2*nn*mm*d_alpha[ 7]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 7]*nn*sin(alph) + m2*mm*d_nn_vect[ 7]*sin(alph) + m2*mm*nn*d_alpha[ 7]*cos(alph));
	d_alphay4_vect[ 7] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 8]*n_vect[2] + ps*d_ny_vect[ 8] - d_my_vect[ 8]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 8];
	UP2 = d_ps_vect[ 8]*m_vect[2] + ps*d_my_vect[ 8] - d_ny_vect[ 8]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 8];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 8]*mm*sin(alph) + n2*nn*d_mm_vect[ 8]*sin(alph) + n2*nn*mm*d_alpha[ 8]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 8]*nn*sin(alph) + m2*mm*d_nn_vect[ 8]*sin(alph) + m2*mm*nn*d_alpha[ 8]*cos(alph));
	d_alphay4_vect[ 8] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 9]*n_vect[2] + ps*d_ny_vect[ 9] - d_my_vect[ 9]*n2 - m_vect[2]*2.0*nn*d_nn_vect[ 9];
	UP2 = d_ps_vect[ 9]*m_vect[2] + ps*d_my_vect[ 9] - d_ny_vect[ 9]*m2 - n_vect[2]*2.0*mm*d_mm_vect[ 9];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 9]*mm*sin(alph) + n2*nn*d_mm_vect[ 9]*sin(alph) + n2*nn*mm*d_alpha[ 9]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 9]*nn*sin(alph) + m2*mm*d_nn_vect[ 9]*sin(alph) + m2*mm*nn*d_alpha[ 9]*cos(alph));
	d_alphay4_vect[ 9] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[10]*n_vect[2] + ps*d_ny_vect[10] - d_my_vect[10]*n2 - m_vect[2]*2.0*nn*d_nn_vect[10];
	UP2 = d_ps_vect[10]*m_vect[2] + ps*d_my_vect[10] - d_ny_vect[10]*m2 - n_vect[2]*2.0*mm*d_mm_vect[10];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[10]*mm*sin(alph) + n2*nn*d_mm_vect[10]*sin(alph) + n2*nn*mm*d_alpha[10]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[10]*nn*sin(alph) + m2*mm*d_nn_vect[10]*sin(alph) + m2*mm*nn*d_alpha[10]*cos(alph));
	d_alphay4_vect[10] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[11]*n_vect[2] + ps*d_ny_vect[11] - d_my_vect[11]*n2 - m_vect[2]*2.0*nn*d_nn_vect[11];
	UP2 = d_ps_vect[11]*m_vect[2] + ps*d_my_vect[11] - d_ny_vect[11]*m2 - n_vect[2]*2.0*mm*d_mm_vect[11];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[11]*mm*sin(alph) + n2*nn*d_mm_vect[11]*sin(alph) + n2*nn*mm*d_alpha[11]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[11]*nn*sin(alph) + m2*mm*d_nn_vect[11]*sin(alph) + m2*mm*nn*d_alpha[11]*cos(alph));
	d_alphay4_vect[11] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[12]*n_vect[2] + ps*d_ny_vect[12] - d_my_vect[12]*n2 - m_vect[2]*2.0*nn*d_nn_vect[12];
	UP2 = d_ps_vect[12]*m_vect[2] + ps*d_my_vect[12] - d_ny_vect[12]*m2 - n_vect[2]*2.0*mm*d_mm_vect[12];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[12]*mm*sin(alph) + n2*nn*d_mm_vect[12]*sin(alph) + n2*nn*mm*d_alpha[12]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[12]*nn*sin(alph) + m2*mm*d_nn_vect[12]*sin(alph) + m2*mm*nn*d_alpha[12]*cos(alph));
	d_alphay4_vect[12] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	}


void diff_alphaz4_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mz_vect[13], double d_ps_vect[13], double *d_alphaz4_vect)
	{
	/*raideur de alpha_x1*/
	
	double UU1,UP1,VV1,VP1,UU2,UP2,VV2,VP2,ps,n2,m2,nn,mm,n4,m4;
 	
	ps = produit_scal(n_vect, m_vect);
	n2 = produit_scal(n_vect, n_vect);
	m2 = produit_scal(m_vect, m_vect);
	nn = sqrt(n2);	mm = sqrt(m2);
	n4 = n2*n2;	m4 = m2*m2;
	
	UU1 = ps*n_vect[3] - m_vect[3]*n2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV1 = n2*nn*mm*d_vect[1]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001);
			}
		else
			{
			VV1 = n2*nn*mm*d_vect[1]*sin(0.00001-PI);
			}
		}
	UU2 = ps*m_vect[3] - n_vect[3]*m2;
	if ((fabs(alph) >= 0.00001) && (fabs(alph-PI) >= 0.00001))
		{
		VV2 = m2*mm*nn*d_vect[2]*sin(alph);
		}
	else	
		{
		if(fabs(alph) < 0.00001)
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001);
			}
		else
			{
			VV2 = m2*mm*nn*d_vect[2]*sin(0.00001-PI);
			}
		}
	
	UP1 = d_ps_vect[ 1]*n_vect[3] + ps*d_nz_vect[ 1] - d_mz_vect[ 1]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 1];
	UP2 = d_ps_vect[ 1]*m_vect[3] + ps*d_mz_vect[ 1] - d_nz_vect[ 1]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 1];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 1]*mm*sin(alph) + n2*nn*d_mm_vect[ 1]*sin(alph) + n2*nn*mm*d_alpha[ 1]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 1]*nn*sin(alph) + m2*mm*d_nn_vect[ 1]*sin(alph) + m2*mm*nn*d_alpha[ 1]*cos(alph));
	d_alphaz4_vect[ 1] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 2]*n_vect[3] + ps*d_nz_vect[ 2] - d_mz_vect[ 2]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 2];
	UP2 = d_ps_vect[ 2]*m_vect[3] + ps*d_mz_vect[ 2] - d_nz_vect[ 2]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 2];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 2]*mm*sin(alph) + n2*nn*d_mm_vect[ 2]*sin(alph) + n2*nn*mm*d_alpha[ 2]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 2]*nn*sin(alph) + m2*mm*d_nn_vect[ 2]*sin(alph) + m2*mm*nn*d_alpha[ 2]*cos(alph));
	d_alphaz4_vect[ 2] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 3]*n_vect[3] + ps*d_nz_vect[ 3] - d_mz_vect[ 3]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 3];
	UP2 = d_ps_vect[ 3]*m_vect[3] + ps*d_mz_vect[ 3] - d_nz_vect[ 3]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 3];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 3]*mm*sin(alph) + n2*nn*d_mm_vect[ 3]*sin(alph) + n2*nn*mm*d_alpha[ 3]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 3]*nn*sin(alph) + m2*mm*d_nn_vect[ 3]*sin(alph) + m2*mm*nn*d_alpha[ 3]*cos(alph));
	d_alphaz4_vect[ 3] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 4]*n_vect[3] + ps*d_nz_vect[ 4] - d_mz_vect[ 4]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 4];
	UP2 = d_ps_vect[ 4]*m_vect[3] + ps*d_mz_vect[ 4] - d_nz_vect[ 4]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 4];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 4]*mm*sin(alph) + n2*nn*d_mm_vect[ 4]*sin(alph) + n2*nn*mm*d_alpha[ 4]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 4]*nn*sin(alph) + m2*mm*d_nn_vect[ 4]*sin(alph) + m2*mm*nn*d_alpha[ 4]*cos(alph));
	d_alphaz4_vect[ 4] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 5]*n_vect[3] + ps*d_nz_vect[ 5] - d_mz_vect[ 5]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 5];
	UP2 = d_ps_vect[ 5]*m_vect[3] + ps*d_mz_vect[ 5] - d_nz_vect[ 5]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 5];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 5]*mm*sin(alph) + n2*nn*d_mm_vect[ 5]*sin(alph) + n2*nn*mm*d_alpha[ 5]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 5]*nn*sin(alph) + m2*mm*d_nn_vect[ 5]*sin(alph) + m2*mm*nn*d_alpha[ 5]*cos(alph));
	d_alphaz4_vect[ 5] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 6]*n_vect[3] + ps*d_nz_vect[ 6] - d_mz_vect[ 6]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 6];
	UP2 = d_ps_vect[ 6]*m_vect[3] + ps*d_mz_vect[ 6] - d_nz_vect[ 6]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 6];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 6]*mm*sin(alph) + n2*nn*d_mm_vect[ 6]*sin(alph) + n2*nn*mm*d_alpha[ 6]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 6]*nn*sin(alph) + m2*mm*d_nn_vect[ 6]*sin(alph) + m2*mm*nn*d_alpha[ 6]*cos(alph));
	d_alphaz4_vect[ 6] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 7]*n_vect[3] + ps*d_nz_vect[ 7] - d_mz_vect[ 7]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 7];
	UP2 = d_ps_vect[ 7]*m_vect[3] + ps*d_mz_vect[ 7] - d_nz_vect[ 7]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 7];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 7]*mm*sin(alph) + n2*nn*d_mm_vect[ 7]*sin(alph) + n2*nn*mm*d_alpha[ 7]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 7]*nn*sin(alph) + m2*mm*d_nn_vect[ 7]*sin(alph) + m2*mm*nn*d_alpha[ 7]*cos(alph));
	d_alphaz4_vect[ 7] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 8]*n_vect[3] + ps*d_nz_vect[ 8] - d_mz_vect[ 8]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 8];
	UP2 = d_ps_vect[ 8]*m_vect[3] + ps*d_mz_vect[ 8] - d_nz_vect[ 8]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 8];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 8]*mm*sin(alph) + n2*nn*d_mm_vect[ 8]*sin(alph) + n2*nn*mm*d_alpha[ 8]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 8]*nn*sin(alph) + m2*mm*d_nn_vect[ 8]*sin(alph) + m2*mm*nn*d_alpha[ 8]*cos(alph));
	d_alphaz4_vect[ 8] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[ 9]*n_vect[3] + ps*d_nz_vect[ 9] - d_mz_vect[ 9]*n2 - m_vect[3]*2.0*nn*d_nn_vect[ 9];
	UP2 = d_ps_vect[ 9]*m_vect[3] + ps*d_mz_vect[ 9] - d_nz_vect[ 9]*m2 - n_vect[3]*2.0*mm*d_mm_vect[ 9];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[ 9]*mm*sin(alph) + n2*nn*d_mm_vect[ 9]*sin(alph) + n2*nn*mm*d_alpha[ 9]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[ 9]*nn*sin(alph) + m2*mm*d_nn_vect[ 9]*sin(alph) + m2*mm*nn*d_alpha[ 9]*cos(alph));
	d_alphaz4_vect[ 9] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[10]*n_vect[3] + ps*d_nz_vect[10] - d_mz_vect[10]*n2 - m_vect[3]*2.0*nn*d_nn_vect[10];
	UP2 = d_ps_vect[10]*m_vect[3] + ps*d_mz_vect[10] - d_nz_vect[10]*m2 - n_vect[3]*2.0*mm*d_mm_vect[10];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[10]*mm*sin(alph) + n2*nn*d_mm_vect[10]*sin(alph) + n2*nn*mm*d_alpha[10]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[10]*nn*sin(alph) + m2*mm*d_nn_vect[10]*sin(alph) + m2*mm*nn*d_alpha[10]*cos(alph));
	d_alphaz4_vect[10] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[11]*n_vect[3] + ps*d_nz_vect[11] - d_mz_vect[11]*n2 - m_vect[3]*2.0*nn*d_nn_vect[11];
	UP2 = d_ps_vect[11]*m_vect[3] + ps*d_mz_vect[11] - d_nz_vect[11]*m2 - n_vect[3]*2.0*mm*d_mm_vect[11];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[11]*mm*sin(alph) + n2*nn*d_mm_vect[11]*sin(alph) + n2*nn*mm*d_alpha[11]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[11]*nn*sin(alph) + m2*mm*d_nn_vect[11]*sin(alph) + m2*mm*nn*d_alpha[11]*cos(alph));
	d_alphaz4_vect[11] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	
	UP1 = d_ps_vect[12]*n_vect[3] + ps*d_nz_vect[12] - d_mz_vect[12]*n2 - m_vect[3]*2.0*nn*d_nn_vect[12];
	UP2 = d_ps_vect[12]*m_vect[3] + ps*d_mz_vect[12] - d_nz_vect[12]*m2 - n_vect[3]*2.0*mm*d_mm_vect[12];
	VP1 = d_vect[1]*(3.0*n2*d_nn_vect[12]*mm*sin(alph) + n2*nn*d_mm_vect[12]*sin(alph) + n2*nn*mm*d_alpha[12]*cos(alph));
	VP2 = d_vect[2]*(3.0*m2*d_mm_vect[12]*nn*sin(alph) + m2*mm*d_nn_vect[12]*sin(alph) + m2*mm*nn*d_alpha[12]*cos(alph));
	d_alphaz4_vect[12] = (v_vect[3]-v_vect[1])*(UP1*VV1 - UU1*VP1)/VV1/VV1 + (v_vect[2]-v_vect[3])*(UP2*VV2 - UU2*VP2)/VV2/VV2;
	}




